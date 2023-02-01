#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/query8.h"

#include "../../includes/rideRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/userRepository.h"
#include "../../includes/api.h"
#include "../../includes/dates.h"

typedef struct query8Aux {
    char* rideID;
    char* driverID;
    char* driverName;
    char* userID;
    char* userName;
} Q8Aux;

typedef struct query8Temp {
    char gender;
    int accountYears;
    HashTable* hashTable;
} Q8Temp;

int compareFunc2(Pointer a, Pointer b) {
    Q8Aux* d1 = (Q8Aux*)a;
    Q8Aux* d2 = (Q8Aux*)b;

    Driver* driver1 = findDriverByID(d1->driverID);
    Driver* driver2 = findDriverByID(d2->driverID);
    User* user1 = findUserByUsername(d1->userID);
    User* user2 = findUserByUsername(d2->userID);

    if (strcmp(getDAccountCreation(driver1), getDAccountCreation(driver2)) == 0) {
        if (strcmp(getUAccountCreation(user1), getUAccountCreation(user2)) == 0) 
            return strcmp(d1->rideID, d2->rideID); //fazer comparação com os ID's das viagens.
        else return -compareDates(getUAccountCreation(user1), getUAccountCreation(user2)); //fazer comparação das datas de criação da conta dos Users 
    } else return -compareDates(getDAccountCreation(driver1), getDAccountCreation(driver2)); //fazer comparação das datas de criação da conta dos Drivers
}

void copyToHash2(Pointer key, Pointer value, Pointer userData) {
    char* rideID = (char*)key;
    Ride* r = (Ride*)value;
    Q8Temp* copy = (Q8Temp*)userData;

    char gender = copy->gender;
    int accountYears = copy->accountYears;

    Driver* d = findDriverByID(getRDriverId(r));
    User* u = findUserByUsername(getRUsername(r));

    Q8Aux* temp = (Q8Aux*)malloc(sizeof(Q8Aux));

    int driverAccountCreation = dateDifference(dateConvert(getDAccountCreation(d)));
    int userAccountCreation = dateDifference(dateConvert(getUAccountCreation(u)));

    int validGender = (getDGender(d) == gender && getUGender(u) == gender);
    int validAccountYears = (driverAccountCreation >= accountYears && userAccountCreation >= accountYears);

    if (validGender && validAccountYears) {
        temp->rideID = strdup(rideID);
        temp->driverID = getRDriverId(r);
        temp->driverName = getDName(d);
        temp->userID = getRUsername(r);
        temp->userName = getUName(u);
        addToTable(copy->hashTable, strdup(rideID), temp);
    }
}

/* 
    O output deverá ser ordenado de forma que as contas mais antigas apareçam primeiro.
    Ordenar por conta mais antiga de condutor e, se necessário, pela conta do utilizador.
    Se persistirem empates, ordenar por id da viagem (ordem descendente).
*/


char* q8(char gender, int years) {
    HashTable* rides = rideHashTableSingleton();
    HashTable* resultHash = createHashTable();

    Q8Temp* temp = (Q8Temp*)malloc(sizeof(Q8Temp));
    temp->gender = gender;
    temp->accountYears = years;
    temp->hashTable = resultHash;
    hashForeach(rides, copyToHash2, temp);

    List* copy = copyFromHash(resultHash);
    copy = sortList(copy, compareFunc2);

    size_t lineLength = 20 + 50 + 5;
    char* stringGrande = calloc(lineLength * listLength(copy), sizeof(char));
    
    int i = 0, j = listLength(copy);
    while (i < j) {
        Q8Aux* q8 = findInListByIndex(copy, i);

        Driver* driver = findDriverByID(q8->driverID);
        User* user = findUserByUsername(q8->userID);

        if (getDAccountStatus(driver) && getUAccountStatus(user)) {
            printf("%s,%s,%s,%s,%s,%s\n", q8->driverID, q8->driverName, q8->userID, q8->userName, getDAccountCreation(driver), q8->rideID);
            char *stringAux = calloc(lineLength, sizeof(char));
            sprintf(stringAux, "%s;%s;%s;%s\n", q8->driverID, q8->driverName, q8->userID, q8->userName);
            strcat(stringGrande, stringAux);
            free(stringAux);
        }
        i++;
    }
    return stringGrande;
}