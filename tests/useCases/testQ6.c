#include "../includes/testQ6.h"

#include "../includes/assertion.h"
#include "../includes/timer.h"
#include "../../includes/reader.h"
#include "../../includes/query6.h"

// Recebe um array com apontadores de 3 Tokens
void testQ6(Token *(tokens[3]), Catalog *c, char *filename) {
	char *(arguments[]) = {tokens[0]->value, tokens[1]->value, tokens[2]->value};

	clock_t time = clock();
	char *result = q6(c, arguments[0], arguments[1], arguments[2]);
	double queryTime = calcQueryTime(&time);

	char *expectedResult = readFile(filename);

	assertResult(result, expectedResult, arguments, 6, queryTime, 0);
}