#ifndef READER_H
#define READER_H

#include <stdio.h>

FILE *openFile(const char *path);
int readLine(char **buffer, FILE *fp);
void foreachLineOfFile(const char *path, void(*func)(char *line));

#endif
