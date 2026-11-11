//
// Created by Rushe on 11/6/2026.
//
#include "vm.h"
#include "../bytecode_comp/debug.h"

int main(int argc, char** argv) {

    Chunk chunk;
    disassembleChunk(&chunk, "test Chunk");
    freeVM();

}
