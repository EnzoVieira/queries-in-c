#ifndef TEST_Q6_H
#define TEST_Q6_H

// TODO: O include do databse só é necessário pois lá dentro está
// o typedef do Catalog, não sei se é realmente necessário incluir a database.h
// somente por conta disso ou eu deveria criar um typedef Catalog aqui mesmo.
#include "../../includes/database.h"
#include "../../includes/token.h"

void testQ6(Token *(tokens[3]), Catalog *c, char *filename);

#endif
