# Exam Study — Topic 2: Inheritance & Polymorphism

**Source:** `CK-20252-Troy K69/2 - Inheritance, Polymorphism/`
**Course:** [[C++ OOP - Hub|C++ OOP & Data Structures — Final Exam Hub]]
**Tags:** #cpp #oop #inheritance #polymorphism #virtual #exam

---

## 🎤 Professor's Opening (deliver this first)

> "Polymorphism literally means *'many forms'*. In C++ it is the ability to call the **same function through a base-class pointer or reference** and have the program automatically execute the **correct derived version at run time**. The mechanism is the `virtual` keyword: it switches the call from *static binding*, decided at compile time, to *dynamic binding*, decided at run time using a hidden lookup table called the **vtable**. This is what lets me store a `GradedActivity*` that secretly points to a `PassFailExam`, call `getLetterGrade()`, and get the pass/fail logic — not the base logic. It is the single most powerful idea in object-oriented design because it lets me write code against an *interface* and add new types later without changing that code."

---

## 1. Executive Summary

We have an inheritance hierarchy of grading classes:

```
GradedActivity            (base: numeric score → A/B/C/D/F)
   └── PassFailActivity   (overrides grading: ≥ minPassingScore → 'P', else 'F')
          └── PassFailExam(computes a numeric score from #questions & #missed)
```

The "mystery function" builds an **array of base-class pointers** (`GradedActivity**`), fills it with *different* derived objects, and loops calling `getScore()`/`getLetterGrade()`. Because `getLetterGrade()` is `virtual`, each element runs *its own* version — that is runtime polymorphism in action.

---

## 2. Zero-Loss Extraction

### 2.1 The class hierarchy (key parts)

```cpp
class GradedActivity {
protected:
    double score;
public:
    GradedActivity()            { score = 0.0; }
    GradedActivity(double s)    { score = s; }
    void   setScore(double s)   { score = s; }
    double getScore() const     { return score; }
    virtual char getLetterGrade() const;   // <-- VIRTUAL: enables polymorphism
};

// A/B/C/D/F based on numeric score
char GradedActivity::getLetterGrade() const {
    if      (score > 89) return 'A';
    else if (score > 79) return 'B';
    else if (score > 69) return 'C';
    else if (score > 59) return 'D';
    else                 return 'F';
}

class PassFailActivity : public GradedActivity {
protected:
    double minPassingScore;
public:
    PassFailActivity()        : GradedActivity() { minPassingScore = 0.0; }
    PassFailActivity(double mps): GradedActivity() { minPassingScore = mps; }
    virtual char getLetterGrade() const;   // overrides the base version
};

char PassFailActivity::getLetterGrade() const {
    return (score >= minPassingScore) ? 'P' : 'F';
}

class PassFailExam : public PassFailActivity {
private:
    int    numQuestions;
    double pointsEach;
    int    numMissed;
public:
    PassFailExam(int questions, int missed, double mps)
        : PassFailActivity(mps) { set(questions, missed); }
    void set(int, int);        // computes numericScore and calls setScore()
    // ... accessors ...
};

void PassFailExam::set(int questions, int missed) {
    numQuestions = questions;
    numMissed    = missed;
    pointsEach   = 100.0 / numQuestions;
    double numericScore = 100.0 - (missed * pointsEach);
    setScore(numericScore);    // inherited mutator
}
```

### 2.2 The mystery function (decoded)

```cpp
void mysteryFunction()
{
    const int SIZE = 2;
    GradedActivity** ptrArray = new GradedActivity*[SIZE]; // array of BASE pointers

    ptrArray[0] = new PassFailExam(100, 25, 80.0);  // derived object #1
    ptrArray[1] = new PassFailActivity(80.0);        // derived object #2
    ptrArray[1]->setScore(75.0);

    for (int i = 0; i < SIZE; i++) {
        cout << "Activity " << (i + 1) << ":\n";
        cout << "The activity's numeric score is " << ptrArray[i]->getScore() << endl;
        cout << "The activity's letter grade is " << ptrArray[i]->getLetterGrade() << endl;
        cout << "---------------------------\n";
    }

    for (int i = 0; i < SIZE; i++) delete ptrArray[i]; // free each object
    delete[] ptrArray;                                  // free the pointer array
}
```

**Purpose:** It demonstrates **polymorphism through a container of base-class pointers**. One uniform loop drives objects of different concrete types, and the *right* `getLetterGrade()` runs for each thanks to `virtual` dispatch. It also demonstrates correct **two-level dynamic-memory cleanup** (`delete` each object, then `delete[]` the array).

### 2.3 Compiled demo + verified output

```
Activity 1:
The activity's numeric score is 75.0
The activity's letter grade is F
---------------------------
Activity 2:
The activity's numeric score is 75.0
The activity's letter grade is F
---------------------------
```

> [!note] Trace the numbers — be ready to explain this on the spot
> **Activity 1** = `PassFailExam(100, 25, 80.0)`: `pointsEach = 100/100 = 1`, `numericScore = 100 − 25×1 = 75`. The exam inherits `getLetterGrade()` from `PassFailActivity`, so it compares `75 ≥ 80` → **false → 'F'**.
> **Activity 2** = `PassFailActivity(80.0)` then `setScore(75)`: `75 ≥ 80` → **false → 'F'**.
> Both print **'F'**, but for the polymorphism point what matters is that the *pass/fail* version ran — **not** the base A–F version (which would have returned 'C' for a 75).

---

## 3. Deep-Dive Explanations (the *why*)

### 3.1 Static vs. dynamic binding — the heart of the topic

```cpp
GradedActivity* p = new PassFailActivity(80.0);
p->getLetterGrade();
```

- **Without `virtual`** (static binding): the compiler looks at the *pointer's declared type* (`GradedActivity*`) and hard-wires the call to `GradedActivity::getLetterGrade`. Wrong version! You'd get A–F logic.
- **With `virtual`** (dynamic binding): at run time the program follows the object's hidden **vtable pointer** to find the actual type's function. Correct version → pass/fail logic.

> [!important] One sentence to memorise
> *"`virtual` turns a compile-time decision based on the pointer type into a run-time decision based on the object type."*

### 3.2 Why a base pointer can point to a derived object (the "is-a" rule)

A `PassFailExam` **is-a** `PassFailActivity` **is-a** `GradedActivity`. Public inheritance models "is-a", so a base pointer can legally hold the address of any derived object. This **substitutability** is what makes the uniform loop possible (Liskov Substitution Principle).

### 3.3 The constructor chain

Creating a `PassFailExam` runs constructors **base → derived**: `GradedActivity` first, then `PassFailActivity` (via its `: GradedActivity()` initialiser list, which sets `minPassingScore`), then `PassFailExam` (which calls `set()` to compute the score). Initialiser lists (`: PassFailActivity(mps)`) are how a derived constructor passes arguments up to its base.

### 3.4 THE classic trap: the destructor is **not** `virtual`

Look closely — `GradedActivity` has **no virtual destructor**. The mystery function deletes objects through a base pointer:

```cpp
delete ptrArray[i];   // ptrArray[i] is GradedActivity*, object is really a PassFailExam
```

> [!warning] This is technically **undefined behaviour**.
> When you `delete` a derived object through a base pointer and the base destructor is **not** `virtual`, only the *base* destructor runs — the derived part may not be cleaned up. These particular classes have no extra resources, so nothing leaks *here*, but the **rule** is: *a polymorphic base class must declare a `virtual` destructor* (`virtual ~GradedActivity() {}`). Mention this and you instantly sound like a professor.

### 3.5 `protected` vs `private`

`score` is `protected`, not `private`, so derived classes (`PassFailActivity::getLetterGrade`) can read it directly. `protected` = "private to the outside world, but accessible to my descendants." Trade-off: convenience vs. weaker encapsulation (a bug in any subclass can corrupt `score`).

### 3.6 Overriding vs overloading vs hiding (don't confuse them)

| Term | Meaning |
|---|---|
| **Overriding** | Same signature, derived redefines a `virtual` base function → runtime dispatch. (This topic.) |
| **Overloading** | Same name, *different parameters*, resolved at compile time. (Topic 1.) |
| **Hiding** | A derived name hides *all* base overloads of that name; not polymorphism. |

---

## 4. Key Takeaways & Next Steps

1. **Polymorphism = same call, different behaviour, decided at run time** via `virtual` + base pointers/references.
2. The mechanism is the **vtable**; the cost is one extra indirection and a hidden pointer per object — cheap for the flexibility gained.
3. **Public inheritance models "is-a"**, which is why a base pointer can hold a derived object.
4. **Always give a polymorphic base class a `virtual` destructor** — the most important pitfall in this code.
5. Constructors run **base → derived**; destructors run **derived → base**.

> [!question] Stretch questions to rehearse
> 1. What is a *pure virtual* function (`virtual char getLetterGrade() const = 0;`) and how does it create an *abstract class*?
> 2. Why can't constructors be `virtual`, but destructors should be?

---

## Likely Follow-up Oral Questions (with model answers)

**Q1. What exactly does the `virtual` keyword do?**
It enables dynamic (late) binding. A call to a `virtual` function through a base pointer or reference is resolved at run time based on the *actual object type*, using the vtable, rather than at compile time based on the pointer's static type.

**Q2. Why store `GradedActivity*` instead of `GradedActivity` objects in the array?**
Polymorphism in C++ works only through pointers or references. If you stored objects by value, assigning a derived object into a base slot would **slice** it — the derived parts are chopped off and you lose the overridden behaviour. Pointers preserve the full object and enable dynamic dispatch.

**Q3. What is object slicing?**
Copying a derived object into a base-type variable, which discards the derived members and reverts virtual calls to the base version. Avoided by using pointers/references.

**Q4. Both activities printed 'F'. Does that prove polymorphism worked?**
Yes — the proof is that a numeric score of 75 produced **'F'** (pass/fail logic, 75 < 80), not **'C'** (the base A–F logic). The pass/fail version ran even though we called through a `GradedActivity*`.

**Q5. Is there a bug in the cleanup code?**
The cleanup itself (`delete` each, then `delete[]` the array) is correct, but the base class lacks a `virtual` destructor, so deleting derived objects through a base pointer is undefined behaviour in general. The fix is to add `virtual ~GradedActivity() {}`.

**Q6. What is an abstract class?**
A class with at least one pure virtual function (`= 0`). It cannot be instantiated and serves purely as an interface that derived classes must implement.

---

## Graph View Links

**Previous**: [[Exam Study - Topic 1 (Operator Overloading, Object Conversion)]]
**Next**: [[Exam Study - Topic 3 (Exception Handling)]]
**Hub**: [[C++ OOP - Hub]]
