COMP := gcc
FLAGS := -std=c11 -g

all: tree chainlist hashtable

chainlist:
	${COMP} main.c chainlist.c -o chainlist.exe ${FLAGS}

tree:
	${COMP} main.c tree.c -o tree.exe ${FLAGS}

hashtable:
	$(COMP) main.c hashtable.c -o hashtable.exe ${FLAGS}

clean:
	rm *.o
