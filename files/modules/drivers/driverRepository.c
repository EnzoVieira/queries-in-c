#include "../../../includes/driverRepository.h"

void *createDriversHashData()
{
  // Cria a HashTable
  void *hashTable = createTable();

  FILE *fp;
  fp = fopen("../../../db/drivers.csv", "r");
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
    driver->account_status = strsep(&line, ";");

    // insere a key user->user_name e a data user na hash
    addToTable(hashTable, driver->id, driver);
  }

  free(line);
  fclose(fp);

  return hashTable;
}

Driver* cloneDriver(Driver *d) {
  Driver* copy = malloc(sizeof(Driver));
  copy->id = strdup(d->id);
  copy->name = strdup(d->name);
  copy->birth_day = strdup(d->birth_day);
  copy->gender = d->gender;
  copy->car_class = strdup(d->car_class);
  copy->license_plate = strdup(d->license_plate);
  copy->city = strdup(d->city);
  copy->account_creation = strdup(d->account_creation);
  copy->account_status = d->account_status;

  return copy;
}

