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

#include "gen.h"
#include "../../snailer/module.h"

Parse_tok *code_gen::peek() {
    if (i + 1 >= (int)toks.size()) {
        return nullptr;
    }
    return toks[i + 1];
}
void code_gen::next() {
    if (i + 1 >= (int)toks.size()) {
        i = -2;
        return;
    }
    i++;
    ptok = toks[i];
}

// string to int
Fn_block *code_gen::gen_fn() {
    auto fn = ptok->function;
    if (!sym_table.contains(fn->name)) {
        auto fn_b = new Fn_block(fn->name);
        fn_b->return_t = (value_t)str_value_t(fn->ret_type);
        auto c = new code_gen(fn->body);
        auto body = c->while_gen();
        fn_b->body = body;

        if (fn->params.size() > 0) {
            spdlog::warn("Function parameters are unsupported currently.");
            cout << "  - Ignoring " << fn->params.size() << " params" << endl;
        }

        next();
        return fn_b;
    } else {
        spdlog::critical("Cannot redeclare function: {}", fn->name);
        exit(1);
    }
    next();
    return nullptr;
}
Fn_call_block *code_gen::gen_fn_call() {
    auto fn_call = ptok->fn_call;
    Fn_call_block *fn_call_b =
        new Fn_call_block(fn_call->name, fn_call->is_builtin);
    if (fn_call->params.size() > 0) {
        auto c = new code_gen(fn_call->params);
        auto p = c->while_gen();
        for (int j = 0; j < (int)p.size(); j++) {
            if (p[j]->b_type != snailer_value_t) {
                spdlog::critical("Expected token of type Value at line {}",
                                 ptok->line);
            }
            fn_call_b->add_param((Value *)p[j]);
        }
    }

    if (peek() != NULL && peek()->type == flag_set_t) {
        next();
        int index = ptok->flags->index[1] - '0';
        fn_call_b->flags[index - 1] = IWORD_8(ptok->flags->value);
        if (peek()->type == flag_set_t) {
            while (1) {
                next();
                int index = ptok->flags->index[1] - '0';
                fn_call_b->flags[index] = IWORD_8(ptok->flags->value);
                if (peek()->type != flag_set_t) {
                    break;
                }
            }
        }
    }

    next();
    return fn_call_b;
}

Value *code_gen::gen_value() {
    auto val = ptok->param;
    auto value_b = new Value();
    if (str_value_t(val->type) == 0) {
        value_b->set_Integer((int64_t)stol(val->name));
    } else if (str_value_t(val->type) == 1) {
        value_b->set_Integer32((int32_t)stoi(val->name));
    } else if (str_value_t(val->type) == 2) {
        value_b->set_Integer16((int16_t)stoi(val->name));
    } else if (str_value_t(val->type) == 3) {
        value_b->set_Integer8((int8_t)stoi(val->name));
    } else if (str_value_t(val->type) == 4) {
        value_b->set_Integer8(stof(val->name));
    }
    next();
    return value_b;
}

Block *code_gen::gen() {
    if (ptok->type == function_t) {
        return gen_fn();
    } else if (ptok->type == function_c_t) {
        return gen_fn_call();
    } else if (ptok->type == param_t) {
        return gen_value();
    } else {
        spdlog::critical("Unknown parse type ({}) at line {}", ptok->type,
                         ptok->line);
        exit(1);
    }
}
vector<Block *> code_gen::while_gen() {
    while (i != -2) {
        mod->blocks.push_back(gen());
    }

    return mod->blocks;
}
