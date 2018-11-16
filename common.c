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
    long start;
    long i = 0;
    do {
      Entry e;
      fscanf(fp, "%lu", &(e.id));

      fgetc(fp);  //eating the first '|'

      for (i = ftell(fp), start = i; c != '|' && c != EOF; i++, c = getc(fp)){}
      e.title = calloc(i-start, sizeof(char));
      fseek(fp, start, SEEK_SET);
      fread(e.title, sizeof(char), i-start-1, fp);
      fgetc(fp); //eating the '|'
      for (i = ftell(fp), start = i; c != '\n' && c != EOF; i++, c = getc(fp)){}
      e.content = calloc(i-start, sizeof(char));
      fseek(fp, start, SEEK_SET);
      fread(e.content, sizeof(char), i-start, fp);

      wiki = insert(wiki, e);

    } while (c != EOF);

    fclose (fp);
  }
  return wiki;
}


void freeEntry(Entry e)
{
  free(e.content);
  free(e.title);
  memset(&e, 0, sizeof(Entry));
}


Entry copyEntry(Entry e)
{
  Entry r;
  r.id = e.id;
  r.title = malloc(sizeof(char)*(strlen(e.title)+1));
  strcpy(r.title, e.title);
  r.content = malloc(sizeof(char)*(strlen(e.content)+1));
  strcpy(r.content, e.content);
  return r;
}
