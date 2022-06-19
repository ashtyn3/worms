#ifndef SNAILER_BYTE_LOAD_H
#define SNAILER_BYTE_LOAD_H

/*

   Bytecode format:

   First byte in file: start function address.


   Instructions format: [0      0 0 1   0 0 0 0 0 0 0 0 0 0 0]
                         ^      ^^^^^   ^^^^^^^^^ ^^^^^^^^^ ^
                         opcode flags   param 1   param 2   padding

   The third flag being set to 1 or on indicates 2 parameters. If the third flag
   is set to off or 0, this means the instruction only takes one parameter.

   Instructions format (3rd flag off): [0      0 0 0   0 0 0 0 0 0 0 0 0 0 0]
                                        ^      ^^^^^   ^^^^^^^^^^^^^^^^^^^ ^
                                        opcode flags   param 1
*/

#endif
