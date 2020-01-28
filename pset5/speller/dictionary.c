// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

//Declaring the hash function
unsigned int hash_word(const char *word);
//Declaring the string copmpare function
bool compare(const char *word1, const char *word2);

void init(void);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Checks if word is null pointer
    if (word != NULL)
    {
        //assigns value to the hashKey
        int hashKey = hash_word(word);

        //Points the cursor to begining of the linked list
        node *cursor = hashArray[hashKey];
        //Checks if cursor is pointing to a word in dictionary
        if (cursor == NULL)
        {
            return false;
        }
        //loops through the linked list till reaches the last entry
        while (cursor->counter != 0)
        {
            //Compares the strings
            if (compare(cursor->word, word))
            {
                return true;

            }
            else
            {
                cursor = cursor->next;
            }
        }
        if (compare(cursor->word, word))
        {
            return true;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    init();
    FILE *file = fopen(dictionary, "r");
    //Checks if file points to null
    if (file != NULL)
    {
        //declaring container for the word
        char word[LENGTH + 1];

        // For each word in dictionary
        while (fscanf(file, "%s", word) != EOF)
        {
            //creating a new node for the linked list
            node *newWordNode = malloc(sizeof(node));

            //check if we have memory for the new word
            if (newWordNode == NULL)
            {
                fclose(file);
                free(newWordNode);
                unload();
                return false;
            }

            //storing the word in the node->word variable
            strcpy(newWordNode->word, word);

            //hash value to hashKey
            int hashKey = hash_word(word);

            node *cursor = hashArray[hashKey];
            //Checks if the noe is empty

            if (cursor->counter != 0)
            {
                newWordNode->next = hashArray[hashKey];
                newWordNode->counter = hashArray[hashKey]->counter + 1;
                hashArray[hashKey] = newWordNode;
                wordCount++;
            }
            else
            {
                strcpy(hashArray[hashKey]->word, word);
                wordCount++;
                free(newWordNode);
            }

        }

        fclose(file);
        return true;
    }
    else
    {
        fclose(file);
        unload();
        return false;
    }
}

//Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < SZE; i++)
    {
        node *cursor = hashArray[i];
        while (cursor != NULL)
        {
            node *temp = cursor->next;
            hashArray[i] = temp;
            free(cursor);
            cursor = hashArray[i];
        }
        free(hashArray[i]);
    }

    return true;
}


// Hash function to return hash code
unsigned int hash_word(const char *word)
{
    int hash = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash += tolower(word[i]);
    }

    return hash % SZE;
}

//String copmpare function
bool compare(const char *word1, const char *word2)
{
    bool value = false;
    if (strlen(word1) == strlen(word2))
    {
        for (int i = 0; word2[i] != '\0'; i++)
        {
            if (tolower(word2[i]) != word1[i])
            {
                value = false;
                break;
            }
            else
            {
                value = true;
            }
        }
    }
    return value;
}

void init(void)
{
    for (int i = 0; i < SZE; i++)
    {
        hashArray[i] = malloc(sizeof(node));
        hashArray[i]->counter = 0;
    }
}
