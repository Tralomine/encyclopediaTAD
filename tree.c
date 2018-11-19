#include <string.h>
#include <stdio.h>
#include "wiki.h"

struct WikiSt {
  Entry e;
  Wiki s1, s2;
};

Wiki createWiki()
{
  return NULL;
}

Wiki insert(Wiki w, Entry e)
{
  if (w) { // empty leaf
    if (w->e.id > e.id) { // finds element
      w->s1 = insert(w->s1, e);
    } else {
      w->s2 = insert(w->s2, e);
    }
  } else {
    w = malloc(sizeof(struct WikiSt)); // creates leaf
    w->e = e;
    w->s1 = NULL;
    w->s2 = NULL;
  }
  return w;
}

Wiki del(Wiki w, Id id)
{
  if (w) {
    if (w->e.id > id) {
      w->s1 = del(w->s1, id);
    } else if (w->e.id < id) {
      w->s2 = del(w->s2, id);
    } else {
      Wiki replace = w->s2;
        // Case where s2 doesn't exist
      if (!replace) {
        replace = w->s1;
        w->s1 = NULL;
        destroy(w);
        return replace;
      }
        // Case where s2 exists, but has no s1 child
      if (!replace->s1) {
        replace->s1 = w->s1;
        w->s1 = NULL;
        w->s2 = NULL;
        destroy(w);
        return replace;
      }
        // Other cases
      Wiki prev = replace;
      while (replace->s1) {
        prev = replace;
        replace = replace->s1;
      }
      prev->s1 = replace->s2;
      replace->s1 = w->s1;
      replace->s2 = w->s2;
      w->s1 = NULL;
      w->s2 = NULL;
      destroy(w);
      return replace;
    }
  }
  return w;
}

Entry search(Wiki w, Id id)
{
  if (w) {
    if (w->e.id > id) {
      return search(w->s1, id);
    } else if (w->e.id < id) {
      return search(w->s2, id);
    } else {
      return w->e;
    }
  } else {
    Entry e = {0};
    return e;
  }
}

Wiki insertSearchTxtWiki(Wiki w, Wiki ws, char* txt);

Wiki searchTxt(Wiki w, char* txt)
{
  Wiki ret = createWiki();
  return insertSearchTxtWiki(ret, w, txt);
}

Wiki insertSearchTxtWiki(Wiki w, Wiki ws, char* txt)
{
  // The "ws" (for WikiSearch) serves the purpose of the selected wiki that is scanned
  // Whereas "w" is the wiki that is progressively filled with the entries that match our search
  if (ws) {
    if (strstr(ws->e.content, txt)) {
      w = insert(w, copyEntry(ws->e));
    }
    w = insertSearchTxtWiki(w, ws->s1, txt);
    w = insertSearchTxtWiki(w, ws->s2, txt);
  }
  return w;
}

void destroy(Wiki w)
{
  if(w) {
    destroy(w->s1);
    destroy(w->s2);
    freeEntry(w->e);
    free(w);
  }
}


void printWiki(Wiki w)
{
  if (w) {
    printWiki(w->s1);
    printEntry(w->e); // infixe order
    printWiki(w->s2);
  }
}


void printWikiSearch(Wiki w, char * str)
{
  if (w) {
    printWikiSearch(w->s1, str);
    printEntrySearch(w->e, str); // infixe order
    printWikiSearch(w->s2, str);
  }
}


int depth(Wiki w)
{
  return w?max(depth(w->s1), depth(w->s2))+1:0;
}

int leafCount(Wiki w)
{
  return w?(w->s1||w->s2)?leafCount(w->s1)+leafCount(w->s2):1:0;
}

void stats(Wiki w)
{
  printf("depth: %d\nleaves: %d\n", depth(w), leafCount(w));
}
