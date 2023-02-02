#include "../../includes/validations.h"

#include "../../includes/strings.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isValidDate(const char *date) {
  int day, month, year;

  // Tamanho da string é inválido
  if (strlen(date) != 10) {
    return 0;
  }

  // Falha na conversão
  if (sscanf(date, "%2d/%2d/%4d", &day, &month, &year) != 3) {
    return 0;
  }

  // Mês inválido
  if (month < 1 || month > 12) {
    return 0;
  }

  // Dia inválido
  if (day < 1 || day > 31) {
    return 0;
  }

  return 1;
}

int isValidInt(const char *str, int isZeroIncluded) {
  char *end;
  long num = strtol(str, &end, 10);

  int isGreater = isZeroIncluded ? num >= 0 : num > 0;

  return (*end == '\0') && isGreater;
}

int isValidDecimal(const char *str) {
  char *end;
  double num = strtod(str, &end);

  return (*end == '\0') && (num > 0);
}

int isValidCarClass(const char *str) {
  char *toLowerStr = toLowerCase(str);

  return (strcmp(toLowerStr, "premium") == 0 || 
          strcmp(toLowerStr, "green") == 0 || 
          strcmp(toLowerStr, "basic") == 0);
}

int isValidAccountStatus(const char *str) {
  char *toLowerStr = toLowerCase(str);

  return (strcmp(toLowerStr, "active") == 0 || strcmp(toLowerStr, "inactive") == 0);
}
