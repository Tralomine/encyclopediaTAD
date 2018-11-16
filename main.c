#include <stdlib.h>
#include <string.h>
#include "common.c"


int main(int argc, char const *argv[]) {

  Wiki w = loadFile("wikipedia_500.dat");
  // Wiki w = loadFile("B46_wikipedia_500K_random.dat");

  printf("===========================================\n");
  printf("printing entry 4315895\n\n");
  printEntry(search(w, 4315895));

  printf("===========================================\n");
  printf("searching for Kladno in all articles\n\n");
  Wiki searchResult = searchTxt(w, "Kladno");
  printWiki(searchResult);

  printf("===========================================\n");
  printf("deleting element 6390869\n\n");
  del(searchResult, 6390869);
  // printWiki(searchResult);

  destroy(w);
  destroy(searchResult);

  return 0;
}
