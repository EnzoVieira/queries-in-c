#ifndef TEST_Q3_H
#define TEST_Q3_H

// TODO: O include do databse só é necessário pois lá dentro está
// o typedef do Catalog, não sei se é realmente necessário incluir a database.h
// somente por conta disso ou eu deveria criar um typedef Catalog aqui mesmo.
#include "../../includes/database.h"
#include "../../includes/token.h"

void testQ3(Token *token, Catalog *c, char *filename);

#endif
