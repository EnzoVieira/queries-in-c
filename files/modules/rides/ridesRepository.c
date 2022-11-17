#include "../../../includes/rideRepository.h"

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

struct driver {
  char *car_class;
};

struct catalog {
  User *users;
  Driver *drivers;
  Ride *rides;
};

char* getRID(Ride *r) {
  return strdup(r->id);
}

char* getRDate(Ride *r) {
  return strdup(r->date);
}

char* getRDriver(Ride *r) {
  return strdup(r->driver);
}

char* getRUser(Ride *r) {
  return strdup(r->user);
}

char* getRCity(Ride *r) {
  return strdup(r->city);
}

double getRDistance(Ride *r) {
  return r->distance;
}

double getRScoreUser(Ride *r) {
  return r->score_user;
}

double getRScoreDriver(Ride *r) {
  return r->score_driver;
}

double getRTip(Ride *r) {
  return r->tip;
}

char* getRComment(Ride *r) {
  return strdup(r->comment);
}

void *createRidesHashData(const char *path) {
  // Cria a HashTable
  void *hashTable = createTable();

  char *ridesCSVPath = calloc(strlen(path) + strlen("/rides.csv") + 2, sizeof(char));
  sprintf(ridesCSVPath, "%s/rides.csv", path);

  FILE *fp;
  fp = fopen(ridesCSVPath, "r");
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

void driverAccumulator(void *_, void *currentValue, void *acc) {
  Ride *ride = currentValue;
  TotalDriverAcc *accumulator = acc;

  char* currentRDriverId = getRDriver(ride);

  if (strcmp(accumulator->driverId, currentRDriverId) == 0) {
    char *carClass = accumulator->driverCarClass;

    if (strcmp(carClass, "basic") == 0)
      accumulator->totalCost += (3.25 + 0.62 * getRDistance(ride) + getRTip(ride));
    else if (strcmp(carClass, "green") == 0)
      accumulator->totalCost += (4.00 + 0.79 * getRDistance(ride) + getRTip(ride));
    else if (strcmp(carClass, "premium") == 0)
      accumulator->totalCost += (5.20 + 0.94 * getRDistance(ride) + getRTip(ride));

    accumulator->accRating += getRScoreDriver(ride);
    accumulator->totalTrips++;
  }

  free(currentRDriverId);
}

TotalDriverAcc *totalDriver(Catalog *catalog, Driver *driverCopy) {
  TotalDriverAcc *accumulator = calloc(1, sizeof(TotalDriverAcc));

  accumulator->driverId = getDID(driverCopy);
  accumulator->driverCarClass = getDCarClass(driverCopy);
  accumulator->driversTable = catalog->drivers;
  accumulator->totalTrips = 0;
  accumulator->accRating = 0;

  foreach(catalog->rides, driverAccumulator, accumulator);

  accumulator->rating = accumulator->accRating / accumulator->totalTrips;

  return accumulator;
}

void userAccumulator(void *_, void *currentValue, void *acc) {
  Ride *ride = currentValue;
  TotalUserAcc *accumulator = acc;

  char *currentRUsername = getRUser(ride);

  if (strcmp(accumulator->username, currentRUsername) == 0) {
    char *currentRDriverId = getRDriver(ride);
    Driver *driver = findDriverByID(accumulator->tables->drivers, currentRDriverId);
    char *carClass = getDCarClass(driver);

    if (strcmp(carClass, "basic") == 0)
      accumulator->totalCost += (3.25 + 0.62 * getRDistance(ride) + getRTip(ride));
    else if (strcmp(carClass, "green") == 0)
      accumulator->totalCost += (4.00 + 0.79 * getRDistance(ride) + getRTip(ride));
    else if (strcmp(carClass, "premium") == 0)
      accumulator->totalCost += (5.20 + 0.94 * getRDistance(ride) + getRTip(ride));

    accumulator->accRating += getRScoreUser(ride);
    accumulator->totalTrips++;

    free(currentRDriverId);
    free(carClass);
  }

  free(currentRUsername);
}

TotalUserAcc *totalUser(Catalog *catalog, User *userCopy) {
  TotalUserAcc *accumulator = calloc(1, sizeof(TotalUserAcc));

  accumulator->username = getUUsername(userCopy);
  accumulator->tables = catalog;
  accumulator->totalTrips = 0;
  accumulator->accRating = 0;

  foreach(catalog->rides, userAccumulator, accumulator);

  accumulator->rating = accumulator->accRating / accumulator->totalTrips;

  return accumulator;
}
