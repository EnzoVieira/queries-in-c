#include "../../includes/reader.h"

#include <stdlib.h>

FILE *openFile(const char *path) {
  FILE *fp;
  fp = fopen(path, "r");

  if (fp == NULL) {
    printf("Falha ao ler o file %s\n", path);
    exit(1);
  }

  return fp;
}

int readLine(char **buffer, FILE *fp) {
  size_t len;

  return getline(buffer, &len, fp);
}

void foreachLineOfFile(const char *path, void(*func)(char *line)) {
  FILE *fp = openFile(path);

  char *line = NULL;

  // Pula primeira linha
  readLine(&line, fp);

  while (readLine(&line, fp) != -1) {
    func(line);
  }

  free(line);
  fclose(fp);
}
