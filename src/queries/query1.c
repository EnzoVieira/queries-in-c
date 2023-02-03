#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/query1.h"

#include "../../includes/userRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/userStatistics.h"
#include "../../includes/driverStatistics.h"
#include "../../includes/dates.h"

char *q1 (char *identification){
    
    User *userExists = findUserByUsername(identification);
    Driver *driverExists = findDriverByID(identification);

    char *name = NULL;
    char gender = '0';
    int age = 0;
    double scoreMedia = 0.0;
    double totalRides = 0;
    double totalPrice = 0.0;

    if (userExists && getUAccountStatus(userExists)){
        char *userBirthDate = getUBirthDate(userExists);

        UserStatistics *userStatistics = findUserStatisticsByUsername(identification);
        name = getUName(userExists);
        gender = getUGender(userExists);
        age = dateToAge (userBirthDate);
        totalRides = getUStotalTrips(userStatistics);
        scoreMedia = getUStotalScore(userStatistics)/totalRides;
        totalPrice = getUStotalExpense(userStatistics)+getUStotalTipsExpense(userStatistics);
        free(userStatistics);
        free(userBirthDate);
    }
    else if (driverExists && getDAccountStatus(driverExists)){
        char *driverBirthDate = getDBirthDate(driverExists);

        DriverStatistics *driverStatistics = findDriverStatisticsByUsername(identification);
        name = getDName(driverExists);
        gender = getDGender(driverExists);
        age = dateToAge (driverBirthDate);
        totalRides = getDStotalTrips(driverStatistics);
        scoreMedia = getDStotalScore(driverStatistics)/totalRides;
        totalPrice = getDStotalEarn(driverStatistics)+getDStotalTipsEarn(driverStatistics);
        free(driverStatistics);
        free(driverBirthDate);
    }
    else {
        free(name);
        destructUserCopy(userExists);
        destructDriverCopy(driverExists);
        return NULL;
    }

    char *output = calloc(100, sizeof(char));
    sprintf(output, "%s;%c;%d;%.3f;%g;%.3f\n", name, gender, age, scoreMedia, totalRides, totalPrice);
    
    free(name);
    destructUserCopy(userExists);
    destructDriverCopy(driverExists);

    return output;
}