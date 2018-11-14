COMP := gcc
FLAGS := -std=c11

all:
	${COMP} main.c

clean:
	rm *.o
