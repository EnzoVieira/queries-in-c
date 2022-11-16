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

  while (((getline(&line, &len, fp)) != -1))
  {
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

/*
Ride* cloneRide(Ride *r) {
    Ride* copy = malloc(sizeof(Ride));
    copy->id = strdup(r->id);
    copy->date = strdup(r->date);
    copy->driver = strdup(r->driver);
    copy->user = strdup(r->user);
    copy->city = strdup(r->city);
    copy->distance = r->distance;
    copy->score_user = r->score_user;
    copy->score_driver = r->score_driver;
    copy->tip = r->tip;
    copy->comment = strdup(r->comment);

    return copy;
}
*/

/*
Ride* findRideByID(GHashTable* rides, char* id) {
  if (g_hash_table_lookup(rides, id))
    printf("A viagem com o ID %s existe.\n", id);
  return g_hash_table_lookup(rides, id);
}
*/
