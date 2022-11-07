#include "../../../includes/userRepository.h"

struct user
{
  char *user_name;
  char *name;
  char gender;
  char *birth_date;
  char *account_creation;
  char *pay_method;
  char *account_status;
};

char* getUUsername(User *u) {
    return strdup(u->user_name);
}

char* getUName(User *u) {
  return strdup(u->name);
}

char getUGender(User *u) {
  return u->gender;
}

char* getUBirthDate(User *u) {
  return strdup(u->birth_date);
}

char* getUAccountCreation(User *u) {
  return strdup(u->account_creation);
}

char* getUPayMethod(User *u) {
  return strdup(u->pay_method);
}

char* getUAccountStatus(User *u) {
  return strdup(u->account_status);
}


void *createUsersHashData()
{
  // Cria a HashTable
  void *hashTable = createTable();

  FILE *fp;
  fp = fopen("files/data/users.csv", "r");

  if (fp == NULL)
  {
    printf("Falha ao ler o file\n");
  }

  char *line = NULL;
  size_t len;

  getline(&line, &len, fp);

  while (((getline(&line, &len, fp)) != -1))
  {

    User *user = (User *)malloc(sizeof(User));

    user->user_name = strsep(&line, ";");
    user->name = strsep(&line, ";");
    user->gender = *strsep(&line, ";");
    user->birth_date = strsep(&line, ";");
    user->account_creation = strsep(&line, ";");
    user->pay_method = strsep(&line, ";");
    user->account_status = strsep(&line, ";");

    // insere a key user->user_name e a data user na hash
    addToTable(hashTable, user->user_name, user);
  }

  free(line);
  fclose(fp);

  return hashTable;
}

/*
User* cloneUser(User *u) {
  User* copy = malloc(sizeof(User));
  copy->user_name = strdup(u->user_name);
  copy->name = strdup(u->name);
  copy->gender = u->gender;
  copy->birth_date = strdup(u->birth_date);
  copy->account_creation = strdup(u->pay_method);
  copy->pay_method = strdup(u->pay_method);
  copy->account_status = strdup(u->account_status);

  return copy;
}
*/

User* findUserByUsername(GHashTable *users, char* username) {
  return(g_hash_table_lookup(users, username));
}
