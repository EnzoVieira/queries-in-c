#include "../includes/parserTest.h"

#include "../includes/testQ1.h"
#include "../includes/testQ2.h"
#include "../includes/testQ3.h"
#include "../includes/testQ4.h"
#include "../includes/testQ5.h"
#include "../includes/testQ6.h"


#include <stdio.h>
#include <stdlib.h>

// Testa se uma string está contida dentro de um array de string
// Exemplo:
// includesIn("foo", ["foo", "bar"], 2) = true
int isTestIncluded(char *value, char *arr[], int N) {
	for (int i = 0; i < N; i++) {
		if(strcmp(value, arr[i]) == 0) return 1;
	}

	return 0;
}

void parserTest(Lexer *lexer, Catalog *c, int argc, char* argv[]) {
	Token *token = NULL;

	int command = 1;
	char *filename = calloc(strlen("exemplos_de_queries2/tests_2/commandX_output.txt") + 2, sizeof(char));

	while ((token = getNextToken(lexer))->type != TOKEN_EOF) {
		sprintf(filename, "exemplos_de_queries2/tests_2/command%d_output.txt", command);

		if (token->type == TOKEN_QUERY) {
			switch (token->value[0]) {
				case '1': {
					token = getNextToken(lexer);

					if (argc < 4 || isTestIncluded("q1", argv, argc)) 
						testQ1(token, c, filename);

					break;
				}

				case '2': {
					token = getNextToken(lexer);

					if (argc < 4 || isTestIncluded("q2", argv, argc)) 
						testQ2(token, c, filename);

					break;
				}

				case '3': {
					token = getNextToken(lexer);

					if (argc < 4 || isTestIncluded("q3", argv, argc)) 
						testQ3(token, c, filename);

					break;
				}

				case '4': {
					token = getNextToken(lexer);

					if (argc < 4 || isTestIncluded("q4", argv, argc)) 
						testQ4(token, c, filename);

					break;
				}

				case '5': {
					Token *token1 = getNextToken(lexer);
					Token *token2 = getNextToken(lexer);

					Token *(tokens[2]) = {token1, token2};
					
					if (argc < 4 || isTestIncluded("q5", argv, argc)) 
						testQ5(tokens,c,filename);

					break;
				}

				case '6': {
					Token *token1 = getNextToken(lexer);
					Token *token2 = getNextToken(lexer);
					Token *token3 = getNextToken(lexer);

					Token *(tokens[3]) = {token1, token2, token3};

					if (argc < 4 || isTestIncluded("q6", argv, argc)) 
						testQ6(tokens, c, filename);

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