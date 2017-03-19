#include <iostream>

using namespace std;

#define SIZE 128

class Node
{
public:
    int key;
	int value;
	Node *next;

    Node(int key, int value)
    {
        this -> key = key;
	    this -> value = value;
	    this -> next = NULL;
    }
};

class HashMap
{
private:
    Node **hashTable;
    Node **tmpTable;
    int sizeOfMap;

public:
    HashMap()
    {
        sizeOfMap = 0;
        hashTable = new Node *[SIZE];

        // Инициализация хешмапа NULL значениями
        for (int i = 0; i < SIZE; i++)
            hashTable[i] = NULL;
    }
    // Простая хеш-функция
    int hashFunc(int key)
    {
        return key % SIZE;
    }

    // Добавление элемента в хешмап
    void setElement(int key, int value)
    {
        // Получить хеш
        int hash = hashFunc(key);
        Node *prev = NULL;
        Node *node = hashTable[hash];

        // Добавить новый ключ в хешмап
        while (node != NULL)
        {
            prev = node;
            node = node -> next;
        }
        // Если таблица пустая
        if (node == NULL)
        {
            // Новый узел
            node = new Node(key, value);
            // В начало
            if (prev == NULL)
                hashTable[hash] = node;
            // Следующий элемент
	        else
                prev -> next = node;
        }
        // Добавить значение
        else
        {
            node -> value = value;
        }

        sizeOfMap++;
    }

    //Удаление элемента с хешмапа
    void removeElement(int key)
    {
        // Получить хеш
        int hash = hashFunc(key);
        // Пока не конец хешмапа и пока не встретили искомый элемент - продолжаем искать
        while (hashTable[hash] != NULL && hashTable[hash] -> key != key)
            hash = hashFunc(hash + 1);
        // Если ничего не найдено
        if (hashTable[hash] == NULL)
            cout << "Nothing to delete!" << endl;
        // Иначе - удалить элемент
        else
        {
            delete hashTable[hash];
            sizeOfMap--;
        }
    }

    // Поиск элемента
    void searchForElement(int key)
    {
        bool wasFound = false;
        int hash = hashFunc(key);
        Node *node = hashTable[hash];

        // Пока не конец хешмапа
        while (node != NULL)
	    {
	        // Если элемент найден
            if (node -> key == key)
	        {
	            wasFound = true;
                cout << "Element " << node -> value << " was found!" << endl;
            }

            node = node -> next;
        }
        // Если элемент не найден
        if (!wasFound)
            cout << "Element wasn't found!" << endl;
    }

    // Размер хешмапа
    int getSize()
    {
        return sizeOfMap;
    }

    // Вывод на экран хешмапа
    void show()
    {
        int hash;

        for (int i = 0; i < SIZE; i++)
        {
            hash = hashFunc(i);
            Node *node = hashTable[hash];

            while (node)
            {
                cout << node -> value << " ";
                node = node -> next;
            }
        }
    }
};

int main()
{
    HashMap *newMap = new HashMap();

    // Добавить 10 пар "ключ-значение" в хешмап
    for (int i = 0, j = 0; i < 10; i++, j += 10)
        newMap -> setElement(i, j);

    // Добавить еще один элемент с ключем "5" в хешмап
    newMap -> setElement(5, 87);
    // Удалить 8 элемент
    newMap -> removeElement(7);
    // Вывести хешмап на экран
    newMap -> show();
    // Размер хешмапа
    cout << "\nSize: " << newMap -> getSize() << endl;
    // Поиск по ключу
    newMap -> searchForElement(5);

    delete newMap;
    return 0;
}
