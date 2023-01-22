#This is a makefile

CC = gcc
CFLAGS = -Wall `pkg-config --cflags --libs glib-2.0`
OBJ = programa-principal
FILES = src/modules/**/*.c src/database/*.c src/parsing/*.c src/queries/*.c src/utils/*.c src/interactive/*.c

OBJTEST = programa-testes
TESTFILES = src/modules/**/*.c src/database/*.c src/parsing/*.c src/queries/*.c src/utils/*.c

all:
	$(CC) main.c $(FILES) -o $(OBJ) $(CFLAGS)
	$(CC) tests/main.c $(TESTFILES) -o $(OBJTEST) $(CFLAGS)

exec:
	./programa-principal "src/data" "exemplos_de_queries2/tests_2/input.txt"

test:
	./programa-testes "src/data" "exemplos_de_queries2/tests_2/input.txt"

clean:
	rm -rf test
	rm -rf *.ex
	rm -rf *.o
	rm -rf Resultados/*
