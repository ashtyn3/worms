#pragma once

#include "stdint.h"

union word {
  int8_t INT8;
  int16_t INT16;
  int32_t INT32;
  int64_t INT;
  int8_t *FLOAT;
};
#define STACK_SIZE 8000

#define IWORD(int)                                                             \
  { .INT = int }
