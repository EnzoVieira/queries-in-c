#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../../includes/driverRepository.h"
#include "../../../includes/driverStatistics.h"
#include "../../../includes/rideRepository.h"

struct driverStatistics {
  double totalDistance;
  double totalScore;
  double totalTrips;
  double totalEarn;
  double totalTipsEarn;
};

DriverStatistics *getDriverStatisticsCopy(DriverStatistics *driverStatistics) {
  DriverStatistics *driverStatisticsCopy = calloc(1, sizeof(DriverStatistics));

  driverStatisticsCopy->totalDistance = driverStatistics->totalDistance;
  driverStatisticsCopy->totalScore = driverStatistics->totalScore;
  driverStatisticsCopy->totalTrips = driverStatistics->totalTrips;
  driverStatisticsCopy->totalEarn = driverStatistics->totalEarn;
  driverStatisticsCopy->totalTipsEarn = driverStatistics->totalTipsEarn;
  return driverStatisticsCopy;
}

HashTable *driversStatisticsHashTableSingleton() {
  static HashTable *driverStatisticsHashTable = NULL;

  if (driverStatisticsHashTable == NULL) {
    driverStatisticsHashTable = createHashTable();
  }

  return driverStatisticsHashTable;
}


DriverStatistics *createDriverStatistics(char *id, double distance, double score, double earn, double tips) {
  
  DriverStatistics *driverStatistics = calloc(1, sizeof(DriverStatistics));

  driverStatistics->totalDistance += distance;
  driverStatistics->totalScore += score;
  driverStatistics->totalTrips ++;
  driverStatistics->totalEarn += earn;
  driverStatistics->totalTipsEarn += tips;

  return driverStatistics;

}

void addDriverStatistics(char *id, double distance, double score, double earn, double tips) {

  HashTable *driversStatisticsHashTable = driversStatisticsHashTableSingleton();
  DriverStatistics *driverStatistics = findById(driversStatisticsHashTable,id);

  //Se não existir cria um novo
  if (!driverStatistics){
    driverStatistics = createDriverStatistics (id, distance, score,earn,tips);
    addToTable(driversStatisticsHashTable, strdup(id),(Pointer)driverStatistics);
  }
  //Se existir atualiza o existente
  else {
    driverStatistics->totalDistance += distance;
    driverStatistics->totalScore += score;
    driverStatistics->totalTrips ++;
    driverStatistics->totalEarn += earn;
    driverStatistics->totalTipsEarn += tips;
  }
}

DriverStatistics *findDriverStatisticsByUsername(const char *id) {
  HashTable *driverStatisticsHashTable = driversStatisticsHashTableSingleton();

  DriverStatistics *driverFinded = (DriverStatistics*) findById(driverStatisticsHashTable, id);
  if (driverFinded) {
    return getDriverStatisticsCopy(driverFinded);
  }

  return NULL;
}

double getDStotalDistance(const DriverStatistics *driverStatistics) {
  return driverStatistics->totalDistance;
}

double getDStotalScore(const DriverStatistics *driverStatistics) {
  return driverStatistics->totalScore;
}

double getDStotalEarn(const DriverStatistics *driverStatistics) {
  return driverStatistics->totalEarn;
}

double getDStotalTrips(const DriverStatistics *driverStatistics) {
  return driverStatistics->totalTrips;
}

double getDStotalTipsEarn(const DriverStatistics *driverStatistics) {
  return driverStatistics->totalTipsEarn;
}