#ifndef RIDE_REPOSITORY_H
#define RIDE_REPOSITORY_H

#include "./api.h"

typedef struct ride Ride;

Ride *createRide(const char *id, const char* username, const char *city);
HashTable *rideHashTableSingleton();
void addRide(Ride *newRide);
// Always returns a copy when ride exists
Ride *findRideById(const char *id);

// ============================
//           GETTERS
// ============================

char *getRID(const Ride *ride);
char *getRUsername(const Ride *ride);
char *getRCity(const Ride *ride);

#endif
