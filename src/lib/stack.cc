#include "stack.h"
#include "utils.h"

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
    cout << "  " << i << ": " << stack[i].INT << endl;
  }
}
void Stack_frame::op_stdout_dump() {
  cout << "operator stack:" << endl;
  if (op_top == -1) {
    cout << "  [empty]" << endl;
    return;
  }
  for (int i = 0; i < op_top + 1; i++) {
    cout << "  " << i << ": " << op_stack[i].INT << endl;
  }
}

void Stack_frame::push_loc(word value) {
  op_top++;
  op_stack[op_top] = value;
}
void Stack_frame::pop_loc(int64_t id) { op_top = op_top - id; }

// call stack related functions ->

void Call_stack::push_frame() {
  top++;
  pointer = top;
}
void Call_stack::pop_frame() {
  pointer = pointer - top;
  top = pointer;
}
