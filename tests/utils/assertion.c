#include "../includes/assertion.h"

#include "../../includes/reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Verifica se o valor obtido da query é igual ao valor esperado.
// No final faz o print dos testes
void assertResult(char *result, char *expectedResult, char *(args[3]), int queryNumber, double queryTime, int isMultiline) {
  int isCorrect = 0;

	// Se o resultado for NULL, deve-se verificar se o resultado esperado também é NULL
	// e como a função logTest já espera que os dois terminem com um '\n', tem que ser inserido um '\n' no final da string
	if (result == NULL && expectedResult == NULL) {
		isCorrect = 1;
		result = strdup("NULL\n");
		expectedResult = strdup("NULL\n");
	} else {
		isCorrect = strcmp(result, expectedResult) == 0;
	}

	TestLog results = {
		.result = result,
		.expectedResult = expectedResult,
		.isMultiline = isMultiline,
		.isCorrect = isCorrect,

		.query = queryNumber,
		.queryTime = queryTime,
	};

	if (args[0]) results.firstArgument = args[0];
	if (args[1]) results.secondArgument = args[1];
	if (args[2]) results.thirdArgument = args[2];

	logTest(&results);
}

// Irá imprimir no terminal em verde os valores corretos e em vermelho os valores errados.
// A função não irá mostrar a repostas corretas que tenham muitas linhas, porém, no caso contrário,
// irá imprimir o valor esperado mesmo que tenha muitas linhas caso esteja errada.
void logTest(TestLog *log) {
	if (log->isCorrect) {
		// Cor verde
		printf("\033[32m");

		printf("%.3fs - query%d('%s') ", log->queryTime, log->query, log->firstArgument);
		if (!log->isMultiline) printf("= %s", log->result);

		// Cor padrão
		printf("\033[0m");
		if (log->isMultiline) printf("\n");
	} else {
		// Cor vermelha
		printf("\033[31m");
		printf("%.3fs - query%d('%s')\n", log->queryTime, log->query, log->firstArgument);

		printf("\tEsperado:");

		if (log->isMultiline) printf("\n");
		if (!log->isMultiline) printf(" ");
		printf("%s", log->expectedResult);
		
		printf("\tObteve:");
		if (log->isMultiline) printf("\n");
		if (!log->isMultiline) printf("   ");
		printf("%s", log->result);

		// Cor padrão
		printf("\033[0m");
	}

	if (log->result) free(log->result);
	if (log->expectedResult) free(log->expectedResult);
}
