C Counting and Probability

This appendix reviews elementary combinatorics and probability theory.
If  you  have  a  good  background  in  these  areas,  you  may  want  to  skim
the  beginning  of  this  appendix  lightly  and  concentrate  on  the  later
sections. Most of this book’s chapters do not require probability, but for
some chapters it is essential.

Section C.1 reviews elementary results in counting theory, including
standard  formulas  for  counting  permutations  and  combinations.  The
axioms  of  probability  and  basic
facts  concerning  probability
distributions  form  Section  C.2.  Random  variables  are  introduced  in
Section  C.3,  along  with  the  properties  of  expectation  and  variance.
Section  C.4  investigates  the  geometric  and  binomial  distributions  that
arise  from  studying  Bernoulli  trials.  The  study  of  the  binomial
distribution  continues  in  Section  C.5,  an  advanced  discussion  of  the
“tails” of the distribution.

C.1 Counting

Counting  theory  tries  to  answer  the  question  “How  many?”  without
actually enumerating all the choices. For example, you might ask, “How
many different n-bit numbers are there?” or “How many orderings of n
distinct  elements  are  there?”  This  section  reviews  the  elements  of
counting  theory.  Since  some  of  the  material  assumes  a  basic
understanding of sets, you might wish to start by reviewing the material
in Section B.1.

Rules of sum and product

We  can  sometimes  express  a  set  of  items  that  we  wish  to  count  as  a
union of disjoint sets or as a Cartesian product of sets.

The rule of sum says that the number of ways to choose one element
from one of two disjoint sets is the sum of the cardinalities of the sets.
That is, if A and B are two ﬁnite sets with no members in common, then
|A ∪ B| = |A| + |B|, which follows from equation (B.3) on page 1156. For
example,  if  each  position  on  a  car’s  license  plate  is  a  letter  or  a  digit,
then the number of possibilities for each position is 26 + 10 = 36, since
there are 26 choices if it is a letter and 10 choices if it is a digit.

The  rule  of  product  says  that  the  number  of  ways  to  choose  an
ordered pair is the number of ways to choose the ﬁrst element times the
number of ways to choose the second element. That is, if A and B are
two ﬁnite sets, then |A × B| = |A|·|B|, which is simply equation (B.4) on
page  1157.  For  example,  if  an  ice-cream  parlor  offers  28  ﬂavors  of  ice
cream  and  four  toppings,  the  number  of  possible  sundaes  with  one
scoop of ice cream and one topping is 28 · 4 = 112.

Strings

A string over a ﬁnite set S is a sequence of elements of S. For example,
there are eight binary strings of length 3:

000, 001, 010, 011, 100, 101, 110, 111.

(Here  we  use  the  shorthand  of  omitting  the  angle  brackets  when
denoting a sequence.) We sometimes call a string of length k a k-string.
A  substring  s′  of  a  string  s  is  an  ordered  sequence  of  consecutive
elements of s. A k-substring of a string is a substring of length k. For
example, 010 is a 3-substring of 01101001 (the 3-substring that begins in
position 4), but 111 is not a substring of 01101001.

We  can  view  a  k-string  over  a  set  S  as  an  element  of  the  Cartesian
product Sk of k-tuples, which means that there are |S|k strings of length
k.  For  example,  the  number  of  binary  k-strings  is  2k.  Intuitively,  to
construct  a  k-string  over  an  n-set,  there  are  n  ways  to  pick  the  ﬁrst
element; for each of these choices, there are n ways to pick the second

element;  and  so  forth  k  times.  This  construction  leads  to  the  k-fold

product

 as the number of k-strings.

Permutations

A permutation of a ﬁnite set S is an ordered sequence of all the elements
of S, with each element appearing exactly once. For example, if S = {a,
b, c}, then S has 6 permutations:

abc, acb, bac, bca, cab, cba.

(Again,  we  use  the  shorthand  of  omitting  the  angle  brackets  when
denoting a sequence.) There are n! permutations of a set of n elements,
since there are n ways to choose the ﬁrst element of the sequence, n − 1
ways for the second element, n − 2 ways for the third, and so on.

A  k-permutation  of  S  is  an  ordered  sequence  of  k  elements  of  S,
with  no  element  appearing  more  than  once  in  the  sequence.  (Thus,  an
ordinary permutation is an n-permutation of an n-set.) Here are the 2-
permutations of the set {a, b, c, d}:

ab, ac, ad, ba, bc, bd, ca, cb, cd, da, db, dc.

The number of k-permutations of an n-set is

since there are n ways to choose the ﬁrst element, n − 1 ways to choose
the second element, and so on, until k elements are chosen, with the last
element  chosen  from  the  remaining  n  −  k  +  1  elements.  For  the  above
example, with n = 4 and k = 2, the formula (C.1) evaluates to 4!/2! = 12,
matching the number of 2-permutations listed.

Combinations

A  k-combination  of  an  n-set  S  is  simply  a  k-subset  of  S.  For  example,
the 4-set {a, b, c, d} has six 2-combinations:

ab, ac, ad, bc, bd, cd.

(Here we use the shorthand of omitting the braces around each subset.)
To  construct  a  k-combination  of  an  n-set,  choose  k  distinct  (different)
elements  from  the  n-set.  The  order  of  selecting  the  elements  does  not
matter.

We  can  express  the  number  of  k-combinations  of  an  n-set  in  terms
of the number of k-permutations of an n-set. Every k-combination has
exactly  k!  permutations  of  its  elements,  each  of  which  is  a  distinct  k-
permutation of the n-set. Thus the number of k-combinations of an n-
set is the number of k-permutations divided by k!. From equation (C.1),
this quantity is

For  k  =  0,  this  formula  tells  us  that  the  number  of  ways  to  choose  0
elements from an n-set is 1 (not 0), since 0! = 1.

Binomial coefﬁcients

The  notation
combinations of an n-set. Equation (C.2) gives

  (read  “n  choose  k”)  denotes  the  number  of  k-

This formula is symmetric in k and n − k:

These  numbers  are  also  known  as  binomial  coefﬁcients,  due  to  their
appearance in the binomial theorem:

where  n  ∈  ℕ  and  x,  y  ∈  ℝ.  The  right-hand  side  of  equation  (C.4)  is
called the binomial expansion of the left-hand side. A special case of the
binomial theorem occurs when x = y = 1:

This  formula  corresponds  to  counting  the  2n  binary  n-strings  by  the
number  of  1s  they  contain:
  binary  n-strings  contain  exactly  k  1s,
since  there  are
  ways  to  choose  k  out  of  the  n  positions  in  which  to
place the 1s.

Many  identities  involve  binomial  coefﬁcients.  The  exercises  at  the

end of this section give you the opportunity to prove a few.

Binomial bounds

You sometimes need to bound the size of a binomial coefﬁcient. For 1 ≤
k ≤ n, we have the lower bound

Taking  advantage  of  the  inequality  k!  ≥  (k/e)k  derived  from  Stirling’s
approximation (3.25) on page 67, we obtain the upper bounds

For all integers k such that 0 ≤ k ≤ n, you can use induction (see Exercise
C.1-12) to prove the bound

where for convenience we assume that 00 = 1. For k = λn, where 0 ≤ λ ≤
1, we can rewrite this bound as

where

is the (binary) entropy function and where, for convenience, we assume
that 0 lg 0 = 0, so that H(0) = H(1) = 0.

Exercises

C.1-1
How  many  k-substrings  does  an  n-string  have?  (Consider  identical  k-
substrings  at  different  positions  to  be  different.)  How  many  substrings
does an n-string have in total?

C.1-2
An n-input, m-output boolean function is a function from {0, 1}n to {0,
1}m.  How  many  n-input,  1-output  boolean  functions  are  there?  How
many n-input, m-output boolean functions are there?

C.1-3

In  how  many  ways  can  n  professors  sit  around  a  circular  conference
table?  Consider  two  seatings  to  be  the  same  if  one  can  be  rotated  to
form the other.

C.1-4
In how many ways is it possible to choose three distinct numbers from
the set {1, 2, … , 99} so that their sum is even?

C.1-5
Prove the identity

for 0 < k ≤ n.

C.1-6
Prove the identity

for 0 ≤ k < n.

C.1-7
To  choose  k  objects  from  n,  you  can  make  one  of  the  objects
distinguished  and  consider  whether  the  distinguished  object  is  chosen.
Use this approach to prove that

C.1-8

Using the result of Exercise C.1-7, make a table for n = 0, 1, … , 6 and 0
≤ k ≤ n of the binomial coefﬁcients
 on the
 at the top,
,  and  so  forth.  Such  a  table  of  binomial
,
next  line,  then
coefﬁcients is called Pascal’s triangle.

,  and

 with

 and

C.1-9
Prove that

C.1-10

Show that for any integers n ≥ 0 and 0 ≤ k ≤ n, the expression
its maximum value when k = ⌊n/2⌋ or k = ⌈n/2⌉.

 achieves

★ C.1-11
Argue that for any integers n ≥ 0, j ≥ 0, k ≥ 0, and j + k ≤ n,

Provide  both  an  algebraic  proof  and  an  argument  based  on  a  method
for  choosing  j  +  k  items  out  of  n.  Give  an  example  in  which  equality
does not hold.

★ C.1-12
Use induction on all integers k such that 0 ≤ k ≤ n/2 to prove inequality
(C.7), and use equation (C.3) to extend it to all integers k such that 0 ≤ k
≤ n.

★ C.1-13
Use Stirling’s approximation to prove that

★ C.1-14
By  differentiating  the  entropy  function  H(λ),  show  that  it  achieves  its
maximum value at λ = 1/2. What is H(1/2)?

★ C.1-15
Show that for any integer n ≥ 0,

★ C.1-16
Inequality (C.5) provides a lower bound on the binomial coefﬁcient
For small values of k, a stronger bound holds. Prove that

.

