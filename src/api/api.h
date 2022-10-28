#ifndef API_H
#define API_H

#include <glib.h>

// Definição da função de comparação
typedef int (*CompareFunction)(const void *a, const void *b);

// Macro que retorna o apontador de um item em uma posição do arary
// TODO: Este macro não devera retornar um apontador, mas uma cópia daquele item
#define arrayIndex(array, index, type) (((type *)(void *)((GArray *)array)->data)[(index)])

// Macro que adicionar elemento à table
#define addToTable(array, data) g_array_append_vals(array, &(data), 1)

// Inicia uma table
void *createTable(int item_size);

// Ordena uma table por uma função de comparação
void arraySort(void *array, CompareFunction compare_func);

#endif
