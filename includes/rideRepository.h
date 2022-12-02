#ifndef RIDES_REPOSITORY_H
#define RIDES_REPOSITORY_H

// #include <stdio.h>
// #include <string.h>

// #include "api.h"

#include "userRepository.h"
#include "driverRepository.h"

typedef struct catalog Catalog;

typedef struct {
  char *driverId;
  char *driverCarClass;
  HashTable *driversTable;

  double totalCost;
  int totalTrips;
  double accRating;
  double rating;
} TotalDriverAcc;

typedef struct {
  char *username;
  Catalog *tables;

  double totalCost;
  int totalTrips;
  double accRating;
  double rating;
} TotalUserAcc;

typedef struct {
  char *city;
  char *dateA;
  char *dateB;

  double distanceAcc;
  double averageDistance;
  int totalTrips;
} TotalRideAcc;

typedef struct ride Ride;

char* getRID(Ride *r);
char* getRDate(Ride *r);
char* getRDriver(Ride *r);
char* getRUser(Ride *r);
char* getRCity(Ride *r);
double getRDistance(Ride *r);
double getRScoreUser(Ride *r);
double getRScoreDriver(Ride *r);
double getRTip(Ride *r);
char* getRComment(Ride *r);

void driverAccumulator(void *_, void *currentValue, void *acc);
TotalDriverAcc *totalDriver(Catalog *catalog, Driver *driverCopy);
void userAccumulator(void *_, void *currentValue, void *acc);
TotalUserAcc *totalUser(Catalog *catalog, User *userCopy);
void rideAccumulator(void *_, void *currentValue, void *acc);
TotalRideAcc *totalRide(Catalog *catalog, char *city, char *dateA, char *dateB);

#endif
