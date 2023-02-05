#include "../../../includes/rideRepository.h"

#include "../../../includes/driverRepository.h"
#include "../../../includes/driverStatistics.h"
#include "../../../includes/userRepository.h"
#include "../../../includes/userStatistics.h"
#include "../../../includes/utilsStatistics.h"
#include "../../../includes/dates.h"
#include "../../../includes/validations.h"

#include "../../../includes/reader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_FIELD_LEN 100

struct ride {
  char *date;
  char *driver;
  char *user;
  char *city;
  double distance;
  double score_user;
  double score_driver;
  double tip;
};

// ============================
//       private methods
// ============================

int isValidRide(const char *line) {
  char id[13], date[11], driver[MAX_FIELD_LEN], user[MAX_FIELD_LEN], city[MAX_FIELD_LEN], distance[13], scoreUser[16], scoreDriver[16], tip[16], comment[MAX_FIELD_LEN];
  
  int fields = sscanf(line, "%12[^;];%10[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s", id, date, driver, user, city, distance, scoreUser, scoreDriver, tip, comment);
  // Falha na conversão
  if (fields < 9) {
    return 0;
  }

  int isCorrect = isValidDate(date) &&
                  isValidInt(distance, 0) &&
                  isValidInt(scoreUser, 0) &&
                  isValidInt(scoreDriver, 0) &&
                  isValidDecimal(tip);

  return isCorrect;
}

// ============================
//       public methods
// ============================

Ride *createRide(char *line) {
  Ride *ride = calloc(1, sizeof(Ride));

  ride->date = strdup(strsep(&line, ";"));
  ride->driver = strdup(strsep(&line, ";"));
  ride->user = strdup(strsep(&line, ";"));    
  ride->city = strdup(strsep(&line, ";"));
  ride->distance = atof(strsep(&line, ";"));
  ride->score_user = atof(strsep(&line, ";"));
  ride->score_driver = atof(strsep(&line, ";"));
  ride->tip = atof(strsep(&line, ";"));

  return ride;
}

void addRide(char* line) {
  HashTable *ridesHashTable = rideHashTableSingleton();
  char* id = strsep(&line, ";"); 
  Ride *newRide = createRide(line);
  
  if (!newRide) return ;
  addToTable(ridesHashTable, strdup(id), (Pointer)newRide);
 
  double ridePrice = 0;
  char *carClass = getDCarClassNew(newRide->driver); 
  char *driverLastRide = getDLastRideNew(newRide->driver); 
  char *userLastRide = getULastRideNew(newRide->user); 

  ridePrice = ridePriceCalculator(carClass,newRide->distance);
  
  addDriverStatistics(newRide->driver, newRide->distance,newRide->score_driver,ridePrice,newRide->tip);
  addUserStatistics(newRide->user, newRide->distance,newRide->score_user,ridePrice,newRide->tip);
  
  if (!driverLastRide || isSmallerDate(driverLastRide,newRide->date))
    addDriverLastRide(newRide->driver,newRide->date);
    
  if (!userLastRide || isSmallerDate(userLastRide,newRide->date))
    addUserLastRide(newRide->user,newRide->date);
  
  free(carClass);
  free(driverLastRide);
  free(userLastRide);

}

void createRidesHashTable(const char *path) {
  foreachLineOfFile(path, &addRide, &isValidRide);
}

HashTable *rideHashTableSingleton() {
  static HashTable *ridesHashTable = NULL;

  if (ridesHashTable == NULL) {
    ridesHashTable = createHashTable(&destructRideCopy);
  }

  return ridesHashTable;
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

void destructRideCopy(void *r){
  Ride *ride = (Ride*)r; 
  if (ride){
    if (ride->city)
      free(ride->city);
    if(ride->date)
      free(ride->date);
    if(ride->driver)
      free(ride->driver);
    if(ride->user)
      free(ride->user);
  free(ride);
  }
}

char *getRDateNew(char *id) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  Ride *rideFinded = (Ride*) findById(ridesHashTable, id);
  
  return strdup(rideFinded->date);
}

char *getRDriverIdNew(char *id) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  Ride *rideFinded = (Ride*) findById(ridesHashTable, id);
  
  return strdup(rideFinded->driver);
}

char *getRUsernameNew(char *id) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  Ride *rideFinded = (Ride*) findById(ridesHashTable, id);
  
  return strdup(rideFinded->user);
}

char *getRCityNew(char *id) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  Ride *rideFinded = (Ride*) findById(ridesHashTable, id);
  
  return strdup(rideFinded->city);
}

double getRDistanceNew(char *id) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  Ride *rideFinded = (Ride*) findById(ridesHashTable, id);
  
  return rideFinded->distance;
}

double getRScoreUserNew(char *id) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  Ride *rideFinded = (Ride*) findById(ridesHashTable, id);
  
  return rideFinded->score_user;
}

double getRScoreDriverNew(char *id) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  Ride *rideFinded = (Ride*) findById(ridesHashTable, id);
  
  return rideFinded->score_driver;
}

double getRTipNew(char *id) {
  HashTable *ridesHashTable = rideHashTableSingleton();

  Ride *rideFinded = (Ride*) findById(ridesHashTable, id);
  
  return rideFinded->tip;
}