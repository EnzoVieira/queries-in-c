#include "../../includes/userRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/rideRepository.h"

#include "../../includes/terminal.h"
#include "../../includes/strings.h"
#include "../../includes/times.h"

#include <stdio.h>

void seedDatabase(char *folderPath) {
  clock_t timer;

  blueColor();
  printf("\n🌱 A criar a database...\n\n");

  timer = initClock();

  createUsersHashTable(concatStrings(folderPath, "/users.csv"));
  createDriversHashTable(concatStrings(folderPath, "/drivers.csv"));
  // A tabela de rides precisa ser a última a ser criada.
  createRidesHashTable(concatStrings(folderPath, "/rides.csv"));

  greenColor();
  printf("Database criada em %.3fs ✅\n\n", calcTime(&timer));
  resetColor();
}
