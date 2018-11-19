#include <stdlib.h>
#include <string.h>
#include "common.c"


int main() {

  // Wiki w = loadFile("wikipedia_500.dat");
  unsigned long start = getTime();
  Wiki w = loadFile("B46_wikipedia_500K_random.dat");
  printf("\nload time: %f\n", (getTime()-start)/1000000000.f);

  printf("===========================================\n");
  printf("printing entry 502098\n\n");
  start = getTime();
  printEntrySearch(search(w, 502098), "Second impact");
  printf("search time: %f\n", (getTime()-start)/1000000000.f);

  printf("===========================================\n");
  printf("searching for Neon Genesis Evangelion in all articles\n\n");
  start = getTime();
  Wiki searchResult = searchTxt(w, "Neon Genesis Evangelion");
  printf("search time: %f\n", (getTime()-start)/1000000000.f);
//  printWikiSearch(searchResult, "Neon Genesis Evangelion");

  printf("===========================================\n");
  printf("deleting element #502098 from search results\n");
  start = getTime();
  del(searchResult, 502098);
  printf("delete time: %f\n", (getTime()-start)/1000000000.f);

  printf("\nstats search results:\n");
  stats(searchResult);
  destroy(searchResult);

  printf("\nstats full wiki:\n");
  start = getTime();
  stats(w);
  printf("destroy time: %f\n", (getTime()-start)/1000000000.f);

  destroy(w);

  return 0;
}
