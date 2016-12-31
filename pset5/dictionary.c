/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

node* root;
unsigned int word = 0;

/**
 * Returns true if word is in dictionary else false.
 */
 
node* createnode()
{
    node* trinode = NULL;
    trinode = calloc(1,sizeof(node));
    if (trinode)
    {
        trinode->is_word = false;
        
        for (int i = 0; i < 27; i++)
        {
            trinode->nodes[i] = NULL;
        }
        
        
    }
    return trinode;
}
bool check(const char* word)
{
    // TODO
    node* ptr = root;
    char c;
    int index;
    
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        c = tolower(word[i]);
        index = (c - 'a');
        if (c == '\'')
        {
            index = 26;
        }
        if (ptr->nodes[index]==NULL)
        {
            return false;
        }
        ptr = ptr->nodes[index];
    }
    
    return (ptr != NULL && ptr->is_word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    FILE* wd =fopen(dictionary, "r");
    root = createnode();
    node* ptr = root;
    if(!ptr)
    {
        return false;
    }
    
    int index;
    
    for (char c = fgetc(wd); c != EOF; c = fgetc(wd))
    {
        index = ((int)c - (int)'a');
        if (c == '\'')
        {
            index = 26;
        }
        if (c == '\n')
        {
            ptr->is_word = true;
            word++;
            ptr = root;
        }
        else
        {
            if (!ptr->nodes[index])
            {
                ptr->nodes[index] = createnode();
            }
            ptr = ptr->nodes[index];
        }
    }
    fclose(wd);
    return true;

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return word;
}
void delet_e(node* poi)
{
    node* ptr = poi;
    for (int i = 0; i < 27; i++)
    {
        if(ptr->nodes[i])
        {
            delet_e(ptr->nodes[i]);
        }
    }
    free(ptr);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    delet_e(root);
    return true;
}
