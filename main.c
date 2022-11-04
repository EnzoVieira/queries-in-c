#include <stdio.h>

#include "includes/api.h"

#include "includes/userEntity.h"
#include "includes/driverEntity.h"

#include "includes/findDriverByIdUseCase.h"
// #include "includes/findUserByUsernameUseCase.h"

int main()
{
    // Init tables
    void *usersTable = createTable(sizeof(User));
    void *driversTable = createTable(sizeof(Driver));

    Driver driver = {
        "0001",
        "Driver",
        "birth_day",
        'M',
        "car_class",
        "license_plate",
        "city",
        "account_creation",
        1};
    Driver driver1 = {
        "0002",
        "Driver 1",
        "birth_day",
        'M',
        "car_class",
        "license_plate",
        "city",
        "account_creation",
        1};
    User user = {
        "enzovieira",
        "Enzo Vieira",
        'M',
        "blabla",
        "Ontem",
        "Crédito",
        "active"};
    User user2 = {
        "marco",
        "Enzo Vieira",
        'M',
        "blabla",
        "Ontem",
        "Crédito",
        "active"};
    User user3 = {
        "joel",
        "Enzo Vieira",
        'M',
        "blabla",
        "Ontem",
        "Crédito",
        "active"};

    // Populate tables
    addToTable(usersTable, user);
    addToTable(usersTable, user2);
    addToTable(usersTable, user3);

    addToTable(driversTable, driver1);
    addToTable(driversTable, driver);

    // QUERIES 1
    findDriverByIdUseCase("0002");
    // findUserByUsernameUseCase("enzovieira");

    // ============== Código de testes ==============

    // arraySort(driversTable, sortDriverById);

    for (int i = 0; i < 3; i++)
    {
      User data = arrayIndex(usersTable, i, User);
      printf("%s \n", data.user_name);
    }

    for (int i = 0; i < 2; i++)
    {
      Driver data = arrayIndex(driversTable, i, Driver);
      printf("%s \n", data.name);
    }

    return 0;
}