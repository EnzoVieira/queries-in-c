#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "./api.h"

typedef struct user User;

User *createUser(const char *line);
HashTable *userHashTableSingleton();
void addUser(User *newUser);
// Always returns a copy when user exists
User *findUserByUsername(const char *username);

// ============================
//           GETTERS
// ============================

char *getUUsername(const User *user);
char *getUName(const User *user);
char* getUBirthDate(const User *user);
char *getUAccountCreation(const User *user);
char *getUPayMethod(const User *user);
int getUAccountStatus(const User *user);

// ============================
//           SETTERS
// ============================

// Function to add a rideId to a user->userRidesId list
void addUserRide(const char *username, const char *rideId);

// ============================
//           UTILS
// ============================

void printUser(User *user);

#endif
