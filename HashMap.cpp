#include <iostream>
#include <cstring>

using namespace std;

#define ARRAY_SIZE 10000
#define POLYNOM 31

class HashMap
{
private:
    string hashTable[ARRAY_SIZE];
    int sizeOfHashTable;
    // Hash function
    unsigned int getHash(string word)
    {
        unsigned int hash = 0;

        for (int i = 0; word[i] != '\0'; i++)
            hash = POLYNOM * hash + word[i];

        return hash % ARRAY_SIZE;
    }

public:
    HashMap()
    {
        sizeOfHashTable = 0;
    }

    void add(string str)
    {
        // Add element
        hashTable[getHash(str)] = str;
        sizeOfHashTable++;
    }

    void remove(string str)
    {
        // If element which needs to be deleted is found
        if (hashTable[getHash(str)] == str)
        {
            // Move all elements, starting with one which needs to be deleted, on 1 position to the left
            for (int i = getHash(str); i < ARRAY_SIZE - 1; i++)
                hashTable[i] = hashTable[i + 1];

            cout << "\nElement " << str << " was removed!" << endl;
            sizeOfHashTable--;
        }
        else
        {
            cout << "\nNo such element in table. Nothing to delete!" << endl;
        }

    }

    void search(string str)
    {
        if (hashTable[getHash(str)] == str)
            cout << "\nElement " << str << " was found!" << endl;
        else
            cout << "\nElement " << str << " wasn't found!" << endl;
    }

    int size()
    {
        return sizeOfHashTable;
    }

    void show()
    {
        for (int i = 0; i < ARRAY_SIZE; i++)
            cout << hashTable[i] << " ";
    }
};

int main()
{
    HashMap *hm = new HashMap();

    // Add elements
    hm -> add("mama");
    hm -> add("amam");
    hm -> add("papa");
    hm -> add("son");
    hm -> add("daughter");
    hm -> add("family");
    // Remove element "son"
    hm -> remove("son");
    // Search for element "mama"
    hm -> search("mama");
    // Size
    cout << "\nSize: " << hm -> size() << endl;
    // Display
    hm -> show();

    delete hm;
    return 0;
}
