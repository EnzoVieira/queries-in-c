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
void addUserLastRide(const char *username, const char *date);

// ============================
//           GETTERS
// ============================

char *getUName(const User *user) ;
char getUGender(const User *user);
char* getUBirthDate(const User *user);
char *getUAccountCreation(const User *user) ;
int getUAccountStatus(const User *user);
char *getULastRide(const User *user);
void destructUserCopy(void *user);

#endif
