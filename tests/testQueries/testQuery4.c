#include "../includes/testQuery4.h"

#include "../includes/assert.h"

#include "../../includes/query4.h"
#include "../../includes/terminal.h"
#include "../../includes/times.h"

#include <stdio.h>
#include <stdlib.h>

void testQuery4(const char *filename, char *token) {
  clock_t timer = initClock();
  char *result = q4(token);
  double seconds = calcTime(&timer);

  char *expectedResult = NULL;
  int isCorrect = assertResult(result, filename, &expectedResult);

  if (isCorrect) {
    greenColor();
    printf("in %.3fs - query4(%s)\n", seconds, token);
  } else {
    redColor();
    printf("in %.3fs - query4(%s)\n\n", seconds, token);

    printf("expected:\n\n");
    printf("%s\n\n", expectedResult);

    printf("got:\n\n");
    printf("%s\n\n", result);
  }

  if (result != NULL) free(result);
  if (expectedResult != NULL) free(expectedResult);
}
