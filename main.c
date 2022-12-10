#include "includes/userRepository.h"
#include "includes/rideRepository.h"
#include "includes/api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // userHashTableSingleton();
  // rideHashTableSingleton();

  // // TODO: Add free users
  // char *line = strdup("000000000002;19/10/2019;000000002536;LoSousa98;Faro;1;4;2;5.0;Image outside north effect than though sport.");
  
  // addUser("MiTeixeira;Miguel Teixeira;M;03/09/1958;05/11/2017;cash;active");
  // addUser("MelisAlmeida;Melissa de Almeida;F;18/06/1983;23/09/2020;debit_card;active");
  // addRide(line);
  // free(line);
  // //printUser(userTest);
  // //printUser(userTest2);

  createUsersHashTable("config/data/users.csv");

  return 0;
}
