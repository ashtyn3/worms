#ifndef BYTE_GEN_H
#define BYTE_GEN_H
#include "../lib/inst.h"
#include "module.h"
#include <cstdint>
union IEEE_754 {
  uint8_t bytes[4];
  float fp;
};

class snailer_byte_generator {
  Inst *reproduce_inst(uint8_t *inst);
  uint8_t *produce_bytes(Inst *inst);
  Module *mod;
  map<string, pair<Block *, int>> symbol_table;

public:
  vector<uint8_t> bytecode = {0};
  snailer_byte_generator(Module *m) : mod(m) {
    symbol_table["push"] = pair(nullptr, PUSH_INST);
    symbol_table["pull"] = pair(nullptr, POP_INST);
    symbol_table["stop"] = pair(nullptr, HALT_INST);
    symbol_table["dup"] = pair(nullptr, DUP_INST);
    symbol_table["add"] = pair(nullptr, ADD_INST);
    symbol_table["sub"] = pair(nullptr, 5);
    symbol_table["mul"] = pair(nullptr, 6);
    symbol_table["div"] = pair(nullptr, 7);
    symbol_table["jump"] = pair(nullptr, 8);
    symbol_table["equal"] = pair(nullptr, 9);
    symbol_table["not_equal"] = pair(nullptr, 10);
    symbol_table["get_local"] = pair(nullptr, 11);
    symbol_table["alloc"] = pair(nullptr, 12);
    symbol_table["free_local"] = pair(nullptr, 13);
  };
  void proc_module();
  void write(string name);
};

#endif
