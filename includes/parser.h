#ifndef PARSER_H
#define PARSER_H

#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query6.h"

#include "lexer.h"
#include "writer.h"

void parser(Lexer *lexer, Catalog *c);

#endif