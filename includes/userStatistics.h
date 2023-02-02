#ifndef USER_STATISTICS_H
#define USER_STATISTICS_H

#include "./api.h"

typedef struct userStatistics UserStatistics;

void addUserStatistics(char *user, double distance, double score, double expense, double tips);
HashTable *usersStatisticsHashTableSingleton();

UserStatistics *findUserStatisticsByUsername(const char *username);
double getUStotalDistance(const UserStatistics *userStatistics);
double getUStotalScore(const UserStatistics *userStatistics);
double getUStotalExpense(const UserStatistics *userStatistics);
double getUStotalTrips(const UserStatistics *userStatistics);
double getUStotalTipsExpense(const UserStatistics *userStatistics);
void destroyUserStatistics(void *us);

#endif
