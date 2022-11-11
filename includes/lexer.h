#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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