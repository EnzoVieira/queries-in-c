#ifndef DRIVER_REPOSITORY_H
#define DRIVER_REPOSITORY_H

#include <stdio.h>
#include <string.h>

#include "api.h"
#include "date.h"

#include "driverEntity.h"

void *createDriversHashData(const char *path);
Driver *cloneDriver(Driver *d);

Driver *findDriverByID(Driver *drivers, char *id);
int getDriverAge(Driver *driver);

#endif
