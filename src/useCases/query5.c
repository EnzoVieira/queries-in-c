#include "../../includes/query5.h"

#include "../../includes/rideRepository.h"

#include <stdio.h>
#include <stdlib.h>

struct catalog {
  void *users;
  void *drivers;
  void *rides;
};

char *q5(Catalog *c, char *city, char *dateA, char *dateB) {
  TotalRideAcc *acc = totalRide(c, city, dateA, dateB);

  if (acc->averageDistance) {
    size_t outputLength = 12;
    char *output = calloc(outputLength, sizeof(char));
    sprintf(output, "%.3f\n", acc->averageDistance);

    return output;
  }

  return NULL;
}