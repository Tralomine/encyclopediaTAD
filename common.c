#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wiki.h"

void printEntry(Entry e) {
  printf("%lu: %s\n\t %s\n\n",
                              e.id,
                              e.title,
                              e.content+(e.id?strlen(e.title)+2:0)
                              //removing the title that starts the article
                              );
}

Wiki loadFile(char* file) {
  Wiki wiki = createWiki();

  FILE *fp;
  fp = fopen (file,"r");
  if (fp!=NULL) {

    char c = 0;
    long start, size;
    int i = 0;
    do {
      if (!(i%10000)) {
         putc('.', stdout);
         fflush(stdout);
      }
      i++;
      Entry e;
      fscanf(fp, "%lu", &(e.id));

      if (fgetc(fp) == EOF) break;  //eating the first '|'

      for (start = ftell(fp); c != '|' && c != EOF; c = getc(fp)){}
      if (c != EOF) {
        size = ftell(fp)-start;
        e.title = calloc(size+1, sizeof(char));
        fseek(fp, start, SEEK_SET);
        fread(e.title, sizeof(char), size-1, fp);
      }

      for (start = ftell(fp); c != '\n' && c != EOF; c = getc(fp)){}
      if (c != EOF) {
        size = ftell(fp)-start;
        e.content = calloc(size+1, sizeof(char));
        fseek(fp, start, SEEK_SET);
        fread(e.content, sizeof(char), size-1, fp);
      }

      wiki = insert(wiki, e);

    } while (c != EOF);

    printf("loaded %d entries", i);

    fclose (fp);
  }
  return wiki;
}

void freeEntry(Entry e)
{
  if (e.id) {
    free(e.content);
    free(e.title);
    memset(&e, 0, sizeof(Entry));
  }
}

inline Entry copyEntry(Entry e)
{
  Entry r;
  r.id = e.id;
  r.title = malloc(sizeof(char)*(strlen(e.title)+1));
  strcpy(r.title, e.title);
  r.content = malloc(sizeof(char)*(strlen(e.content)+1));
  strcpy(r.content, e.content);
  return r;
}
