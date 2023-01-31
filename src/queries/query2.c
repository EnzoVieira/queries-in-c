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

int mediaDriverCompare (Pointer a, Pointer b){
  Q2Aux *driver1 = (Q2Aux*)a;
  Q2Aux *driver2 = (Q2Aux*)b;

  if (!b) return 1;
  double score1 = driver1->scoreMedia;
  double score2 = driver2->scoreMedia;

  if (driver1->scoreMedia != driver2->scoreMedia){
    return (score1 < score2);
  }

  else {
    Driver *driver1cpy = findDriverByID(driver1->driverId);
    Driver *driver2cpy = findDriverByID(driver2->driverId);
    
    char *date1 = getDLastRide(driver1cpy);
    char *date2 = getDLastRide(driver2cpy);

    return -(compareDates(date1,date2)||strcmp(driver1->driverId,driver2->driverId));
  }
}

void createDriversList (Pointer key, Pointer value, Pointer data){
  
  char* id = (char*) key;
  Driver *driver = findDriverByID(id); 
  
  if (getDAccountStatus(driver)){
    
    DriverStatistics* driverStatistics = (DriverStatistics*)value;
    Q2Aux *driverToList = (Q2Aux*)malloc(sizeof(Q2Aux));
    List *driversList = (List*)data;

    driverToList->driverId = strdup(id);
    driverToList->driverName = getDName(driver);
    driverToList->scoreMedia = getDStotalScore(driverStatistics)/getDStotalTrips(driverStatistics);

    addToSortedList(driversList,driverToList,mediaDriverCompare);
  }
}



char *q2(int N) {

  static List *driversInfo = NULL;

  if(driversInfo == NULL){
    HashTable *driversStatistics = driversStatisticsHashTableSingleton();
    driversInfo = createList();
    hashForeach(driversStatistics,createDriversList,driversInfo);
  }
  Q2Aux *driver;
  
  char *resultStr = calloc(MAX_LINE_LEN * N, sizeof(char));

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
