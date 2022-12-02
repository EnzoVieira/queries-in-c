#include "../../includes/lexer.h"

#include <stdlib.h>
#include <ctype.h>

Lexer *createLexer(char *args) {
  Lexer *lexer = calloc(1, sizeof(Lexer));

  lexer->length = strlen(args);
  lexer->args = args;
  lexer->currentChar = args[0];
  lexer->index = 0;

  return lexer;
}

void lexerAdvance(Lexer *lexer) {
  if (lexer->index < lexer->length && lexer->currentChar != '\0') {
    lexer->index += 1;
    lexer->currentChar = lexer->args[lexer->index];
  }
}

void lexerSkipWhitespace(Lexer *lexer) {
  // Whitespace, tab, carriage return, new line
  while(lexer->currentChar == ' ' || lexer->currentChar == '\t' || lexer->currentChar == 13 || lexer->currentChar == 10) {
    lexerAdvance(lexer);
  }
}

Token *getNextToken(Lexer *lexer) {
  lexerSkipWhitespace(lexer);

  char *instruction = calloc(1, sizeof(char));
  instruction[0] = '\0';

  while(lexer->currentChar != '\0' && lexer->currentChar != ' ' && lexer->currentChar != '\n') {
    instruction = realloc(instruction, (strlen(instruction) + 2) * sizeof(char));

    strcat(instruction, &(lexer->currentChar));

    lexerAdvance(lexer);
  }
  
  lexerAdvance(lexer);

  if (isdigit(instruction[0]) && strlen(instruction) == 1) {
    return createToken(instruction, TOKEN_QUERY);
  }
  else if (lexer->currentChar == 0) {
    return createToken(instruction, TOKEN_EOF);
  }
  
  return createToken(instruction, TOKEN_ARGUMENT);
}