#include "../../includes/strings.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *concatStrings(const char *str1, const char *str2) {
  char *concat = calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));

  sprintf(concat, "%s%s", str1, str2);

  return concat;
}

void removeNewLine(char *line) {
  unsigned int len = strlen(line);

  len--;
  if (line[len] == '\n') { 
    line[len] = 0;
  }
}
