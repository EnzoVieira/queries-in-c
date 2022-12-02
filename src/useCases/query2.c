#include "../../includes/query2.h"

#include "../../includes/api.h"
#include "../../includes/date.h"
#include "../../includes/driverRepository.h"
#include "../../includes/rideRepository.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct catalog {
  void *users;
  void *drivers;
  void *rides;
};

typedef struct querie2Aux{
  char *driverId;
  double scoreAcc;
  double scoreAccAddendsQty;
  double media;
  char *lastRide;
} q2Aux;

// Função utilizada para free da data da hash de SumData
void destroyQ2Aux(void *u)
{
  q2Aux *destroyME = (q2Aux *)u;
  if (destroyME)
  {
    if (destroyME->driverId)
      free(destroyME->driverId);
  }
  destroyME = NULL;
}

// Função comparação para ordenar array de q2Aux (Ordem decrescente)
int compareMedia(void* a, void* b){
  //Variavel que contem os sumatórios das viagens
  q2Aux *driver1 = (q2Aux *)a;
  q2Aux *driver2 = (q2Aux *)b;

  driver1->media = driver1->scoreAcc / driver1->scoreAccAddendsQty;
  driver2->media = driver2->scoreAcc / driver2->scoreAccAddendsQty;

  //Se a média for diferente (ordena pela média maior)
  if (driver1->media != driver2->media){
    return (driver1->media < driver2->media);
  //Se a média for igual (ordena pela data mais recente)
  }else if (compareDates(driver1->lastRide,driver2->lastRide)){
    return compareDates(driver1->lastRide,driver2->lastRide);
  //Se a média e a data são iguais (ordena pelo id crescente)
  }else
    return strcmp(driver1->driverId,driver2->driverId);
}

// Função para criar a hash com os dados driverId e scoreSum
void createTableOfDriversScore(void* key, void* value, void* data){

  // hash a ser preenchida com q2Aux(Driver;Soma dos scores;total de elementos da soma)
  HashTable *driversScoreHash = data;
  // variavel que guarda cada ride da hash Rides
  Ride *ride = (Ride *)value;

  char *rideDriver = getRDriver(ride);
  char* lastRide = getRDate(ride);
  double rideDriverScore = getRScoreDriver(ride);


  // procura se o driver ja existe na hashlastDrive
  q2Aux *driverToken = findBy(driversScoreHash, rideDriver);
  // caso exista
  if (driverToken != NULL){

    // incrementa o scoreAccAddendsQty, acrescenta ao somatório o valor da Ride atual,guarda a viagem mais recente
    driverToken->scoreAccAddendsQty++;
    driverToken->scoreAcc += rideDriverScore;
    if (compareDates(driverToken->lastRide,lastRide)>0){
      driverToken->lastRide = lastRide;
    }
    else free(lastRide);
  }
  // caso não exista
  else{
    // cria espaço para um novo driver do tipo q2Aux
    driverToken = (q2Aux*)malloc(sizeof(q2Aux));
    // atribui os valores necessários (de modo a poder ser libertado mais tarde)
    driverToken->driverId = rideDriver;
    driverToken->scoreAccAddendsQty = 1;
    driverToken->scoreAcc = rideDriverScore;
    driverToken->lastRide = lastRide;
    // insere na hash
    addToTable(driversScoreHash, strdup(rideDriver), driverToken);
  }
}

char *q2(Catalog *catalog, int N) {

  // Hash que vai conter todas as structs temporárias da soma dos scores (nao precisa de keyDestroy)
  HashTable *driversTotalScoreHash = createTable(destroyQ2Aux);
  // Função que vai prencher a hash anterior
  foreach(catalog->rides, createTableOfDriversScore, driversTotalScoreHash);

  // Lista con toda a data da hash
  List *hashContent = getListFromTable(driversTotalScoreHash);
  // Ordenação da Lista por Médias
  hashContent = listSortBy(hashContent, compareMedia, NULL);
  
  size_t lineLength = 12 + 10 + 50;
  char *stringGrande = calloc(lineLength * N, sizeof(char));

  int i = 0, j = N;
  while (i < j) {
    // Guardar o id do elemento da lista em uma variavel para facil leitura
    char *id = (*(q2Aux *)findFromList(hashContent, i)).driverId;

    Driver *driver = findBy(catalog->drivers,id);
    if (getDAccountStatus(driver)) {
      // Guardar a media ja calculada do elemento da lista em uma variavel para facil leitura
      double mediaTotal = (*(q2Aux *)findFromList(hashContent, i)).media;
  
      char *stringAux = calloc(lineLength, sizeof(char));
      sprintf(stringAux, "%s;%s;%.3f\n", id, getDName(driver), mediaTotal);

      strcat(stringGrande, stringAux);

      free(stringAux);


      i++;
    }
    else {
      i++;
      j++;
    }
  }

  // free da lista
  freeList(hashContent);
  // free da hash
  destroyTable(driversTotalScoreHash);

  return stringGrande;
}
