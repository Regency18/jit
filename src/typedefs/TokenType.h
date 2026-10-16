//
// Created by Rushe on 7/23/2026.
//

#ifndef JITVM_TOKENTYPE_H
#define JITVM_TOKENTYPE_H
/**
 * The Enumerator for each possible token type that can be parsed by the lexer
 */
typedef enum {
    //Single Character Tokens
    PAREN_LEFT, PAREN_RIGHT, BRACE_LEFT, BRACE_RIGHT, BRACKET_LEFT, BRACKET_RIGHT,
    COMMA, COLON, SEMICOLON, PLUS, MINUS, DOT, STAR, SLASH, NEWLINE,


    //One or two character tokens
    BANG_EQUAL, EQUAL,
    BANG, EQUAL_EQUAL,
    LESS, LESS_EQUAL,
    GREATER, GREATER_EQUAL,

    //Types
    INTEGER, STRING, FLOAT, BOOLEAN,

    //Keywords
    AND, ELSE, NOT, FOR, WHILE, IF, TRUE, FALSE, RETURN, OR, IDENTIFIER, FUNC, PRINT,

    END
} TokenType;

/**
 * The Token that that is placed in the Tokens list for a program
 * May add or remove types based on what is needed.
 * Currently:
 *
 * Enum TokenType
 */
typedef struct {
    TokenType type;
    const char* lexeme;
    int line;
} Token;

#endif //JITVM_TOKENTYPE_H