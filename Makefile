#This is a makefile

CC = gcc
CFLAGS = -Wall `pkg-config --cflags --libs glib-2.0`
OBJ = test
FILES = files/useCases/*.c files/api/*.c files/modules/**/*.c 

all:
	$(CC) joel.c $(FILES) -o $(OBJ) $(CFLAGS)

exec:
	./test

clean:
	rm -rf test
	rm -rf *.ex
	rm -rf *.o