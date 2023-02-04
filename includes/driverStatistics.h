#ifndef DRIVER_STATISTICS_H
#define DRIVER_STATISTICS_H

#include "./api.h"

typedef struct driverStatistics DriverStatistics;

void addDriverStatistics(char *id, double distance, double score, double earn, double tips);
HashTable *driversStatisticsHashTableSingleton();

DriverStatistics *findDriverStatisticsByUsername(const char *id);
double getDStotalDistance(const DriverStatistics *driverStatistics);
double getDStotalScore(const DriverStatistics *driverStatistics);
double getDStotalEarn(const DriverStatistics *driverStatistics);
double getDStotalTrips(const DriverStatistics *driverStatistics);
double getDStotalTipsEarn(const DriverStatistics *driverStatistics);
void destroyDriverStatistics(void *ds);

double getDStotalDistanceNew(char *id);
double getDStotalScoreNew(char *id);
double getDStotalEarnNew(char *id);
double getDStotalTripsNew(char *id);
double getDStotalTipsEarnNew(char *id);
#endif
