#include "../../includes/parser.h"

#include "../../includes/writer.h"

#include "../../includes/query1.h"
#include "../../includes/query2.h"
#include "../../includes/query3.h"
#include "../../includes/query4.h"
#include "../../includes/query6.h"

#include <stdlib.h>
#include <stdio.h>

struct catalog {
	void *users;
	void *drivers;
	void *rides;
};

void parser(Lexer *lexer, Catalog *c) {
	Token *token = NULL;

	int command = 1;
	char *filenameAux1 = "Resultados/command";
	char *filenameAux2 = "_output.txt";
	size_t filenameLength = strlen(filenameAux1) + strlen(filenameAux2) + 2;
	char *filename = calloc(filenameLength, sizeof(char));

	while ((token = getNextToken(lexer))->type != TOKEN_EOF) {
		sprintf(filename, "%s%d%s", filenameAux1, command, filenameAux2);

		if (token->type == TOKEN_QUERY) {
			switch (token->value[0]) {
			case '1': {
				token = getNextToken(lexer);
				char *output = q1(c, token->value);

				writeFile(output, filename);
				if (output != NULL) {
					free(output);
				}

				break;
			}
			case '2': {
				token = getNextToken(lexer);
				char *output = q2(c, atoi(token->value));

				writeFile(output, filename);
				if (output != NULL) {
					free(output);
				}

				break;
			}
			case '3': {
				token = getNextToken(lexer);
				char *output = q3(c, atoi(token->value));

				writeFile(output, filename);
				if (output != NULL) {
					free(output);
				}

				break;
			}
			case '4': {
				token = getNextToken(lexer);
				char *output = q4(c, token->value);

				writeFile(output, filename);
				if (output != NULL) {
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
				Token *token1 = getNextToken(lexer);
				Token *token2 = getNextToken(lexer);
				Token *token3 = getNextToken(lexer);

				char *output = q6(c, token1->value, token2->value, token3->value);

				writeFile(output, filename);
				if (output != NULL) {
					free(output);
				}

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