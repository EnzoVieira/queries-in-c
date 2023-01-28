#include <stdio.h>
#include <string.h>
#include <regex.h>

#include "../../../includes/validateFuncs.h"


int validateDate (char* date){

char  *dateRegex = "^[0-9]{2}/[0-9]{2}/[0-9]{4}$";
regex_t regex;
int match;

if (regcomp(&regex,dateRegex,REG_EXTENDED) !=0){
    return 0;
}

match = regexec(&regex,date,0,NULL,0);
regfree(&regex);

    if (!match) {
        int month,day;
        sscanf(date, "%2d/%2d/%*4d", &day, &month);

        if (day >= 1 && day <= 31 && month >= 1 && month <= 12){
            return 1;
        }
        else return 0;

    } else return 0;
}
int validateCarClass(char *carClass) {
    regex_t regex;
    int match;

    regcomp(&regex, "^(premium|green|basic)$", REG_ICASE | REG_EXTENDED);

    match = regexec(&regex, carClass, 0, NULL, 0);

    regfree(&regex);
    return match == 0;
}

int validateStatus(char *status) {
    regex_t regex;
    int match;

    regcomp(&regex, "^(active|inactive)$", REG_ICASE | REG_EXTENDED);

    match = regexec(&regex, status, 0, NULL, 0);

    regfree(&regex);
    return match == 0;
}



