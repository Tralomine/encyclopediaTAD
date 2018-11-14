

#include <stdlib.h>
#include "wiki.h"

Wiki loadFile(char* file) {
  Wiki wiki = createWiki();
  
  Entry e;
  e.id = 0;
  wiki = insert(wiki, e);

  return wiki;
}



int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
