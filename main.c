#include <stdlib.h>
#include <string.h>
#include "common.c"


int main() {

  // Wiki w = loadFile("wikipedia_500.dat");
  Wiki w = loadFile("B46_wikipedia_500K_random.dat");

  printf("===========================================\n");
  printf("printing entry 502098\n\n");
  printEntry(search(w, 502098));

  printf("===========================================\n");
  printf("searching for Neon Genesis Evangelion in all articles\n\n");
  Wiki searchResult = searchTxt(w, "Neon Genesis Evangelion");
  printWiki(searchResult);

  printf("===========================================\n");
  printf("deleting element 502098 from search results\n\n");
  del(searchResult, 502098);

  destroy(searchResult);
  // printWikiSearch(searchResult, "Neon Genesis Evangelion");

  stats(w);

  destroy(w);

  return 0;
}
