#ifndef PARSER_TEST_H
#define PARSER_TEST_H

#include "../../includes/query1.h"
#include "../../includes/query2.h"
#include "../../includes/query3.h"
#include "../../includes/query4.h"
#include "../../includes/query6.h"

#include "../../includes/token.h"
#include "../../includes/lexer.h"
#include "../../includes/reader.h"

void parserTest(Lexer *lexer, Catalog *c);

#endif