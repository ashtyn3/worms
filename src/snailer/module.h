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

#ifndef MODULE_H
#define MODULE_H
#include "../lib/inst.h"
#include "spdlog/spdlog.h"
#include "val.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

enum value_t {
    snailer_int64_t,
    snailer_int32_t,
    snailer_int16_t,
    snailer_int8_t,
    snailer_float64_t,
    snailer_null_t,
    snailer_pointer_t,
};
string t_string(value_t t);
string debug_value_type(value_t t);
enum block_t {
    snailer_fn_block_t,
    snailer_fn_call_block_t,
    snailer_value_t,
    Snailer_param_t,
};

class Fn_block;
class Fn_call_block;
// class Value;
// class Param;

class Block {

    Fn_block *fn;
    Fn_call_block *call;

  public:
    word flags[3] = {};
    word p_size = IWORD_8(0);
    virtual ~Block() = default;
    // int get_pointer_to();
    virtual Inst raw_instruction() { return {}; };
    virtual string produce() { return {}; };

    block_t b_type;
    // virtual int make_local(string name, value_t type) = 0;
    // virtual void add_block(Block *b) = 0;
};

class Module {
  public:
    vector<Block *> blocks;
    Fn_block *make_fn(string, value_t);
};

class Value : public Block {

  public:
    value_t type;

    Ptr ptr;
    Int integer;
    Float s_float;

    Ptr set_ptr(int ref);

    Int set_Integer(int64_t i);
    Int set_Integer32(int32_t i);
    Int set_Integer16(int16_t i);
    Int set_Integer8(int8_t i);

    Float set_float(float f);

    string produce();
    Inst raw_instruction();
    friend std::ostream &operator<<(std::ostream &os, const Value &v) {
        os << "<Snailer <Value " << debug_value_type(v.type);
        switch (v.type) {
        case snailer_int64_t:
            os << v.integer.value;
            break;
        case snailer_int32_t:
            os << v.integer.value_32;
            break;
        case snailer_int16_t:
            os << v.integer.value_16;
            break;
        case snailer_int8_t:
            os << v.integer.value_8;
            break;
        case snailer_float64_t:
            os << v.s_float.value;
            break;
        case snailer_pointer_t:
            os << "0x" << std::hex << v.ptr.value;
            break;
        case snailer_null_t:
            os << "Nil";
            break;
        }
        os << "> >";
        return os;
    }
    Value() { b_type = snailer_value_t; };
};

class Snailer_param : public Block {
  public:
    string name;
    value_t val_t;
    Snailer_param(string name, value_t vt) : name(name), val_t(vt) {
        b_type = Snailer_param_t;
    };
    friend std::ostream &operator<<(std::ostream &os, const Snailer_param &v) {
        os << "<Snailer <Parameter ";
        os << debug_value_type(v.val_t) << " ";
        os << v.name << "> >";
        return os;
    }
    string produce();
};

class Fn_block : public Block {
  protected:
    map<string, value_t> heap_model;

  public:
    Fn_block(string name) : name(name) { b_type = snailer_fn_block_t; };
    string name;
    value_t return_t;
    vector<Snailer_param *> params;
    vector<Block *> body;
    int make_local(string name, value_t type);
    void add_block(Block *b);
    void add_param_sig(string n, value_t vt);
    string produce();
};

class Fn_call_block : public Block {
  public:
    string name;
    bool is_builtin;
    vector<Value *> params;
    Fn_call_block(string name, bool builtin) : name(name), is_builtin(builtin) {
        b_type = snailer_fn_call_block_t;
    };
    string produce();
    Inst raw_instruction();
    void add_param(Value *p);
};
#endif
