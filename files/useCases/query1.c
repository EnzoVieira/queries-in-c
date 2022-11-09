#include "../../includes/query1.h"

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
  int age;
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
  {
    q1->totalTrips++;
  }
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
}

double totalRating(Catalog *c, char *id)
{
  q1Aux q1 = {id, 0, 0};
  g_hash_table_foreach(c->rides, rating, &q1);
  return (q1.averageRating / q1.totalTrips);
}

Ride *findRideByID(Catalog *c, char *id)
{
  if (g_hash_table_lookup(c->rides, id))
    printf("A viagem com o ID %s existe.\n", id);
  return (g_hash_table_lookup(c->rides, id));
}

void travelCost(gpointer key, gpointer value, gpointer userData)
{
  Ride *r = value;
  q1Aux *q1 = userData;
  // Catalogo* c = (Catalogo*) q1->catalogo;
  GHashTable *drivers = q1->catalogo->drivers;
  char *u = getRUser(r);
  char *d = getRDriver(r);
  // a viagem existe na hashtable
  if (strcmp(u, q1->id) == 0 || strcmp(d, q1->id) == 0)
  {
    char *carClass = getDCarClass(findDriverByID(drivers, d));
    if (strcmp(carClass, "basic") == 0)
      q1->tripValue = q1->tripValue + (3.25 + 0.62 * getRDistance(r));
    else if (strcmp(carClass, "green") == 0)
      q1->tripValue = q1->tripValue + (4.00 + 0.79 * getRDistance(r));
    else if (strcmp(carClass, "premium") == 0)
      q1->tripValue = q1->tripValue + (5.20 + 0.94 * getRDistance(r));
  }
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

int dateDifference(Date *d)
{
  Date *consideredDate = dateConvert(DATE);
  int age = 0;
  if ((consideredDate->year >= d->year && consideredDate->month > d->month) ||
      (consideredDate->year >= d->year && consideredDate->month == d->month && consideredDate->day >= d->day))
    age = consideredDate->year - d->year;
  else
    age = (consideredDate->year - d->year) - 1;
  return age;
}

void findAge(gpointer key, gpointer value, gpointer userData)
{
  Ride *r = value;
  q1Aux *q1 = userData;
  char *u = getRUser(r);
  char *d = getRDriver(r);
  GHashTable *us = q1->catalogo->users;
  GHashTable *dr = q1->catalogo->drivers;
  if (strcmp(getUUsername(findUserByUsername(us, u)), q1->id) == 0)
    q1->age = dateDifference(dateConvert(getUBirthDate(findUserByUsername(us, u))));
  else if (strcmp(getDID(findDriverByID(dr, d)), q1->id) == 0)
    q1->age = dateDifference(dateConvert(getDBirthDate(findDriverByID(dr, d))));
}

int getAge(Catalog *c, char *id)
{
  q1Aux q1 = {id, 0, 0, 0, c, 0};
  g_hash_table_foreach(c->rides, findAge, &q1);
  return q1.age;
}

void q1(Catalog *c, char *id)
{
  User *u = findUserByUsername(c->users, id);
  Driver *d = findDriverByID(c->drivers, id);
  char *name = NULL;
  char gender = '0';
  int age = 0;
  double rating = 0.0;
  int total_rides = 0;
  double total_cost = 0.0;

  if (u)
  {
    name = getUUsername(u);
    gender = getUGender(u);
    age = getAge(c, id);
    rating = totalRating(c, id);
    total_rides = numberOfTrips(c, id);
    total_cost = totalCost(c, id);
  }
  else if (d)
  {
    name = getDID(d);
    gender = getDGender(d);
    age = getAge(c, id);
    rating = totalRating(c, id);
    total_rides = numberOfTrips(c, id);
    total_cost = totalCost(c, id);
  }
  printf("%s; %c; %d; %.3f; %d; %.3f\n", name, gender, age, rating, total_rides, total_cost);
}