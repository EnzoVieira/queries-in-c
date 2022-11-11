#include <stdio.h>

#include "includes/api.h"

#include "includes/userRepository.h"
#include "includes/driverRepository.h"
#include "includes/rideRepository.h"
#include "includes/catalogEntity.h"

#include "includes/token.h"
#include "includes/lexer.h"
#include "includes/reader.h"

struct catalog
{
    void *users;
    void *drivers;
    void *rides;
};

int main()
{
    Catalog c;
    c.users = createUsersHashData();
    c.drivers = createDriversHashData();
    c.rides = createRidesHashData();

    char *args = readFile("queries/queries.txt");

    Lexer *lexer = createLexer(args);
    Token *token = NULL;

    while ((token = getNextToken(lexer))->type != TOKEN_EOF) {
        

        if(token->type == TOKEN_QUERY) {
            switch(token->value[0]) {
                case '1': {
                    token = getNextToken(lexer);
                    q1(&c, token->value);
                }
                // case '2': {
                    // token = getNextToken(lexer);
                    // q2(&c, atoi(token->value));
                // }
                // case '4': {
                //     token = getNextToken(lexer);
                //     q4(&c, token->value);
                // }
            }
        }
    }

    free(args);

    return 0;
}
