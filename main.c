#include "includes/userRepository.h"
#include "includes/rideRepository.h"

#include <stdio.h>

int main() {
  userHashTableSingleton();
  rideHashTableSingleton();

  // TODO: Add free users
  User *userTest = createUser("user1;User Teste 1;20");
  User *userTest2 = createUser("user2;User Teste 2;21");

  addUser(userTest);
  addUser(userTest2);

  Ride *ride1 = createRide("1", "user1", "Braga");
  Ride *ride2 = createRide("2", "user2", "Braga");
  Ride *ride3 = createRide("3", "user1", "Braga");
  Ride *ride4 = createRide("4", "user1", "Braga");
  Ride *ride5 = createRide("5", "user2", "Braga");
  Ride *ride6 = createRide("6", "user2", "Braga");
  Ride *ride7 = createRide("7", "user2", "Braga");
  Ride *ride8 = createRide("8", "user1", "Braga");
  Ride *ride9 = createRide("9", "user2", "Braga");

  addRide(ride1);
  addRide(ride2);
  addRide(ride3);
  addRide(ride4);
  addRide(ride5);
  addRide(ride6);
  addRide(ride7);
  addRide(ride8);
  addRide(ride9);

  printUser(userTest);
  printUser(userTest2);

  return 0;
}
