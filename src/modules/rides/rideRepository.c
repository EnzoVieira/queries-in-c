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

int isValidRide(const char *line) {
  char id[13], date[11], driver[MAX_FIELD_LEN], user[MAX_FIELD_LEN], city[MAX_FIELD_LEN], distance[13], scoreUser[16], scoreDriver[16], tip[16], comment[MAX_FIELD_LEN];
  
  int fields = sscanf(line, "%12[^;];%10[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s", id, date, driver, user, city, distance, scoreUser, scoreDriver, tip, comment);
  // Falha na conversão
  if (fields < 9) {
    return 0;
  }

  int isCorrect = isValidDate(date) && isValidInt(distance, 0) && isValidInt(scoreUser, 1) && isValidInt(scoreDriver, 1) && isValidDecimal(tip);

  return isCorrect;
}

// ============================
//       public methods
// ============================

Ride *createRide(char *line) {
  Ride *ride = calloc(1, sizeof(Ride));

  char *lineCopy = strdup(line);

  ride->date = strdup(strsep(&lineCopy, ";"));
  ride->driver = strdup(strsep(&lineCopy, ";"));
  ride->user = strdup(strsep(&lineCopy, ";"));    
  ride->city = strdup(strsep(&lineCopy, ";"));
  ride->distance = atof(strsep(&lineCopy, ";"));
  ride->score_user = atof(strsep(&lineCopy, ";"));
  ride->score_driver = atof(strsep(&lineCopy, ";"));
  ride->tip = atof(strsep(&lineCopy, ";"));
  ride->comment = strdup(strsep(&lineCopy, ";"));

  return ride;
}

void addRide(char* line) {
  HashTable *ridesHashTable = rideHashTableSingleton();
  char* id = strdup(strsep(&line, ";"));
  Ride *newRide = createRide(line);
  if (!newRide) return ;
  addToTable(ridesHashTable, id, (Pointer)newRide);

  User *user = findUserByUsername(newRide->user);
  Driver *driver = findDriverByID(newRide->driver);
  double ridePrice = 0;

  if(driver){
    char *carClass = getDCarClass(driver);
    char *lastRide = getDLastRide(driver);

    ridePrice = ridePriceCalculator(carClass,newRide->distance);
    addDriverStatistics(newRide->driver, newRide->distance,newRide->score_driver,ridePrice,newRide->tip);
    
    if (!lastRide || isSmallerDate(lastRide,newRide->date)){
      addDriverLastRide(newRide->driver,newRide->date);
    //free(carClass);
    }
  }
  if (user){
    char *lastRide = getULastRide(user);
    
  // Add user and ride relation
    addUserRide(newRide->user, id);
  //Cria ou atualiza um UserStatistics
    addUserStatistics(newRide->user, newRide->distance,newRide->score_user,ridePrice,newRide->tip);
   
    if (!lastRide || isSmallerDate(lastRide,newRide->date)){
      addUserLastRide(newRide->user,newRide->date);
    //free(carClass);
    }
  }


}

void createRidesHashTable(const char *path) {
  foreachLineOfFile(path, &addRide, &isValidRide);
}

HashTable *rideHashTableSingleton() {
  static HashTable *ridesHashTable = NULL;

  if (ridesHashTable == NULL) {
    ridesHashTable = createHashTable();
  }

  return ridesHashTable;
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
