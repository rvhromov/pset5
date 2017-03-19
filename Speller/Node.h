#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#define SIZE 27

class Node
{
public:
    char *word;
    Node *next;
};

Node *hashtable[SIZE];

#endif // NODE_H_INCLUDED
