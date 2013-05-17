SHELL    = /bin/bash
UTILDIR  = ../util/

CC       = gcc -std=c99
CFBASE   = -Wall -pedantic $(ADDFLAGS)
CFLAGS   = $(CFBASE) -DNDEBUG -O3
INCS     = -I$(UTILDIR)

LD       = gcc
LDFLAGS  = 
LIBS     = -lm

HDRS     = $(UTILDIR)/hashtable.h
OBJS     = $(UTILDIR)/hashtable.o  \
           test.o

PRGS     = main

#-----------------------------------------------------------------------
# Build Program
#-----------------------------------------------------------------------
all:        $(PRGS)

main:       $(OBJS) makefile
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

#-----------------------------------------------------------------------
# Main Program
#-----------------------------------------------------------------------
test.o: test.c makefile
	$(CC) $(CFLAGS) $(INCS) -c test.c -o $@

#-----------------------------------------------------------------------
# External Modules
#-----------------------------------------------------------------------
$(UTILDIR)/hashtable.o:
	cd $(UTILDIR);  $(MAKE) hashtable.o  ADDFLAGS=$(ADDFLAGS)

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
