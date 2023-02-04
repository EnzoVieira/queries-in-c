#ifndef STRINGS_H
#define STRINGS_H

// Cria um novo apontador (calloc) para uma string concatenada
char *concatStrings(const char *str1, const char *str2);
void removeNewLine(char *line);
void eraseUntilFind(char *str, char delim);
void toLowerCase(char *str);

#endif
