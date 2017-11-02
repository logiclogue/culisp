CC=gcc
CFLAGS=-Wall -O3 -std=c99 -pedantic
BUILDFLAGS=
LDFLAGS=
DIRBUILD=build
DIRSRC=src
SOURCES=$(shell ls $(DIRSRC)/*.c)
EXECUTABLE=$(DIRBUILD)/culisp

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):
	mkdir -p $(DIRBUILD)
	$(CC) $(LDFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)

.PHONY: clean all $(DIRSRC)/main.c
