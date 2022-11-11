#ifndef QUERY_3_H
#define QUERY_3_H

#include "userRepository.h"
#include "driverRepository.h"
#include "rideRepository.h"
#include "catalogEntity.h"
#include "query1.h"


typedef struct querie3Aux q3Aux;

void totalDistance(gpointer key, gpointer value, gpointer userData);
double getTotalDistance(Catalog *c, char* id);
char* compareDates(char* date1, char* date2);
void recentTrip(gpointer key, gpointer value, gpointer userData);
char* getMostRecentTrip(Catalog* c, char* id);
int compareFunc(gconstpointer a, gconstpointer b);
void copyToHash(gpointer key, gpointer value, gpointer userData);
void fillHash(Catalog* c, char* id);

#endif