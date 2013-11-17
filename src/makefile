SHELL    = /bin/bash
UTILDIR  = ../util

CC       = gcc -std=c99
CFBASE   = -Wall -pedantic 
CFLAGS   = $(CFBASE) -DNDEBUG -O3
INCS     = -I$(UTILDIR)

LD       = gcc
LIBDIR   = -L../util
LIBS     = -lm -lhts

OBJS     = test.o

PRGS     = main

#-----------------------------------------------------------------------
# Build Program
#-----------------------------------------------------------------------
all:        $(PRGS)

main:       $(OBJS) statics makefile
	$(LD) $(OBJS) $(LIBDIR) $(LIBS) -o $@

#-----------------------------------------------------------------------
# Main Program
#-----------------------------------------------------------------------
test.o: test.c makefile
	$(CC) $(CFLAGS) $(INCS) -c test.c -o $@

#-----------------------------------------------------------------------
# External Modules
#-----------------------------------------------------------------------
statics:
	cd $(UTILDIR);  $(MAKE) libhts.a
#-----------------------------------------------------------------------
# Installation
#-----------------------------------------------------------------------
install:
	cp $(PRGS) $(HOME)/bin

#-----------------------------------------------------------------------
# Clean up
#-----------------------------------------------------------------------
localclean:
	rm -f *.o *~ *.flc core $(PRGS)

clean:
	$(MAKE) localclean
	cd $(UTILDIR);  $(MAKE) clean
