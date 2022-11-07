#include "../../../includes/catalogEntity.h"
#include "../../../includes/catalogRepository.h"
#include "../../../includes/userEntity.h"
#include "../../../includes/rideEntity.h"
#include "../../../includes/rideRepository.h"
#include "../../../includes/driverEntity.h"
#include "../../../includes/findUserByUsernameUseCase.h"
#include "../../../includes/findDriverByIdUseCase.h"


struct catalogo {
    void* users;
    void* drivers;
    void* rides;
};

typedef struct querie1Aux {
    char* id;
    int totalTrips;
    double averageRating;
    double tripValue;
    Catalogo* catalogo;
} q1Aux;



void ridesCounter(gpointer key, gpointer value, gpointer userData) {
    Ride* r = value;
    q1Aux* q1 = userData;
    char* u = getRUser(r);
    char* d = getRDriver(r);
    if (strcmp(u,q1->id) == 0 || strcmp(d,q1->id) == 0) {
        q1->totalTrips++;
    }
}

int numberOfTrips(Catalogo *c, char* id) {
    q1Aux q1 = {id, 0};
    g_hash_table_foreach(c->rides, ridesCounter, &q1);
    return q1.totalTrips;
}

void rating(gpointer key, gpointer value, gpointer userData) {
    Ride* r = value;
    q1Aux* q1 = userData;
    char* u = getRUser(r);
    char* d = getRDriver(r);
    if (strcmp(u,q1->id) == 0) {
        q1->averageRating = q1->averageRating + getRScoreUser(r);
        q1->totalTrips++;
    } else if (strcmp(d,q1->id) == 0) {
        q1->averageRating = q1->averageRating + getRScoreDriver(r);
        q1->totalTrips++;
    }
}

double totalRating(Catalogo *c, char* id) {
    q1Aux q1 = {id, 0, 0};
    g_hash_table_foreach(c->rides, rating, &q1);
    return (q1.averageRating / q1.totalTrips);
}

Ride* findRideByID(Catalogo* c, char* id) {
    if (g_hash_table_lookup(c->rides, id))
        printf("A viagem com o ID %s existe.\n", id);
    return(g_hash_table_lookup(c->rides, id));
}

void travelCost(gpointer key, gpointer value, gpointer userData) {
    Ride* r = value;
    q1Aux* q1 = userData;
    //Catalogo* c = (Catalogo*) q1->catalogo;
    GHashTable* drivers = q1->catalogo->drivers;
    char* u = getRUser(r);
    char* d = getRDriver(r);
    // a viagem existe na hashtable
    if (strcmp(u, q1->id) == 0 || strcmp(d, q1->id) == 0) {
        char* carClass = getDCarClass(findDriverByID(drivers, d));
        if (strcmp(carClass, "basic") == 0)
            q1->tripValue = q1->tripValue + (3.25 + 0.62 * getRDistance(r));
        else if (strcmp(carClass, "green") == 0)
            q1->tripValue = q1->tripValue + (4.00 + 0.79 * getRDistance(r));
        else if (strcmp(carClass, "premium") == 0)
            q1->tripValue = q1->tripValue + (5.20 + 0.94 * getRDistance(r));
    }
}

double totalCost(Catalogo* c, char* id) {
    q1Aux q1 = {id, 0, 0, 0, c};
    g_hash_table_foreach(c->rides, travelCost, &q1);
    return q1.tripValue;
}














