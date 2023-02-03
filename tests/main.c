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
#include "includes/testQuery7.h"
#include "includes/testQuery8.h"
#include "includes/testQuery9.h"

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

  switch (queryNumber) {
    case '1': {
      token = strtok(NULL, delim);

      testQuery1(path, token);

      break;
    }

    case '2': {
      token = strtok(NULL, delim);

      testQuery2(path, token);

      break;
    }

    case '3': {
      token = strtok(NULL, delim);

      testQuery3(path, token);

      break;
    }

    case '4': {
      token = strtok(NULL, delim);

      testQuery4(path, token);

      break;
    }

    case '5': {
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);

      testQuery5(path, date1, date2);

      break;
    }

    case '6': {
      char *city = strtok(NULL, delim);
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);

      testQuery6(path, city, date1, date2);

      break;
    }

    case '7': {
      char *N = strtok(NULL, delim);
      char *city = strtok(NULL, delim);

      testQuery7(path, atoi(N), city);

      break;
    }

    case '8': {
      char *gender = strtok(NULL, delim);
      char *years = strtok(NULL, delim);

      testQuery8(path, *gender, atoi(years));

      break;
    }

    case '9': {
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);

      testQuery9(path, date1, date2);

      break;
    }

    default:
      printf("\n");
      break;
  }

  // free(filename);
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
