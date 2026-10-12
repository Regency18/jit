#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"


/**
 *
 * @param current current position
 */
void advance(int* current) {
    printf("advancing\n");
    (*current)++;
}

/**
 *
 * @param str The substring passed in for lexical analysis
 * @return if the string is at the end
 */
bool isAtEnd(const char* str) {

    //checks for null terminator
    return *str == '\0';
}

bool match(char token, const char* str, const int* currentPos) {
    if (isAtEnd(&token)) return false;

    if (token != str[*currentPos + 1] ) return false;

    return true;
}

char* turnCharIntoString(const char character) {
    char* string = malloc(2);
    string[0] = character;
    string[1] = '\0';
    return string;
}

void addSingleToken(const TokenType token, TokenArray* tokenArray, const char keyword, const int* line) {
    char* lexeme = turnCharIntoString(keyword);
    //add new token and keyword to array
    const Token newToken = {token, lexeme, *line};
    array_append(tokenArray, newToken);
}

void addDoubleToken(const TokenType token, TokenArray* tokenArray, const char* lexeme, const int* line) {
    //add new token and keyword to array
    const Token newToken = {token, lexeme, *line};
    array_append(tokenArray, newToken);
}

char* getLiteral(const int start, const int* current, const char* str) {
    const int length = *current-start+1;
    //copy substring from start index to current index
    char* string = malloc(length + 1);
    strncpy(string, str + start,length);
    string[length] = '\0';
    return string;
}

void numberToken(char token, int* current, const char* str, int start, TokenArray* tokenArray, const int* line) {
    while (isdigit(token - '0')) {
        advance(current);
        token = str[*current];
    }

    if (token != '.' || isdigit(str[*current + 1] - '0')) {
        //change this to substring

        const char* number = getLiteral(start, current, str);
        addDoubleToken(INTEGER, tokenArray, number, line);
        return;
    }

    advance(current);
    while (isdigit(token - '0')) {
        advance(current);
        token = str[*current];
    }

    const char* number = getLiteral(start, current, str);
    addDoubleToken(FLOAT, tokenArray, number, line);
}


void identifier(const char* str, int* current, kh_tokenMap_t* map, TokenArray* tokenArray, int start, const int* line) {
    while ((isalnum(str[*current]) || match('_', str, current)) && isalnum(str[*current+1])) {
        advance(current);
    }

    if (!isalnum(str[*current])) printf("Making thing now");
    const char* text = getLiteral(start, current, str);
    printf("token: %s\n", text);
    //get enum keyword using text
    khint_t k = kh_get(tokenMap, map, text);
    if (k != kh_end(map)) {
        TokenType Token = kh_value(map, k);
        addDoubleToken(Token, tokenArray, text, line);
    } else {
        addDoubleToken(IDENTIFIER, tokenArray, text, line);
    }
};

void putToken(khiter_t* k,kh_tokenMap_t *map, const char* key, TokenType token, int* ret){
    *k = kh_put_tokenMap(map, key, ret);
    kh_val(map, *k) = token;
}

kh_tokenMap_t* makeMap() {
    khiter_t k;
    int ret;
    khash_t(tokenMap) *map = kh_init(tokenMap);
    putToken(&k, map, "and", AND, &ret);
    putToken(&k, map, "else", ELSE, &ret);
    putToken(&k, map, "for", FOR, &ret);
    putToken(&k, map, "if", IF, &ret);
    putToken(&k, map, "while", WHILE, &ret);
    putToken(&k, map, "return", RETURN, &ret);
    putToken(&k, map, "true", TRUE, &ret);
    putToken(&k, map, "false", FALSE, &ret);
    putToken(&k, map, "return", RETURN, &ret);
    putToken(&k, map, "or", OR, &ret);
    putToken(&k, map, "func", FUNC, &ret);

    return map;
}

void handleString(const char* str, int* current, TokenArray* tokenArray, int start, const int* line) {
    while (str[*current] != '"' && str[*current] != '\0') {
        advance(current);
    }

    if (str[*current] == '\0') {
        printf("String is unterminated");
        exit(1);
    }

    const char* string = getLiteral(start, current, str);

    addDoubleToken(STRING, tokenArray, string, line);
}

void handleComments(const char* str, int* current, TokenArray* tokenArray, const char token, const int* line) {
    if (str[*current + 1] == '/') {
        while (str[*current] != '\n' && str[*current] != '\0') {
            advance(current);
        }
    } else {
        addSingleToken(SLASH, tokenArray, token, line);
    }
}

void scanToken(const char* str, int start, int* current, TokenArray* tokenArray, kh_tokenMap_t *map, int* line) {
    char token = str[start];
    printf("Token: %c\n", token);
    switch (token) {
        case '(': addSingleToken(PAREN_LEFT, tokenArray, token, line); break;
        case ')': addSingleToken(PAREN_RIGHT, tokenArray, token, line); break;
        case '{': addSingleToken(BRACE_LEFT, tokenArray, token, line); break;
        case '}': addSingleToken(BRACE_RIGHT, tokenArray, token, line); break;
        case '[': addSingleToken(BRACKET_LEFT, tokenArray, token, line); break;
        case ']': addSingleToken(BRACKET_RIGHT, tokenArray, token, line); break;
        case ',': addSingleToken(COMMA, tokenArray, token, line); break;
        case ':': addSingleToken(COLON, tokenArray, token, line); break;
        case ';': addSingleToken(SEMICOLON, tokenArray, token, line); break;
        case '+': addSingleToken(PLUS, tokenArray, token, line); break;
        case '-': addSingleToken(MINUS, tokenArray, token, line); break;
        case '.': addSingleToken(DOT, tokenArray, token, line); break;
        case '*': addSingleToken(STAR, tokenArray, token, line); break;
        case '!': addSingleToken(match('=', str, current) ? BANG_EQUAL: BANG, tokenArray, token, line); break;
        case '=': addSingleToken(match('=', str, current) ? EQUAL_EQUAL: EQUAL, tokenArray, token, line); break;
        case '<': addSingleToken(match('=', str, current) ? LESS_EQUAL: LESS, tokenArray, token, line); break;
        case '>': addSingleToken(match('=', str, current) ? GREATER_EQUAL: GREATER, tokenArray, token, line); break;
        case '/':
            handleComments(str, current, tokenArray, token, line); break;
        case '\n' : addSingleToken(NEWLINE, tokenArray, token, line); (*line)++; break;
        case '\r':
        case '\t':
        case '\b':
        case ' ':
        case '\v':
        case '\f': break;
        case '"':
            handleString(str, current, tokenArray, start, line);
            break;
        default:
            if (isdigit(token) || token == '0') {
                numberToken(token, current, str, start, tokenArray, line);
                printf("number");
            } else if (isalpha(token)){
                identifier(str, current, map, tokenArray, start, line);
                printf("identifier");
            } else {
                printf("Unrecognized token: %c\n", token);
            }
    }
}


TokenArray scanTokens(const char* str) {
    int start = 0, current = 0, line = 0;
    TokenArray array = {0};
    char token = str[0];

    while (!isAtEnd(&token))  {
        kh_tokenMap_t* map = makeMap();
        scanToken(str, start, &current, &array, map, &line);
        advance(&current);
        start = current;
        token = str[start];
    }
    addDoubleToken(END, &array, "bitch", &line);

    return array;
};


// LEXER_H