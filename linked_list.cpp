#include "linked_list.hpp"
#include <sstream>
#include <iostream>
LinkedList::~LinkedList()
{
    deleteAll();
}

LinkedList::LinkedList()
{
    this->head = nullptr;
    this->size = 0;
}
// copy constructor, deep copy to a current nil object
LinkedList::LinkedList(const LinkedList &from)
{
    deepCopy(from);
}
// Copy Assignment Operator, deep copy + remove existed
LinkedList &LinkedList::operator=(const LinkedList &from)
{
    deleteAll();
    deepCopy(from);
    return *this;
}

void LinkedList::deepCopy(const LinkedList &from)
{
    if (from.head == nullptr)
    {
        this->head = nullptr; // initialize the head
    }
    LinkedList::Node *p = from.head, *q = this->head;

    while (p != nullptr)
    {
        LinkedList::Node *n = new LinkedList::Node(p->val());
        q->setNext(*n);
        q = n;
        p = p->getNext();
    }
    this->size = from.size; // assign size
}

// Move constructor, shallow copy to new object
LinkedList::LinkedList(LinkedList &&from)
{
    shallowCopy(from);
}
// Move Operator, shallow copy
// remove old content of the list
// move content from other to this object
LinkedList &LinkedList::operator=(LinkedList &&from)
{
    deleteAll();
    shallowCopy(from);
    return *this;
}

void LinkedList::shallowCopy(const LinkedList &from)
{
    this->head = from.head;
    this->size = from.size;
}

LinkedList::Node::Node(int val) : value(val), next(nullptr) {}

LinkedList::Node::Node(int val, Node *n) : value(val), next(n) {}

int LinkedList::Node::val()
{
    return value;
}

LinkedList::Node *LinkedList::Node::getNext() const
{
    return this->next;
}

void LinkedList::Node::setNext(LinkedList::Node n)
{
    this->next = &n;
}

int LinkedList::length() const
{
    return this->size;
}

bool LinkedList::isEmpty() const
{
    return this->size == 0;
}

// recursive,without managing size
LinkedList::Node *LinkedList::remove(LinkedList::Node *head, int val)
{
    if (head == nullptr)
    { // list is empty
        return nullptr;
    }
    LinkedList::Node *p = head; // first node
    if (p->val() == val)
    {
        LinkedList::Node *tmp = p;
        head = p->getNext();
        return tmp;
    }
    else
    {
        return remove(p->getNext(), val);
    }
}

void LinkedList::deleteAll()
{
    LinkedList::Node *p = this->head, *q = p; // q is always one step behind p
    while (p != nullptr)
    {
        p = p->getNext();
        delete q;
        q = p;
    }
}

void LinkedList::insert(int val)
{
    LinkedList::Node *n = new LinkedList::Node(val);

    LinkedList::Node *p = head, *q = p;

    if (p != nullptr)
    {
        head = n;
        return;
    }

    // insert before p when  p.value > val.
    // p is one step after q
    while (p->val() < val)
    {
        q = p;
        p = p->getNext();
    }
    n->setNext(*p);

    if (q == head)
    {
        head = n;
    }
    else
    {
        q->setNext(*n);
    }
    size++;
    return;
}

LinkedList::Node *LinkedList::removeByVal(int val)
{
    LinkedList::Node *n = remove(head, val);
    if (n != nullptr)
    {
        size--;
    }
    return n;
}

LinkedList::Node *LinkedList::removeByIndex(int index)
{
    if (index >= size)
    {
        return nullptr;
    }
    LinkedList::Node *p = head, *prev;
    while (index-- >= 0)
    {
        prev = p;
        p = p->getNext();
    }

    LinkedList::Node *tmp = p;
    prev->setNext(*p->getNext());
    size--;
    return tmp;
}

int LinkedList::at(int val) const
{
    LinkedList::Node *p = head;
    int i = 0, tmp;
    while (p != nullptr && p->val() != val)
    {
        i++;
        p = p->getNext();
    }
    if (p == nullptr || p->val() != val)
    { // val not found in the list
        i = -1;
    }
    return i;
}

void LinkedList::print() const
{
    std::cout << toString();
}

std::string LinkedList::toString() const
{
    std::stringstream ss;
    LinkedList::Node *p = head->getNext();
    ss << "[";
    while (p != nullptr)
    {
        ss << p->val();
        if (p->getNext() != nullptr)
        {
            ss << " -> ";
        }
    }

    ss << "]";
    return ss.str();
}
