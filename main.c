#include "includes/userRepository.h"
#include "includes/driverRepository.h"
#include "includes/rideRepository.h"
#include "includes/userStatistics.h"
#include "includes/driverStatistics.h"

#include "includes/query1.h"
#include "includes/query2.h"
#include "includes/dates.h"

#include "includes/api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printUserList(Pointer data, Pointer _) {
  printf("%s", (char*) data);
}

int main() {
  createUsersHashTable("config/data/users.csv");
  createDriversHashTable("config/data/drivers.csv");
  // A tabela de rides precisa ser a última a ser criada.
  createRidesHashTable("config/data/rides.csv");

  HashTable *usersTable = userHashTableSingleton();
  HashTable *driversTable = driverHashTableSingleton();
  HashTable *ridesTable = rideHashTableSingleton();
  HashTable *usersStatisticsTable = usersStatisticsHashTableSingleton();
  HashTable *driversStatisticsTable = driversStatisticsHashTableSingleton();

  User *user = findById(usersTable, "SebastFerreira-Lopes");
  printf("user name: %s\n", getUName(user));
  List *userList = getUserRidesList(user);
  listForeach(userList, &printUserList);

  Driver *driver = findById(driversTable, "000000004416");
  printf("driver name: %s\n", getDName(driver));

  Ride *ride = findById(ridesTable, "000000002236");
  printf("ride user: %s\n", getRUsername(ride));

  UserStatistics *userStatistics = findById(usersStatisticsTable,"PetrPacheco");

  printf("AGEAGE:%d\n",dateToAge("29/04/1996"));

  printf("%s\n",q1("000000003874"));
  q2(50);
  q2(50);
  q2(50);


  return 0;
}
