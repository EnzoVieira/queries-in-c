#include "../../includes/pagination.h"

#include "../../includes/terminal.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINES_PER_PAGE 10

typedef struct page_s {
  char *content;
  struct page_s *nextPage;
  struct page_s *prevPage;
} Page;

typedef struct {
  unsigned int numOfPages;
  unsigned int currentPageIndex;
  Page *currentPage;
  Page *firstPage;
  Page *lastPage;
} Pagination;

Page *initPage(char *multilineString) {
  Page *page = calloc(1, sizeof(Page));

  page->content = multilineString;
  page->nextPage = NULL;
  page->prevPage = NULL;

  return page;
}

Pagination *initPagination() {
  Pagination *pagination = calloc(1, sizeof(Pagination));
  
  pagination->numOfPages = 0;
  pagination->currentPageIndex = 0;
  pagination->currentPage = NULL;
  pagination->firstPage = NULL;
  pagination->lastPage = NULL;

  return pagination;
}

int isLastLine(char *line) {
  // Avança até o primeiro \n
  while (*line != '\n') {
    line++;
  }

  // Se houver algo depois do \n, não é a última linha
  if (line[1] != '\0') return 0;

  return 1;
}

char *advanceLine(char *strPointer) {
  while (*strPointer != '\n' && *strPointer != '\0') {
    strPointer++;
  }

  // pula o último \n
  if (*strPointer == '\n') strPointer++;

  return strPointer;
}

Page *getNextPagePointer(Page *page) {
  char *linePointer = page->content;
  int lineCount = 0;

  while (lineCount < 10) {
    linePointer = advanceLine(linePointer);
    lineCount++;
  }

  Page *newPage = initPage(linePointer);
  newPage->prevPage = page;

  return newPage;
}

void fillPagination(Page *firstPage, Pagination *pagination) {
  pagination->firstPage = firstPage;
  pagination->currentPage = firstPage;
  if (firstPage != NULL) pagination->numOfPages++;

  Page *currentPage = firstPage;
  char *nextLine = currentPage->content;
  int lineCount = 0;

  while (!isLastLine(nextLine)) {
    nextLine = advanceLine(nextLine);
    lineCount++;

    if (lineCount >= 10) {
      currentPage->nextPage = getNextPagePointer(currentPage);
      currentPage = currentPage->nextPage;

      pagination->numOfPages++;

      lineCount = 0;
    }
  }

  pagination->lastPage = currentPage;
}

// Printa uma linha até achar um \n ou \0
void printLine(char *str) {
  for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
    printf("%c", str[i]);
  }

  printf("\n");
}

// Printa uma página inteira
void printPage(Page *page) {
  char *contentCopyPointer = page->content;
  // Linha atual
  int lineCount = 0;

  printLine(page->content);

  while (lineCount < MAX_LINES_PER_PAGE - 1 && *contentCopyPointer != '\0') {
    if (*contentCopyPointer == '\n') {
      // Pula o \n
      contentCopyPointer++;

      printLine(contentCopyPointer);

      lineCount++;
    }

    contentCopyPointer++;
  }

  printf("\n");
}

// seleciona a página escolhida
// retorna de obteve sucesso ou não
int goToPage(unsigned int page, Pagination *pagination) {
  if (page > pagination->numOfPages) return 0;

  while (page-1 < pagination->currentPageIndex) {
    pagination->currentPageIndex--;
    pagination->currentPage = pagination->currentPage->prevPage;
  }

  while (page-1 > pagination->currentPageIndex) {
    pagination->currentPageIndex++;
    pagination->currentPage = pagination->currentPage->nextPage;
  }

  return 1;
}

// FIXME: Remover esta função depois
char *readInput2() {
  char *line = (char*) calloc(sizeof(char), 100);
  unsigned int len;
  size_t bufferSize = 100;

  len = getline(&line, &bufferSize, stdin);
  len--;
  line[len] = 0;

  return line;
}

void pagination(char *multilineString) {
  Page *firstPage = initPage(multilineString);
  Pagination *pagination = initPagination();

  fillPagination(firstPage, pagination);

  // Printar informações sobre o sistema de paginação
  blueColor();
  printf("\n> Resultado muito grande.\n");
  printf("> É possível navegar entre %d página(s)\n\n", pagination->numOfPages);
  printf("> Digite o número da página que deseja vizualizar.\n\n");
  resetColor();

  // Input de paginação
  char *input = "1";
  while(strcmp(input, "exit") != 0) {
    int pageNum = atoi(input);

    if (pageNum <= 0) {
      redColor();
      printf("> Não é possível acessar uma página negativa.\n");
      printf("> Digite um número válido.\n\n");
    }
    else if (goToPage(pageNum, pagination)) {
      blueColor();
      printf("=== Página %d/%d ===\n\n", atoi(input), pagination->numOfPages);

      greenColor();
      printPage(pagination->currentPage);
    }
    else {
      redColor();
      printf("> Página excede o número de páginas existentes.\n");
      printf("> Digite um número válido.\n\n");
    }
    resetColor();

    input = readInput2();

    printf("\n");
  }

  free(input);
}
