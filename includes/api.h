#ifndef API_H
#define API_H
#include <glib.h>
typedef GHashTable HashTable;
typedef GList List;

void destroyKey(void *u);
HashTable *createTable(void(*destroyData)(void* u));
void addToTable(HashTable* table, void *key, void *value);
void *findBy(HashTable* table, void* key);
void foreach(HashTable* table, void *func, void *accumulator);
void *getListFromTable(HashTable* table);
void *listSortBy(void* list, void *func, void* data);
void *findFromList(void* list, int index);
void freeList(void* list);
void destroyTable(HashTable* table);





#endif
