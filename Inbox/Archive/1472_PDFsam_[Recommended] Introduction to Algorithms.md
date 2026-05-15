A1 ∩ A2 ∩ … ∩ An = A1 ∪ A2 ∪ … ∪ An,
A1 ∪ A2 ∪ … ∪ An = A1 ∩ A2 ∩ … ∩ An.

★ B.1-3
Prove the generalization of equation (B.3), which is called the principle
of inclusion and exclusion:

|A1 ∪ A2 ∪ … ∪ An| =
|A1| + |A2| + … + |An|
− |A1 ∩ A2| − |A1 ∩ A3| − … (all pairs)
(all triples)
+ |A1 ∩ A2 ∩ A3| + …

⋮
+ (−1)n−1 |A1 ∩ A2 ∩ … ∩ An|.

B.1-4
Show that the set of odd natural numbers is countable.

B.1-5
Show that for any ﬁnite set S, the power set 2S has 2|S| elements (that is,
there are 2|S| distinct subsets of S).

B.1-6
Give an inductive deﬁnition for an n-tuple by extending the set-theoretic
deﬁnition for an ordered pair.

B.2 Relations

A  binary  relation  R  on  two  sets  A  and  B  is  a  subset  of  the  Cartesian
product  A×B.  If  (a,  b)  ∈  R,  we  sometimes  write  a  R  b.  When  we  say
that R is a binary relation on a set A, we mean that R is a subset of A ×
A.  For  example,  the  “less  than”  relation  on  the  natural  numbers  is  the

set {(a, b) : a, b ∈ ℕ and a < b}. An n-ary relation on sets A1, A2, … ,
An is a subset of A1 × A2 × … × An.

A binary relation R ⊆ A × A is reﬂexive if

a R a

for all a ∈ A. For example, “=” and “≤” are reﬂexive relations on ℕ, but
“<” is not. The relation R is symmetric if

a R b implies b R a

for  all  a,  b  ∈  A.  For  example,  “=”  is  symmetric,  but  “<”  and  “≤”  are
not. The relation R is transitive if

a R b and b R c imply a R c

for  all  a,  b,  c  ∈  A.  For  example,  the  relations  “<,”  “≤,”  and  “=”  are
transitive, but the relation R = {(a, b) : a, b ∈ ℕ and a = b − 1} is not,
since 3 R 4 and 4 R 5 do not imply 3 R 5.

A relation that is reﬂexive, symmetric, and transitive is an equivalence
relation.  For  example,  “=”  is  an  equivalence  relation  on  the  natural
numbers, but “<” is not. If R is an equivalence relation on a set A, then
for a ∈ A, the equivalence class of a is the set [a] = {b ∈ A : a R b}, that
is, the set of all elements equivalent to a. For example, if we deﬁne R =
{(a, b) : a, b ∈ ℕ and a + b is an even number}, then R is an equivalence
relation, since a + a is even (reﬂexive), a + b is even implies b + a is even
(symmetric),  and  a  +  b  is  even  and  b  +  c  is  even  imply  a  +  c  is  even
(transitive).  The  equivalence  class  of  4  is  [4]  =  {0,  2,  4,  6,…},  and  the
equivalence  class  of  3  is  [3]  =  {1,  3,  5,  7,…}.  A  basic  theorem  of
equivalence classes is the following.

Theorem B.1 (An equivalence relation is the same as a partition)
The equivalence classes of any equivalence relation R on a set A form a
partition  of  A,  and  any  partition  of  A  determines  an  equivalence
relation  on  A  for  which  the  sets  in  the  partition  are  the  equivalence
classes.

Proof      For  the  ﬁrst  part  of  the  proof,  we  must  show  that  the
equivalence  classes  of  R  are  nonempty,  pairwise-disjoint  sets  whose

union is A. Because R is reﬂexive, a ∈ [a], and so the equivalence classes
are  nonempty.  Moreover,  since  every  element  a  ∈  A  belongs  to  the
equivalence  class  [a],  the  union  of  the  equivalence  classes  is  A.  It
remains to show that the equivalence classes are pairwise disjoint, that
is, if two equivalence classes [a] and [b] have an element c in common,
then  they  are  in  fact  the  same  set.  Suppose  that  a  R  c  and  b  R  c.
Symmetry gives that c R b and, by transitivity, a R b. Thus, we have x R
a for any arbitrary element x ∈ [a] and, by transitivity, x R b, and thus
[a] ⊆ [b]. Similarly, [b] ⊆ [a], and thus [a] = [b].

For the second part of the proof, let A = {Ai} be a partition of A,
and deﬁne R = {(a, b) : there exists i such that a ∈ Ai and b ∈ Ai}. We
claim that R is an equivalence relation on A. Reﬂexivity holds, since a ∈
Ai implies a R a. Symmetry holds, because if a R b, then a and b belong
to the same set Ai, and hence b R a. If a R b and b R c, then all three
elements are in the same set Ai, and thus a R c and transitivity holds. To
see that the sets in the partition are the equivalence classes of R, observe
that if a ∈ Ai, then x ∈ [a] implies x ∈ Ai, and x ∈ Ai implies x ∈ [a].

▪

A binary relation R on a set A is antisymmetric if

a R b and b R a imply a = b.

For example, the “≤” relation on the natural numbers is antisymmetric,
since  a  ≤  b  and  b  ≤  a  imply  a  =  b.  A  relation  that  is  reﬂexive,
antisymmetric,  and  transitive  is  a  partial  order,  and  we  call  a  set  on
which a partial order is deﬁned a partially ordered set. For example, the
relation “is a descendant of ” is a partial order on the set of all people
(if we view individuals as being their own descendants).

In  a  partially  ordered  set  A,  there  may  be  no  single  “maximum”
element  a  such  that  b  R  a  for  all  b  ∈  A.  Instead,  the  set  may  contain
several maximal elements a such that for no b ∈ A, where b ≠ a, is it the
case that a R b. For example, a collection of different-sized boxes may
contain several maximal boxes that don’t ﬁt inside any other box, yet it
has no single “maximum” box into which any other box will ﬁt.3

A relation R on a set A is a total relation if for all a, b ∈ A, we have a
R  b  or  b  R  a  (or  both),  that  is,  if  every  pairing  of  elements  of  A  is
related by R. A partial order that is also a total relation is a total order
or  linear  order.  For  example,  the  relation  “≤”  is  a  total  order  on  the
natural  numbers,  but  the  “is  a  descendant  of ”  relation  is  not  a  total
order  on  the  set  of  all  people,  since  there  are  individuals  neither  of
whom is descended from the other. A total relation that is transitive, but
not necessarily either symmetric or antisymmetric, is a total preorder.

Exercises

B.2-1
Prove that the subset relation “⊆” on all subsets of ℤ is a partial order
but not a total order.

B.2-2
Show that for any positive integer n, the relation “equivalent modulo n”
is an equivalence relation on the integers. (We say that a = b (mod n) if
there  exists  an  integer  q  such  that  a  −  b  =  qn.)  Into  what  equivalence
classes does this relation partition the integers?

B.2-3
Give examples of relations that are

a. reﬂexive and symmetric but not transitive,

b. reﬂexive and transitive but not symmetric,

c. symmetric and transitive but not reﬂexive.

B.2-4
Let  S  be  a  ﬁnite  set,  and  let  R  be  an  equivalence  relation  on  S  ×  S.
Show that if in addition R is antisymmetric, then the equivalence classes
of S with respect to R are singletons.

B.2-5
Professor  Narcissus  claims  that  if  a  relation  R  is  symmetric  and
transitive,  then  it  is  also  reﬂexive.  He  offers  the  following  proof.  By

