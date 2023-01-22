#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/dates.h"

#define DATE "09/10/2022"

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

    return age;
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

int compareDates (char* a, char* b){
  //Os return são com "-"(menos) antes pois eu quero ordenar por ordem decrescente 
  //0 se a==b ; -1 se a>b ; 1 se a<b
  //DATA TIPO XX/XX/XXXX
  //a+6 vai ler só a parte da string que corresposde ao ano
  //a+3 vai ler a parte da string que corresposde ao mes e ano
  //a vai ler só a parte da string que corresposde ao dia mes e ano

  //Se o ano for igual
  if (!strcmp(a+6,b+6)){
    //Se o mes e o ano for igual (compara os dias)
    if (!strcmp(a+3,b+3)){
      return -(strcmp(a,b));
    }
    //Se o mes for diferente (compara os meses)
    return -(strcmp(a+3,b+3));
  }
  //Se o ano for diferente (compara os anos)
  return -(strcmp(a+6,b+6));
}