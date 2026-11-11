//
// Created by Rushe on 11/9/2026.
//
#include "astWalk.h"

#include <stdlib.h>

#include "chunk.h"
#include "../typedefs/ast.h"

Chunk walk(const Node* node) {
    Chunk chunk = {0};
    ChunkArray* chunk_ptr = &chunk.chunks;
    while (true) {
        switch (node->type) {
            case VARIABLE_NODE:
                int constant = addValue(strtod(node->data.variableNode->Variable, NULL), &chunk);
                array_append(uint8_t, chunk_ptr, OP_CONSTANT);
                array_append(uint8_t, chunk_ptr, constant);
                break;
            case BINARY_EXPR:
                switch (node->data.binaryExpr->token) {
                    case PLUS:
                        array_append(uint8_t, chunk_ptr, OP_ADD);
                        break;
                    case MINUS:
                        array_append(uint8_t, chunk_ptr, OP_SUB);
                        break;
                    case STAR:
                        array_append(uint8_t, chunk_ptr, OP_MULTIPLY);
                        break;
                    case SLASH:
                        array_append(uint8_t, chunk_ptr, OP_DIVIDE);
                        break;
                    default:
                        printf("error");
                }
                break;
            default:
                array_append(uint8_t, chunk_ptr, OP_RETURN);
                return chunk;
        }
    }
}