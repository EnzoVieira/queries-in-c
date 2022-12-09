#include "../../../includes/userRepository.h"

#include "../../../includes/api.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct user {
  char *user_name;
  char *name;
  char gender;
  char *birth_date;
  char *account_creation;
  char *pay_method;
  int  account_status;
  List *userRidesId;
};

// ============================
//       private methods
// ============================

User *getUserCopy(User *user) {
  User *userCopy = calloc(1, sizeof(User));

  userCopy->user_name = strdup(user->user_name);
  userCopy->name = strdup(user->name);
  userCopy->gender = user->gender;
  userCopy->birth_date = strdup(user->birth_date);
  userCopy->account_creation = strdup(user->account_creation);
  userCopy->pay_method = strdup(user->pay_method);
  userCopy->account_status = user->account_status;
  userCopy->userRidesId = copyList(user->userRidesId);

  return userCopy;
}

// ============================
//       public methods
// ============================

User *createUser(const char *line) {
  User *user = calloc(1, sizeof(User));

  char *lineCopy = strdup(line);

  user->user_name = strdup(strsep(&lineCopy, ";"));
  user->name = strdup(strsep(&lineCopy, ";"));
  user->gender = *strsep(&lineCopy, ";");
  user->birth_date = strdup(strsep(&lineCopy, ";"));
  user->account_creation = strdup(strsep(&lineCopy, ";"));
  user->pay_method = strdup(strsep(&lineCopy, ";"));
  
  if (*(strsep(&lineCopy, ";")) == 'a')
    user->account_status = 1;
  else 
    user->account_status = 0;
  
  free(lineCopy);
  return user;
}

HashTable *userHashTableSingleton() {
  static HashTable *usersHashTable = NULL;

  if (usersHashTable == NULL) {
    usersHashTable = createHashTable();
  }

  return usersHashTable;
}

void addUser(User *newUser) {
  HashTable *userHashTable = userHashTableSingleton();

  addToTable(userHashTable, newUser->user_name, (Pointer) newUser);
}

// Always returns a copy when user exists
User *findUserByUsername(const char *username) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*) findById(userHashTable, username);

  if (userFinded) {
    return getUserCopy(userFinded);
  }

  return NULL;
}

char *getUUsername(const User *user) {
  return strdup(user->user_name);
}

char *getUName(const User *user) {
  return strdup(user->name);
}

char* getUBirthDate(const User *user) {
  return strdup(user->birth_date);
}

char *getUAccountCreation(const User *user) {
  return strdup(user->account_creation);
}

char *getUPayMethod(const User *user) {
  return strdup(user->pay_method);
}

int getUAccountStatus(const User *user) {
  return user->account_status;
}


// Function to add a rideId to a user->userRidesId list
void addUserRide(const char *username, const char *rideId) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*) findById(userHashTable, username);

  userFinded->userRidesId = addToList(userFinded->userRidesId, strdup(rideId));
}

void printUser(User *user) {
  printf("username: %s\n", user->user_name);
  printList(user->userRidesId);
}
