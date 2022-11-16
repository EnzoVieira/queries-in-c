#include "../includes/parserTest.h"

typedef struct {
	char *filename;
	char *result;
	int isMultiline;

	int query;
	double queryTime;

	char *firstArgument;
	char *secondArgument;
	char *thirdArgument;
} TestLog;

double calcQueryTime(clock_t *start) {
  clock_t time = clock() - *start;
  double queryTime = ((double)time)/CLOCKS_PER_SEC;

  return queryTime;
}

// Função que retornará NULL caso as respostas sejam iguais,
// caso contrário, retornará o resultado esperado.
char *assertResult(char *result, const char *filename, int isMultiline) {
  char *expectedResult = readFile(filename);
	
	if (!isMultiline) 
  	result = strcat(result, "\n");

  if (strcmp(result, expectedResult) == 0) {
    return NULL;
  }

  return expectedResult;
}

void logTest(TestLog *log) {
	char *expectedResult;

	if ((expectedResult = assertResult(log->result, log->filename, log->isMultiline)) == NULL) {
		// Cor verde
		printf("\033[32m");

		printf("%.3fs - query%d('%s') ", log->queryTime, log->query, log->firstArgument);
		!log->isMultiline && printf("= %s", log->result);

		// Cor padrão
		printf("\033[0m");
		log->isMultiline && printf("\n");
	} else {
		// Cor vermelha
		printf("\033[31m");
		printf("%.3fs - query%d('%s')\n", log->queryTime, log->query, log->firstArgument);

		printf("\tEsperado:");

		log->isMultiline && printf("\n");
		!log->isMultiline && printf(" ");
		printf("%s", expectedResult);
		
		printf("\tObteve:");
		log->isMultiline && printf("\n");
		!log->isMultiline && printf("   ");
		printf("%s", log->result);

		// Cor padrão
		printf("\033[0m");

		free(expectedResult);
	}
}

void parserTest(Lexer *lexer, Catalog *c) {
	Token *token = NULL;
	char *result;
	clock_t time;
	double queryTime;

	int command = 1;
	char *filename = calloc(strlen("exemplos_de_queries2/tests_2/commandX_output.txt") + 2, sizeof(char));

	while ((token = getNextToken(lexer))->type != TOKEN_EOF) {
		sprintf(filename, "exemplos_de_queries2/tests_2/command%d_output.txt", command);

		if (token->type == TOKEN_QUERY) {
			switch (token->value[0]) {
			case '1': {
				token = getNextToken(lexer);

        time = clock();
				result = q1(c, token->value);
        queryTime = calcQueryTime(&time);

				if (result != NULL) {
					TestLog results = {
						.filename = filename,
						.result = result,
						.isMultiline = 0,

						.query = 1,
						.queryTime = queryTime,

						.firstArgument = token->value,
					};

					logTest(&results);
				}

				break;
			}
			case '2': {
				token = getNextToken(lexer);

				time = clock();
				result = q2(c, atoi(token->value));
				queryTime = calcQueryTime(&time);

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

				break;
			}
			case '3': {
				token = getNextToken(lexer);
				break;
			}
			case '4': {
				token = getNextToken(lexer);

				time = clock();
				result = q4(c, token->value);
				queryTime = calcQueryTime(&time);

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