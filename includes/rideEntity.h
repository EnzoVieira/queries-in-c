#ifndef RIDE_ENTITY
#define RIDE_ENTITY

typedef struct
{
  char *id;
  char *date;
  char *driver;
  char *user;
  char *city;
  double distance;
  double score_user;
  double score_driver;
  double tip;
  char *comment;
} Ride;

#endif