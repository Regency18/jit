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
 * @param token the token of the next token
 * @return return true if it matches and return false if it doesn't
 */
Token lookahead(TokenArray* tokenArray, int current);


/**
 * Main recursive descent function
 * @param tokenArray array of tokens
 * @param current current index
 */
void recursiveDescent(TokenArray* tokenArray, int* current);

/**
 * function for functions
 * @param tokenArray array of tokens
 * @param current current index
 */
void funcNode(TokenArray* tokenArray, int* current);

struct Node* handleParen(TokenArray* array, int* current, int line);


#endif //JITVM_PARSER_H