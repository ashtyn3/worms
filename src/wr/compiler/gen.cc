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
            cout << "Function parameters are unsupported currently." << endl;
            cout << "  - Ignoring " << fn->params.size() << " params" << endl;
        }

        next();
        return fn_b;
    } else {
        cout << "Cannot redeclare function: " << fn->name << endl;
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
                cout << "Expected token of type Value at line " << ptok->line
                     << endl;
            }
            fn_call_b->add_param((Value *)p[j]);
        }
    }

    if (peek() != NULL && peek()->type == flag_set_t) {
        next();
        int index = ptok->flags->index[1] - '0';
        fn_call_b->flags[index] = IWORD_8(ptok->flags->value);
        while (1) {
            next();
            int index = ptok->flags->index[1] - '0';
            fn_call_b->flags[index] = IWORD_8(ptok->flags->value);
            if (peek()->type != flag_set_t) {
                break;
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
        cout << "Unknown parse type (" << ptok->type << ") at line"
             << ptok->line << endl;
        exit(1);
    }
}
vector<Block *> code_gen::while_gen() {
    while (i != -2) {
        mod->blocks.push_back(gen());
    }

    return mod->blocks;
}
