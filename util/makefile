SHELL    = /bin/bash

CC       = gcc -std=c99
CFBASE   = -Wall -pedantic 
CFLAGS   = $(CFBASE) -DNDEBUG -O3

LD       = gcc
LDFLAGS  = 
LIBS     = 

PRGS     = hashtable.o

all:        $(PRGS)

hashtable.o:   hashtable.h hashtable.c makefile
	$(CC) $(CFLAGS) -c hashtable.c -o $@

#-----------------------------------------------------------------------
# Clean up
#-----------------------------------------------------------------------
clean:
	rm -f $(PRGS) *.o 
