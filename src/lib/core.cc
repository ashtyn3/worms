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

#include "core.h"

#include <iostream>
using namespace std;

string is_type(int t_flag) {
    switch (t_flag) {
    case 0:
        return "i64";
    case 1:
        return "i32";
    case 2:
        return "i16";
    case 3:
        return "i8";
    case 4:
        return "f64";
    default:
        return "i64";
    }
}
int is_size(word w) {
    switch (w.t_flag) {
    case 0:
        return 64;
    case 1:
        return 32;
    case 2:
        return 16;
    case 3:
        return 8;
    case 4:
        return 64;
    default:
        return 64;
    }
}

int str_value_t(string t_name) {
    if (t_name == "i64") {
        return 0;
    } else if (t_name == "i32") {
        return 1;
    } else if (t_name == "i16") {
        return 2;
    } else if (t_name == "i8") {
        return 3;
    } else if (t_name == "f64") {
        return 4;
    }
    return 0;
}
string GET_VALUE(word w) {
    int t_flag = w.t_flag;
    if (is_type(t_flag) == "i64") {
        return to_string(w.value.INT);
    } else if (is_type(t_flag) == "i32") {
        return to_string(w.value.INT32);
    } else if (is_type(t_flag) == "i16") {
        return to_string(w.value.INT16);
    } else if (is_type(t_flag) == "i8") {
        return to_string(w.value.INT8);
    } else if (is_type(t_flag) == "f64") {
        return to_string(w.value.FLOAT);
    }
    return "";
}
