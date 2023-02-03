#ifndef ASSERT_H
#define ASSERT_H

// Confirma se o resultado está igual ao encontrado em `confirmResultPath`
// e coloca dentro de `result` e `expectedResult` o resultado obtido e o esperado respetivamente
int assertResult(const char *confirmResultPath, char **result, char **expectedResult);

#endif
