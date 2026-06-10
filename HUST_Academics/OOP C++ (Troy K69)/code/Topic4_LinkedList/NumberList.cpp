#include "NumberList.h"
#include <iostream>
using namespace std;

void NumberList::appendNode(double num)
{
    ListNode *newNode = new ListNode;
    newNode->value = num;
    newNode->next  = nullptr;
    if (!head) head = newNode;
    else {
        ListNode *nodePtr = head;
        while (nodePtr->next) nodePtr = nodePtr->next;
        nodePtr->next = newNode;
    }
}

void NumberList::insertNode(double num)
{
    ListNode *newNode = new ListNode;
    newNode->value = num;
    if (!head) { head = newNode; newNode->next = nullptr; }
    else {
        ListNode *nodePtr = head;
        ListNode *previousNode = nullptr;
        while (nodePtr != nullptr && nodePtr->value < num) {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        if (previousNode == nullptr) { head = newNode; newNode->next = nodePtr; }
        else { previousNode->next = newNode; newNode->next = nodePtr; }
    }
}

void NumberList::deleteNode(double num)
{
    if (!head) return;
    ListNode *nodePtr, *previousNode;
    if (head->value == num) {
        nodePtr = head->next;
        delete head;
        head = nodePtr;
    } else {
        nodePtr = head;
        while (nodePtr != nullptr && nodePtr->value != num) {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        if (nodePtr != nullptr) {
            previousNode->next = nodePtr->next;
            delete nodePtr;
        }
    }
}

void NumberList::displayList() const
{
    ListNode *nodePtr = head;
    while (nodePtr) {
        cout << nodePtr->value << " ";
        nodePtr = nodePtr->next;
    }
    cout << endl;
}

NumberList::~NumberList()
{
    ListNode *nodePtr = head, *nextNode;
    while (nodePtr != nullptr) {
        nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

// ===== Integrated mystery functions =====
int NumberList::countNodes(ListNode *nodePtr) const
{
    if (nodePtr != nullptr) return 1 + countNodes(nodePtr->next);
    else                    return 0;
}

void NumberList::printReverse(ListNode *nodePtr) const
{
    if (nodePtr != nullptr) {
        printReverse(nodePtr->next);
        cout << nodePtr->value << " ";
    }
}

void NumberList::reverseList()
{
    ListNode *curr = head, *prev = nullptr, *next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}
