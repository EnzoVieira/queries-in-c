#include <stdio.h>

#include "includes/api.h"

#include "includes/userRepository.h"
// #include "includes/driverRepository.h"
// #include "includes/rideRepository.h"

// #include "includes/findDriverByIdUseCase.h"
// #include "includes/findUserByUsernameUseCase.h"

int main()
{
    void *usersHash = createUsersHashData();
    void *driversHash = createDriversHashData();
    void *ridesHash = createRidesHashData();

    return 0;
}
