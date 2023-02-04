#ifndef DRIVER_REPOSITORY_H
#define DRIVER_REPOSITORY_H

#include "./api.h"

typedef struct driver Driver;

Driver *createDriver(char *line);
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

char *getDNameNew(char *id);
char *getDBirthDateNew(char *id);
char getDGenderNew(char *id);
char *getDCarClassNew(char *id);
char *getDCityNew(char *id);
char *getDAccountCreationNew(char *id);
int getDAccountStatusNew(char *id);
char *getDLastRideNew(char *id);

#endif