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

#ifndef GEN_H
#define GEN_H
#include "../../snailer/module.h"
#include "parse.h"

class code_gen {
    map<string, Fn_block *> sym_table;

    int i = 0;
    vector<Parse_tok *> toks;
    Parse_tok *ptok = toks[i];

    Fn_block *gen_fn();
    Fn_call_block *gen_fn_call();
    Param *gen_param();
    Value *gen_value();

    void next();
    Parse_tok *peek();

  public:
    Module *mod = new Module();
    Block *gen();
    vector<Block *> while_gen();
    code_gen(vector<Parse_tok *> p) : toks(p){};
};

#endif
