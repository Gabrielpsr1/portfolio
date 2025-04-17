// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 190801;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;

    char buffer[LENGTH + 1];

    unsigned int hashk;

    // read strings and create a node
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        {
            if (n == NULL)
                return false;
        }

        strcpy(n->word, buffer);
        n->next = NULL;
        hashk = hash(n->word);

        // if table doenst have a value yet
        if (table[hashk] == NULL)
        {
            table[hashk] = n;
        }
        // if table have a value
        else
        {
            n->next = table[hashk];
            table[hashk] = n;
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
