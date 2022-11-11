#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

typedef struct
{
  char *value;

  enum {
    TOKEN_QUERY,
    TOKEN_ARGUMENT,
    TOKEN_EOF
  } type;
} Token;

Token *createToken(char *value, int type);

#endif