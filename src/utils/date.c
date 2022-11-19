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

// Calcula se a data A é menor que a data B
int isSmallerDate(char *a, char *b) {
  // compara anos
  if (atoi(a+6) < atoi(b+6)) return 1;
  // compara meses, mas tem a certeza que os anos são iguais
  if ((atoi(a+6) == atoi(b+6)) && (atoi(a+3) < atoi(b+3))) return 1;
  // compara os dias, mas tem a certeza que os anos e os meses são igual
  if ((atoi(a+6) == atoi(b+6)) && (atoi(a+3) == atoi(b+3)) && (atoi(a) <= atoi(b))) return 1;

  return 0;
}

// Calcula se a data B está entre a data A e a data C
int isDateBetween(char* dateA, char* dateB, char *dateC) {
  return (isSmallerDate(dateA, dateB) && isSmallerDate(dateB, dateC));
}