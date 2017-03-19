#include <iostream>
#include "Dictionary.h"

using namespace std;

char *getFile();
bool openForReading(FILE *f);
void igonoreBigWords(FILE *fp, char c, int index);
bool checkWord(int index, char *word, Dictionary *d);

int main()
{
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

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

    fclose(fp);
    dicts -> unload();

    cout << "\nWORDS MISSPELLED: " << misspellings << endl;
    cout << "WORDS IN DICTIONARY: " << dicts -> size() << endl;
    cout << "WORDS IN TEXT: " << words << endl;

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

bool openForReading(FILE *f)
{
    if (f == NULL)
    {
        cout << "Could not open a text. Usage: file.txt" << endl;
        return true;
    }

    return false;
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

bool checkWord(int index, char *word, Dictionary *d)
{
    // Добавить '\0' в конец строки
    word[index] = '\0';

    // Если текущего слова нет в словаре - вывести на экран
    if (!d -> check(word))
    {
        cout << endl << word;
        return true;
    }

    return false;
}


