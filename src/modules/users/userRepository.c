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
  char *pay_method;
  int  account_status;
  char *last_ride;
  List *userRidesId;
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
  userCopy->pay_method = strdup(user->pay_method);
  userCopy->account_status = user->account_status;
  userCopy->userRidesId = copyList(user->userRidesId);
  userCopy->last_ride = strdup(user->last_ride);

  

  return userCopy;
}

void userDestroy (User *user){

  if (user){
    if (user->name)
      free(user->name);
    if (user->birth_date)
      free(user->birth_date);
    if (user->account_creation)
      free(user->account_creation);
    if (user->pay_method)
      free(user->pay_method);
  }
  //destroyME = NULL;
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
  user->pay_method = strdup(strsep(&lineCopy, ";"));  
  if (*(strsep(&lineCopy, ";")) == 'a')
    user->account_status = 1;
  else 
    user->account_status = 0;
  user->last_ride = "00/00/0000";
  
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
  foreachLineOfFile(path, &addUser);
}

HashTable *userHashTableSingleton() {
  static HashTable *usersHashTable = NULL;

  if (usersHashTable == NULL) {
    usersHashTable = createHashTable();
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

// Function to add a rideId to a user->userRidesId list
void addUserRide(const char *username, const char *rideId) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*)findById(userHashTable, username);

  userFinded->userRidesId = addToList(userFinded->userRidesId, strdup(rideId));
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

char *getUPayMethod(const User *user) {
  return strdup(user->pay_method);
}

int getUAccountStatus(const User *user) {
  return user->account_status;
}

List *getUserRidesList(const User *user) {
  return copyList(user->userRidesId);
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
    if (user->pay_method)
      free(user->pay_method);
    if (user->last_ride)
      free(user->last_ride);

    freeListOfStrings(user->userRidesId);
    user = NULL;
  }
}
