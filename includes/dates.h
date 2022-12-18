#ifndef DATES_H
#define DATES_H

typedef struct date {
    int day;
    int month;
    int year;
} Date;

Date* dateConvert(char *birthDate);
int dateToAge (char *dateString);
int dateDifference(Date *d);
int isSmallerDate(char *a, char *b);
int isDateBetween(char* dateA, char* dateB, char *dateC);
int compareDates(char* a, char* b);


#endif
