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

HashTable *createHashTable() {
  HashTable *hashTable = (HashTable*) g_hash_table_new_full(g_str_hash, g_str_equal, destroyKey, NULL);
  return hashTable;
}

void addToTable(HashTable *table, char *key, Pointer value) {
  g_hash_table_insert((GHashTable *) table, key, value);
}

Pointer findById(HashTable *table, const char* id) {
  return g_hash_table_lookup((GHashTable*) table, id);
}

List *createList() {
  return (List*) g_list_alloc();
}

List *copyList(List *list) {
  return (List*) g_list_copy((GList*) list);
}

List *addToList(List *list, Pointer data) {
  return (List*) g_list_append((GList*) list, (gpointer) data);
}

void listForeach(List *list, Func func) {
  g_list_foreach((GList*) list, (GFunc) func, NULL);
}
