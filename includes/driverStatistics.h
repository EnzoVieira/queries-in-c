#ifndef DRIVER_STATISTICS_H
#define DRIVER_STATISTICS_H

#include "./api.h"

typedef struct driverStatistics DriverStatistics;

void addDriverStatistics(char *id, double distance, double score, double earn, double tips);
HashTable *driversStatisticsHashTableSingleton();

#endif
