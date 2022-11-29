#ifndef ASSERTION_H
#define ASSERTION_H

#include "../../includes/query1.h"

#include "../../includes/token.h"
#include "../../includes/lexer.h"
#include "../../includes/reader.h"

typedef struct {
	char *filename;
	char *result;
	char *expectedResult;
	int isCorrect;
	int isMultiline;

	int query;
	double queryTime;

	char *firstArgument;
	char *secondArgument;
	char *thirdArgument;
} TestLog;

// Verifica se o valor obtido da query é igual ao valor esperado.
// Irá imprimir no terminal em verde os valores corretos e em vermelho os valores errados.
void assertResult(char *result, char *expectedResult, char *(args[3]), int queryNumber, double queryTime, int isMultiline);
void logTest(TestLog *log);

#endif
