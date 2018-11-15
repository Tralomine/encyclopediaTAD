#include <stdlib.h>
#include <string.h>
#include "common.c"


int main(int argc, char const *argv[]) {

  Wiki w = loadFile("wikipedia_500.dat");
  printEntry(search(w, 4315895));

  Wiki searchResult = searchTxt(w, "lépidoptère");
  printWiki(searchResult);

  return 0;
}
