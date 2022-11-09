#ifndef USER_ENTITY_H
#define USER_ENTITY_H

typedef struct user User;

char *getUUsername(User *u);
char *getUName(User *u);
char getUGender(User *u);
char *getUBirthDate(User *u);
char *getUAccountCreation(User *u);
char *getUPayMethod(User *u);
int getUAccountStatus(User *u);

#endif
