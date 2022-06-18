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

    cout << inst->params[i].t_flag << endl;
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
      if (w.t_flag != -1) {
        bytes[(4 + (i * length))] = w.t_flag;
      }
      int index = (4 + (i * length)) + j + 1;
      bytes[index] = (int)buffer[j];
      // offset++;
    }
  }
  for (int i = 0; i < 15; i++) {
    cout << i << ":" << (int)bytes[i] << endl;
  }

  return bytes;
}

Inst *reproduce_inst(uint8_t *b) {
  auto in = new Inst;

  in->opcode = IWORD_8((int8_t)b[0]);

  in->flags[0] = IWORD_8((int8_t)b[1]);
  in->flags[1] = IWORD_8((int8_t)b[2]);
  in->flags[2] = IWORD_8((int8_t)b[3]);

  int length = 10;
  if (b[3] == 1) {
    length = 5;
  }

  cout << "==========" << endl;
  for (int i = 0; i < b[3] + 1; i++) {
    int root_addr = (i * length) + 4;

    int t = b[root_addr];
    uint8_t bytes[10] = {};
    for (int j = 0; j < length; j++) {
      int index = (4 + (i * length)) + j;
      bytes[j] = b[index + 1];
    }
    switch (t) {
    case 4: {
      IEEE_754 un;
      un.bytes[0] = bytes[0];
      un.bytes[1] = bytes[1];
      un.bytes[2] = bytes[2];
      un.bytes[3] = bytes[3];
      in->params[i].value.FLOAT = un.fp;
      break;
    }
    case 3: {
      int64_t val;
      bfs::DecodeLeb128(bytes, length, &val);
      in->params[i].value.INT8 = static_cast<int8_t>(val);
      break;
    }
    case 2: {
      int64_t val;
      bfs::DecodeLeb128(bytes, length, &val);
      in->params[i].value.INT16 = static_cast<int16_t>(val);
      break;
    }
    case 1: {
      int64_t val;
      bfs::DecodeLeb128(bytes, length, &val);
      in->params[i].value.INT32 = static_cast<int32_t>(val);
    }
    case 0:
      bfs::DecodeLeb128(bytes, length, &in->params[i].value.INT);
      break;
    case -1:
      break;
    }
  }

  return in;
}