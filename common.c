#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "wiki.h"


void printEntry(Entry e) {
  int length = (int)strlen(e.title);
  printf(CYAN"%lu"RF"\n"ORANGE"%*.*s"RF"%s",
         e.id, length, length, e.content, &(e.content[length]));
}

void printEntrySearch(Entry e, char* str)
{
  if (!e.id) {
    printf("Empty entry.\n");
    return;
  }
  printf(""CYAN"%lu"RF"\n", e.id);
  int length = (int)strlen(str);
  char* found = e.content;
  char* endOfLast = found;
  while ((found = strstr(found, str))) {
    if (found >= endOfLast) {
      int length2 = (int)(found-endOfLast);
      if (length2) {
        printf("%*.*s", length2, length2, endOfLast);
      }
      printf(RED"%*.*s"RF, length, length, found); // sets the text corresponding to search in red
      found += length;
      endOfLast = found;
    }
  }
  printf("%s\n", endOfLast);
}

Wiki loadFile(char* file) {
  Wiki wiki = createWiki();

  printf("Loading");

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
        e.title = calloc(size+1, sizeof(char));
        fseek(fp, -(long)size-1, SEEK_CUR); // rewinds to beginning of title
        fread(e.title, sizeof(char), size-1, fp); // reads and copies title into e.title
      }
      fgetc(fp);
      fgetc(fp);

      for (start = ftell(fp); c != '\n' && c != EOF; c = (char)getc(fp)){} // gets to the end of content
      if (c != EOF) {
        size = (unsigned)(ftell(fp)-start); // calculates size of content
        e.content = calloc(size+1, sizeof(char));
        fseek(fp, -(long)size+1, SEEK_CUR); // rewinds to beginning of content, +1 to skip "| "
        fread(e.content, sizeof(char), size-1, fp); // reads and copies content into e.content
        e.content[strlen(e.title)] = ':';
      }

      wiki = insert(wiki, e);
      i++;
    } while (c != EOF);

    printf("\nloaded %d entries\n", i);

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

unsigned long getTime(void);
void printTime(unsigned long ns);

unsigned long getTime(void)
{
#ifndef __WIN32
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);
  return (unsigned long)(1000000000L * ts.tv_sec + ts.tv_nsec);
#else
  return 0;
#endif
}

void printTime(unsigned long ns)
{
  if (ns < 1000) {
    printf(LAVENDER"%lu"RF" ns", ns);
  } else if (ns < 1000000) {
    printf(LAVENDER"%f"RF" µs", ns/1000.0);
  } else if (ns < 1000000000) {
    printf(LAVENDER"%f"RF" ms", ns/1000000.0);
  } else {
    printf(LAVENDER"%f"RF" s", ns/1000000000.0);
  }
}
