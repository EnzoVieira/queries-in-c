#include "../includes/testQuery7.h"

#include "../includes/assert.h"

#include "../../includes/query7.h"
#include "../../includes/terminal.h"
#include "../../includes/times.h"

#include <stdio.h>
#include <stdlib.h>

void testQuery7(const char *filename, int N, char *city) {
  clock_t timer = initClock();
  char *result = q7(N,city);
  double seconds = calcTime(&timer);

  char *expectedResult = NULL;
  int isCorrect = assertResult(result, filename, &expectedResult);

  if (isCorrect) {
    greenColor();
    printf("in %.3fs - query7(%d, %s)\n", seconds, N, city);
  } else {
    redColor();
    printf("in %.3fs - query7(%d, %s)\n", seconds, N, city);

    // printf("expected:\n\n");
    // printf("%s\n\n", expectedResult);

    // printf("got:\n\n");
    // printf("%s\n\n", result);
  }

  if (result != NULL) free(result);
  if (expectedResult != NULL) free(expectedResult);
}
