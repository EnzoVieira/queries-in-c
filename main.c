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

int main() {
    Catalog c;
    c.users = createUsersHashData();
    c.drivers = createDriversHashData();
    c.rides = createRidesHashData();

    char *args = readFile("exemplos_de_queries2/tests_2/input.txt");

    Lexer *lexer = createLexer(args);

    parser(lexer, &c);

    free(args);

    return 0;
}
