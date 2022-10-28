#include "api.h"

#define ARRAY_SIZE 10000

void *createTable(int item_size)
{
  GArray *newTable = g_array_sized_new(0, 1, item_size, 10000);

  return newTable;
}

void arraySort(void *array, CompareFunction compare_func)
{
  g_array_sort((GArray *)array, compare_func);
}
