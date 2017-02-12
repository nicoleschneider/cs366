# target: prereq
# <tab>commands

all: wash

wash: wash.c
        $(CC) $(CFLAGS) -o wash wash.c $(TIMER)

a.out: wash.o
        gcc wash.o

wash.o: wash.c
        gcc -Wall -c wash.c

clean:
        /bin/rm wash.o a.out
