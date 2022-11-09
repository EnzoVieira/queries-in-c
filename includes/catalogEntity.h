#ifndef CATALOG_ENTITY_H
#define CATALOG_ENTITY_H

// #include <stdio.h>
#include <glib.h>

#include "driverRepository.h"
#include "userRepository.h"
#include "rideEntity.h"

// // Funções Destroy
// void destroySumData(void *u);
// void destroyKey(void *u);

// // Querry 1
typedef struct catalog Catalog;
typedef struct date Date;

typedef struct querie1Aux q1Aux;

void ridesCounter(gpointer key, gpointer value, gpointer userData);
int numberOfTrips(Catalog *c, char *id);
void rating(gpointer key, gpointer value, gpointer userData);
double totalRating(Catalog *c, char *id);
void travelCost(gpointer key, gpointer value, gpointer userData);
double totalCost(Catalog *c, char *id);
Ride *findRideByID(Catalog *c, char *id);
void travelCost(gpointer key, gpointer value, gpointer userData);
double totalCost(Catalog *c, char *id);
Date *dateConvert(char *birthdate);
int dateDifference(Date *d);
void findAge(gpointer key, gpointer value, gpointer userData);
int getAge(Catalog *c, char *id);
void q1(Catalog *c, char *id);

// // Querry 2
// int compareMedia(gconstpointer a, gconstpointer b);
// void interactMedia(gpointer key, gpointer value, gpointer data);
// int q2(Catalogo *catalog, int N);

// // Querry 3

// void interactPriceMedia(gpointer key, gpointer value, gpointer data);
// void totalPriceCalculator(gpointer key, gpointer value, gpointer data);
// int q4(Catalogo *catalog, char *city);

#endif