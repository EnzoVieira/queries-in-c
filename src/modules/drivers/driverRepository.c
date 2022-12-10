#include "../../../includes/driverRepository.h"
#include <string.h>
#include <stdlib.h>

struct driver {
  //char *id;
  char *name;
  char *birth_date;
  char gender;
  char *car_class;
  char *license_plate;
  char *city;
  char *account_creation;
  int account_status;
  List *driverRidesId;
};

// ============================
//       private methods
// ============================

Driver *getDriverCopy(Driver* driver) {
  Driver* driverCopy = calloc(1, sizeof(Driver));

  //driverCopy->id = strdup(driver->id);
  driverCopy->name = strdup(driver->name);
  driverCopy->birth_date = strdup(driver->birth_date);
  driverCopy->gender = driver->gender;
  driverCopy->car_class = strdup(driver->car_class);
  driverCopy->license_plate = strdup(driver->license_plate);
  driverCopy->city = strdup(driver->city);
  driverCopy->account_creation = strdup(driver->account_creation);
  driverCopy->account_status = driver->account_status;

  return driverCopy;
}

// ============================
//       public methods
// ============================

Driver *createDriver(const char *line) {
  Driver *driver = calloc(1, sizeof(Driver));

  char *lineCopy = strdup(line);

  //driver->id = strdup(strsep(&lineCopy, ";"));
  driver->name = strdup(strsep(&lineCopy, ";"));
  driver->birth_date = strdup(strsep(&lineCopy, ";"));
  driver->gender = *strsep(&lineCopy, ";");
  driver->car_class = strdup(strsep(&lineCopy, ";"));
  driver->license_plate = strdup(strsep(&lineCopy, ";"));
  driver->city = strdup(strsep(&lineCopy, ";"));
  driver->account_creation = strdup(strsep(&lineCopy, ";"));

  if (*(strsep(&lineCopy, ";")) == 'a')
    driver->account_status = 1;
  else
    driver->account_status = 0;
  
  free(lineCopy);
  return driver;
}

char *getDName(Driver *driver) {
  return strdup(driver->name);
}

char *getDBirthDate(Driver *driver) {
  return strdup(driver->birth_date);
}

char getDGender(Driver *driver) {
  return driver->gender;
}

char *getDCarClass(Driver *driver) {
  return strdup(driver->car_class);
}

char *getDLicensePlate(Driver *driver) {
  return strdup(driver->license_plate);
}

char *getDCity(Driver *driver) {
  return strdup(driver->city);
}

char *getDAccountCreation(Driver *driver) {
  return strdup(driver->account_creation);
}

int getDAccountStatus(Driver *driver) {
  return driver->account_status;
}

HashTable *driverHashTableSingleton() {
  static HashTable *driversHashTable = NULL;

  if (driversHashTable == NULL) {
    driversHashTable = createHashTable();
  }

  return driversHashTable;
}

void addDriver(const char *line) {
  //HashTable *driverHashTable = driverHashTableSingleton();

  //addToTable(driverHashTable, strdup(id), (Pointer) newDriver);
}

// Always returns a copy when driver exists
Driver *findDriverByID(const char *id) {
  HashTable* driverHashTable = driverHashTableSingleton();

  Driver* driverFinded = (Driver*) findById(driverHashTable, id);

  if (driverFinded) {
    return getDriverCopy(driverFinded);
  }

  return NULL;
}