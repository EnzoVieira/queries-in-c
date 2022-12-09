#This is a makefile

CC = gcc
CFLAGS = -Wall `pkg-config --cflags --libs glib-2.0`
OBJ = programa-principal
FILES = src/modules/**/*.c src/database/*.c

OBJTEST = programa-testes
TESTFILES = src/api/*.c src/database/*.c src/modules/**/*.c src/useCases/*.c src/lexer/*.c src/utils/*.c tests/useCases/*.c tests/utils/*.c

all:
	$(CC) main.c $(FILES) -o $(OBJ) $(CFLAGS)

# $(CC) tests/main.c $(TESTFILES) -o $(OBJTEST) $(CFLAGS)

exec:
	./programa-principal "src/data" "exemplos_de_queries2/tests_2/input.txt"

# test:
# 	clear && ./programa-testes "src/data" "exemplos_de_queries2/tests_2/input.txt"

clean:
	rm -rf test
	rm -rf *.ex
	rm -rf *.o
	rm -rf Resultados/*