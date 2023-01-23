#ifndef TERMINAL_H
#define TERMINAL_H

#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_BLUE "\x1b[34m"
#define AC_NORMAL "\033[0m"

void resetColor();
void redColor();
void greenColor();
void blueColor();

#endif
