// Copyright (c) 2022 Ashtyn Morel-Blake
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "vm.h"

word Worms::load_program(vector<Inst> prog) {
    program = prog;
    return IWORD(TRAP_OK);
}

word Worms::exec() {
    Inst in = program[ip.value.INT];
    switch (in.opcode.value.INT) {

    case HALT_INST: {
        halted = true;
        break;
    }

    case PUSH_INST: {
        if (stack.top + 1 >= STACK_SIZE) {
            return IWORD(TRAP_STACK_OVERFLOW);
        }
        stack.push(in.params[0]);
        ip.value.INT++;
        break;
    }
    case POP_INST: {
        if (stack.top < 0) {
            return IWORD(TRAP_STACK_UNDERFLOW);
        }
        stack.pop();
        ip.value.INT++;
        break;
    }

    case DUP_INST: {
        word to_dup;
        if (in.flags[0].value.INT == 0) {
            to_dup = stack.at_top();
        } else if (in.flags[0].value.INT == 1) {

            if (in.params[0].value.INT >= STACK_SIZE) {
                return IWORD(TRAP_STACK_OVERFLOW);
            }

            if (in.params[0].value.INT < 0) {
                return IWORD(TRAP_STACK_UNDERFLOW);
            }

            to_dup = stack.stack[in.params[0].value.INT];
        } else {
            return IWORD(TRAP_UNKNOWN_FLAG);
        }

        if (in.flags[1].value.INT == 0) {
            stack.push(to_dup);
        } else {
            return IWORD(TRAP_UNKNOWN_FLAG);
        }
        ip.value.INT++;
        break;
    }

    case ADD_INST: {
        if (stack.top - 1 < 0) {
            return IWORD(TRAP_STACK_UNDERFLOW);
        }
        word num1 = stack.pop();
        word num2 = stack.pop();
        MATH_OP(+, num1, num2);
        ip.value.INT++;
        break;
    }
    case SUB_INST: {
        if (stack.top - 1 < 0) {
            return IWORD(TRAP_STACK_UNDERFLOW);
        }
        word num1 = stack.pop();
        word num2 = stack.pop();

        MATH_OP(-, num1, num2);
        ip.value.INT++;
        break;
    }
    case MUL_INST: {
        if (stack.top - 1 < 0) {
            return IWORD(TRAP_STACK_UNDERFLOW);
        }
        word num1 = stack.pop();
        word num2 = stack.pop();

        MATH_OP(*, num1, num2);
        ip.value.INT++;
        break;
    }
    case DIV_INST: {
        if (stack.top - 1 < 0) {
            return IWORD(TRAP_STACK_UNDERFLOW);
        }
        word num1 = stack.pop();
        word num2 = stack.pop();

        if (num2.value.INT <= 0) {
            return IWORD(TRAP_DIVIDE_ZERO);
        }
        MATH_OP(/, num1, num2);
        ip.value.INT++;
        break;
    }
    case EQ_INST: {
        if (stack.top - 1 < 0) {
            return IWORD(TRAP_STACK_UNDERFLOW);
        }
        word e1 = stack.pop();
        word e2 = stack.pop();
        COMP_OP(==, e1, e2);

        ip.value.INT++;
        break;
    }
    case N_EQ_INST: {
        if (stack.top - 1 < 0) {
            return IWORD(TRAP_STACK_UNDERFLOW);
        }
        word e1 = stack.pop();
        word e2 = stack.pop();
        COMP_OP(!=, e1, e2);

        ip.value.INT++;
        break;
    }
    case JMP_INST: {
        if (in.params[0].value.INT < 0 ||
            in.params[0].value.INT >= (int)program.size()) {
            return IWORD(TRAP_BAD_JUMP);
        }

        // If equal jump
        if (in.flags[0].value.INT == 1) {
            if (stack.top - 1 < 0) {
                return IWORD(TRAP_STACK_UNDERFLOW);
            }
            word e1 = stack.pop();
            if (e1.value.INT != 0) {
                ip.value.INT++;
                break;
            }
        } else if (in.flags[0].value.INT == 0) {
        } else {
            return IWORD(TRAP_UNKNOWN_FLAG);
        }

        last_jmp = ip;
        ip = in.params[0];
        jump_count.value.INT++;
        break;
    }
    case GET_LOCAL_INST: {
        int addr = in.params[0].value.INT + 1;
        int length = stack.op_stack[in.params[0].value.INT].value.INT;
        for (int i = addr; i < addr + length; i++) {
            stack.push(stack.op_stack[i]);
        }
        stack.push(IWORD(length));
        ip.value.INT++;
        break;
    }
    case FREE_LOCAL_INST: {
        int addr = in.params[0].value.INT;
        stack.pop_loc(addr);
        ip.value.INT++;
        break;
    }
    case LOAD_LOCAL_INST: {
        if (stack.top == -1) {
            return IWORD(TRAP_STACK_UNDERFLOW);
        }
        if (in.params[0].value.INT == 0) {
            word w = stack.pop();
            int addr = stack.alloc_loc(1);
            stack.push(IWORD(addr));
            stack.push_loc(IWORD(addr + 1), w);
        } else {
            int addr = stack.alloc_loc(in.params[0].value.INT) + 1;
            stack.push(IWORD(addr - 1));
            int length = in.params[0].value.INT;
            word val;
            for (int i = 0; i < length; i++) {
                val = stack.pop();
                int index = addr + i;
                stack.push_loc(IWORD(index), val);
            }
        }
        ip.value.INT++;
        break;
    }
    case ALLOC_LOCAL_INST: {
        int addr = stack.alloc_loc(in.params[0].value.INT);
        stack.push(IWORD(addr));
        ip.value.INT++;
        break;
    }
    case INDEX_LOAD_LOCAL_INST: {
        int addr = in.params[0].value.INT;
        int offset = in.params[1].value.INT;
        stack.op_stack[addr + 1 + offset] = stack.pop();
        ip.value.INT++;
        break;
    }
    }
    return IWORD(TRAP_OK);
}
string Worms::debug(word trap) {
    switch (trap.value.INT) {
    case TRAP_STACK_OVERFLOW:
        return "TRAP_STACK_OVERFLOW";
    case TRAP_STACK_UNDERFLOW:
        return "TRAP_STACK_UNDERFLOW";
    case TRAP_UNKNOWN_FLAG:
        return "TRAP_UNKNOWN_FLAG";
    case TRAP_DIVIDE_ZERO:
        return "TRAP_DIVIDE_ZERO";
    case TRAP_BAD_JUMP:
        return "TRAP_BAD_JUMP";
    case TRAP_MAXIMUM_JUMP_STACK_EXCEEDED:
        return "TRAP_MAXIMUM_JUMP_STACK_EXCEEDED";
    default:
        return "";
    };
}
void Worms::run() {
    while (!halted) {
        if (full_trace) {
            program.at(ip.value.INT).debug(ip);
        }
        word status = exec();
        if (full_trace) {
            stack.stdout_dump();
            stack.op_stdout_dump();
            cout << "\n==============================\n\n";
        }
        if (jump_count.value.INT == 60) {
            status = IWORD(TRAP_MAXIMUM_JUMP_STACK_EXCEEDED);
            ip = last_jmp;
        }
        if (last_jmp.value.INT >= 0 && ip.value.INT > last_jmp.value.INT) {
            last_jmp.value.INT = -1;
            jump_count.value.INT = 0;
        }
        if (status.value.INT != TRAP_OK) {
            cout << debug(status) << " AT ADDRESS " << ip.value.INT
                 << ": WITH OPCODE "
                 << program.at(ip.value.INT).opcode.value.INT << endl;
            break;
        }
    }
}
