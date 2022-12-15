#include "../../includes/query1.h"

#include "../../includes/userRepository.h"
#include "../../includes/driverRepository.h"
#include "../../includes/userStatistics.h"
#include "../../includes/driverStatistics.h"


void q1 (char *identification){
    
    User userExists = findUserByUsername(identification);
    Driver driverExists = findDriverByID(identification);

    if (userExists && getUAccountStatus(userExists)){

    
    
    }
    else if (driverExists && getDAccountStatus(driverExists)){

    

    }
}