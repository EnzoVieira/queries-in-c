#include "../../../includes/rideRepository.h"

#include "../../../includes/userRepository.h"

#include <stdlib.h>
#include <string.h>

struct ride {
  char *id;
  char *username;
  char *city;
};

// ============================
//       private methods
// ============================

Ride *getRideCopy(Ride *ride) {
  Ride *rideCopy = calloc(1, sizeof(Ride));

  rideCopy->id = strdup(ride->id);
  rideCopy->username = strdup(ride->username);
  rideCopy->city = strdup(ride->city);

  return rideCopy;
}

// ============================
//       public methods
// ============================

Ride *createRide(const char *id, const char* username, const char *city) {
  Ride *ride = calloc(1, sizeof(Ride));

  ride->id = strdup(id);
  ride->username = strdup(username);
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
  User *user = findUserByUsername(newRide->username);
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

char *getRID(const Ride *ride) {
  return strdup(ride->id);
}

char *getRUsername(const Ride *ride) {
  return strdup(ride->username);
}

char *getRCity(const Ride *ride) {
  return strdup(ride->city);
}
