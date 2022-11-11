#ifndef QUERY_2_H
#define QUERY_2_H

#include "catalogEntity.h"
#include "userRepository.h"
#include "driverRepository.h"

typedef struct catalog Catalog;


void destroyQ2Aux(void *u);
void destroyKey(void *u);
int mostRecenteRide (char* a, char* b);
int compareMedia(gconstpointer a, gconstpointer b, gpointer user_data);
void interactMedia(gpointer key, gpointer value, gpointer data);
int q2(Catalog *catalog, int N);


#endif