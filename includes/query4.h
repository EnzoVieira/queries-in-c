#ifndef QUERY_4_H
#define QUERY_4_H

#include "rideRepository.h"
#include "userRepository.h"
#include "driverRepository.h"

typedef struct catalog Catalog;

void destroyQ4Aux(void *u);
//void destroyKey(void *u);
void interactPriceMedia(gpointer key, gpointer value, gpointer data);
void totalPriceCalculator(gpointer key, gpointer value, gpointer data);
char *q4(Catalog *catalog, char *city);

#endif