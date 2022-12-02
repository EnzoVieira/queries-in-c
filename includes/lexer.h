#ifndef LEXER_H
#define LEXER_H

#include <string.h>

#include "token.h"

typedef struct {
  size_t length;
  char *args;
  char currentChar;
  unsigned int index;
} Lexer;

Lexer *createLexer(char *args);
void lexerAdvance(Lexer *lexer);
void lexerSkipWhitespace(Lexer *lexer);
Token *getNextToken(Lexer *lexer);

#endif