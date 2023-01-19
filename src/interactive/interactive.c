#include "../../includes/interactive.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 1000
#define MAX_COMMANDS_PER_INPUT_LEN 10
#define MAX_COMMAND_LEN 100
#define REGEX_OPTIONS_LEN 7

#define AC_BLUE "\x1b[34m"
#define AC_GREEN "\x1b[32m"
#define AC_NORMAL "\033[0m"

typedef enum {
  ON,
  OFF
} Status;

typedef enum {
  NOT_FOUND,    // 0
  REGEX_ERROR,  // 1
  QUERY,        // 2
  ID,           // 3
  USERNAME,     // 4
  DATE,         // 5
  DIR_PATH,     // 6
  INFO,         // 7
  EXIT          // 8
} Command;

typedef struct {
  Command commandType;
  char *token;
} CommandToken;

typedef struct {
    char regex[MAX_COMMAND_LEN];
    Command command;
} RegexOption;

RegexOption options[REGEX_OPTIONS_LEN] = {
  { "^(query[1-9]|q[1-9]|[1-9]{1})$", QUERY }, // query1 ou q1 ou 1 exatamente
  { "^[0-9]{12}$", ID }, // Exatamente 12 digitos de 0-9
  { "^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/[0-9]{4}$", DATE }, // Apenas datas válidas no formato nn/nn/nnnn
  { "^(.+)/([^/]+)$", DIR_PATH }, // Caminhos de diretórios
  { "^info$", INFO }, // Exatamente 'info'
  { "^exit$", EXIT }, // Exatamente 'exit'
  { "^.+$", USERNAME }, // Qualquer outra coisa será interpretada como um username
};

// Verifica se uma string da match com o regex
// retorna o comando encontrado se der match
// retorna NOT_FOUND se não der match com nenhum comando
// retorna REGEX_ERROR se der erro ao compilar o regex
Command useRegex(char* textToCheck) {
  regex_t compiledRegex;
  int reti;
  
  for (int i = 0; i < REGEX_OPTIONS_LEN; i++) {
    reti = regcomp(&compiledRegex, options[i].regex, REG_EXTENDED | REG_ICASE);
    if (reti) {
      printf("Could not compile regex\n");
      return REGEX_ERROR;
    }

    reti = regexec(&compiledRegex, textToCheck, 0, NULL, 0);
    if (reti == 0) {
      regfree(&compiledRegex);
      return options[i].command;
    }
  }

  regfree(&compiledRegex);
  return NOT_FOUND;
}

// Retorna um array de comandos na linha do input e coloca em 'size' o tamanho do array
CommandToken *identifyCommands(char *line, int *size) {
  char delim[] = " ";
  char *token = strtok(line, delim);

  // Cria o array de comandos
  CommandToken *commandsArray = calloc(sizeof(CommandToken), MAX_COMMANDS_PER_INPUT_LEN);
  unsigned int arrayIndex = 0;

  Command command;
  while (token != NULL) {
    // adiciona o token a struct no array de comandos
    commandsArray[arrayIndex].token = token;

    // Identifica o comando
    command = useRegex(token);
    // Avança para o próximo token
    token = strtok(NULL, delim);

    // Adiciona o comando a struct no array de comandos
    commandsArray[arrayIndex++].commandType = command;
  }

  *size = arrayIndex;
  return commandsArray;
}

// Função que é responsável por saber quantos argumentos cada query espera, e o que fazer com elas.
void handleQueryCommand(CommandToken *commandTokens) {
  int tokenLen = strlen(commandTokens->token);
  char queryNumber = commandTokens->token[tokenLen - 1];

  switch (queryNumber) {
    case '1': {
      commandTokens++;

      printf("A executar query1(%s)...\n\n", commandTokens->token);
      break;
    }

    case '2':
      commandTokens++;

      printf("A executar query2(%s)...\n\n", commandTokens->token);
      break;

    case '3':
      printf("A executar query3(%s)...\n\n", (++commandTokens)->token);
      break;
    
    case '4':
      printf("A executar query4(%s)...\n\n", (++commandTokens)->token);
      break;
    
    case '5': {
      commandTokens++;
      char *arg1 = commandTokens->token;
      commandTokens++;
      char *arg2 = commandTokens->token;

      printf("A executar query5(%s, %s)...\n\n", arg1, arg2);
      break;
    }
    
    case '6': {
      commandTokens++;
      char *arg1 = commandTokens->token;
      commandTokens++;
      char *arg2 = commandTokens->token;
      commandTokens++;
      char *arg3 = commandTokens->token;

      printf("A executar query6(%s, %s, %s)...\n\n", arg1, arg2, arg3);
      break;
    }

    case '7': {
      commandTokens++;
      char *arg1 = commandTokens->token;
      commandTokens++;
      char *arg2 = commandTokens->token;

      printf("A executar query7(%s, %s)...\n\n", arg1, arg2);
      break;
    }

    case '8': {
      commandTokens++;
      char *arg1 = commandTokens->token;
      commandTokens++;
      char *arg2 = commandTokens->token;

      printf("A executar query8(%s, %s)...\n\n", arg1, arg2);
      break;
    }

    case '9': {
      commandTokens++;
      char *arg1 = commandTokens->token;
      commandTokens++;
      char *arg2 = commandTokens->token;

      printf("A executar query9(%s, %s)...\n\n", arg1, arg2);
      break;
    }

    default:
      break;
  }
}

void handleCommandTokens(Status *status, CommandToken *commandTokens) {
  switch (commandTokens->commandType) {
    case EXIT:
      *status = OFF;
      printf("\n%s> A sair do modo interativo 👋\n", AC_GREEN);
      break;

    case INFO:
      printf("\n%s> Informações sobre o menu:\n", AC_BLUE);

      printf("\n> Para executar uma query, digite query desejada seguida pelos seus argumentos.\n");
      printf(">> '< query | q | [ID] > [arg1...argN]'\n");
      printf("\nPor exemplo:\n");
      printf("$ 1 <ID>\n");
      printf("$ query1 <ID>\n");
      printf("$ q6 <city> <date A> <date B>%s\n\n", AC_NORMAL);
      break;

    case QUERY:
      handleQueryCommand(commandTokens);
      break;

    case NOT_FOUND:
      printf("\n> Comando não encontrado. Digite 'info' para saber os comandos disponíveis.\n\n");
      break;
    
    default:
      break;
    }
}

// Função que irá ler o input, e depois passá-lo a outra função que ira criar um array de comandos
void readInput(Status *status) {
  char *line = (char*) calloc(sizeof(char), MAX_INPUT_LEN);
  unsigned int len;
  size_t bufferSize = MAX_INPUT_LEN;

  len = getline(&line, &bufferSize, stdin);
  len--;
  line[len] = 0;

  int arraySize = 0;
  CommandToken *commandsArray = identifyCommands(line, &arraySize);

  handleCommandTokens(status, commandsArray);
}

void interactiveMode() {
  Status status = ON;

  printf("\n%s> Você entrou no modo interativo\n", AC_BLUE);
  printf("> Digite 'info' para mostrar comandos possíveis do menu\n");
  printf("> Digite 'exit' a qualquer momento para sair%s\n\n", AC_NORMAL);

  while(status != OFF) {
    readInput(&status);
  }
}
