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


void totalDistance(gpointer key, gpointer value, gpointer userData) {
    Ride* r = value;
    q3Aux* q3 = userData;
    char* u = getRUser(r);
    if (strcmp(u, q3->id) == 0) {
        q3->distance = q3->distance + getRDistance(r);
    }
    free(u);
}

double getTotalDistance(Catalog* c, char* id) {
    q3Aux q3 = {id, 0, 0};
    g_hash_table_foreach(c->rides, totalDistance, &q3);
    printf("Total: %d\n", q3.distance);
    return q3.distance;
}

char* compareDates(char* date1, char* date2) {
    Date* d1 = dateConvert(date1);
    Date* d2 = dateConvert(date2);
    char* recentDate;
    //quanto maior for o ano mais recente a data é
    if ((d1->year > d2->year) || (d1->year == d2->year && d1->month > d2->month) || (d1->year == d2->year && d1->month == d2->month && d1->day >= d2->day)) {
        recentDate = strdup(date1);
    }
    else recentDate = strdup(date2);
    free(d1);
    free(d2);
    return recentDate;
}

void recentTrip(gpointer key, gpointer value, gpointer userData) {
    Ride* r = value;
    q3Aux* q3 = userData;
    char* u = getRUser(r);
    if (strcmp(u, q3->id) == 0) {
        q3->moreRecentTrip = compareDates(getRDate(r), q3->moreRecentTrip);
    }
    free(u);
}

char* getMostRecentTrip(Catalog* c, char* id) {
    q3Aux q3 = {id, 0, "00/00/0000"};
    g_hash_table_foreach(c->rides, recentTrip, &q3);
    printf("%s\n", q3.moreRecentTrip);
    return q3.moreRecentTrip;
}

void copyToHash(gpointer key, gpointer value, gpointer userData) {
    GHashTable* copy = (GHashTable*)userData;
    Ride* r = (Ride*)value;
    char* u = getRUser(r);
    // verifica se o user já existe na hash
    q3Aux* user = g_hash_table_lookup(copy, u);
    if (user != NULL) {
        user->distance = user->distance + getRDistance(r);
        user->moreRecentTrip = compareDates(user->moreRecentTrip, getRDate(r));
    } else {
        user = (q3Aux*)malloc(sizeof(q3Aux*));
        user->distance = getRDistance(r);
        user->id = u;
        user->moreRecentTrip = getRDate(r);
        g_hash_table_insert(copy, user->id, user);
    }
}

int compareFunc(gconstpointer a, gconstpointer b) {
    q3Aux* u1 = (q3Aux*)a;
    q3Aux* u2 = (q3Aux*)b;
    return (u1->distance < u2->distance);
}

void fillHash(Catalog* c, char* id) {
    GHashTable* usersTotalDistance = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    g_hash_table_foreach(c->rides, copyToHash, usersTotalDistance);
    //q3Aux* u = g_hash_table_lookup(usersTotalDistance, id);
    GList* copyFromHash = g_hash_table_get_values(usersTotalDistance);
    copyFromHash = g_list_sort_with_data(copyFromHash, (GCompareDataFunc)compareFunc, NULL);
    q3Aux* q3 = copyFromHash->data;
    int i = 0;
    while (copyFromHash->next && i < 50) {
        User* u = findUserByUsername(c->users, q3->id);
        copyFromHash = copyFromHash->next;
        printf("%s, %s, %d\n", q3->id, getUName(u), q3->distance);
        q3 = copyFromHash->data;
        i++;
    }
}