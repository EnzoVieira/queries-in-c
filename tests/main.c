#include <stdio.h>
#include <string.h>
#include <time.h>

#include "includes/parserTest.h"

struct catalog {
    void *users;
    void *drivers;
    void *rides;
};

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Argumentos insuficientes\n");
        exit(1);
    }

    Catalog c;
    c.users = createUsersHashData(argv[1]);
    c.drivers = createDriversHashData(argv[1]);
    c.rides = createRidesHashData(argv[1]);

    char *args = readFile(argv[2]);
    Lexer *lexer = createLexer(args);
    parserTest(lexer, &c);

    free(args);

    return 0;
}