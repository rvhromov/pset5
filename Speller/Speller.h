#ifndef SPELLER_H_INCLUDED
#define SPELLER_H_INCLUDED
#include <ctime>
#include "Dictionary.h"

class SpellCheck
{
private:
    Dictionary *dicts;
    FILE *fp;

    int misspellings, amountOfWords;
    double startTime, endTime;

public:
    SpellCheck()
    {
        dicts = new Dictionary();
        misspellings = 0;
        amountOfWords = 0;

        checkLoading();
        openFileForReading();
        startTime = clock();
        spellCheck();
        showResults();
        endTime = clock();
        endUpAllWork();
        // Total runtime
        executionTime();
    }

    ~SpellCheck()
    {
        delete dicts;
    }

    void checkLoading()
    {
        // Load dictionary into memory
        if(!dicts -> load("large"))
            cout << "Could not load dictionary" << endl;
    }

    void openFileForReading()
    {
        char *text = new char(MAX_WORD_LENGTH);
        cout << "Enter the name of a file you'd like to check: ";
        cin >> text;

        fp = fopen(text, "r");
        if (fp == NULL)
        {
            cout << "Could not open a text. Usage: file.txt" << endl;
            dicts -> unload();
            return;
        }
    }

    void spellCheck()
    {
        int index = 0;
        char word[MAX_WORD_LENGTH];

        cout << "\nMISSPELLED WORDS:\n\n";
        // Spell-check of every word in text
        for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
        {
            // If it's letter or apostrophe (apostrophe shouldn't be the first character in string)
            if (isalpha(c) || (c == '\'' && index > 0))
            {
                // Add character to the word
                word[index] = c;
                index++;
                // Ignore words longer than 45 characters
                igonoreBigWords(c, index);
            }
            // If it's figure - ignore string with figures
            else if (isdigit(c))
            {
                // Pass through remaining characters in string
                while ((c = fgetc(fp)) != EOF && isalnum(c));
                index = 0;
            }
            // If reached the end of the word
            else if (index > 0)
            {
                amountOfWords++;
                // Amount of words in the text which are not in dictionary
                if(checkWord(index, word))
                    misspellings++;

                index = 0;
            }
        }
    }

    void igonoreBigWords(char c, int index)
    {
        if (index > MAX_WORD_LENGTH)
        {
            // Pass through remaining characters in string
            while ((c = fgetc(fp)) != EOF && isalpha(c));
            index = 0;
        }
    }

    bool checkWord(int index, char *word)
    {
        // Add '\0' at the end of string
        word[index] = '\0';
        // If current word is not in the dictionary - display it
        if (!dicts -> check(word))
        {
            cout << endl << word;
            return true;
        }

        return false;
    }

    void showResults()
    {
        cout << "\nWORDS MISSPELLED: " << misspellings << endl;
        cout << "WORDS IN DICTIONARY: " << dicts -> size() << endl;
        cout << "WORDS IN TEXT: " << amountOfWords << endl;
    }

    void endUpAllWork()
    {
        fclose(fp);
        dicts -> unload();
    }

    void executionTime()
    {
        cout << "Time: " << (endTime - startTime) / 1000 << " seconds" << endl;
    }
};


#endif // SPELLER_H_INCLUDED
