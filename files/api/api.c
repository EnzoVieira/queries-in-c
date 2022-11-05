#include "../../includes/api.h"

void *createTable()
{
  GHashTable *hashTable = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

  return hashTable;
}

void addToTable(void *table, void *key, void *value)
{
  g_hash_table_insert(table, key, value);
}