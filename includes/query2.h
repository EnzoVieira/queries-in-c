#ifndef QUERY_2_H
#define QUERY_2_H

typedef struct catalog Catalog;

void destroyQ2Aux(void *u);
int compareMedia(void* a, void* b);
void createTableOfDriversScoreAcc(void* key, void* value, void* data);
char *q2(Catalog *catalog, int N);


#endif