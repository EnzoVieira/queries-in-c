#ifndef DRIVER_REPOSITORY_H
#define DRIVER_REPOSITORY_H

#include "./api.h"

typedef struct driver Driver;

Driver *createDriver(const char *line);
void addDriver(char *line);
void createDriversHashTable(const char *path);
HashTable *driverHashTableSingleton();
Driver *findDriverByID(const char *id);
void addDriverLastRide(const char *id, const char *date);

// ============================
//           GETTERS
// ============================

char *getDName(Driver *d);
char *getDBirthDate(Driver *d);
char getDGender(Driver *d);
char *getDCarClass(Driver *d);
char *getDCity(Driver *d);
char *getDAccountCreation(Driver *d);
int getDAccountStatus(Driver *d);
char *getDLastRide(Driver *d);
void destructDriverCopy(void *d);


#endif