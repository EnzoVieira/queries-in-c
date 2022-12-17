#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/query1.h"

#include "../../includes/userRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/userStatistics.h"
#include "../../includes/driverStatistics.h"
#include "../../includes/dates.h"


void q1 (char *identification){
    
    User *userExists = findUserByUsername(identification);
    Driver *driverExists = findDriverByID(identification);

    char *name = NULL;
    char gender = '0';
    int age = 0;
    double scoreMedia = 0.0;
    double totalRides = 0;
    double totalPrice = 0.0;

    if (userExists && getUAccountStatus(userExists)){
        UserStatistics *userStatistics = findUserStatisticsByUsername(identification);
        name = getUName(userExists);
        gender = getUGender(userExists);
        age = dateToAge (getUBirthDate(userExists));
        totalRides = getUStotalTrips(userStatistics);
        scoreMedia = getUStotalScore(userStatistics)/totalRides;
        totalPrice = getUStotalExpense(userStatistics)+getUStotalTipsExpense(userStatistics);
    }
    else if (driverExists && getDAccountStatus(driverExists)){
        DriverStatistics *driverStatistics = findDriverStatisticsByUsername(identification);
        name = getDName(driverExists);
        gender = getDGender(driverExists);
        age = dateToAge (getDBirthDate(driverExists));
        totalRides = getDStotalTrips(driverStatistics);
        scoreMedia = getDStotalScore(driverStatistics)/totalRides;
        totalPrice = getDStotalEarn(driverStatistics)+getDStotalTipsEarn(driverStatistics);
    }

    size_t outputLength = (strlen(name) + 1 + 3 + 4 + 6 + 7) * 5;
    char *output = calloc(outputLength, sizeof(char));


    sprintf(output, "%s;%c;%d;%.3f;%g;%.3f\n", name, gender, age, scoreMedia, totalRides, totalPrice);

    printf("OUTPUT: %s\n",output);

}