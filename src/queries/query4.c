#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/api.h"
#include "../../includes/query4.h"

#include "../../includes/driverRepository.h"
#include "../../includes/rideRepository.h"
#include "../../includes/utilsStatistics.h"

typedef struct querie4Aux {
    char *city;
    double priceAcc;
    double totalRides;
}Q4Aux;

void mediaPriceCalculator(Pointer key, Pointer value, Pointer data){
    Q4Aux *cityInfo = (Q4Aux*)data; 
    Ride *ride = (Ride*)value;

    if (!strcmp(getRCity(ride),cityInfo->city)){
        char *carClass = getDCarClass(findDriverByID(getRDriverId(ride)));
        cityInfo->priceAcc += ridePriceCalculator(carClass,getRDistance(ride));
        cityInfo->totalRides ++;
        free(carClass);
    }
}


char *q4(char *city) {
    HashTable *rideHashTable = rideHashTableSingleton();
    Q4Aux cityInfo = {city,0,0};
    
    hashForeach (rideHashTable,mediaPriceCalculator,&cityInfo);

    char *output = calloc(10, sizeof(char));
    sprintf(output, "%.3f\n", cityInfo.priceAcc/cityInfo.totalRides);

    return output;
}