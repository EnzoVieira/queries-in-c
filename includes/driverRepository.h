#ifndef DRIVER_REPOSITORY_H
#define DRIVER_REPOSITORY_H

#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "api.h"
#include "driverEntity.h"

void *createDriversHashData(const char *path);
Driver *cloneDriver(Driver *d);

Driver *findDriverByID(GHashTable *drivers, char *id);

#endif
