# Topic 2 — Inheritance & Polymorphism (Code Walkthrough)

**Files:** `GradedActivity.{h,cpp}`, `PassFailActivity.{h,cpp}`, `PassFailExam.{h,cpp}`, `main.cpp`
**Build & run:**
```bash
g++ -std=c++11 main.cpp GradedActivity.cpp PassFailActivity.cpp PassFailExam.cpp -o demo && ./demo
```

The class hierarchy (each is-a the one above):
```
GradedActivity  ←  PassFailActivity  ←  PassFailExam
```

---

## File: `GradedActivity.{h,cpp}` — the base class

| Member | Meaning |
|---|---|
| `double score` (**protected**) | the numeric score; `protected` so derived classes can read it |

- `GradedActivity()` / `GradedActivity(double s)` — set `score` to 0 or `s`.
- `setScore(double)` / `getScore()` — mutator / accessor for `score`.
- `virtual char getLetterGrade() const` — **the key function.** `virtual` means a call through a base pointer runs the *actual object's* version (late binding). Base version maps score → A/B/C/D/F (`.cpp`).
- `virtual ~GradedActivity()` — virtual destructor so `delete basePtr` cleans up the real object safely.

## File: `PassFailActivity.{h,cpp}` — first derived class

Adds `double minPassingScore` (protected). **Overrides** `getLetterGrade()` to return `'P'` if `score >= minPassingScore`, else `'F'`. Constructor `PassFailActivity(double mps)` calls the base constructor via `: GradedActivity()` then stores `mps`.

## File: `PassFailExam.{h,cpp}` — second derived class (grandchild)

Adds `numQuestions`, `pointsEach`, `numMissed`. Does **not** override `getLetterGrade` → it inherits the pass/fail version from `PassFailActivity`.
- `set(int questions, int missed)` (`.cpp`) computes `pointsEach = 100.0/numQuestions`, then `numericScore = 100 - missed*pointsEach`, then calls the **inherited** `setScore(numericScore)`.
- Constructor `PassFailExam(int,int,double mps)` passes `mps` up via `: PassFailActivity(mps)` then calls `set(...)`.

## File: `main.cpp` — `mysteryFunction()`

Builds `GradedActivity** ptrArray` (array of **base** pointers), fills it with two **different** derived objects, loops calling `getScore()`/`getLetterGrade()`, then frees everything.

---

## Execution flow

```
mysteryFunction():
 1. ptrArray = new GradedActivity*[2]            (array of base pointers on heap)

 2. ptrArray[0] = new PassFailExam(100,25,80.0)
       constructor chain (base → derived):
         GradedActivity()  →  PassFailActivity(80.0)  →  PassFailExam(...)
         PassFailExam::set(100,25): pointsEach=1, score = 100-25 = 75

 3. ptrArray[1] = new PassFailActivity(80.0); setScore(75.0)

 4. loop i = 0,1:
       getScore()        → not virtual → returns 75 for both
       getLetterGrade()  → VIRTUAL → runs each object's own version:
            ptr[0] (PassFailExam→inherits PassFailActivity): 75>=80? no → 'F'
            ptr[1] (PassFailActivity):                       75>=80? no → 'F'

 5. delete ptrArray[i]  (virtual destructor → derived dtor then base dtor)
    delete[] ptrArray
```

**The teaching point in the flow:** step 4 is where polymorphism shows — both calls go through a `GradedActivity*`, yet the **pass/fail** logic runs (giving `'F'` for a 75), not the base A–F logic (which would give `'C'`). That only happens because `getLetterGrade` is `virtual`.
