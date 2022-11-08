#include "../../../includes/catalogEntity.h"
#include "../../../includes/catalogRepository.h"
#include "../../../includes/userEntity.h"
#include "../../../includes/rideEntity.h"
#include "../../../includes/rideRepository.h"
#include "../../../includes/driverEntity.h"
#include "../../../includes/findUserByUsernameUseCase.h"
#include "../../../includes/findDriverByIdUseCase.h"

#define DATE "09/10/2022"


struct catalogo {
    void* users;
    void* drivers;
    void* rides;
};

struct date {
    int day;
    int month;
    int year;
};

typedef struct querie1Aux {
    char* id;
    int totalTrips;
    double averageRating;
    double tripValue;
    Catalogo* catalogo;
    int age;
} q1Aux;

typedef struct querie2Aux{

    char* data_identification;
    double media;
    double valueQty;

}q2Aux;


//Funções destroy

//Função utilizada para free da data da hash de SumData
void destroySumData(void *u) {
    q2Aux *destroyME = (q2Aux*)u;
    if(destroyME) {
        if(destroyME->data_identification)
            free(destroyME->data_identification);
    }
    destroyME = NULL;
}

//Função para dar free da key(se for string) da hash
void destroyKey(void *u) {
        char *destroyME = (char*)u; 
        if(destroyME)
            free(destroyME);
}


//QUERRY 1

void ridesCounter(gpointer key, gpointer value, gpointer userData) {
    Ride* r = value;
    q1Aux* q1 = userData;
    char* u = getRUser(r);
    char* d = getRDriver(r);
    if (strcmp(u,q1->id) == 0 || strcmp(d,q1->id) == 0) {
        q1->totalTrips++;
    }
}

int numberOfTrips(Catalogo *c, char* id) {
    q1Aux q1 = {id, 0};
    g_hash_table_foreach(c->rides, ridesCounter, &q1);
    return q1.totalTrips;
}

void rating(gpointer key, gpointer value, gpointer userData) {
    Ride* r = value;
    q1Aux* q1 = userData;
    char* u = getRUser(r);
    char* d = getRDriver(r);
    if (strcmp(u,q1->id) == 0) {
        q1->averageRating = q1->averageRating + getRScoreUser(r);
        q1->totalTrips++;
    } else if (strcmp(d,q1->id) == 0) {
        q1->averageRating = q1->averageRating + getRScoreDriver(r);
        q1->totalTrips++;
    }
}

double totalRating(Catalogo *c, char* id) {
    q1Aux q1 = {id, 0, 0};
    g_hash_table_foreach(c->rides, rating, &q1);
    return (q1.averageRating / q1.totalTrips);
}

Ride* findRideByID(Catalogo* c, char* id) {
    if (g_hash_table_lookup(c->rides, id))
        printf("A viagem com o ID %s existe.\n", id);
    return(g_hash_table_lookup(c->rides, id));
}

void travelCost(gpointer key, gpointer value, gpointer userData) {
    Ride* r = value;
    q1Aux* q1 = userData;
    //Catalogo* c = (Catalogo*) q1->catalogo;
    GHashTable* drivers = q1->catalogo->drivers;
    char* u = getRUser(r);
    char* d = getRDriver(r);
    // a viagem existe na hashtable
    if (strcmp(u, q1->id) == 0 || strcmp(d, q1->id) == 0) {
        char* carClass = getDCarClass(findDriverByID(drivers, d));
        if (strcmp(carClass, "basic") == 0)
            q1->tripValue = q1->tripValue + (3.25 + 0.62 * getRDistance(r));
        else if (strcmp(carClass, "green") == 0)
            q1->tripValue = q1->tripValue + (4.00 + 0.79 * getRDistance(r));
        else if (strcmp(carClass, "premium") == 0)
            q1->tripValue = q1->tripValue + (5.20 + 0.94 * getRDistance(r));
    }
}

double totalCost(Catalogo* c, char* id) {
    q1Aux q1 = {id, 0, 0, 0, c};
    g_hash_table_foreach(c->rides, travelCost, &q1);
    return q1.tripValue;
}

Date* dateConvert(char* birthDate) {
    char* date = strdup(birthDate);
    Date* d = (Date*)malloc(sizeof(Date));
    while (date) {
        d->day = atoi(strdup(strsep(&date, "/")));
        d->month = atoi(strdup(strsep(&date, "/")));
        d->year = atoi(strdup(strsep(&date, "\0")));
    }
    return d;
}

int dateDifference(Date* d) {
    Date* consideredDate = dateConvert(DATE);
    int age = 0;
    if ((consideredDate->year >= d->year && consideredDate->month > d->month) || 
        (consideredDate->year >= d->year && consideredDate->month == d->month && consideredDate->day >= d->day))
        age = consideredDate->year - d->year;
    else  
        age = (consideredDate->year - d->year) - 1;
    return age;
}

void findAge(gpointer key, gpointer value, gpointer userData) {
    Ride* r = value;
    q1Aux* q1 = userData;
    char* u = getRUser(r);
    char* d = getRDriver(r);
    GHashTable* us = q1->catalogo->users;
    GHashTable* dr = q1->catalogo->drivers;
    if (strcmp(getUUsername(findUserByUsername(us, u)), q1->id) == 0)
        q1->age = dateDifference(dateConvert(getUBirthDate(findUserByUsername(us, u))));
    else if (strcmp(getDID(findDriverByID(dr, d)), q1->id) == 0)
        q1->age = dateDifference(dateConvert(getDBirthDate(findDriverByID(dr, d))));
}

int getAge(Catalogo* c, char* id) {
    q1Aux q1 = {id, 0, 0, 0, c, 0};
    g_hash_table_foreach(c->rides, findAge, &q1);
    return q1.age;
}

//QUERRY 2

//Função comparação para ordenar array de q2Aux (Ordem decrescente)
int compareMedia (gconstpointer a,gconstpointer b){

    q2Aux *val1 = (q2Aux*)a;
    q2Aux *val2 = (q2Aux*)b;

    return ((val1->media/val1->valueQty)<(val2->media/val2->valueQty));
}

//Função para criar a hash com os dados data_identification e scoreSum
void interactMedia(gpointer key,gpointer value, gpointer data){
    
    //hash a ser preenchida com q2Aux(Driver;Soma dos scores;total de elementos da soma)
    GHashTable* media = (GHashTable*)data;
    //variavel que guarda cada ride da hash Rides
    Ride *ride = (Ride*)value;
    
    char* rideDriver = getRDriver(ride);
    double rideDriverScore = getRScoreDriver(ride);

    //procura se o driver ja existe na hash
    q2Aux* driverToken = g_hash_table_lookup(media,rideDriver);
    //caso exista
    if (driverToken != NULL){
        //incrementa o valueQty e acrescenta ao somatório o valor da Ride atual
        driverToken->valueQty ++;
        driverToken->media = driverToken->media + rideDriverScore;
    }
    //caso não exista
    else {
        //cria espaço para um novo driver do tipo q2Aux
        driverToken = (q2Aux*)malloc(sizeof(q2Aux*));
        //atribui os valores necessários (de modo a poder ser libertado mais tarde)
        driverToken->data_identification = rideDriver;
        driverToken->valueQty = 1;
        driverToken->media = rideDriverScore;
        //insere na hash
        g_hash_table_insert(media,driverToken->data_identification,driverToken);
    }
}

int q2(Catalogo *catalog,int N){

    //Hash que vai conter todas as structs temporárias da soma dos scores (nao precisa de keyDestroy)
    GHashTable *driversTotalScoreHash = g_hash_table_new_full(g_str_hash, g_str_equal,NULL, destroySumData);
    //Função que vai prencher a hash anterior
    g_hash_table_foreach(catalog->rides,interactMedia,driversTotalScoreHash);

    //Lista con toda a data da hash
    GList *hashContent = g_hash_table_get_values(driversTotalScoreHash);
    //Ordenação da Lista por Médias
    hashContent = g_list_sort_with_data(hashContent,(GCompareDataFunc)compareMedia,NULL);
    
    //Array que vai conter os N condutores com melhor média por cordem decrescente
    GArray* fianlArrayQ2 = g_array_sized_new(0,1,sizeof(q2Aux),1);

    //Variavel utilizada para preencher o GArray de estruturas com os id e as médias dos condutores
    q2Aux listItem;
    //= *(q2Aux*)(g_list_nth(hashContent,i))->data
    //Preenchimento do array com os N maiores elementos
    int i = 0;

    while (i<N){
        
        //Guardar o id do elemento da lista em uma variavel para facil leitura
        char* id = (*(q2Aux*)(g_list_nth(hashContent,i)->data)).data_identification;
        //Guardar a media ja calculada do elemento da lista em uma variavel para facil leitura
        float mediaTotal = (*(q2Aux*)(g_list_nth(hashContent,i)->data)).media / 
                           (*(q2Aux*)(g_list_nth(hashContent,i)->data)).valueQty;
        
        //Atribuição do id à copia da estrutura que vai passar para o array final
        listItem.data_identification = strdup(id);
        //Atribuição da media à copia da estrutura que vai passar para o array final
        listItem.media = mediaTotal;
        //inserção da cópia no array final
        g_array_append_vals(fianlArrayQ2,&listItem,1);
        i++;
    }

    //free da lista
    g_list_free(hashContent);
    //free da hash
    g_hash_table_destroy(driversTotalScoreHash);
    
    //TESTE DE PRINT --  APAGAR DEPOIS (IMPORTANTE)
    i=0;
    q2Aux teste3;
    while(i<fianlArrayQ2->len){
        teste3 = (g_array_index(fianlArrayQ2,q2Aux,i));
        printf ("DRIVER: %d %s ; MEDIA: %f\n",i+1,teste3.data_identification,teste3.media);
        i++;
    }
    return 0;
}

//Querry 4

void interactPriceMedia(gpointer key,gpointer value, gpointer data){

    
    //hash a ser preenchida com q2Aux(Driver;soma total km;total de elementos na soma)
    GHashTable* media = (GHashTable*)data;
    //variavel que guarda cada ride da hash Rides
    Ride *ride = (Ride*)value;
    
    char* rideDriver = getRDriver(ride);
    double rideTotalKm = getRDistance(ride);

    char* city = getRCity(ride);
    char* cityFilter = ((q2Aux*)g_hash_table_lookup(media,"city"))->data_identification;

    //procura se o driver ja existe na hash
    q2Aux* driverToken = g_hash_table_lookup(media,rideDriver);

    //caso exista
    if(!strcmp(city,cityFilter)){
        if (driverToken != NULL){
            //incrementa o valueQty e acrescenta ao somatório o valor da Ride atual
            driverToken->valueQty ++;
            driverToken->media = driverToken->media + rideTotalKm;
        }
        //caso não exista
        else {
            //cria espaço para um novo driver do tipo q2Aux
            driverToken = (q2Aux*)malloc(sizeof(q2Aux*));
            //atribui os valores necessários (de modo a poder ser libertado mais tarde)
            driverToken->data_identification = rideDriver;
            driverToken->valueQty = 1;
            driverToken->media = rideTotalKm;
            //insere na hash
            g_hash_table_insert(media,driverToken->data_identification,driverToken);
        }
    }
}

void totalPriceCalculator(gpointer key,gpointer value, gpointer data){

    //Variavel que vai permitir o acesso aos Drivers
    Driver *driver = (Driver*)value;

    //variavel que guarda as estruturas com o id dos driver e os km feitos na cidade
    GHashTable* driversInf = (GHashTable*)data;
    
    char* driverId = getDID(driver);
    char* carClass = getDCarClass(driver);

    q2Aux* city = g_hash_table_lookup(driversInf,"city");
    q2Aux* driverInf = g_hash_table_lookup(driversInf,driverId);

    if (driverInf && !strcmp(carClass,"basic")){
        city->media = city->media + driverInf->media*0.62 + driverInf->valueQty *3.25; 
        city->valueQty += driverInf->valueQty;

    }else if (driverInf && !strcmp(carClass,"green")){
        city->media = city->media + driverInf->media*0.79+driverInf->valueQty*4.0;
        city->valueQty += driverInf->valueQty;

    }else if (driverInf && !strcmp(carClass,"premium")){
        city->media = city->media + driverInf->media*0.94+driverInf->valueQty*5.2;
        city->valueQty += driverInf->valueQty;

    }else printf("NAO ENCONTREI\n");


    free(driverId);
    free(carClass);    
}




int q4 (Catalogo *catalog, char* city){

    //Hash que vai conter todas as structs temporárias da soma dos KM (nao precisa de keyDestroy)
    GHashTable *driversTotalKm = g_hash_table_new_full(g_str_hash, g_str_equal,NULL, destroySumData);

    //Allocação e inicialização da struct com as informações da cidade(nome/soma dos preços medios/total de somas)
    q2Aux* cityToken = (q2Aux*)malloc(sizeof(q2Aux));
    cityToken->data_identification = strdup(city);
    cityToken->media=0;
    cityToken->valueQty=0;

    //Inserir a cidade na hash para passar a informação para dentro do foreach

    g_hash_table_insert(driversTotalKm,"city",cityToken);
    //Função que vai prencher a hash anterior
    g_hash_table_foreach(catalog->rides,interactPriceMedia,driversTotalKm);

    g_hash_table_foreach(catalog->drivers,totalPriceCalculator,driversTotalKm);


    g_hash_table_steal(driversTotalKm,"city");
    
    g_hash_table_destroy(driversTotalKm);

    cityToken->media = cityToken->media/cityToken->valueQty;

    printf("%s %f %f\n",cityToken->data_identification,cityToken->media,cityToken->valueQty);

    return 0;
}











