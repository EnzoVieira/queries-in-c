#include "../../includes/userRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/rideRepository.h"

#include "../../includes/terminal.h"
#include "../../includes/strings.h"
#include "../../includes/times.h"

#include <stdio.h>
#include <stdlib.h>

void seedDatabase(char *folderPath) {
  clock_t timer;

  blueColor();
  printf("\n🌱 A criar a database...\n\n");

  timer = initClock();

  char *usersPath = concatStrings(folderPath, "/users.csv");
  char *driversPath = concatStrings(folderPath, "/drivers.csv");
  char *ridesPath = concatStrings(folderPath, "/rides.csv");
  
  createUsersHashTable(usersPath);
  createDriversHashTable(driversPath);
  // A tabela de rides precisa ser a última a ser criada.
  createRidesHashTable(ridesPath);

  greenColor();
  printf("Database criada em %.3fs ✅\n\n", calcTime(&timer));
  resetColor();

  free(usersPath);
  free(driversPath);
  free(ridesPath);
}
