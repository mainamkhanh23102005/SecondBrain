# Part IV Introduction: Advanced Design and Analysis Techniques

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #dynamic-programming #greedy #amortized-analysis

## Overview

Part IV covers three important algorithm design and analysis techniques that go beyond the divide-and-conquer and sorting paradigms.

---

## Chapters in This Part

| Chapter | Technique | Core Idea |
|---|---|---|
| Ch 14 | Dynamic Programming | Store subproblem solutions; transform exponential → polynomial |
| Ch 15 | Greedy Algorithms | Make locally optimal choices at each step |
| Ch 16 | Amortized Analysis | Bound total cost of a sequence of operations |

## Key Distinctions

**Dynamic programming vs. Greedy:**
- Both apply to optimization problems with choice sequences
- DP: exhaustively considers all subproblem solutions; correct for any problem with optimal substructure + overlapping subproblems
- Greedy: makes one locally optimal choice and never reconsiders; faster but only correct when the greedy-choice property holds

**Amortized analysis:** Not a design technique but an analysis technique — provides a worst-case bound on a sequence rather than individual operations. Most useful when some operations are expensive but rare.

---

### Navigation
**Previous:** [[Ch13_Red_Black_Trees]]
**Next:** [[Ch14_Dynamic_Programming]]
**Hub:** [[Index_Introduction_to_Algorithms]]
