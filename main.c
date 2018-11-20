#include <stdlib.h>
#include <string.h>
#include "wiki.h"

#include "common.c"

int main() {

  unsigned long start = getTime();
  // Wiki w = loadFile("wikipedia_500.dat");
  Wiki w = loadFile("B46_wikipedia_500K_random.dat");
  printf("\nload time: ");
  printTime((getTime()-start));

  printf(BOLD"\n===========================================\n"RF);
  printf("printing entry "CYAN"#502098"RF"\n");
  start = getTime();
  printEntrySearch(search(w, 502098), "Second impact");
  printf("search time: ");
  printTime((getTime()-start));

  printf(BOLD"\n===========================================\n"RF);
  char* searchStr = "Neon Genesis Evangelion";
  printf("searching for "ORANGE"%s"RF" in all articles\n\n", searchStr);
  start = getTime();
  Wiki searchResult = searchTxt(w, searchStr);
  printf("search time: ");
  printTime((getTime()-start));
  // printWikiSearch(searchResult, searchStr);

  printf(BOLD"\n===========================================\n"RF);
  printf("deleting element "CYAN"#502098"RF" from search results\n");
  start = getTime();
  searchResult = del(searchResult, 502098);
  printf("delete time: ");
  printTime((getTime()-start));

  printf(BOLD"\n===========================================\n"RF);
  // 11218729: 17th Vermont Infantry, first element inserted
  printf("printing element "CYAN"#11218729"RF"("GREEN"first inserted"RF") from wiki\n");
  printEntry(search(w, 11218729));
  printf("deleting element "CYAN"#11218729"RF"("GREEN"first inserted"RF") from wiki\n");
  w = del(w, 11218729);

  // 10619657: Didac Ortega, last element inserted
  printf("\nprinting element "CYAN"#10619657"RF"("GREEN"last inserted"RF") from wiki\n");
  printEntry(search(w, 10619657));
  printf("deleting element "CYAN"#10619657"RF"("GREEN"last inserted"RF") from wiki\n");
  w = del(w, 10619657);

  printf(BOLD"\n===========================================\n"RF);
  printf("deleting element "CYAN"#11342306"RF" from wiki\n");
  start = getTime();
  del(w, 11342306);
  printf("delete time: ");
  printTime((getTime()-start));

  printf(BOLD"\n===========================================\n"RF);
  printf("\nstats search results:\n");
  stats(searchResult);
  destroy(searchResult);

  printf("\nstats full wiki:\n");
  stats(w);
  start = getTime();
  destroy(w);
  printf("\ndestroy time: ");
  printTime((getTime()-start));

  printf("\n");

  return 0;
}
