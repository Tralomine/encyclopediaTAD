COMP := gcc
FLAGS := -std=c11 -g

all: tree

tree:
	${COMP} main.c tree.c -o tree.out ${FLAGS}

clean:
	rm *.o
