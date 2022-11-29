#include "../includes/testQ3.h"

void testQ3(Token *token, Catalog *c, char *filename) {
	clock_t time = clock();
	char *result = q3(c, atoi(token->value));
	double queryTime = calcQueryTime(&time);

	if (result != NULL) {
		TestLog results = {
			.filename = filename,
			.result = result,
			.isMultiline = 1,

			.query = 3,
			.queryTime = queryTime,

			.firstArgument = token->value,
		};

		logTest(&results);
	}
}
