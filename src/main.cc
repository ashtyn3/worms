#include <iostream>

#include <vector>

using namespace std;

enum Traps {
  TRAP_OK,
  TRAP_STACK_OVERFLOW,
  TRAP_STACK_UNDERFLOW,
  TRAP_UNKNOWN_FLAG,
  TRAP_DIVIDE_ZERO,
  TRAP_BAD_JUMP,
  TRAP_MAXIMUM_JUMP_STACK_EXCEEDED
};
enum {
  PUSH_INST,
  POP_INST,
  HALT_INST,
  DUP_INST,
  ADD_INST,
  SUB_INST,
  MUL_INST,
  DIV_INST,
  JMP_INST,
  EQ_INST,
  N_EQ_INST,
};
#define PUSH(value)                                                            \
  { .opcode = PUSH_INST, .params = value }

#define HALT                                                                   \
  { .opcode = HALT_INST }

#define POP                                                                    \
  { .opcode = POP_INST }

#define DUP(flags, params)                                                     \
  { .opcode = DUP_INST, flags, params }

#define ADD                                                                    \
  { .opcode = ADD_INST }

#define SUB                                                                    \
  { .opcode = SUB_INST }
#define MUL                                                                    \
  { .opcode = MUL_INST }

#define DIV                                                                    \
  { .opcode = DIV_INST }

#define JMP(value, value2)                                                     \
  { .opcode = JMP_INST, .flags = value, .params = value2 }

#define EQ                                                                     \
  { .opcode = EQ_INST }

#define N_EQ                                                                   \
  { .opcode = N_EQ_INST }

typedef int64_t word;
struct Stack {
  int top = -1;
  vector<word> stack;
  word at_top() { return stack.at(top); }
  word pop() {
    word top_val = at_top();
    stack.pop_back();
    top--;
    return top_val;
  }
  void push(word value) {
    top++;
    stack.push_back(value);
  }
  void stdout_dump() {
    cout << "stack:" << endl;
    if (stack.size() == 0) {
      cout << "  [empty]" << endl;
      return;
    }
    for (int i = 0; i < stack.size(); i++) {
      cout << "  " << i << ": " << stack.at(i) << endl;
    }
  }
};

#define STACK_SIZE 200000

struct Inst {
  word opcode;
  word flags[3];
  word params[5];
  void debug(word ip) {
    cout << ip << ": ";
    switch (opcode) {
    case PUSH_INST:
      cout << "<" << opcode << "> PUSH";
      break;
    case POP_INST:
      cout << "<" << opcode << "> POP";
      break;
    case HALT_INST:
      cout << "<" << opcode << "> HALT";
      break;
    case ADD_INST:
      cout << "<" << opcode << "> ADD";
      break;
    case SUB_INST:
      cout << "<" << opcode << "> SUB";
      break;
    case MUL_INST:
      cout << "<" << opcode << "> SUB";
      break;
    case DIV_INST:
      cout << "<" << opcode << "> DIV";
      break;
    case EQ_INST:
      cout << "<" << opcode << "> EQ";
      break;
    case N_EQ_INST:
      cout << "<" << opcode << "> NEQ";
      break;
    case DUP_INST:
      cout << "<" << opcode << "> DUP";
      break;
    case JMP_INST:
      cout << "<" << opcode << "> JMP";
      break;
    }
    cout << "\n  FLAGS: ";
    for (int i = 0; i < 3; i++) {
      cout << flags[i] << " ";
    }
    cout << "\n  PARAMS: ";
    for (int i = 0; i < 5; i++) {
      cout << params[i] << " ";
    }
    cout << endl;
  }
};

struct Worms {
  word ip;
  vector<Inst> program;
  Stack stack;
  bool halted;
  bool full_trace;
  word jump_count = 0;
  word last_jmp = -1;
  word load_program(vector<Inst> prog) {
    program = prog;
    return TRAP_OK;
  }
  word exec() {
    Inst in = program[ip];
    switch (in.opcode) {

    case HALT_INST: {
      halted = true;
      break;
    }

    case PUSH_INST: {
      if (stack.stack.size() + 1 >= STACK_SIZE) {
        return TRAP_STACK_OVERFLOW;
      }
      stack.push(in.params[0]);
      ip++;
      break;
    }
    case POP_INST: {
      if ((signed int)stack.stack.size() - 1 < 0) {
        return TRAP_STACK_UNDERFLOW;
      }
      stack.pop();
      ip++;
      break;
    }

    case DUP_INST: {
      word to_dup;
      if (in.flags[0] == 0) {
        to_dup = stack.at_top();
      } else if (in.flags[0] == 1) {

        if (in.params[0] >= STACK_SIZE) {
          return TRAP_STACK_OVERFLOW;
        }

        if (in.params[0] < 0) {
          return TRAP_STACK_UNDERFLOW;
        }

        to_dup = stack.stack.at(in.params[0]);
      } else {
        return TRAP_UNKNOWN_FLAG;
      }

      if (in.flags[1] == 0) {
        stack.push(to_dup);
      } else {
        return TRAP_UNKNOWN_FLAG;
      }
      ip++;
      break;
    }

    case ADD_INST: {
      if ((signed int)stack.stack.size() - 2 < 0) {
        return TRAP_STACK_UNDERFLOW;
      }
      word num1 = stack.pop();
      word num2 = stack.pop();

      stack.push(num1 + num2);
      ip++;
      break;
    }
    case SUB_INST: {
      if ((signed int)stack.stack.size() - 2 < 0) {
        return TRAP_STACK_UNDERFLOW;
      }
      word num1 = stack.pop();
      word num2 = stack.pop();

      stack.push(num1 - num2);
      ip++;
      break;
    }
    case MUL_INST: {
      if ((signed int)stack.stack.size() - 2 < 0) {
        return TRAP_STACK_UNDERFLOW;
      }
      word num1 = stack.pop();
      word num2 = stack.pop();

      stack.push(num1 * num2);
      ip++;
      break;
    }
    case DIV_INST: {
      if ((signed int)stack.stack.size() - 2 < 0) {
        return TRAP_STACK_UNDERFLOW;
      }
      word num1 = stack.pop();
      word num2 = stack.pop();

      if (num2 <= 0) {
        return TRAP_DIVIDE_ZERO;
      }
      stack.push(num1 / num2);
      ip++;
      break;
    }
    case EQ_INST: {
      if ((signed int)stack.stack.size() - 2 < 0) {
        return TRAP_STACK_UNDERFLOW;
      }
      word e1 = stack.pop();
      word e2 = stack.pop();
      if (e1 == e2) {
        stack.push(0);
      } else {
        stack.push(1);
      }

      ip++;
      break;
    }
    case N_EQ_INST: {
      if ((signed int)stack.stack.size() - 2 < 0) {
        return TRAP_STACK_UNDERFLOW;
      }
      word e1 = stack.pop();
      word e2 = stack.pop();
      if (e1 != e2) {
        stack.push(0);
      } else {
        stack.push(1);
      }

      ip++;
      break;
    }
    case JMP_INST: {
      if (in.params[0] < 0 || in.params[0] >= program.size()) {
        return TRAP_BAD_JUMP;
      }

      // If equal jump
      if (in.flags[0] == 1) {
        if ((signed int)stack.stack.size() - 1 < 0) {
          return TRAP_STACK_UNDERFLOW;
        }
        word e1 = stack.pop();
        if (e1 != 0) {
          ip++;
          break;
        }
      } else if (in.flags[0] == 0) {
      } else {
        return TRAP_UNKNOWN_FLAG;
      }

      last_jmp = ip;
      ip = in.params[0];
      jump_count++;
      break;
    }
    }
    return TRAP_OK;
  }
  string debug(word trap) {
    switch (trap) {
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
  void run() {
    while (!halted) {
      if (full_trace) {
        program.at(ip).debug(ip);
      }
      word status = exec();
      if (full_trace) {
        stack.stdout_dump();
        cout << "\n==============================\n\n";
      }
      if (jump_count == 60) {
        status = TRAP_MAXIMUM_JUMP_STACK_EXCEEDED;
        ip = last_jmp;
      }
      if (last_jmp >= 0 && ip > last_jmp) {
        last_jmp = -1;
        jump_count = 0;
      }
      if (status != TRAP_OK) {
        cout << debug(status) << " AT ADDRESS " << ip << ": WITH OPCODE "
             << program.at(ip).opcode << endl;
        break;
      }
    }
  }
};

int main() {
  vector<Inst> prog = {PUSH({0}),  PUSH({1}), ADD,           DUP({}, {}),
                       PUSH({10}), N_EQ,      JMP({1}, {1}), HALT};
  Worms *hi = new Worms;
  hi->full_trace = true;
  hi->load_program(prog);
  hi->run();
}
