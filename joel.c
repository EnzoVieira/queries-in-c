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
    //void *usersHash = createUsersHashData();
    //void *driversHash = createDriversHashData();
    //void *ridesHash = createRidesHashData();
    
    Catalogo catalogo;
    catalogo.users = createUsersHashData();
    catalogo.drivers = createDriversHashData();
    catalogo.rides = createRidesHashData();
    
    
    printf("Testes para Users\n");
    int n_trips_user = 0;
    double rating_user = 0;
    double total_cost = 0;
    User* u = findUserByUsername(catalogo.users, "RenatPaiva");
    n_trips_user = numberOfTrips(&catalogo, "RenatPaiva");
    rating_user = totalRating(&catalogo, "RenatPaiva");
    total_cost = totalCost(&catalogo, "RenatPaiva");


    printf("%s; %c; %s; %.3f; %d; %.3f  \n", getUUsername(u), getUGender(u), getUBirthDate(u), rating_user, n_trips_user, total_cost);
    

    printf("Testes para Drivers\n");
    int n_trips_driver = 0;
    double rating_driver = 0;
    double total_earned = 0;
    Driver* d = findDriverByID(catalogo.drivers, "000000009720");
    n_trips_driver = numberOfTrips(&catalogo, "000000009720");
    rating_driver = totalRating(&catalogo, "000000009720");
    total_earned = totalCost(&catalogo, "000000009720");
    

    printf("%s; %c; %s; %.3f; %d; %.3f  \n", getDID(d), getDGender(d), getDBirthDate(d), rating_driver, n_trips_driver, total_earned);
    

    //printf("Testes para Rides\n");
    //Ride* r = findRideByID(&catalogo, "000000000080");
    //char* ride_user = getRUser(r);
    //char* ride_driver = getRDriver(r);
    //double total_pago_User = totalCost(&catalogo, ride_user);
    //double total_auferido_Driver = totalCost(&catalogo, ride_driver);


    //printf("Viagem: %s; %f; %f  \n", getRID(r), total_auferido_Driver, total_pago_User);


    return 0;
}

