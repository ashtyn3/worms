#include "stack.h"

word Stack_frame::at_top() { return stack[top]; }

word Stack_frame::pop() {
  word value = at_top();
  top--;
  return value;
}

void Stack_frame::push(word value) {
  top++;
  stack[top] = value;
}

void Stack_frame::stdout_dump() {
  cout << "stack:" << endl;
  if (top == -1) {
    cout << "  [empty]" << endl;
    return;
  }
  for (int i = 0; i < top + 1; i++) {
    cout << "  " << i << ": " << GET_VALUE(stack[i]) << endl;
  }
}
void Stack_frame::op_stdout_dump() {
  cout << "operator stack:" << endl;
  if (op_top == -1) {
    cout << "  [empty]" << endl;
    return;
  }
  for (int i = 0; op_stack[i].t_flag != -1; i++) {
    cout << "  " << i << ": " << GET_VALUE(op_stack[i]) << endl;
  }
}

int Stack_frame::alloc_loc(int size) {
  int start_addr = -1;
  int space = 0;
  for (int i = 0; i < STACK_SIZE; i++) {
    if (space == size + 1) {
      break;
    }
    if (op_stack[i].value.INT == 0 && op_stack[i].value.FLOAT == 0.0 &&
        op_stack[i].value.INT16 == 0 && op_stack[i].value.INT32 == 0 &&
        op_stack[i].value.INT8 == 0) {
      if (start_addr == -1) {
        start_addr = i;
      } else {
        space++;
      }
    } else {
      space = 0;
      start_addr = -1;
    }
  }

  if (start_addr > -1) {
    op_stack[start_addr] = IWORD(size);
  }

  return start_addr;
}

void Stack_frame::push_loc(word addr, word value) {
  op_top++;
  op_stack[addr.value.INT] = value;
}

void Stack_frame::pop_loc(int64_t id) {
  for (int i = id; i < op_stack[id].value.INT; i++) {
    op_stack[i] = {};
  }
}

// call stack related functions ->

void Call_stack::push_frame() {
  top++;
  pointer = top;
}

void Call_stack::pop_frame() {
  pointer = pointer - top;
  top = pointer;
}
