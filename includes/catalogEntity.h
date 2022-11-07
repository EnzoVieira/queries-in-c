#ifndef CATALOG_ENTITY
#define CATALOG_ENTITY

#include <stdio.h>
#include <glib.h>

#include "rideEntity.h"

typedef struct catalogo Catalogo;
void ridesCounter(gpointer key, gpointer value, gpointer userData);
int numberOfTrips(Catalogo* c, char* id);
void rating(gpointer key, gpointer value, gpointer userData);
double totalRating(Catalogo* c, char* id);
void travelCost(gpointer key, gpointer value, gpointer userData);
double totalCost(Catalogo* c, char* id);
Ride* findRideByID(Catalogo* c, char* id);
void travelCost(gpointer key, gpointer value, gpointer userData);
double totalCost(Catalogo* c, char* id);
#endif