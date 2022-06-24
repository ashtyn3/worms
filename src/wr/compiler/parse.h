/*
 * Copyright (c) 2022 Ashtyn Morel-Blake
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "lex.h"
#include <map>
#include <memory>

class Parse_tok;
class Function {
  public:
    vector<Parse_tok *> body;
    string name;
    string ret_type;
    vector<Parse_tok *> params;
};

class Function_call {
  public:
    string name;
    string ret_type;
    bool is_builtin;
    vector<Parse_tok *> params;
};

class Flags {
  public:
    string index;
    int8_t value;
};

class Return {
  public:
    bool is;
};
class Param {
  public:
    string name;
    string type;
};
class End {
  public:
    bool is;
};

enum Parse_type {
    param_t,
    function_t,
    function_c_t,
    function_r_t,
    end_t,
    flag_set_t
};
class Parse_tok {
  public:
    int line = 0;
    Parse_type type;
    Param *param;
    Function *function;
    Function_call *fn_call;
    Return *fn_return;
    Flags *flags;
    End *end;
};
