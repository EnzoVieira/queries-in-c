#include "../../includes/reader.h"

#include <stdlib.h>
#include <string.h>

// Confirma se o resultado está igual ao encontrado em `confirmResultPath`
// e coloca dentro de `expectedResult` o resultado esperado
int assertResult(char *result, const char *confirmResultPath, char **expectedResult) {
  char *content = readFile(confirmResultPath);

  // Copia o valor de content se for diferente de NULL
  if (content != NULL) {
    *expectedResult = calloc(strlen(content) + 1, sizeof(char));
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
