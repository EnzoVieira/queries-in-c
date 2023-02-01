#ifndef ASSERT_H
#define ASSERT_H

// Confirma se o resultado está igual ao encontrado em `confirmResultPath`
// e coloca dentro de `expectedResult` o resultado esperado
int assertResult(char *result, const char *confirmResultPath, char **expectedResult);

#endif
