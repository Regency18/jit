//
// Created by Rushe on 8/15/2026.
//

#ifndef JITVM_AST_H
#define JITVM_AST_H

#include "bool.h"
#include "TokenType.h"
#include "Array.h"

typedef struct {
    TokenType token;
    struct Node* left;
    struct Node* right;
}BinaryExpr;

typedef struct {
    const char* name;
    struct Node* Nodes;
    char** args;
}FuncNode;

typedef struct {
    BinaryExpr* expr;
    struct Node* Nodes;
    struct IfStmt* ifStmt;
}IfStmt;

typedef struct {
    TokenType token;
    const char* Variable;
} VariableNode;

typedef enum {
    BINARY_EXPR,
    FUNCTION_EXPR,
    NODE_ARRAY,
    IF_STMT,
    VARIABLE_NODE
}MemberType;

struct Node{
    MemberType type;
    union {
        BinaryExpr* binaryExpr;
        FuncNode* funcNode;
        struct Node* bodyNodes;
        IfStmt* ifStmt;
        VariableNode* variableNode;
    } data;
};

#endif //JITVM_AST_H