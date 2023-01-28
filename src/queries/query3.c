#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/api.h"
#include "../../includes/query3.h"

#include "glib.h"
#include "../../includes/userRepository.h"
#include "../../includes/userStatistics.h"
#include "../../includes/dates.h"

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

    return -(compareDates(date1,date2)||strcmp(user1->username,user2->username));
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

void q3 (int N){

  printf("oi");
  static List *usersInfo = NULL;

  if(usersInfo == NULL){
      HashTable *usersStatistics = usersStatisticsHashTableSingleton();
      HashTable *usersInfoHash = createHashTable();
      hashForeach(usersStatistics,createUsersList,usersInfoHash);
      usersInfo = copyFromHash(usersInfoHash);
      usersInfo = sortList(usersInfo,userCompare);
  }
  Q3Aux *user;
  
  int i = 0;
  while (i < N) {
        user = (Q3Aux*)findInListByIndex(usersInfo,i);
        printf("i :%d,%s,%s,%.3f\n",i,user->username,user->name,user->totalDistance);
        i++;
    }    
}