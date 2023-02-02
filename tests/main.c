#include "../includes/database.h"
#include "../includes/strings.h"
#include "../includes/terminal.h"
#include "../includes/reader.h"

#include "includes/testQuery1.h"
#include "includes/testQuery2.h"
#include "includes/testQuery3.h"
#include "includes/testQuery4.h"
#include "includes/testQuery5.h"
#include "includes/testQuery6.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void func(const char *path, char *line, unsigned int *index) {
  char *token = NULL;

  removeNewLine(line);

  char delim[] = " ";
  token = strtok(line, delim);

  char queryNumber = token[0];

  // print do número do input
  resetColor();
  printf("%d ", (*index)+1);

  char *pathCopy = strdup(path);
  // Apaga os caracteres do final até encontrar um /
  eraseUntilFind(pathCopy, '/');
  
  char *filename = calloc(strlen(pathCopy) + strlen("commandX_output.txt") + 1, sizeof(char));
  sprintf(filename, "%scommand%d_output.txt", pathCopy, (*index) + 1);

  switch (queryNumber) {
    case '1': {
      token = strtok(NULL, delim);

      testQuery1(filename, token);

      break;
    }

    case '2': {
      token = strtok(NULL, delim);

      testQuery2(filename, token);

      break;
    }

    case '3': {
      token = strtok(NULL, delim);

      testQuery3(filename, token);

      break;
    }

    case '4': {
      token = strtok(NULL, delim);

      testQuery4(filename, token);

      break;
    }

    case '5': {
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);

      testQuery5(filename, date1, date2);

      break;
    }

    case '6': {
      char *city = strtok(NULL, delim);
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);

      testQuery6(filename, city, date1, date2);

      break;
    }

    default:
      printf("\n");
      break;
  }

  free(filename);
}

// FIXME: Arrumar organização dos testes
int main(int argc, char *argv[]) {
  seedDatabase(argv[1]);

  FILE *fp = openFile(argv[2]);

  char *line = NULL;

  unsigned int index = 0;
  while (readLine(&line, fp) != -1) {
    func(argv[2], line, &index);
    index++;
  }

  fclose(fp);
  free(line);

  return 0;
}
