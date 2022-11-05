#ifndef FIND_DRIVER_BY_ID_USE_CASE_H
#define FIND_DRIVER_BY_ID_USE_CASE_H

#include "driverEntity.h"
#include "driverRepository.h"

typedef struct
{
  char *nome;
  char genero;
  double idade;
  double avaliacao_media;
  int numero_viagens;
  double total_auferido;
} DriverDTO_Q1;

Driver* findDriverByID(GHashTable *drivers, char* id);

#endif
