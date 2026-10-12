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

struct Node* prattParser(TokenArray* tokenArray, int* current, double min_bp, int line) {

    struct Node* lhs;

    //return node, must be Binary_expr
    struct Node expression;
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

        lhs = malloc(sizeof(struct Node));
        lhs->type = VARIABLE_NODE;
        lhs->data.variableNode = ptr1;
    }



    //set result to lhs
    struct Node* result = lhs;
    struct Node* new;
    struct Node* rhs;
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

        new = malloc(sizeof(struct Node));
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

struct Node* handleParen(TokenArray* array, int* current, int line) {
    advance(current);
    struct Node* expr = prattParser(array, current, 0, line);
    if (lookahead(array, *current).type != PAREN_RIGHT) {
        //do error
    }

    return expr;
}

char** handleFuncArgs(TokenArray* array, int* current) {
    advance(current);
    char** result;
    while () {

    }


}

//handle function, if statement, loops, and expression
void recursiveDescent(TokenArray* tokenArray, int* current) {
    switch (tokenArray->items[*current].type) {
        case FUNC:
            funcNode(tokenArray, current);
            break;
        default: break;
    }
}

void funcNode(TokenArray* tokenArray, int* current) {
    FuncNode* function = malloc(sizeof(FuncNode));
    advance(current);
    function->name = tokenArray->items[*current].lexeme;
    function->args = handleFuncArgs(tokenArray, current);
}

int main() {
    TokenArray tokenArray = scanTokens("x = a + 5 + 3");
    int current = 0;
    struct Node* parsedTree = prattParser(&tokenArray, &current, 0, 0);
    free(parsedTree);
}