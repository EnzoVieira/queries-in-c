#include "../includes/timer.h"

// Função que calcula o tempo gasto em segundos de uma função, dado o tempo de início da função
double calcQueryTime(clock_t *start) {
  clock_t time = clock() - *start;
  double queryTime = ((double)time)/CLOCKS_PER_SEC;

  return queryTime;
}
