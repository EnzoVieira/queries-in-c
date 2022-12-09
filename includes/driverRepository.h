#ifndef DRIVER_REPOSITORY_H
#define DRIVER_REPOSITORY_H

#include "./api.h"

typedef struct driver Driver;

// ============================
//           GETTERS
// ============================

Driver *getDriverCopy(Driver* d);
char *getDID(Driver *d);
char *getDName(Driver *d);
char *getDBirthDate(Driver *d);
char getDGender(Driver *d);
char *getDCarClass(Driver *d);
char *getDLicensePlate(Driver *d);
char *getDCity(Driver *d);
char *getDAccountCreation(Driver *d);
int getDAccountStatus(Driver *d);
HashTable *driverHashTableSingleton();
void addDriver(Driver* newDriver);
Driver *findDriverByID(const char *id);

#endif