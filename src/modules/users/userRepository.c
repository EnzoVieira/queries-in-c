#include "userRepository.h"

#define cast_user(a) (*(User *)a)

int userUsernameCmp(const void *a, const void *b)
{
  User userA = cast_user(a);
  User userB = cast_user(b);

  return strcmp(userA.user_name, userA.user_name);
}
