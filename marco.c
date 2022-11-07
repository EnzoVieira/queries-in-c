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


int main(){

    Catalogo catalogo;
    catalogo.users = createUsersHashData();
    catalogo.drivers = createDriversHashData();
    catalogo.rides = createRidesHashData();

    q2(&catalogo,50);
    q4(&catalogo,"Faro");

    return 0;
}