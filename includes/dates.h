#ifndef DATES_H
#define DATES_H

typedef struct date Date;
Date *dateConvert(char *birthDate);
int dateToAge (char *dateString);

#endif
