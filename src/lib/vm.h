#pragma once
#ifndef VM_H
#define VM_H
#include "core.h"
#include "inst.h"
#include "stack.h"
#include "traps.h"
#include <vector>

struct Worms {
  word ip;
  vector<Inst> program;
  Stack_frame stack;
  bool halted;
  bool full_trace;
  word jump_count = IWORD(0);
  word last_jmp = IWORD(-1);
  word load_program(vector<Inst> prog);
  word exec();
  string debug(word trap);
  void run();
};
#endif
