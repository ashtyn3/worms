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
#ifndef INST_H
#define INST_H
#include "core.h"
#include "iostream"
using namespace std;

enum {
    PUSH_INST = 1,
    POP_INST,
    HALT_INST,
    DUP_INST,
    ADD_INST,
    SUB_INST,
    MUL_INST,
    DIV_INST,
    JMP_INST,
    EQ_INST,
    N_EQ_INST,
    GET_LOCAL_INST,
    LOAD_LOCAL_INST,
    ALLOC_LOCAL_INST,
    INDEX_LOAD_LOCAL_INST,
    FREE_LOCAL_INST,
    CALL_INST,
};

#define PUSH(value)                                                            \
    { .opcode = IWORD(PUSH_INST), .params = value }

#define HALT                                                                   \
    { .opcode = IWORD(HALT_INST) }

#define POP                                                                    \
    { .opcode = IWORD(POP_INST) }

#define DUP(flags, params)                                                     \
    { .opcode = IWORD(DUP_INST), flags, params }

#define ADD(flag)                                                              \
    {                                                                          \
        .opcode = IWORD(ADD_INST), .flags = { IWORD(0), IWORD(0), flag }       \
    }

#define SUB(flag)                                                              \
    { .opcode = IWORD(SUB_INST), .flags = flag }
#define MUL(flag)                                                              \
    { .opcode = IWORD(MUL_INST), .flags = flag }

#define DIV(flag)                                                              \
    { .opcode = IWORD(DIV_INST), .flags = flag }

#define JMP(value, value2)                                                     \
    { .opcode = IWORD(JMP_INST), .flags = value, .params = value2 }

#define EQ                                                                     \
    { .opcode = IWORD(EQ_INST) }

#define N_EQ                                                                   \
    { .opcode = IWORD(N_EQ_INST) }

#define GET_LOCAL(value)                                                       \
    { .opcode = IWORD(GET_LOCAL_INST), .params = value }

#define FREE_LOCAL(value)                                                      \
    { .opcode = IWORD(FREE_LOCAL_INST), .params = value }

#define LOAD_LOCAL(size)                                                       \
    { .opcode = IWORD(LOAD_LOCAL_INST), .params = size }

struct Inst {
    word opcode;
    word flags[3];
    word params[2];
    void debug(word ip) {
        cout << ip.value.INT << ": ";
        switch (opcode.value.INT) {
        case PUSH_INST:
            cout << "<" << opcode.value.INT << "> PUSH";
            break;
        case POP_INST:
            cout << "<" << opcode.value.INT << "> POP";
            break;
        case HALT_INST:
            cout << "<" << opcode.value.INT << "> HALT";
            break;
        case ADD_INST:
            cout << "<" << opcode.value.INT << "> ADD";
            break;
        case SUB_INST:
            cout << "<" << opcode.value.INT << "> SUB";
            break;
        case MUL_INST:
            cout << "<" << opcode.value.INT << "> SUB";
            break;
        case DIV_INST:
            cout << "<" << opcode.value.INT << "> DIV";
            break;
        case EQ_INST:
            cout << "<" << opcode.value.INT << "> EQ";
            break;
        case N_EQ_INST:
            cout << "<" << opcode.value.INT << "> NEQ";
            break;
        case DUP_INST:
            cout << "<" << opcode.value.INT << "> DUP";
            break;
        case JMP_INST:
            cout << "<" << opcode.value.INT << "> JMP";
            break;
        case GET_LOCAL_INST:
            cout << "<" << opcode.value.INT << "> GET_LOCAL";
            break;
        case LOAD_LOCAL_INST:
            cout << "<" << opcode.value.INT << "> LOAD_LOCAL";
            break;
        case ALLOC_LOCAL_INST:
            cout << "<" << opcode.value.INT << "> ALLOC_LOCAL";
            break;
        case FREE_LOCAL_INST:
            cout << "<" << opcode.value.INT << "> FREE_LOCAL";
            break;
        case INDEX_LOAD_LOCAL_INST:
            cout << "<" << opcode.value.INT << "> INDEX_LOAD_LOCAL_INST";
            break;
        }
        cout << "\n  FLAGS: ";
        for (int i = 0; i < 3; i++) {
            cout << GET_VALUE(flags[i]) << " ";
        }
        cout << "\n  PARAMS: ";
        for (int i = 0; i < 2; i++) {
            cout << GET_VALUE(params[i]) << " ";
        }
        cout << endl;
    }
};
#endif
