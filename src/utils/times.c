#include "../../includes/times.h"

clock_t initClock() {
  return clock();
}

double calcTime(clock_t *initTime) {
  clock_t clocks = clock() - *initTime;

  return ( (double) clocks ) / CLOCKS_PER_SEC;
}
