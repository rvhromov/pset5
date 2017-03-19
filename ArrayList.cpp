#include <iostream>
#include <cstring>

using namespace std;

#define MULTIPLIER 2

class ArrayList
{
private:
    int size;
    int index;
    int counter;
    bool wasFound;
    int *arrayList;

    void makeBiggerArray()
    {
        // Временный массив для хранения
        int *tmp = new int[size];
        // Копировать все элементы основного массива во временный
        for (int i = 0; i < size; i++)
            tmp[i] = arrayList[i];
        // Увеличить размер в 2 раза
        size *= MULTIPLIER;
        // Увеличить размер основного массива в 2 раза
        arrayList = new int[size];
        // Копировать все элементы обратно в основной массив
        for (int i = 0; i < size; i++)
            arrayList[i] = tmp[i];
        // Освободить память
        delete tmp;
    }

public:
    ArrayList()
    {
        size = 10;
        index = 0;
        counter = 0;
        wasFound = false;
        arrayList = new int[size];
    }

    void addElement(int element)
    {
        // Если элементов больше чем массив может принять
        if (index >= size)
            makeBiggerArray();
        // Добавить элемент в массив
        arrayList[index] = element;
        index++;
    }

    void removeElement(int indexOfElement)
    {
        // Сдвинуть все эелементы, начиная с того который нужно удалить, на 1 влево
        for (int i = indexOfElement; i < index; i++)
            arrayList[i] = arrayList[i + 1];

        size--;
        index--;
    }

    void insertElement(int element, int indexOfElement)
    {
        // Если элементов больше чем массив может принять
        if (index >= size)
            makeBiggerArray();

        // Сдвинуть все элементы на 1 вправо до индекса на который нужно вставить элемент
        for (int i = index; i > indexOfElement; i--)
            arrayList[i] = arrayList[i - 1];

        arrayList[indexOfElement] = element;

        size++;
        index++;
    }

    void *trimToSize(int trim)
    {
        // Временный массив для хранения
        int *tmp = new int[trim];
        index = trim;
        size = trim;

        // Копировать все элементы основного массива во временный
        for (int i = 0; i <= trim; i++)
            tmp[i] = arrayList[i];

        // Новый размер основного массива
        int *arrayList = new int[trim];
        // Копировать все элементы обратно в основной массив
        for (int i = 0; i <= trim; i++)
            arrayList[i] = tmp[i];
        // Освободить память
        delete tmp;
    }

    void searchForElement(int element)
    {
        // Пройти по всему списку и сравнить каждый элемент с искомым
        for (int i = 0; i < index; i++)
        {
            if (arrayList[i] == element)
            {
                wasFound = true;
                counter++;
            }
        }

        if (wasFound)
            cout << "Element " << element << " is in the list! " << "Appears " << counter << " times" << endl;
        else
            cout << "Element " << element << " is not in the list! ";

    }

    int getSize()
    {
        return index;
    }

    void show()
    {
        for (int i = 0; i < index; i++)
            cout << arrayList[i] << " ";
    }
};

int main()
{
    ArrayList *newList = new ArrayList();

    // Добавить эелементы в список
    for (int i = 0; i < 14; i++)
        newList -> addElement(i);

    // Удалить 8 элемент
    newList -> removeElement(7);
    // вставить элемент "89" на 3 место в списке
    newList -> insertElement(89, 2);
    // Обрезать список до 11 элементов
    newList -> trimToSize(11);
    // Вывести список на экран
    newList -> show();
    // Размер списка
    cout << "\nSize: " << newList -> getSize() << endl;
    // Проверить, есть ли элемент "10" в списке
    newList -> searchForElement(10);

    delete newList;
    return 0;
}
