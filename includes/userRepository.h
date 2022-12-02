#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "api.h"

typedef struct user User;

char *getUUsername(User *u);
char *getUName(User *u);
char getUGender(User *u);
char *getUBirthDate(User *u);
char *getUAccountCreation(User *u);
char *getUPayMethod(User *u);
int getUAccountStatus(User *u);

User *findUserByUsername(HashTable *users, char *username);
int getUserAge(User *user);

#endif
