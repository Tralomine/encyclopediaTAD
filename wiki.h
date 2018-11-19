#pragma once

#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

typedef size_t Id;

typedef struct EntrySt {
  Id id;
  char *title;
  char *content;
} Entry;

struct WikiSt;
typedef struct WikiSt* Wiki;

/*
 * @post-condition: The wiki exists. (It is considered implicit that the wiki is valid.)
 *
 * Returns an empty Wiki, that is, a pointer whose address is NULL.
 *
 * @return: the Wiki
 */
Wiki createWiki(void);

/*
 * @post-condition: The entry has been registered in the wiki.
 * @invariant: The wiki exists.
 *
 * Creates a new link, fills this new link with the entry's values, then links it to the rest of the chain.
 *
 * @param w: Wiki - The wiki which the program is working on
 * @param e: Entry - The entry which the program will add to the wiki
 * @return: the Wiki including the new entry
 */
Wiki insert(Wiki w, Entry e);

/*
 * @post-condition: The entry with the selected ID has been deleted from the wiki.
 * @invariant: The wiki exists.
 *
 * Scans the list in search of the entry with the selected ID, then proceeds to delete both its title and content.
 *
 * @param w: Wiki - The wiki which the program is working on
 * @param id: Id - The ID of the entry to delete
 * @return: the Wiki whose selected entry has been deleted from
 */
Wiki del(Wiki w, Id id);

/*
 * @invariant: The wiki exists.
 *
 * Scans the list in search of the entry with the selected ID, then returns it.
 * If the wiki is empty or does not have the entry with the selected ID, returns an empty entry created on the spot.
 *
 * @param w: Wiki - The wiki which the program is working on
 * @param id: Id - The ID of the entry to search
 * @return: the entry included in the wiki and corresponding to the ID in parameter
 */
Entry search(Wiki w, Id id);

/*
 * @post-condition: The wiki "results" exists (but can be empty).
 * @invariant: The wiki exists.
 *
 * Creates an empty wiki "results", then scans the entire wiki in search of entries that match the search.
 * If there is a match, the concerned entry is automatically added to "results".
 *
 * @param w: Wiki - The which which the program is working on
 * @param txt: char* - The string of text which the program searches in the wiki
 * @return: A new wiki including all the entries corresponding to the search query
 */
Wiki searchTxt(Wiki w, char* txt);

/*
 * @pre-condition: The wiki exists.
 *
 * Frees the memory allocated for every entry in the wiki.
 *
 * @param w: Wiki - The wiki to be destroyed
 */
void destroy(Wiki w);

/*
 * @invariant: The wiki exists.
 *
 * Prints every entry in the selected Wiki.
 *
 * @param w: Wiki - The wiki to be printed
 */
void printWiki(Wiki w);

//utility functions

/*
 * @invariant: The wiki exists.
 *
 * Prints the ID, the title and the content of the selected entry.
 *
 * @param e: Entry - The entry to be printed
 */
void printEntry(Entry e);

/*
 * @post-condition: One specific entry in the wiki has been deleted.
 * @invariant: The wiki exists.
 *
 * Sets every value in the selected entry to 0.
 *
 * @param e: Entry - The entry to be deleted
 */
void freeEntry(Entry e);

/*
 * @post-condition: The file has been loaded and can be used in the main.
 *
 * Loads the file with which the program will work.
 *
 * @param file: char* - The name of the file to load.
 * @return: the loaded Wiki
 */
Wiki loadFile(char* file);

/*
 * @invariant: The wiki exists.
 *
 * Copies the values of the selected entry into a new entry. Returns that entry.
 *
 * @param e: Entry - The entry to be copied
 * @return: A new entry with the exact same parameters as the initial entry.
 */
Entry copyEntry(Entry e);



/*
 * @invariant: The wiki exists.
 * @param w: Wiki - The wiki to be printed
 * @param str: Char* - The string to outline
 *
 * Prints every entries in the selected Wiki, with str outlined
 *
 */
void printWikiSearch(Wiki w, char* str);

/*
 * @invariant: The wiki exists.
 *
 * Prints the ID, the title and the content of the selected entry, with str outlined
 *
 * @param e: Entry - The entry to be printed
 * @param str: Char* - The string to outline
 */
void printEntrySearch(Entry e, char* str);


/*
 * @invariant: The wiki exists and is inchanged.
 *
 * Prints stats about the Wiki, depending on the implementation.
 *
 * @param w: Wiki - The wiki whose stats are printed
 */
void stats(Wiki w);


int max(int a, int b);
