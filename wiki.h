#include <stdlib.h>

typedef int bool;
#define true 1;
#define false 0;

typedef size_t Id;

typedef struct EntrySt {
  Id id;
  char *title;
  char *content;
} Entry;

struct WikiSt;
typedef struct WikiSt* Wiki;

/* -------------------------
@pre-condition:
@post-condition: The wiki exists. (It is considered implicit that the wiki is valid.)
@invariant:
------------------------ */
Wiki createWiki();

/* -------------------------
@pre-condition:
@post-condition: The entry has been registered in the wiki.
@invariant: The wiki exists.
------------------------ */
Wiki insert(Wiki w, Entry e);

/* -------------------------
@pre-condition:
@post-condition: The entry with the selected ID has been deleted from the wiki.
@invariant: The wiki exists.
------------------------ */
Wiki del(Wiki w, Id id);

/* -------------------------
@pre-condition:
@post-condition:
@invariant: The wiki exists.
------------------------ */
Entry search(Wiki w, Id id);

/* -------------------------
@pre-condition:
@post-condition:
@invariant: The wiki exists.
------------------------ */
Wiki searchTxt(Wiki w, char* txt);

/* -------------------------
@pre-condition: The wiki exists.
@post-condition:
@invariant:
------------------------ */
void destroy(Wiki w);

/* -------------------------
@pre-condition:
@post-condition:
@invariant: The wiki exists.
------------------------ */
void printWiki(Wiki w);


//utility functions

void printEntry(Entry e);

/* -------------------------
@pre-condition:
@post-condition: One specific entry in the wiki has been deleted.
@invariant: The wiki exists.
------------------------ */
void freeEntry(Entry e);

/* -------------------------
@pre-condition:
@post-condition: The file has been loaded and can be used in the main.
@invariant:
------------------------ */
Wiki loadFile(char* file);

/* -------------------------
@pre-condition:
@post-condition:
@invariant: The wiki exists.
------------------------ */
Entry copyEntry(Entry e);
