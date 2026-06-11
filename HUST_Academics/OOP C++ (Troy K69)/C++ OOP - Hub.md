# C++ OOP & Data Structures — Final Exam Hub (Troy K69, CK-20252)

**Textbook:** *Starting Out with C++: From Control Structures through Objects* — Tony Gaddis (8th ed.)
**Exam format:** Oral exam (vấn đáp). Each student draws **1 of 6 topics**, gets **5 minutes to prepare**, then **4–5 minutes to answer in English**.
**Tags:** #cpp #oop #datastructures #exam #oral #TroyK69

---

## How each note is organised

Every topic note answers the **three questions** from its `Questions.txt`, grounded in the Gaddis textbook:

1. **Q1** — explain the concept.
2. **Q2** — explain the purpose of the given "mystery functions".
3. **Q3** — the integrated, **compiled-and-verified** demo (code + real output).

The actual **runnable code** lives in the [`code/`](code) folder, one subfolder per topic. Each builds with `g++` exactly as shown in the note.

---

## The 6 Topics

> Each `code/TopicN_.../` folder has a **`README.md`** code walkthrough — every file, each function explained, and the execution flow when you run the demo.

| # | Note | Code folder | Build command |
|---|---|---|---|
| 1 | [[Topic 1 - Operator Overloading, Object Conversion\|Operator Overloading & Object Conversion]] | `code/Topic1_OperatorOverloading/` | `g++ -std=c++11 main.cpp -o demo` |
| 2 | [[Topic 2 - Inheritance, Polymorphism\|Inheritance & Polymorphism]] | `code/Topic2_Polymorphism/` | `g++ -std=c++11 main.cpp GradedActivity.cpp PassFailActivity.cpp PassFailExam.cpp -o demo` |
| 3 | [[Topic 3 - Exception Handling\|Exception Handling]] | `code/Topic3_Exception/` | `g++ -std=c++11 main.cpp Rectangle.cpp -o demo` |
| 4 | [[Topic 4 - Linked List\|Linked List]] | `code/Topic4_LinkedList/` | `g++ -std=c++11 main.cpp NumberList.cpp -o demo` |
| 5 | [[Topic 5 - Queue\|Queue (Circular Array)]] | `code/Topic5_Queue/` | `g++ -std=c++11 main.cpp IntQueue.cpp -o demo` |
| 6 | [[Topic 6 - Stack\|Stack (Array)]] | `code/Topic6_Stack/` | `g++ -std=c++11 main.cpp IntStack.cpp -o demo` |

> All six projects were compiled and run; the outputs shown in the notes are the **actual** program outputs.

---

**Start here**: [[Topic 1 - Operator Overloading, Object Conversion|Topic 1]]
