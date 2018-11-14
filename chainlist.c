#include "wiki.h"
#include <stdlib.h>
#include <string.h>

struct WikiSt {
  Entry entry;
  Wiki next;
};


Wiki createWiki() {
  return NULL;
}

Wiki insert(Wiki w, Entry  e) {
  Wiki newWiki;
  newWiki= malloc(sizeof(struct WikiSt));
  newWiki->entry = e;
  newWiki->next = w;
  return newWiki;
}

Wiki del(Wiki w, Id id){
  Wiki mem;
  Wiki prev;
  if (w->entry.id != id){
    prev = w;
    w = w->next;
  } else {
    w->entry.title = NULL;
    w->entry.content = NULL;
    prev->next = w->next;
    w->next = NULL;
  }
  return mem;
}

Entry search(Wiki w, Id id){
  if (w == NULL) {
    Entry e;
    e.id = 0;
    return e;
  }
  if (w->entry.id == id){
    return w->entry;
  } else {
    return search(w->next, id);
  }
}

Wiki searchTxt(Wiki w, char* txt){
  Wiki result = createWiki();
  while (w->next){
    if (strstr(w->entry.content, txt)){
      insert(result, w->entry);
    }
    w = w->next;
  }
  return result;
}

void destroy(Wiki w){
  while (w){
    Wiki temp = w->next;
    free(w);
    w = temp;
  }
}
