#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_WORD_LENGTH 46
#define HASHTABLE_SIZE 27
#define POLYNOM 31

using namespace::std;

class Node
{
public:
    char *word;
    Node *next;
};

Node *hashtable[HASHTABLE_SIZE];

class Dictionary
{
private:
    // Amount of words in dictionary
    int amountOfWords;
    // A word
    char word[MAX_WORD_LENGTH];

    // Hash function. Returns hash of the string
    // Taken - stackoverflow.com/questions/20462826/hash-function-for-strings-in-c
    unsigned int hash(char *word)
    {
        unsigned int hash = 0;

        for (int i = 0; word[i] != '\0'; i++)
            hash = POLYNOM * hash + tolower(word[i]);

        return hash % HASHTABLE_SIZE;
    }

public:
    Dictionary()
    {
        amountOfWords = 0;
    }

    // Returns true if word is in dictionary, else false.
    bool check(char *word)
    {
        // Pointer to the first node
        Node *cursor = new Node();
        cursor = hashtable[hash(word)];

        while (cursor != NULL)
        {
            // Looks for word in hashtable, comparing strings
            if (strcasecmp(cursor -> word, word) == 0)
                return true;

            cursor = cursor -> next;
        }

        return false;
    }

    // Loads dictionary into memory. Returns true if successful, else false
    bool load(char  *dictionary)
    {
        // Open file for reading
        FILE *f = fopen(dictionary, "r");
        if(f == NULL)
        {
            cout << "Could not open " << dictionary << endl;
            return false;
        }

        // Read every string while not the end of a file
        while(fscanf(f, "%s", word) != EOF)
        {
            amountOfWords++;

            Node *newNode = new Node();
            if(newNode == NULL)
            {
                unload();
                return false;
            }
            // Allocate memory
            newNode -> word = (char *)malloc(strlen(word) + 1);
            // Set value for node 
            strcpy(newNode -> word, word);
            // Hash node's value
            int index = hash(newNode -> word);
            // Add new node
            newNode -> next = hashtable[index];
            // Point to new node
            hashtable[index] = newNode;
        }

        fclose(f);
        return true;
    }

    // Returns number of words in dictionary if loaded, else 0 if not yet loaded
    int size()
    {
        return amountOfWords;
    }

    // Unload dictionary from memory. Returns true if successful, else false
    void unload()
    {
        // Free every element in hashtable
        for (int i = 0; i < HASHTABLE_SIZE; i++)
        {
            // Current node
            Node *cursor = hashtable[i];
            // Free node
            while (cursor != NULL)
            {
                Node *tmp = cursor;
                cursor = cursor -> next;
                free(tmp);
            }
        }
    }
};

#endif // DICTIONARY_H_INCLUDED
