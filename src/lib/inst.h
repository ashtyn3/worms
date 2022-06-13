#pragma once

#include "core.h"
#include "iostream"
using namespace std;

enum {
  PUSH_INST,
  POP_INST,
  HALT_INST,
  DUP_INST,
  ADD_INST,
  SUB_INST,
  MUL_INST,
  DIV_INST,
  JMP_INST,
  EQ_INST,
  N_EQ_INST,
  GET_LOCAL_INST,
  LOAD_LOCAL_INST,
};

#define PUSH(value)                                                            \
  { .opcode = IWORD(PUSH_INST), .params = value }

#define HALT                                                                   \
  { .opcode = IWORD(HALT_INST) }

#define POP                                                                    \
  { .opcode = IWORD(POP_INST) }

#define DUP(flags, params)                                                     \
  { .opcode = IWORD(DUP_INST), flags, params }

#define ADD(flag)                                                              \
  {                                                                            \
    .opcode = IWORD(ADD_INST), .flags = { IWORD(0), IWORD(0), flag }           \
  }

#define SUB(flag)                                                              \
  { .opcode = IWORD(SUB_INST), .flags = flag }
#define MUL(flag)                                                              \
  { .opcode = IWORD(MUL_INST), .flags = flag }

#define DIV(flag)                                                              \
  { .opcode = IWORD(DIV_INST), .flags = flag }

#define JMP(value, value2)                                                     \
  { .opcode = IWORD(JMP_INST), .flags = value, .params = value2 }

#define EQ                                                                     \
  { .opcode = IWORD(EQ_INST) }

#define N_EQ                                                                   \
  { .opcode = IWORD(N_EQ_INST) }

#define GET_LOCAL(value)                                                       \
  { .opcode = IWORD(GET_LOCAL_INST), .params = value }

#define LOAD_LOCAL(size)                                                       \
  { .opcode = IWORD(LOAD_LOCAL_INST), .params = size }

struct Inst {
  word opcode;
  word flags[3];
  word params[5];
  void debug(word ip) {
    cout << ip.value.INT << ": ";
    switch (opcode.value.INT) {
    case PUSH_INST:
      cout << "<" << opcode.value.INT << "> PUSH";
      break;
    case POP_INST:
      cout << "<" << opcode.value.INT << "> POP";
      break;
    case HALT_INST:
      cout << "<" << opcode.value.INT << "> HALT";
      break;
    case ADD_INST:
      cout << "<" << opcode.value.INT << "> ADD";
      break;
    case SUB_INST:
      cout << "<" << opcode.value.INT << "> SUB";
      break;
    case MUL_INST:
      cout << "<" << opcode.value.INT << "> SUB";
      break;
    case DIV_INST:
      cout << "<" << opcode.value.INT << "> DIV";
      break;
    case EQ_INST:
      cout << "<" << opcode.value.INT << "> EQ";
      break;
    case N_EQ_INST:
      cout << "<" << opcode.value.INT << "> NEQ";
      break;
    case DUP_INST:
      cout << "<" << opcode.value.INT << "> DUP";
      break;
    case JMP_INST:
      cout << "<" << opcode.value.INT << "> JMP";
      break;
    case GET_LOCAL_INST:
      cout << "<" << opcode.value.INT << "> GET_LOCAL";
      break;
    case LOAD_LOCAL_INST:
      cout << "<" << opcode.value.INT << "> LOAD_LOCAL";
      break;
    }
    cout << "\n  FLAGS: ";
    for (int i = 0; i < 3; i++) {
      cout << GET_VALUE(flags[i]) << " ";
    }
    cout << "\n  PARAMS: ";
    for (int i = 0; i < 5; i++) {
      cout << GET_VALUE(params[i]) << " ";
    }
    cout << endl;
  }
};
