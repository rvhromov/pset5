#include <iostream>
#include <cstring>

using namespace std;

#define ARRAY_SIZE_MULTIPLIER 2

class ArrayList
{
private:
    int sizeOfArray;
    int amountOfElements;
    int *arrayList;

    void makeBiggerArray()
    {
        // Temporary storage array
        int *tmpArray = new int[sizeOfArray];
        // Copy all elements from main array to the temporary
        for (int i = 0; i < sizeOfArray; i++)
            tmpArray[i] = arrayList[i];
        // Increase size by 2 times
        sizeOfArray *= ARRAY_SIZE_MULTIPLIER;
        // Increase size of the main array by 2 times
        arrayList = new int[sizeOfArray];
        // Copy all elements back to the main array
        for (int i = 0; i < sizeOfArray; i++)
            arrayList[i] = tmpArray[i];
        // Free up the memory
        delete tmpArray;
    }

public:
    ArrayList()
    {
        sizeOfArray = 10;
        amountOfElements = 0;
        arrayList = new int[sizeOfArray];
    }

    ~ArrayList()
    {
        delete arrayList;
    }

    void add(int element)
    {
        // If amount of elements bigger than size of array
        if (amountOfElements >= sizeOfArray)
            makeBiggerArray();
        // Add element to the array
        arrayList[amountOfElements] = element;
        amountOfElements++;
    }

    void remove(int indexOfElement)
    {
        // Move all elements, starting with one which needs to be deleted on 1 position left
        for (int i = indexOfElement; i < amountOfElements; i++)
            arrayList[i] = arrayList[i + 1];

        sizeOfArray--;
        amountOfElements--;
    }

    void set(int element, int indexOfElement)
    {
        // If amount of elements bigger than size of array
        if (amountOfElements >= sizeOfArray)
            makeBiggerArray();

        // Move all elements on the 1 right to the index on which you want to insert the element
        for (int i = amountOfElements; i > indexOfElement; i--)
            arrayList[i] = arrayList[i - 1];

        arrayList[indexOfElement] = element;

        sizeOfArray++;
        amountOfElements++;
    }

    void trimToSize(int trim)
    {
        // Temporary storage array
        int *tmpArray = new int[trim];
        amountOfElements = trim;
        sizeOfArray = trim;

        // Copy all elements from main array to the temporary
        for (int i = 0; i <= trim; i++)
            tmpArray[i] = arrayList[i];

        // New size of the main array 
        int *arrayList = new int[trim];
        // Copy all elements back to the main array
        for (int i = 0; i <= trim; i++)
            arrayList[i] = tmpArray[i];
        // Free up the memory
        delete tmpArray;
    }

    void search(int element)
    {
        bool wasFound = false;
        int counter = 0;
        // Pass through the whole list and compare elements
        for (int i = 0; i < amountOfElements; i++)
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

    int size()
    {
        return amountOfElements;
    }

    void show()
    {
        for (int i = 0; i < amountOfElements; i++)
            cout << arrayList[i] << " ";
    }
};

int main()
{
    ArrayList *newList = new ArrayList();

    // Add elements to the list
    for (int i = 0; i < 14; i++)
        newList -> add(i);

    // Remove eighth element
    newList -> remove(7);
    // Insert element "89" on the third place in the list
    newList -> set(89, 2);
    // Trim list to 11 elements
    newList -> trimToSize(11);
    // Display list
    newList -> show();
    // Size of the list
    cout << "\nSize: " << newList -> size() << endl;
    // Search for element "10" in the list
    newList -> search(10);

    delete newList;
    return 0;
}
