CS256
|                                       | Chapter          | 17: Linked     | List       |      |
| ------------------------------------- | ---------------- | -------------- | ---------- | ---- |
|                                       | Hanoi University | of Science and | Technology |      |
| HanoiUniversityofScienceandTechnology |                  | CS256          |            | 1/25 |

| Slide contents | are mainly | based | on the following documents: |     |
| -------------- | ---------- | ----- | --------------------------- | --- |
Tony Gaddis, Starting out with C++, Eighth Edition, Pearson, 2015
| Tony | Gaddis, Power | Points | Slides: |     |
| ---- | ------------- | ------ | ------- | --- |
https://www.umsl.edu/~antognolij/gaddis.html
| HanoiUniversityofScienceandTechnology |     |     | CS256 | 2/25 |
| ------------------------------------- | --- | --- | ----- | ---- |

Linked List
Linked List: set of data structures (nodes) that contain references to
other data structures
Data structures (nodes) can be added to or removed from the linked list
during execution
HanoiUniversityofScienceandTechnology CS256 3/25

| Linked List, | Array, Vector |     |     |     |     |
| ------------ | ------------- | --- | --- | --- | --- |
Linked lists can grow and shrink as needed, unlike arrays, which have
| a fixed size                          |            |                |             |        |      |
| ------------------------------------- | ---------- | -------------- | ----------- | ------ | ---- |
| Linked lists                          | can insert | a node between | other nodes | easily |      |
| HanoiUniversityofScienceandTechnology |            | CS256          |             |        | 4/25 |

Node Organization
A node contains:
data: one or more data fields – may be organized as structure, object,
etc.
| a pointer that                        | can point | to another node |      |
| ------------------------------------- | --------- | --------------- | ---- |
| HanoiUniversityofScienceandTechnology |           | CS256           | 5/25 |

| Linked List                           | Organization  |                      |                   |      |
| ------------------------------------- | ------------- | -------------------- | ----------------- | ---- |
| Linked                                | list contains | 0 or more nodes      |                   |      |
| Has a list                            | head to       | point to first node  |                   |      |
| Last node                             | points to     | NULL                 |                   |      |
| Empty                                 | list:         |                      |                   |      |
| - If a list                           | currently     | contains 0 nodes, it | is the empty list |      |
| - In this                             | case the list | head points to NULL  |                   |      |
| HanoiUniversityofScienceandTechnology |               | CS256                |                   | 6/25 |

Declaring a Node
struct ListNode
{
| double value;   |        | // The value | in this     | node |
| --------------- | ------ | ------------ | ----------- | ---- |
| struct ListNode | *next; | // To point  | to the next | node |
};
| HanoiUniversityofScienceandTechnology |     | CS256 |     | 7/25 |
| ------------------------------------- | --- | ----- | --- | ---- |

| Defining                              | a Linked      | List             |                     |               |      |
| ------------------------------------- | ------------- | ---------------- | ------------------- | ------------- | ---- |
| Define                                | a pointer     | for the          | head of the list    |               |      |
|                                       | ListNode      | *head            | = NULL;             |               |      |
| Head                                  | pointer       | initialized      | to NULL to indicate | an empty list |      |
| NULL                                  | Pointer:      |                  |                     |               |      |
| -                                     | Should always | be tested        | for before using    | a pointer:    |      |
|                                       | ListNode      | *p;              |                     |               |      |
|                                       | while         | (p != NULL)      | ...                 |               |      |
| -                                     | Can also      | test the pointer | itself:             |               |      |
|                                       | while         | (p) ... //       | same meaning        | as above      |      |
| HanoiUniversityofScienceandTechnology |               |                  | CS256               |               | 8/25 |

Traverse a List
| HanoiUniversityofScienceandTechnology | CS256 | 9/25 |
| ------------------------------------- | ----- | ---- |

| Traverse |          | a List    |         |        |              |          |       |     |
| -------- | -------- | --------- | ------- | ------ | ------------ | -------- | ----- | --- |
| ListNode |          | *nodePtr; | //      | To     | move through | the      | list  |     |
| //       | Position |           | nodePtr | at the | head         | of the   | list. |     |
| nodePtr  |          | = head;   |         |        |              |          |       |     |
| //       | While    | nodePtr   | points  | to     | a node,      | traverse |       |     |
| //       | the      | list.     |         |        |              |          |       |     |
| while    |          | (nodePtr) |         |        |              |          |       |     |
{
|     | //      | Display | the value        | in    | this     | node. |     |     |
| --- | ------- | ------- | ---------------- | ----- | -------- | ----- | --- | --- |
|     | cout    | <<      | nodePtr->value   |       | << endl; |       |     |     |
|     | //      | Move    | to the next      | node. |          |       |     |     |
|     | nodePtr |         | = nodePtr->next; |       |          |       |     |     |
}
| HanoiUniversityofScienceandTechnology |     |     |     |     | CS256 |     |     | 10/25 |
| ------------------------------------- | --- | --- | --- | --- | ----- | --- | --- | ----- |

| Appending                             | a Node      |           |            |          |       |
| ------------------------------------- | ----------- | --------- | ---------- | -------- | ----- |
| Appending                             | a Node: Add | a node to | the end of | the list |       |
| HanoiUniversityofScienceandTechnology |             | CS256     |            |          | 11/25 |

| Appending      |          |            | a List    |          |           |          |         |      |     |     |
| -------------- | -------- | ---------- | --------- | -------- | --------- | -------- | ------- | ---- | --- | --- |
| ListNode       |          | *newNode;  |           | //       | To point  | to       | a new   | node |     |     |
| ListNode       |          | *nodePtr;  |           | //       | To move   | through  | the     | list |     |     |
| //             | Allocate |            | a new     | node     | and store | num      | there.  |      |     |     |
| newNode        |          | = new      | ListNode; |          |           |          |         |      |     |     |
| newNode->value |          |            | =         | num;     |           |          |         |      |     |     |
| newNode->next  |          |            | =         | nullptr; |           |          |         |      |     |     |
| //             | If       | there      | are       | no nodes | in        | the list |         |      |     |     |
| if             | (!head)  |            | // make   | newNode  | the       | first    | node.   |      |     |     |
|                | head     | =          | newNode;  |          |           |          |         |      |     |     |
| else           | //       | Otherwise, |           | insert   | newNode   |          | at end. |      |     |     |
{
|     | nodePtr       |                 | = head; | //               | Initialize |           | nodePtr  | to head | of list.    |       |
| --- | ------------- | --------------- | ------- | ---------------- | ---------- | --------- | -------- | ------- | ----------- | ----- |
|     | while         | (nodePtr->next) |         |                  | //         | Find      | the last | node    | in the      | list. |
|     |               | nodePtr         |         | = nodePtr->next; |            |           |          |         |             |       |
|     | nodePtr->next |                 |         | = newNode;       |            | // Insert | newNode  |         | as the last | node. |
}
| HanoiUniversityofScienceandTechnology |     |     |     |     |     | CS256 |     |     |     | 12/25 |
| ------------------------------------- | --- | --- | --- | --- | --- | ----- | --- | --- | --- | ----- |

Appending a Node
| HanoiUniversityofScienceandTechnology | CS256 | 13/25 |
| ------------------------------------- | ----- | ----- |

Appending a Node
| HanoiUniversityofScienceandTechnology | CS256 | 14/25 |
| ------------------------------------- | ----- | ----- |

Appending a Node
| HanoiUniversityofScienceandTechnology | CS256 | 15/25 |
| ------------------------------------- | ----- | ----- |

| Inserting   | a node       |             |                      |     |
| ----------- | ------------ | ----------- | -------------------- | --- |
| Assumption: | the nodes    | in the list | are already in order |     |
| Requires    | two pointers | to traverse | the list:            |     |
- pointer to locate the node with data value greater than that of node
| to be | inserted |     |     |     |
| ----- | -------- | --- | --- | --- |
- pointer to ’trail behind’ one node, to point to node before point of
insertion
New node is inserted between the nodes pointed at by these pointers
| HanoiUniversityofScienceandTechnology |     |     | CS256 | 16/25 |
| ------------------------------------- | --- | --- | ----- | ----- |

Inserting a node
| HanoiUniversityofScienceandTechnology | CS256 | 17/25 |
| ------------------------------------- | ----- | ----- |

Inserting a node
| HanoiUniversityofScienceandTechnology | CS256 | 18/25 |
| ------------------------------------- | ----- | ----- |

Inserting a node
| HanoiUniversityofScienceandTechnology | CS256 | 19/25 |
| ------------------------------------- | ----- | ----- |

| Deleting a   | Node            |      |             |             |     |
| ------------ | --------------- | ---- | ----------- | ----------- | --- |
| If list uses | dynamic memory, | then | delete node | from memory |     |
Requires two pointers: one to locate the node to be deleted, one to
| point to                              | the node before | the node | to be deleted |     |       |
| ------------------------------------- | --------------- | -------- | ------------- | --- | ----- |
| HanoiUniversityofScienceandTechnology |                 |          | CS256         |     | 20/25 |

Deleting a node
| HanoiUniversityofScienceandTechnology | CS256 | 21/25 |
| ------------------------------------- | ----- | ----- |

| Destroying  | a Linked       | List      |               |      |     |
| ----------- | -------------- | --------- | ------------- | ---- | --- |
| Must remove | all nodes      | used in   | the list:     |      |     |
| To do       | this, use list | traversal | to visit each | node |     |
1
| 2 For each | node,    |          |      |     |     |
| ---------- | -------- | -------- | ---- | --- | --- |
| – Unlink   | the node | from the | list |     |     |
– If the list uses dynamic memory, then free the node’s memory
| Set the | list head | to NULL |     |     |     |
| ------- | --------- | ------- | --- | --- | --- |
3
| HanoiUniversityofScienceandTechnology |     |     | CS256 |     | 22/25 |
| ------------------------------------- | --- | --- | ----- | --- | ----- |

| Variations | of the Linked | List |     |     |     |
| ---------- | ------------- | ---- | --- | --- | --- |
doubly-linked list: each node contains two pointers: one to the next
| node | in the list, one | to the previous | node in | the list |     |
| ---- | ---------------- | --------------- | ------- | -------- | --- |
circular linked list: the last node in the list points back to the first
| node | in the list, not | to NULL |     |     |     |
| ---- | ---------------- | ------- | --- | --- | --- |
s
| HanoiUniversityofScienceandTechnology |     | CS256 |     |     | 23/25 |
| ------------------------------------- | --- | ----- | --- | --- | ----- |

The STL list Container
#include <list>
See Table 17.1
| HanoiUniversityofScienceandTechnology | CS256 | 24/25 |
| ------------------------------------- | ----- | ----- |

Exercises
| Challenging |        | problems:       | 4,     | 5, 6 + | 7.    |                 |      |     |
| ----------- | ------ | --------------- | ------ | ------ | ----- | --------------- | ---- | --- |
| Additional  |        | exercises:      |        |        |       |                 |      |     |
|             | Merge  | two sorted      | linked | lists. |       |                 |      |     |
|             | Delete | all occurrences |        | of a   | given | key in a linked | list |     |
Given a linked list and positions m and n, reverse the linked list from
|                                       | position | m to    | n     |         |       |               |     |       |
| ------------------------------------- | -------- | ------- | ----- | ------- | ----- | ------------- | --- | ----- |
|                                       | Delete   | N nodes | after | M nodes | of    | a linked list |     |       |
| HanoiUniversityofScienceandTechnology |          |         |       |         | CS256 |               |     | 25/25 |