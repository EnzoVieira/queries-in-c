#include "../../includes/query2.h"

#include "../../includes/driverRepository.h"
#include "../../includes/driverStatistics.h"

#include "../../includes/api.h"
#include "../../includes/dates.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 200

typedef struct querie2Aux{
  char *driverId;
  char *driverName;
  double scoreMedia;
}Q2Aux;

void destroyQ2Aux(void *q2Aux){
  Q2Aux *q2 = (Q2Aux*)q2Aux;
  
  if (q2){
    if(q2->driverId)
      free(q2->driverId);
    if(q2->driverName)
      free(q2->driverName);
    free(q2);
  }
}

int mediaDriverCompare (Pointer a, Pointer b){
  Q2Aux *driver1 = (Q2Aux*)a;
  Q2Aux *driver2 = (Q2Aux*)b;

  if (!b) return 1;
  double score1 = driver1->scoreMedia;
  double score2 = driver2->scoreMedia;

  if (score1 != score2){
    return (score1 < score2);
  }

  //Driver *driver1cpy = findDriverByID(driver1->driverId); 
  //Driver *driver2cpy = findDriverByID(driver2->driverId);

  char *date1 = getDLastRideNew(driver1->driverId);
  char *date2 = getDLastRideNew(driver2->driverId);

  int dateCompare = compareDates(date1, date2);
  free(date1);
  free(date2);
  //destructDriverCopy(driver1cpy);
  //destructDriverCopy(driver2cpy);

  if (dateCompare) return dateCompare;
  return strcmp(driver1->driverId, driver2->driverId);
}

void createDriversList (Pointer key, Pointer value, Pointer data){
  
  char* id = (char*)key;
  //Driver *driver = findDriverByID(id); 
  
  if (getDAccountStatusNew(id)){
    
    DriverStatistics* driverStatistics = (DriverStatistics*)value;
    Q2Aux *driverToList = (Q2Aux*)malloc(sizeof(Q2Aux));
    List *driversList = (List*)data;

    driverToList->driverId = strdup(id);
    driverToList->driverName = getDNameNew(id);
    driverToList->scoreMedia = getDStotalScore(driverStatistics)/getDStotalTrips(driverStatistics);

    addToSortedList(driversList,driverToList,mediaDriverCompare);
  }
  //destructDriverCopy(driver);
}

int *q2SingletonIsCreated() {
  static int alreadyCreated = 0;
  return &alreadyCreated;
}

List *q2Singleton () {
  static List *driversInfo = NULL;
  
  if(driversInfo == NULL) {
    HashTable *driversStatistics = driversStatisticsHashTableSingleton();
    driversInfo = createList();
    hashForeach(driversStatistics,createDriversList,driversInfo);

    int *isAlreadyCreated = q2SingletonIsCreated();
    *isAlreadyCreated = 1;
  }

  return driversInfo;
}

void destroyDataQ2() {
  int *isAlreadyCreated = q2SingletonIsCreated();

  if (*isAlreadyCreated) {
    List *q2Data = q2Singleton();
    freeListFull(q2Data,&destroyQ2Aux);
  }
}

char *q2(int N) {

  if(N<1)return NULL;

  List *driversInfo = q2Singleton();

  
  char *resultStr = calloc(MAX_LINE_LEN * N, sizeof(char));
  Q2Aux *driver;

  int i = 1;
  while (i <= N) {
    driver = (Q2Aux*)findInListByIndex(driversInfo,i);
    
    char *stringAux = (char*) calloc(MAX_LINE_LEN, sizeof(char));
    // FIXME: Não acessar diretamente aos valores.
    sprintf(stringAux, "%s;%s;%.3f\n", driver->driverId, driver->driverName, driver->scoreMedia);
    
    strcat(resultStr, stringAux);

    free(stringAux);
    i++;
  }

  return resultStr;
}
