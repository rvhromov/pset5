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
    int sizeOfList;

public:
    LinkedList()
    {
       head = NULL;
       sizeOfList = 0;
    }

    void add(int element)
    {
        Node *newNode = new Node();
        Node *tmp = new Node();
        // Set a value for node 
        newNode -> data = element;
        // Next node points to the end of the list
        newNode -> next = NULL;

        // If list isn't empty
        if (head != NULL)
        {
            tmp = head;
            // Reach the end of the list
            while (tmp -> next != NULL)
                tmp = tmp -> next;

            // Insert new element into the end of the list
            tmp -> next = newNode;
        }
        // Otherwise, new node is the first element in the list
        else
        {
            head = newNode;
        }

        sizeOfList++;
    }

    void remove(int index)
    {
        Node *current = head;
        Node *previous = new Node();

        // If list is empty
        if (current == NULL)
        {
            cout << "The list is empty! Nothing to delete" << endl;
            return;
        }
        // If need to remove the first element of the list
        if (index == 0)
        {
            head = head -> next;
            delete current;
            sizeOfList--;
        }
        // Otherwise - remove other elements
        else
        {
            for (int i = 1; i < index; i++)
            {
                previous = current;
                current = current -> next;
            }

            previous -> next = current -> next;
            delete current;
            sizeOfList--;
        }
    }

    void set(int element, int index)
    {
        Node *newNode = new Node();
        Node *current = head;
        Node *previous = new Node();

        newNode -> data = element;

        // If element needs to be inserted at the beginning of the list
        if (index == 0)
        {
            newNode -> next = head;
            head = newNode;
            sizeOfList++;
        }
        // Otherwise element needs to be inserted somewhere else
        else
        {
           for (int i = 1; i < index; i++)
            {
                previous = current;
                current = current -> next;
            }

            previous -> next = newNode;
            newNode -> next = current;
            sizeOfList++;
        }

    }

    void search(int element)
    {
        Node *node = head;
        int counter = 0;
        bool wasFound = false;

        // Until not the end of the list - compare elements
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

    int size()
    {
        return sizeOfList;
    }

    void show()
    {
        Node *node = head;
        // Until not the end of the list - display every element
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

    // Add 10 elements to the list
    for (int i = 0; i < 10; i++)
        linked -> add(i);

    // Remove ninth element
    linked -> remove(9);
    // Insert element "7" on the fifth place in the list
    linked -> set(7, 5);
    // Display the whole list
    linked -> show();
    // Size of the list
    cout << "\nSize: " << linked -> size() << endl;
    // Search for element "4" in the list
    linked -> search(4);

    delete linked;
    return 0;
}
