#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "common.c"


int main(int argc, char const *argv[]) {
  Wiki w = loadFile("wikipedia_500.dat");
  printEntry(search(w, 4315895));
  Wiki searchResult = searchTxt(w, "Syrie");
  printWiki(searchResult);
  getch();
  return 0;
}
