#include "includes/database.h"
#include "includes/interactive.h"
#include "includes/reader.h"
#include "includes/writer.h"
#include "includes/strings.h"

#include "includes/query1.h"
#include "includes/query2.h"
#include "includes/query3.h"
#include "includes/query4.h"
#include "includes/query5.h"
#include "includes/query6.h"
#include "includes/query7.h"
#include "includes/query8.h"
#include "includes/query9.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(const char *line, unsigned int *index) {
  char *token = NULL;
  char *linecopy = strdup(line);
  removeNewLine(linecopy);

  char delim[] = " ";
  token = strtok(linecopy, delim);

  char queryNumber = token[0];

  switch (queryNumber) {

    case '1': {
      token = strtok(NULL, delim);

      q1(token);

      break;
    }

    case '2': {
      token = strtok(NULL, delim);

      q2(atoi(token));

      break;
    }
 
    case '3': {
      token = strtok(NULL, delim);

      q3(atoi(token));

      break;
    }

    case '4': {
      token = strtok(NULL, delim);

      q4(token);

      break;
    }

    case '5': {
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);

      q5(date1, date2);

      break;
    }

    case '6': {
      char *city = strtok(NULL, delim);
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);

      q6(city, date1, date2);

      break;
    }

    case '7': {
      char *N = strtok(NULL, delim);
      char *city = strtok(NULL, delim);

      q7(atoi(N), city);

      break;
    }

    case '8': {
      char *gender = strtok(NULL, delim);
      char *years = strtok(NULL, delim);

      q8(*gender, atoi(years));

      break;
    }

    // case '9': {
    //   char *date1 = strtok(NULL, delim);
    //   char *date2 = strtok(NULL, delim);

    //   q9(date1, date2);

    //   break;
    // }
  }

  free(linecopy);
}

int main(int argc, char *argv[]) {
  // Programa executado com 1 ou mais de 3 argumentos
  if (argc == 2 || argc > 3) {
    printf("Argumentos inválidos\n");
    exit(1);
  }

  // Programa executado sem argumentos
  if (argc == 1) {
    interactiveMode();

    destroyDatabase();
    return 0;
  }

  seedDatabase(argv[1]);

  // Criar pasta de resultados
  FILE *fp = openFile(argv[2]);

  char *line = NULL;

  unsigned int index = 0;
  while(readLine(&line, fp) != -1) {
    func(line, &index);
    free(line);
    line=NULL;
    index++;
  }

  destroyDatabase();

  return 0;
}
