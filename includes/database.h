#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"

typedef struct user User;
typedef struct driver Driver;
typedef struct ride Ride;
typedef struct catalog Catalog;

void *createUsersHashData(const char *path);
void *createDriversHashData(const char *path);
void *createRidesHashData(const char *path);
Catalog *seedDatabase(const char* path);

#endif