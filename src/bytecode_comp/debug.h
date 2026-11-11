//
// Created by Rushe on 11/2/2026.
//

#ifndef JITVM_DEBUG_H
#define JITVM_DEBUG_H

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
void printValue(Value val);
int disassembleInstruction(Chunk* chunk, int offset);

#endif //JITVM_DEBUG_H