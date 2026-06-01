# Chapter 10: Elementary Data Structures

## Executive Summary

Chapter 10 covers the foundational pointer-based data structures: **arrays** and **matrices** (contiguous memory), **stacks** (LIFO) and **queues** (FIFO) implemented with arrays, **linked lists** (singly and doubly linked, with sentinel optimization), and **rooted trees** (binary tree pointer representation, and the left-child/right-sibling representation for arbitrary-branching trees). All operations on stacks and queues run in $O(1)$. Linked-list operations on $n$ elements: SEARCH $\Theta(n)$, PREPEND/INSERT $O(1)$, DELETE $O(1)$ (given pointer).

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**Stack operations** (array-based, LIFO):

```
STACK-EMPTY(S)
1  if S.top == 0
2      return TRUE
3  else return FALSE

PUSH(S, x)
1  if S.top == S.size
2      error "overflow"
3  else S.top = S.top + 1
4       S[S.top] = x

POP(S)
1  if STACK-EMPTY(S)
2      error "underflow"
3  else S.top = S.top – 1
4       return S[S.top + 1]
```

**Queue operations** (circular array, FIFO):

```
ENQUEUE(Q, x)
1  Q[Q.tail] = x
2  if Q.tail == Q.size
3      Q.tail = 1
4  else Q.tail = Q.tail + 1

DEQUEUE(Q)
1  x = Q[Q.head]
2  if Q.head == Q.size
3      Q.head = 1
4  else Q.head = Q.head + 1
5  return x
```

**Doubly linked list operations**:

```
LIST-SEARCH(L, k)
1  x = L.head
2  while x ≠ NIL and x.key ≠ k
3      x = x.next
4  return x

LIST-PREPEND(L, x)
1  x.next = L.head
2  x.prev = NIL
3  if L.head ≠ NIL
4      L.head.prev = x
5  L.head = x

LIST-INSERT(x, y)         // insert x immediately after y
1  x.next = y.next
2  x.prev = y
3  if y.next ≠ NIL
4      y.next.prev = x
5  y.next = x

LIST-DELETE(L, x)
1  if x.prev ≠ NIL
2      x.prev.next = x.next
3  else L.head = x.next
4  if x.next ≠ NIL
5      x.next.prev = x.prev
```

**Sentinel-based list** (circular doubly linked with `L.nil` sentinel — simpler DELETE):

```
LIST-DELETE′(x)           // no boundary conditions needed
1  x.prev.next = x.next
2  x.next.prev = x.prev

LIST-INSERT′(x, y)        // insert x after y
1  x.next = y.next
2  x.prev = y
3  y.next.prev = x
4  y.next = x

LIST-SEARCH′(L, k)        // uses sentinel to eliminate end-of-list check
1  L.nil.key = k
2  x = L.nil.next
3  while x.key ≠ k
4      x = x.next
5  if x == L.nil
6      return NIL
7  else return x
```

---

## Deep-Dive Explanations

### Arrays and Matrices

**Array:** Contiguous memory, $O(1)$ random access. Element $A[i]$ at address $a + b(i-s)$ where $a$ = base address, $b$ = element size, $s$ = starting index.

**Matrix storage:**
- **Row-major:** row-by-row contiguously. Element $M[i,j]$ at index $n(i-1)+j$ (1-indexed).
- **Column-major:** column-by-column. Element $M[i,j]$ at index $i + m(j-1)$.
- **Multiple-array:** array of row/column pointers — supports "ragged arrays" but slower on modern cache.

### Stacks and Queues

**Stack** (LIFO): Array $S[1:n]$ with attribute $S.top$. All operations $O(1)$.
- PUSH: increment top, store element
- POP: return top element, decrement top
- Empty: $S.top = 0$; Full: $S.top = S.size$

**Queue** (FIFO): Circular array $Q[1:n]$ with `Q.head` and `Q.tail`. All operations $O(1)$. Holds at most $n-1$ elements (distinguish full from empty: $Q.head = Q.tail$ means empty).

### Linked Lists

**Doubly linked list:** Each node has `.key`, `.next`, `.prev`. Header attribute `L.head`.

| Operation | Time | Notes |
|-----------|------|-------|
| LIST-SEARCH | $\Theta(n)$ | Linear scan |
| LIST-PREPEND | $O(1)$ | Update head |
| LIST-INSERT | $O(1)$ | Given pointer $y$ to insert after |
| LIST-DELETE | $O(1)$ | Given pointer $x$ to delete |

To **delete by key**: LIST-SEARCH ($\Theta(n)$) + LIST-DELETE ($O(1)$) = $\Theta(n)$ total.

**Sentinel optimization:** Replace NIL with sentinel node `L.nil`; list becomes circular. Benefits:
- LIST-DELETE becomes 2 lines (no boundary checks)
- LIST-SEARCH can use the sentinel to eliminate end-of-list check → slightly faster constants
- No asymptotic improvement; costs extra memory per list

### Rooted Trees

**Binary tree:** Each node has `.p` (parent), `.left`, `.right` pointers. $T.root$ → root; NIL pointers mark boundaries.

**Left-child, right-sibling representation** (for arbitrary branching factor):
- Each node has `.p` (parent), `.left-child` (leftmost child), `.right-sibling`
- Uses exactly 3 pointers per node regardless of branching factor
- Traversing all children of node $x$: follow `.left-child`, then traverse `.right-sibling` chain
- Space: $O(n)$ for any $n$-node tree

**Heap representation** (from Chapter 6): uses array indices directly — parent at $\lfloor i/2 \rfloor$, children at $2i$ and $2i+1$. Efficient but only for complete binary trees.

### Time Complexity Summary

| Structure | SEARCH | INSERT | DELETE |
|-----------|--------|--------|--------|
| Unsorted linked list | $\Theta(n)$ | $O(1)$ | $O(1)$ (given ptr) |
| Sorted linked list | $\Theta(n)$ | $\Theta(n)$ | $O(1)$ (given ptr) |
| Stack | N/A | $O(1)$ PUSH | $O(1)$ POP |
| Queue | N/A | $O(1)$ ENQUEUE | $O(1)$ DEQUEUE |

---

## Key Takeaways & Next Steps

1. **Arrays** give $O(1)$ access but $\Theta(n)$ insert/delete at arbitrary positions. **Linked lists** give $O(1)$ insert/delete (given pointer) but $\Theta(n)$ search.
2. **Stacks and queues** are simple but powerful: $O(1)$ all operations, fundamental to BFS, DFS, and expression evaluation.
3. **Sentinels** simplify linked-list code by eliminating boundary conditions — use judiciously (memory cost per list).
4. **Left-child, right-sibling** representation handles trees with arbitrary branching factor in $O(n)$ space.
5. The matrix storage layout (row-major vs. column-major) has significant practical impact on cache performance — important for numerical algorithms.

---

### Navigation

**Previous:** [[PartIII_Introduction_Data_Structures]]
**Next:** [[Ch11_Hash_Tables]]
**Hub:** [[Index_Introduction_to_Algorithms]]
