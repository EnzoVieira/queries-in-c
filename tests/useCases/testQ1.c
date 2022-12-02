#include "../includes/testQ1.h"

#include "../../includes/query1.h"
#include "../../includes/reader.h"
#include "../includes/assertion.h"
#include "../includes/timer.h"

void testQ1(Token *token, Catalog *c, char *filename) {
	char *(arguments[]) = {token->value};

	clock_t time = clock();
	char *result = q1(c, arguments[0]);
	double queryTime = calcQueryTime(&time);

	char *expectedResult = readFile(filename);

	assertResult(result, expectedResult, arguments, 1, queryTime, 0);
}
