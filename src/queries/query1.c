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
    
    char *name = NULL;
    char gender = '0';
    int age = 0;
    double scoreMedia = 0.0;
    double totalRides = 0;
    double totalPrice = 0.0;

    if (getUAccountStatusNew(identification)){
        char *userBirthDate = getUBirthDateNew(identification);
        name = getUNameNew(identification);
        gender = getUGenderNew(identification);
        age = dateToAge (userBirthDate);
        totalRides = getUStotalTripsNew(identification);
        scoreMedia = getUStotalScoreNew(identification)/totalRides;
        totalPrice = getUStotalExpenseNew(identification)+getUStotalTipsExpenseNew(identification);
        free(userBirthDate);
    }
    else if (getDAccountStatusNew(identification)){
        char *driverBirthDate = getDBirthDateNew(identification);

        name = getDNameNew(identification);
        gender = getDGenderNew(identification);
        age = dateToAge (driverBirthDate);
        totalRides = getDStotalTripsNew(identification);
        scoreMedia = getDStotalScoreNew(identification)/totalRides;
        totalPrice = getDStotalEarnNew(identification)+getDStotalTipsEarnNew(identification);
        free(driverBirthDate);
    }
    else {
        free(name);
        return NULL;
    }

    char *output = calloc(100, sizeof(char));
    sprintf(output, "%s;%c;%d;%.3f;%g;%.3f\n", name, gender, age, scoreMedia, totalRides, totalPrice);
    
    free(name);
    return output;
}