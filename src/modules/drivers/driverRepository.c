#include "../../../includes/driverRepository.h"

struct driver {
  char *id;
  char *name;
  char *birth_date;
  char gender;
  char *car_class;
  char *license_plate;
  char *city;
  char *account_creation;
  int  account_status;
};

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

Driver *findDriverByID(HashTable *drivers, char *id) {
  return findBy(drivers, id);
}

int getDriverAge(Driver *driver) {
  char *driverBirthDate = getDBirthDate(driver);

  return dateDifference(dateConvert(driverBirthDate));
}
