#pragma once

#include "stdint.h"
#include <string>

union W_value {
  int8_t INT8;
  int16_t INT16;
  int32_t INT32;
  int64_t INT;
  float FLOAT;
};

struct word {
  W_value value;
  int t_flag = -1;
};
#define STACK_SIZE 8000

#define MATH_OP(sign, value1, value2)                                          \
  {                                                                            \
    if (is_type(in.flags[2].value.INT8) == "i64") {                            \
      stack.push(IWORD(value1.value.INT sign value2.value.INT));               \
    } else if (is_type(in.flags[2].value.INT8) == "i32") {                     \
      stack.push(IWORD_32(value1.value.INT32 sign value2.value.INT32));        \
    } else if (is_type(in.flags[2].value.INT8) == "i16") {                     \
      stack.push(IWORD_16(                                                     \
          static_cast<int16_t>(value1.value.INT16 sign value2.value.INT16)));  \
    } else if (is_type(in.flags[2].value.INT8) == "i8") {                      \
      stack.push(IWORD_8(                                                      \
          static_cast<int8_t>(value1.value.INT8 sign value2.value.INT8)));     \
    } else if (is_type(in.flags[2].value.INT8) == "f64") {                     \
      stack.push(FWORD(value1.value.FLOAT sign value2.value.FLOAT));           \
    }                                                                          \
  }

#define COMP_OP(sign, value1, value2)                                          \
  {                                                                            \
    if (is_type(in.flags[2].value.INT8) == "i64") {                            \
      stack.push(IWORD_8(value1.value.INT sign value2.value.INT));             \
    } else if (is_type(in.flags[2].value.INT8) == "i32") {                     \
      stack.push(IWORD_8(value1.value.INT32 sign value2.value.INT32));         \
    } else if (is_type(in.flags[2].value.INT8) == "i16") {                     \
      stack.push(IWORD_8(value1.value.INT16 sign value2.value.INT16));         \
    } else if (is_type(in.flags[2].value.INT8) == "i8") {                      \
      stack.push(IWORD_8(                                                      \
          static_cast<int8_t>(value1.value.INT8 sign value2.value.INT8)));     \
    } else if (is_type(in.flags[2].value.INT8) == "f64") {                     \
      stack.push(IWORD_8(value1.value.FLOAT sign value2.value.FLOAT));         \
    }                                                                          \
  }
std::string is_type(int);
std::string GET_VALUE(word);

#define IWORD(v)                                                               \
  { .value = {.INT = v}, .t_flag = 0 }

#define IWORD_32(int)                                                          \
  { .value = {.INT32 = int}, .t_flag = 1 }

#define IWORD_16(int)                                                          \
  { .value = {.INT16 = int}, .t_flag = 2 }

#define IWORD_8(int)                                                           \
  { .value = {.INT8 = int}, .t_flag = 3 }

#define FWORD(int)                                                             \
  { .value = {.FLOAT = int}, .t_flag = 4 }
