#include <stdio.h>
#include "includes/dates.h"


int main() {
    char* date = "10/12/2022";
    int res = 0;

    res = dateToAge(date);
    printf("%d", res);
    
    return 0;
}