#include "debug.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->chunks.size;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, const int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    const uint8_t constant = chunk->chunks.items[offset + 1];
    printf("%-16s %4d ", name, constant);
    printValue(chunk->values.items[constant]);
    printf("\n");
    return offset + 2;
}

void printValue(const Value val) {
    printf("%g", val);
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);
    const uint8_t instruction = chunk->chunks.items[offset];
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OP_SUB:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}