#ifndef API_H
#define API_H

typedef struct hashTable HashTable;
typedef struct list List;
typedef void* Pointer;

typedef void(*Func)(Pointer data, Pointer aux);

HashTable *createHashTable();
void addToTable(HashTable *table, char *key, Pointer value);
Pointer findById(HashTable *table, const char* id);
List *createList();
List *copyList(List *list);
List *addToList(List *list, Pointer data);
void listForeach(List *list, Func func);

#endif
