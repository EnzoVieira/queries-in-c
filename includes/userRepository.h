#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "api.h"
#include "userEntity.h"

void *createUsersHashData();
User* cloneUser(User *u);

#endif