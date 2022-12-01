#include "../../includes/database.h"

struct user {
  char *user_name;
  char *name;
  char gender;
  char *birth_date;
  char *account_creation;
  char *pay_method;
  int  account_status;
};

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

struct ride {
  char *id;
  char *date;
  char *driver;
  char *user;
  char *city;
  double distance;
  double score_user;
  double score_driver;
  double tip;
  char *comment;
};

struct catalog {
  void *users;
  void *drivers;
  void *rides;
};

void *createUsersHashData(const char *path) {
  // Cria a HashTable
  void *hashTable = createTable(NULL);

  char *userCSVPath = calloc(strlen(path) + strlen("/users.csv") + 2, sizeof(char));
  sprintf(userCSVPath, "%s/users.csv", path);

  FILE *fp;
  fp = fopen(userCSVPath, "r");

  if (fp == NULL) {
    printf("Falha ao ler o file %s\n", path);
    exit(1);
  }

  char *line = NULL;
  size_t len;

  getline(&line, &len, fp);

  while (((getline(&line, &len, fp)) != -1)) {
    User *user = (User *)malloc(sizeof(User));

    user->user_name = strdup(strsep(&line, ";"));
    user->name = strdup(strsep(&line, ";"));
    user->gender = *strsep(&line, ";");
    user->birth_date = strdup(strsep(&line, ";"));
    user->account_creation = strdup(strsep(&line, ";"));
    user->pay_method = strdup(strsep(&line, ";"));

    if (*(strsep(&line, ";")) == 'a')
      user->account_status = 1;
    else 
      user->account_status = 0;

    // insere a key user->user_name e a data user na hash
    addToTable(hashTable, user->user_name, user);
  }

  free(line);
  fclose(fp);

  return hashTable;
}

void *createDriversHashData(const char *path) {
  // Cria a HashTable
  void *hashTable = createTable(NULL);

  char *driversCSVPath = calloc(strlen(path) + strlen("/drivers.csv") + 2, sizeof(char));
  sprintf(driversCSVPath, "%s/drivers.csv", path);

  FILE *fp;
  fp = fopen(driversCSVPath, "r");

  if (fp == NULL) {
    printf("Falha ao ler o file %s\n", path);
    exit(1);
  }

  char *line = NULL;
  size_t len;

  getline(&line, &len, fp);

  while (((getline(&line, &len, fp)) != -1)) {

    Driver *driver = (Driver *)malloc(sizeof(Driver));

    driver->id = strdup(strsep(&line, ";"));
    driver->name = strdup(strsep(&line, ";"));
    driver->birth_date = strdup(strsep(&line, ";"));
    driver->gender = *strsep(&line, ";");
    driver->car_class = strdup(strsep(&line, ";"));
    driver->license_plate = strdup(strsep(&line, ";"));
    driver->city = strdup(strsep(&line, ";"));
    driver->account_creation = strdup(strsep(&line, ";"));

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

void *createRidesHashData(const char *path) {
  // Cria a HashTable
  void *hashTable = createTable(NULL);

  char *ridesCSVPath = calloc(strlen(path) + strlen("/rides.csv") + 2, sizeof(char));
  sprintf(ridesCSVPath, "%s/rides.csv", path);

  FILE *fp;
  fp = fopen(ridesCSVPath, "r");

  if (fp == NULL) {
    printf("Falha ao ler o file %s\n", path);
    exit(1);
  }

  char *line = NULL;
  size_t len;

  getline(&line, &len, fp);

  while (((getline(&line, &len, fp)) != -1)) {
    Ride *ride = (Ride *)malloc(sizeof(Ride));

    ride->id = strdup (strsep(&line, ";"));
    ride->date = strdup(strsep(&line, ";"));
    ride->driver = strdup(strsep(&line, ";"));
    ride->user = strdup(strsep(&line, ";"));
    ride->city = strdup(strsep(&line, ";"));
    ride->distance = atof(strsep(&line, ";"));
    ride->score_user = atof(strsep(&line, ";"));
    ride->score_driver = atof(strsep(&line, ";"));
    ride->tip = atof(strsep(&line, ";"));
    ride->comment = strdup(strsep(&line, ";"));

    // insere a key user->user_name e a data user na hash
    addToTable(hashTable, ride->id, ride);
  }

  free(line);
  fclose(fp);

  return hashTable;
}

Catalog *seedDatabase(const char* path) {
    Catalog *c = calloc(1, sizeof(Catalog));

    c->users = createUsersHashData(path);
    printf("Tabela Users criada. ✅\n");
    c->drivers = createDriversHashData(path);
    printf("Tabela Drivers criada. ✅\n");
    c->rides = createRidesHashData(path);
    printf("Tabela Rides criada. ✅\n");

    return c;
}