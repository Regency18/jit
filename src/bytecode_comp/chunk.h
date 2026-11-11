//
// Created by Rushe on 11/2/2026.
//

#ifndef JITVM_VALUE_H
#define JITVM_VALUE_H
#include "common.h"
typedef double Value;
new_array(Value, Value);
typedef struct {
    ValueArray values;
    ChunkArray chunks;
}Chunk;


void init_Chunk(Chunk* chunk);

int addValue(Value value, Chunk* chunk);

#endif //JITVM_VALUE_H