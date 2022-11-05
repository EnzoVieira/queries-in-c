#ifndef DRIVER_ENTITY
#define DRIVER_ENTITY

#include <stdbool.h>

typedef struct
{
  char *id;
  char *name;
  char *birth_date;
  char gender;
  char *car_class;
  char *license_plate;
  char *city;
  char *account_creation;
  bool account_status;
} Driver;

#endif