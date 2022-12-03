#ifndef API_H
#define API_H

typedef void* Pointer;

typedef struct hashTable HashTable;
typedef struct {
    Pointer data;
    Pointer next;
} List;

void destroyKey(void *u);
HashTable *createTable(void(*destroyData)(void* u));
void addToTable(HashTable* table, void *key, void *value);
void *findBy(HashTable* table, void* key);
void foreach(HashTable* table, void *func, void *accumulator);
int hashSize(HashTable* table);
List *getListFromTable(HashTable* table);
void *listSortBy(List* list, void *func, void* data);
void *findFromList(List* list, int index);
void freeList(List* list);
void destroyTable(HashTable* table);

#endif
