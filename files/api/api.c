#include "../../includes/api.h"

void *createTable() {
  GHashTable *hashTable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

  return hashTable;
}

void addToTable(void *table, void *key, void *value) {
  g_hash_table_insert(table, key, value);
}

void *findBy(void *table, void* key) {
  return g_hash_table_lookup((GHashTable*) table, key);
}

void foreach(void *table, void *func, void *accumulator) {
  g_hash_table_foreach((GHashTable*) table, (GHFunc) func, accumulator);
}