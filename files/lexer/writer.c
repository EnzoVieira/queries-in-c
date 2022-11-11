#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

#include "../../includes/writer.h"

void writeFile(const char *args, const char *filename) {
  DIR* dir = opendir("Resultados");
  if (dir) {
      /* Directory exists. */
      closedir(dir);
  } else if (ENOENT == errno) {
      /* Directory does not exist. */
      mkdir("Resultados", 0777);
  } else {
      /* opendir() failed for some other reason. */
      printf("Não foi possível abrir o diretório Resultados\n");
  }

  FILE *fp;

  fp = fopen(filename, "a");
  if (fp == 0) {
    printf("Não foi possível abrir o ficheiro %s\n", filename);
    exit(1);
  }

  fprintf(fp, "%s", args);

  fclose(fp);
}