#include "../../../includes/rideRepository.h"

void *createRidesHashData()
{
  // Cria a HashTable
  void *hashTable = createTable();

  FILE *fp;
  fp = fopen("../../../db/rides.csv", "r");
  char *line = NULL;
  size_t len;

  getline(&line, &len, fp);

  while (((getline(&line, &len, fp)) != -1))
  {
    Ride *ride = (Ride *)malloc(sizeof(Ride));

    ride->id = strsep(&line, ";");
    ride->date = strsep(&line, ";");
    ride->driver = strsep(&line, ";");
    ride->user = strsep(&line, ";");
    ride->city = strsep(&line, ";");
    ride->distance = atof(strsep(&line, ";"));
    ride->score_user = atof(strsep(&line, ";"));
    ride->score_driver = atof(strsep(&line, ";"));
    ride->tip = atof(strsep(&line, ";"));
    ride->comment = strsep(&line, ";");

    // insere a key user->user_name e a data user na hash
    addToTable(hashTable, ride->id, ride);
  }

  free(line);
  fclose(fp);

  return hashTable;
}