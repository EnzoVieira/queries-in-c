#include <stdio.h>

#include "includes/api.h"

#include "includes/userRepository.h"
#include "includes/driverRepository.h"
#include "includes/rideRepository.h"
#include "includes/catalogEntity.h"

struct catalog
{
    void *users;
    void *drivers;
    void *rides;
};

int main()
{
    Catalog c;
    c.users = createUsersHashData();
    c.drivers = createDriversHashData();
    c.rides = createRidesHashData();

    q1(&c, "");
    q1(&c, "000000000013");

    return 0;
}
