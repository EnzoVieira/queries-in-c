#include "../../includes/query2.h"

struct catalog
{
  void *users;
  void *drivers;
  void *rides;
};

typedef struct querie2Aux{

  char *data_identification;
  double media;
  double valueQty;
  char *last_ride;
} q2Aux;

// Funções destroy

// Função utilizada para free da data da hash de SumData
void destroyQ2Aux(void *u)
{
  q2Aux *destroyME = (q2Aux *)u;
  if (destroyME)
  {
    if (destroyME->data_identification)
      free(destroyME->data_identification);
  }
  destroyME = NULL;
}

// Função para dar free da key(se for string) da hash
void destroyKey(void *u)
{
  char *destroyME = (char *)u;
  if (destroyME)
    free(destroyME);
}

// QUERRY 2


//Calcular qual a viagem mais recente
int mostRecenteRide (char* a, char* b){
  //Os return são com "-"(menos) antes pois eu quero ordenar por ordem decrescente 
  //0 se a==b ; -1 se a>b ; 1 se a<b
  //DATA TIPO XX/XX/XXXX
  //a+6 vai ler só a parte da string que corresposde ao ano
  //a+3 vai ler a parte da string que corresposde ao mes e ano
  //a vai ler só a parte da string que corresposde ao dia mes e ano

  //Se o ano for igual
  if (!strcmp(a+6,b+6)){
    //Se o mes e o ano for igual (compara os dias)
    if (!strcmp(a+3,b+3)){
      return -(strcmp(a,b));
    }
    //Se o mes for diferente (compara os meses)
    else {
      return -(strcmp(a+3,b+3));
    }
  }
  //Se o ano for diferente (compara os anos)
  else {
    return -(strcmp(a+6,b+6));
  }
}

// Função comparação para ordenar array de q2Aux (Ordem decrescente)
int compareMedia(gconstpointer a, gconstpointer b, gpointer user_data)
{

  //Variavel que contem os sumatórios das viagens
  q2Aux *val1 = (q2Aux *)a;
  q2Aux *val2 = (q2Aux *)b;

  //Se a média for diferente (ordena pela média maior)
  if ((val1->media / val1->valueQty) != (val2->media / val2->valueQty)){
    return ((val1->media / val1->valueQty) < (val2->media / val2->valueQty));
  //Se a média for igual (ordena pela data mais recente)
  }else if (mostRecenteRide(val1->last_ride,val2->last_ride)){
    return mostRecenteRide(val1->last_ride,val2->last_ride);
  //Se a média e a data são iguais (ordena pelo id crescente)
  }else
    return strcmp(val1->data_identification,val2->data_identification);
}

// Função para criar a hash com os dados data_identification e scoreSum
void interactMedia(gpointer key, gpointer value, gpointer data)
{

  // hash a ser preenchida com q2Aux(Driver;Soma dos scores;total de elementos da soma)
  GHashTable *media = (GHashTable *)data;
  // variavel que guarda cada ride da hash Rides
  Ride *ride = (Ride *)value;

  char *rideDriver = getRDriver(ride);
  char* lastRide = getRDate(ride);
  double rideDriverScore = getRScoreDriver(ride);


  // procura se o driver ja existe na hashlastDrive
  q2Aux *driverToken = g_hash_table_lookup(media, rideDriver);
  // caso exista
  if (driverToken != NULL)
  {
    // incrementa o valueQty, acrescenta ao somatório o valor da Ride atual,guarda a viagem mais recente
    driverToken->valueQty++;
    driverToken->media = driverToken->media + rideDriverScore;
    if (mostRecenteRide(driverToken->last_ride,lastRide)>0){
      driverToken->last_ride = lastRide;
    }
    else free(lastRide);
  }
  // caso não exista
  else
  {
    // cria espaço para um novo driver do tipo q2Aux
    driverToken = (q2Aux*)malloc(sizeof(q2Aux));
    // atribui os valores necessários (de modo a poder ser libertado mais tarde)
    driverToken->data_identification = rideDriver;
    driverToken->valueQty = 1;
    driverToken->media = rideDriverScore;
    driverToken->last_ride = lastRide;
    // insere na hash
    g_hash_table_insert(media, driverToken->data_identification, driverToken);
  }
}

int q2(Catalog *catalog, int N)
{

  // Hash que vai conter todas as structs temporárias da soma dos scores (nao precisa de keyDestroy)
  GHashTable *driversTotalScoreHash = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroyQ2Aux);
  // Função que vai prencher a hash anterior
  g_hash_table_foreach(catalog->rides, interactMedia, driversTotalScoreHash);

  // Lista con toda a data da hash
  GList *hashContent = g_hash_table_get_values(driversTotalScoreHash);
  // Ordenação da Lista por Médias
  hashContent = g_list_sort_with_data(hashContent, (GCompareDataFunc)compareMedia, catalog->drivers);

  // Array que vai conter os N condutores com melhor média por cordem decrescente
  GArray *fianlArrayQ2 = g_array_sized_new(0, 1, sizeof(q2Aux), 1);

  // Variavel utilizada para preencher o GArray de estruturas com os id e as médias dos condutores
  q2Aux listItem;
  //= *(q2Aux*)(g_list_nth(hashContent,i))->data
  // Preenchimento do array com os N maiores elementos
  int i = 0,j=N;

  while (i < j)
  {
    // Guardar o id do elemento da lista em uma variavel para facil leitura
    char *id = (*(q2Aux *)(g_list_nth(hashContent, i)->data)).data_identification;
    if  (getDAccountStatus(g_hash_table_lookup(catalog->drivers,id))){
      // Guardar a media ja calculada do elemento da lista em uma variavel para facil leitura
      float mediaTotal = (*(q2Aux *)(g_list_nth(hashContent, i)->data)).media /
                         (*(q2Aux *)(g_list_nth(hashContent, i)->data)).valueQty;

      // Atribuição do id à copia da estrutura que vai passar para o array final
      listItem.data_identification = strdup(id);
      // Atribuição da media à copia da estrutura que vai passar para o array final
      listItem.media = mediaTotal;
      listItem.last_ride = strdup((*(q2Aux *)(g_list_nth(hashContent, i)->data)).last_ride);
      // inserção da cópia no array final
      g_array_append_vals(fianlArrayQ2, &listItem, 1);
      i++;
    }
    else{
      i++;
      j++;
    }
  }
  
  // free da lista
  g_list_free(hashContent);
  // free da hash
  g_hash_table_destroy(driversTotalScoreHash);

  // TESTE DE PRINT --  APAGAR DEPOIS (IMPORTANTE)
  i = 0;
  q2Aux teste3;
  while (i < fianlArrayQ2->len)
  {
    teste3 = (g_array_index(fianlArrayQ2, q2Aux, i));
    printf("DRIVER: %d %s ; DATA %s ; MEDIA: %f\n", i + 1, teste3.data_identification,teste3.last_ride, teste3.media);
    i++;
  }

  return 0;
}