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


Wiki createWiki();

Wiki insert(Wiki w, Entry e);

Wiki del(Wiki w, Id id);

Entry search(Wiki w, Id id);

Wiki searchTxt(Wiki w, char* txt);

void destroy(Wiki w);

void printWiki(Wiki w);


//utility functions

void printEntry(Entry e);

void freeEntry(Entry e);

Wiki loadFile(char* file);

Entry copyEntry(Entry e);
