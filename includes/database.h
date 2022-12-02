#ifndef DATABASE_H
#define DATABASE_H

typedef struct catalog Catalog;

void *createUsersHashData(const char *path);
void *createDriversHashData(const char *path);
void *createRidesHashData(const char *path);
Catalog *seedDatabase(const char* path);

#endif