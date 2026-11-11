//
// Created by Rushe on 11/3/2026.
//
#include "chunk.h"

#include <stdlib.h>

int addValue(Value val, Chunk* chunk) {
    ValueArray* values = &chunk->values;
    array_append(Value, values, val);
    return (int)chunk->values.size - 1;
}

void init_Chunk(Chunk* chunk) {
    ChunkArray chunk_array = {0};
    ValueArray value_array = {0};
    chunk->chunks = chunk_array;
    chunk->values = value_array;
}
