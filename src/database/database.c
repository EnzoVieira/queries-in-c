#include "../../includes/userRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/rideRepository.h"

#include "../../includes/terminal.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void seedDatabase(const char *folderPath) {
  char *usersCSVpath = calloc(strlen(folderPath) + strlen("/users.csv"), sizeof(char));
  char *driversCSVpath = calloc(strlen(folderPath) + strlen("/drivers.csv"), sizeof(char));
  char *ridesCSVpath = calloc(strlen(folderPath) + strlen("/rides.csv"), sizeof(char));

  blueColor();
  printf("\n🌱 A criar a database...\n\n");

  sprintf(usersCSVpath, "%s/users.csv", folderPath);
  createUsersHashTable(usersCSVpath);

  sprintf(driversCSVpath, "%s/drivers.csv", folderPath);
  createDriversHashTable(driversCSVpath);

  sprintf(ridesCSVpath, "%s/rides.csv", folderPath);
  // A tabela de rides precisa ser a última a ser criada.
  createRidesHashTable(ridesCSVpath);

  greenColor();
  printf("Database criada em 0.00s\n\n");

  resetColor();
}
