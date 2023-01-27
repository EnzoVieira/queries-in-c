#include "includes/database.h"
#include "includes/interactive.h"

#include <stdio.h>
#include <stdlib.h>

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
  
  // TODO: Criar pasta de resultados

  return 0;
}
