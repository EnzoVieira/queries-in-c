#include "../../includes/query1.h"

struct catalog {
  void *users;
  void *drivers;
  void *rides;
};

struct user {
  char *name;
  char gender;
  char *birth_date;
  char *account_creation;
  char *pay_method;
  int  account_status;
};

struct driver {
  char *id;
  char *name;
  char *birth_date;
  char gender;
  char *car_class;
  char *license_plate;
  char *city;
  char *account_creation;
  int  account_status;
};

char *q1(Catalog *c, char *id) {
  User *userExists = findUserByUsername(c->users, id);
  Driver *driverExists = findDriverByID(c->drivers, id);

  char *name = NULL;
  char gender = '0';
  int age = 0;
  double rating = 0.0;
  int total_rides = 0;
  double total_cost = 0.0;

  if (userExists && getUAccountStatus(userExists)) {
    User userCopy = *userExists;
    TotalUserAcc *acc = totalUser(c, &userCopy);

    name = getUName(userExists);
    gender = getUGender(userExists);
    age = getUserAge(userExists);
    rating = acc->rating;
    total_rides = acc->totalTrips;
    total_cost = acc->totalCost;
  }
  else if (driverExists && getDAccountStatus(driverExists)) {
    Driver driverCopy = *driverExists;
    TotalDriverAcc *acc = totalDriver(c, &driverCopy);

    name = getDName(driverExists);
    gender = getDGender(driverExists);
    age = getDriverAge(driverExists);
    rating = acc->rating;
    total_rides = acc->totalTrips;
    total_cost = acc->totalCost;
  }

  if (name) {
    // numero de caracteres em name, gender, age, rating, total_rides e total_cost, respectivamente, vezes 5
    // para ter certeza que haverá espaço suficiente
    size_t outputLength = (strlen(name) + 1 + 3 + 4 + 6 + 7) * 5;
    char *output = calloc(outputLength, sizeof(char));
    sprintf(output, "%s;%c;%d;%.3f;%d;%.3f\n", name, gender, age, rating, total_rides, total_cost);

    free(name);

    return output;
  }

  return NULL;
}