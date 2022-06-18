#ifndef BYTE_GEN_H
#define BYTE_GEN_H
#include "../lib/inst.h"
#include <cstdint>
union IEEE_754 {
  uint8_t bytes[4];
  float fp;
};
uint8_t *produce_bytes(Inst *inst);
#endif
