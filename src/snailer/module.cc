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

#include "module.h"
#include "snailer_nanoid.h"
#include <iostream>
#include <random>

int Fn_block::make_local(string name, value_t type) { return 0; }

string t_string(value_t t) {
    switch (t) {
    case snailer_null_t:
        return "nullptr";
    case snailer_pointer_t:
        return "ref";
    case snailer_int64_t:
        return "i64";
    case snailer_int32_t:
        return "i32";
    case snailer_int16_t:
        return "i16";
    case snailer_int8_t:
        return "i8";
    case snailer_float64_t:
        return "f64";
    }
}
string debug_value_type(value_t t) {
    switch (t) {
    case snailer_int64_t:
        return "Int64";
        break;
    case snailer_int32_t:
        return "Int32";
        break;
    case snailer_int16_t:
        return "Int16";
        break;
    case snailer_int8_t:
        return "Int8";
        break;
    case snailer_float64_t:
        return "Float64";
        break;
    case snailer_pointer_t:
        return "Ptr";
        break;
    case snailer_null_t:
        return "Null";
        break;
    }
}

string Fn_block::produce() {
    string str;
    str.append("fn ");
    str.append(name);
    if (params.empty() == false) {
        str.append("(");
        for (int i = 0; i < (int)params.size(); i++) {
            if (i > 0) {
                str.append(params[i]->produce() + ", ");
                continue;
            }
            str.append(params[i]->produce());
        }
        str.append(")");
    }

    if (return_t != snailer_null_t) {
        str.append(" -> ");
        str.append(t_string(return_t));
        str.append(" \n");
    }
    if (body.empty() == false) {
        for (int i = 0; i < (int)body.size(); i++) {
            str.append("\t" + body[i]->produce() + "\n");
        }
    }
    str.append("end ");
    str.append(name + ";\n");
    return str;
}

Float Value::set_float(float f) {
    type = snailer_float64_t;
    s_float = {.value = f, .size = 64};
    return s_float;
}

Int Value::set_Integer(int64_t i) {
    type = snailer_int64_t;
    integer = {.value = i, .size = 64};
    return integer;
}

Int Value::set_Integer32(int32_t i) {
    type = snailer_int32_t;
    integer = {.value_32 = i, .size = 32};
    return integer;
}

Int Value::set_Integer16(int16_t i) {
    type = snailer_int16_t;
    integer = {.value_16 = i, .size = 16};
    return integer;
}

Int Value::set_Integer8(int8_t i) {
    type = snailer_int8_t;
    integer = {.value_8 = i, .size = 8};
    return integer;
}

string Value::produce() {
    string str;
    str.append(" ");
    switch (type) {
    case snailer_int64_t:
        str.append(to_string(integer.value));
        str.append(" i" + to_string(integer.size));
        break;
    case snailer_int32_t:
        str.append(to_string(integer.value_32));
        str.append(" i" + to_string(integer.size));
        break;
    case snailer_int16_t:
        str.append(to_string(integer.value_16));
        str.append(" i" + to_string(integer.size));
        break;
    case snailer_int8_t:
        str.append(to_string(integer.value_8));
        str.append(" i" + to_string(integer.size));
        break;
    case snailer_float64_t:
        str.append(to_string(s_float.value));
        str.append(" f" + to_string(s_float.size));
        break;
    case snailer_pointer_t:
        str.append(to_string(ptr.value));
        str.append(" ref");
        break;
    case snailer_null_t:
        str.append("nil");
        str.append(" ref");
    }
    return str;
}

Inst Value::raw_instruction() {
    Inst inst;
    switch (type) {
    case snailer_int64_t:
        inst.opcode = IWORD(integer.value);
        break;
    case snailer_int32_t:
        inst.opcode = IWORD_32(integer.value_32);
        break;
    case snailer_int16_t:
        inst.opcode = IWORD_16(integer.value_16);
        break;
    case snailer_int8_t:
        inst.opcode = IWORD_8(integer.value_8);
        break;
    case snailer_float64_t:
        inst.opcode = FWORD(s_float.value);
        break;
    case snailer_pointer_t:
        inst.opcode = IWORD(integer.value);
        break;
    case snailer_null_t:
        inst.opcode = IWORD(-5);
        break;
    }
    return inst;
}

void Fn_call_block::add_param(Value *p) { params.push_back(p); }

void Fn_block::add_param_sig(string n, value_t vt) {
    heap_model[n] = vt;
    params.push_back(new Snailer_param(n, vt));
}

string Fn_call_block::produce() {
    string str;
    str.append("call ");
    if (is_builtin) {
        str.append("&");
    }
    str.append(name);
    if (params.empty() == false) {
        for (int i = 0; i < (int)params.size(); i++) {
            str.append(params[i]->produce());
        }
    }
    str.append(";");
    return str;
}

Inst Fn_call_block::raw_instruction() {
    Inst inst;
    inst.opcode = IWORD_8(CALL_INST);

    inst.flags[0] = flags[0];
    inst.flags[1] = flags[1];
    inst.flags[2] = p_size;

    if (params.size() < 2 && p_size.value.INT8 == 1) {
        spdlog::critical("Bad argument length of 2 with param mode set to 1");
        exit(1);
    }
    if (params.empty()) {
        return inst;
    }
    for (int i = 0; i < p_size.value.INT + 1; i++) {
        inst.params[i] = params[i]->raw_instruction().opcode;
    }

    return inst;
}

Fn_block *Module::make_fn(string name, value_t ret_t) {
    Fn_block *fn = new Fn_block(name);
    fn->name = name;
    fn->return_t = ret_t;
    blocks.push_back(fn);
    return fn;
}

void Fn_block::add_block(Block *b) { body.push_back(b); }

string Snailer_param::produce() {
    string str;
    str.append(name + " ");
    str.append(t_string(val_t));
    return str;
}
