#include <stdio.h>
#include <string.h>

#include "includes/database.h"

#include "includes/lexer.h"
#include "includes/reader.h"
#include "includes/parser.h"

struct catalog {
    void *users;
    void *drivers;
    void *rides;
};

int main(int argc, char *argv[]) {
    printf("\n🚀 A executar o programa...\n");

    if(argc < 3) {
        printf("Argumentos insuficientes\n");
        exit(1);
    }

    printf("\n🌱 A criar as seeds da database...\n");

    Catalog *catalog = seedDatabase(argv[1]);

    printf("\n✅ Tabelas criadas com sucesso!\n");
    printf("\n📚 A executar as queries...\n");

    char *args = readFile(argv[2]);
    Lexer *lexer = createLexer(args);
    parser(lexer, catalog);

    free(args);

    printf("\n✅ Programa finalizado com sucesso!\n");

    return 0;
}
