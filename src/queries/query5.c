#include <stdio.h>
#include <stdlib.h>
#include "../../includes/query5.h"

#include "../../includes/userRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/rideRepository.h"
#include "../../includes/dates.h"           // chama a função isDateBetween
#include "../../includes/utilsStatistics.h" // chama a função ridePriceCalculator
#include "../../includes/api.h"             // chama o tipo Pointer

typedef struct query5Aux {
    double totalValue;
    int totalTrips;
    char* date1;
    char* date2;
} Q5Aux;

void currentTrip(Pointer key, Pointer value, Pointer userData) {
    Ride* r = value;
    Q5Aux* q5 = (Q5Aux*) userData;

    if (isDateBetween(q5->date1, getRDate(r), q5->date2)) {
        char* carClass = getDCarClass(findDriverByID(getRDriverId(r)));
        q5->totalValue += ridePriceCalculator(carClass, getRDistance(r));
        q5->totalTrips++;
        
        free(carClass);
    }
}

char* q5(char* date1, char* date2) {
    Q5Aux q5 = {0.0, 0, date1, date2};
    HashTable* rides = rideHashTableSingleton();
    hashForeach(rides, currentTrip, &q5);
    char* output = calloc(10, sizeof(char));
    sprintf(output, "%.3f\n", (q5.totalValue / q5.totalTrips));
    return output;
}




