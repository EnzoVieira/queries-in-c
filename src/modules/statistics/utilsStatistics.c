#include <stdio.h>
#include <string.h>
#include "../../../includes/utilsStatistics.h"

double ridePriceCalculator (char *carClass, double distance){

  if (strcmp(carClass, "basic") == 0)
    return (3.25 + 0.62 * distance);
  else if (strcmp(carClass, "green") == 0)
    return (4.00 + 0.79 * distance);
  else if (strcmp(carClass, "premium") == 0)
    return (5.20 + 0.94 * distance);
  return -1;

}