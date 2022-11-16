#include <stdio.h>
#include <string.h>
#include <time.h>

#define UNIT_TESTS 1

#include "../includes/parser.h"
#include "includes/parserTest.h"

struct catalog {
    void *users;
    void *drivers;
    void *rides;
};

int main(int argc, char *argv[]) {
    clock_t hashTableTime, totalProgramTime;
    double calcTime;

    totalProgramTime = clock();

    if(argc < 3) {
        printf("Argumentos insuficientes\n");
        exit(1);
    }

    printf("🌱 A criar Hash Tables...\n");

    hashTableTime = clock();
    Catalog c;
    c.users = createUsersHashData(argv[1]);
    c.drivers = createDriversHashData(argv[1]);
    c.rides = createRidesHashData(argv[1]);
    hashTableTime = clock() - hashTableTime;

    calcTime = ((double)hashTableTime)/CLOCKS_PER_SEC;
    printf("Hash Tables criadas em %.3fs ✅\n", calcTime);

    char *args = readFile(argv[2]);
    Lexer *lexer = createLexer(args);

    if (UNIT_TESTS) {
        parserTest(lexer, &c);
    } else {
        printf("A executar o programa... 💣\n");

        parser(lexer, &c);
        totalProgramTime = clock() - totalProgramTime;

        calcTime = ((double)totalProgramTime)/CLOCKS_PER_SEC;
        printf("\033[32mPrograma executado em %.3fs \n\033[0m", calcTime);        
    }

    free(args);

    return 0;
}