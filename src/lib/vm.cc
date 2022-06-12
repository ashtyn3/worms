#include "vm.h"

word Worms::load_program(vector<Inst> prog) {
  program = prog;
  return {.INT = TRAP_OK};
}

word Worms::exec() {
  Inst in = program[ip.INT];
  switch (in.opcode.INT) {

  case HALT_INST: {
    halted = true;
    break;
  }

  case PUSH_INST: {
    if (stack.top + 1 >= STACK_SIZE) {
      return {.INT = TRAP_STACK_OVERFLOW};
    }
    stack.push(in.params[0]);
    ip.INT++;
    break;
  }
  case POP_INST: {
    if (stack.top - 1 < 0) {
      return {.INT = TRAP_STACK_UNDERFLOW};
    }
    stack.pop();
    ip.INT++;
    break;
  }

  case DUP_INST: {
    word to_dup;
    if (in.flags[0].INT == 0) {
      to_dup = stack.at_top();
    } else if (in.flags[0].INT == 1) {

      if (in.params[0].INT >= STACK_SIZE) {
        return {.INT = TRAP_STACK_OVERFLOW};
      }

      if (in.params[0].INT < 0) {
        return {.INT = TRAP_STACK_UNDERFLOW};
      }

      to_dup = stack.stack[in.params[0].INT];
    } else {
      return {.INT = TRAP_UNKNOWN_FLAG};
    }

    if (in.flags[1].INT == 0) {
      stack.push(to_dup);
    } else {
      return {.INT = TRAP_UNKNOWN_FLAG};
    }
    ip.INT++;
    break;
  }

  case ADD_INST: {
    if (stack.top - 1 < 0) {
      return {.INT = TRAP_STACK_UNDERFLOW};
    }
    word num1 = stack.pop();
    word num2 = stack.pop();

    stack.push({.INT = num1.INT + num2.INT});
    ip.INT++;
    break;
  }
  case SUB_INST: {
    if (stack.top - 1 < 0) {
      return {.INT = TRAP_STACK_UNDERFLOW};
    }
    word num1 = stack.pop();
    word num2 = stack.pop();

    stack.push({.INT = num1.INT - num2.INT});
    ip.INT++;
    break;
  }
  case MUL_INST: {
    if (stack.top - 1 < 0) {
      return {.INT = TRAP_STACK_UNDERFLOW};
    }
    word num1 = stack.pop();
    word num2 = stack.pop();

    stack.push({.INT = num1.INT * num2.INT});
    ip.INT++;
    break;
  }
  case DIV_INST: {
    if (stack.top - 1 < 0) {
      return {.INT = TRAP_STACK_UNDERFLOW};
    }
    word num1 = stack.pop();
    word num2 = stack.pop();

    if (num2.INT <= 0) {
      return {.INT = TRAP_DIVIDE_ZERO};
    }
    stack.push({.INT = num1.INT / num2.INT});
    ip.INT++;
    break;
  }
  case EQ_INST: {
    if (stack.top - 1 < 0) {
      return {.INT = TRAP_STACK_UNDERFLOW};
    }
    word e1 = stack.pop();
    word e2 = stack.pop();
    if (e1.INT == e2.INT) {
      stack.push({.INT = 0});
    } else {
      stack.push({.INT = 1});
    }

    ip.INT++;
    break;
  }
  case N_EQ_INST: {
    if (stack.top - 1 < 0) {
      return {.INT = TRAP_STACK_UNDERFLOW};
    }
    word e1 = stack.pop();
    word e2 = stack.pop();
    if (e1.INT != e2.INT) {
      stack.push({.INT = 0});
    } else {
      stack.push({.INT = 1});
    }

    ip.INT++;
    break;
  }
  case JMP_INST: {
    if (in.params[0].INT < 0 || in.params[0].INT >= (int)program.size()) {
      return {.INT = TRAP_BAD_JUMP};
    }

    // If equal jump
    if (in.flags[0].INT == 1) {
      if (stack.top - 1 < 0) {
        return {.INT = TRAP_STACK_UNDERFLOW};
      }
      word e1 = stack.pop();
      if (e1.INT != 0) {
        ip.INT++;
        break;
      }
    } else if (in.flags[0].INT == 0) {
    } else {
      return {.INT = TRAP_UNKNOWN_FLAG};
    }

    last_jmp = ip;
    ip = in.params[0];
    jump_count.INT++;
    break;
  }
  case GET_LOCAL_INST: {
    stack.push(stack.op_stack[in.params[0].INT]);
    ip.INT++;
    break;
  }
  case LOAD_LOCAL_INST: {
    if (stack.top == -1) {
      return {.INT = TRAP_STACK_UNDERFLOW};
    }
    word w = stack.pop();
    stack.push_loc(w);
    ip.INT++;
    break;
  }
  }
  return {.INT = TRAP_OK};
}
string Worms::debug(word trap) {
  switch (trap.INT) {
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
      program.at(ip.INT).debug(ip);
    }
    word status = exec();
    if (full_trace) {
      stack.stdout_dump();
      stack.op_stdout_dump();
      cout << "\n==============================\n\n";
    }
    if (jump_count.INT == 60) {
      status = {.INT = TRAP_MAXIMUM_JUMP_STACK_EXCEEDED};
      ip = last_jmp;
    }
    if (last_jmp.INT >= 0 && ip.INT > last_jmp.INT) {
      last_jmp.INT = -1;
      jump_count.INT = 0;
    }
    if (status.INT != TRAP_OK) {
      cout << debug(status) << " AT ADDRESS " << ip.INT << ": WITH OPCODE "
           << program.at(ip.INT).opcode.INT << endl;
      break;
    }
  }
}
