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
