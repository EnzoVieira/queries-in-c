#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/query9.h"

#include "../../includes/rideRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/userRepository.h"
#include "../../includes/dates.h"

typedef struct query9Aux {
    char* rideID;
    char* date;
    double distance;
    char* city;
    double tip;
} Q9Aux;

typedef struct query9Temp {
    char* date1;
    char* date2;
    HashTable* hashTable;
} Q9Temp;

int compareFunc3(Pointer a, Pointer b) {
    Q9Aux* r1 = (Q9Aux*)a;
    Q9Aux* r2 = (Q9Aux*)b;

    if (r1->distance == r2->distance) {             
        if (compareDates(r1->date, r2->date) == 0)  
            return strcmp(r1->rideID, r2->rideID);      //compara por ID da viagem
        else return compareDates(r1->date, r2->date);   //compara por data da viagem
    } else return r1->distance > r2->distance;          //compara por distância
}

void copyToHash3(Pointer key, Pointer value, Pointer userData) {
    char* rideID = (char*)key;
    Ride* r = (Ride*)value;
    Q9Temp* temp = (Q9Temp*)userData;

    Q9Aux* result = (Q9Aux*)malloc(sizeof(Q9Aux));

    if (getRTip(r) > 0.0 && isDateBetween(temp->date1, getRDate(r), temp->date2)) {
        result->rideID = rideID;
        result->date = getRDate(r);
        result->distance = getRDistance(r);
        result->city = getRCity(r);
        result->tip = getRTip(r);
        addToTable(temp->hashTable, strdup(rideID), result);
    }
}

char* q9(char* date1, char* date2) {
    HashTable* rides = rideHashTableSingleton();
    HashTable* resultHash = createHashTable();

    Q9Temp* temp = (Q9Temp*)malloc(sizeof(Q9Temp));
    temp->date1 = date1;
    temp->date2 = date2;
    temp->hashTable = resultHash;
    hashForeach(rides, copyToHash3, temp);

    List* copy = copyFromHash(resultHash);
    copy = sortList(copy, compareFunc3);

    size_t lineLength = 20 + 50 + 5;
    char* stringGrande = calloc(lineLength * listLength(copy), sizeof(char));
    
    int i = 0, j = listLength(copy);
    while (i < j) {
        Q9Aux* q9 = findInListByIndex(copy, i);

        printf("%s,%s,%f,%s,%f\n", q9->rideID, q9->date, q9->distance, q9->city, q9->tip);
        char *stringAux = calloc(lineLength, sizeof(char));
        sprintf(stringAux, "%s;%s;%f;%s;%f\n", q9->rideID, q9->date, q9->distance, q9->city, q9->tip);
        strcat(stringGrande, stringAux);
        free(stringAux);
        i++;
    }
    return stringGrande;
}