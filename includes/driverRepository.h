#ifndef DRIVER_REPOSITORY_H
#define DRIVER_REPOSITORY_H

// #include <stdio.h>
// #include <string.h>

#include "api.h"
// #include "date.h"

typedef struct driver Driver;

char* getDID(Driver *d);
char* getDName(Driver *d);
char* getDBirthDate(Driver *d);
char getDGender(Driver *d);
char* getDCarClass(Driver *d);
char* getDLicensePlate(Driver *d);
char* getDCity(Driver *d);
char* getDAccountCreation(Driver *d);
int getDAccountStatus(Driver *d);

Driver* findDriverByID(HashTable *drivers, char *id);
int getDriverAge(Driver *driver);

#endif
