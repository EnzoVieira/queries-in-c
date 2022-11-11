#include "../../includes/query4.h"
#include "../../includes/writer.h"

struct catalog {
  void *users;
  void *drivers;
  void *rides;
};

typedef struct querie4Aux {

  char *data_identification;
  double media;
  double valueQty;
} q4Aux;

void destroyQ4Aux(void *u) {
  q4Aux *destroyME = (q4Aux *)u;
  if (destroyME)
  {
    if (destroyME->data_identification)
      free(destroyME->data_identification);
  }
  destroyME = NULL;
}

//void destroyKey(void *u)
//{
//  char *destroyME = (char *)u;
//  if (destroyME)
//    free(destroyME);
//}

void interactPriceMedia(gpointer key, gpointer value, gpointer data) {

  // hash a ser preenchida com q2Aux(Driver;soma total km;total de elementos na soma)
  GHashTable *media = (GHashTable *)data;
  // variavel que guarda cada ride da hash Rides
  Ride *ride = (Ride *)value;

  char *rideDriver = getRDriver(ride);
  double rideTotalKm = getRDistance(ride);

  char *city = getRCity(ride);
  char *cityFilter = ((q4Aux *)g_hash_table_lookup(media, "city"))->data_identification;

  // procura se o driver ja existe na hash
  q4Aux *driverToken = g_hash_table_lookup(media, rideDriver);

  // caso exista
  if (!strcmp(city, cityFilter)) {
    if (driverToken != NULL) {
      // incrementa o valueQty e acrescenta ao somatório o valor da Ride atual
      driverToken->valueQty++;
      driverToken->media = driverToken->media + rideTotalKm;
    }
    // caso não exista
    else {
      // cria espaço para um novo driver do tipo q2Aux
      driverToken = (q4Aux *)malloc(sizeof(q4Aux));
      // atribui os valores necessários (de modo a poder ser libertado mais tarde)
      driverToken->data_identification = rideDriver;
      driverToken->valueQty = 1;
      driverToken->media = rideTotalKm;
      // insere na hash
      g_hash_table_insert(media, driverToken->data_identification, driverToken);
    }
  }
}

void totalPriceCalculator(gpointer key, gpointer value, gpointer data) {

  // Variavel que vai permitir o acesso aos Drivers
  Driver *driver = (Driver *)value;

  // hash que guarda as estruturas com o id dos driver e os km feitos na cidade
  GHashTable *driversInf = (GHashTable *)data;

  char *driverId = getDID(driver);
  char *carClass = getDCarClass(driver);

  // Variavel que guarda a struct da cidade para prencher com os preços totais de cada condutor
  q4Aux *city = g_hash_table_lookup(driversInf, "city");
  // Variavel que que verifica se certo condutor fez viagens nessa cidade
  q4Aux *driverInf = g_hash_table_lookup(driversInf, driverId);

  if (driverInf && !strcmp(carClass, "basic"))
  {
    city->media = city->media + driverInf->media * 0.62 + driverInf->valueQty * 3.25;
    city->valueQty += driverInf->valueQty;
  }
  else if (driverInf && !strcmp(carClass, "green"))
  {
    city->media = city->media + driverInf->media * 0.79 + driverInf->valueQty * 4.0;
    city->valueQty += driverInf->valueQty;
  }
  else if (driverInf && !strcmp(carClass, "premium"))
  {
    city->media = city->media + driverInf->media * 0.94 + driverInf->valueQty * 5.2;
    city->valueQty += driverInf->valueQty;
  }
  else
    printf("NAO ENCONTREI\n");

  free(driverId);
  free(carClass);
}

char *q4(Catalog *catalog, char *city) {
  // Hash que vai conter todas as structs temporárias da soma dos KM (nao precisa de keyDestroy)
  GHashTable *driversTotalKm = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, destroyQ4Aux);
  // Allocação e inicialização da struct com as informações da cidade(nome/soma dos preços medios/total de somas)
  q4Aux *cityToken = (q4Aux *)malloc(sizeof(q4Aux));
  cityToken->data_identification = strdup(city);
  cityToken->media = 0;
  cityToken->valueQty = 0;

  // Inserir a cidade na hash para passar a informação para dentro do foreach
  g_hash_table_insert(driversTotalKm, "city", cityToken);
  // Função que vai prencher a hash com structs dos condutores e os Km que fizeram viagens na cidade
  g_hash_table_foreach(catalog->rides, interactPriceMedia, driversTotalKm);
  
  //Se a hash não contem nenhum driver então a cidade não existe(retorna -1)
  if (g_hash_table_size(driversTotalKm) > 1) {
    // Função que vai retirar a classe do Driver e os preços por viagem e Km
    g_hash_table_foreach(catalog->drivers, totalPriceCalculator, driversTotalKm);

    // Retira da hash apenas a cidade ja com o sumatório de todos os preços
    g_hash_table_steal(driversTotalKm, "city");

    // calcula a média
    cityToken->media = cityToken->media / cityToken->valueQty;

    // numero de caracteres em cityToken->media, vezes 5
    // para ter certeza que haverá espaço suficiente
    size_t outputLength = 7 * 5;
    char *output = calloc(outputLength, sizeof(char));
    sprintf(output, "%.3f", cityToken->media);

    return output;
  }

  // Destroi todos os driver depois de já não serem necessarias as informações
  g_hash_table_destroy(driversTotalKm);

  return NULL;
}