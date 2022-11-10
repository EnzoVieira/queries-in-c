#include <stdio.h>

#include "includes/api.h"

#include "includes/userRepository.h"
#include "includes/driverRepository.h"
#include "includes/rideRepository.h"
#include "includes/catalogEntity.h"


struct catalog {
    void* users;
    void* drivers;
    void* rides;
};


int main(){

    Catalog catalogo;
    catalogo.users = createUsersHashData();
    catalogo.drivers = createDriversHashData();
    catalogo.rides = createRidesHashData();

    q2(&catalogo,50);
    q4(&catalogo,"Faro");

    return 0;
}