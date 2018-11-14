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
  }
  return w;
}

Wiki del(Wiki w, Id id)
{
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
    free(w->e.title);
    free(w->e.content);
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
