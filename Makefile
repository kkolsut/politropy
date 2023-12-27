#makefile

CC=gcc
CFLAGS=-Wall
MFLAGS=-lm
OPT=-O2
all:politropy
politropy:politropy.o obliczenia.o funkcje.o io.o opt.o
	$(CC) $(OPT) -o politropy politropy.o obliczenia.o funkcje.o io.o opt.o $(CFLAGS) $(MFLAGS)
politropy.o:politropy.cc funkcje.h opt.h io.h
	$(CC) $(OPT) -c politropy.cc -o politropy.o $(CFLAGS)
obliczenia.o:obliczenia.cc obliczenia.h funkcje.cc funkcje.h
	$(CC) $(OPT) -c obliczenia.cc -o obliczenia.o $(CFLAGS)
funkcje.o:funkcje.cc funkcje.h
	$(CC) $(OPT) -c funkcje.cc -o funkcje.o $(CFLAGS)
io.o:io.cc io.h
	$(CC) $(OPT) -c io.cc -o io.o $(CLFAGS)
opt.o:opt.cc opt.h
	$(CC) $(OPT) -c opt.cc -o opt.o $(CFLAGS)
clean:
	rm -f *.o *~

























