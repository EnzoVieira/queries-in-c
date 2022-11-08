#include <stdio.h>

#include "includes/api.h"

#include "includes/userRepository.h"
#include "includes/driverRepository.h"
#include "includes/rideRepository.h"
#include "includes/catalogRepository.h"

#include "includes/findDriverByIdUseCase.h"
#include "includes/findUserByUsernameUseCase.h"

/*
int dateToInt (char* date) {
    int d = 0, m = 0, a = 0;
    char* dt = strdup(date);
    d = atoi(strsep(&dt, "/"));
    m = atoi(strsep(&dt, "/"));
    a = atoi(strsep(&dt, "/"));
    printf("%d - %d - %d\n", d, m, a);
    return d;
}
*/

struct catalogo {
    void* users;
    void* drivers;
    void* rides;
};

int main()
{   
    Catalogo catalogo;
    catalogo.users = createUsersHashData();
    catalogo.drivers = createDriversHashData();
    catalogo.rides = createRidesHashData();

    q1(&catalogo, "");
    q1(&catalogo, "000000000013");

    return 0;
}

