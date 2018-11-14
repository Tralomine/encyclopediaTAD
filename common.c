#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wiki.h"

void printEntry(Entry e) {
  printf("%lu: %s\n\t %s\n\n", e.id, e.title, e.content);
}

Wiki loadFile(char* file) {
  Wiki wiki = NULL;//createWiki();

  FILE *fp;
  fp = fopen (file,"r");
  if (fp!=NULL) {

    char title[8192] = {0};
    char content[131072] = {0};

    char c = 0;
    size_t i = 0;
    do {
      Entry e;
      fscanf(fp, "%lu", &(e.id));

      fgetc(fp);

      for (c = 0, i = 0; c != '|' && c != EOF; i++) {
        c = getc(fp);
        title[i] = c;
      }
      title[i-1] = '\0';  //replace '|' by '\0'
      for (c = 0, i = 0; c != '\n' && c != EOF; i++) {
        c = getc(fp);
        content[i] = c;
      }
      content[i-1] = '\0';  //replace '|' by '\0'

      e.title = calloc(strlen(title)+1, sizeof(char));
      e.content = calloc(strlen(content)+1, sizeof(char));
      strcpy(e.title, title);
      strcpy(e.content, content);

      wiki = insert(wiki, e);

    } while (c != EOF);

    fclose (fp);
  }
  return wiki;
}
