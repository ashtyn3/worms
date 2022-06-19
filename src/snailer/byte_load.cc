#include "byte_load.h"
#include "byte_gen.h"

void snailer_byte_loader::load_segments() {
    file.start_addr = bytecode[0];

    bytecode.erase(bytecode.begin());
    bytecode.erase(bytecode.begin());

    vector<uint8_t> chunk;
    vector<vector<uint8_t>> chunks;

    int offset = 0;
    for (int i = 0; i < (int)bytecode.size() + 1; i++) {
        if (offset == 15) {
            chunks.push_back(chunk);
            chunk.clear();
            offset = 0;
        }
        chunk.push_back(bytecode[i]);
        offset++;
    }

    // for (int i = 0; i < (int)chunks.size(); i++) {
    //     for (int j = 0; j < 15; j++) {
    //         cout << (int)chunks[i][j] << endl;
    //     }
    //     cout << "========" << endl;
    // }

    file.byte_arr = chunks;
    auto gen = new snailer_byte_generator(mod);
    for (int i = 0; i < (int)chunks.size(); i++) {
        auto l = gen->reproduce_inst(chunks[i]);
        instructions.push_back(*l);
    }
}
