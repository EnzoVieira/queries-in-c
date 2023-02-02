#include "../../../includes/rideRepository.h"

#include "../../../includes/driverRepository.h"
#include "../../../includes/driverStatistics.h"
#include "../../../includes/userRepository.h"
#include "../../../includes/userStatistics.h"
#include "../../../includes/utilsStatistics.h"
#include "../../../includes/dates.h"

#include "../../../includes/validateFuncs.h"



#include "../../../includes/reader.h"

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
  //char *comment;
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
  //rideCopy->comment = strdup(ride->comment);

  return rideCopy;
}

// ============================
//       public methods
// ============================

Ride *createRide(char *line) {
  Ride *ride = calloc(1, sizeof(Ride));

  char *lineCopy = strdup(line);
  int valid;

  //ride->id = strdup (strsep(&line, ";"));
  ride->date = strdup(strsep(&lineCopy, ";"));
  //if (*(ride->date) == '\0' || !(validateDate(ride->date))) return NULL;
  
  ride->driver = strdup(strsep(&lineCopy, ";"));
  //if (*(ride->driver) == '\0') return NULL;
  
  ride->user = strdup(strsep(&lineCopy, ";")); 
  //if (*(ride->user) == '\0') return NULL;
  
  ride->city = strdup(strsep(&lineCopy, ";"));
  //if (*(ride->city) == '\0') return NULL;
  
  char* tmpDistance = strdup(strsep(&lineCopy, ";"));
  //if ((!validatePositiveInt(tmpDistance))) return NULL;
  ride->distance = atof(tmpDistance);
  free(tmpDistance);
  
  char* tmpScoreUser = strdup(strsep(&lineCopy, ";"));
  //if ((!validatePositiveFloat(tmpScoreUser))) return NULL;
  ride->score_user = atof(tmpScoreUser);
  free(tmpScoreUser);

  char* tmpScoreDriver = strdup(strsep(&lineCopy, ";"));
  //if ((!validatePositiveFloat(tmpScoreDriver))) return NULL;
  ride->score_driver = atof(tmpScoreDriver);
  free(tmpScoreDriver);
  
  char* tmpTip = strdup(strsep(&lineCopy, ";"));
  //if ((!validatePositiveFloat(tmpTip))) return NULL;
  ride->tip = atof(tmpTip);
  free(tmpTip);
  
  //ride->comment = strdup(strsep(&lineCopy, ";"));
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
  if (user){
    char *lastRide = getULastRide(user);
    
  //Cria ou atualiza um UserStatistics
    addUserStatistics(newRide->user, newRide->distance,newRide->score_user,ridePrice,newRide->tip);
   
    if (!lastRide || isSmallerDate(lastRide,newRide->date)){
      addUserLastRide(newRide->user,newRide->date);
      free(lastRide);
    }
  }

    if(driver){
    char *carClass = getDCarClass(driver);
    char *lastRide = getDLastRide(driver);

    ridePrice = ridePriceCalculator(carClass,newRide->distance);
    addDriverStatistics(strdup(newRide->driver), newRide->distance,newRide->score_driver,ridePrice,newRide->tip);
    
    if (!lastRide || isSmallerDate(lastRide,newRide->date)){
      addDriverLastRide(newRide->driver,newRide->date);
    //free(carClass);
    }
  }
    destructUserCopy(user);
    destructDriverCopy(driver);
}

void createRidesHashTable(const char *path) {
  foreachLineOfFile(path, &addRide);
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

//char *getRComment(const Ride *ride) {
//  return strdup(ride->comment);
//}
