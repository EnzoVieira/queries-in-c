#include "../../includes/reader.h"

#include "../../includes/strings.h"

#include <stdlib.h>
#include <string.h>

// Confirma se o resultado está igual ao encontrado em `confirmResultPath`
// e coloca dentro de `result` e `expectedResult` o resultado obtido e o esperado respetivamente
int assertResult(const char *path, char **result, char **expectedResult) {
  static int currentIndex = 1;

  char *pathCopy = strdup(path);
  // Apaga os caracteres do final até encontrar um /
  eraseUntilFind(pathCopy, '/');
  
  char *confirmResultPath = calloc(strlen(pathCopy) + strlen("commandX_output.txt") + 1, sizeof(char));
  sprintf(confirmResultPath, "%scommand%d_output.txt", pathCopy, currentIndex);

  char *resultPath = calloc(strlen("Resultados/commandX_output.txt") + 2, sizeof(char));
  sprintf(resultPath, "Resultados/command%d_output.txt", currentIndex);

  char *confirmedResult = readFile(confirmResultPath);
  char *resultObteined = readFile(resultPath);
  currentIndex++;

  // Copia o valor de result se for diferente de NULL
  if (resultObteined != NULL) {
    *result = calloc(strlen(resultObteined) + 1, sizeof(char));
    *result = resultObteined;
  }

  // Copia o valor de confirmedResult se for diferente de NULL
  if (confirmedResult != NULL) {
    *expectedResult = calloc(strlen(confirmedResult) + 1, sizeof(char));
    *expectedResult = confirmedResult;
  }

  if (resultObteined == NULL) {
    return confirmedResult == NULL;
  }

  if (confirmedResult == NULL) {
    return resultObteined == NULL;
  }

  return strcmp(resultObteined, confirmedResult) == 0;
}
