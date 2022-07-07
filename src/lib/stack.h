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
#ifndef STACK_H
#define STACK_H
#include "core.h"
#include <iostream>
#include <map>

using namespace std;
struct Stack_frame {
    int top = -1;
    int frame = top;

    word stack[STACK_SIZE];

    word at_top();

    word pop();

    void push(word value);

    void stdout_dump();
    void op_stdout_dump();

    int op_top = -1;
    word op_stack[STACK_SIZE];

    int alloc_loc(int size);
    void push_loc(word addr, word value);
    void pop_loc(int64_t id);
};

struct Call_stack {
    int pointer = -1;
    Stack_frame stack[STACK_SIZE];

    void push_frame();
    void pop_frame();
    int top = -1;
};
#endif
