#ifndef NUMBERLIST_H
#define NUMBERLIST_H

class NumberList
{
private:
    struct ListNode
    {
        double value;
        struct ListNode *next;
    };
    ListNode *head;
public:
    NumberList() { head = nullptr; }
    ~NumberList();

    void appendNode(double);
    void insertNode(double);
    void deleteNode(double);
    void displayList() const;

    // --- Integrated mystery functions ---
    int  countNodes(ListNode *nodePtr) const;    // Function 1: recursive count
    void printReverse(ListNode *nodePtr) const;  // Function 2: recursive reverse-print
    void reverseList();                          // Function 3: iterative in-place reverse

    // Public wrappers so main() can call the recursive ones without touching head
    int  countNodes()   const { return countNodes(head); }
    void printReverse() const { printReverse(head); }
};
#endif
