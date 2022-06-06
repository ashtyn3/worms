#pragma once

#include "core.h"
#include <iostream>

using namespace std;
struct Stack {
  int top = -1;
  int pointer = -1;

  word stack[STACK_SIZE];

  word at_top();
  word pop();
  void push(word value);
  void stdout_dump();
  void op_stdout_dump();
  void push_frame();
  void pop_frame();

  int op_top = -1;
  word op_stack[STACK_SIZE];

  void push_loc(word value);
  void pop_loc(int64_t id);
};
