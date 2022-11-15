#This is a makefile

CC = gcc
CFLAGS = -Wall `pkg-config --cflags --libs glib-2.0`
OBJ = test
FILES = files/useCases/*.c files/api/*.c files/modules/**/*.c files/lexer/*.c

all:
	$(CC) main.c $(FILES) -o $(OBJ) $(CFLAGS)

exec:
	./test "files/data" "exemplos_de_queries2/tests_2/input.txt"

clean:
	rm -rf test
	rm -rf *.ex
	rm -rf *.o
	rm -rf Resultados/*