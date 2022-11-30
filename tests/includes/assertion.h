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
// No final faz o print dos testes
void assertResult(char *result, char *expectedResult, char *(args[3]), int queryNumber, double queryTime, int isMultiline);
// Irá imprimir no terminal em verde os valores corretos e em vermelho os valores errados.
// A função não irá mostrar a repostas corretas que tenham muitas linhas, porém, no caso contrário,
// irá imprimir o valor esperado mesmo que tenha muitas linhas caso esteja errada.
void logTest(TestLog *log);

#endif
