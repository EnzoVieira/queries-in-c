#include <stdio.h>

#include "includes/api.h"

#include "includes/userRepository.h"
#include "includes/driverRepository.h"
#include "includes/rideRepository.h"

#include "includes/findDriverByIdUseCase.h"
#include "includes/findUserByUsernameUseCase.h"

#include "userEntity.h"

int main()
{
    void *usersHash = createUsersHashData();
    void *driversHash = createDriversHashData();
    void *ridesHash = createRidesHashData();

    findDriverByID(driversHash, "NULL");
    findUserByUsername(usersHash, "WNogueira");

    return 0;
}
