#ifndef USER_ENTITY
#define USER_ENTITY

typedef struct user User;
char* getUUsername(User *u);
char* geUtName(User *u);
char getUGender(User *u);
char* getUBirthDate(User *u);
char* getUAccountCreation(User *u);
char* getUPayMethod(User *u);
char* getUAccountStatus(User *u);
#endif