#include <string.h>
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
  if (w) {
    if (w->e.id > e.id) {
      w->s1 = insert(w->s1, e);
    } else {
      w->s2 = insert(w->s2, e);
    }
  } else {
    w = malloc(sizeof(struct WikiSt));
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
      //deleting w
      //case where s2 doesn't exist
      Wiki replace = w->s2;
      if (!replace) {
        replace = w->s1;
        w->s1 = NULL;
        destroy(w);
        return replace;
      }
      //case where s2 as no s1 child
      if (!replace->s1) {
        replace->s1 = w->s1;
        w->s1 = NULL;
        w->s2 = NULL;
        destroy(w);
        return replace;
      }
      //other cases
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

Wiki insertSearchTxtWiki(Wiki w, Wiki ws, char* txt)
{
  if (ws) {
    if (strstr(ws->e.content, txt)) {
      w = insert(w, ws->e);
    }
    w = insertSearchTxtWiki(w, ws->s1, txt);
    w = insertSearchTxtWiki(w, ws->s2, txt);
  }
  return w;
}

Wiki searchTxt(Wiki w, char* txt)
{
  Wiki ret = createWiki();
  return insertSearchTxtWiki(ret, w, txt);
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
    printEntry(w->e);
    printWiki(w->s2);
  }
}
