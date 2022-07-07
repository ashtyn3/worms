// Copyright (c) 2022 Ashtyn Morel-Blake
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

#include "byte_load.h"
#include "byte_gen.h"

vector<vector<uint8_t>> group_by_k(const vector<uint8_t> &arr, const size_t k) {

    vector<vector<uint8_t>> result;
    assert(k > 0);
    result.reserve(arr.size() / k);

    for (size_t i = 0; i < arr.size(); i += k) {
        size_t begin = i;
        size_t end = min(arr.size(), i + k);
        result.emplace_back(arr.begin() + begin, arr.begin() + end);
    }

    return result;
}

void snailer_byte_loader::load_segments() {
    file.start_addr = bytecode[0];

    bytecode.erase(bytecode.begin());
    bytecode.erase(bytecode.begin());

    vector<uint8_t> chunk;
    vector<vector<uint8_t>> chunks;

    chunks = group_by_k(bytecode, 15);
    for (int i = 0; i < (int)chunks.size(); i++) {
        if (chunks[i][0] == 0) {
            chunks[i].erase(chunks[i].begin());
        }
    }
    // for (int i = 0; i < (int)bytecode.size() + 1; i++) {
    //     chunk.push_back(bytecode[i]);
    //     if (offset == 14 + (bytecode.size() % 15)) {
    //         chunks.push_back(chunk);
    //         chunk.clear();
    //         offset = 0;
    //     }
    //     offset++;
    // }

    // for (int i = 0; i < (int)chunks.size(); i++) {
    //     for (int j = 0; j < 15; j++) {
    //         cout << (int)chunks[i][j] << endl;
    //     }
    //     cout << "========" << endl;
    // }

    file.byte_arr = chunks;
    auto gen = new snailer_byte_generator(mod);
    for (int i = 0; i < (int)chunks.size(); i++) {
        if (chunks[i].size() < 14) {
            continue;
        }

        auto l = gen->reproduce_inst(chunks[i]);
        instructions.push_back(*l);
    }
}
