#include "../includes/database.h"
#include "../includes/strings.h"
#include "../includes/terminal.h"
#include "../includes/reader.h"

// Mover para outro lugar
#include "../includes/query1.h"
#include "../includes/query4.h"
#include "../includes/query5.h"
#include "../includes/query6.h"
#include "../includes/query7.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
  resetColor();
  printf("%d ", (*index)+1);

  char *filename = calloc(strlen("config/inputs/inputs2/commandX_output.txt"), sizeof(char));
  sprintf(filename, "config/inputs/inputs2/command%d_output.txt", (*index) + 1);

  switch (queryNumber) {
    case '1': {
      token = strtok(NULL, delim);
      result = q1(token);
      char *expectedResult = NULL;

      if (assertResult(result, filename, &expectedResult)) {
        greenColor();
        printf("query1(%s)\n", token);
      } else {
        redColor();
        printf("query1(%s)\n\n", token);

        printf("expected:\n\n");
        printf("\t%s\n\n", expectedResult);

        printf("got:\n\n");
        printf("\t%s\n\n", result);
      }

      break;
    }

    case '4': {
      token = strtok(NULL, delim);
      result = q4(token);
      char *expectedResult = NULL;

      if (assertResult(result, filename, &expectedResult)) {
        greenColor();
        printf("query4(%s)\n", token);
      } else {
        redColor();
        printf("query4(%s)\n\n", token);

        printf("expected:\n\n");
        printf("\t%s\n\n", expectedResult);

        printf("got:\n\n");
        printf("\t%s\n\n", result);
      }

      break;
    }

    case '5': {
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);
      result = q5(date1, date2);
      char *expectedResult = NULL;

      if (assertResult(result, filename, &expectedResult)) {
        greenColor();
        printf("query5(%s, %s)\n", date1, date2);
      } else {
        redColor();
        printf("query5(%s, %s)\n\n", date1, date2);

        printf("expected:\n\n");
        printf("\t%s\n\n", expectedResult);

        printf("got:\n\n");
        printf("\t%s\n\n", result);
      }

      break;
    }

    case '6': {
      char *city = strtok(NULL, delim);
      char *date1 = strtok(NULL, delim);
      char *date2 = strtok(NULL, delim);
      result = q6(city, date1, date2);
      char *expectedResult = NULL;

      if (assertResult(result, filename, &expectedResult)) {
        greenColor();
        printf("query6(%s, %s, %s)\n", city, date1, date2);
      } else {
        redColor();
        printf("query6(%s, %s, %s)\n\n", city, date1, date2);

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

// FIXME: Arrumar organização dos testes
int main(int argc, char *argv[]) {
  seedDatabase(argv[1]);

  FILE *fp = openFile(argv[2]);

  char *line = NULL;

  unsigned int index = 0;
  while (readLine(&line, fp) != -1) {
    func(line, &index);
    index++;
  }

  fclose(fp);

  return 0;
}
