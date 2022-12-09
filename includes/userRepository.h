#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "./api.h"

typedef struct user User;

User *createUser(const char *username, const char* name, int age);
HashTable *userHashTableSingleton();
void addUser(User *newUser);
// Always returns a copy when user exists
User *findUserByUsername(const char *username);

// ============================
//           GETTERS
// ============================

char *getUsername(const User *user);
char *getUName(const User *user);
int getUserAge(const User *user);

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
