// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

//Global variable, number of words in dictionary when loaded
int word_count_dict = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    int word_index = hash(word);

    //Go to the right linked list
    /*----Initialize cursor pointer----*/
    node* cursor;
    cursor = table[word_index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            //They match
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //TODO
    //Returns a positive (hence unsigned) interger between 0 and N-1 (i.e. 0-25)
    //ASCII: #97 - #122 (lowercase)

    //Method picked: the first letter dictates which bucket it is in e.g. C = bucket 3 = table[2]
    char first_letter = word[0];
    int ascii_first_letter = tolower(first_letter) - 97;
    return ascii_first_letter;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //TODO

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dict,"%s",word) != EOF)
    {
        node *node1 = malloc(sizeof(node));
        if (node1 == NULL)
        {
            //If no space for node, quit
            return false;
        }

        //If space available, create a new node
        strcpy(node1->word, word);
        node1->next = NULL;
        word_count_dict = word_count_dict + 1;

        //Obtain hash index
        int hash_index = hash(word);

        //Insert node into hashtable
            /*table[hash_index] is like which bucket it is in
            if that bucket is empty, table[hash_index] == NULL
            just drop that node as first node; else, insert the new node as a linked list */
        if (table[hash_index] == NULL)
        {
            table[hash_index] = node1;
        }
        else
        {
            //Perform the linking
            /*1) Set the pointer of node1 (the new node) to the existing node (table[hash_index])--*/
            node1->next = table[hash_index];
            /*2) Change the current table[hash_index] from previous word to this new word,
            completing the insertion--*/
            table[hash_index] = node1;
        }



    }

    fclose(dict);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count_dict;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < 26; i++)
    {
        node* cursor;
        node* temp;
        cursor = table[i];
        temp = table[i];

        //Move cursor 1 step forward, while temp stays behind
        //Then clear what temp is occupying

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }

    }

    return true;

}
