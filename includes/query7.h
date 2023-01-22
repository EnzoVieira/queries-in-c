#ifndef QUERY7_H
#define QUERY7_H

#include "./api.h"

void getTotalScoreByCity(Pointer key, Pointer value, Pointer userData);
int compareFunc(Pointer a, Pointer b);
void copyToHash(Pointer key, Pointer value, Pointer userData);
char* q7(int N, char* city);

#endif