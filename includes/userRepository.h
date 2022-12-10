#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "./api.h"

typedef struct user User;

User *createUser(const char *line);
void addUser(char *line);
void createUsersHashTable(const char *path);
HashTable *userHashTableSingleton();
// Always returns a copy when user exists
User *findUserByUsername(const char *username);
// Function to add a rideId to a user->userRidesId list
void addUserRide(const char *username, const char *rideId);

// ============================
//           GETTERS
// ============================

char *getUName(const User *user) ;
char* getUBirthDate(const User *user);
char *getUAccountCreation(const User *user) ;
char *getUPayMethod(const User *user);
int getUAccountStatus(const User *user);

// ============================
//           UTILS
// ============================

void printUser(User *user);

#endif
