#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
};

class LinkedList
{
private:
    Node *head;
    int size;
    int counter;

public:
    LinkedList()
    {
       head = NULL;
       size = 0;
       counter = 0;
    }

    void addElement(int element)
    {
        Node *newNode = new Node();
        Node *tmp = new Node();
        // Установить значение для узла
        newNode -> data = element;
        // Следующий узел указывает в конец списка
        newNode -> next = NULL;

        // Если список не пустой
        if (head != NULL)
        {
            tmp = head;
            // Дойти до конца списка
            while (tmp -> next != NULL)
                tmp = tmp -> next;

            // Вставить новый элемент в конец списка
            tmp -> next = newNode;
        }
        // Иначе, новый узел будет первым элемнтом в списке
        else
            head = newNode;

        size++;
    }

    void removeElement(int index)
    {
        Node *current = head;
        Node *previous = new Node();
        Node *tail = new Node();

        // Если список пуст
        if (current == NULL)
        {
            cout << "The list is empty! Nothing to delete" << endl;
            return;
        }
        // Если нужно удалить первый элемент списка
        if (index == 0)
        {
            head = head -> next;
            delete current;
            size--;
        }
        // Если нужно удалить последний элемент в списке
        else if (current -> next == NULL)
        {
            while (current -> next != NULL)
            {
                previous = current;
                current = current -> next;
            }

            tail = previous;
            previous -> next = NULL;
            delete current;
            size--;
        }
        // Иначе - нужно удалить элементы в середине
        else
        {
            for (int i = 1; i < index; i++)
            {
                previous = current;
                current = current -> next;
            }

            previous -> next = current -> next;
            delete current;
            size--;
        }
    }

    void insertElement(int element, int index)
    {
        Node *newNode = new Node();
        Node *current = head;
        Node *previous = new Node();

        newNode -> data = element;

        // Если элемнт нужно вставить в начало списка
        if (index == 0)
        {
            newNode -> next = head;
            head = newNode;
            size++;
        }
        // Если элемнт нужно вставить где-то в середину
        else
        {
           for (int i = 1; i < index; i++)
            {
                previous = current;
                current = current -> next;
            }

            previous -> next = newNode;
            newNode -> next = current;
            size++;
        }

    }

    void searchForElement(int element)
    {
        Node *node = head;
        bool wasFound = false;

        // Пока не конец списка - сравнивать элементы с искомым
        while (node)
        {
            if (node -> data == element)
            {
                wasFound = true;
                counter++;
            }

            node = node -> next;
        }

        if (wasFound)
            cout << "Element " << element << " is in the list! Appears " << counter << " times" << endl;
        else
            cout << "Element " << element << " is not in the list!" << endl;
    }

    int getSize()
    {
        return size;
    }

    void show()
    {
        Node *node = head;
        // Пока не конец списка - вывести каждый эелемент
        while (node)
        {
            cout << node -> data << " ";
            node = node -> next;
        }
    }
};

int main()
{
    LinkedList *linked = new LinkedList();

    // Добавить 10 элементов в список
    for (int i = 0; i < 10; i++)
        linked -> addElement(i);

    // Удалить девятый элемент
    linked -> removeElement(9);
    // Вставить элемент "7" на 5 место в списке
    linked -> insertElement(7, 5);
    // Вывести список на экран
    linked -> show();
    // Размер списка
    cout << "\nSize: " << linked -> getSize() << endl;
    // Проверить есть ли элемент "4" в списке
    linked -> searchForElement(4);

    delete linked;
    return 0;
}
