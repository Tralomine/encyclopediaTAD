COMP := gcc
FLAGS := -std=c11 -g

all: tree chainlist

chainlist:
	${COMP} main.c chainlist.c -o chainlist.exe ${FLAGS}

tree:
	${COMP} main.c tree.c -o tree.exe ${FLAGS}

clean:
	rm *.o
