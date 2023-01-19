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

HashTable *createHashTable() {
  HashTable *hashTable = (HashTable*) g_hash_table_new_full(g_str_hash, g_str_equal, destroyKey, NULL);
  return hashTable;
}

void hashForeach(HashTable *list, HFunc func ,Pointer data) {
  g_hash_table_foreach((GHashTable*) list, (GHFunc) func,(gpointer) data);
}

void addToTable(HashTable *table, char *key, Pointer value) {
  g_hash_table_insert((GHashTable *) table, key, value);
}

Pointer findById(HashTable *table, const char* id) {
  return g_hash_table_lookup((GHashTable*) table, id);
}


//List

List *createList() {
  return (List*) g_list_alloc();
}

List *copyList(List *list) {
  return (List*) g_list_copy((GList*) list);
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

void listForeach(List *list, Func func) {
  g_list_foreach((GList*) list, (GFunc) func, NULL);
}

void freeListOfStrings(List *list){
  g_list_free_full((GList*)list,(GDestroyNotify)free);
}
