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
 * Returns an empty Wiki, that is, a pointer whose address is NULL.
 *
 * @post-condition: The wiki exists. (It is considered implicit that the wiki is valid.)
 */
Wiki createWiki(void);

/*
 * @param w: Wiki - The wiki which the program is working on
 * @param e: Entry - The entry which the program will add to the wiki
 *
 * Creates a new link, fills this new link with the entry's values, then links it to the rest of the chain.
 *
 * @post-condition: The entry has been registered in the wiki.
 * @invariant: The wiki exists.
 */
Wiki insert(Wiki w, Entry e);

/*
 * @param w: Wiki - The wiki which the program is working on
 * @param id: Id - The ID of the entry to delete
 *
 * Scans the list in search of the entry with the selected ID, then proceeds to delete both its title and content.
 *
 * @post-condition: The entry with the selected ID has been deleted from the wiki.
 * @invariant: The wiki exists.
 */
Wiki del(Wiki w, Id id);

/*
 * @param w: Wiki - The wiki which the program is working on
 * @param id: Id - The ID of the entry to search
 *
 * Scans the list in search of the entry with the selected ID, then returns it.
 * If the wiki is empty or does not have the entry with the selected ID, returns an empty entry created on the spot.
 *
 * @invariant: The wiki exists.
 */
Entry search(Wiki w, Id id);

/*
 * @param w: Wiki - The which which the program is working on
 * @param txt: char* - The string of text which the program searches in the wiki
 *
 * Creates an empty wiki "results", then scans the entire wiki in search of entries that match the search.
 * If there is a match, the concerned entry is automatically added to "results".
 *
 * @post-condition: The wiki "results" exists (but can be empty).
 * @invariant: The wiki exists.
 */
Wiki searchTxt(Wiki w, char* txt);

/*
 * @param w: Wiki - The wiki to be destroyed
 *
 * Frees the memory allocated for every entry in the wiki.
 *
 * @pre-condition: The wiki exists.
 */
void destroy(Wiki w);

/*
 * @param w: Wiki - The wiki to be printed
 *
 * Prints every entries in the selected Wiki.
 *
 * @invariant: The wiki exists.
 */
void printWiki(Wiki w);

//utility functions

/*
 * @param e: Entry - The entry to be printed
 *
 * Prints the ID, the title and the content of the selected entry.
 *
 * @invariant: The wiki exists.
 */
void printEntry(Entry e);

/*
 * @param e: Entry - The entry to be deleted
 *
 * Sets every value in the selected entry to 0.
 *
 * @post-condition: One specific entry in the wiki has been deleted.
 * @invariant: The wiki exists.
 */
void freeEntry(Entry e);

/*
 * @param file: char* - The name of the file to load.
 *
 *
 *
 * @post-condition: The file has been loaded and can be used in the main.
 */
Wiki loadFile(char* file);

/*
 * @param e: Entry - The entry to be copied
 *
 * Copies the values of the selected entry into a new entry. Returns that entry.
 *
 * @invariant: The wiki exists.
 */
Entry copyEntry(Entry e);
