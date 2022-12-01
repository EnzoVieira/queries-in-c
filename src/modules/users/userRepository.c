#include "../../../includes/userRepository.h"

struct user {
  char *user_name;
  char *name;
  char gender;
  char *birth_date;
  char *account_creation;
  char *pay_method;
  int  account_status;
};

char *getUUsername(User *u) {
  return strdup(u->user_name);
}

char *getUName(User *u) {
  return strdup(u->name);
}

char getUGender(User *u) {
  return u->gender;
}

char *getUBirthDate(User *u) {
  return strdup(u->birth_date);
}

char *getUAccountCreation(User *u) {
  return strdup(u->account_creation);
}

char *getUPayMethod(User *u) {
  return strdup(u->pay_method);
}

int getUAccountStatus(User *u) {
  return u->account_status;
}

User *findUserByUsername(HashTable* users, char* username) {
  return findBy(users, username);
}

int getUserAge(User *user) {
  char *userBirthDate = getUBirthDate(user);

  return dateDifference(dateConvert(userBirthDate));
}
