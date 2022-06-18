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

public:
  vector<uint8_t> bytecode;
  snailer_byte_generator(Module *m) : mod(m){};
  void proc_module();
  void write(string name);
};

#endif
