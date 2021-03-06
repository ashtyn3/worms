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

#include "./byte_gen.h"
#include "./snailer_leb128.h"
#include "fstream"
#include <ieee754.h>

uint8_t *snailer_byte_generator::produce_bytes(Inst *inst) {
    static uint8_t bytes[15] = {0};
    fill_n(bytes, 15, 0);
    bytes[0] = inst->opcode.value.INT8;

    bytes[1] = inst->flags[0].value.INT8;
    bytes[2] = inst->flags[1].value.INT8;
    bytes[3] = inst->flags[2].value.INT8;

    if (inst->params[0].t_flag == -1) {
        return bytes;
    }
    for (int i = 0; i < bytes[3] + 1; i++) {
        int length = 10;
        if (inst->flags[2].value.INT8 == 1) {
            length = 5;
        }
        word w = inst->params[i];

        uint8_t buffer[10] = {};

        switch (w.t_flag) {
        case 4:
            IEEE_754 un;
            un.fp = w.value.FLOAT;
            buffer[0] = un.bytes[0];
            buffer[1] = un.bytes[1];
            buffer[2] = un.bytes[2];
            buffer[3] = un.bytes[3];
            break;
        case -1:
            break;
        default:
            int size = bfs::EncodeLeb128(w.value.INT, buffer, length);
            if (size == 0 && w.value.INT > 0) {
                cout << "INTEGER OVERFLOW" << endl;
            }
            break;
        }
        // int offset = 0;
        for (int j = 0; j < length; j++) {
            if (w.t_flag != -1) {
                bytes[(4 + (i * length))] = w.t_flag;
            }
            int index = (4 + (i * length)) + j + 1;
            bytes[index] = (int)buffer[j];
            // offset++;
        }
    }
    // for (int i = 0; i < 15; i++) {
    //   cout << i << ":" << (int)bytes[i] << endl;
    // }

    return bytes;
}

Inst *snailer_byte_generator::reproduce_inst(vector<uint8_t> b) {
    auto in = new Inst;

    in->opcode = IWORD_8((int8_t)b[0]);

    in->flags[0] = IWORD_8((int8_t)b[1]);
    in->flags[1] = IWORD_8((int8_t)b[2]);
    in->flags[2] = IWORD_8((int8_t)b[3]);

    int length = 10;
    if (b[3] == 1) {
        length = 5;
    }

    for (int i = 0; i < b[3] + 1; i++) {
        int root_addr = (i * length) + 4;

        int t = b[root_addr];
        uint8_t bytes[10] = {};
        for (int j = 0; j < length; j++) {
            int index = (4 + (i * length)) + j;
            bytes[j] = b[index + 1];
        }
        in->params[i].t_flag = t;
        switch (t) {
        case 4: {
            IEEE_754 un;
            un.bytes[0] = bytes[0];
            un.bytes[1] = bytes[1];
            un.bytes[2] = bytes[2];
            un.bytes[3] = bytes[3];
            in->params[i].value.FLOAT = un.fp;
            break;
        }
        case 3: {
            int64_t val;
            bfs::DecodeLeb128(bytes, length, &val);
            in->params[i].value.INT16 = static_cast<int8_t>(val);
            break;
        }
        case 2: {
            int64_t val;
            bfs::DecodeLeb128(bytes, length, &val);
            in->params[i].value.INT16 = static_cast<int16_t>(val);
            break;
        }
        case 1: {
            int64_t val;
            bfs::DecodeLeb128(bytes, length, &val);
            in->params[i].value.INT32 = static_cast<int32_t>(val);
        }
        case 0:
            bfs::DecodeLeb128(bytes, length, &in->params[i].value.INT);
            break;
        case -1:
            break;
        }
    }

    return in;
}

void snailer_byte_generator::proc_module() {
    for (int i = 0; i < (int)mod->blocks.size(); i++) {

        Block *b = mod->blocks[i];

        if (b->b_type == snailer_fn_block_t) {
            Module *M = new Module();

            Fn_block *fn = (Fn_block *)b;

            symbol_table[fn->name] = pair(fn, place);
            // symbol_table.insert(pair(fn->name, pair(fn, place + 1)));

            if (fn->name == "start") {
                bytecode[0] = place;
            }
            M->blocks = fn->body;
            auto g = new snailer_byte_generator(M);
            g->symbol_table.insert(symbol_table.begin(), symbol_table.end());

            g->proc_module();
            place += g->place;
            bytecode.insert(bytecode.end(), g->bytecode.begin(),
                            g->bytecode.end());
        } else if (b->b_type == snailer_fn_call_block_t) {
            Fn_call_block *fn = (Fn_call_block *)b;

            if (!symbol_table.contains(fn->name)) {
                cout << "BAD NAME: " << fn->name << endl;
                exit(255);
            }

            Inst inst = b->raw_instruction();
            inst.opcode.value.INT8 = CALL_INST;
            if (fn->is_builtin == true) {
                inst.opcode = IWORD_8((int8_t)symbol_table[fn->name].second);
            } else {
                inst.params[0] = IWORD(symbol_table[fn->name].second);
            }
            uint8_t *bytes = produce_bytes(&inst);

            for (int i = 0; i < 15; i++) {
                bytecode.push_back(bytes[i]);
            }
            place += 1;
        }
    }
}

void snailer_byte_generator::write(string name) {
    if (!symbol_table.contains("start")) {
        cout << "COMPILED LIBRARY" << endl;
    }
    ofstream fout(name, ios::out | ios::binary);
    fout.write((char *)&bytecode[0], bytecode.size() * sizeof(uint8_t));
    fout.close();
}
