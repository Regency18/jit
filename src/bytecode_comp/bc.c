#include <stdlib.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk = {0};
    init_Chunk(&chunk);
    ChunkArray* chunk_ptr = &chunk.chunks;
    int constant = addValue(1.2, &chunk);
    array_append(uint8_t, chunk_ptr, OP_CONSTANT);
    array_append(uint8_t, chunk_ptr, constant);

    array_append(uint8_t, chunk_ptr, OP_ADD);

    constant = addValue(2.3, &chunk);
    array_append(uint8_t, chunk_ptr, OP_CONSTANT);
    array_append(uint8_t, chunk_ptr, constant);

    array_append(uint8_t, chunk_ptr, OP_DIVIDE);
    array_append(uint8_t, chunk_ptr, OP_NEGATE);
    array_append(uint8_t, chunk_ptr, OP_RETURN);
    disassembleChunk(&chunk, "test_chunk");

    return 0;
}