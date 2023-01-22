#ifndef READER_H
#define READER_H

#include <stdio.h>

FILE *openFile(const char *path);
// Retorna o conteúdo de um ficheiro.
// Caso ele esteja vazio (i.e. 0 bytes), retorna NULL.
char *readFile(const char *filename);
int readLine(char **buffer, FILE *fp);
void foreachLineOfFile(const char *path, void(*func)(char *line));

#endif
