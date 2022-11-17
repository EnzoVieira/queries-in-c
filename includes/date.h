#ifndef DATE_H
#define DATE_H

#include <stdlib.h>
#include <string.h>

typedef struct {
  int day;
  int month;
  int year;
} Date;

Date *dateConvert(char *birthDate);
int dateDifference(Date *d);

#endif
