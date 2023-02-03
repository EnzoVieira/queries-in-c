#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/query8.h"
#include "../../includes/api.h"

#include "../../includes/rideRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/userRepository.h"
#include "../../includes/dates.h"
#include "../../includes/writer.h"

#define MAX_LINE_LENGTH 200

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

void destroyQ8Aux (void *q8Aux){
    
    Q8Aux *q8 = (Q8Aux*)q8Aux;

    if(q8){
        if(q8->driverID)
            free(q8->driverID);
        if(q8->driverName)
            free(q8->driverName);
        if(q8->userID)
            free(q8->userID);
        if(q8->userName)
            free(q8->userName);
        free (q8);
    }
}

int compareFunc2(Pointer a, Pointer b) {
    Q8Aux* d1 = (Q8Aux*)a;
    Q8Aux* d2 = (Q8Aux*)b;

    Driver* driver1 = findDriverByID(d1->driverID);
    Driver* driver2 = findDriverByID(d2->driverID);

    char *accountCreationD1 = getDAccountCreation(driver1);
    char *accountCreationD2 = getDAccountCreation(driver2);
    int driverComp = compareDates(accountCreationD1,accountCreationD2);
    
    free(accountCreationD1);
    free(accountCreationD2);
    destructDriverCopy(driver1);
    destructDriverCopy(driver2);

    if (!driverComp){
        User* user1 = findUserByUsername(d1->userID);
        User* user2 = findUserByUsername(d2->userID);
        char *accountCreationU1 = getUAccountCreation(user1);
        char *accountCreationU2 = getUAccountCreation(user2);
        int userComp = compareDates(accountCreationU1,accountCreationU2);

        free(accountCreationU1);
        free(accountCreationU2);
        destructUserCopy(user1);
        destructUserCopy(user2);

        if (!userComp) return strcmp(d1->rideID, d2->rideID);
        else return -userComp;
    } else return -driverComp;


}

void copyToHash2(Pointer key, Pointer value, Pointer userData) {
    char* rideID = (char*)key;
    Ride* r = (Ride*)value;
    Q8Temp* copy = (Q8Temp*)userData;

    char gender = copy->gender;
    int accountYears = copy->accountYears;

    char *driverId = getRDriverId(r);
    char *username = getRUsername(r);
    

    Driver* d = findDriverByID(getRDriverId(r));
    User* u = findUserByUsername(getRUsername(r));

    Q8Aux* temp = (Q8Aux*)malloc(sizeof(Q8Aux));

    char *date1 = getDAccountCreation(d);
    char *date2 = getUAccountCreation(u);

    int driverAccountCreation = dateDifference(dateConvert(date1));
    int userAccountCreation = dateDifference(dateConvert(date2));

    free(date1);
    free(date2);

    int validGender = (getDGender(d) == gender && getUGender(u) == gender);
    int validAccountYears = (driverAccountCreation >= accountYears && userAccountCreation >= accountYears);

    if (validGender && validAccountYears) {
        temp->rideID = strdup(rideID);
        temp->driverID = driverId;
        temp->driverName = getDName(d);
        temp->userID = username;
        temp->userName = getUName(u);
        addToTable(copy->hashTable, temp->rideID, temp);
    }
}

/* 
    O output deverá ser ordenado de forma que as contas mais antigas apareçam primeiro.
    Ordenar por conta mais antiga de condutor e, se necessário, pela conta do utilizador.
    Se persistirem empates, ordenar por id da viagem (ordem descendente).
*/


void q8(char gender, int years) {
    HashTable* rides = rideHashTableSingleton();
    HashTable* resultHash = createHashTable2(&destroyQ8Aux);

    Q8Temp* temp = (Q8Temp*)malloc(sizeof(Q8Temp));
    temp->gender = gender;
    temp->accountYears = years;
    temp->hashTable = resultHash;
    hashForeach(rides, copyToHash2, temp);

    List* copy = copyFromHash(resultHash);
    copy = sortList(copy, compareFunc2);

    int i = 0, j = listLength(copy);
    if (!j) {
        writeResultFile(NULL);
        advanceResultIndex();
        return;
    }

    while (i < j) {
        Q8Aux* q8 = findInListByIndex(copy, i);

        Driver* driver = findDriverByID(q8->driverID);
        User* user = findUserByUsername(q8->userID);

        if (getDAccountStatus(driver) && getUAccountStatus(user)) {
            char *stringAux = calloc(MAX_LINE_LENGTH, sizeof(char));
            sprintf(stringAux, "%s;%s;%s;%s\n", q8->driverID, q8->driverName, q8->userID, q8->userName);

            writeResultFile(stringAux);

            free(stringAux);
        }

        i++;
    }

    advanceResultIndex();

    freeList(copy);
    destroyHash(temp->hashTable);
    free(temp);
}