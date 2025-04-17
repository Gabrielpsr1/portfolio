// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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

int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // unsigned int key = hash(word);
    // node *n = malloc(sizeof(node));

    // // if its on the first element of the list
    // if(table[key] == NULL)
    // return false;

    // if (strcasecmp(table[key]->word, word) == 0)
    // {
    //     return true;
    // }
    // else if (table[key] == NULL)
    // {
    //     return false;
    // }
    // else
    // {
    //     n = table[key]->next;
    //     while (n != NULL)
    //     {
    //         if (strcasecmp(n->word, word) == 0)
    //             return true;

    //         else
    //             n = n->next;
    //     }
    // }
    // return false;
    unsigned int key = hash(word);
    node *cursor = table[key];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
    long long unsigned int key = 0;
    // TODO: Improve this hash function
    for (int i = 0; word[i] != '\0'; i++)
    {
        key = key * 53 + word[i];
    }
    return key % N;
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
    node *n = NULL;

    // read strings and create a node
    while (fscanf(file, "%s", buffer) != EOF)
    {
        n = malloc(sizeof(node));
        {
            if (n == NULL)
                return false;
        }

        // copy str
        // int len = strlen(buffer);
        for (int i = 0; i != '\0'; i++)
        {
            buffer[i] = toupper(buffer[i]);
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

        word_count++;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
