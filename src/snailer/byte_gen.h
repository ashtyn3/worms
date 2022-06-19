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

#ifndef BYTE_GEN_H
#define BYTE_GEN_H
#include "../lib/inst.h"
#include "module.h"
#include <cstdint>
union IEEE_754 {
    uint8_t bytes[4];
    float fp;
};

class snailer_byte_generator {
    uint8_t *produce_bytes(Inst *inst);
    Module *mod;
    map<string, pair<Block *, int>> symbol_table;

  public:
    vector<uint8_t> bytecode = {0};
    Inst *reproduce_inst(vector<uint8_t> inst);
    snailer_byte_generator(Module *m) : mod(m) {
        symbol_table["push"] = pair(nullptr, PUSH_INST);
        symbol_table["pop"] = pair(nullptr, POP_INST);
        symbol_table["exit"] = pair(nullptr, HALT_INST);
        symbol_table["dup"] = pair(nullptr, DUP_INST);
        symbol_table["add"] = pair(nullptr, ADD_INST);
        symbol_table["sub"] = pair(nullptr, SUB_INST);
        symbol_table["mul"] = pair(nullptr, MUL_INST);
        symbol_table["div"] = pair(nullptr, DIV_INST);
        symbol_table["jump"] = pair(nullptr, JMP_INST);
        symbol_table["equal"] = pair(nullptr, EQ_INST);
        symbol_table["not_equal"] = pair(nullptr, N_EQ_INST);
        symbol_table["get_local"] = pair(nullptr, GET_LOCAL_INST);
        symbol_table["alloc"] = pair(nullptr, LOAD_LOCAL_INST);
        symbol_table["free_local"] = pair(nullptr, FREE_LOCAL_INST);
    };
    void proc_module();
    void write(string name);
};

#endif
