#include "../../includes/token.h"

#include <stdlib.h>

Token *createToken(char *value, int type) {
  Token *token = calloc(1, sizeof(Token));

  token->value = value;
  token->type = type;

  return token;
}