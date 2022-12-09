#include "../../../includes/userRepository.h"

#include "../../../includes/api.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct user {
  char *username;
  char *name;
  int age;

  List *userRidesId;
};

// ============================
//       private methods
// ============================

User *getUserCopy(User *user) {
  User *userCopy = calloc(1, sizeof(User));

  userCopy->username = strdup(user->username);
  userCopy->name = strdup(user->name);
  userCopy->age = user->age;
  userCopy->userRidesId = copyList(user->userRidesId);

  return userCopy;
}

// ============================
//       public methods
// ============================

User *createUser(const char *username, const char* name, int age) {
  User *user = calloc(1, sizeof(User));

  user->username = strdup(username);
  user->name = strdup(name);
  user->age = age;
  user->userRidesId = NULL;

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

  addToTable(userHashTable, newUser->username, (Pointer) newUser);
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

char *getUsername(const User *user) {
  return strdup(user->username);
}

char *getUName(const User *user) {
  return strdup(user->name);
}

int getUserAge(const User *user) {
  return user->age;
}

// Function to add a rideId to a user->userRidesId list
void addUserRide(const char *username, const char *rideId) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*) findById(userHashTable, username);

  userFinded->userRidesId = addToList(userFinded->userRidesId, strdup(rideId));
}

void printUser(User *user) {
  printf("username: %s\n", user->username);
  printList(user->userRidesId);
}
