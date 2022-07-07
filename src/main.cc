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
#include "./include/argparse.hpp"
#include "./lib/vm.h"
#include "./snailer/byte_load.h"
#include "./version.h"
#include "spdlog/spdlog.h"

#include <fstream>
#include <vector>

using std::ifstream;

using namespace std;

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("Worms", WORMS_VERSION);

    program.add_argument("filename").help("The bytecode filename.").required();
    program.add_argument("--trace", "-T")
        .help("Print debug stack traces")
        .default_value(false)
        .implicit_value(true);

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }
    //
    ifstream is(program.get<string>("filename"),
                std::ios::in | std::ios::binary);
    std::vector<uint8_t> file_bytes((std::istreambuf_iterator<char>(is)),
                                    std::istreambuf_iterator<char>());
    //
    snailer_byte_loader *h = new snailer_byte_loader(file_bytes);
    auto vm = new Worms;
    if (program["-T"] == true) {
        vm->full_trace = true;
    }
    // cout << (int)h->instructions[6].opcode.value.INT8 << endl;
    vm->ip = IWORD(file_bytes[0]);
    vm->load_program(h->instructions);
    vm->run();

    return 0;
}
