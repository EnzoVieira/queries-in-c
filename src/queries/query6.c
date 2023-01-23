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

void getTotalDistanceByCity(Pointer key, Pointer value, Pointer userData) {
    Ride* r = value;
    Q6Aux* q6 = (Q6Aux*) userData;
    
    if (strcmp(q6->city, getRCity(r)) == 0 && isDateBetween(q6->date1, getRDate(r), q6->date2)) {
        q6->totalDistance += getRDistance(r);
        q6->totalTrips++;
    }
}

char* q6(char* city, char* date1, char* date2) {
    Q6Aux q6 = {city, 0.0, 0, date1, date2};
    HashTable* rides = rideHashTableSingleton();
    hashForeach(rides, getTotalDistanceByCity, &q6);
    char* output = calloc(10, sizeof(char));
    sprintf(output, "%.3f\n", (q6.totalDistance / q6.totalTrips));
    return output;
}