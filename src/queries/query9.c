#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/query9.h"
#include "../../includes/api.h"

#include "../../includes/rideRepository.h"
#include "../../includes/dates.h"

typedef struct query9Aux {
    char* rideID;
    char* date;
    int distance;
    char* city;
    double tip;
} Q9Aux;

typedef struct query9Temp {
    char* date1;
    char* date2;
    HashTable* hashTable;
} Q9Temp;

void destroyQ9Aux (void *q9Aux){

    Q9Aux *q9 = (Q9Aux*)q9Aux;

    if(q9){
        if(q9->city)
            free(q9->city);
        if(q9->date)
            free(q9->date);
        free(q9);
    }
}

int compareFunc3(Pointer a, Pointer b) {
    Q9Aux* r1 = (Q9Aux*)a;
    Q9Aux* r2 = (Q9Aux*)b;

    int datesDiference = compareDates(r1->date, r2->date);
    int distanceDiference = r1->distance - r2->distance;

    if (!distanceDiference) {             
        if (!datesDiference)  
            return -strcmp(r1->rideID, r2->rideID);      //compara por ID da viagem
        else return datesDiference;   //compara por data da viagem
    } else return -distanceDiference;          //compara por distância
}

void copyToHash3(Pointer key, Pointer value, Pointer userData) {
    char* rideID = (char*)key;
    Ride* r = (Ride*)value;
    Q9Temp* temp = (Q9Temp*)userData;

    char *date =  getRDate(r);

    if (getRTip(r) > 0.0 && isDateBetween(temp->date1, date, temp->date2)) {
        Q9Aux* result = (Q9Aux*)malloc(sizeof(Q9Aux));
        result->rideID = strdup(rideID);
        result->date = strdup(date);
        result->distance = getRDistance(r);
        result->city = getRCity(r);
        result->tip = getRTip(r);
        addToTable(temp->hashTable, result->rideID, result);
    }
        free(date);
}

char* q9(char* date1, char* date2) {
    HashTable* rides = rideHashTableSingleton();
    HashTable* resultHash = createHashTable(&destroyQ9Aux);

    Q9Temp* temp = (Q9Temp*)malloc(sizeof(Q9Temp));
    temp->date1 = strdup(date1);
    temp->date2 = strdup(date2);
    temp->hashTable = resultHash;
    hashForeach(rides, copyToHash3, temp);

    List* copy = copyFromHash(resultHash);
    copy = sortList(copy, compareFunc3);

    size_t lineLength = 20 + 50 + 5;
    char* stringGrande = calloc(lineLength * listLength(copy), sizeof(char));
    List *tmp = copy;
    int i = 0, j = listLength(copy);
    while (i < j) {
        Q9Aux* q9 = getListData(copy);
        copy = listNext(copy);
        char *stringAux = calloc(lineLength, sizeof(char));
        sprintf(stringAux, "%s;%s;%d;%s;%.3f\n", q9->rideID, q9->date, q9->distance, q9->city, q9->tip);
        strcat(stringGrande, stringAux);
        free(stringAux);
        i++;
    }
    copy = tmp;
    freeList(copy);
    destroyHash(temp->hashTable);
    free(temp->date1);
    free(temp->date2);
    free(temp);
    return stringGrande;
}