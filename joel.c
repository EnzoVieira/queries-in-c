#include <stdio.h>

#include "includes/api.h"

#include "includes/userRepository.h"
#include "includes/driverRepository.h"
#include "includes/rideRepository.h"
#include "includes/catalogRepository.h"

#include "includes/findDriverByIdUseCase.h"
#include "includes/findUserByUsernameUseCase.h"

struct catalogo {
    void* users;
    void* drivers;
    void* rides;
};

int main()
{   
    Catalog catalogo;
    catalogo.users = createUsersHashData();
    catalogo.drivers = createDriversHashData();
    catalogo.rides = createRidesHashData();

    q1(&catalogo, "");
    q1(&catalogo, "000000000013");

    return 0;
}

