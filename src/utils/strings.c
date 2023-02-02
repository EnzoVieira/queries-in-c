#include "../../includes/strings.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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

void eraseUntilFind(char *str, char delim) {
  unsigned int len = strlen(str);

  len--;
  while ( str[len] != delim ) {
    str[len] = 0;
    len--;
  }
}

char *toLowerCase(const char *str) {
  int i, len = strlen(str);
  char *lower = malloc((len + 1) * sizeof(char));

  for (i = 0; i < len; i++) {
    lower[i] = tolower(str[i]);
  }
  lower[len] = '\0';

  return lower;
}
