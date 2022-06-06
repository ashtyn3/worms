#pragma once

#include "core.h"
#include "inst.h"
#include "stack.h"
#include "traps.h"
#include <vector>

struct Worms {
  word ip;
  vector<Inst> program;
  Stack stack;
  bool halted;
  bool full_trace;
  word jump_count = {.INT = 0};
  word last_jmp = {.INT = static_cast<uint64_t>(-1)};
  word load_program(vector<Inst> prog);
  word exec();
  string debug(word trap);
  void run();
};
