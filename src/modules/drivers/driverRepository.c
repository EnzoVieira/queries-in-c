#include "../../../includes/driverRepository.h"
#include <string.h>
#include <stdlib.h>

struct driver {
  char *id;
  char *name;
  char *birth_date;
  char gender;
  char *car_class;
  char *license_plate;
  char *city;
  char *account_creation;
  int account_status;
};

// ============================
//       private methods
// ============================

Driver *getDriverCopy(Driver* d) {
  Driver* driverCopy = calloc(1, sizeof(Driver));

  driverCopy->id = strdup(d->id);
  driverCopy->name = strdup(d->name);
  driverCopy->birth_date = strdup(d->birth_date);
  driverCopy->gender = d->gender;
  driverCopy->car_class = strdup(d->car_class);
  driverCopy->license_plate = strdup(d->license_plate);
  driverCopy->city = strdup(d->city);
  driverCopy->account_creation = strdup(d->account_creation);
  driverCopy->account_status = d->account_status;

  return driverCopy;
}

// ============================
//       public methods
// ============================

char *getDID(Driver *d) {
  return strdup(d->id);
}

char *getDName(Driver *d) {
  return strdup(d->name);
}

char *getDBirthDate(Driver *d) {
  return strdup(d->birth_date);
}

char getDGender(Driver *d) {
  return d->gender;
}

char *getDCarClass(Driver *d) {
  return strdup(d->car_class);
}

char *getDLicensePlate(Driver *d) {
  return strdup(d->license_plate);
}

char *getDCity(Driver *d) {
  return strdup(d->city);
}

char *getDAccountCreation(Driver *d) {
  return strdup(d->account_creation);
}

int getDAccountStatus(Driver *d) {
  return d->account_status;
}

HashTable *driverHashTableSingleton() {
  static HashTable *driversHashTable = NULL;

  if (driversHashTable == NULL) {
    driversHashTable = createHashTable();
  }

  return driversHashTable;
}

void addDriver(Driver* newDriver) {
  HashTable *driverHashTable = driverHashTableSingleton();

  addToTable(driverHashTable, newDriver->id, (Pointer) newDriver);
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