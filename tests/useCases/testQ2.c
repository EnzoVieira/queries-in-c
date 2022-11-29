#include "../includes/testQ2.h"

void testQ2(Token *token, Catalog *c, char *filename) {
	clock_t time = clock();
	char *result = q2(c, atoi(token->value));
	double queryTime = calcQueryTime(&time);

	if (result != NULL) {
		TestLog results = {
			.filename = filename,
			.result = result,
			.isMultiline = 1,

			.query = 2,
			.queryTime = queryTime,

			.firstArgument = token->value,
		};

		logTest(&results);
	}
}
