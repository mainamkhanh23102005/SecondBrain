3          Characterizing Running Times

The  order  of  growth  of  the  running  time  of  an  algorithm,  deﬁned  in
Chapter 2, gives a simple way to characterize the algorithm’s efﬁciency
and also allows us to compare it with alternative algorithms. Once the
input size n becomes large enough, merge sort, with its Θ(n lg n) worst-
case running time, beats insertion sort, whose worst-case running time is
Θ(n2). Although we can sometimes determine the exact running time of
an  algorithm,  as  we  did  for  insertion  sort  in  Chapter  2,  the  extra
precision  is  rarely  worth  the  effort  of  computing  it.  For  large  enough
inputs,  the  multiplicative  constants  and  lower-order  terms  of  an  exact
running time are dominated by the effects of the input size itself.

When we look at input sizes large enough to make relevant only the
order  of  growth  of  the  running  time,  we  are  studying  the  asymptotic
efﬁciency of algorithms. That is, we are concerned with how the running
time of an algorithm increases with the size of the input in the limit, as
the  size  of  the  input  increases  without  bound.  Usually,  an  algorithm
that  is  asymptotically  more  efﬁcient  is  the  best  choice  for  all  but  very
small inputs.

This  chapter  gives  several  standard  methods  for  simplifying  the
asymptotic analysis of algorithms. The next section presents informally
the  three  most  commonly  used  types  of  “asymptotic  notation,”  of
which we have already seen an example in Θ-notation. It also shows one
way  to  use  these  asymptotic  notations  to  reason  about  the  worst-case
running  time  of  insertion  sort.  Then  we  look  at  asymptotic  notations
more  formally  and  present  several  notational  conventions  used

throughout this book. The last section reviews the behavior of functions
that commonly arise when analyzing algorithms.

3.1      O-notation, Ω-notation, and Θ-notation

When  we  analyzed  the  worst-case  running  time  of  insertion  sort  in
Chapter 2, we started with the complicated expression

We then discarded the lower-order terms (c1 + c2 + c4 + c5/2 – c6/2 –
c7/2 + c8)n and c2 + c4 + c5 + c8, and we also ignored the coefﬁcient
c5/2 + c6/2 + c7/2 of n2. That left just the factor n2, which we put into
Θ-notation as Θ(n2). We use this style to characterize running times of
algorithms:  discard  the  lower-order  terms  and  the  coefﬁcient  of  the
leading term, and use a notation that focuses on the rate of growth of
the running time.

Θ-notation  is  not  the  only  such  “asymptotic  notation.”  In  this
section,  we’ll  see  other  forms  of  asymptotic  notation  as  well.  We  start
with  intuitive  looks  at  these  notations,  revisiting  insertion  sort  to  see
how  we  can  apply  them.  In  the  next  section,  we’ll  see  the  formal
deﬁnitions  of  our  asymptotic  notations,  along  with  conventions  for
using them.

Before  we  get  into  speciﬁcs,  bear  in  mind  that  the  asymptotic
notations  we’ll  see  are  designed  so  that  they  characterize  functions  in
general.  It  so  happens  that  the  functions  we  are  most  interested  in
denote  the  running  times  of  algorithms.  But  asymptotic  notation  can
apply  to  functions  that  characterize  some  other  aspect  of  algorithms
(the amount of space they use, for example), or even to functions that
have nothing whatsoever to do with algorithms.

O-notation

O-notation characterizes an upper bound on the asymptotic behavior of
a function. In other words, it says that a function grows no faster than a
certain rate, based on the highest-order term. Consider, for example, the
function 7n3 + 100n2 – 20n + 6. Its highest-order term is 7n3, and so we
say that this function’s rate of growth is n3. Because this function grows
no faster than n3, we can write that it is O(n3). You might be surprised
that we can also write that the function 7n3 + 100n2 – 20n + 6 is O(n4).
Why? Because the function grows more slowly than n4, we are correct in
saying that it grows no faster. As you might have guessed, this function
is  also  O(n5),  O(n6),  and  so  on.  More  generally,  it  is  O(nc)  for  any
constant c ≥ 3.

Ω-notation

Ω-notation characterizes a lower bound on the asymptotic behavior of a
function. In other words, it says that a function grows at least as fast as
a  certain  rate,  based  —  as  in  O-notation—on  the  highest-order  term.
Because  the  highest-order  term  in  the  function  7n3  +  100n2  –  20n  +  6
grows at least as fast as n3, this function is Ω(n3). This function is also
Ω(n2) and Ω(n). More generally, it is Ω(nc) for any constant c ≤ 3.

Θ-notation
Θ-notation characterizes a tight bound on the asymptotic behavior of a
function. It says that a function grows precisely at a certain rate, based
—once again—on the highest-order term. Put another way, Θ-notation
characterizes  the  rate  of  growth  of  the  function  to  within  a  constant
factor  from  above  and  to  within  a  constant  factor  from  below.  These
two constant factors need not be equal.

If you can show that a function is both O(f (n)) and Ω(f (n)) for some
function  f  (n),  then  you  have  shown  that  the  function  is  Θ(f  (n)).  (The
next  section  states  this  fact  as  a  theorem.)  For  example,  since  the
function 7n3 + 100n2 – 20n + 6 is both O(n3) and Ω(n3), it is also Θ(n3).

Example: Insertion sort

Let’s  revisit  insertion  sort  and  see  how  to  work  with  asymptotic
notation  to  characterize  its  Θ(n2)  worst-case  running  time  without
evaluating  summations  as  we  did
is  the
INSERTION-SORT procedure once again:

in  Chapter  2.  Here

INSERTION-SORT(A, n)
1 for i = 2 to n
key = A[i]
2
// Insert A[i] into the sorted subarray A[1 : i – 1].
j = i – 1
while j > 0 and A[j] > key

5

3

4

6

7

8

A[j + 1] = A[j]
j = j – 1
A[j + 1] = key

What  can  we  observe  about  how  the  pseudocode  operates?  The
procedure has nested loops. The outer loop is a for loop that runs n – 1
times,  regardless  of  the  values  being  sorted.  The  inner  loop  is  a  while
loop, but the number of iterations it makes depends on the values being
sorted.  The  loop  variable  j  starts  at  i  –  1  and  decreases  by  1  in  each
iteration until either it reaches 0 or A[j] ≤ key. For a given value of i, the
while  loop  might  iterate  0  times,  i  –  1  times,  or  anywhere  in  between.
The body of the while loop (lines 6–7) takes constant time per iteration
of the while loop.

Figure  3.1  The  Ω(n2)  lower  bound  for  insertion  sort.  If  the  ﬁrst  n/3  positions  contain  the  n/3
largest  values,  each  of  these  values  must  move  through  each  of  the  middle  n/3  positions,  one
position at a time, to end up somewhere in the last n/3 positions. Since each of n/3 values moves
through at least each of n/3 positions, the time taken in this case is at least proportional to (n/3)
(n/3) = n2/9, or Ω(n2).

These observations sufﬁce to deduce an O(n2) running time for any
case  of  INSERTION-SORT,  giving  us  a  blanket  statement  that  covers
all  inputs.  The  running  time  is  dominated  by  the  inner  loop.  Because
each  of  the  n  –  1  iterations  of  the  outer  loop  causes  the  inner  loop  to
iterate at most i – 1 times, and because i is at most n, the total number
of iterations of the inner loop is at most (n – 1)(n – 1), which is less than
n2. Since each iteration of the inner loop takes constant time, the total
time spent in the inner loop is at most a constant times n2, or O(n2).

With  a  little  creativity,  we  can  also  see  that  the  worst-case  running
time  of  INSERTION-SORT  is  Ω(n2).  By  saying  that  the  worst-case
running time of an algorithm is Ω(n2), we mean that for every input size
n above a certain threshold, there is at least one input of size n for which
the  algorithm  takes  at  least  cn2  time,  for  some  positive  constant  c.  It
does not necessarily mean that the algorithm takes at least cn2 time for
all inputs.

Let’s  now  see  why  the  worst-case  running  time  of  INSERTION-
SORT is Ω(n2). For a value to end up to the right of where it started, it
must  have  been  moved  in  line  6.  In  fact,  for  a  value  to  end  up  k
positions  to  the  right  of  where  it  started,  line  6  must  have  executed  k
times. As Figure 3.1 shows, let’s assume that n is a multiple of 3 so that
we can divide the array A into groups of n/3 positions. Suppose that in

the input to INSERTION-SORT, the n/3 largest values occupy the ﬁrst
n/3  array  positions  A[1  :  n/3].  (It  does  not  matter  what  relative  order
they have within the ﬁrst n/3 positions.) Once the array has been sorted,
each  of  these  n/3  values  ends  up  somewhere  in  the  last  n/3  positions
A[2n/3 + 1 : n]. For that to happen, each of these n/3 values must pass
through each of the middle n/3 positions A[n/3 + 1 : 2n/3]. Each of these
n/3  values  passes  through  these  middle  n/3  positions  one  position  at  a
time, by at least n/3 executions of line 6. Because at least n/3 values have
to pass through at least n/3 positions, the time taken by INSERTION-
SORT  in  the  worst  case  is  at  least  proportional  to  (n/3)(n/3)  =  n2/9,
which is Ω(n2).

Because we have shown that INSERTION-SORT runs in O(n2) time
in all cases and that there is an input that makes it take Ω(n2) time, we
can  conclude  that  the  worst-case  running  time  of  INSERTION-SORT
is  Θ(n2).  It  does  not  matter  that  the  constant  factors  for  upper  and
lower  bounds  might  differ.  What  matters  is  that  we  have  characterized
the  worst-case  running  time  to  within  constant  factors  (discounting
lower-order  terms).  This  argument  does  not  show  that  INSERTION-
SORT runs in Θ(n2) time in all cases. Indeed, we saw in Chapter 2 that
the best-case running time is Θ(n).

Exercises

3.1-1
Modify  the  lower-bound  argument  for  insertion  sort  to  handle  input
sizes that are not necessarily a multiple of 3.

3.1-2
Using reasoning similar to what we used for insertion sort, analyze the
running time of the selection sort algorithm from Exercise 2.2-2.

3.1-3
Suppose  that  α  is  a  fraction  in  the  range  0  <  α  <  1.  Show  how  to
generalize  the  lower-bound  argument  for  insertion  sort  to  consider  an
input in which the αn largest values start in the ﬁrst αn positions. What

additional  restriction  do  you  need  to  put  on  α?  What  value  of  α
maximizes  the  number  of  times  that  the  αn  largest  values  must  pass
through each of the middle (1 – 2α)n array positions?

3.2      Asymptotic notation: formal deﬁnitions

Having seen asymptotic notation informally, let’s get more formal. The
notations  we  use  to  describe  the  asymptotic  running  time  of  an
algorithm are deﬁned in terms of functions whose domains are typically
the  set  N  of  natural  numbers  or  the  set  R  of  real  numbers.  Such
notations  are  convenient  for  describing  a  running-time  function  T  (n).
This section deﬁnes the basic asymptotic notations and also introduces
some common “proper” notational abuses.

Figure 3.2 Graphic examples of the O, Ω, and Θ notations. In each part, the value of n0 shown
is the minimum possible value, but any greater value also works. (a) O-notation gives an upper
bound for a function to within a constant factor. We write f (n) = O(g(n)) if there are positive
constants n0 and c such that at and to the right of n0, the value of f (n) always lies on or below
cg(n). (b) Ω-notation gives a lower bound for a function to within a constant factor. We write f
(n) = Ω(g(n)) if there are positive constants n0 and c such that at and to the right of n0, the value
of  f  (n)  always  lies  on  or  above  cg(n).  (c)  Θ-notation  bounds  a  function  to  within  constant
factors. We write f (n) = Θ(g(n)) if there exist positive constants n0, c1, and c2 such that at and
to the right of n0, the value of f (n) always lies between c1g(n) and c2g(n) inclusive.

O-notation

As  we  saw  in  Section  3.1,  O-notation  describes  an  asymptotic  upper
bound.  We  use  O-notation  to  give  an  upper  bound  on  a  function,  to
within a constant factor.

Here  is  the  formal  deﬁnition  of  O-notation.  For  a  given  function
g(n),  we  denote  by  O(g(n))  (pronounced  “big-oh  of  g  of  n”  or
sometimes just “oh of g of n”) the set of functions

O(g(n))  =
{f (n)

 : there  exist  positive  constants  c  and  n0  such
that 0 ≤ f (n) ≤ cg(n) for all n ≥ n0}.1

A  function  f  (n)  belongs  to  the  set  O(g(n))  if  there  exists  a  positive
constant  c  such  that  f  (n)  ≤  cg(n)  for  sufﬁciently  large  n.  Figure  3.2(a)
shows  the  intuition  behind  O-notation.  For  all  values  n  at  and  to  the
right of n0, the value of the function f (n) is on or below cg(n).

The deﬁnition of O(g(n)) requires that every function f (n) in the set
O(g(n))  be  asymptotically  nonnegative:  f  (n)  must  be  nonnegative
whenever  n  is  sufﬁciently  large.  (An  asymptotically  positive  function  is
one  that  is  positive  for  all  sufﬁciently  large  n.)  Consequently,  the
function  g(n)  itself  must  be  asymptotically  nonnegative,  or  else  the  set
O(g(n))  is  empty.  We  therefore  assume  that  every  function  used  within
O-notation  is  asymptotically  nonnegative.  This  assumption  holds  for
the other asymptotic notations deﬁned in this chapter as well.

You  might  be  surprised  that  we  deﬁne  O-notation  in  terms  of  sets.
Indeed,  you  might  expect  that  we  would  write  “f  (n)  ∈  O(g(n))”  to
indicate that f (n) belongs to the set O(g(n)). Instead, we usually write “f
(n)  =  O(g(n))”  and  say  “f  (n)  is  big-oh  of  g(n)”  to  express  the  same
notion. Although it may seem confusing at ﬁrst to abuse equality in this
way, we’ll see later in this section that doing so has its advantages.

Let’s explore an example of how to use the formal deﬁnition of O-
notation  to  justify  our  practice  of  discarding  lower-order  terms  and
ignoring the constant coefﬁcient of the highest-order term. We’ll show
that 4n2 + 100n + 500 = O(n2), even though the lower-order terms have
much larger coefﬁcients than the leading term. We need to ﬁnd positive
constants  c  and  n0  such  that  4n2  +  100n  +  500  ≤  cn2  for  all  n  ≥  n0.

Dividing both sides by n2 gives 4 + 100/n + 500/n2 ≤ c. This inequality is
satisﬁed for many choices of c and n0. For example, if we choose n0 = 1,
then this inequality holds for c = 604. If we choose n0 = 10, then c = 19
works, and choosing n0 = 100 allows us to use c = 5.05.

We can also use the formal deﬁnition of O-notation to show that the
function n3 – 100n2 does not belong to the set O(n2), even though the
coefﬁcient  of  n2  is  a  large  negative  number.  If  we  had  n3  –  100n2  =
O(n2),  then  there  would  be  positive  constants  c  and  n0  such  that  n3  –
100n2 ≤ cn2 for all n ≥ n0. Again, we divide both sides by n2, giving n –
100  ≤  c.  Regardless  of  what  value  we  choose  for  the  constant  c,  this
inequality does not hold for any value of n > c + 100.

Ω-notation

Just as O-notation provides an asymptotic upper bound on a function,
Ω-notation  provides  an  asymptotic  lower  bound.  For  a  given  function
g(n),  we  denote  by  Ω(g(n))  (pronounced  “big-omega  of  g  of  n”  or
sometimes just “omega of g of n”) the set of functions

Ω(g(n))  =
{f (n)

 : there  exist  positive  constants  c  and  n0  such

that 0 ≤ cg(n) ≤ f (n) for all n ≥ n0}.

Figure 3.2(b) shows the intuition behind Ω-notation. For all values n at
or to the right of n0, the value of f (n) is on or above cg(n).

We’ve already shown that 4n2 + 100n + 500 = O(n2). Now let’s show
that 4n2 + 100n + 500 = Ω(n2). We need to ﬁnd positive constants c and
n0 such that 4n2 + 100n + 500 ≥ cn2 for all n ≥ n0. As before, we divide
both  sides  by  n2,  giving  4  +  100/n  +  500/n2  ≥  c.  This  inequality  holds
when n0 is any positive integer and c = 4.

What if we had subtracted the lower-order terms from the 4n2 term
instead  of  adding  them?  What  if  we  had  a  small  coefﬁcient  for  the  n2

term?  The  function  would  still  be  Ω(n2).  For  example,  let’s  show  that
n2/100 – 100n – 500 = Ω(n2). Dividing by n2 gives 1/100 – 100/n – 500/n2
≥  c.  We  can  choose  any  value  for  n0  that  is  at  least  10,005  and  ﬁnd  a
positive value for c. For example, when n0 = 10,005, we can choose c =
2.49 × 10–9. Yes, that’s a tiny value for c, but it is positive. If we select a
larger value for n0, we can also increase c. For example, if n0 = 100,000,
then we can choose c = 0.0089. The higher the value of n0, the closer to
the coefﬁcient 1/100 we can choose c.

Θ-notation
We use Θ-notation for asymptotically tight bounds. For a given function
g(n), we denote by Θ(g(n)) (“theta of g of n”) the set of functions

Θ(g(n))  =
{f (n)

 : there  exist  positive  constants  c1,  c2,  and  n0
such that 0 ≤ c1g(n) ≤ f (n) ≤ c2g(n) for all n ≥
n0}.

Figure 3.2(c) shows the intuition behind Θ-notation. For all values of n
at and to the right of n0, the value of f (n) lies at or above c1g(n) and at
or below c2g(n). In other words, for all n ≥ n0, the function f (n) is equal
to g(n) to within constant factors.

The  deﬁnitions  of  O-,  Ω-,  and  Θ-notations  lead  to  the  following

theorem, whose proof we leave as Exercise 3.2-4.

Theorem 3.1
For any two functions f (n) and g(n), we have f (n) = Θ(g(n)) if and only
if f (n) = O(g(n)) and f (n) = Ω(g(n)).

▪

We  typically  apply  Theorem  3.1  to  prove  asymptotically  tight  bounds
from asymptotic upper and lower bounds.

Asymptotic notation and running times

When  you  use  asymptotic  notation  to  characterize  an  algorithm’s
running  time,  make  sure  that  the  asymptotic  notation  you  use  is  as
precise as possible without overstating which running time it applies to.
Here  are  some  examples  of  using  asymptotic  notation  properly  and
improperly to characterize running times.

Let’s  start  with  insertion  sort.  We  can  correctly  say  that  insertion
sort’s worst-case running time is O(n2), Ω(n2), and—due to Theorem 3.1
—Θ(n2). Although all three ways to characterize the worst-case running
times  are  correct,  the  Θ(n2)  bound  is  the  most  precise  and  hence  the
most preferred. We can also correctly say that insertion sort’s best-case
running  time  is  O(n),  Ω(n),  and  Θ(n),  again  with  Θ(n)  the  most  precise
and therefore the most preferred.

Here is what we cannot correctly say: insertion sort’s running time is
Θ(n2). That is an overstatement because by omitting “worst-case” from
the statement, we’re left with a blanket statement covering all cases. The
error  here  is  that  insertion  sort  does  not  run  in  Θ(n2)  time  in  all  cases
since,  as  we’ve  seen,  it  runs  in  Θ(n)  time  in  the  best  case.  We  can
correctly  say  that  insertion  sort’s  running  time  is  O(n2),  however,
because in all cases, its running time grows no faster than n2. When we
say  O(n2)  instead  of  Θ(n2),  there  is  no  problem  in  having  cases  whose
running time grows more slowly than n2. Likewise, we cannot correctly
say  that  insertion  sort’s  running  time  is  Θ(n),  but  we  can  say  that  its
running time is Ω(n).

How about merge sort? Since merge sort runs in Θ(n lg n) time in all
cases,  we  can  just  say  that  its  running  time  is  Θ(n  lg  n)  without
specifying worst-case, best-case, or any other case.

People  occasionally  conﬂate  O-notation  with  Θ-notation  by
mistakenly using O-notation to indicate an asymptotically tight bound.
They  say  things  like  “an  O(n  lg  n)-time  algorithm  runs  faster  than  an
O(n2)-time  algorithm.”  Maybe  it  does,  maybe  it  doesn’t.  Since  O-
notation denotes only an asymptotic upper bound, that so-called O(n2)-
time algorithm might actually run in Θ(n) time. You should be careful to

choose the appropriate asymptotic notation. If you want to indicate an
asymptotically tight bound, use Θ-notation.

We  typically  use  asymptotic  notation  to  provide  the  simplest  and
most  precise  bounds  possible.  For  example,  if  an  algorithm  has  a
running  time  of  3n2  +  20n  in  all  cases,  we  use  asymptotic  notation  to
write  that  its  running  time  is  Θ(n2).  Strictly  speaking,  we  are  also
correct  in  writing  that  the  running  time  is  O(n3)  or  Θ(3n2  +  20n).
Neither  of  these  expressions  is  as  useful  as  writing  Θ(n2)  in  this  case,
however:  O(n3)  is  less  precise  than  Θ(n2)  if  the  running  time  is  3n2  +
20n, and Θ(3n2 + 20n) introduces complexity that obscures the order of
growth. By writing the simplest and most precise bound, such as Θ(n2),
we  can  categorize  and  compare  different  algorithms.  Throughout  the
book,  you  will  see  asymptotic  running  times  that  are  almost  always
based on polynomials and logarithms: functions such as n, n lg2 n, n2 lg
n, or n1/2. You will also see some other functions, such as exponentials,
lg lg n, and lg*n (see Section 3.3). It is usually fairly easy to compare the
rates of growth of these functions. Problem 3-3 gives you good practice.

Asymptotic notation in equations and inequalities

Although  we  formally  deﬁne  asymptotic  notation  in  terms  of  sets,  we
use  the  equal  sign  (=)  instead  of  the  set  membership  sign  (∈)  within
formulas.  For  example,  we  wrote  that  4n2  +  100n  +  500  =  O(n2).  We
might also write 2n2 + 3n + 1 = 2n2 + Θ(n). How do we interpret such
formulas?

When  the  asymptotic  notation  stands  alone  (that  is,  not  within  a
larger formula) on the right-hand side of an equation (or inequality), as
in 4n2 + 100n + 500 = O(n2), the equal sign means set membership: 4n2
+ 100n + 500 ∈ O(n2). In general, however, when asymptotic notation
appears  in  a  formula,  we  interpret  it  as  standing  for  some  anonymous
function that we do not care to name. For example, the formula 2n2 +

3n + 1 = 2n2 + Θ(n) means that 2n2 + 3n + 1 = 2n2 + f (n), where f (n)
∈ Θ(n). In this case, we let f (n) = 3n + 1, which indeed belongs to Θ(n).
Using  asymptotic  notation  in  this  manner  can  help  eliminate
inessential detail and clutter in an equation. For example, in Chapter 2
we  expressed  the  worst-case  running  time  of  merge  sort  as  the
recurrence

T (n) = 2T (n/2) + Θ(n).

If we are interested only in the asymptotic behavior of T (n), there is no
point in specifying all the lower-order terms exactly, because they are all
understood  to  be  included  in  the  anonymous  function  denoted  by  the
term Θ(n).

The number of anonymous functions in an expression is understood
to  be  equal  to  the  number  of  times  the  asymptotic  notation  appears.
For example, in the expression

there  is  only  a  single  anonymous  function  (a  function  of  i).  This
expression  is  thus  not  the  same  as  O(1)  +  O(2)  +  ⋯  +  O(n),  which
doesn’t really have a clean interpretation.

In some cases, asymptotic notation appears on the left-hand side of

an equation, as in
2n2 + Θ(n) = Θ(n2).
Interpret  such  equations  using  the  following  rule:  No  matter  how  the
anonymous  functions  are  chosen  on  the  left  of  the  equal  sign,  there  is  a
way to choose the anonymous functions on the right of the equal sign to
make the equation valid. Thus, our example means that for any function
f (n) ∈ Θ(n), there is some function g(n) ∈ Θ(n2) such that 2n2 + f (n) =
g(n)  for  all  n.  In  other  words,  the  right-hand  side  of  an  equation
provides a coarser level of detail than the left-hand side.

We can chain together a number of such relationships, as in

2n2 + 3n + 1 = 2n2 + Θ(n)

 = Θ(n2).

By the rules above, interpret each equation separately. The ﬁrst equation
says that there is some function f (n) ∈ Θ(n) such that 2n2 + 3n + 1 =
2n2 + f (n) for all n. The second equation says that for any function g(n)
∈ Θ(n) (such as the f (n) just mentioned), there is some function h(n) ∈
Θ(n2)  such  that  2n2  +  g(n)  =  h(n)  for  all  n.  This  interpretation  implies
that  2n2  +  3n  +  1  =  Θ(n2),  which  is  what  the  chaining  of  equations
intuitively says.

Proper abuses of asymptotic notation

Besides  the  abuse  of  equality  to  mean  set  membership,  which  we  now
see  has  a  precise  mathematical  interpretation,  another  abuse  of
asymptotic notation occurs when the variable tending toward ∞ must be
inferred  from  context.  For  example,  when  we  say  O(g(n)),  we  can
assume that we’re interested in the growth of g(n) as n grows, and if we
say O(g(m)) we’re talking about the growth of g(m) as m grows. The free
variable in the expression indicates what variable is going to ∞.

The  most  common  situation  requiring  contextual  knowledge  of
which  variable  tends  to  ∞  occurs  when  the  function  inside  the
asymptotic notation is a constant, as in the expression O(1). We cannot
infer  from  the  expression  which  variable  is  going  to  ∞,  because  no
variable appears there. The context must disambiguate. For example, if
the equation using asymptotic notation is f (n) = O(1), it’s apparent that
the  variable  we’re  interested  in  is  n.  Knowing  from  context  that  the
variable of interest is n, however, allows us to make perfect sense of the
expression by using the formal deﬁnition of O-notation: the expression f
(n)  =  O(1)  means  that  the  function  f  (n)  is  bounded  from  above  by  a
constant  as  n  goes  to  ∞.  Technically,  it  might  be  less  ambiguous  if  we
explicitly indicated the variable tending to ∞ in the asymptotic notation
itself, but that would clutter the notation. Instead, we simply ensure that
the context makes it clear which variable (or variables) tend to ∞.

When  the  function  inside  the  asymptotic  notation  is  bounded  by  a
positive  constant,  as  in  T  (n)  =  O(1),  we  often  abuse  asymptotic
notation  in  yet  another  way,  especially  when  stating  recurrences.  We
may  write  something  like  T  (n)  =  O(1)  for  n  <  3.  According  to  the
formal deﬁnition of O-notation, this statement is meaningless, because
the  deﬁnition  only  says  that  T  (n)  is  bounded  above  by  a  positive
constant c for n ≥ n0 for some n0 > 0. The value of T (n) for n < n0 need
not  be  so  bounded.  Thus,  in  the  example  T  (n)  =  O(1)  for  n  <  3,  we
cannot  infer  any  constraint  on  T  (n)  when  n  <  3,  because  it  might  be
that n0 > 3.

What is conventionally meant when we say T (n) = O(1) for n < 3 is
that there exists a positive constant c such that T (n) ≤ c for n < 3. This
convention  saves  us  the  trouble  of  naming  the  bounding  constant,
allowing  it  to  remain  anonymous  while  we  focus  on  more  important
variables in an analysis. Similar abuses occur with the other asymptotic
notations.  For  example,  T  (n)  =  Θ(1)  for  n  <  3  means  that  T  (n)  is
bounded above and below by positive constants when n < 3.

Occasionally,  the  function  describing  an  algorithm’s  running  time
may  not  be  deﬁned  for  certain  input  sizes,  for  example,  when  an
algorithm assumes that the input size is an exact power of 2. We still use
asymptotic  notation  to  describe  the  growth  of  the  running  time,
understanding  that  any  constraints  apply  only  when  the  function  is
deﬁned.  For  example,  suppose  that  f  (n)  is  deﬁned  only  on  a  subset  of
the  natural  or  nonnegative  real  numbers.  Then  f  (n)  =  O(g(n))  means
that the bound 0 ≤ T (n) ≤ cg(n) in the deﬁnition of O-notation holds for
all n ≥ n0 over the domain of f (n), that is, where f (n) is deﬁned. This
abuse is rarely pointed out, since what is meant is generally clear from
context.

In  mathematics,  it’s  okay  —  and  often  desirable  —  to  abuse  a
notation, as long as we don’t misuse it. If we understand precisely what
is  meant  by  the  abuse  and  don’t  draw  incorrect  conclusions,  it  can
simplify  our  mathematical  language,  contribute  to  our  higher-level
understanding, and help us focus on what really matters.

o-notation

The  asymptotic  upper  bound  provided  by  O-notation  may  or  may  not
be asymptotically tight. The bound 2n2 = O(n2) is asymptotically tight,
but the bound 2n = O(n2) is not. We use o-notation to denote an upper
bound  that  is  not  asymptotically  tight.  We  formally  deﬁne  o(g(n))
(“little-oh of g of n”) as the set

o(g(n))  =
{f (n)

 : for any positive constant c > 0, there exists a constant n0 >

0 such that 0 ≤ f (n) < cg(n) for all n ≥ n0}.

For example, 2n = o(n2), but 2n2 ≠ o(n2).

The deﬁnitions of O-notation and o-notation are similar. The main
difference is that in f (n) = O(g(n)), the bound 0 ≤ f (n) ≤ cg(n) holds for
some constant c > 0, but in f (n) = o(g(n)), the bound 0 ≤ f (n) < cg(n)
holds for all constants c > 0. Intuitively, in o-notation, the function f (n)
becomes insigniﬁcant relative to g(n) as n gets large:

Some  authors  use  this  limit  as  a  deﬁnition  of  the  o-notation,  but  the
deﬁnition  in  this  book  also  restricts  the  anonymous  functions  to  be
asymptotically nonnegative.

ω-notation
By analogy, ω-notation is to Ω-notation as o-notation is to O-notation.
We use  ω-notation to denote a lower bound that is not asymptotically
tight. One way to deﬁne it is by

f (n) ∈ ω(g(n)) if and only if g(n) ∈ o(f (n)).
Formally, however, we deﬁne ω(g(n)) (“little-omega of g of n”) as the set

ω(g(n))  =
{f (n)

 : for any positive constant c > 0, there exists a constant n0 >

0 such that 0 ≤ cg(n) < f (n) for all n ≥ n0}.

Where the deﬁnition of o-notation says that f (n) < cg(n), the deﬁnition
of ω-notation says the opposite: that cg(n) < f (n). For examples of ω-

notation,  we  have  n2/2  =  ω(n),  but  n2/2  ≠  ω(n2).  The  relation  f  (n)  =
ω(g(n)) implies that

if the limit exists. That is, f (n) becomes arbitrarily large relative to g(n)
as n gets large.

Comparing functions

Many of the relational properties of real numbers apply to asymptotic
comparisons  as  well.  For  the  following,  assume  that  f  (n)  and  g(n)  are
asymptotically positive.

Transitivity:

(n)  =

f
Θ(g(n))
f
O(g(n))
f
Ω(g(n))
f
o(g(n))

(n)  =

(n)  =

(n)  =

(n)  =

f
ω(g(n))

Reﬂexivity:

and g(n)

Θ(h(n))

and g(n)

O(h(n))

and g(n)

Ω(h(n))

and g(n)

o(h(n))

and g(n)

ω(h(n))

=

=

=

=

=

imply f

imply f

imply f

imply f

(n)
Θ(h(n)),
(n)
O(h(n)),
(n)
Ω(h(n)),
(n)
o(h(n)),

imply f

(n)
ω(h(n)).

=

=

=

=

=

f (n) = Θ(f (n)),
f (n) = O(f (n)),
f (n) = Ω(f (n)).

Symmetry:

f (n) = Θ(g(n)) if and only if g(n) = Θ(f (n)).

Transpose symmetry:

=

(n)

f
O(g(n))
f (n) = o(g(n)) if  and  only

if  and  only
if

if

g(n)  =  Ω(f
(n)),
g(n)  =  ω(f
(n)).

Because these properties hold for asymptotic notations, we can draw
an analogy between the asymptotic comparison of two functions f and
g and the comparison of two real numbers a and b:

f (n) = O(g(n)) is like a ≤ b,

f (n) = Ω(g(n)) is like a ≥ b,
f (n) = Θ(g(n)) is like a = b,
f (n) = o(g(n)) is like a < b,
f (n) = ω(g(n)) is like a > b.

We  say  that  f  (n)  is  asymptotically  smaller  than  g(n)  if  f  (n)  =  o(g(n)),
and f (n) is asymptotically larger than g(n) if f (n) = ω(g(n)).

One  property  of  real  numbers,  however,  does  not  carry  over  to

asymptotic notation:

Trichotomy:  For  any  two  real  numbers  a  and  b,  exactly  one  of  the

following must hold: a < b, a = b, or a > b.

Although any two real numbers can be compared, not all functions are
asymptotically comparable. That is, for two functions f (n) and  g(n), it
may be the case that neither f (n) = O(g(n)) nor f (n) = Ω(g(n)) holds. For
example,  we  cannot  compare  the  functions  n  and  n1  +  sin  n  using
asymptotic  notation,  since  the  value  of  the  exponent  in  n1  +  sin  n
oscillates between 0 and 2, taking on all values in between.

Exercises

3.2-1
Let  f  (n)  and  g(n)  be  asymptotically  nonnegative  functions.  Using  the
basic deﬁnition of Θ-notation, prove that max {f (n), g(n)} = Θ(f (n) +

g(n)).

3.2-2
Explain why the statement, “The running time of algorithm A is at least
O(n2),” is meaningless.

3.2-3
Is 2n + 1 = O(2n)? Is 22n = O(2n)?

3.2-4
Prove Theorem 3.1.

3.2-5
Prove that the running time of an algorithm is Θ(g(n)) if and only if its
worst-case  running  time  is  O(g(n))  and  its  best-case  running  time  is
Ω(g(n)).

3.2-6
Prove that o(g(n)) ∩ ω(g(n)) is the empty set.

3.2-7
We can extend our notation to the case of two parameters n and m that
can  go  to  ∞  independently  at  different  rates.  For  a  given  function  g(n,
m), we denote by O(g(n, m)) the set of functions

O(g(n,  m))
= {f (n, m)

 : there exist positive constants c, n0, and m0
such that 0 ≤ f (n, m) ≤ cg(n, m) for all n ≥
n0 or m ≥ m0}.

Give corresponding deﬁnitions for Ω(g(n, m)) and Θ(g(n, m)).

3.3      Standard notations and common functions

This  section  reviews  some  standard  mathematical  functions  and
notations and explores the relationships among them. It also illustrates
the use of the asymptotic notations.

Monotonicity

A function f (n) is monotonically increasing if m ≤ n implies f (m) ≤ f (n).
Similarly, it is monotonically decreasing if m ≤ n implies f (m) ≥ f (n). A
function  f  (n)  is  strictly  increasing  if  m  <  n  implies  f  (m)  <  f  (n)  and
strictly decreasing if m < n implies f (m) > f (n).

Floors and ceilings

For any real number x, we denote the greatest integer less than or equal
to x by ⌊x⌋ (read “the ﬂoor of x”) and the least integer greater than or
equal  to  x  by  ⌈x⌉  (read  “the  ceiling  of  x”).  The  ﬂoor  function  is
monotonically increasing, as is the ceiling function.

Floors and ceilings obey the following properties. For any integer n,

we have

For all real x, we have

We also have

or equivalently,

For any real number x ≥ 0 and integers a, b > 0, we have

For any integer n and real number x, we have

Modular arithmetic

For  any  integer  a  and  any  positive  integer  n,  the  value  a  mod  n  is  the
remainder (or residue) of the quotient a/n:

It follows that

even when a is negative.

Given  a  well-deﬁned  notion  of  the  remainder  of  one  integer  when
divided  by  another,  it  is  convenient  to  provide  special  notation  to
indicate equality of remainders. If (a mod n) = (b mod n), we write a =
b (mod n) and say that a is equivalent to b, modulo n. In other words, a
=  b  (mod  n)  if  a  and  b  have  the  same  remainder  when  divided  by  n.
Equivalently,  a  =  b  (mod  n)  if  and  only  if  n  is  a  divisor  of  b  –  a.  We
write a ≠ b (mod n) if a is not equivalent to b, modulo n.

Polynomials

Given  a  nonnegative  integer  d,  a  polynomial  in  n  of  degree  d  is  a
function p(n) of the form

where the constants a0, a1, … , ad are the coefﬁcients of the polynomial
and ad ≠ 0. A polynomial is asymptotically positive if and only if ad >
0. For an asymptotically positive polynomial p(n) of degree d, we have
p(n)  =  Θ(nd).  For  any  real  constant  a  ≥  0,  the  function  na  is
monotonically increasing, and for any real constant a ≤ 0, the function

na  is  monotonically  decreasing.  We  say  that  a  function  f  (n)  is
polynomially bounded if f (n) = O(nk) for some constant k.

Exponentials

For all real a > 0, m, and n, we have the following identities:

a0 = 1,
a1 = a,
a–1 = 1/a,
(am)n = amn,
(am)n = (an)m,
aman = am+n.

For  all  n  and  a  ≥  1,  the  function  an  is  monotonically  increasing  in  n.
When convenient, we assume that 00 = 1.

We  can  relate  the  rates  of  growth  of  polynomials  and  exponentials

by the following fact. For all real constants a > 1 and b, we have

from which we can conclude that

Thus, any exponential function with a base strictly greater than 1 grows
faster than any polynomial function.

Using  e  to  denote  2.71828  …,  the  base  of  the  natural-logarithm

function, we have for all real x,

where “!” denotes the factorial function deﬁned later in this section. For
all real x, we have the inequality

where  equality  holds  only  when  x  =  0.  When  |x|  ≤  1,  we  have  the
approximation

When x → 0, the approximation of ex by 1 + x is quite good:
ex = 1 + x + Θ(x2).
(In  this  equation,  the  asymptotic  notation  is  used  to  describe  the
limiting behavior as x → 0 rather than as x → ∞.) We have for all x,

Logarithms

We use the following notations:

lg n = log2 n (binary logarithm),
ln n = loge n (natural logarithm),
lgk n = (lg n)k (exponentiation),
lg lg n = lg(lg n) (composition).

We  adopt  the  following  notational  convention:  in  the  absence  of
parentheses,  a  logarithm  function  applies  only  to  the  next  term  in  the
formula, so that lg n + 1 means (lg n) + 1 and not lg(n + 1).

For  any  constant  b  >  1,  the  function  logb  n  is  undeﬁned  if  n  ≤  0,
strictly increasing if n > 0, negative if 0 < n < 1, positive if n > 1, and 0
if n = 1. For all real a > 0, b > 0, c > 0, and n, we have

where, in each equation above, logarithm bases are not 1.

By  equation  (3.19),  changing  the  base  of  a  logarithm  from  one
constant  to  another  changes  the  value  of  the  logarithm  by  only  a
constant factor. Consequently, we often use the notation “lg n” when we
don’t  care  about  constant  factors,  such  as  in  O-notation.  Computer
scientists  ﬁnd  2  to  be  the  most  natural  base  for  logarithms  because  so
many  algorithms  and  data  structures  involve  splitting  a  problem  into
two parts.

There is a simple series expansion for ln(1 + x) when |x| < 1:

We also have the following inequalities for x > – 1:

where equality holds only for x = 0.

We say that a function f (n) is polylogarithmically bounded if f (n) =
O(lgk n) for some constant k. We can relate the growth of polynomials
and  polylogarithms  by  substituting  lg  n  for  n  and  2a  for  a  in  equation
(3.13). For all real constants a > 0 and b, we have

Thus,  any  positive  polynomial  function  grows  faster  than  any
polylogarithmic function.

Factorials

The notation n! (read “n factorial”) is deﬁned for integers n ≥ 0 as

Thus, n! = 1 · 2 · 3 ⋯ n.

A weak upper bound on the factorial function is n! ≤ nn, since each
of  the  n  terms  in  the  factorial  product  is  at  most  n.  Stirling’s
approximation,

where  e  is  the  base  of  the  natural  logarithm,  gives  us  a  tighter  upper
bound, and a lower bound as well. Exercise 3.3-4 asks you to prove the
three facts

where Stirling’s approximation is helpful in proving equation (3.28). The
following equation also holds for all n ≥ 1:

where

Functional iteration

We  use  the  notation  f(i)  (n)  to  denote  the  function  f  (n)  iteratively
applied i times to an initial value of n. Formally, let f (n) be a function
over the reals. For nonnegative integers i, we recursively deﬁne

For example, if f (n) = 2n, then f(i) (n) = 2in.

The iterated logarithm function

We  use  the  notation  lg*n  (read  “log  star  of  n”)  to  denote  the  iterated
logarithm, deﬁned as follows. Let lg(i) n be as deﬁned above, with f (n) =
lg n. Because the logarithm of a nonpositive number is undeﬁned, lg(i)
n  is  deﬁned  only  if  lg(i–1)  n  >  0.  Be  sure  to  distinguish  lg(i)  n  (the
logarithm function applied i times in succession, starting with argument
n) from lgi n (the logarithm of n raised to the ith power). Then we deﬁne
the iterated logarithm function as

lg*n = min {i ≥ 0 : lg(i) n ≤ 1}.

The iterated logarithm is a very slowly growing function:

lg* 2 = 1,
lg* 4 = 2,
lg* 16 = 3,
lg* 65536 = 4,
lg* (265536) = 5.

Since the number of atoms in the observable universe is estimated to be
about 1080, which is much less than 265536 = 1065536/lg 10 ≈ 1019,728,
we rarely encounter an input size n for which lg* n > 5.

Fibonacci numbers

We deﬁne the Fibonacci numbers Fi, for i ≥ 0, as follows:

Thus, after the ﬁrst two, each Fibonacci number is the sum of the two
previous ones, yielding the sequence

0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ….

Fibonacci numbers are related to the golden ratio ϕ and its conjugate
which are the two roots of the equation

,

x2 = x + 1.

As Exercise 3.3-7 asks you to prove, the golden ratio is given by

and its conjugate, by

Speciﬁcally, we have

which can be proved by induction (Exercise 3.3-8). Since

, we have

which implies that

which  is  to  say  that  the  ith  Fibonacci  number  Fi  is  equal  to
rounded  to  the  nearest  integer.  Thus,  Fibonacci  numbers  grow
exponentially.

Exercises

3.3-1
Show that if f (n) and g(n) are monotonically increasing functions, then
so are the functions f (n) + g(n) and f (g(n)), and if f (n) and g(n) are in
addition nonnegative, then f (n) · g(n) is monotonically increasing.

3.3-2
Prove that ⌊αn⌋ + ⌈(1 – α)n⌉ = n for any integer n and real number α in
the range 0 ≤ α ≤ 1.

3.3-3
Use equation (3.14) or other means to show that (n + o(n))k = Θ(nk) for
any real constant k. Conclude that ⌈n⌉

k = Θ(nk) and ⌊n⌋

k = Θ(nk).

3.3-4
Prove the following:

a. Equation (3.21).

b. Equations (3.26)–(3.28).

c. lg(Θ(n)) = Θ(lg n).

★ 3.3-5
Is the function ⌈lg n⌉! polynomially bounded? Is the function ⌈lg lg n⌉!
polynomially bounded?

★ 3.3-6
Which is asymptotically larger: lg(lg* n) or lg*(lg n)?

3.3-7
Show  that  the  golden  ratio  ϕ  and  its  conjugate
equation x2 = x + 1.

  both  satisfy  the

3.3-8
Prove by induction that the ith Fibonacci number satisﬁes the equation

where ϕ is the golden ratio and

 is its conjugate.

3.3-9
Show that k lg k = Θ(n) implies k = Θ(n/lg n).

Problems

3-1     Asymptotic behavior of polynomials
Let

where  ad  >  0,  be  a  degree-d  polynomial  in  n,  and  let  k  be  a  constant.
Use  the  deﬁnitions  of  the  asymptotic  notations  to  prove  the  following
properties.

a. If k ≥ d, then p(n) = O(nk).

b. If k ≤ d, then p(n) = Ω(nk).
c. If k = d, then p(n) = Θ(nk).
d. If k > d, then p(n) = o(nk).
e. If k < d, then p(n) = ω(nk).

3-2     Relative asymptotic growths

Indicate, for each pair of expressions (A, B) in the table below whether
A  is  O,  o,  Ω,  ω,  or  Θ  of  B.  Assume  that  k  ≥  1,  ϵ  >  0,  and  c  >  1  are
constants. Write your answer in the form of the table with “yes” or “no”
written in each box.

3-3     Ordering by asymptotic growth rates

a. Rank the following functions by order of growth. That is, ﬁnd an

arrangement g1, g2, … , g30 of the functions satisfying g1 = Ω(g2), g2
= Ω(g3), … , g29 = Ω(g30). Partition your list into equivalence classes
such that functions f (n) and g(n) belong to the same class if and only
if f (n) = Θ(g(n)).

lg(lg* n) 2lg* n
(3/2)n

n3

n2
lg2 n lg(n!)

n!

(lg n)!

n1/lg
n

ln ln n

lg* n

n · 2n nlg lg

ln n

1

n

2lg n

(lg n)lg
n

lg*(lg n)

en

n

4lg n (n +
1)!

2n

n lg n

b. Give an example of a single nonnegative function f (n) such that for
all functions gi(n) in part (a), f (n) is neither O(gi(n)) nor Ω(gi(n)).

3-4     Asymptotic notation properties
Let f (n) and g(n) be asymptotically positive functions. Prove or disprove
each of the following conjectures.

a. f (n) = O(g(n)) implies g(n) = O(f (n)).

b. f (n) + g(n) = Θ(min {f (n), g(n)}).
c. f (n) = O(g(n)) implies lg f (n) = O(lg g(n)), where lg g(n) ≥ 1 and f (n)

≥ 1 for all sufﬁciently large n.

d. f (n) = O(g(n)) implies 2f(n) = O (2g(n)).

e. f (n) = O ((f (n))2).

f. f (n) = O(g(n)) implies g(n) = Ω(f (n)).

g. f (n) = Θ(f (n/2)).
h. f (n) + o(f (n)) = Θ(f (n)).

3-5     Manipulating asymptotic notation
Let  f  (n)  and  g(n)  be  asymptotically  positive  functions.  Prove  the
following identities:

a. Θ(Θ(f (n))) = Θ(f (n)).
b. Θ(f (n)) + O(f (n)) = Θ(f (n)).
c. Θ(f (n)) + Θ(g(n)) = Θ(f (n) + g(n)).
d. Θ(f (n)) · Θ(g(n)) = Θ(f (n) · g(n)).
e. Argue that for any real constants a1, b1 > 0 and integer constants k1,

k2, the following asymptotic bound holds:

★ f. Prove that for S ⊆ Z, we have

assuming that both sums converge.

★ g. Show that for S ⊆ Z, the following asymptotic bound does not
necessarily hold, even assuming that both products converge, by
giving a counterexample:

3-6     Variations on O and Ω

Some  authors  deﬁne  Ω-notation  in  a  slightly  different  way  than  this
 (read “omega inﬁnity”) for
textbook does. We’ll use the nomenclature

this  alternative  deﬁnition.  We  say  that
  if  there  exists  a
positive constant c such that f (n) ≥ cg(n) ≥ 0 for inﬁnitely many integers
n.

a. Show that for any two asymptotically nonnegative functions f (n) and

g(n), we have f (n) = O(g(n)) or

 (or both).

b. Show that there exist two asymptotically nonnegative functions f (n)
and g(n) for which neither f (n) = O(g(n)) nor f (n) = Ω(g(n)) holds.

c. Describe the potential advantages and disadvantages of using  -

notation instead of Ω-notation to characterize the running times of
programs.

Some authors also deﬁne O in a slightly different manner. We’ll use O′
for  the  alternative  deﬁnition:  f  (n)  =  O′(g(n))  if  and  only  if  |f  (n)|  =
O(g(n)).

d. What happens to each direction of the “if and only if ” in Theorem

3.1 on page 56 if we substitute O′ for O but still use Ω?

Some  authors  deﬁne
factors ignored:

  (read  “soft-oh”)  to  mean  O  with  logarithmic

 : there exist positive constants c, k, and n0
such that 0 ≤ f (n) ≤ cg(n) lgk(n) for all n
≥ n0}.

e. Deﬁne

 and

 in a similar manner. Prove the corresponding analog

to Theorem 3.1.

3-7     Iterated functions
We  can  apply  the  iteration  operator  *  used  in  the  lg*  function  to  any
monotonically  increasing  function  f  (n)  over  the  reals.  For  a  given
constant c ∈ R, we deﬁne the iterated function

 by

which need not be well deﬁned in all cases. In other words, the quantity
 is the minimum number of iterated applications of the function f

required to reduce its argument down to c or less.

For  each  of  the  functions  f  (n)  and  constants  c  in  the  table  below,
. If there is no i such that f(i)

give as tight a bound as possible on
(n) ≤ c, write “undeﬁned” as your answer.

f (n)

n – 1

lg n

n/2

n/2

n1/3

c

0

1

1

2

2

1

2

a.

b.

c.

d.

e.

f.

g.

Chapter notes

Knuth [259] traces the origin of the O-notation to a number-theory text
by P. Bachmann in 1892. The o-notation was invented by E. Landau in
1909 for his discussion of the distribution of prime numbers. The Ω and
Θ notations were advocated by Knuth [265] to correct the popular, but
technically  sloppy,  practice  in  the  literature  of  using  O-notation  for
both  upper  and  lower  bounds.  As  noted  earlier  in  this  chapter,  many
people  continue  to  use  the  O-notation  where  the  Θ-notation  is  more
technically  precise.  The  soft-oh  notation
  in  Problem  3-6  was
introduced  by  Babai,  Luks,  and  Seress  [31],  although  it  was  originally
 as ignoring factors that
written as O~. Some authors now deﬁne
are logarithmic in g(n), rather than in n. With this deﬁnition, we can say
that
, but with the deﬁnition in Problem 3-6, this statement
is  not  true.  Further  discussion  of  the  history  and  development  of
asymptotic  notations  appears  in  works  by  Knuth  [259,  265]  and
Brassard and Bratley [70].

Not  all  authors  deﬁne  the  asymptotic  notations  in  the  same  way,
although the various deﬁnitions agree in most common situations. Some
of  the  alternative  deﬁnitions  encompass  functions  that  are  not
asymptotically  nonnegative,  as  long  as  their  absolute  values  are
appropriately bounded.

Equation  (3.29)  is  due  to  Robbins  [381].  Other  properties  of
elementary  mathematical  functions  can  be  found
in  any  good
mathematical  reference,  such  as  Abramowitz  and  Stegun  [1]  or
Zwillinger [468], or in a calculus book, such as Apostol [19] or Thomas
et  al.  [433].  Knuth  [259]  and  Graham,  Knuth,  and  Patashnik  [199]
contain  a  wealth  of  material  on  discrete  mathematics  as  used  in
computer science.

1 Within set notation, a colon means “such that.”

