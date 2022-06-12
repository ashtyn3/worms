#pragma once

#include "stdint.h"

union word {
  int8_t INT8;
  int16_t INT16;
  int32_t INT32;
  int64_t INT;
  float FLOAT;
};
#define STACK_SIZE 8000

#define IWORD(int)                                                             \
  { .INT = int }

#define IWORD_8(int)                                                           \
  { .INT8 = int }

#define IWORD_16(int)                                                          \
  { .INT16 = int }

#define IWORD_32(int)                                                          \
  { .INT32 = int }

#define FWORD(fl)                                                              \
  { .FLOAT = fl }
