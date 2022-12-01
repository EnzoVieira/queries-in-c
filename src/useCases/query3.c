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
        if (compareRecentTrip(u1->moreRecentTrip, u2->moreRecentTrip) == 0) //se a viagem mais recente for igual
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
    g_list_free(copyFromHash);
    return stringGrande;
}