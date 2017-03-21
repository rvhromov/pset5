#include <iostream>
#include "Dictionary.h"

using namespace std;

char *getFile();
bool openForReading(FILE *fp);
void spellCheck(FILE *fp, Dictionary *dicts);
void igonoreBigWords(FILE *fp, char c, int index);
bool checkWord(int index, char *word, Dictionary *dicts);
void showResults(int misspellings, int words, Dictionary *dicts);

int main()
{
    Dictionary *dicts = new Dictionary();
    // Загрузить словарь в память
    if(!dicts -> load("large"))
    {
        cout << "Could not load dictionary" << endl;
        return 1;
    }
     // Открыть файл с текстом
    FILE *fp = fopen(getFile(), "r");
    if (openForReading(fp))
    {
        dicts -> unload();
        return 1;
    }

    cout << "\nMISSPELLED WORDS:\n\n";

    spellCheck(fp, dicts);
    fclose(fp);
    dicts -> unload();

    delete dicts;
    return 0;
}

char *getFile()
{
    char *text = new char(LENGTH);
    cout << "Enter the name of a file you'd like to check: ";
    cin >> text;
    return text;
}

bool openForReading(FILE *fp)
{
    if (fp == NULL)
    {
        cout << "Could not open a text. Usage: file.txt" << endl;
        return true;
    }

    return false;
}

void spellCheck(FILE *fp, Dictionary *dicts)
{
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];
    // Проверить правописание кажого слова в тексте
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // Если буква или апостроф (апостроф не должен быть первым символом в строке)
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Добавить символ к слову
            word[index] = c;
            index++;
            // Игнорировать слова длиннее чем 45 символов
            igonoreBigWords(fp, c, index);
        }
        // Если цифра - игнорировать строку с цифрами
        else if (isdigit(c))
        {
            // Пройти оставшиеся символы
            while ((c = fgetc(fp)) != EOF && isalnum(c));
            index = 0;
        }
        // Если достигнут конец слова
        else if (index > 0)
        {
            // Количество слов в тексте
            words++;
            // Количество слов в тексте, которых нет в словаре
            if(checkWord(index, word, dicts))
                misspellings++;

            index = 0;
        }
    }
    // Вывести результаты на экран
    showResults(misspellings, words, dicts);
}

void igonoreBigWords(FILE *fp, char c, int index)
{
    if (index > LENGTH)
    {
        // Пройти оставшиеся символы в строке
        while ((c = fgetc(fp)) != EOF && isalpha(c));
        index = 0;
    }
}

bool checkWord(int index, char *word, Dictionary *dicts)
{
    // Добавить '\0' в конец строки
    word[index] = '\0';
    // Если текущего слова нет в словаре - вывести на экран
    if (!dicts -> check(word))
    {
        cout << endl << word;
        return true;
    }

    return false;
}

void showResults(int misspellings, int words, Dictionary *dicts)
{
    cout << "\nWORDS MISSPELLED: " << misspellings << endl;
    cout << "WORDS IN DICTIONARY: " << dicts -> size() << endl;
    cout << "WORDS IN TEXT: " << words << endl;
}