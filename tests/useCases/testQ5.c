#include "../includes/testQ5.h"

#include "../../includes/query5.h"
#include "../../includes/reader.h"
#include "../includes/assertion.h"
#include "../includes/timer.h"

void testQ5(Token *(tokens[2]), Catalog *c, char *filename) {
	char *(arguments[]) = {tokens[0]->value, tokens[1]->value};

	clock_t time = clock();
	char *result = q5(c, arguments[0], arguments[1]);
	double queryTime = calcQueryTime(&time);

	char *expectedResult = readFile(filename);

	assertResult(result, expectedResult, arguments, 5, queryTime, 0);
}
