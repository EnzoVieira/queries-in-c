#include "../../../includes/rideRepository.h"

#include "../../../includes/userRepository.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ride {
  //char *id;
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

// ============================
//       private methods
// ============================

Ride *getRideCopy(Ride *ride) {
  Ride *rideCopy = calloc(1, sizeof(Ride));

  //rideCopy->id = strdup(ride->id);
  rideCopy->date = strdup(ride->date);
  rideCopy->driver = strdup(ride->driver);
  rideCopy->user = strdup(ride->user);
  rideCopy->city = strdup(ride->city);
  rideCopy->distance = ride->distance;
  rideCopy->score_user = ride->score_user;
  rideCopy->score_driver = ride->score_driver;
  rideCopy->tip = ride->tip;
  rideCopy->comment = strdup(ride->comment);

  return rideCopy;
}

// ============================
//       public methods
// ============================

Ride *createRide(char *line) {
  Ride *ride = calloc(1, sizeof(Ride));

  //char *line = strdup(line);

  //ride->id = strdup (strsep(&line, ";"));
  ride->date = strdup(strsep(&line, ";"));
  ride->driver = strdup(strsep(&line, ";"));
  ride->user = strdup(strsep(&line, ";"));    
  ride->city = strdup(strsep(&line, ";"));
  ride->distance = atof(strsep(&line, ";"));
  ride->score_user = atof(strsep(&line, ";"));
  ride->score_driver = atof(strsep(&line, ";"));
  ride->tip = atof(strsep(&line, ";"));
  ride->comment = strdup(strsep(&line, ";"));
  return ride;
}

HashTable *rideHashTableSingleton() {
  static HashTable *ridesHashTable = NULL;

  if (ridesHashTable == NULL) {
    ridesHashTable = createHashTable();
  }

  return ridesHashTable;
}

void addRide(char* line) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  char* id = strdup(strsep(&line, ";"));

  Ride *newRide = createRide(line);

  addToTable(ridesHashTable, id, (Pointer)newRide);

  // Add user and ride relation
  User *user = findUserByUsername(newRide->user);
  if (user)
    addUserRide(newRide->user, id);
}

// Always returns a copy when ride exists
Ride *findRideById(const char *id) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  Ride *rideFinded = (Ride*) findById(ridesHashTable, id);

  if (rideFinded) {
    return getRideCopy(rideFinded);
  }

  return NULL;
}

// ============================
//           GETTERS
// ============================

char *getRDate(const Ride *ride) {
  return strdup(ride->date);
}

char *getRDriverId(const Ride *ride) {
  return strdup(ride->driver);
}

char *getRUsername(const Ride *ride) {
  return strdup(ride->user);
}

char *getRCity(const Ride *ride) {
  return strdup(ride->city);
}

double getRDistance(const Ride *ride) {
  return ride->distance;
}

double getRScoreUser(const Ride *ride) {
  return ride->score_user;
}

double getRScoreDriver(const Ride *ride) {
  return ride->score_driver;
}

double getRTip(const Ride *ride) {
  return ride->tip;
}

char *getRComment(const Ride *ride) {
  return strdup(ride->comment);
}
