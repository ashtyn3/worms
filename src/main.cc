#include <iostream>

// #include "lib/inst.h"
// #include "lib/vm.h"
#include "snailer/byte_gen.h"
#include "snailer/module.h"
#include "src/lib/core.h"
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
  Fn_block *fn = mod->make_fn("main", snailer_int64_t);

  // fn->add_param_sig("a", snailer_float64_t);

  Fn_call_block *c = new Fn_call_block("hi", true);
  c->p_size = IWORD(1);

  Value *v = new Value();
  // v->set_Integer(9007199254740991);
  v->set_float(9.9);

  c->add_param(v);

  Value *v2 = new Value();
  v2->set_Integer(20);

  c->add_param(v2);

  fn->add_block(c);

  auto in = c->raw_instruction();
  uint8_t *bit_code = produce_bytes(&in);
  Inst *i = reproduce_inst(bit_code);

  cout << i->params[0].value.FLOAT << endl;
}
