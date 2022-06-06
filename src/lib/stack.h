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
};
