#include "../../includes/terminal.h"

#include <stdio.h>

void resetColor() {
  printf("%s", AC_NORMAL);
}

void redColor() {
  printf("%s", AC_RED);
}

void greenColor() {
  printf("%s", AC_GREEN);
}

void yellowColor() {
  printf("%s", AC_YELLOW);
}

void blueColor() {
  printf("%s", AC_BLUE);
}
