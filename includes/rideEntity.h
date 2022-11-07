#ifndef RIDE_ENTITY
#define RIDE_ENTITY

typedef struct ride Ride;
char* getRID(Ride *r);
char* getRDate(Ride *r);
char* getRDriver(Ride *r);
char* getRUser(Ride *r);
char* getRCity(Ride *r);
double getRDistance(Ride *r);
double getRScoreUser(Ride *r);
double getRScoreDriver(Ride *r);
double getRTip(Ride *r);
char* getRComment(Ride *r);

#endif