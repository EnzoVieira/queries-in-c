#ifndef RIDES_REPOSITORY_H
#define RIDES_REPOSITORY_H

#include <stdio.h>
#include <string.h>

#include "api.h"

#include "userRepository.h"
#include "driverRepository.h"
#include "rideEntity.h"

typedef struct catalog Catalog;

typedef struct {
  char *driverId;
  char *driverCarClass;
  Driver *driversTable;

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

void driverAccumulator(void *_, void *currentValue, void *acc);
TotalDriverAcc *totalDriver(Catalog *catalog, Driver *driverCopy);
void userAccumulator(void *_, void *currentValue, void *acc);
TotalUserAcc *totalUser(Catalog *catalog, User *userCopy);
void rideAccumulator(void *_, void *currentValue, void *acc);
TotalRideAcc *totalRide(Catalog *catalog, char *city, char *dateA, char *dateB);

#endif
