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

#define ADD                                                                    \
  { .opcode = IWORD(ADD_INST) }

#define SUB                                                                    \
  { .opcode = IWORD(SUB_INST) }
#define MUL                                                                    \
  { .opcode = IWORD(MUL_INST) }

#define DIV                                                                    \
  { .opcode = IWORD(DIV_INST) }

#define JMP(value, value2)                                                     \
  { .opcode = IWORD(JMP_INST), .flags = value, .params = value2 }

#define EQ                                                                     \
  { .opcode = IWORD(EQ_INST) }

#define N_EQ                                                                   \
  { .opcode = IWORD(N_EQ_INST) }

#define GET_LOCAL(value)                                                       \
  { .opcode = IWORD(GET_LOCAL_INST), .params = value }

#define LOAD_LOCAL                                                             \
  { .opcode = IWORD(LOAD_LOCAL_INST) }

struct Inst {
  word opcode;
  word flags[3];
  word params[5];
  void debug(word ip) {
    cout << ip.INT << ": ";
    switch (opcode.INT) {
    case PUSH_INST:
      cout << "<" << opcode.INT << "> PUSH";
      break;
    case POP_INST:
      cout << "<" << opcode.INT << "> POP";
      break;
    case HALT_INST:
      cout << "<" << opcode.INT << "> HALT";
      break;
    case ADD_INST:
      cout << "<" << opcode.INT << "> ADD";
      break;
    case SUB_INST:
      cout << "<" << opcode.INT << "> SUB";
      break;
    case MUL_INST:
      cout << "<" << opcode.INT << "> SUB";
      break;
    case DIV_INST:
      cout << "<" << opcode.INT << "> DIV";
      break;
    case EQ_INST:
      cout << "<" << opcode.INT << "> EQ";
      break;
    case N_EQ_INST:
      cout << "<" << opcode.INT << "> NEQ";
      break;
    case DUP_INST:
      cout << "<" << opcode.INT << "> DUP";
      break;
    case JMP_INST:
      cout << "<" << opcode.INT << "> JMP";
      break;
    case GET_LOCAL_INST:
      cout << "<" << opcode.INT << "> GET_LOCAL";
      break;
    case LOAD_LOCAL_INST:
      cout << "<" << opcode.INT << "> LOAD_LOCAL";
      break;
    }
    cout << "\n  FLAGS: ";
    for (int i = 0; i < 3; i++) {
      cout << flags[i].INT << " ";
    }
    cout << "\n  PARAMS: ";
    for (int i = 0; i < 5; i++) {
      cout << params[i].INT << " ";
    }
    cout << endl;
  }
};
