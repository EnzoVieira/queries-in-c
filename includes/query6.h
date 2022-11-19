#ifndef QUERY_6_H
#define QUERY_6_H

#include "userRepository.h"
#include "driverRepository.h"
#include "rideRepository.h"

typedef struct catalog Catalog;

char *q6(Catalog *c, char *city, char *dateA, char *dateB);

#endif