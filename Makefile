CC = gcc
DEBUGGER = lldb
CFLAGS = -Wall -Wextra -Wno-unused-parameter -g `pkg-config --cflags --libs glib-2.0`
VALFLAGS = --leak-check=full

SRC = ./src
TESTSRC = ./tests
MAINFILE = main.c
TESTMAINFILE = tests/main.c

FILES = $(shell find $(SRC) -name '*.c')
TESTFILES = $(shell find $(SRC) -name '*.c') $(shell find $(TESTSRC) -name '*.c' | grep -v '$(TESTMAINFILE)')
INCLUDE = ./includes
TESTINCLUDE = ./tests/includes

DATA = "config/data"
INPUTS = "config/inputs/inputs2/input.txt"
RES = Resultados

PBINARY = programa-principal
SBINARY = programa-testes

all: $(PBINARY) $(SBINARY)

exec: $(PBINARY) clean_result
	./$< $(DATA) $(INPUTS)

test: $(SBINARY)
	clear && ./$< $(DATA) $(INPUTS)

it: $(PBINARY)
	./$<

debug: $(PBINARY) clean_result
	$(DEBUGGER) $< $(DATA) $(INPUTS)

$(PBINARY): main.c $(FILES)
	$(CC) $< $(FILES) -o $@ $(CFLAGS)

$(SBINARY): tests/main.c $(TESTFILES)
	$(CC) $< $(TESTFILES) -o $@ $(CFLAGS)

clean_result:
	rm -rf $(RES)

clean: 
	rm -rf $(PBINARY) $(SBINARY) $(RES)

valgrind: $(PBINARY)
	valgrind $(VALFLAGS) $< $(DATA) $(INPUTS)

