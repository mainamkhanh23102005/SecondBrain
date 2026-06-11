# Topic 2 — Inheritance & Polymorphism

**Questions source:** `2 - Inheritance, Polymorphism/Questions.txt`
**Runnable code:** `code/Topic2_Polymorphism/` (multi-file project)
**Textbook:** *Starting Out with C++* (Gaddis, 8th ed.), Ch. 15 — Inheritance, Polymorphism, and Virtual Functions
**Hub:** [[C++ OOP - Hub]]

---

## Q1. Explain the ideas of Polymorphism in OOP C++

**Polymorphism** — *"Polymorphism allows an object reference variable or an object pointer to reference objects of different types and to call the correct member functions, depending upon the type of object being referenced"* (Gaddis §15.3). The word means *"many forms"*: the **same call** through a base-class pointer/reference runs the **correct version** for whatever derived object it actually points to.

The mechanism is the **virtual function**. From the textbook: *"A virtual function is a member function that is dynamically bound to function calls. In dynamic binding, C++ determines which function to call at runtime, depending on the type of the object responsible for the call"* (§15.3). You declare it by putting `virtual` before the return type in the base class:

```cpp
virtual char getLetterGrade() const;
```

This is the contrast that examiners test (the lecturer's slides call these **Early Binding** vs **Late Binding**):
- **Early Binding (Static Typing)** — the slide's wording: *"Method calls are resolved based on the pointer's type, not the actual object it points to."* Without `virtual`, the compiler binds the call at **compile time** to the **pointer's declared type** → it always calls the base version.
- **Late Binding (Dynamic Binding)** — *"C++ introduces virtual functions to implement late binding."* With `virtual`, the choice is deferred to **runtime**, based on the **actual object type**. A `GradedActivity*` that really points to a `PassFailActivity` calls `PassFailActivity::getLetterGrade`.

The lecturer demonstrates this with a minimal `BaseClass`/`DerivedClass` `display()` example:

```cpp
class BaseClass    { public: virtual void display(){ cout << "Base";   } };  // virtual!
class DerivedClass : public BaseClass { public: void display(){ cout << "Derived"; } };

DerivedClass d;
BaseClass* basePtr = &d;   // a base pointer holding a derived object
basePtr->display();        // NO virtual → "Base" (early);  WITH virtual → "Derived" (late)
```

```
Same pointer type, different objects → different function runs:

   GradedActivity* p ──▶ ┌──────────────────────┐
                         │ a PassFailActivity    │   p->getLetterGrade()
                         │ object                │      │
                         └──────────────────────┘      ▼
   WITHOUT virtual (EARLY binding): decided by the POINTER type → GradedActivity::getLetterGrade  (A/B/C..) ✗
   WITH    virtual (LATE  binding): decided by the OBJECT  type → PassFailActivity::getLetterGrade (P/F)    ✓
```

> **Critical requirement (textbook §15.3):** *"Polymorphism Requires References or Pointers."* If you pass/store an object **by value**, the derived part is sliced off (**object slicing**) and you lose the overridden behaviour. That is exactly why the mystery function uses an **array of pointers**.

The hierarchy in this project:
```
GradedActivity            (numeric score → A/B/C/D/F)
   └── PassFailActivity   (score ≥ minPassingScore → 'P' else 'F')   [overrides getLetterGrade]
          └── PassFailExam (computes the numeric score from #questions & #missed)
```

> **Constructor / destructor order (from the slides):** *"When an object of a derived class is created, the base class's constructor is executed first, followed by the derived class's constructor. When it is destroyed, its own destructor is called first, then that of the base class."* So construction runs **base → derived**, and destruction runs **derived → base** (the reverse).
>
> ```
> new PassFailExam(...)        delete a PassFailExam
>   GradedActivity()             ~PassFailExam()
>   PassFailActivity()    vs     ~PassFailActivity()
>   PassFailExam()               ~GradedActivity()
>   (base → derived)             (derived → base)
> ```

---

## Q2. Explain the primary purpose of the following function

```cpp
void mysteryFunction()
{
    const int SIZE = 2;
    GradedActivity** ptrArray = new GradedActivity*[SIZE]; // array of BASE pointers

    ptrArray[0] = new PassFailExam(100, 25, 80.0);  // a derived object
    ptrArray[1] = new PassFailActivity(80.0);        // a different derived object
    ptrArray[1]->setScore(75.0);

    for (int i = 0; i < SIZE; i++) {
        cout << "Activity " << (i + 1) << ":\n";
        cout << "The activity's numeric score is " << ptrArray[i]->getScore() << endl;
        cout << "The activity's letter grade is " << ptrArray[i]->getLetterGrade() << endl;
        cout << "---------------------------\n";
    }

    for (int i = 0; i < SIZE; i++) delete ptrArray[i];  // free each object
    delete[] ptrArray;                                   // free the pointer array
}
```

**Memory picture — one array, two different object types:**

```
   ptrArray (array of GradedActivity*)
   ┌──────────┬──────────┐
   │ ptr[0] ● │ ptr[1] ● │   (on the heap: new GradedActivity*[2])
   └────┼─────┴────┼─────┘
        │          │
        ▼          ▼
  ┌──────────────┐  ┌──────────────────┐
  │ PassFailExam │  │ PassFailActivity │   ← actual objects (also on the heap)
  │ score = 75   │  │ score = 75       │
  └──────────────┘  └──────────────────┘
        │                  │
   ptr[i]->getLetterGrade() picks each object's OWN version (virtual):
        ▼                  ▼
   'F' (75 < 80)      'F' (75 < 80)     ← pass/fail logic, NOT base A/B/C..
```

**Primary purpose:** it **demonstrates runtime polymorphism through a container of base-class pointers**. A single uniform loop drives objects of *different* concrete types, and because `getLetterGrade()` is `virtual`, each element automatically runs **its own** version (dynamic binding). It also shows the matching **two-step cleanup** for dynamic memory: `delete` each object, then `delete[]` the array of pointers.

- `getScore()` is **not** virtual → it simply returns the stored `score` (same for all).
- `getLetterGrade()` **is** virtual → element 0 and element 1 use the **pass/fail** logic, not the base A–F logic.

---

## Q3. Integrate this function into the project and run a demo

**Full runnable files:** `code/Topic2_Polymorphism/` — `GradedActivity.{h,cpp}`, `PassFailActivity.{h,cpp}`, `PassFailExam.{h,cpp}`, `main.cpp` (contains `mysteryFunction`).
**Build & run:**
```bash
g++ -std=c++11 main.cpp GradedActivity.cpp PassFailActivity.cpp PassFailExam.cpp -o demo && ./demo
```

**✅ Verified output:**
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

**How to read it (be ready to trace this aloud):**
- **Activity 1** = `PassFailExam(100, 25, 80.0)`: `pointsEach = 100/100 = 1`, `numericScore = 100 − 25×1 = 75`; `minPassingScore = 80`. It inherits `getLetterGrade` from `PassFailActivity`, so `75 ≥ 80` → **false → 'F'**.
- **Activity 2** = `PassFailActivity(80.0)` then `setScore(75)`: `75 ≥ 80` → **false → 'F'**.

The **proof that polymorphism worked** is that a score of 75 produced **'F'** (pass/fail rule, 75 < 80) and **not 'C'** (which the base A–F rule would give) — even though we called through a `GradedActivity*`.

> **Note:** the base class is given a `virtual ~GradedActivity()` destructor in this project. That is best practice for any class deleted through a base pointer; without it, `delete ptrArray[i]` would be undefined behaviour.

---

**Previous**: [[Topic 1 - Operator Overloading, Object Conversion]] · **Next**: [[Topic 3 - Exception Handling]] · **Hub**: [[C++ OOP - Hub]]
