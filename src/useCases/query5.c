#include "../../includes/query4.h"
#include "../../includes/writer.h"

#include "../../includes/driverRepository.h"
#include "../../includes/rideRepository.h"
#include "../../includes/date.h"

// FIXME: Remover glib
#include <glib.h>
#include <stdio.h>

struct catalog {
  void *users;
  void *drivers;
  void *rides;
};

typedef struct querie5Aux {

  char *data_identification;
  double priceAcc;
  double priceAccAddendsQty;
} q5Aux;

typedef struct foreachAux{
  char* dataA;
  char* dataB;
  double totalPriceAcc;
  double totalPriceAccAddendsQty;
  HashTable* driversTable;
}ForeachAux;

void destroyQ5Aux(void *u) {
  q5Aux *destroyME = (q5Aux *)u;
  if (destroyME)
  {
    if (destroyME->data_identification)
      free(destroyME->data_identification);
  }
  destroyME = NULL;
}

void createTableOfDriversKm(gpointer key, gpointer value, gpointer data) {

  // hash a ser preenchida com q5Aux(Driver;soma total km;total de elementos na soma)
  ForeachAux *foreachAux = (ForeachAux*)data;
  // variavel que guarda cada ride da hash Rides
  Ride *ride = (Ride *)value;

  char *rideDriver = getRDriver(ride);
  double rideTotalKm = getRDistance(ride);
  char* curretRideDate = getRDate(ride);


  // caso exista
  if (isDateBetween(foreachAux->dataA,curretRideDate,foreachAux->dataB)) {
  // procura se o driver ja existe na hash
  q5Aux *driverToken = findBy(foreachAux->driversTable, rideDriver);
    if (driverToken != NULL) {
      // incrementa o priceAccAddendsQty e acrescenta ao somatório o valor da Ride atual
      driverToken->priceAccAddendsQty++;
      driverToken->priceAcc = driverToken->priceAcc + rideTotalKm;
    }
    // caso não exista
    else {
      // cria espaço para um novo driver do tipo q2Aux
      driverToken = (q5Aux *)malloc(sizeof(q5Aux));
      // atribui os valores necessários (de modo a poder ser libertado mais tarde)
      driverToken->data_identification = rideDriver;
      driverToken->priceAccAddendsQty = 1;
      driverToken->priceAcc = rideTotalKm;
      // insere na hash
      addToTable(foreachAux->driversTable, driverToken->data_identification, driverToken);
    }
  }
}

void totalPriceCalculator2(void *key, void *value, void *data) {

  // Variavel que vai permitir o acesso aos Drivers
  Driver *driver = (Driver *)value;

  // hash que guarda as estruturas com o id dos driver e os km feitos na cidade
  ForeachAux* foreachAux = (ForeachAux*)data;

  char *driverId = getDID(driver);
  char *carClass = getDCarClass(driver);

  // Variavel que que verifica se certo condutor fez viagens nessa cidade
  q5Aux *driverInf = findBy(foreachAux->driversTable, driverId);


  if (driverInf && !strcmp(carClass, "basic")){

    foreachAux->totalPriceAcc = foreachAux->totalPriceAcc + driverInf->priceAcc * 0.62 + driverInf->priceAccAddendsQty * 3.25;
    foreachAux->totalPriceAccAddendsQty += driverInf->priceAccAddendsQty;
  }
  else if (driverInf && !strcmp(carClass, "green"))
  {
    foreachAux->totalPriceAcc = foreachAux->totalPriceAcc + driverInf->priceAcc * 0.79 + driverInf->priceAccAddendsQty * 4.0;
    foreachAux->totalPriceAccAddendsQty += driverInf->priceAccAddendsQty;
  }
  else if (driverInf && !strcmp(carClass, "premium"))
  {
    foreachAux->totalPriceAcc = foreachAux->totalPriceAcc + driverInf->priceAcc * 0.94 + driverInf->priceAccAddendsQty * 5.2;
    foreachAux->totalPriceAccAddendsQty += driverInf->priceAccAddendsQty;
  }

  free(driverId);
  free(carClass);
}

char *q5(Catalog *catalog,char* dateA, char* dateB) {
  // Allocação e inicialização da struct com as informações da cidade(nome/soma dos preços medios/total de somas)
  ForeachAux *foreachAux = (ForeachAux*)malloc(sizeof(ForeachAux));
  foreachAux->dataA = strdup(dateA);
  foreachAux->dataB = strdup(dateB);
  foreachAux->totalPriceAcc = 0;
  foreachAux->totalPriceAccAddendsQty = 0;
  foreachAux->driversTable = createTable(destroyQ4Aux);
  // Função que vai prencher a hash com structs dos condutores e os Km que fizeram viagens na cidade
  foreach(catalog->rides, createTableOfDriversKm, foreachAux);
  
  //Se a hash não contem nenhum driver então a cidade não existe(retorna -1)
  if (hashSize(foreachAux->driversTable) > 0) {
    // Função que vai retirar a classe do Driver e os preços por viagem e Km
    foreach(catalog->drivers, totalPriceCalculator2, foreachAux);

    double priceMedia = foreachAux->totalPriceAcc/foreachAux->totalPriceAccAddendsQty;

    // numero de caracteres em cityToken->priceAcc, vezes 5
    // para ter certeza que haverá espaço suficiente
    size_t outputLength = 7 * 5;
    char *output = calloc(outputLength, sizeof(char));
    sprintf(output, "%.3f\n", priceMedia);

    return output;
  }

  // Destroi todos os driver depois de já não serem necessarias as informações
  //g_hash_table_destroy(foreachAux->driversTable);

  return NULL;
}