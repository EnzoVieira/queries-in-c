#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/query7.h"
#include "../../includes/api.h"
#include "../../includes/writer.h"

#include "../../includes/rideRepository.h"
#include "../../includes/driverRepository.h"


typedef struct query7Aux {
    char* driverID;
    double totalScore;
    int totalTrips;
} Q7Aux;

typedef struct query7Temp {
    char* city;
    HashTable* hashTable;
} Q7Temp;

void destroyQ7Aux(void *q7Aux){
   
    Q7Aux *q7 = (Q7Aux*)q7Aux;
    
    if(q7){
        free(q7);
    }
}

int compareFunc(Pointer a, Pointer b) {
    Q7Aux* d1 = (Q7Aux*)a;
    Q7Aux* d2 = (Q7Aux*)b;
    double average_d1 = (d1->totalScore / d1->totalTrips);
    double average_d2 = (d2->totalScore / d2->totalTrips);

    if (average_d1 == average_d2) 
        return -(strcmp(d1->driverID, d2->driverID));
    else return average_d1 < average_d2;
}

void copyToHash(Pointer key, Pointer value, Pointer userData) {
    Ride* r = (Ride*)value;
    Q7Temp* copy = (Q7Temp*)userData;

    char *id = getRDriverId(r);
    char *city = getRCity(r);
    Q7Aux* driver = findById(copy->hashTable, id);

    if (strcmp(city, copy->city) == 0) {
        if (driver) {
            driver->totalScore += getRScoreDriver(r);
            driver->totalTrips++;
        } else {
            driver = (Q7Aux*)malloc(sizeof(Q7Aux));
            driver->driverID = id;
            driver->totalScore = getRScoreDriver(r);
            driver->totalTrips = 1;
            addToTable(copy->hashTable, driver->driverID, driver);
        }
    }
    free(city);
}
    

/*
Top N condutores numa determinada cidade, representada por <city> (no ficheiro rides.csv), ordenado pela avaliação média do condutor. 
Em caso de empate, o resultado deverá ser ordenado através do id do condutor, de forma decrescente. 
A avaliação média de um condutor numa cidade é referente às suas viagens nessa cidade, e não na cidade que está no seu perfil (ou seja, o mesmo
condutor poderá ter médias diferentes dependendo da cidade)
*/

void q7(int N, char* city) {
    HashTable* rides = rideHashTableSingleton();

    Q7Temp* temp = (Q7Temp*)malloc(sizeof(Q7Temp));
    temp->city = strdup(city);
    temp->hashTable = createHashTable2(&destroyQ7Aux);
    hashForeach(rides, copyToHash, temp);

    List* copy = copyFromHash(temp->hashTable);
    copy = sortList(copy, compareFunc);

    size_t lineLength = 20 + 50 + 5;
    
    int i = 0, j = N;
    while (i < j) {
        Q7Aux* q7 = findInListByIndex(copy, i);
        Driver* driver = findDriverByID(q7->driverID);

        if (getDAccountStatus(driver)) {

            char *stringAux = calloc(lineLength, sizeof(char));
            sprintf(stringAux, "%s;%s;%.3f\n", q7->driverID, getDName(driver), (q7->totalScore / q7->totalTrips));

            writeResultFile(stringAux);

            free(stringAux);
            i++;
        } else {
            i++;
            j++;
        }

        q7 = NULL;
        destructDriverCopy(driver);
    }

    advanceResultIndex();

    freeList(copy);
    destroyHash(temp->hashTable);
    free(temp->city);
    free(temp);
}
