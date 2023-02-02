#include "../../../includes/userRepository.h"

#include "../../../includes/reader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct user {
  //char *user_name;
  char *name;
  char gender;
  char *birth_date;
  char *account_creation;
  int  account_status;
  char *last_ride;
};

// ============================
//       private methods
// ============================

User *getUserCopy(User *user) {
  User *userCopy = calloc(1, sizeof(User));

  //userCopy->user_name = strdup(user->user_name);
  userCopy->name = strdup(user->name);
  userCopy->gender = user->gender;
  userCopy->birth_date = strdup(user->birth_date);
  userCopy->account_creation = strdup(user->account_creation);
  userCopy->account_status = user->account_status;
  userCopy->last_ride = strdup(user->last_ride);

  

  return userCopy;
}

// ============================
//       public methods
// ============================

User *createUser(const char *line) {
  User *user = calloc(1, sizeof(User));

  char *lineCopy = strdup(line);

  //user->user_name = strdup(strsep(&lineCopy, ";"));
  user->name = strdup(strsep(&lineCopy, ";"));
  user->gender = *strsep(&lineCopy, ";");
  user->birth_date = strdup(strsep(&lineCopy, ";"));
  user->account_creation = strdup(strsep(&lineCopy, ";"));
  strdup(strsep(&lineCopy, ";"));  
  if (*(strsep(&lineCopy, ";")) == 'a')
    user->account_status = 1;
  else 
    user->account_status = 0;
  user->last_ride = calloc(11,sizeof(char));
  
  free(lineCopy);
  return user;
}

void addUser(char *line) {
  HashTable *userHashTable = userHashTableSingleton();
  
  char* lineCopy = strdup(line);
  char* username = strdup(strsep(&lineCopy, ";"));

  User *newUser = createUser(lineCopy);

  addToTable(userHashTable, username, (Pointer) newUser);
}

void createUsersHashTable(const char *path) {
  foreachLineOfFile(path, &addUser, NULL);
}

HashTable *userHashTableSingleton() {
  static HashTable *usersHashTable = NULL;

  if (usersHashTable == NULL) {
    usersHashTable = createHashTable2(&destructUserCopy);
  }

  return usersHashTable;
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

void addUserLastRide(const char *username, const char *date) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*)findById(userHashTable, username);

  userFinded->last_ride = strdup(date);
}

// ============================
//           GETTERS
// ============================

char *getUName(const User *user) {
  return strdup(user->name);
}

char getUGender(const User *user) {
  return user->gender;
}

char* getUBirthDate(const User *user) {
  return strdup(user->birth_date);
}

char *getUAccountCreation(const User *user) {
  return strdup(user->account_creation);
}

int getUAccountStatus(const User *user) {
  return user->account_status;
}

char *getULastRide(const User *user) {
  return strdup(user->last_ride);
}

void destructUserCopy(void *u){
  User *user = (User*)u; 
  
  if(user){
    if (user->name)
      free(user->name);
    if (user->birth_date)
      free(user->birth_date);
    if (user->account_creation)
      free(user->account_creation);
    if (user->last_ride)
      free(user->last_ride);
    free(user);
  }
}
