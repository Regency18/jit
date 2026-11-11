//
// Created by Rushe on 11/6/2026.
//

#include "vm.h"

#include "../bytecode_comp/debug.h"

static void resetStack(VM vm) {
    vm.stackTop = vm.stack;
}

void initVM(const VM vm) {
    resetStack(vm);
}

void push(const Value val, VM vm) {
    *vm.stackTop = val;
    ++vm.stackTop;
}

Value pop(VM vm) {
    --vm.stackTop;
    return *vm.stackTop;
}
void freeVM(VM vm) {

}

#define READ_CONSTANT(vm) vm.chunk->values.items[READ_BYTE(vm)]
#define BINARY_OP(op, vm)\
    do {\
        double b = pop(vm);\
        double a = pop(vm);\
        push(a op b, vm);\
    } while (0)

static InterpretResult run(VM vm) {
#define READ_BYTE(vm) (*vm.ip++)
    while (true) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value* i = vm.stack; i < vm.stackTop; ++i) {
            printf("[ ");
            printValue(*i);
            printf("] ");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->chunks.items));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE(vm)) {
            case OP_RETURN:
                printValue(pop(vm));
                printf("\n");
                return INTERPRET_OK;
            case OP_ADD: BINARY_OP(+, vm); break;
            case OP_SUB: BINARY_OP(-, vm); break;
            case OP_MULTIPLY: BINARY_OP(*, vm); break;
            case OP_DIVIDE: BINARY_OP(/, vm); break;
            case OP_NEGATE: push(-pop(vm), vm); break;
            case OP_CONSTANT:
                const Value constant = READ_CONSTANT(vm);
                printValue(constant);
                printf("\n");
                break;
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(Chunk* chunk, VM vm) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->chunks.items;
    return run(vm);
}