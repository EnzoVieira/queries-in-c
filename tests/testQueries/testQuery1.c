#include "../includes/testQuery1.h"

#include "../includes/assert.h"

#include "../../includes/query1.h"
#include "../../includes/terminal.h"
#include "../../includes/times.h"

#include <stdio.h>
#include <stdlib.h>

void testQuery1(const char *filename, char *token) {
  clock_t timer = initClock();
  char *result = q1(token);
  double seconds = calcTime(&timer);

  char *expectedResult = NULL;
  int isCorrect = assertResult(result, filename, &expectedResult);

  if (isCorrect) {
    greenColor();
    printf("in %.3fs - query1(%s)\n", seconds, token);
  } else {
    redColor();
    printf("in %.3fs - query1(%s)\n\n", seconds, token);

    printf("expected:\n\n");
    printf("\t%s\n\n", expectedResult);

    printf("got:\n\n");
    printf("\t%s\n\n", result);
  }

  if (result != NULL) free(result);
  if (expectedResult != NULL) free(expectedResult);
}
