#include "../../includes/driverRepository.h"

#define cast_driver(a) (*(Driver *)a)

Driver findDriverById(const char *id);

int sortDriverById(const void *a, const void *b)
{
  Driver driverA = cast_driver(a);
  Driver driverB = cast_driver(b);

  return strcmp(driverA.id, driverB.id);
}
