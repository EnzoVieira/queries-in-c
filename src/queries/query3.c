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


int userCompare (Pointer a, Pointer b){
  Q3Aux *user1 = (Q3Aux*)a;
  Q3Aux *user2 = (Q3Aux*)b;

  double distance1 = user1->totalDistance;
  double distance2 = user2->totalDistance;

  if (distance1 != distance2){
    return (distance1 < distance2);
  }

  else {
    User *user1cpy = findUserByUsername(user1->username);
    User *user2cpy = findUserByUsername(user2->username);
    
    char *date1 = getULastRide(user1cpy);
    char *date2 = getULastRide(user2cpy);

    int cmpDates = compareDates(date1, date2);

    if (cmpDates) return cmpDates;
    return strcmp(user1->username, user2->username);
  }
}

void createUsersList (Pointer key, Pointer value, Pointer data){
  
  char* username = (char*) key;
  User *user = findUserByUsername(username); 
  UserStatistics* userStatistics = (UserStatistics*)value;
  if (getUAccountStatus(user)){
    
    Q3Aux *userToList = (Q3Aux*)malloc(sizeof(Q3Aux));
    HashTable *usersList = (HashTable*)data;

    userToList->username = strdup(username);
    userToList->name = getUName(user);
    userToList->totalDistance = getUStotalDistance(userStatistics);

    addToTable(usersList,strdup(username),userToList);    
  }
}

char *q3 (int N){

  static List *usersInfo = NULL;

  if(usersInfo == NULL){
    HashTable *usersStatistics = usersStatisticsHashTableSingleton();
    HashTable *usersInfoHash = createHashTable();
    hashForeach(usersStatistics,createUsersList,usersInfoHash);
    usersInfo = copyFromHash(usersInfoHash);
    usersInfo = sortList(usersInfo,userCompare);
  }
  Q3Aux *user;

  char *resultStr = calloc(MAX_LINE_LEN * N, sizeof(char));
  
  int i = 0;
  while (i < N) {
    user = (Q3Aux*)findInListByIndex(usersInfo,i);

    char *stringAux = (char*) calloc(MAX_LINE_LEN, sizeof(char));
    // FIXME: Não acessar diretamente aos valores.
    sprintf(stringAux, "%s;%s;%.0f\n", user->username, user->name, user->totalDistance);
    
    strcat(resultStr, stringAux);
    free(stringAux);

    i++;
  }

  return resultStr;
}