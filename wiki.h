#include <stdlib.h>

typedef size_t Id;

typedef struct EntrySt {
  Id id;
  char *title;
  char *content;
} Entry;

struct WikiSt;
typedef struct WikiSt* Wiki;


Wiki createWiki();

Wiki insert(Wiki w, Entry  e);

Wiki del(Wiki w, Id id);

Entry search(Wiki w, Id id);

Wiki searchTxt(Wiki w, char* txt);

void destroy(Wiki w);

void printWiki(Wiki w);


//utility functions

void printEntry(Entry e);

Wiki loadFile(char* file);

unsigned long hash(char*, size_t n);
