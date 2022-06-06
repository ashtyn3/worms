#pragma once

#include "stdint.h"

union word {
  uint8_t *FLOAT;
  uint64_t INT;
};

#define STACK_SIZE 8000
#define IWORD(int)                                                             \
  { .INT = int }
