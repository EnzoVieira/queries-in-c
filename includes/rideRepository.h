#ifndef RIDES_REPOSITORY_H
#define RIDES_REPOSITORY_H

#include <stdio.h>
#include <string.h>

#include "api.h"
#include "rideEntity.h"

void *createRidesHashData();
Ride* cloneRide(Ride *r);
//Ride* findRideByID(GHashTable* rides, char* id);

#endif
