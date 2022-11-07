#include "../../../includes/catalogEntity.h"
#include "../../../includes/catalogRepository.h"
#include "../../../includes/userEntity.h"
#include "../../../includes/rideEntity.h"
#include "../../../includes/rideRepository.h"
#include "../../../includes/driverEntity.h"
#include "../../../includes/findUserByUsernameUseCase.h"
#include "../../../includes/findDriverByIdUseCase.h"


struct catalogo {
    void* users;
    void* drivers;
    void* rides;
};

typedef struct querie1Aux {
    char* id;
    int totalTrips;
    double averageRating;
    double tripValue;
    Catalogo* catalogo;
} q1Aux;

typedef struct sumData{

    char* data_identification;
    double media;
    double valueQty;

}SumDataToken;


//Funções destroy

//Função utilizada para free da data da hash de SumData
void destroySumData(void *u) {
    SumDataToken *destroyME = (SumDataToken*)u;
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

//QUERRY 2

//Função comparação para ordenar array de SumDataToken (Ordem decrescente)
int compareMedia (gconstpointer a,gconstpointer b){

    SumDataToken *val1 = (SumDataToken*)a;
    SumDataToken *val2 = (SumDataToken*)b;

    return ((val1->media/val1->valueQty)<(val2->media/val2->valueQty));
}

//Função para criar a hash com os dados data_identification e scoreSum
void interactMedia(gpointer key,gpointer value, gpointer data){
    
    //hash a ser preenchida com SumDataToken
    GHashTable* media = (GHashTable*)data;
    //variavel que guarda cada ride da hash Rides
    Ride *ride = (Ride*)value;
    
    char* rideDriver = getRDriver(ride);
    double rideDriverScore = getRScoreDriver(ride);

    //procura se o driver ja existe na hash
    SumDataToken* driverToken = g_hash_table_lookup(media,rideDriver);
    //caso exista
    if (driverToken != NULL){
        //incrementa o valueQty e acrescenta ao somatório o valor da Ride atual
        driverToken->valueQty ++;
        driverToken->media = driverToken->media + rideDriverScore;
    }
    //caso não exista
    else {
        //cria espaço para um novo driver do tipo SumDataToken
        driverToken = (SumDataToken*)malloc(sizeof(SumDataToken*));
        //atribui os valores necessários (de modo a poder ser libertado mais tarde)
        driverToken->data_identification = rideDriver;
        driverToken->valueQty = 1;
        driverToken->media = rideDriverScore;
        //insere na hash
        g_hash_table_insert(media,driverToken->data_identification,driverToken);
    }
}

int q2(Catalogo catalog,int N){

    //Hash que vai conter todas as structs temporárias da soma dos scores (nao precisa de keyDestroy)
    GHashTable *driversTotalScoreHash = g_hash_table_new_full(g_str_hash, g_str_equal,NULL, destroySumData);
    //Função que vai prencher a hash anterior
    g_hash_table_foreach(catalog.rides,interactMedia,driversTotalScoreHash);

    //Lista con toda a data da hash
    GList *hashContent = g_hash_table_get_values(driversTotalScoreHash);
    //Ordenação da Lista por Médias
    hashContent = g_list_sort_with_data(hashContent,(GCompareDataFunc)compareMedia,NULL);
    
    //Array que vai conter os N condutores com melhor média por cordem decrescente
    GArray* fianlArrayQ2 = g_array_sized_new(0,1,sizeof(SumDataToken),1);

    //Variavel utilizada para preencher o GArray de estruturas com os id e as médias dos condutores
    SumDataToken listItem;
    //= *(SumDataToken*)(g_list_nth(hashContent,i))->data
    //Preenchimento do array com os N maiores elementos
    int i = 0;

    while (i<N){
        
        //Guardar o id do elemento da lista em uma variavel para facil leitura
        char* id = (*(SumDataToken*)(g_list_nth(hashContent,i)->data)).data_identification;
        //Guardar a media ja calculada do elemento da lista em uma variavel para facil leitura
        float mediaTotal = (*(SumDataToken*)(g_list_nth(hashContent,i)->data)).media / 
                           (*(SumDataToken*)(g_list_nth(hashContent,i)->data)).valueQty;
        
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
    SumDataToken teste3;
    while(i<fianlArrayQ2->len){
        teste3 = (g_array_index(fianlArrayQ2,SumDataToken,i));
        printf ("DRIVER: %d %s ; MEDIA: %f\n",i+1,teste3.data_identification,teste3.media);
        i++;
    }
    return 0;
}













