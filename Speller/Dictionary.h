#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "Node.h"

#define LENGTH 45
#define SIZE 27
#define MULTIPLIER 31

using namespace::std;

class Dictionary
{
private:
    // Количество слов в словаре
    int words;
    // Слово
    char word[LENGTH + 1];

    // Функция хеширования. Возвращает хеш строки
    // Взято - stackoverflow.com/questions/20462826/hash-function-for-strings-in-c
    unsigned int hash(char *word)
    {
        unsigned int hash = 0;

        for (int i = 0; word[i] != '\0'; i++)
            hash = MULTIPLIER * hash + tolower(word[i]);

        return hash % SIZE;
    }

public:
    Dictionary()
    {
        words = 0;
    }

    // Функция проверки. Возвращает true, если слово есть в словаре, иначе - false
    bool check(char *word)
    {
        // Указатель на первый узел
        Node *cursor = new Node();
        // Найти местоположение слова
        cursor = hashtable[hash(word)];

        while (cursor != NULL)
        {
            // Ищет слово в hashtable, сравнение строк без учёта регистра
            if (strcasecmp(cursor -> word, word) == 0)
                return true;

            cursor = cursor -> next;
        }

        return false;
    }

    // Функция загрузки. Загружает словарь в память, возвращает true, если успешно, иначе - false
    bool load(char  *dictionary)
    {
        // Открыть файл для чтения
        FILE *f = fopen(dictionary, "r");
        if(f == NULL)
        {
            cout << "Could not open " << dictionary << endl;
            return false;
        }

        // Читать каждую строку пока не конец файла
        while(fscanf(f, "%s", word) != EOF)
        {
            words++;

            Node *newNode = new Node();
            if(newNode == NULL)
            {
                unload();
                return false;
            }
            // Выделить память
            newNode -> word = (char *)malloc(strlen(word) + 1);
            // Установить значение для узла
            strcpy(newNode -> word, word);
            // Хешировать значение узла
            int index = hash(newNode -> word);
            // Добавить новый узел
            newNode -> next = hashtable[index];
            // Указывать на новый узел
            hashtable[index] = newNode;
        }

        fclose(f);
        return true;
    }

    // Функция получения размера. Возвращает количество слов в загруженном словаре,
    // если словарь еще не загружен возвращает 0
    int size()
    {
        return words;
    }

    // Функция выгрузки из памяти. Выгружает словарь из памяти
    void unload()
    {
        // Освободить каждый элемент в hashtable
        for (int i = 0; i < SIZE; i++)
        {
            // Текущий узел
            Node *cursor = hashtable[i];
            // Освободить узел
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
