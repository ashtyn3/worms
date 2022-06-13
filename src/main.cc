#include <iostream>

#include "lib/inst.h"
#include "lib/vm.h"
#include "snailer/module.cc"
#include "snailer/module.h"
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
  vector<Inst> prog = {PUSH({FWORD(0.1)}), PUSH({FWORD(0.1)}),
                       LOAD_LOCAL({IWORD(2)}), HALT};
  Worms *hi = new Worms;
  hi->full_trace = true;
  hi->load_program(prog);
  hi->run();
  // Module *mod = new Module;
  // Fn_block *fn = mod->make_fn("main", snailer_int64_t);
  //
  // fn->add_param_sig("a", snailer_float64_t);
  //
  // Fn_call_block *c = new Fn_call_block("hi", true);
  //
  // Value *v = new Value();
  // v->set_Integer(2);
  //
  // c->add_param(v);
  //
  // fn->add_block(c);
  //
  // cout << fn->produce() << endl;
}
