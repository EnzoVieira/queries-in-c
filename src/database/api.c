#include "../../includes/api.h"

#include <glib.h>
#include <stdio.h>

#define DATE "09/10/2022"

// ============================
//       private methods
// ============================

void destroyKey(void *u){
  char *destroyME = (char *)u;

  if (destroyME)
    free(destroyME);
}

// ============================
//       public methods
// ============================



//HashTable

HashTable *createHashTable(DestroyFunc destroyFunc) {
  HashTable *hashTable = (HashTable*) g_hash_table_new_full(g_str_hash, g_str_equal,destroyKey, destroyFunc);
  return hashTable;
}

void hashForeach(HashTable *list, HFunc func ,Pointer data) {
  g_hash_table_foreach((GHashTable*) list, (GHFunc) func,(gpointer) data);
}

void addToTable(HashTable *table, char *key, Pointer value) {
  g_hash_table_insert((GHashTable *) table, (gpointer)key, value);
}

Pointer findById(HashTable *table, const char* id) {
  return g_hash_table_lookup((GHashTable*) table, id);
}

List* copyFromHash(HashTable* table) {
  return (List*) g_hash_table_get_values((GHashTable*) table);
}

void destroyHash(HashTable* table){
  g_hash_table_destroy((GHashTable*)table);
}

List *createList() {
  return (List*) g_list_alloc();
}

List *addToList(List *list, Pointer data) {
  return (List*) g_list_append((GList*) list, (gpointer) data);
}

List *addToSortedList(List *list, Pointer data,CompareFunc func) {
  return (List*) g_list_insert_sorted((GList*) list, (gpointer) data,(GCompareFunc)func);
}

List *sortList(List *list, CompareFunc func) {
  return (List*) g_list_sort((GList*) list, (GCompareFunc)func);
}

Pointer findInListByIndex(List *list, int index) {
  return g_list_nth((GList*)list, index)->data;
}

void freeListFull(List *list,DestroyFunc destroyFunc){
  g_list_free_full((GList*)list,(GDestroyNotify)destroyFunc);
}

void freeList(List *list){
  g_list_free((GList*)list);
}

int listLength(List* list) {
  return (int) g_list_length((GList*) list);
}

List *listNext(List *list){
  list = (List*)((GList*)list)->next;
  return list;
}
Pointer getListData(List *list){
  return ((GList*)list)->data;
}

