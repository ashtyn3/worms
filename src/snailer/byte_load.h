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

#ifndef SNAILER_BYTE_LOAD_H
#define SNAILER_BYTE_LOAD_H

/*

   Bytecode format:

   First byte in file: start function address.


   Instructions format: [0      0 0 1   0 0 0 0 0 0 0 0 0 0 0]
                         ^      ^^^^^   ^^^^^^^^^ ^^^^^^^^^ ^
                         opcode flags   param 1   param 2   padding

   The third flag being set to 1 or on indicates 2 parameters. If the third flag
   is set to off or 0, this means the instruction only takes one parameter.

   Instructions format (3rd flag off): [0      0 0 0   0 0 0 0 0 0 0 0 0 0 0]
                                        ^      ^^^^^   ^^^^^^^^^^^^^^^^^^^ ^
                                        opcode flags   param 1
*/
#include "module.h"

struct snailer_bytecode_file {
    vector<vector<uint8_t>> byte_arr = {};
    uint8_t start_addr = -1;
};
class snailer_byte_loader {
    void load_segments();
    vector<uint8_t> bytecode = {};
    snailer_bytecode_file file;
    Module *mod = new Module;

  public:
    vector<Inst> instructions = {};
    snailer_byte_loader(vector<uint8_t> file) : bytecode(file) {
        load_segments();
    };
};

#endif
