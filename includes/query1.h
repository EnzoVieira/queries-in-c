#ifndef QUERY_1_H
#define QUERY_1_H

#include "rideRepository.h"
#include "userRepository.h"
#include "driverRepository.h"

typedef struct catalog Catalog;
typedef struct date Date;

void ridesCounter(gpointer key, gpointer value, gpointer userData);
int numberOfTrips(Catalog *c, char *id);
void rating(gpointer key, gpointer value, gpointer userData);
double totalRating(Catalog *c, char *id);
void travelCost(gpointer key, gpointer value, gpointer userData);
double totalCost(Catalog *c, char *id);
Date *dateConvert(char *birthDate);
int dateDifference(Date *d);
int getAge(Catalog *c, char *id);
char *q1(Catalog *c, char *id);

#endif
