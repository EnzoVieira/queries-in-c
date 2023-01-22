#include "../includes/userRepository.h"
#include "../includes/driverRepository.h"
#include "../includes/rideRepository.h"

// APAGAR DEPOIS
#include "../includes/query1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_NORMAL "\033[0m"

// Mover para outro lugar
#include "../includes/reader.h"

void removeNewLine(char *line) {
  unsigned int len = strlen(line);

  len--;
  if (line[len] == '\n') { 
    line[len] = 0;
  }
}

int assertResult(char *result, const char *confirmResultPath, char **expectedResult) {
  char *content = readFile(confirmResultPath);

  // Copia o valor de content se for diferente de NULL
  if (content != NULL) {
    *expectedResult = calloc(strlen(content), sizeof(char));
    *expectedResult = content;
  }

  if (result == NULL) {
    return content == NULL;
  }

  if (content == NULL) {
    return result == NULL;
  }

  return strcmp(result, content) == 0;
}

void func(char *line, unsigned int *index) {
  char *token = NULL;
  char *result = NULL;

  removeNewLine(line);

  char delim[] = " ";
  token = strtok(line, delim);

  char queryNumber = strdup(token)[0];

  // print do número do input
  printf("%s%d ", AC_NORMAL, (*index)+1);

  char *filename = calloc(strlen("config/inputs/inputs2/commandX_output.txt"), sizeof(char));
  sprintf(filename, "config/inputs/inputs2/command%d_output.txt", (*index) + 1);

  switch (queryNumber) {
    case '1': {
      token = strtok(NULL, delim);
      result = q1(token);
      char *expectedResult = NULL;

      if (assertResult(result, filename, &expectedResult)) {
        printf("%squery1(%s)\n", AC_GREEN, token);
      } else {
        printf("%squery1(%s)\n\n", AC_RED, token);

        printf("expected:\n\n");
        printf("\t%s\n\n", expectedResult);


        printf("got:\n\n");
        printf("\t%s\n\n", result);
      }


      break;
    }

    default:
      printf("\n");
      break;
  }

}

int main() {
  createUsersHashTable("config/data/users.csv");
  createDriversHashTable("config/data/drivers.csv");
  // A tabela de rides precisa ser a última a ser criada.
  createRidesHashTable("config/data/rides.csv");

  FILE *fp = openFile("config/inputs/inputs2/input.txt");

  char *line = NULL;

  unsigned int index = 0;
  while (readLine(&line, fp) != -1) {
    func(line, &index);
    index++;
  }

  fclose(fp);

  return 0;
}
