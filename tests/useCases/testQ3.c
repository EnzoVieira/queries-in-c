#include "../includes/testQ3.h"

#include "../../includes/query3.h"
#include "../../includes/reader.h"
#include "../includes/assertion.h"
#include "../includes/timer.h"

#include <stdlib.h>

void testQ3(Token *token, Catalog *c, char *filename) {
	char *(arguments[]) = {token->value};

	clock_t time = clock();
	char *result = q3(c, atoi(arguments[0]));
	double queryTime = calcQueryTime(&time);

	char *expectedResult = readFile(filename);

	assertResult(result, expectedResult, arguments, 3, queryTime, 1);
}
