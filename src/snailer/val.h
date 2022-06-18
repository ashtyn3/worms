#pragma once
#include <cstdint>
#ifndef SNAILER_VALUE_H
#define SNAILER_VALUE_H
class Ptr {
public:
  int value;
};

class Int {
public:
  int64_t value;
  int32_t value_32;
  int16_t value_16;
  int8_t value_8;
  int size;
};

class Float {
public:
  float value;
  int size;
};

#endif
