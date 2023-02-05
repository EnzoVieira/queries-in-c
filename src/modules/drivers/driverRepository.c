#include "../../../includes/driverRepository.h"

#include "../../../includes/reader.h"
#include "../../../includes/validations.h"
#include "../../../includes/strings.h"

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

Driver *createDriver(char *line) {
  Driver *driver = calloc(1, sizeof(Driver));

  driver->name = strdup(strsep(&line, ";"));
  driver->birth_date = strdup(strsep(&line, ";"));
  driver->gender = *strsep(&line, ";");
  driver->car_class = strdup(strsep(&line, ";"));
  toLowerCase(driver->car_class);
  strsep(&line, ";");
  driver->city = strdup(strsep(&line, ";"));
  driver->account_creation = strdup(strsep(&line, ";"));
  driver->last_ride = calloc(11,sizeof(char));

  char *status = strdup(strsep(&line, ";"));
  if (*status == 'a' || *status == 'A')
    driver->account_status = 1;
  else
    driver->account_status = 0;
  
  free(status);
  return driver;
}

void addDriver(char *line) {
  HashTable *driverHashTable = driverHashTableSingleton();

  char *id = strdup(strsep(&line, ";"));

  Driver *newDriver = createDriver(line);

  addToTable(driverHashTable, id, (Pointer) newDriver);
}

void createDriversHashTable(const char *path) {
  foreachLineOfFile(path, &addDriver, &isValidDriver);
}

HashTable *driverHashTableSingleton() {
  static HashTable *driversHashTable = NULL;

  if (driversHashTable == NULL) {
    driversHashTable = createHashTable(&destructDriverCopy);
  }

  return driversHashTable;
}

void addDriverLastRide(const char *id, const char *date) {
  HashTable *driverHashTable = driverHashTableSingleton();

  Driver *driverFinded = (Driver*)findById(driverHashTable, id);
  free(driverFinded->last_ride);
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


char *getDNameNew(char *id) {
  HashTable* driverHashTable = driverHashTableSingleton();

  Driver* driverFinded = (Driver*) findById(driverHashTable, id);
  
  return strdup(driverFinded->name);
}

char *getDBirthDateNew(char *id) {
  
  HashTable* driverHashTable = driverHashTableSingleton();
  Driver* driverFinded = (Driver*) findById(driverHashTable, id);
  
  return strdup(driverFinded->birth_date);
}

char getDGenderNew(char *id) {
 
  HashTable* driverHashTable = driverHashTableSingleton();
  Driver* driverFinded = (Driver*) findById(driverHashTable, id);
  
  return driverFinded->gender;
}

char *getDCarClassNew(char *id) {
  
  HashTable* driverHashTable = driverHashTableSingleton();
  Driver* driverFinded = (Driver*) findById(driverHashTable, id);
  
  return strdup(driverFinded->car_class);
}

char *getDCityNew(char *id) {
  
  HashTable* driverHashTable = driverHashTableSingleton();
  Driver* driverFinded = (Driver*) findById(driverHashTable, id);
  
  return strdup(driverFinded->city);
}

char *getDAccountCreationNew(char *id) {
  
  HashTable* driverHashTable = driverHashTableSingleton();
  Driver* driverFinded = (Driver*) findById(driverHashTable, id);
  
  return strdup(driverFinded->account_creation);
}

int getDAccountStatusNew(char *id) {
  
  HashTable* driverHashTable = driverHashTableSingleton();
  Driver* driverFinded = (Driver*) findById(driverHashTable, id);
  
  if(!driverFinded)
    return 0;

  return driverFinded->account_status;
}

char *getDLastRideNew(char *id) {
  
  HashTable* driverHashTable = driverHashTableSingleton();
  Driver* driverFinded = (Driver*) findById(driverHashTable, id);
  
  return strdup(driverFinded->last_ride);
}