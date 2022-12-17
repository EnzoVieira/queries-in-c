#ifndef DATES_H
#define DATES_H

typedef struct {
    int day;
    int month;
    int year;
} Date;

Date *dateConvert(char *birthDate);
int dateToAge (char *dateString);

#endif
