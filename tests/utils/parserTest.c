#include "../includes/parserTest.h"

double calcQueryTime(clock_t *start) {
  clock_t time = clock() - *start;
  double queryTime = ((double)time)/CLOCKS_PER_SEC;

  return queryTime;
}

char *assertResult(char *result, const char *filename, int isMultiline) {
  char *expectedResult = readFile(filename);
  char *resultAux = calloc(strlen(result) + 1, sizeof(char));
	
	if (!isMultiline) 
  	resultAux = strcat(result, "\n");
	else {
		resultAux = result;
	}

  if (strcmp(resultAux, expectedResult) == 0) {
    return NULL;
  }

  return expectedResult;
}

void parserTest(Lexer *lexer, Catalog *c) {
	Token *token = NULL;

	int command = 1;
	char *filename = calloc(strlen("exemplos_de_queries2/tests_2/commandX_output.txt") + 2, sizeof(char));

	while ((token = getNextToken(lexer))->type != TOKEN_EOF) {
		sprintf(filename, "exemplos_de_queries2/tests_2/command%d_output.txt", command);

		if (token->type == TOKEN_QUERY) {
			switch (token->value[0]) {
			case '1': {
        clock_t time;
        double queryTime;

				token = getNextToken(lexer);

        time = clock();
				char *result = q1(c, token->value);
        queryTime = calcQueryTime(&time);

				if (result != NULL) {
					char *expectedResult;

					if ((expectedResult = assertResult(result, filename, 0)) == 0) {
						printf("\033[32m%.3fs - query1('%s') = %s\033[0m", queryTime, token->value, result);
					} else {
						printf("\033[31m%.3fs - query1('%s')\n", queryTime, token->value);
						printf("\tEsperado: %s", expectedResult);
						printf("\tObteve:   %s\033[0m", result);

						free(expectedResult);
					}

					free(result);
				}

				break;
			}
			case '2': {
				token = getNextToken(lexer);

				clock_t time = clock();
				char *result = q2(c, atoi(token->value));
				double queryTime = calcQueryTime(&time);

				if (result != NULL) {
					char *expectedResult;

					if ((expectedResult = assertResult(result, filename, 1)) == 0) {
						printf("\033[32m%.3fs - query2('%s')\n\033[0m", queryTime, token->value);
					} else {
						printf("\033[31m%.3fs - query2('%s')\n", queryTime, token->value);
						printf("\tEsperado:\n%s", expectedResult);
						printf("\tObteve:\n%s\033[0m", result);

						free(expectedResult);
					}

					free(result);
				}

				break;
			}
			case '3': {
				token = getNextToken(lexer);
				break;
			}
			case '4': {
				token = getNextToken(lexer);
				char *output = q4(c, token->value);

				if (output != NULL) {
					// writeFile(output, filename);
					free(output);
				}

				break;
			}
			case '5': {
				token = getNextToken(lexer);
				token = getNextToken(lexer);
				break;
			}
			case '6': {
				token = getNextToken(lexer);
				token = getNextToken(lexer);
				token = getNextToken(lexer);
				break;
			}
			case '7': {
				token = getNextToken(lexer);
				token = getNextToken(lexer);
				break;
			}
			case '8': {
				token = getNextToken(lexer);
				token = getNextToken(lexer);
				break;
			}
			case '9': {
				token = getNextToken(lexer);
				token = getNextToken(lexer);
				break;
			}
			}
		}

		command++;
	}
}