#include "./byte_gen.h"
#include "./snailer_leb128.h"
#include <ieee754.h>

uint8_t *produce_bytes(Inst *inst) {
  static uint8_t bytes[15] = {};
  bytes[0] = inst->opcode.value.INT8;

  bytes[1] = inst->flags[0].value.INT8;
  bytes[2] = inst->flags[1].value.INT8;
  bytes[3] = inst->flags[2].value.INT8;

  for (int i = 0; i < bytes[3] + 1; i++) {
    int length = 10;
    if (inst->flags[2].value.INT8 == 1) {
      length = 5;
    }
    word w = inst->params[i];

    uint8_t buffer[10] = {};

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
      int size = bfs::EncodeLeb128(w.value.INT, buffer, length);
      if (size == 0 && w.value.INT > 0) {
        cout << "INTEGER OVERFLOW" << endl;
      }
      break;
    }
    // int offset = 0;
    for (int j = 0; j < length; j++) {
      int index = (4 + (i * length)) + j;
      bytes[index] = (int)buffer[j];
      // offset++;
    }
  }
  for (int i = 0; i < 15; i++) {
    cout << i << ":" << (int)bytes[i] << endl;
  }

  return bytes;
}
