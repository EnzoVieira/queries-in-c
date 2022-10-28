#This is a makefile

CC = gcc
CFLAGS = -Wall `pkg-config --cflags --libs glib-2.0`
OBJ = test

all:
	$(CC) users.c $(CFLAGS) -o $(OBJ)

exec:
	./test

clean:
	rm -rf test
	rm -rf *.ex
	rm -rf *.o