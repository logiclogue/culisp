CC=gcc
CFLAGS=-Wall -O3 -std=c99 -pedantic
BUILDFLAGS=
LDFLAGS=
DIRBUILD=build
DIRSRC=src
SOURCES=$(shell ls $(DIRSRC)/*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLES=$(DIRBUILD)/main

all: $(SOURCES) $(DIRBUILD)/main

$(EXECUTABLES): $(OBJECTS)
	mkdir -p $(DIRBUILD)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(BUILDFLAGS) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)

.PHONY: clean all install $(DIRSRC)/main.c
