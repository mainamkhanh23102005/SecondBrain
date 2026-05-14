B Sets, Etc.

Many  chapters  of  this  book  touch  on  the  elements  of  discrete
mathematics.  This  appendix  reviews  the  notations,  deﬁnitions,  and
elementary  properties  of  sets,  relations,  functions,  graphs,  and  trees.  If
you are already well versed in this material, you can probably just skim
this chapter.

B.1 Sets

A  set  is  a  collection  of  distinguishable  objects,  called  its  members  or
elements. If an object x is a member of a set S, we write x ∈ S (read “x
is  a  member  of  S”  or,  more  brieﬂy,  “x  belongs  to  S”).  If  x  is  not  a
member  of  S,  we  write  x  ∉  S.  To  describe  a  set  explicitly,  write  its
members as a list inside braces. For example, to deﬁne a set S to contain
precisely the numbers 1, 2, and 3, write S = {1, 2, 3}. Since 2 belongs to
the set S, we can write 2 ∈ S, and since 4 is not a member, we can write
4 ∉ S. A set cannot contain the same object more than once,1 and its
elements are not ordered. Two sets A and B are equal, written A = B, if
they contain the same elements. For example, {1, 2, 3, 1} = {1, 2, 3} =
{3, 2, 1}.

We adopt special notations for frequently encountered sets:

Ø denotes the empty set, that is, the set containing no members.

ℤ  denotes  the  set  of  integers,  that  is,  the  set  {…  −2,  −1,  0,  1,
2,…}.

ℝ denotes the set of real numbers.
ℕ denotes the set of natural numbers, that is, the set {0, 1, 2,…}.2
If all the elements of a set A are contained in a set B, that is, if x ∈
A implies x ∈ B, then we write A ⊆ B and say that A is a subset of B. A
set  A  is  a  proper  subset  of  set  B,  written  A  ⊂  B,  if  A  ⊆  B  but  A  ≠  B.
(Some  authors  use  the  symbol  “⊂”  to  denote  the  ordinary  subset
relation, rather than the proper-subset relation.) Every set is a subset of
itself: A ⊆ A for any set A. For two sets A and B, we have A = B if and
only  if  A  ⊆  B  and  B  ⊆  A.  The  subset  relation  is  transitive  (see  page
1159): for any three sets A, B, and C, if A ⊆ B and B ⊆ C, then A ⊆ C.
The proper-subset relation is transitive as well. The empty set is a subset
of all sets: for any set A, we have Ø ⊆ A.

Sets can be speciﬁed in terms of other sets. Given a set A, a set B ⊆
A can be deﬁned by stating a property that distinguishes the elements of
B. For example, one way to deﬁne the set of even integers is {x : x ∈ ℤ
and  x/2  is  an  integer}.  The  colon  in  this  notation  is  read  “such  that.”
(Some authors use a vertical bar in place of the colon.)

Given two sets A and B, set operations deﬁne new sets:

The intersection of sets A and B is the set

A ∩ B = {x : x ∈ A and x ∈ B}.
The union of sets A and B is the set

A ∪ B = {x : x ∈ A or x ∈ B}.
The difference between two sets A and B is the set

A − B = {x : x ∈ A and x ∉ B}.
Set operations obey the following laws:

Empty set laws:

A ∩ Ø = Ø,
A ∪ Ø = A.

Idempotency laws:

A ∩ A = A,
A ∪ A = A.

Commutative laws:

A ∩ B = B ∩ A,
A ∪ B = B ∪ A.

Figure B.1 A Venn diagram illustrating the ﬁrst of DeMorgan’s laws (B.2). Each of the sets A, B,
and C is represented as a circle.

Associative laws:

A ∩ (B ∩ C) = (A ∩ B) ∩ C,
A ∪ (B ∪ C) = (A ∪ B) ∪ C.

Distributive laws:

Absorption laws:

A ∩ (A ∪ B) = A,
A ∪ (A ∩ B) = A.

DeMorgan’s laws:

Figure  B.1  illustrates  the  ﬁrst  of  DeMorgan’s  laws,  using  a  Venn
diagram: a graphical picture in which sets are represented as regions of
the plane.

Often, all the sets under consideration are subsets of some larger set
U called the universe. For example, when considering various sets made
up  only  of  integers,  the  set  ℤ  of  integers  is  an  appropriate  universe.
Given a universe U, we deﬁne the complement of a set A as Ā = U − A =
{x : x ∈ U and x ∉ A}. For any set A ⊆ U, we have the following laws:

= A,
A ∩ Ā = Ø,
A ∪ Ā = U.

An  equivalent  way  to  express  DeMorgan’s
complements. For any two sets B, C ⊆ U, we have

laws  (B.2)  uses  set

B ∩ C = B ∪ C,
B ∪ C = B ∩ C.

Two sets A and B are disjoint if they have no elements in common,
that  is,  if  A  ∩  B  =  Ø.  A  collection  of  sets  S1,  S2,  …  ,  either  ﬁnite  or
inﬁnite, is a set of sets, in which each member is a set Si. A collection S
= {Si} of nonempty sets forms a partition of a set S if

the sets are pairwise disjoint, that is, Si, Sj ∈ S and i ≠ j imply Si
∩ Sj = Ø,
their union is S, that is,

In other words, S forms a partition of S if each element of S appears in
exactly one set Si ∈ S.

The number of elements in a set is the cardinality (or size) of the set,
denoted |S|. Two sets have the same cardinality if their elements can be

put into a one-to-one correspondence. The cardinality of the empty set
is |Ø| = 0. If the cardinality of a set is a natural number, the set is ﬁnite,
and otherwise, it is inﬁnite. An inﬁnite set that can be put into a one-to-
one  correspondence  with  the  natural  numbers  ℕ  is  countably  inﬁnite,
and  otherwise,  it  is  uncountable.  For  example,  the  integers  ℤ  are
countable, but the reals ℝ are uncountable.

For any two ﬁnite sets A and B, we have the identity

from which we can conclude that

|A ∪ B| ≤ |A| + |B|.
If A and B are disjoint, then |A ∩ B| = 0 and thus |A ∪ B| = |A| + |B|. If
A ⊆ B, then |A| ≤ |B|.

A  ﬁnite  set  of  n  elements  is  sometimes  called  an  n-set.  A  1-set  is
called a singleton. A subset of k elements of a set is sometimes called a
k-subset.

We denote the set of all subsets of a set S, including the empty set
and S itself, by 2S, called the power set of S. For example, 2{a,b} = {Ø,
{a}, {b}, {a, b}}. The power set of a ﬁnite set S has cardinality 2|S| (see
Exercise B.1-5).

We sometimes care about setlike structures in which the elements are
ordered. An ordered pair of two elements a and b is denoted (a, b) and is
deﬁned formally as the set (a, b) = {a, {a, b}}. Thus, the ordered pair (a,
b) is not the same as the ordered pair (b, a).

The Cartesian product of two sets A and B, denoted A × B, is the set
of all ordered pairs such that the ﬁrst element of the pair is an element
of A and the second is an element of B. More formally,

A × B = {(a, b) : a ∈ A and b ∈ B}.
For example, {a, b}×{a, b, c} = {(a, a), (a, b), (a, c), (b, a), (b, b), (b, c)}.
When A and B are ﬁnite sets, the cardinality of their Cartesian product
is

The Cartesian product of n sets A1, A2, … , An is the set of n-tuples

A1 × A2 × … × An = {(a1, a2, … , an) : ai ∈ Ai for i = 1, 2, … , n},

whose cardinality is

|A1 × A2 × … × An| = |A1| · |A2| · |An|

if  all  sets  Ai  are  ﬁnite.  We  denote  an  n-fold  Cartesian  product  over  a
single set A by the set

whose cardinality is |An| = |A|n if A is ﬁnite. We can also view an n-tuple
as a ﬁnite sequence of length n (see page 1162).

Intervals are continuous sets of real numbers. We denote them with
parentheses  and/or  brackets.  Given  real  numbers  a  and  b,  the  closed
interval  [a,  b]  is  the  set  {x  ∈  ℝ  :  a  ≤  x  ≤  b}  of  reals  between  a  and  b,
including both a and b. (If a > b, this deﬁnition implies that [a, b] = Ø.)
The  open  interval  (a,  b)  =  {x  ∈  ℝ  :  a  <  x  <  b}  omits  both  of  the
endpoints from the set. There are two half-open intervals [a, b) = {x ∈ ℝ
: a ≤ x < b} and (a, b] = {x ∈ ℝ : a < x ≤ b}, each of which excludes one
endpoint.

Intervals  can  also  be  deﬁned  on  the  integers  by  replacing  ℝ  in  the
these deﬁnitions by ℤ. Whether the interval is deﬁned over the reals or
integers can usually be inferred from context.

Exercises

B.1-1
Draw  Venn  diagrams  that  illustrate  the  ﬁrst  of  the  distributive  laws
(B.1).

B.1-2
Prove the generalization of DeMorgan’s laws to any ﬁnite collection of
sets:

