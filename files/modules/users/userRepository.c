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

void *createUsersHashData(const char *path) {
  // Cria a HashTable
  void *hashTable = createTable();

  char *userCSVPath = calloc(strlen(path) + strlen("/users.csv") + 2, sizeof(char));
  sprintf(userCSVPath, "%s/users.csv", path);

  FILE *fp;
  fp = fopen(userCSVPath, "r");

  if (fp == NULL)
  {
    printf("Falha ao ler o file\n");
  }

  char *line = NULL;
  size_t len;

  getline(&line, &len, fp);

  while (((getline(&line, &len, fp)) != -1)) {
    User *user = (User *)malloc(sizeof(User));

    user->user_name = strdup(strsep(&line, ";"));
    user->name = strdup(strsep(&line, ";"));
    user->gender = *strsep(&line, ";");
    user->birth_date = strdup(strsep(&line, ";"));
    user->account_creation = strdup(strsep(&line, ";"));
    user->pay_method = strdup(strsep(&line, ";"));

    if (*(strsep(&line, ";")) == 'a')
      user->account_status = 1;
    else 
      user->account_status = 0;

    // insere a key user->user_name e a data user na hash
    addToTable(hashTable, user->user_name, user);
  }

  free(line);
  fclose(fp);

  return hashTable;
}

User *findUserByUsername(GHashTable *users, char *username) {
  return g_hash_table_lookup(users, username);
}
