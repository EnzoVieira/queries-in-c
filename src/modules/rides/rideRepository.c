#include "../../../includes/rideRepository.h"

#include "../../../includes/userRepository.h"

#include <stdlib.h>
#include <string.h>

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

// ============================
//       private methods
// ============================

Ride *getRideCopy(Ride *ride) {
  Ride *rideCopy = calloc(1, sizeof(Ride));

  rideCopy->id = strdup(ride->id);
  rideCopy->date = strdup(ride->date);
  rideCopy->driver = srtdip(ride->driver);
  rideCopy->user = strdup(ride->user);
  rideCopy->city = strdup(ride->city);
  rideCopy->distance = ride->distance;
  rideCopy->score_user = ride->score_user;
  rideCopy->score_driver = ride->score_driver;
  rideCopy->tip = ride->tip;
  rideCopy->comment = 

  return rideCopy;
}

// ============================
//       public methods
// ============================

Ride *createRide(const char *id, const char* username, const char *city) {
  Ride *ride = calloc(1, sizeof(Ride));

  ride->id = strdup(id);
  ride->user = strdup(username);
  ride->city = strdup(city);

  return ride;
}

HashTable *rideHashTableSingleton() {
  static HashTable *ridesHashTable = NULL;

  if (ridesHashTable == NULL) {
    ridesHashTable = createHashTable();
  }

  return ridesHashTable;
}

void addRide(Ride *newRide) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  addToTable(ridesHashTable, newRide->id, (Pointer) newRide);

  // Add user and ride relation
  User *user = findUserByUsername(newRide->user);
  addUserRide(getUUsername(user), newRide->id);
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

char *getRID(const Ride *ride) {
  return strdup(ride->id);
}

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
