#include "../includes/testQuery2.h"

#include "../includes/assert.h"

#include "../../includes/query2.h"
#include "../../includes/terminal.h"
#include "../../includes/times.h"

#include <stdio.h>
#include <stdlib.h>

void testQuery2(const char *filename, char *token) {
  clock_t timer = initClock();
  char *result = q2(atoi(token));
  double seconds = calcTime(&timer);

  char *expectedResult = NULL;
  int isCorrect = assertResult(result, filename, &expectedResult);

  if (isCorrect) {
    greenColor();
    printf("in %.3fs - query2(%s)\n", seconds, token);
  } else {
    redColor();
    printf("in %.3fs - query2(%s)\n\n", seconds, token);

    printf("expected:\n\n");
    printf("%s\n\n", expectedResult);

    printf("got:\n\n");
    printf("%s\n\n", result);
  }

  if (result != NULL) free(result);
  if (expectedResult != NULL) free(expectedResult);
}
