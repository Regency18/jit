//
// Created by Rushe on 8/13/2026.
//

#ifndef JITVM_PARSER_H
#define JITVM_PARSER_H
#include "../typedefs/Array.h"
#include "../typedefs/TokenType.h"
#include "../typedefs/ast.h"


/**
 * The root function that runs the parser and starts the parsing of the tokens.
 * @param tokenArray Array of all the tokens from program string
 */
//void Parser(TokenArray* tokenArray, union node* rootNode);

/**
 * Checking if the next character is the correct character
 * @param tokenArray the token of the next token
 * @return return true if it matches and return false if it doesn't
 */
Token lookahead(TokenArray* tokenArray, int current);

/**
 *
 * @param array array of tokens
 * @param current current index
 * @return Loop node
 */
Loop* loop(TokenArray* array, int* current);

/**
 *
 * @param tokenArray array of parsed tokens
 * @param current current index
 * @return if statement node
 */
struct IfStmt* condition(TokenArray* tokenArray, int* current);

/**
 * returns indentifier for variable name
 * @param array tokenarray
 * @param current current index
 * @return variable name
 */
const char* term(TokenArray* array, int *current);


/**
 * Main recursive descent function
 * @param tokenArray array of tokens
 * @param current current index
 */
struct Node* recursiveDescent(TokenArray* tokenArray, int* current, struct Node* right);

/**
 * function for functions
 * @param tokenArray array of tokens
 * @param current current index
 */
FuncNode* func(TokenArray* tokenArray, int* current);

struct Node* handleParen(TokenArray* array, int* current, int line);


#endif //JITVM_PARSER_H