#ifndef CATALOG_ENTITY
#define CATALOG_ENTITY

#include <stdio.h>
#include <glib.h>

#include "rideEntity.h"

//Funções Destroy
void destroySumData(void *u);
void destroyKey(void *u);

//Querry 1
typedef struct catalogo Catalogo;
typedef struct date Date;
void ridesCounter(gpointer key, gpointer value, gpointer userData);
int numberOfTrips(Catalogo* c, char* id);
void rating(gpointer key, gpointer value, gpointer userData);
double totalRating(Catalogo* c, char* id);
void travelCost(gpointer key, gpointer value, gpointer userData);
double totalCost(Catalogo* c, char* id);
Ride* findRideByID(Catalogo* c, char* id);
void travelCost(gpointer key, gpointer value, gpointer userData);
double totalCost(Catalogo* c, char* id);
Date* dateConvert(char* birthdate);
int dateDifference(Date* d);
void findAge(gpointer key, gpointer value, gpointer userData);
int getAge(Catalogo* c, char* id);

//Querry 2
int compareMedia (gconstpointer a,gconstpointer b);
void interactMedia(gpointer key,gpointer value, gpointer data);
int q2(Catalogo* catalog,int N);

//Querry 3

void interactPriceMedia(gpointer key,gpointer value, gpointer data);
void totalPriceCalculator(gpointer key,gpointer value, gpointer data);
int q4 (Catalogo *catalog, char* city);



#endif