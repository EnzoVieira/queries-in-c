#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "api.h"
#include "date.h"

#include "userEntity.h"

typedef struct user User;

User *findUserByUsername(HashTable *users, char *username);
int getUserAge(User *user);

#endif
