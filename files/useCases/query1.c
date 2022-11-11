#include "../../includes/query1.h"
#include "../../includes/writer.h"

#define DATE "09/10/2022"

struct catalog
{
  void *users;
  void *drivers;
  void *rides;
};

typedef struct querie1Aux
{
  char *id;
  int totalTrips;
  double averageRating;
  double tripValue;
  Catalog *catalogo;
} q1Aux;

struct date
{
  int day;
  int month;
  int year;
};

void ridesCounter(gpointer key, gpointer value, gpointer userData)
{
  Ride *r = value;
  q1Aux *q1 = userData;
  char *u = getRUser(r);
  char *d = getRDriver(r);
  if (strcmp(u, q1->id) == 0 || strcmp(d, q1->id) == 0)
    q1->totalTrips++;
  free(u);
  free(d);
}

int numberOfTrips(Catalog *c, char *id)
{
  q1Aux q1 = {id, 0};
  g_hash_table_foreach(c->rides, ridesCounter, &q1);
  return q1.totalTrips;
}

void rating(gpointer key, gpointer value, gpointer userData)
{
  Ride *r = value;
  q1Aux *q1 = userData;
  char *u = getRUser(r);
  char *d = getRDriver(r);
  if (strcmp(u, q1->id) == 0)
  {
    q1->averageRating = q1->averageRating + getRScoreUser(r);
    q1->totalTrips++;
  }
  else if (strcmp(d, q1->id) == 0)
  {
    q1->averageRating = q1->averageRating + getRScoreDriver(r);
    q1->totalTrips++;
  }
  free(u);
  free(d);
}

double totalRating(Catalog *c, char *id)
{
  q1Aux q1 = {id, 0, 0};
  g_hash_table_foreach(c->rides, rating, &q1);
  return (q1.averageRating / q1.totalTrips);
}

void travelCost(gpointer key, gpointer value, gpointer userData) 
{
  Ride *r = value;
  q1Aux *q1 = userData;
  char* u = getRUser(r);
  char* d = getRDriver(r);
  if (strcmp(u, q1->id) == 0 || strcmp(d, q1->id) == 0)
  {
    Driver* driver = findDriverByID(q1->catalogo->drivers, d);
    char *carClass = getDCarClass(driver);
    if (strcmp(carClass, "basic") == 0)
      q1->tripValue = q1->tripValue + (3.25 + 0.62 * getRDistance(r) + getRTip(r));
    else if (strcmp(carClass, "green") == 0)
      q1->tripValue = q1->tripValue + (4.00 + 0.79 * getRDistance(r) + getRTip(r));
    else if (strcmp(carClass, "premium") == 0)
      q1->tripValue = q1->tripValue + (5.20 + 0.94 * getRDistance(r) + getRTip(r));
  }
  free(u);
  free(d);
}

double totalCost(Catalog *c, char *id)
{
  q1Aux q1 = {id, 0, 0, 0, c};
  g_hash_table_foreach(c->rides, travelCost, &q1);
  return q1.tripValue;
}

Date *dateConvert(char *birthDate)
{
  char *date = strdup(birthDate);
  Date *d = (Date *)malloc(sizeof(Date));
  while (date)
  {
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

int getAge(Catalog *c, char *id) {
  User* u = findUserByUsername(c->users, id);
  if (u) {
    return dateDifference(dateConvert(getUBirthDate(u)));
  }
  Driver* d = findDriverByID(c->drivers, id);
  if (d) {
    return dateDifference(dateConvert(getDBirthDate(d)));
  } 
  return 0;
}

void q1(Catalog *c, char *id) {
  User *u = findUserByUsername(c->users, id);
  Driver *d = findDriverByID(c->drivers, id);

  char *name = NULL;
  char gender = '0';
  int age = 0;
  double rating = 0.0;
  int total_rides = 0;
  double total_cost = 0.0;

  if (u && getUAccountStatus(u)) {
    name = getUName(u);
    gender = getUGender(u);
    age = getAge(c, id);
    rating = totalRating(c, id);
    total_rides = numberOfTrips(c, id);
    total_cost = totalCost(c, id);
  }
  else if (d && getDAccountStatus(d)) {
    name = getDName(d);
    gender = getDGender(d);
    age = getAge(c, id);
    rating = totalRating(c, id);
    total_rides = numberOfTrips(c, id);
    total_cost = totalCost(c, id);
  }

  if (name) {
    // numero de caracteres em name, gender, age, rating, total_rides e total_cost, respectivamente, vezes 5
    // para ter certeza que haverá espaço suficiente
    size_t outputLength = (strlen(name) + 1 + 3 + 4 + 6 + 7) * 5;
    char *output = calloc(outputLength, sizeof(char));
    sprintf(output, "%s;%c;%d;%.3f;%d;%.3f\n", name, gender, age, rating, total_rides, total_cost);

    writeFile(output, "Resultados/command1_output.txt");

    // printf("output: %s\n", output);

    free(name);
    free(output);
  }
}
