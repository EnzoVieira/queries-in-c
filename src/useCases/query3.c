#include "../../includes/query3.h"

#define DATE "09/10/2022"

struct catalog
{
  void *users;
  void *drivers;
  void *rides;
};

struct date
{
  int day;
  int month;
  int year;
};

struct querie3Aux {
    char* id;
    int distance;
    char* moreRecentTrip;
};


//void totalDistance(gpointer key, gpointer value, gpointer userData) {
//    Ride* r = value;
//    q3Aux* q3 = userData;
//    char* u = getRUser(r);
//    if (strcmp(u, q3->id) == 0) {
//        q3->distance = q3->distance + getRDistance(r);
//    }
//    free(u);
//}
//
//double getTotalDistance(Catalog* c, char* id) {
//    q3Aux q3 = {id, 0, 0};
//    g_hash_table_foreach(c->rides, totalDistance, &q3);
//    printf("Total: %d\n", q3.distance);
//    return q3.distance;
//}



//void recentTrip(gpointer key, gpointer value, gpointer userData) {
//    Ride* r = value;
//    q3Aux* q3 = userData;
//    char* u = getRUser(r);
//    if (strcmp(u, q3->id) == 0) {
//        q3->moreRecentTrip = compareDates(getRDate(r), q3->moreRecentTrip);
//    }
//    free(u);
//}

//char* getMostRecentTrip(Catalog* c, char* id) {
//    q3Aux q3 = {id, 0, "00/00/0000"};
//    g_hash_table_foreach(c->rides, recentTrip, &q3);
//    printf("%s\n", q3.moreRecentTrip);
//    return q3.moreRecentTrip;
//}

//char* compareDates(char* date1, char* date2) {
//    Date* d1 = dateConvert(date1);
//    Date* d2 = dateConvert(date2);
//    char* recentDate;
//    //quanto maior for o ano mais recente a data é
//    if ((d1->year > d2->year) || (d1->year == d2->year && d1->month > d2->month) || (d1->year == d2->year && d1->month == d2->month && d1->day >= d2->day)) {
//        recentDate = strdup(date1);
//    }
//    else recentDate = strdup(date2);
//    free(d1);
//    free(d2);
//    return recentDate;
//}

int compareRecentTrip(char* a, char* b) {
    if (strcmp(a+6, b+6) == 0) //se o ano igual
        if (strcmp(a+3, b+3) == 0) //se o mês for igual
            return -strcmp(a, b); //compara o dia
        else 
            return -strcmp(a+3, b+3);  //senão, compara o mês
    else 
        return -strcmp(a+6, b+6); //senão, compara o ano
}

int compareFunc(gconstpointer a, gconstpointer b) {
    q3Aux* u1 = (q3Aux*)a;
    q3Aux* u2 = (q3Aux*)b;
    if (u1->distance == u2->distance) { //se a distância for igual
        if (compareRecentTrip(u1->moreRecentTrip, u2->moreRecentTrip)) //se a viagem mais recente for igual
            return (strcmp(u1->id, u2->id)); //compara o ID
        else
            return compareRecentTrip(u1->moreRecentTrip, u2->moreRecentTrip); //compara a viagem mais recente
    } else return u1->distance < u2->distance; //compara a distância
}

void copyToHash(gpointer key, gpointer value, gpointer userData) {
    GHashTable* copy = (GHashTable*)userData;
    Ride* r = (Ride*)value;
    char* u = getRUser(r);
    char* lastRide = getRDate(r);
    // verifica se o user já existe na hash
    q3Aux* user = g_hash_table_lookup(copy, u);
    if (user) {
        user->distance = user->distance + getRDistance(r);
        if (compareRecentTrip(user->moreRecentTrip, lastRide)>0){
            user->moreRecentTrip = lastRide;
        }
        else free(lastRide);
    } else {
        user = (q3Aux*)malloc(sizeof(q3Aux));
        user->distance = getRDistance(r);
        user->id = u;
        user->moreRecentTrip = lastRide;
        g_hash_table_insert(copy, user->id, user);
    }
}


char *q3(Catalog* c, int N) {
    GHashTable* usersTotalDistance = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    g_hash_table_foreach(c->rides, copyToHash, usersTotalDistance);
    GList* copyFromHash = g_hash_table_get_values(usersTotalDistance);
    copyFromHash = g_list_sort(copyFromHash, (GCompareFunc)compareFunc);

    size_t lineLength = 20 + 50 + 5;
    char *stringGrande = calloc(lineLength * N, sizeof(char));
    
    int i = 0;
    while (copyFromHash->next && i < N) {
        q3Aux* q3 = copyFromHash->data;
        User* u = findUserByUsername(c->users, q3->id);

        if (getUAccountStatus(u)) {
            char *stringAux = calloc(lineLength, sizeof(char));
            sprintf(stringAux, "%s;%s;%d\n", getUUsername(u), getUName(u), q3->distance);
            strcat(stringGrande, stringAux);
            free(stringAux);

            copyFromHash = copyFromHash->next;
            i++;
        } else {
            copyFromHash = copyFromHash->next;
            q3 = copyFromHash->data;
        }
    }
    return stringGrande;
}