#include <string.h>
#include "wiki.h"

struct WikiSt {
  Entry e;
  Wiki s1, s2;
};

// The function "createWiki" merely returns an empty Wiki, that is, a pointer whose adress is NULL.
Wiki createWiki()
{
  return NULL;
}

Wiki insert(Wiki w, Entry e)
{
  if (w) { // This part of the function works until an empty leaf has been found
    if (w->e.id > e.id) { // To ensure the validity of the binary search tree
      w->s1 = insert(w->s1, e);
    } else {
      w->s2 = insert(w->s2, e);
    }
  } else {
    w = malloc(sizeof(struct WikiSt)); // Once it has been found, it creates the leaf according to the e entry
    w->e = e;
    w->s1 = NULL;
    w->s2 = NULL;
  }
  return w;
}

Wiki del(Wiki w, Id id)
{
  if (w) {
    if (w->e.id > id) { // This part of the function works until it finds the node to be deleted
      w->s1 = del(w->s1, id);
    } else if (w->e.id < id) {
      w->s2 = del(w->s2, id);
    } else {
      // Then, it proceeds with the deletion of the node
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
      return w->e; // Returns the selected entry when it has been found
    }
  } else {
    Entry e = {0}; // Creates an empty entry on the spot if the id has not been found
    return e;
  }
}

Wiki insertSearchTxtWiki(Wiki w, Wiki ws, char* txt)
{
  // The "ws" (for WikiSearch) serves the purpose of the selected wiki that is scanned
  // Whereas "w" is the wiki that is progressively filled with the entries that match our search
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
  Wiki ret = createWiki(); // Creates an empty wiki which will contain all the entries that match our search
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
    printEntry(w->e); // Prints the tree is order
    printWiki(w->s2);
  }
}
