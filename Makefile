COMP := clang
FLAGS := -std=c11 -g -Weverything

all: tree linkedlist hashtable

linkedlist:
	${COMP} main.c linkedlist.c -o linkedlist.exe ${FLAGS}

tree:
	${COMP} main.c tree.c -o tree.exe ${FLAGS}

hashtable:
	$(COMP) main.c hashtable.c -o hashtable.exe ${FLAGS}

clean:
	rm *.o
