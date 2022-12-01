#ifndef QUERY_5_H
#define QUERY_5_H

#include "userRepository.h"
#include "driverRepository.h"
#include "rideRepository.h"

typedef struct catalog Catalog;

char *q5(Catalog *c, char *city, char *dateA, char *dateB);

#endif