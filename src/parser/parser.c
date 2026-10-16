//
// Created by Rushe on 8/13/2026.
//
#include "../lexer/lexer.h"
#include "../parser/parser.h"

#include <assert.h>
#include <string.h>

typedef enum {
    P_ADD,
    P_SUBTRACT,
    P_MULTIPLY,
    P_DIVIDE,
    P_GREATER_THAN,
    P_LESS_THAN,
    P_EQUALS,
    P_EQUALITY,
    INVALID

} Precedence;

typedef struct {
    double lbp;
    double rbp;
} Binding_powers;

Binding_powers getBindingPower(Precedence op) {
    switch (op) {
        case P_ADD:
        case P_SUBTRACT: return (Binding_powers){2, 2.1};
        case P_MULTIPLY:
        case P_DIVIDE: return (Binding_powers){3, 3.1};
        case P_EQUALS: return (Binding_powers){0, 0.1};
        default: return (Binding_powers){-0.1, 0};
    }
}

Precedence getOperator(const char* op) {
    switch (*op) {
        case '+':
            return P_ADD;
        case '*':
            return P_MULTIPLY;
        case '/':
            return P_DIVIDE;
        case '-':
            return P_SUBTRACT;
        case '=':
            return P_EQUALS;
        default:
            return INVALID;
    }
}

Token lookahead(TokenArray* array, int current) {
    return array->items[current + 1];

}

bool unary(TokenArray* array, int current) {
    return array->items[current].type == BANG || array->items[current].type == MINUS;
}

const char* term(TokenArray* array, int *current) {
    if (unary(array, *current)) {

        assert(lookahead(array, *current).type == IDENTIFIER);
        const char* result = strcat((char*)array->items[*current].lexeme,lookahead(array, *current).lexeme);
        advance(current);
        return result;
    }

    return array->items[*current].lexeme;
}

Node* prattParser(TokenArray* tokenArray, int* current, double min_bp, int line) {

    Node* lhs;

    //return node, must be Binary_expr
    Node expression;
    expression.type = BINARY_EXPR;

    //atom token and atom lexeme
    TokenType token = tokenArray->items[*current].type;
    const char* lexeme = term(tokenArray, current);

    //initial lhs with the first variable
    if (token == PAREN_LEFT) {
        lhs = handleParen(tokenArray, current, line);
    } else {
        VariableNode* ptr1 = malloc(sizeof(VariableNode));
        ptr1->token = token;
        ptr1->Variable = lexeme;

        lhs = malloc(sizeof(Node));
        lhs->type = VARIABLE_NODE;
        lhs->data.variableNode = ptr1;
    }



    //set result to lhs
    Node* result = lhs;
    Node* new;
    Node* rhs;
    BinaryExpr* bin;

    while (true) {

        advance(current);
        const char* op = tokenArray->items[*current].lexeme;
        TokenType opToken = tokenArray->items[*current].type;
        Precedence operator = getOperator(op);
        Binding_powers bp = getBindingPower(operator);

        if (min_bp > bp.lbp) {
            --*current;
            break;
        }
        advance(current);
        rhs = prattParser(tokenArray, current, bp.rbp, line);

        new = malloc(sizeof(Node));
        result = new;
        bin = malloc(sizeof(BinaryExpr));
        bin->token = opToken;
        bin->left = lhs;
        bin->right = rhs;
        assert(result != lhs);

        result->type = BINARY_EXPR;
        result->data.binaryExpr = bin;

        lhs = result;
    }
    return result;
}

Node* handleParen(TokenArray* array, int* current, int line) {
    advance(current);
     Node* expr = prattParser(array, current, 0, line);
    if (lookahead(array, *current).type != PAREN_RIGHT) {
        //do error
    }

    return expr;
}

void handleFuncArgs(TokenArray* array, int* current, StringArray* result) {
    advance(current);
    TokenType token = array->items[*current].type;
    if (token == PAREN_RIGHT) {
        advance(current);
        return;
    }

    while (token != PAREN_RIGHT) {
        advance(current);
        token = array->items[*current].type;
        char* arg = (char*)array->items[*current].lexeme;
        array_append(char*, result, arg);

        //check for comma or right paren
        advance(current);
    }
}

Loop* loop(TokenArray* array, int* current) {
    Loop* result = malloc(sizeof(Loop));
    result->condition = prattParser(array, current, 0, array->items[*current].line);
    advance(current);
    result->body = recursiveDescent(array, current, result->body);
    advance(current);
    return result;
}

//handle function, if statement, loops, and expression
Node* recursiveDescent(TokenArray* tokenArray, int* current,  Node* right) {
    right = malloc(sizeof(Node));
    switch (tokenArray->items[*current].type) {
        case FUNC:
            right->data.binaryExpr->left->data.funcNode = func(tokenArray, current);
            break;
        case IF: right->data.binaryExpr->left->data.ifStmt = condition(tokenArray, current);
            break;
        case FOR:
        case WHILE:
            right->data.binaryExpr->left->data.loopNode = loop(tokenArray, current);
            break;
        case NEWLINE:
            free(right);
            right = recursiveDescent(tokenArray, current, right);
            break;
        case END:
            free(right);
            right = NULL;
            return right;
        case IDENTIFIER: right->data.binaryExpr->left = prattParser(tokenArray, current, 0, tokenArray->items[*current].line);
            break;
        default:
            //handle panic mode parsing
            break;
    }

    assert(tokenArray->items[*current].type == NEWLINE);
    advance(current);
    right->data.binaryExpr->right = recursiveDescent(tokenArray, current, right->data.binaryExpr->right);
    return right;
}

IfStmt* condition(TokenArray* array, int* current) {
    IfStmt* result = malloc(sizeof(IfStmt));
    int line = array->items[*current].line;
    result->condition = prattParser(array, current, 0, line);

    //check for left brace
    advance(current);

    result->body = recursiveDescent(array, current, result->body);

    //check for right brace
    advance(current);

    if (lookahead(array, *current).type == ELSE) {
        result->ifStmt = condition(array, current);
    } else {
        result->ifStmt = NULL;
    }

    //check for leftBrace
    advance(current);

    return result;
}

FuncNode* func(TokenArray* tokenArray, int* current) {
    FuncNode* function;
    function = malloc(sizeof(FuncNode));
    advance(current);
    function->name = tokenArray->items[*current].lexeme;
    StringArray args;
    handleFuncArgs(tokenArray, current, &args);
    function->args = args;

    //check for left brace
    advance(current);

    function->body = recursiveDescent(tokenArray, current, function->body);

    //check for right brace
    advance(current);

    return function;
}

int main() {
    TokenArray tokenArray = scanTokens("x = 5\n if (x = 5) {\n x = 5\n}");
    int current = 0;
    Node* parsedTree = prattParser(&tokenArray, &current, 0, 0);
    free(parsedTree);
}