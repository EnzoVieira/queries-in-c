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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(char *line, unsigned int *index) {
  char *token = NULL, *result = NULL;

  removeNewLine(line);

  char delim[] = " ";
  token = strtok(line, delim);

  char queryNumber = strdup(token)[0];

	char *filenameAux1 = "Resultados/command";
	char *filenameAux2 = "_output.txt";
	size_t filenameLength = strlen(filenameAux1) + strlen(filenameAux2) + 2;
	char *filename = calloc(filenameLength, sizeof(char));


  sprintf(filename, "%s%d%s", filenameAux1, (*index)+1, filenameAux2);

  switch (queryNumber) {

    case '1': {
      token = strtok(NULL, delim);
      result = q1(token);

      writeFile(result, filename);
      if (result != NULL) {
        free(result);
      }

      break;
    }

    case '2': {
      token = strtok(NULL, delim);
      result = q2(atoi(token));

      writeFile(result, filename);
      if (result != NULL) {
        free(result);
      }

      break;
    }

    case '3': {
      token = strtok(NULL, delim);
      result = q3(atoi(token));

      writeFile(result, filename);
      if (result != NULL) {
        free(result);
      }

      break;
    }

    case '4': {
      token = strtok(NULL, delim);
      result = q4(token);

      writeFile(result, filename);
      if (result != NULL) {
        free(result);
      }

      break;
    }

    case '5': {
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);
      result = q5(date1, date2);

      writeFile(result, filename);
      if (result != NULL) {
        free(result);
      }

      break;
    }

    case '6': {
      char *city = strtok(NULL, delim);
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);
      result = q6(city, date1, date2);

      writeFile(result, filename);
      if (result != NULL) {
        free(result);
      }

      break;
    }
  }
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

    return 0;
  }

  seedDatabase(argv[1]);
  
  // Criar pasta de resultados
  FILE *fp = openFile(argv[2]);

  char *line = NULL;

  unsigned int index = 0;
  while(readLine(&line, fp) != -1) {
    func(line, &index);
    index++;
  }

  return 0;
}
