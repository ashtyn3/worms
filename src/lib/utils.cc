#include "utils.h"
#include "core.h"

int64_t b8_t_i64(word u[8]) {
  int64_t value = static_cast<int64_t>(u[0].INT) |
                  static_cast<int64_t>(u[1].INT) << 8 |
                  static_cast<int64_t>(u[2].INT) << 16 |
                  static_cast<int64_t>(u[3].INT) << 24 |
                  static_cast<int64_t>(u[4].INT) << 32 |
                  static_cast<int64_t>(u[5].INT) << 40 |
                  static_cast<int64_t>(u[6].INT) << 48 |
                  static_cast<uint64_t>(u[7].INT) << 56;
  return value;
}

int8_t *i64_t_b8(int64_t num) {
  int8_t *p = (int8_t *)&num;
  int8_t result[8];
  for (int i = 0; i < 8; i++) {
    result[i] = p[i];
  }
  return p;
}

int32_t b8_t_i32(word u[4]) {
  int32_t value = static_cast<int32_t>(u[0].INT) |
                  static_cast<int32_t>(u[1].INT) << 8 |
                  static_cast<int32_t>(u[2].INT) << 16 |
                  static_cast<int32_t>(u[3].INT) << 24;
  return value;
}

int8_t *i32_t_b8(int32_t num) {
  int8_t *p = (int8_t *)&num;
  int8_t result[4];
  for (int i = 0; i < 4; i++) {
    result[i] = p[i];
  }
  return p;
}

int16_t b8_t_i16(word u[2]) {
  int16_t value =
      static_cast<int16_t>(u[0].INT) | static_cast<int16_t>(u[1].INT) << 8;
  return value;
}

int8_t *i16_t_b8(int16_t num) {
  int8_t *p = (int8_t *)&num;
  int8_t result[4];
  for (int i = 0; i < 2; i++) {
    result[i] = p[i];
  }
  return p;
}
