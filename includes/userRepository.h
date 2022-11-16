#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "api.h"
#include "userEntity.h"

void *createUsersHashData(const char *path);
User *findUserByUsername(GHashTable *users, char *username);

#endif
