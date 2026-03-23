#makefile

CC=gcc
CFLAGS=-Wall
MFLAGS=-lm
OPT=-O2
all:politropy
politropy:politropy.o calculations.o functions.o io.o opt.o
	$(CC) $(OPT) -o politropy politropy.o calculations.o functions.o io.o opt.o $(CFLAGS) $(MFLAGS)
politropy.o:politropy.c functions.h opt.h io.h
	$(CC) $(OPT) -c politropy.c -o politropy.o $(CFLAGS)
calculations.o:calculations.c calculations.h functions.c functions.h
	$(CC) $(OPT) -c calculations.c -o calculations.o $(CFLAGS)
functions.o:functions.c functions.h
	$(CC) $(OPT) -c functions.c -o functions.o $(CFLAGS)
io.o:io.c io.h
	$(CC) $(OPT) -c io.c -o io.o $(CLFAGS)
opt.o:opt.c opt.h
	$(CC) $(OPT) -c opt.c -o opt.o $(CFLAGS)
clean:
	rm -f *.o *~

























