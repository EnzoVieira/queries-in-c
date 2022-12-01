#ifndef DRIVER_REPOSITORY_H
#define DRIVER_REPOSITORY_H

#include <stdio.h>
#include <string.h>

#include "api.h"
#include "date.h"

#include "driverEntity.h"

Driver* findDriverByID(HashTable *drivers, char *id);
int getDriverAge(Driver *driver);

#endif
