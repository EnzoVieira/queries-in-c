#include "../includes/testQ4.h"

void testQ4(Token *token, Catalog *c, char *filename) {
	clock_t time = clock();
	char *result = q4(c, token->value);
	double queryTime = calcQueryTime(&time);

	if (result != NULL) {
		TestLog results = {
			.filename = filename,
			.result = result,
			.isMultiline = 0,

			.query = 4,
			.queryTime = queryTime,

			.firstArgument = token->value,
		};

		logTest(&results);
	}
}
