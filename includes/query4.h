#ifndef QUERY_4_H
#define QUERY_4_H

typedef struct catalog Catalog;

void destroyQ4Aux(void *u);

void interactPriceMedia(void *key, void *value, void *data);
void totalPriceCalculator(void *key, void *value, void *data);
char *q4(Catalog *catalog, char *city);

#endif