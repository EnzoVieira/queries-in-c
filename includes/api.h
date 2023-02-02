#ifndef API_H
#define API_H

typedef struct hashTable HashTable;
typedef struct list List;
typedef void* Pointer;

typedef void(*HFunc)(Pointer key, Pointer value, Pointer data);
typedef void(*Func)(Pointer data, Pointer aux);
typedef int(*CompareFunc)(Pointer a, Pointer b);

HashTable *createHashTable();
void hashForeach(HashTable *list, HFunc func ,Pointer data);
void addToTable(HashTable *table, char *key, Pointer value);
List* copyFromHash(HashTable* table);
Pointer findById(HashTable *table, const char* id);
int hashSize(HashTable* hashTable);
void destroyHash(HashTable* table);
List *createList();
List *copyList(List *list);
List *addToList(List *list, Pointer data);
List *sortList(List *list, CompareFunc func);
List *addToSortedList(List *list, Pointer data, CompareFunc func);
Pointer findInListByIndex(List *list, int index);
void listForeach(List *list, Func func);
void freeListOfStrings(List *list);
int listLength(List* list);
void freeList(List *list);

#endif
