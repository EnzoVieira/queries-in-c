#ifndef FIND_USER_BY_USERNAME_USE_CASE_H
#define FIND_USER_BY_USERNAME_USE_CASE_H

#include "userEntity.h"
#include "userRepository.h"

typedef struct
{
  char *nome;
  char genero;
  double idade;
  double avaliacao_media;
  int numero_viagens;
  double total_gasto;
} UserDTO;

void findUserByUsernameUseCase(const char *username);

#endif
