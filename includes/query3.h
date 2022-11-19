#ifndef QUERY_3_H
#define QUERY_3_H

#include "userRepository.h"
#include "driverRepository.h"
#include "rideRepository.h"
#include "query1.h"


typedef struct querie3Aux q3Aux;

void totalDistance(gpointer key, gpointer value, gpointer userData);
double getTotalDistance(Catalog *c, char* id);
char* compareDates(char* date1, char* date2);
void recentTrip(gpointer key, gpointer value, gpointer userData);
char* getMostRecentTrip(Catalog* c, char* id);
void copyToHash(gpointer key, gpointer value, gpointer userData);
int compareRecentTrip(char* a, char* b);
int compareFunc(gconstpointer a, gconstpointer b);
char *q3(Catalog* c, int N);

#endif