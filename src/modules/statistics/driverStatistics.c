#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../../includes/driverRepository.h"
#include "../../../includes/driverStatistics.h"
#include "../../../includes/rideRepository.h"

struct driverStatistics {
  double totaDistance;
  double totalScore;
  double totalTrips;
  double totalEarn;
  double totalTipsEarn;
};

HashTable *driversStatisticsHashTableSingleton() {
  static HashTable *driverStatisticsHashTable = NULL;

  if (driverStatisticsHashTable == NULL) {
    driverStatisticsHashTable = createHashTable();
  }

  return driverStatisticsHashTable;
}


DriverStatistics *createDriverStatistics(char *id, double distance, double score, double earn, double tips) {
  
  DriverStatistics *driverStatistics = calloc(1, sizeof(DriverStatistics));

  driverStatistics->totaDistance += distance;
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
    driverStatistics->totaDistance += distance;
    driverStatistics->totalScore += score;
    driverStatistics->totalTrips ++;
    driverStatistics->totalEarn += earn;
    driverStatistics->totalTipsEarn += tips;
  }
}