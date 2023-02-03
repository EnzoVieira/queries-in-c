#include "../../includes/reader.h"

#include <stdlib.h>
#include <string.h>

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
  size_t len = 0;

  return getline(buffer, &len, fp);
}

// Retorna o conteúdo de um ficheiro.
// Caso ele esteja vazio (i.e. 0 bytes), retorna NULL.
char *readFile(const char *filename) {
  FILE *fp;
  char *line = NULL;

  fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("Não foi possível ler o ficheiro %s\n", filename);
    free(line);
    exit(1);
  }

  char *buffer = calloc(1, sizeof(char));
  buffer[0] = '\0';

  while(readLine(&line, fp) != -1) {
    buffer = realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
    strcat(buffer, line);
    free(line);
    line = NULL;
  }

  fclose(fp);

  // Caso o buffer tenha apenas um '\0', significa que o ficheiro está vazio, logo, retorne NULL
  if (strcmp(buffer, "\0") == 0){
    free(buffer);
    return NULL;
  }
  
  return buffer;
}

void foreachLineOfFile(const char *path, void (*func) (char *line), int (*validation) (const char *line)) {
  FILE *fp = openFile(path);

  char *line = NULL;

  // Pula primeira linha
  readLine(&line, fp);

  while (readLine(&line, fp) != -1) {
    // Se receber uma função de validação
    if (validation != NULL)
      // Valida se a linha é válida, caso não seja, avança para a próxima
      if (!validation(line)) continue;

    func(line);
    free(line);
    line=NULL;
  }

  fclose(fp);
}
