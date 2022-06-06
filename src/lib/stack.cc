#include "stack.h"

word Stack::at_top() { return stack[top]; }
word Stack::pop() {
  word top_val = at_top();
  top--;
  return top_val;
}
void Stack::push(word value) {
  top++;
  stack[top] = value;
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
