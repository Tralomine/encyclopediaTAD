#include "wiki.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // needed for strstr function in the "searchTxt" function

struct WikiSt {
  Entry entry;
  Wiki next;
};

// The function "createWiki" merely returns an empty Wiki, that is, a pointer whose adress is NULL.
Wiki createWiki()
{
  return NULL;
}

/* The function "insert" creates a new link NewWiki, allocates enough memory for a new Link,
   fills its entry with the wanted value e, then links the NewWiki's adress to the rest
   of the chain */
Wiki insert(Wiki w, Entry  e)
{
  Wiki newWiki;
  newWiki= malloc(sizeof(struct WikiSt));
  newWiki->entry = e;
  newWiki->next = w;
  return newWiki;
}


Wiki del(Wiki w, Id id)
{
  bool first = true; // used to know if the selected link is the first of the chainlist
  /* The function "del" first creates a new Wiki mem, that will be returned at the end once the
  wanted link will have been deleted.  */
  Wiki mem = w;
  Wiki prev; // used to link the rest of the chained list after the removal of the wanted link
  while (w) {
    if (w->entry.id != id) {
      prev = w; // prev is used to keep in memory the previous link while the link to delete has not been reached
      w = w->next;
      first = false; // if the instructions of this loop are used even once, first switches to false
    } else {
      w->entry.title = NULL; // once it has been reached, the function deletes both its title...
      w->entry.content = NULL; // ... and its content
      if (first == true) { // if the selected link is the first of the loop
        prev = w->next;
      } else {
        prev->next = w->next; // then it links the rest of the chain back together
      }
      w->next = NULL; // and empties the adress of the following link for
      destroy(w);
      break; // breaks the "while" loop if the function has achieved its purpose
    }
  }
  return mem; // mem, which took the value of the first link, is returned
}

Entry search(Wiki w, Id id)
{
  while (w->entry.id != id && w != NULL) {
    w = w->next; // the function keeps scanning the list as long as the selected link or an empty link has not been found
  }
  if (w == NULL) {
    Entry e; // if the wiki is empty, it returns an empty entry created on the spot
    e.id = 0;
    return e;
  }
  return w->entry;
}

Wiki searchTxt(Wiki w, char* txt)
{
  Wiki result = createWiki(); // creates an empty wiki to contain all the entries that match the search
  while (w) {
    if (strstr(w->entry.content, txt)) { // the function strstr returns an empty pointor if the txt is not contained in the content's entry
    // as the entry's content necessarily contains the title, we do not need to check the latter
      result = insert(result, w->entry); // inserts the entry in the results
    }
    w = w->next;
  }
  return result;
}

void destroy(Wiki w)
{
  while (w) {
    Wiki temp = w->next; // temp keeps in memory the next link to get to it once the selected link has been deleted
    freeEntry(w->entry);
    free(w);
    w = temp;
  }
}

void printWiki(Wiki w)
{
  while (w) {
    printEntry(w->entry); // the printEntry function is located in common.c
    w = w->next;
  }
}
