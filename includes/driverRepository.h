#ifndef DRIVER_REPOSITORY_H
#define DRIVER_REPOSITORY_H

#include <stdio.h>
#include <string.h>

#include "api.h"
#include "driverEntity.h"

void *createDriversHashData();
Driver* cloneDriver(Driver *d);

#endif
