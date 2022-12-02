#include "../includes/testQ2.h"

#include "../../includes/query2.h"
#include "../../includes/reader.h"
#include "../includes/assertion.h"
#include "../includes/timer.h"

#include <stdlib.h>

void testQ2(Token *token, Catalog *c, char *filename) {
	// Array de agumentos (Tokens) que serão passados à query
	char *(arguments[]) = {token->value};

	clock_t time = clock();
	char *result = q2(c, atoi(token->value));
	double queryTime = calcQueryTime(&time);

	char *expectedResult = readFile(filename);

	assertResult(result, expectedResult, arguments, 2, queryTime, 1);
}
