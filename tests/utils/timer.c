#include "../includes/timer.h"

double calcQueryTime(clock_t *start) {
  clock_t time = clock() - *start;
  double queryTime = ((double)time)/CLOCKS_PER_SEC;

  return queryTime;
}
