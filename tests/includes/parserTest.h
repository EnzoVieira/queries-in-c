#ifndef PARSER_TEST_H
#define PARSER_TEST_H

#include "testQ1.h"
#include "testQ2.h"
#include "testQ3.h"
#include "testQ4.h"
#include "testQ6.h"

#include "../../includes/lexer.h"
#include "../../includes/reader.h"

// Testa se uma string está contida dentro de um array de string.
// Exemplo:
// isTestIncluded("foo", ["foo", "bar"], 2) = true
int isTestIncluded(char *value, char *arr[], int N);
void parserTest(Lexer *lexer, Catalog *c, int argc, char* argv[]);

#endif
