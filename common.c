#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wiki.h"

void printEntry(Entry e) {
  printf("%lu: %s\n\n", e.id, e.content);
}


void printEntrySearch(Entry e, char* str)
{
  int length = strlen(str);
  char* found = e.content;
  char* endOfLast = found;
  while ((found = strstr(found, str))) {
    if (found >= endOfLast) {
      int length2 = found-endOfLast;
      if (length2)
        printf("%*.*s", length2, length2, endOfLast);
      printf("\x1b[31m%*.*s\x1b[0m", length, length, found); // sets the text corresponding to search in red
      found += length;
      endOfLast = found;
    }
  }
  printf("%s\n\n", endOfLast);
}


Wiki loadFile(char* file) {
  Wiki wiki = createWiki();

  FILE *fp;
  fp = fopen (file,"r");
  if (fp!=NULL) {

    char c = 0;
    long start;
    size_t size;
    int i = 0;
    do {
      if (!(i%10000)) {
         putc('.', stdout);
         fflush(stdout); // prints a dot each 10000 entries analyzed
      }

      Entry e;
      fscanf(fp, "%lu", &(e.id)); // scans the ID

      if (fgetc(fp) == EOF) break;  // eating the first '|'

      for (start = ftell(fp); c != '|' && c != EOF; c = (char)getc(fp)){} // gets to the end of title
      if (c != EOF) {
        size = (unsigned)(ftell(fp)-start); // calculates size of title
        e.title = calloc(size+1, sizeof(char)); // allocates memory for the title
        fseek(fp, -(size+1), SEEK_CUR); // rewinds to beginning of title
        fread(e.title, sizeof(char), size-1, fp); // reads and copies title into e.title
      }
      fgetc(fp);
      fgetc(fp);

      for (start = ftell(fp); c != '\n' && c != EOF; c = (char)getc(fp)){} // gets to the end of content
      if (c != EOF) {
        size = (unsigned)(ftell(fp)-start); // calculates size of content
        e.content = calloc(size+1, sizeof(char)); // allocates memory for the content
        fseek(fp, -size+1, SEEK_CUR); // rewinds to beginning of content, +1 to skip "| "
        fread(e.content, sizeof(char), size-1, fp); // reads and copies content into e.content
        e.content[strlen(e.title)] = ':';
      }

      wiki = insert(wiki, e);
      i++;
    } while (c != EOF);

    printf("loaded %d entries\n", i);

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

inline Entry copyEntry(Entry e) // cut & paste
{
  Entry r;
  r.id = e.id;
  r.title = malloc(sizeof(char)*(strlen(e.title)+1));
  strcpy(r.title, e.title);
  r.content = malloc(sizeof(char)*(strlen(e.content)+1));
  strcpy(r.content, e.content);
  return r;
}


inline int max(int a, int b)
{
  return (a>b)?a:b;
}
