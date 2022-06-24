// Copyright (c) 2023 Ashtyn Morel-Blake
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

#include <iostream>

// #include "lib/inst.h"
// #include "lib/vm.h"
#include "snailer/byte_gen.h"
#include "snailer/byte_load.h"
#include "snailer/module.h"
#include "src/lib/core.h"
#include "src/lib/vm.h"
#include <vector>

using namespace std;

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

int main() {
    // vector<Inst> prog = {PUSH({IWORD(0)}),
    //                      PUSH({IWORD(1)}),
    //                      ADD,
    //                      DUP({}, {}),
    //                      PUSH({IWORD(10)}),
    //                      N_EQ,
    //                      JMP({IWORD(1)}, {IWORD(1)}),
    //                      HALT};
    // Inst add = {.opcode = IWORD(ADD_INST),
    //             .flags = {IWORD(0), IWORD(0), IWORD(4)}};
    // Worms *hi = new Worms;
    // hi->full_trace = true;
    // hi->load_program(prog);
    // hi->run();
    Module *mod = new Module;
    Fn_block *fn = mod->make_fn("start", snailer_int64_t);

    // fn->add_param_sig("a", snailer_float64_t);

    Fn_call_block *c = new Fn_call_block("push", true);

    Value *v = new Value();
    v->set_Integer32(2);
    c->add_param(v);

    fn->add_block(c);
    fn->add_block(c);

    Fn_call_block *a = new Fn_call_block("add", true);
    a->flags[0] = IWORD_8(1);
    fn->add_block(a);

    Fn_call_block *al = new Fn_call_block("alloc", true);
    Value *v2 = new Value();
    v2->set_Integer(2);
    al->add_param(v2);

    fn->add_block(al);

    Fn_call_block *dup = new Fn_call_block("dup", true);

    dup->flags[0] = IWORD_8(1);
    Value *v22 = new Value();
    v22->set_Integer(0);
    dup->add_param(v22);

    fn->add_block(dup);

    Fn_call_block *gl = new Fn_call_block("gl_offset", true);
    gl->p_size = IWORD_8(1);
    Value *v11 = new Value();
    v11->set_Integer(0);
    gl->add_param(v11);

    Value *v12 = new Value();
    v12->set_Integer(0);
    gl->add_param(v12);

    fn->add_block(gl);

    Fn_call_block *h = new Fn_call_block("exit", true);
    fn->add_block(h);

    auto gen = new snailer_byte_generator(mod);
    gen->proc_module();
    gen->write("worms.out");

    auto sn_load = new snailer_byte_loader(gen->bytecode);
    Worms *hi = new Worms;
    hi->full_trace = true;
    hi->load_program(sn_load->instructions);
    hi->run();
    // cout << (int)i->params[0].value.INT16 << endl;
}
