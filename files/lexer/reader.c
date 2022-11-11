#include "../../includes/reader.h"

char *readFile(const char *filename) {
  FILE *fp;
  char *line = NULL;
  size_t length = 0;
  ssize_t read;

  fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("Não foi possível ler o ficheiro %s\n", filename);
    exit(1);
  }

  char *buffer = calloc(1, sizeof(char));
  buffer[0] = '\0';

  while((read = getline(&line, &length, fp)) != -1) {
    buffer = realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
    strcat(buffer, line);
  }

  fclose(fp);

  if(line)
    free(line);
  
  return buffer;
}