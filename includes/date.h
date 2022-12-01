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
int isSmallerDate(char *a, char *b);
int isDateBetween(char* dateA, char* dateB, char *dateC);
int compareDates (char* a, char* b);

#endif
