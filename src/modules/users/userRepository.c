#include "../../../includes/userRepository.h"

#include "../../../includes/reader.h"
#include "../../../includes/validations.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_FIELD_LEN 100

struct user {
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

int isValidUser(const char *line) {
  char username[MAX_FIELD_LEN], name[MAX_FIELD_LEN], gender[2], birthDay[11], accountCreation[11], pay_method[MAX_FIELD_LEN], accountStatus[9];

  int fields = sscanf(line, "%[^;];%[^;];%1[^;];%10[^;];%10[^;];%[^;];%[^\n]", username, name, gender, birthDay, accountCreation, pay_method, accountStatus);
  // Falha na conversão
  if (fields != 7) {
    return 0;
  }

  int isCorrect = isValidDate(birthDay) &&
                  isValidDate(accountCreation) &&
                  isValidAccountStatus(accountStatus);

  return isCorrect;
}

// ============================
//       public methods
// ============================

User *createUser(char *line) {
  User *user = calloc(1, sizeof(User));

  user->name = strdup(strsep(&line, ";"));
  user->gender = *strsep(&line, ";");
  user->birth_date = strdup(strsep(&line, ";"));
  user->account_creation = strdup(strsep(&line, ";"));
  strsep(&line, ";");

  char *status = strdup(strsep(&line, ";"));
  if (*status == 'a' || *status == 'A')
    user->account_status = 1;
  else 
    user->account_status = 0;
  user->last_ride = calloc(11,sizeof(char));
  
  free(status);
  return user;
}

void addUser(char *line) {
  HashTable *userHashTable = userHashTableSingleton();
  
  //char* lineCopy = strdup(line);
  char* username = strdup(strsep(&line, ";"));

  User *newUser = createUser(line);

  addToTable(userHashTable, username, (Pointer) newUser);
}

void createUsersHashTable(const char *path) {
  foreachLineOfFile(path, &addUser, &isValidUser);
}

HashTable *userHashTableSingleton() {
  static HashTable *usersHashTable = NULL;

  if (usersHashTable == NULL) {
    usersHashTable = createHashTable(&destructUserCopy);
  }

  return usersHashTable;
}

void addUserLastRide(const char *username, const char *date) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*)findById(userHashTable, username);
  free (userFinded->last_ride);
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


char *getUNameNew(char *username) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*)findById(userHashTable, username);

  return strdup(userFinded->name);
}

char getUGenderNew(char *username) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*)findById(userHashTable, username);

  return userFinded->gender;
}

char *getUBirthDateNew(char *username) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*)findById(userHashTable, username);

  return strdup(userFinded->birth_date);
}

char *getUAccountCreationNew(char *username) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*)findById(userHashTable, username);

  return strdup(userFinded->account_creation);
}

int getUAccountStatusNew(char *username) {
  
  HashTable *userHashTable = userHashTableSingleton();
  User *userFinded = (User*)findById(userHashTable, username);

  if(!userFinded)
    return 0;

  return userFinded->account_status;
}

char *getULastRideNew(char *username) {
  HashTable *userHashTable = userHashTableSingleton();

  User *userFinded = (User*)findById(userHashTable, username);

  return strdup(userFinded->last_ride);
}