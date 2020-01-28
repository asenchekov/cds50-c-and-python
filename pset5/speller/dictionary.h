// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define SZE 300

typedef struct node
{
    char word[LENGTH + 1];
    int counter;
    struct node *next;
}
node;

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
node *hashArray[SZE];
int wordCount;

#endif // DICTIONARY_H
