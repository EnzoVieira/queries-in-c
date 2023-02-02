#include "../includes/testQuery8.h"

#include "../includes/assert.h"

#include "../../includes/query8.h"
#include "../../includes/terminal.h"
#include "../../includes/times.h"

#include <stdio.h>
#include <stdlib.h>

void testQuery8(const char *filename, char gender, int years) {
  clock_t timer = initClock();
  char *result = q8(gender, years);
  double seconds = calcTime(&timer);

  char *expectedResult = NULL;
  int isCorrect = assertResult(result, filename, &expectedResult);

  if (isCorrect) {
    greenColor();
    printf("in %.3fs - query8(%c, %d)\n", seconds, gender, years);
  } else {
    redColor();
    printf("in %.3fs - query8(%c, %d)\n\n", seconds, gender, years);

    printf("expected:\n\n");
    printf("%s\n\n", expectedResult);

    printf("got:\n\n");
    printf("%s\n\n", result);
  }

  if (result != NULL) free(result);
  if (expectedResult != NULL) free(expectedResult);
}
