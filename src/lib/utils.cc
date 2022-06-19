// Copyright (c) 2022 Ashtyn Morel-Blake
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "utils.h"
#include "core.h"

int64_t b8_t_i64(int8_t u[8]) {
    int64_t value =
        static_cast<int64_t>(u[0]) | static_cast<int64_t>(u[1]) << 8 |
        static_cast<int64_t>(u[2]) << 16 | static_cast<int64_t>(u[3]) << 24 |
        static_cast<int64_t>(u[4]) << 32 | static_cast<int64_t>(u[5]) << 40 |
        static_cast<int64_t>(u[6]) << 48 | static_cast<uint64_t>(u[7]) << 56;
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

int32_t b8_t_i32(int8_t u[4]) {
    int32_t value =
        static_cast<int32_t>(u[0]) | static_cast<int32_t>(u[1]) << 8 |
        static_cast<int32_t>(u[2]) << 16 | static_cast<int32_t>(u[3]) << 24;
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

int16_t b8_t_i16(int16_t u[2]) {
    int16_t value = static_cast<int16_t>(u[0]) | static_cast<int16_t>(u[1])
                                                     << 8;
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
