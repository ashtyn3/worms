#include "./byte_gen.h"
#include "./snailer_leb128.h"
#include <ieee754.h>

uint8_t *produce_bytes(Inst *inst) {
  static uint8_t bytes[64] = {};
  malloc(sizeof(bytes));
  bytes[0] = inst->opcode.value.INT8;

  bytes[1] = inst->flags[0].value.INT8;
  bytes[2] = inst->flags[1].value.INT8;
  bytes[3] = inst->flags[2].value.INT8;

  for (int i = 0; i < 5; i++) {
    word w = inst->params[i];
    uint8_t buffer[6] = {};
    switch (w.t_flag) {
    case 4:
      IEEE_754 un;
      un.fp = w.value.FLOAT;
      buffer[0] = un.bytes[0];
      buffer[1] = un.bytes[1];
      buffer[2] = un.bytes[2];
      buffer[3] = un.bytes[3];
      break;
    case -1:
      break;
    default:
      bfs::EncodeLeb128(w.value.INT, buffer, 6);
      break;
    }
    // for (int j = 0; j < 6; j++) {
    //   bytes[j + 4 + (i * 6)] = (int)buffer[j];
    //   cout << j + 4 + (i * 6) << ": " << (int)buffer[j] << endl;
    // }
    // cout << "==========" << endl;
  }

  return bytes;
}
