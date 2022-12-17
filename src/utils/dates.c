#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/dates.h"

#define DATE "09/10/2022"

struct date{
    int day;
    int month;
    int year;
};


Date *dateConvert(char *birthDate) {
    
    char *date = strdup(birthDate);
    Date *d = (Date *)malloc(sizeof(Date)); 
    
    d->day = atoi(strdup(strsep(&date, "/")));
    d->month = atoi(strdup(strsep(&date, "/")));
    d->year = atoi(strdup(strsep(&date, "\0")));

    if(date)
        free(date);


  return d;
}

int dateToAge (char *dateString){
    
    int age = 0;
    Date *todayDate = dateConvert(DATE);
    Date *date = dateConvert(dateString);
          //diferença de anos           retira 1 se o mes é anterior            retira 1 se o mes for igual e o dia anterior              
    age = (todayDate->year - date->year)-(todayDate->month<date->month || (todayDate->month==date->month && todayDate->day<date->day));

    printf("AGE:%d\n",age);

    return age;
}