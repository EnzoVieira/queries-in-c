#ifndef DRIVER_REPOSITORY_H
#define DRIVER_REPOSITORY_H

#include "./api.h"

typedef struct driver Driver;

Driver *createDriver(const char *line);
void addDriver(char *line);
void createDriversHashTable(const char *path);
HashTable *driverHashTableSingleton();
Driver *findDriverByID(const char *id);

// ============================
//           GETTERS
// ============================

char *getDName(Driver *d);
char *getDBirthDate(Driver *d);
char getDGender(Driver *d);
char *getDCarClass(Driver *d);
char *getDLicensePlate(Driver *d);
char *getDCity(Driver *d);
char *getDAccountCreation(Driver *d);
int getDAccountStatus(Driver *d);
void destructDriverCopy(void *d);

#endif