#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct catalog Catalog;

void parser(Lexer *lexer, Catalog *c);

#endif