#include "../../includes/date.h"

#define DATE "09/10/2022"

Date *dateConvert(char *birthDate) {
  char *date = strdup(birthDate);
  Date *d = (Date *)malloc(sizeof(Date));

  while (date) {
    d->day = atoi(strdup(strsep(&date, "/")));
    d->month = atoi(strdup(strsep(&date, "/")));
    d->year = atoi(strdup(strsep(&date, "\0")));
  }

  return d;
}

int dateDifference(Date *d) {
  Date *consideredDate = dateConvert(DATE);
  int age = 0;
  
  if ((consideredDate->year >= d->year && consideredDate->month > d->month) ||
      (consideredDate->year >= d->year && consideredDate->month == d->month && consideredDate->day >= d->day))
    age = consideredDate->year - d->year;
  else
    age = (consideredDate->year - d->year) - 1;

  free(consideredDate);
  return age;
}