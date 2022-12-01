
#include "../../includes/api.h"

void destroyKey(void *u){
  char *destroyME = (char *)u;
  if (destroyME)
    free(destroyME);
}

HashTable *createTable(void(*destroyData)(void* u)) {
  HashTable *hashTable = g_hash_table_new_full(g_str_hash, g_str_equal,destroyKey, destroyData);
  return hashTable;
}

void addToTable(HashTable *table, void *key, void *value) {
  g_hash_table_insert(table, key, value);
}

void *findBy(HashTable *table, void* key) {
  return g_hash_table_lookup((GHashTable*) table, key);
}

void foreach(HashTable *table, void *func, void *accumulator) {
  g_hash_table_foreach((GHashTable*) table, (GHFunc) func, accumulator);
}

void *getListFromTable(HashTable *table) {
  return g_hash_table_get_values((GHashTable*) table);
}

void *listSortBy(void* list, void *func, void* data){
  return g_list_sort_with_data((GList*) list,(GCompareDataFunc)func,(gpointer)data);
}

void *findFromList(void* list, int index){
  return g_list_nth((GList*) list, index)->data;
}

void freeList(void* list){
  g_list_free((GList*)list);
}

void destroyTable(HashTable* table){
  g_hash_table_destroy((GHashTable*)table);
}

//struct User2{
//  char*(*getUUsername);
//
//};
