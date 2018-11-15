#include "wiki.h"
#include "string.h"

#define TABLE_SIZE 65536

typedef struct ChainedListSt {
  Entry entry;
  struct ChainedListSt* next;
}* ChainedList;

struct WikiSt {
  ChainedList table[TABLE_SIZE];
};


Wiki createWiki()
{
  Wiki w = malloc(sizeof(struct WikiSt));
  memset(w->table, 0, TABLE_SIZE);
  return w;
}

Wiki insert(Wiki w, Entry e)
{
  ChainedList l = malloc(sizeof(struct ChainedListSt));
  l->entry = e;
  l->next = w->table[e.id%TABLE_SIZE];
  w->table[e.id%TABLE_SIZE] = l;
  return w;
}

Wiki del(Wiki w, Id id)
{
  ChainedList l = w->table[id%TABLE_SIZE];
  ChainedList prev = NULL;
  while (l && l->entry.id != id) {
    prev = l;
    l = l->next;
  }
  if (l) {
    if (prev) {
      prev->next = l->next;
    } else {
      w->table[id%TABLE_SIZE] = l->next;
    }
    freeEntry(l->entry);
    free(l);
  }
  return w;
}

Entry search(Wiki w, Id id)
{
  ChainedList l = w->table[id%TABLE_SIZE];
  while (l && l->entry.id != id)
    l = l->next;
  if (l)
    return l->entry;
  Entry e = {0};
  return e;
}

Wiki searchTxt(Wiki w, char* txt)
{
  Wiki ret = createWiki();
  for (size_t i = 0; i < TABLE_SIZE; i++) {
    ChainedList l = w->table[i];
    while (l) {
      if (strstr(l->entry.content, txt))
        insert(ret, l->entry);
      l = l->next;
    }
  }
  return ret;
}

void destroy(Wiki w)
{
  for (size_t i = 0; i < TABLE_SIZE; i++) {
    ChainedList l = w->table[i];
    while (l) {
      ChainedList tmp = l;
      l = l->next;
      freeEntry(tmp->entry);
      free(tmp);
    }
  }
}

void printWiki(Wiki w)
{
  for (size_t i = 0; i < TABLE_SIZE; i++) {
    ChainedList l = w->table[i];
    while (l) {
      printEntry(l->entry);
      l = l->next;
    }
  }

}
