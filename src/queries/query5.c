#include <stdio.h>
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
} q5Aux;

void currentTrip(Pointer key, Pointer value, Pointer userData) {
    Ride* r = value;
    q5Aux* q5 = (q5Aux*) userData;
    Driver* driver = findDriverByID(getRDriverId(r)); 

    q5->totalValue += ridePriceCalculator(getDCarClass(driver), getRDistance(r));
    q5->totalTrips++;
}

double q5(char* date1, char* date2) {
    HashTable* rides = rideHashTableSingleton();
    
} 




