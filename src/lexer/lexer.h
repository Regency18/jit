//
// Created by Rushe on 8/12/2026.
//

#ifndef JITVM_LEXER_H
#define JITVM_LEXER_H
#include "../typedefs/bool.h"
#include "../typedefs/Array.h"
#include "../typedefs/khash.h"
#include "../typedefs/TokenType.h"
new_array(Token);

KHASH_MAP_INIT_STR(tokenMap, TokenType);

void advance(int* current);

bool isAtEnd(const char* str);

bool match(char token, const char* str, const int* currentPos);

char* turnCharIntoString(const char character);

void addSingleToken(const TokenType token, TokenArray* tokenArray, const char keyword, const int* line);

void addDoubleToken(const TokenType token, TokenArray* tokenArray, const char* lexeme, const int* line);

char* getLiteral(const int start, const int* current, const char* str);

void numberToken(char token, int* current, const char* str, int start, TokenArray* tokenArray, const int* line);

void identifier(const char* str, int* current, kh_tokenMap_t* map, TokenArray* tokenArray, int start, const int* line);

void putToken(khiter_t* k,kh_tokenMap_t *map, const char* key, TokenType token, int* ret);

void handleString(const char* str, int* current, TokenArray* tokenArray, int start, const int* line);

void handleComments(const char* str, int* current, TokenArray* tokenArray, const char token, const int* line);

void scanToken(const char* str, int start, int* current, TokenArray* tokenArray, kh_tokenMap_t *map, int* line);

TokenArray scanTokens(const char* str);

#endif //JITVM_LEXER_H