CC = gcc -g -Wall

OBJS =	driver.o \
			dna.o \
			gc.o \
			hamm.o \
			rna.o \
			revc.o \
			display.o \
			help_func.o

SRC =		driver.c \
			display.c \
			display.h \
			dna.c \
			dna.h \
			gc.c \
			gc.h \
			hamm.c \
			hamm.h \
			rna.c \
			rna.h \
			revc.c \
			revc.h \
			help_func.c \
			help_func.h

all: rosalind

driver.o:		driver.c dna.h display.h gc.h help_func.h revc.h rna.h \
					hamm.h
					$(CC) -c driver.c

dna.o:			dna.c dna.h help_func.h
					$(CC) -c dna.c

gc.o:				gc.c gc.h help_func.h
					$(CC) -c gc.c

hamm.o:			hamm.c hamm.h help_func.h
					$(CC) -c hamm.c

rna.o:			rna.c rna.h help_func.h
					$(CC) -c rna.c

revc.o:			revc.c revc.h help_func.h
					$(CC) -c revc.c

display.o:		display.c display.h
					$(CC) -c display.c

help_func.o:	help_func.c help_func.h
					$(CC) -c help_func.c

rosalind:		$(OBJS)
					$(CC) $(OBJS) -o rosalind

clean:
					rm -f *.o rosalind core
