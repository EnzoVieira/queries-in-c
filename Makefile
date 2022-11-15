#This is a makefile

CC = gcc
CFLAGS = -Wall `pkg-config --cflags --libs glib-2.0`
OBJ = programa-principal
FILES = files/useCases/*.c files/api/*.c files/modules/**/*.c files/lexer/*.c

OBJTEST = programa-testes
TESTFILES = files/useCases/*.c files/api/*.c files/modules/**/*.c files/lexer/*.c tests/utils/*.c

all:
	$(CC) main.c $(FILES) -o $(OBJ) $(CFLAGS)
	$(CC) tests/main.c $(TESTFILES) -o $(OBJTEST) $(CFLAGS)

exec:
	./programa-principal "files/data" "exemplos_de_queries2/tests_2/input.txt"

test:
	clear && ./programa-testes "files/data" "exemplos_de_queries2/tests_2/input.txt"

clean:
	rm -rf test
	rm -rf *.ex
	rm -rf *.o
	rm -rf Resultados/*