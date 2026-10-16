//
// Created by Rushe on 8/15/2026.
//

#ifndef JITVM_AST_H
#define JITVM_AST_H

#include "TokenType.h"
#include "Array.h"

new_array(char*, String);
typedef struct IfStmt IfStmt;
typedef struct Node Node;
typedef struct Loop Loop;

typedef struct {
    TokenType token;
    Node* left;
    Node* right;
}BinaryExpr;

struct Loop {
    Node* condition;
    Node* body;
};

typedef struct {
    const char* name;
    Node* body;
    StringArray args;
}FuncNode;

struct IfStmt {
    Node* condition;
    Node* body;
    IfStmt* ifStmt;
};

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
        Node* bodyNodes;
        IfStmt* ifStmt;
        VariableNode* variableNode;
        Loop* loopNode;
    } data;
};

#endif //JITVM_AST_H