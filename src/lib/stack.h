#pragma once
#ifndef STACK_H
#define STACK_H
#include "core.h"
#include <iostream>
#include <map>

using namespace std;
struct Stack_frame {
  int top = -1;

  word stack[STACK_SIZE];

  word at_top();

  word pop();

  void push(word value);

  void stdout_dump();
  void op_stdout_dump();

  int op_top = -1;
  word op_stack[STACK_SIZE];

  int alloc_loc(int size);
  void push_loc(word addr, word value);
  void pop_loc(int64_t id);
};

struct Call_stack {
  int pointer = -1;
  Stack_frame stack[STACK_SIZE];

  void push_frame();
  void pop_frame();
  int top = -1;
};
#endif
