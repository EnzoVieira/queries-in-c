#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../../includes/userStatistics.h"
#include "../../../includes/userRepository.h"
#include "../../../includes/rideRepository.h"

struct userStatistics {
  double totalDistance;
  double totalScore;
  double totalTrips;
  double totalExpense;
  double totalTipsExpense;
};


HashTable *usersStatisticsHashTableSingleton() {
  static HashTable *userStatisticsHashTable = NULL;

  if (userStatisticsHashTable == NULL) {
    userStatisticsHashTable = createHashTable();
  }

  return userStatisticsHashTable;
}


UserStatistics *createUserStatistics(char *user, double distance, double score, double expense, double tips) {
  UserStatistics *userStatistics = calloc(1, sizeof(UserStatistics));

  userStatistics->totalDistance += distance;
  userStatistics->totalScore += score;
  userStatistics->totalTrips ++;
  userStatistics->totalExpense += expense;
  userStatistics->totalTipsExpense += tips;

  return userStatistics;

}

void addUserStatistics(char *user, double distance, double score, double expense, double tips) {

  HashTable *usersStatisticsHashTable = usersStatisticsHashTableSingleton();
  UserStatistics *userStatistics = findById(usersStatisticsHashTable,user);

  //Se não existir cria um novo
  if (!userStatistics){
    userStatistics = createUserStatistics (user, distance, score,expense,tips);
    addToTable(usersStatisticsHashTable, strdup(user),(Pointer)userStatistics);
  }
  //Se existir atualiza o existente
  else {
    userStatistics->totalDistance += distance;
    userStatistics->totalScore += score;
    userStatistics->totalTrips ++;
    userStatistics->totalExpense += expense;
    userStatistics->totalTipsExpense += tips;
  }
}

double getUStotalExpense(const UserStatistics *userStatistics) {
  return userStatistics->totalExpense;
}

double getUStotalTrips(const UserStatistics *userStatistics) {
  return userStatistics->totalTrips;
}

double getUStotalTipsExpense(const UserStatistics *userStatistics) {
  return userStatistics->totalTipsExpense;
}