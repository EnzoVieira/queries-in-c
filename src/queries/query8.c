#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/query8.h"
#include "../../includes/api.h"

#include "../../includes/rideRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/userRepository.h"
#include "../../includes/dates.h"

#define MAX_LINE_LENGTH 200

typedef struct q8Data{
    HashTable *hashM;
    HashTable *hashF;
    List *listM;
    List *listF;
}Q8Data;

typedef struct query8Aux {
    char* rideID;
    char* driverID;
    char* userID;
    int ageD;
    int ageU;
} Q8Aux;

void destroyQ8Aux (void *q8Aux){
    
    Q8Aux *q8 = (Q8Aux*)q8Aux;

    if(q8){
        if(q8->driverID)
            free(q8->driverID);
        if(q8->userID)
            free(q8->userID);
        free (q8);
    }
}

int compareFunc2(Pointer a, Pointer b) {
    Q8Aux* d1 = (Q8Aux*)a;
    Q8Aux* d2 = (Q8Aux*)b;

    char *accountCreationD1 = getDAccountCreationNew(d1->driverID);
    char *accountCreationD2 = getDAccountCreationNew(d2->driverID);
    int driverComp = compareDates(accountCreationD1,accountCreationD2);
    
    free(accountCreationD1);
    free(accountCreationD2);

    if (!driverComp){
        char *accountCreationU1 = getUAccountCreationNew(d1->userID);
        char *accountCreationU2 = getUAccountCreationNew(d2->userID);
        int userComp = compareDates(accountCreationU1,accountCreationU2);

        free(accountCreationU1);
        free(accountCreationU2);

        if (!userComp) return strcmp(d1->rideID, d2->rideID);
        else return -userComp;
    } else return -driverComp;


}

void copyToHash2(Pointer key, Pointer value, Pointer userData) {
    char* rideID = (char*)key;
    Ride* r = (Ride*)value;
    Q8Data* copy = (Q8Data*)userData;

    char *driverId = getRDriverId(r);
    char *username = getRUsername(r);
    
    
    if (getDAccountStatusNew(driverId) && getUAccountStatusNew(username)) {
        
        if((getDGenderNew(driverId) == getUGenderNew(username))){
            Q8Aux* temp = (Q8Aux*)malloc(sizeof(Q8Aux));
    
            char *driverAccountCreation = getDAccountCreationNew(driverId);
            char *userAccountCreation = getUAccountCreationNew(username);
            int driverAccountAge = dateToAge(driverAccountCreation);
            int userAccountAge = dateToAge(userAccountCreation);
            free(driverAccountCreation);
            free(userAccountCreation);
            temp->rideID = strdup(rideID);
            temp->driverID = driverId;
            temp->userID = username;
            temp->ageD = driverAccountAge;
            temp->ageU = userAccountAge;       
            if (getDGenderNew(driverId) == 'M'){
                addToTable(copy->hashM, temp->rideID, temp);
            }
            else {
                addToTable(copy->hashF, temp->rideID, temp);
            }
        }else {
            free(driverId);
            free(username);
        }
    } else {
        free(driverId);
        free(username);
    }
}

Q8Data *resulHashSingleton () {
    static Q8Data *data = NULL;

    if(!data){
        HashTable* rides = rideHashTableSingleton();
        data = (Q8Data*)calloc(1,sizeof(Q8Data));
        data->hashM = createHashTable(&destroyQ8Aux);
        data->hashF = createHashTable(&destroyQ8Aux);
        hashForeach(rides, copyToHash2, data);
        data->listM = copyFromHash(data->hashM);
        data->listM = sortList(data->listM,compareFunc2);
        data->listF = copyFromHash(data->hashF);
        data->listF = sortList(data->listF,compareFunc2);
    }

    return data;

}

void destroyDataQ8(){
  Q8Data *q8Data = resulHashSingleton();
  freeList(q8Data->listM);
  freeList(q8Data->listF);
  destroyHash(q8Data->hashM);
  destroyHash(q8Data->hashF);
  free(q8Data);
}

char* q8(char gender, int years) {    

    Q8Data *resultData = resulHashSingleton(); //Retorna data dependendo do genero
    List *list;
    if (gender == 'M'){
        list = resultData->listM;
    }
    else{
        list = resultData->listF;
    }
    
    int i = 0, j = listLength(list);
    
    if (!j) return NULL;
    Q8Aux* q8 = getListData(list);
    if (!(years <= q8->ageD || years <= q8->ageU)) return NULL;
    char* stringGrande = calloc(MAX_LINE_LENGTH * listLength(list), sizeof(char));
    char *uName;
    char *dName;
    while ((years <= q8->ageD || years <= q8->ageU) && i<j) {

        if ((years <= q8->ageD && years <= q8->ageU)){
            uName = getUNameNew(q8->userID);
            dName = getDNameNew(q8->driverID);
            char *stringAux = calloc(MAX_LINE_LENGTH, sizeof(char));
            sprintf(stringAux, "%s;%s;%s;%s\n", q8->driverID, dName, q8->userID, uName);
            strcat(stringGrande, stringAux);
            free(dName);
            free(uName);
            free(stringAux);
            i++;
        }
        else{
            i++;
        }
        list = listNext(list);
        q8 = getListData(list);
    }

    return stringGrande;
}