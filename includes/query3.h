#ifndef QUERY_3_H
#define QUERY_3_H

typedef struct catalog Catalog;
typedef struct querie3Aux q3Aux;

void copyToHash(void *key, void *value, void *userData);
int compareRecentTrip(char* a, char* b);
int compareFunc(void *a, void *b);
char *q3(Catalog* c, int N);

#endif