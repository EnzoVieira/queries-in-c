#include "../../includes/writer.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

int *getResultIndex() {
  static int currentResultIndex = 1;

  return &currentResultIndex;
}

void advanceResultIndex() {
  int *currentIndex = getResultIndex();

  (*currentIndex) += 1;
}

void writeResultFile(const char *args) {
  DIR* dir = opendir("Resultados");

  if (dir) {
      // Directory exists.
      closedir(dir);
  } else if (ENOENT == errno) {
      // Directory does not exist.
      mkdir("Resultados", 0777);
  } else {
      // opendir() failed for some other reason.
      printf("Não foi possível abrir o diretório Resultados\n");
  }

  // Escreve no ficheiro de resultados

  char *filenameAux1 = "Resultados/command";
	char *filenameAux2 = "_output.txt";
	size_t filenameLength = strlen(filenameAux1) + strlen(filenameAux2) + 2;
	char *filename = calloc(filenameLength, sizeof(char));

  int currentIndex = *(getResultIndex());
  sprintf(filename, "%s%d%s", filenameAux1, currentIndex, filenameAux2);

  FILE *fp = fopen(filename, "a");
  if (fp == 0) {
    printf("Não foi possível abrir o ficheiro %s\n", filename);
    exit(1);
  }

  if (args != NULL) 
    fprintf(fp, "%s", args);

  fclose(fp);
}
