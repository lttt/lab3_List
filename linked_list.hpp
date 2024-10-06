#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <string>

// a linked list that is always in ascending order
class LinkedList
{

public:
    class Node
    {
    private:
        int value;
        Node *next;

    public:
        // constructor
        Node(int val);
        Node(int val, Node *n);
        int val();
        LinkedList::Node *getNext() const;
        void setNext(LinkedList::Node n);
        // LinkedList::Node* getPrev();
    };
    // constructor
    LinkedList();
    // destructor
    ~LinkedList();
    // copy constructor
    LinkedList(const LinkedList &from);
    // Copy Assignment Operator
    LinkedList &operator=(const LinkedList &l);
    // Move constructor
    LinkedList(LinkedList &&l);
    // Move Operator
    LinkedList &operator=(LinkedList &&l);
    // functions
    void insert(int val);
    LinkedList::Node *removeByVal(int val); // remove the first node has val as value
    LinkedList::Node *removeByIndex(int index);
    int at(int val) const; // return -1 when val not found in the list
    void print() const;
    std::string toString() const;
    int length() const;
    bool isEmpty() const;

private:
    Node *head;
    int size;
    Node *remove(Node *start, int val);
    void deleteAll();
    // deep copy all nodes.
    // overwriting current nodes
    // caller must be responsible for cleaning existing nodes
    void deepCopy(const LinkedList &from);
    // shallow copy copy all nodes .
    // overwriting current nodes
    // caller must be responsible for cleaning existing nodes
    void shallowCopy(const LinkedList &from);
};

#endif;