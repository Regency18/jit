//
// Created by Rushe on 11/6/2026.
//

#ifndef JITVM_VM_H
#define JITVM_VM_H
#define STACK_MAX 256

#include "../bytecode_comp/chunk.h"

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stackTop;
}VM;

typedef enum  {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM(VM vm);
void freeVM(VM vm);
InterpretResult interpret(Chunk* chunk, VM vm);
static InterpretResult run();
void push(Value val, VM vm);
Value pop(VM vm);
#endif //JITVM_VM_H