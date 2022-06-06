#include "stack.h"

word Stack::at_top() { return stack[top]; }

word Stack::pop() {
  word top_val = at_top();
  top--;
  return top_val;
}

void Stack::pop_frame() {
  pointer = pointer - top;
  top = pointer;
}

void Stack::push(word value) {
  top++;
  stack[top] = value;
}

void Stack::push_frame() {
  top++;
  pointer = top;
}

void Stack::stdout_dump() {
  cout << "stack:" << endl;
  if (top == -1) {
    cout << "  [empty]" << endl;
    return;
  }
  for (int i = 0; i < top + 1; i++) {
    cout << "  " << i << ": " << stack[i].INT << endl;
  }
}
void Stack::op_stdout_dump() {
  cout << "operator stack:" << endl;
  if (op_top == -1) {
    cout << "  [empty]" << endl;
    return;
  }
  for (int i = 0; i < op_top + 1; i++) {
    cout << "  " << i << ": " << op_stack[i].INT << endl;
  }
}

void Stack::push_loc(word value) {
  op_top++;
  op_stack[op_top] = value;
}
void Stack::pop_loc(int64_t id) { op_top = op_top - id; }
