#include <stdio.h>
#include <string.h>

#include "includes/api.h"

#include "includes/userRepository.h"
#include "includes/driverRepository.h"
#include "includes/rideRepository.h"

#include "includes/query1.h"
#include "includes/query4.h"
#include "includes/query3.h"

#include "includes/token.h"
#include "includes/lexer.h"
#include "includes/reader.h"
#include "includes/writer.h"
#include "includes/parser.h"

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

    parser(lexer, &c);

    free(args);

    return 0;
}
