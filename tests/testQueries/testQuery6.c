#include "../includes/testQuery6.h"

#include "../includes/assert.h"

#include "../../includes/query6.h"
#include "../../includes/terminal.h"
#include "../../includes/times.h"

#include <stdio.h>
#include <stdlib.h>

void testQuery6(const char *filename, char *city, char *date1, char *date2) {
  clock_t timer = initClock();
  char *result = q6(city, date1, date2);
  double seconds = calcTime(&timer);

  char *expectedResult = NULL;
  int isCorrect = assertResult(result, filename, &expectedResult);

  if (isCorrect) {
    greenColor();
    printf("in %.3fs - query6(%s, %s, %s)\n", seconds, city, date1, date2);
  } else {
    redColor();
    printf("in %.3fs - query6(%s, %s, %s)\n\n", seconds, city, date1, date2);

    printf("expected:\n\n");
    printf("%s\n\n", expectedResult);

    printf("got:\n\n");
    printf("%s\n\n", result);
  }

  if (result != NULL) free(result);
  if (expectedResult != NULL) free(expectedResult);
}
