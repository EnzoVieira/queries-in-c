#ifndef RIDE_REPOSITORY_H
#define RIDE_REPOSITORY_H

#include "./api.h"

typedef struct ride Ride;

Ride *createRide(char* line);
void addRide(char* line);
void createRidesHashTable(const char *path);
HashTable *rideHashTableSingleton();
// Always returns a copy when ride exists
Ride *findRideById(const char *id);

// ============================
//           GETTERS
// ============================

char *getRDate(const Ride *ride);
char *getRDriverId(const Ride *ride);
char *getRUsername(const Ride *ride);
char *getRCity(const Ride *ride);
double getRDistance(const Ride *ride);
double getRScoreUser(const Ride *ride);
double getRScoreDriver(const Ride *ride);
double getRTip(const Ride *ride);
void destructRideCopy(void *r);

#endif
