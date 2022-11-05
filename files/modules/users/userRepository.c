#include "../../../includes/userRepository.h"

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