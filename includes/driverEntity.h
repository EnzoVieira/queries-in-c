#ifndef DRIVER_ENTITY
#define DRIVER_ENTITY

#include <stdbool.h>

typedef struct driver Driver;
char* getDID(Driver *d);
char* getDName(Driver *d);
char* getDBirthDate(Driver *d);
char getDGender(Driver *d);
char* getDCarClass(Driver *d);
char* getDLicensePlate(Driver *d);
char* getDCity(Driver *d);
char* getDAccountCreation(Driver *d);
char* getDAccountStatus(Driver *d);

#endif