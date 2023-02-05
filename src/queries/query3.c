#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/api.h"
#include "../../includes/query3.h"

#include "../../includes/userRepository.h"
#include "../../includes/userStatistics.h"
#include "../../includes/dates.h"

#define MAX_LINE_LEN 200

typedef struct querie3Aux{
  char *username;
  char *name;
  double totalDistance;
}Q3Aux;

typedef struct q3Data{
  HashTable *hash;
  List *list;
}Q3Data;

void destroyQ3Aux(void *q3Aux){
  Q3Aux *q3 = (Q3Aux*)q3Aux;
  
  if (q3){
    if(q3->username)
      free(q3->username);
    if(q3->name)
      free(q3->name);
    free(q3);
  }
}

int userCompare (Pointer a, Pointer b){
  Q3Aux *user1 = (Q3Aux*)a;
  Q3Aux *user2 = (Q3Aux*)b;

  double distance1 = user1->totalDistance;
  double distance2 = user2->totalDistance;

  if (distance1 != distance2){
    return (distance1 < distance2);
  }

    //User *user1cpy = findUserByUsername(user1->username);
    //User *user2cpy = findUserByUsername(user2->username);
    
    char *date1 = getULastRideNew(user1->username);
    char *date2 = getULastRideNew(user2->username);
    
    int cmpDates = compareDates(date1, date2);
    free(date1);
    free(date2);
    //destructUserCopy(user1cpy);
    //destructUserCopy(user2cpy);

    if (cmpDates) return cmpDates;
    return strcmp(user1->username, user2->username);
}

void createUsersList (Pointer key, Pointer value, Pointer data){
  
  char* username = (char*) key;
  UserStatistics* userStatistics = (UserStatistics*)value;
  //User *userCpy = findUserByUsername(username); 
  if (getUAccountStatusNew(username)){
    Q3Aux *userToList = (Q3Aux*)malloc(sizeof(Q3Aux));
    HashTable *usersList = (HashTable*)data;

    userToList->username = strdup(username);
    userToList->name = getUNameNew(username);
    userToList->totalDistance = getUStotalDistance(userStatistics);
    addToTable(usersList,strdup(username),userToList);    
  }
  //destructUserCopy(userCpy);
}

int *q3SingletonIsCreated() {
  static int alreadyCreated = 0;
  return &alreadyCreated;
}

Q3Data *dataSingleton (){
  static Q3Data *data = NULL;
  
  if(data==NULL){
    data = (Q3Data*)malloc(sizeof(Q3Data));
    HashTable *usersStatistics = usersStatisticsHashTableSingleton();
    data->hash = createHashTable(&destroyQ3Aux);
    hashForeach(usersStatistics,createUsersList,data->hash);
    data->list = copyFromHash(data->hash);
    data->list = sortList(data->list,userCompare);

    int *isAlreadyCreated = q3SingletonIsCreated();
    *isAlreadyCreated = 1;
  }

  return data;
}

void destroyDataQ3(){
  int *isAlreadyCreated = q3SingletonIsCreated();

  if (*isAlreadyCreated) {
    Q3Data *q3Data = dataSingleton();
    freeList(q3Data->list);
    destroyHash(q3Data->hash);
    free(q3Data);
  }
}

char *q3 (int N){

  if(N<1) return NULL;

  Q3Data *data = dataSingleton();

  Q3Aux *user;

  char *resultStr = calloc(MAX_LINE_LEN * N, sizeof(char));
  
  int i = 0;
  while (i < N) {
    user = (Q3Aux*)findInListByIndex(data->list,i);

    char *stringAux = (char*) calloc(MAX_LINE_LEN, sizeof(char));
    // FIXME: Não acessar diretamente aos valores.
    sprintf(stringAux, "%s;%s;%.0f\n", user->username, user->name, user->totalDistance);
    
    strcat(resultStr, stringAux);
    free(stringAux);

    i++;
  }

  return resultStr;
}