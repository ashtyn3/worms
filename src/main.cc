#include <iostream>

#include "lib/core.h"
#include "lib/inst.h"
#include "lib/vm.h"
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
  vector<Inst> prog = {PUSH({IWORD(2)}), LOAD_LOCAL, HALT};
  Worms *hi = new Worms;
  hi->full_trace = true;
  hi->load_program(prog);
  hi->run();
}
