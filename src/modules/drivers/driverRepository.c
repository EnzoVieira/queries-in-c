#include "../../../includes/driverRepository.h"

#include "../../../includes/reader.h"
#include "../../../includes/validations.h"

#include <string.h>
#include <stdlib.h>

#define MAX_FIELD_LEN 100

struct driver {
  char *name;
  char *birth_date;
  char gender;
  char *car_class;
  char *city;
  char *account_creation;
  int account_status;
  char *last_ride;
};

// ============================
//       private methods
// ============================

Driver *getDriverCopy(Driver* driver) {
  Driver* driverCopy = calloc(1, sizeof(Driver));

  driverCopy->name = strdup(driver->name);
  driverCopy->birth_date = strdup(driver->birth_date);
  driverCopy->gender = driver->gender;
  driverCopy->car_class = strdup(driver->car_class);
  driverCopy->city = strdup(driver->city);
  driverCopy->account_creation = strdup(driver->account_creation);
  driverCopy->last_ride = strdup(driver->last_ride);
  driverCopy->account_status = driver->account_status;

  return driverCopy;
}

int isValidDriver(const char *line) {
  char id[13], name[MAX_FIELD_LEN], birthDay[11], gender[2], carClass[8], licensePlate[9], city[MAX_FIELD_LEN], accountCreation[11], accountStatus[9];

  int fields = sscanf(line, "%12[^;];%[^;];%10[^;];%1[^;];%[^;];%8[^;];%[^;];%10[^;];%[^\n]", id, name, birthDay, gender, carClass, licensePlate, city, accountCreation, accountStatus);
  // Falha na conversão
  if (fields != 9) {
    return 0;
  }

  int isCorrect = isValidDate(birthDay) && 
                  isValidDate(accountCreation) && 
                  isValidCarClass(carClass) && 
                  isValidAccountStatus(accountStatus);

  return isCorrect;
}

// ============================
//       public methods
// ============================

Driver *createDriver(const char *line) {
  Driver *driver = calloc(1, sizeof(Driver));

  char *lineCopy = strdup(line);

  driver->name = strdup(strsep(&lineCopy, ";"));
  driver->birth_date = strdup(strsep(&lineCopy, ";"));
  driver->gender = *strsep(&lineCopy, ";");
  driver->car_class = strdup(strsep(&lineCopy, ";"));
  strsep(&lineCopy, ";");
  driver->city = strdup(strsep(&lineCopy, ";"));
  driver->account_creation = strdup(strsep(&lineCopy, ";"));
  driver->last_ride = calloc(11,sizeof(char));

  if (*(strsep(&lineCopy, ";")) == 'a')
    driver->account_status = 1;
  else
    driver->account_status = 0;
  
  free(lineCopy);
  return driver;
}

void addDriver(char *line) {
  HashTable *driverHashTable = driverHashTableSingleton();

  char *lineCopy = strdup(line);
  char *id = strdup(strsep(&lineCopy, ";"));

  Driver *newDriver = createDriver(lineCopy);

  addToTable(driverHashTable, id, (Pointer) newDriver);
}

void createDriversHashTable(const char *path) {
  foreachLineOfFile(path, &addDriver, &isValidDriver);
}

HashTable *driverHashTableSingleton() {
  static HashTable *driversHashTable = NULL;

  if (driversHashTable == NULL) {
    driversHashTable = createHashTable2(&destructDriverCopy);
  }

  return driversHashTable;
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

void addDriverLastRide(const char *id, const char *date) {
  HashTable *driverHashTable = driverHashTableSingleton();

  Driver *driverFinded = (Driver*)findById(driverHashTable, id);

  driverFinded->last_ride = strdup(date);
}


// ============================
//           GETTERS
// ============================

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

char *getDCity(Driver *driver) {
  return strdup(driver->city);
}

char *getDAccountCreation(Driver *driver) {
  return strdup(driver->account_creation);
}

int getDAccountStatus(Driver *driver) {
  return driver->account_status;
}

char *getDLastRide(Driver *driver) {
  return strdup(driver->last_ride);
}

void destructDriverCopy(void *d){
  Driver *driver = (Driver*)d; 
  if (driver){
    if (driver->name)
      free(driver->name);
    if (driver->birth_date)
      free(driver->birth_date);
    if (driver->car_class)
      free(driver->car_class);
    if (driver->city)
      free(driver->city);
    if (driver->account_creation)
      free(driver->account_creation);
    if (driver->last_ride)
      free(driver->last_ride);
    free(driver);
  }
}