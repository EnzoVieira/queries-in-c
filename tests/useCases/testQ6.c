#include "../includes/testQ6.h"

void testQ6(Token *(tokens[3]), Catalog *c, char *filename) {
	clock_t time = clock();
	char *result = q6(c, tokens[0]->value, tokens[1]->value, tokens[2]->value);
	double queryTime = calcQueryTime(&time);

	if (result != NULL) {
		TestLog results = {
			.filename = filename,
			.result = result,
			.isMultiline = 0,

			.query = 6,
			.queryTime = queryTime,

			.firstArgument = tokens[0]->value,
			.secondArgument = tokens[1]->value,
			.thirdArgument = tokens[2]->value,
		};

		logTest(&results);
	}
}
