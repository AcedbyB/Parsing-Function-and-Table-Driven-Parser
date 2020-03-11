#
# File: Makefile
# Creator: George Ferguson
# Created: Thu Jun 30 11:00:49 2016
# Time-stamp: <Sun Aug  5 15:17:51 EDT 2018 ferguson>
#
# Sample Makefile distributed with CSC173 Project 1 code bundle
#
# This Makefile builds the test programs for the data structures
# distributed with the bundle, and show how you might use it to
# build YOUR program for the project.
#

PROGRAMS = rexp 

CFLAGS = -g -std=c99 -Wall -Werror

programs: $(PROGRAMS)

rexp: main.o
	$(CC) -o $@ $^

:
	$(CC) -o $@ $(CFLAGS) -DMAIN $@.c

clean:
	-rm $(PROGRAMS) *.o
	-rm -r *.dSYM
