#include "../includes/testQ4.h"

#include "../../includes/query4.h"
#include "../../includes/reader.h"
#include "../includes/assertion.h"
#include "../includes/timer.h"

void testQ4(Token *token, Catalog *c, char *filename) {
	char *(arguments[]) = {token->value};

	clock_t time = clock();
	char *result = q4(c, arguments[0]);
	double queryTime = calcQueryTime(&time);

	char *expectedResult = readFile(filename);

	assertResult(result, expectedResult, arguments, 4, queryTime, 0);
}
