#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/query6.h"

#include "../../includes/rideRepository.h"
#include "../../includes/dates.h"           // chama a função isDateBetween
#include "../../includes/api.h"             // chama o tipo Pointer, hashForeach

typedef struct query6Aux {
    char* city;
    double totalDistance;
    int totalTrips;
    char* date1;
    char* date2;
} Q6Aux;

void destroyQ6Aux(void *q6Aux){
  Q6Aux *q6 = (Q6Aux*)q6Aux;
  
  if (q6){
    if(q6->city)
        free(q6->city);
    if(q6->date1)
        free(q6->date1);
    if(q6->date2)
        free(q6->date2);
    free(q6);
  }
}

void getTotalDistanceByCity(Pointer key, Pointer value, Pointer userData) {
    Ride* r = value;
    Q6Aux* q6 = (Q6Aux*) userData;
    char *city = getRCity(r);
    char *date = getRDate(r);
    
    if (strcmp(q6->city, city) == 0 && isDateBetween(q6->date1, date, q6->date2)) {
        q6->totalDistance += getRDistance(r);
        q6->totalTrips++;
    }
    free(city);
    free(date);
}

char* q6(char* city, char* date1, char* date2) {
    Q6Aux *q6 = (Q6Aux*)malloc(sizeof(Q6Aux));
    q6->city = strdup(city);
    q6->date1 = strdup(date1);
    q6->date2 = strdup(date2);
    q6->totalDistance = 0;
    q6->totalTrips = 0;
    
    HashTable* rides = rideHashTableSingleton();
    hashForeach(rides, getTotalDistanceByCity, q6);
    char* output = calloc(10, sizeof(char));
    sprintf(output, "%.3f\n", (q6->totalDistance / q6->totalTrips));

    destroyQ6Aux(q6);
    
    return output;
}