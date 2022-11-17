#ifndef API_H
#define API_H

#include <glib.h>

void *createTable();
void addToTable(void *table, void *key, void *value);
void *findBy(void *table, void* key);
void foreach(void *table, void *func, void *accumulator);

#endif
