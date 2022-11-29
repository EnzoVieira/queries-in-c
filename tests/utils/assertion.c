#include "../includes/assertion.h"

// Verifica se o valor obtido da query é igual ao valor esperado.
// Irá imprimir no terminal em verde os valores corretos e em vermelho os valores errados.
void assertResult(char *result, char *expectedResult, char *(args[3]), int queryNumber, double queryTime, int isMultiline) {
  int isCorrect = 0;

	// Se o resultado for NULL, deve-se verificar se o resultado esperado também é NULL
	// e como todo log por padrão já espera que os dois terminem com um \n, 
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

void logTest(TestLog *log) {
	if (log->isCorrect) {
		// Cor verde
		printf("\033[32m");

		printf("%.3fs - query%d('%s') ", log->queryTime, log->query, log->firstArgument);
		!log->isMultiline && printf("= %s", log->result);

		// Cor padrão
		printf("\033[0m");
		log->isMultiline && printf("\n");
	} else {
		// Cor vermelha
		printf("\033[31m");
		printf("%.3fs - query%d('%s')\n", log->queryTime, log->query, log->firstArgument);

		printf("\tEsperado:");

		log->isMultiline && printf("\n");
		!log->isMultiline && printf(" ");
		printf("%s", log->expectedResult);
		
		printf("\tObteve:");
		log->isMultiline && printf("\n");
		!log->isMultiline && printf("   ");
		printf("%s", log->result);

		// Cor padrão
		printf("\033[0m");
	}

	if (log->result) free(log->result);
	if (log->expectedResult) free(log->expectedResult);
}
