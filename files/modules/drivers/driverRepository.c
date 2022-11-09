#include "../../../includes/driverRepository.h"

struct driver
{
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

char *getDID(Driver *d)
{
  return strdup(d->id);
}

char *getDName(Driver *d)
{
  return strdup(d->name);
}

char *getDBirthDate(Driver *d)
{
  return strdup(d->birth_date);
}

char getDGender(Driver *d)
{
  return d->gender;
}

char *getDCarClass(Driver *d)
{
  return strdup(d->car_class);
}

char *getDLicensePlate(Driver *d)
{
  return strdup(d->license_plate);
}

char *getDCity(Driver *d)
{
  return strdup(d->city);
}

char *getDAccountCreation(Driver *d)
{
  return strdup(d->account_creation);
}

int getDAccountStatus(Driver *d)
{
  return d->account_status;
}

void *createDriversHashData()
{
  // Cria a HashTable
  void *hashTable = createTable();

  FILE *fp;
  fp = fopen("files/data/drivers.csv", "r");
  char *line = NULL;
  size_t len;

  getline(&line, &len, fp);

  while (((getline(&line, &len, fp)) != -1))
  {

    Driver *driver = (Driver *)malloc(sizeof(Driver));

    driver->id = strsep(&line, ";");
    driver->name = strsep(&line, ";");
    driver->birth_date = strsep(&line, ";");
    driver->gender = *strsep(&line, ";");
    driver->car_class = strsep(&line, ";");
    driver->license_plate = strsep(&line, ";");
    driver->city = strsep(&line, ";");
    driver->account_creation = strsep(&line, ";");

    if (*(strsep(&line, ";")) == 'a')
      driver->account_status = 1;
    else
      driver->account_status = 0;

    // insere a key user->user_name e a data user na hash
    addToTable(hashTable, driver->id, driver);
  }

  free(line);
  fclose(fp);

  return hashTable;
}

/*
Driver* cloneDriver(Driver *d) {
  Driver* copy = malloc(sizeof(Driver));
  copy->id = strdup(d->id);
  copy->name = strdup(d->name);
  copy->birth_date = strdup(d->birth_date);
  copy->gender = d->gender;
  copy->car_class = strdup(d->car_class);
  copy->license_plate = strdup(d->license_plate);
  copy->city = strdup(d->city);
  copy->account_creation = strdup(d->account_creation);
  copy->account_status = strdup(d->account_status);

  return copy;
}
*/

Driver *findDriverByID(GHashTable *drivers, char *id)
{
  return g_hash_table_lookup(drivers, id);
}
