9          Medians and Order Statistics

The ith order statistic of a set of n elements is the ith smallest element.
For example, the minimum of a set of elements is the ﬁrst order statistic
(i  =  1),  and  the  maximum  is  the  nth  order  statistic  (i  =  n).  A  median,
informally, is the “halfway point” of the set. When n is odd, the median
is  unique,  occurring  at  i  =  (n  +  1)/2.  When  n  is  even,  there  are  two
medians,  the  lower  median  occurring  at  i  =  n/2  and  the  upper  median
occurring  at  i  =  n/2  +  1.  Thus,  regardless  of  the  parity  of  n,  medians
occur  at  i  =  ⌊(n  +  1)/2⌋  and  i  =  ⌈(n  +  1)/2⌉.  For  simplicity  in  this  text,
however,  we  consistently  use  the  phrase  “the  median”  to  refer  to  the
lower median.

This chapter addresses the problem of selecting the ith order statistic
from a set of n distinct numbers. We assume for convenience that the set
contains  distinct  numbers,  although  virtually  everything  that  we  do
extends  to  the  situation  in  which  a  set  contains  repeated  values.  We
formally specify the selection problem as follows:
Input: A set A of n distinct numbers1 and an integer i, with 1 ≤ i ≤ n.
Output:  The  element  x  ∈  A  that  is  larger  than  exactly  i  –  1  other

elements of A.

We can solve the selection problem in O(n lg n) time simply by sorting
the  numbers  using  heapsort  or  merge  sort  and  then  outputting  the  ith
element in the sorted array. This chapter presents asymptotically faster
algorithms.

Section  9.1  examines  the  problem  of  selecting  the  minimum  and
maximum of a set of elements. More interesting is the general selection
problem,  which  we  investigate  in  the  subsequent  two  sections.  Section
9.2  analyzes  a  practical  randomized  algorithm  that  achieves  an  O(n)
expected running time, assuming distinct elements. Section 9.3 contains
an algorithm of more theoretical interest that achieves the O(n) running
time in the worst case.

9.1      Minimum and maximum

How many comparisons are necessary to determine the minimum of a
set of n elements? To obtain an upper bound of n – 1 comparisons, just
examine each element of the set in turn and keep track of the smallest
element  seen  so  far.  The  MINIMUM  procedure  assumes  that  the  set
resides in array A[1 : n].

MINIMUM(A, n)

1 min = A[1]
2 for i = 2 to n
3

if min > A[i]
min = A[i]

4
5 return min

It’s no more difﬁcult to ﬁnd the maximum with n – 1 comparisons.

Is  this  algorithm  for  minimum  the  best  we  can  do?  Yes,  because  it
turns  out  that  there’s  a  lower  bound  of  n  –  1  comparisons  for  the
problem  of  determining  the  minimum.  Think  of  any  algorithm  that
determines  the  minimum  as  a  tournament  among  the  elements.  Each
comparison  is  a  match  in  the  tournament  in  which  the  smaller  of  the
two  elements  wins.  Since  every  element  except  the  winner  must  lose  at
least one match, we can conclude that n – 1 comparisons are necessary
to  determine  the  minimum.  Hence  the  algorithm  MINIMUM  is
optimal with respect to the number of comparisons performed.

Simultaneous minimum and maximum

Some applications need to ﬁnd both the minimum and the maximum of
a set of n elements. For example, a graphics program may need to scale
a  set  of  (x,  y)  data  to  ﬁt  onto  a  rectangular  display  screen  or  other
graphical output device. To do so, the program must ﬁrst determine the
minimum and maximum value of each coordinate.

Of  course,  we  can  determine  both  the  minimum  and  the  maximum
of n elements using Θ(n) comparisons. We simply ﬁnd the minimum and
maximum independently, using n – 1 comparisons for each, for a total
of 2n – 2 = Θ(n) comparisons.

Although 2n – 2 comparisons is asymptotically optimal, it is possible
to improve the leading constant. We can ﬁnd both the minimum and the
maximum  using  at  most  3  ⌊n/2⌋  comparisons.  The  trick  is  to  maintain
both  the  minimum  and  maximum  elements  seen  thus  far.  Rather  than
processing  each  element  of  the  input  by  comparing  it  against  the
current  minimum  and  maximum,  at  a  cost  of  2  comparisons  per
element, process elements in pairs. Compare pairs of elements from the
input  ﬁrst  with  each  other,  and  then  compare  the  smaller  with  the
current minimum and the larger to the current maximum, at a cost of 3
comparisons for every 2 elements.

How  you  set  up  initial  values  for  the  current  minimum  and
maximum depends on whether n is odd or even. If n is odd, set both the
minimum  and  maximum  to  the  value  of  the  ﬁrst  element,  and  then
process  the  rest  of  the  elements  in  pairs.  If  n  is  even,  perform  1
comparison on the ﬁrst 2 elements to determine the initial values of the
minimum  and  maximum,  and  then  process  the  rest  of  the  elements  in
pairs as in the case for odd n.

Let’s count the total number of comparisons. If n is odd, then 3 ⌊n/2⌋
comparisons occur. If n is even, 1 initial comparison occurs, followed by
another 3(n – 2)/2 comparisons, for a total of 3n/2 – 2. Thus, in either
case, the total number of comparisons is at most 3 ⌊n/2⌋.

Exercises

9.1-1

Show that the second smallest of n elements can be found with n + ⌈lg
n⌉  –  2  comparisons  in  the  worst  case.  (Hint:  Also  ﬁnd  the  smallest
element.)

9.1-2
Given n > 2 distinct numbers, you want to ﬁnd a number that is neither
the  minimum  nor  the  maximum.  What  is  the  smallest  number  of
comparisons that you need to perform?

9.1-3
A racetrack can run races with ﬁve horses at a time to determine their
relative speeds. For 25 horses, it takes six races to determine the fastest
horse,  assuming  transitivity  (see  page  1159).  What’s  the  minimum
number of races it takes to determine the fastest three horses out of 25?

★ 9.1-4
Prove  the  lower  bound  of  ⌈3n/2⌉  –  2  comparisons  in  the  worst  case  to
ﬁnd  both  the  maximum  and  minimum  of  n  numbers.  (Hint:  Consider
how  many  numbers  are  potentially  either  the  maximum  or  minimum,
and investigate how a comparison affects these counts.)

9.2      Selection in expected linear time

The  general  selection  problem—ﬁnding  the  ith  order  statistic  for  any
value of i—appears more difﬁcult than the simple problem of ﬁnding a
minimum.  Yet,  surprisingly,  the  asymptotic  running  time  for  both
problems is the same: Θ(n). This section presents a divide-and-conquer
algorithm  for  the  selection  problem.  The  algorithm  RANDOMIZED-
SELECT  is  modeled  after  the  quicksort  algorithm  of  Chapter  7.  Like
quicksort it partitions the input array recursively. But unlike quicksort,
which
the  partition,
RANDOMIZED-SELECT  works  on  only  one  side  of  the  partition.
This  difference  shows  up  in  the  analysis:  whereas  quicksort  has  an
expected  running  time  of  Θ(n  lg  n),  the  expected  running  time  of
RANDOMIZED-SELECT  is  Θ(n),  assuming  that  the  elements  are
distinct.

recursively  processes  both

sides  of

introduced

RANDOMIZED-SELECT  uses  the  procedure  RANDOMIZED-
PARTITION
in  Section  7.3.  Like  RANDOMIZED-
QUICKSORT,  it  is  a  randomized  algorithm,  since  its  behavior  is
determined  in  part  by  the  output  of  a  random-number  generator.  The
RANDOMIZED-SELECT  procedure  returns  the  ith  smallest  element
of the array A[p : r], where 1 ≤ i ≤ r – p + 1.

return A[p]// 1 ≤ i ≤ r – p + 1 when p == r means that i = 1

RANDOMIZED-SELECT(A, p, r, i)
1 if p == r
2
3 q = RANDOMIZED-PARTITION(A, p, r)
4 k = q – p + 1
5 if i == k
6
7 elseif i < k
return RANDOMIZED-SELECT(A, p, q – 1, i)
8
9 else return RANDOMIZED-SELECT(A, q + 1, r, i – k)

return A[q]// the pivot value is the answer

Figure  9.1  illustrates  how  the  RANDOMIZED-SELECT  procedure
works.  Line  1  checks  for  the  base  case  of  the  recursion,  in  which  the
subarray A[p : r] consists of just one element. In this case, i must equal
1, and line 2 simply returns A[p] as the ith smallest element. Otherwise,
the call to RANDOMIZED-PARTITION in line 3 partitions the array
A[p : r] into two (possibly empty) subarrays A[p : q – 1] and A[q + 1 : r]
such that each element of A[p : q – 1] is less than or equal to A[q], which
in turn is less than each element of A[q + 1 : r]. (Although our analysis
assumes  that  the  elements  are  distinct,  the  procedure  still  yields  the
correct result even if equal elements are present.) As in quicksort, we’ll
refer  to  A[q]  as  the  pivot  element.  Line  4  computes  the  number  k  of
elements in the subarray A[p : q], that is, the number of elements in the
low  side  of  the  partition,  plus  1  for  the  pivot  element.  Line  5  then
checks  whether  A[q]  is  the  ith  smallest  element.  If  it  is,  then  line  6
returns  A[q].  Otherwise,  the  algorithm  determines  in  which  of  the  two
subarrays A[p: q – 1] and A[q + 1 : r] the ith smallest element lies. If i <
k, then the desired element lies on the low side of the partition, and line

8  recursively  selects  it  from  the  subarray.  If  i  >  k,  however,  then  the
desired element lies on the high side of the partition. Since we already
know k values that are smaller than the ith smallest element of A[p : r]
—namely, the elements of A[p : q]—the desired element is the (i – k)th
smallest element of A[q + 1 : r], which line 9 ﬁnds recursively. The code
appears  to  allow  recursive  calls  to  subarrays  with  0  elements,  but
Exercise 9.2-1 asks you to show that this situation cannot happen.

Figure  9.1  The  action  of  RANDOMIZED-SELECT  as  successive  partitionings  narrow  the
subarray  A[p:  r],  showing  the  values  of  the  parameters  p,  r,  and  i  at  each  recursive  call.  The
subarray A[p : r] in each recursive step is shown in tan, with the dark tan element selected as the
pivot for the next partitioning. Blue elements are outside A[p : r]. The answer is the tan element
in the bottom array, where p = r = 5 and i = 1. The array designations A(0), A(1), … , A(5), the
partitioning  numbers,  and  whether  the  partitioning  is  helpful  are  explained  on  the  following
page.

The  worst-case  running  time  for  RANDOMIZED-SELECT  is
Θ(n2), even to ﬁnd the minimum, because it could be extremely unlucky
and  always  partition  around  the  largest  remaining  element  before
identifying the ith smallest when only one element remains. In this worst
case,  each  recursive  step  removes  only  the  pivot  from  consideration.
Because partitioning n elements takes Θ(n) time, the recurrence for the

worst-case running time is the same as for QUICKSORT: T (n) = T (n –
1) + Θ(n), with the solution T (n) = Θ(n2). We’ll see that the algorithm
has  a  linear  expected  running  time,  however,  and  because  it  is
randomized, no particular input elicits the worst-case behavior.

To see the intuition behind the linear expected running time, suppose
that each time the algorithm randomly selects a pivot element, the pivot
lies  somewhere  within  the  second  and  third  quartiles—the  “middle
half ”—of  the  remaining  elements  in  sorted  order.  If  the  ith  smallest
element  is  less  than  the  pivot,  then  all  the  elements  greater  than  the
pivot  are  ignored  in  all  future  recursive  calls.  These  ignored  elements
include at least the uppermost quartile, and possibly more. Likewise, if
the ith smallest element is greater than the pivot, then all the elements
less than the pivot—at least the ﬁrst quartile—are ignored in all future
recursive  calls.  Either  way,  therefore,  at  least  1/4  of  the  remaining
elements are ignored in all future recursive calls, leaving at most 3/4 of
the  remaining  elements  in  play:  residing  in  the  subarray  A[p  :  r].  Since
RANDOMIZED-PARTITION  takes  Θ(n)  time  on  a  subarray  of  n
elements,  the  recurrence  for  the  worst-case  running  time  is  T  (n)  =  T
(3n/4)  +  Θ(n).  By  case  3  of  the  master  method  (Theorem  4.1  on  page
102), this recurrence has solution T (n) = Θ(n).

Of  course,  the  pivot  does  not  necessarily  fall  into  the  middle  half
every time. Since the pivot is selected at random, the probability that it
falls into the middle half is about 1/2 each time. We can view the process
of selecting the pivot as a Bernoulli trial (see Section C.4) with success
equating  to  the  pivot  residing  in  the  middle  half.  Thus  the  expected
number of trials needed for success is given by a geometric distribution:
just  two  trials  on  average  (equation  (C.36)  on  page  1197).  In  other
words,  we  expect  that  half  of  the  partitionings  reduce  the  number  of
elements still in play by at least 3/4 and that half of the partitionings do
not help as much. Consequently, the expected number of partitionings
at  most  doubles  from  the  case  when  the  pivot  always  falls  into  the
middle half. The cost of each extra partitioning is less than the one that
preceded it, so that the expected running time is still Θ(n).

To  make  the  above  argument  rigorous,  we  start  by  deﬁning  the
random  variable  A(j)  as  the  set  of  elements  of  A  that  are  still  in  play

after j partitionings (that is, within the subarray A[p : r] after j calls of
RANDOMIZED-SELECT), so that A(0) consists of all the elements in
A.  Since  each  partitioning  removes  at  least  one  element—the  pivot—
from  being  in  play,  the  sequence  |A(0)|,  |A(1)|,  |A(2)|,  …  strictly
decreases. Set A(j–1) is in play before the j th partitioning, and set A(j)
remains  in  play  afterward.  For  convenience,  assume  that  the  initial  set
A(0) is the result of a 0th “dummy” partitioning.

Let’s  call  the  j  th  partitioning  helpful  if  |A(j)|  ≤  (3/4)|A(j–1)|.  Figure
9.1  shows  the  sets  A(j)  and  whether  partitionings  are  helpful  for  an
example  array.  A  helpful  partitioning  corresponds  to  a  successful
Bernoulli trial. The following lemma shows that a partitioning is at least
as likely to be helpful as not.

Lemma 9.1
A partitioning is helpful with probability at least 1/2.

Proof      Whether  a  partitioning  is  helpful  depends  on  the  randomly
chosen pivot. We discussed the “middle half ” in the informal argument
above.  Let’s  more  precisely  deﬁne  the  middle  half  of  an  n-element
subarray as all but the smallest ⌈n/4⌉ – 1 and greatest ⌈n/4⌉ – 1 elements
(that  is,  all  but  the  ﬁrst  ⌈n/4⌉  –  1  and  last  ⌈n/4⌉  –  1  elements  if  the
subarray were sorted). We’ll prove that if the pivot falls into the middle
half, then the pivot leads to a helpful partitioning, and we’ll also prove
that  the  probability  of  the  pivot  falling  into  the  middle  half  is  at  least
1/2.

Regardless  of  where  the  pivot  falls,  either  all  the  elements  greater
than it or all the elements less than it, along with the pivot itself, will no
longer  be  in  play  after  partitioning.  If  the  pivot  falls  into  the  middle
half, therefore, at least ⌈n/4⌉ – 1 elements less than the pivot or ⌈n/4⌉ – 1
elements greater than the pivot, plus the pivot, will no longer be in play
after  partitioning.  That  is,  at  least  ⌈n/4⌉  elements  will  no  longer  be  in
play.  The  number  of  elements  remaining  in  play  will  be  at  most  n  –

⌈n/4⌉, which equals ⌊3n/4⌋ by Exercise 3.3-2 on page 70. Since ⌊3n/4⌋ ≤
3n/4, the partitioning is helpful.

To  determine  a  lower  bound  on  the  probability  that  a  randomly
chosen pivot falls into the middle half, we determine an upper bound on
the probability that it does not. That probability is

Thus,  the  pivot  has  a  probability  of  at  least  1/2  of  falling  into  the
middle  half,  and  so  the  probability  is  at  least  1/2  that  a  partitioning  is
helpful.

▪

We can now bound the expected running time of RANDOMIZED-

SELECT.

Theorem 9.2
The  procedure  RANDOMIZED-SELECT  on  an  input  array  of  n
distinct elements has an expected running time of Θ(n).

Proof   Since not every partitioning is necessarily helpful, let’s give each
partitioning  an  index  starting  at  0  and  denote  by  〈h0,  h1,  h2,  …  ,  hm〉
the  sequence  of  partitionings  that  are  helpful,  so  that  the  hkth
partitioning is helpful for k = 0, 1, 2, … , m. Although the number m of
helpful partitionings is a random variable, we can bound it, since after
at  most  ⌈log4/3  n⌉  helpful  partitionings,  only  one  element  remains  in
play.  Consider  the  dummy  0th  partitioning  as  helpful,  so  that  h0  =  0.
 by nk, where n0 = |A(0)| is the original problem size. Since
Denote
the  hkth  partitioning  is  helpful  and  the  sizes  of  the  sets  A(j)  strictly
 for k = 1, 2, …
decrease, we have

, m. By iterating nk ≤ (3/4) nk–1, we have that nk ≤ (3/4)kn0 for k = 0, 1,
2, … , m.

Figure 9.2 The sets within each generation in the proof of Theorem 9.2. Vertical lines represent
the sets, with the height of each line indicating the size of the set, which equals the number of
,  which  is  the  result  of  a  helpful
elements  in  play.  Each  generation  starts  with  a  set
partitioning.  These  sets  are  drawn  in  black  and  are  at  most  3/4  the  size  of  the  sets  to  their
immediate  left.  Sets  drawn  in  orange  are  not  the  ﬁrst  within  a  generation.  A  generation  may
. The sets
contain just one set. The sets in generation k are

,

  are  deﬁned  so  that

.  If  the  partitioning  gets  all  the  way  to

generation hm, set

 has at most one element in play.

As  Figure  9.2  depicts,  we  break  up  the  sequence  of  sets  A(j)  into
m generations consisting of consecutively partitioned sets, starting with
  of  a  helpful  partitioning  and  ending  with  the  last  set
the  result
  before  the  next  helpful  partitioning,  so  that  the  sets  in
. Then for each set of elements

,

generation k are
A(j) in the kth generation, we have that
Next, we deﬁne the random variable

.

Xk = hk + 1 – hk

for k = 0, 1, 2, … , m – 1. That is, Xk is the number of sets in the kth
,
generation,  so  that  the  sets

in  the  kth  generation  are

.

By  Lemma  9.1,  the  probability  that  a  partitioning  is  helpful  is  at
least 1/2. The probability is actually even higher, since a partitioning is
helpful  even  if  the  pivot  does  not  fall  into  the  middle  half  but  the  ith
smallest  element  happens  to  lie  in  the  smaller  side  of  the  partitioning.
We’ll just use the lower bound of 1/2, however, and then equation (C.36)
gives that E [Xk] ≤ 2 for k = 0, 1, 2, … , m – 1.

Let’s  derive  an  upper  bound  on  how  many  comparisons  are  made
altogether  during  partitioning,  since  the  running  time  is  dominated  by
the comparisons. Since we are calculating an upper bound, assume that
the  recursion  goes  all  the  way  until  only  one  element  remains  in  play.
The  j  th  partitioning  takes  the  set  A(j–1)  of  elements  in  play,  and  it
compares  the  randomly  chosen  pivot  with  all  the  other  |A(j–1)|  –  1
elements,  so  that  the  jth  partitioning  makes  fewer  than  |A(j–1)|
sizes
the  kth  generation  have
comparisons.  The
.  Thus,  the  total  number  of  comparisons

sets

in

during partitioning is less than

Since  E  [Xk]  ≤  2,  we  have  that  the  expected  total  number  of
comparisons during partitioning is less than

Since  n0  is  the  size  of  the  original  array  A,  we  conclude  that  the
expected number of comparisons, and thus the expected running time,
for RANDOMIZED-SELECT is O(n). All n elements are examined in
the ﬁrst call of RANDOMIZED-PARTITION, giving a lower bound of
Ω(n). Hence the expected running time is Θ(n).

▪

Exercises

9.2-1
Show that RANDOMIZED-SELECT never makes a recursive call to a
0-length array.

9.2-2
Write an iterative version of RANDOMIZED-SELECT.

9.2-3
Suppose that RANDOMIZED-SELECT is used to select the minimum
element of the array A = 〈2, 3, 0, 5, 7, 9, 1, 8, 6, 4〉. Describe a sequence
in  a  worst-case  performance  of
of  partitions
RANDOMIZED-SELECT.

results

that

9.2-4

Argue  that  the  expected  running  time  of  RANDOMIZED-SELECT
does not depend on the order of the elements in its input array A[p : r].
That  is,  the  expected  running  time  is  the  same  for  any  permutation  of
the input array A[p : r]. (Hint: Argue by induction on the length n of the
input array.)

9.3      Selection in worst-case linear time

We’ll  now  examine  a  remarkable  and  theoretically  interesting  selection
algorithm  whose  running  time  is  Θ(n)  in  the  worst  case.  Although  the
RANDOMIZED-SELECT  algorithm  from  Section  9.2  achieves  linear
expected  time,  we  saw  that  its  running  time  in  the  worst  case  was
quadratic.  The  selection  algorithm  presented  in  this  section  achieves
linear  time  in  the  worst  case,  but  it  is  not  nearly  as  practical  as
RANDOMIZED-SELECT. It is mostly of theoretical interest.

Like the expected linear-time RANDOMIZED-SELECT, the worst-
case  linear-time  algorithm  SELECT  ﬁnds  the  desired  element  by
recursively  partitioning  the  input  array.  Unlike  RANDOMIZED-
SELECT,  however,  SELECT  guarantees  a  good  split  by  choosing  a
provably  good  pivot  when  partitioning  the  array.  The  cleverness  in  the
algorithm  is  that  it  ﬁnds  the  pivot  recursively.  Thus,  there  are  two
invocations  of  SELECT:  one  to  ﬁnd  a  good  pivot,  and  a  second  to
recursively ﬁnd the desired order statistic.

The partitioning algorithm used by SELECT is like the deterministic
partitioning  algorithm  PARTITION  from  quicksort  (see  Section  7.1),
but  modiﬁed  to  take  the  element  to  partition  around  as  an  additional
input  parameter.  Like  PARTITION,  the  PARTITION-AROUND
algorithm  returns  the  index  of  the  pivot.  Since  it’s  so  similar  to
PARTITION, the pseudocode for PARTITION-AROUND is omitted.

The SELECT procedure takes as input a subarray A[p : r] of n = r –
p + 1 elements and an integer i in the range 1 ≤ i ≤ n. It returns the ith
smallest element of A. The pseudocode is actually more understandable
than it might appear at ﬁrst.

SELECT(A, p, r, i)

  1 while (r – p + 1) mod 5 ≠ 0
for j = p + 1 to r
  2
if A[p] > A[j]

  3

// put the minimum into A[p]

  4

  5

  6

  7

exchange A[p] with A[j]

// If we want the minimum of A[p : r], we’re done.
if i == 1

return A[p]

  9

  8

// Otherwise, we want the (i – 1)st element of A[p + 1 : r].
p = p + 1
i = i – 1
10
11 g = (r – p + 1)/5

//  number  of  5-element
groups
// sort each group

sort 〈A[j], A[j + g], A[j + 2g], A[j + 3g], A[j + 4g]〉 in place

12 for j = p to p + g – 1
13
14 // All group medians now lie in the middle ﬁfth of A[p : r].
15 // Find the pivot x recursively as the median of the group medians.
16 x = SELECT(A, p + 2g, p + 3g – 1, ⌈g/2⌉)
17 q  =  PARTITION-AROUND(A,  p,  r,

// partition around the pivot

x)

18 // The rest is just like lines 3–9 of RANDOMIZED-SELECT.
19 k = q – p + 1
20 if i == k
21

return A[q]

//  the  pivot  value
answer

is  the

22 elseif i < k
return SELECT(A, p, q – 1, i)
23
24 else return SELECT(A, q + 1, r, i – k)

The  pseudocode  starts  by  executing  the  while  loop  in  lines  1–10  to
reduce  the  number  r  –  p  +  1  of  elements  in  the  subarray  until  it  is
divisible  by  5.  The  while  loop  executes  0  to  4  times,  each  time
rearranging the elements of A[p : r] so that A[p] contains the minimum
element.  If  i  =  1,  which  means  that  we  actually  want  the  minimum
element,  then  the  procedure  simply  returns  it  in  line  7.  Otherwise,
SELECT eliminates the minimum from the subarray A[p : r] and iterates

to  ﬁnd  the  (i  –  1)st  element  in  A[p  +  1  :  r].  Lines  9–10  do  so  by
incrementing p and decrementing i. If the while loop completes all of its
iterations without returning a result, the procedure executes the core of
the  algorithm  in  lines  11–24,  assured  that  the  number  r  –  p  +  1  of
elements in A[p : r] is evenly divisible by 5.

Figure 9.3 The relationships between elements (shown as circles) immediately after line 17 of the
selection algorithm SELECT. There are g = (r – p + 1)/5 groups of 5 elements, each of which
occupies a column. For example, the leftmost column contains elements A[p], A[p + g], A[p +
2g], A[p + 3g], A[p + 4g], and the next column contains A[p + 1], A[p + g + 1], A[p + 2g + 1], A[p
+ 3g + 1], A[p + 4g + 1]. The medians of the groups are red, and the pivot x is labeled. Arrows
go from smaller elements to larger. The elements on the blue background are all known to be
less than or equal to x and cannot fall into the high side of the partition around x. The elements
on the yellow background are known to be greater than or equal to x and cannot fall into the
low side of the partition around x. The pivot x belongs to both the blue and yellow regions and
is shown on a green background. The elements on the white background could lie on either side
of the partition.

The  next  part  of  the  algorithm  implements  the  following  idea,
illustrated in Figure 9.3. Divide the elements in A[p : r] into g = (r – p +
1)/5 groups of 5 elements each. The ﬁrst 5-element group is

〈A[p], A[p + g], A[p + 2g], A[p + 3g], A[p + 4g]〉,

the second is

〈A[p + 1], A[p + g + 1], A[p + 2g + 1], A[p + 3g + 1], A[p + 4g + 1]〉,

and so forth until the last, which is

〈A[p + g – 1], A[p + 2g – 1], A[p + 3g – 1], A[p + 4g – 1], A[r]〉.

(Note that r = p + 5g – 1.) Line 13 puts each group in order using, for
example, insertion sort (Section 2.1), so that for j = p, p + 1, … , p + g –
1, we have

A[j] ≤ A[j + g] ≤ A[j + 2g] ≤ A[j + 3g] ≤ A[j + 4g].

Each vertical column in Figure 9.3 depicts a sorted group of 5 elements.
The  median  of  each  5-element  group  is  A[j  +  2g],  and  thus  all  the  5-
element medians, shown in red, lie in the range A[p + 2g : p + 3g – 1].

Next, line 16 determines the pivot x by recursively calling SELECT
to  ﬁnd  the  median  (speciﬁcally,  the  ⌈g/2⌉th  smallest)  of  the  g  group
medians. Line 17 uses the modiﬁed PARTITION-AROUND algorithm
to partition the elements of A[p : r] around x, returning the index q of
x, so that A[q] = x, elements in A[p : q] are all at most x, and elements in
A[q : r] are greater than or equal to x.

The  remainder  of  the  code  mirrors  that  of  RANDOMIZED-
SELECT.  If  the  pivot  x  is  the  ith  largest,  the  procedure  returns  it.
Otherwise, the procedure recursively calls itself on either A[p : q – 1] or
A[q + 1 : r], depending on the value of i.

Let’s  analyze  the  running  time  of  SELECT  and  see  how  the
judicious choice of the pivot x plays into a guarantee on its worst-case
running time.

Theorem 9.3
The running time of SELECT on an input of n elements is Θ(n).

Proof   Deﬁne T (n) as the worst-case time to run SELECT on any input
subarray A[p : r] of size at most n, that is, for which r – p + 1 ≤ n. By this
deﬁnition, T (n) is monotonically increasing.

We  ﬁrst  determine  an  upper  bound  on  the  time  spent  outside  the
recursive  calls  in  lines  16,  23,  and  24.  The  while  loop  in  lines  1–10
executes  0  to  4  times,  which  is  O(1)  times.  Since  the  dominant  time

within the loop is the computation of the minimum in lines 2–4, which
takes  Θ(n)  time,  lines  1–10  execute  in  O(1)  ·  Θ(n)  =  O(n)  time.  The
sorting of the 5-element groups in lines 12–13 takes Θ(n) time because
each  5-element  group  takes  Θ(1)  time  to  sort  (even  using  an
asymptotically inefﬁcient sorting algorithm such as insertion sort), and
there are g elements to sort, where n/5 – 1 < g ≤ n/5. Finally, the time to
partition  in  line  17  is  Θ(n),  as  Exercise  7.1-3  on  page  187  asks  you  to
show.  Because  the  remaining  bookkeeping  only  costs  Θ(1)  time,  the
total amount of time spent outside of the recursive calls is O(n) + Θ(n)
+ Θ(n) + Θ(1) = Θ(n).

Now  let’s  determine  the  running  time  for  the  recursive  calls.  The
recursive call to ﬁnd the pivot in line 16 takes T (g) ≤ T (n/5) time, since
g ≤ n/5 and T (n) monotonically increases. Of the two recursive calls in
lines  23  and  24,  at  most  one  is  executed.  But  we’ll  see  that  no  matter
which  of  these  two  recursive  calls  to  SELECT  actually  executes,  the
number of elements in the recursive call turns out to be at most 7n/10,
and hence the worst-case cost for lines 23 and 24 is at most T (7n/10).
Let’s  now  show  that  the  machinations  with  group  medians  and  the
choice  of  the  pivot  x  as  the  median  of  the  group  medians  guarantees
this property.

Figure  9.3  helps  to  visualize  what’s  going  on.  There  are  g  ≤  n/5
groups of 5 elements, with each group shown as a column sorted from
bottom  to  top.  The  arrows  show  the  ordering  of  elements  within  the
columns. The columns are ordered from left to right with groups to the
left  of  x’s  group  having  a  group  median  less  than  x  and  those  to  the
right of x’s group having a group median greater than x. Although the
relative  order  within  each  group  matters,  the  relative  order  among
groups to the left of x’s column doesn’t really matter, and neither does
the  relative  order  among  groups  to  the  right  of  x’s  column.  The
important  thing  is  that  the  groups  to  the  left  have  group  medians  less
than x (shown by the horizontal arrows entering x), and that the groups
to the right have group medians greater than x (shown by the horizontal
arrows  leaving  x).  Thus,  the  yellow  region  contains  elements  that  we
know  are  greater  than  or  equal  to  x,  and  the  blue  region  contains
elements that we know are less than or equal to x.

These  two  regions  each  contain  at  least  3g/2  elements.  The  number
of group medians in the yellow region is ⌊g/2⌋ + 1, and for each group
median,  two  additional  elements  are  greater  than  it,  making  a  total  of
3(⌊g/2⌋ + 1) ≥ 3g/2 elements. Similarly, the number of group medians in
the  blue  region  is  ⌈g/2⌉,  and  for  each  group  median,  two  additional
elements are less than it, making a total of 3 ⌈g/2 ⌉ ≥ 3g/2.

The elements in the yellow region cannot fall into the low side of the
partition  around  x,  and  those  in  the  blue  region  cannot  fall  into  the
high  side.  The  elements  in  neither  region—those  lying  on  a  white
background—could  fall  into  either  side  of  the  partition.  But  since  the
low side of the partition excludes the elements in the yellow region, and
there  are  a  total  of  5g  elements,  we  know  that  the  low  side  of  the
partition  can  contain  at  most  5g  –  3g/2  =  7g/2  ≤  7n/10  elements.
Likewise, the high side of the partition excludes the elements in the blue
region,  and  a  similar  calculation  shows  that  it  also  contains  at  most
7n/10 elements.

All  of  which  leads  to  the  following  recurrence  for  the  worst-case

running time of SELECT:

We can show that T (n) = O(n) by substitution.2 More speciﬁcally, we’ll
prove that T (n) ≤ cn for some suitably large constant c > 0 and all n > 0.
Substituting  this  inductive  hypothesis  into  the  right-hand  side  of
recurrence (9.1) and assuming that n ≥ 5 yields

T (n) ≤ c(n/5) + c(7n/10) + Θ(n)

≤ 9cn/10 + Θ(n)
= cn – cn/10 + Θ(n)
≤ cn

if  c  is  chosen  large  enough  that  c/10  dominates  the  upper-bound
constant hidden by the Θ(n). In addition to this constraint, we can pick
c large enough that T (n) ≤ cn for all n ≤ 4, which is the base case of the
recursion  within  SELECT.  The  running  time  of  SELECT  is  therefore

O(n)  in  the  worst  case,  and  because  line  13  alone  takes  Θ(n)  time,  the
total time is Θ(n).

▪

As

in  a  comparison  sort  (see  Section  8.1),  SELECT  and
RANDOMIZED-SELECT  determine  information  about  the  relative
order  of  elements  only  by  comparing  elements.  Recall  from  Chapter  8
that  sorting  requires  Ω(n  lg  n)  time  in  the  comparison  model,  even  on
average  (see  Problem  8-1).  The  linear-time  sorting  algorithms  in
Chapter  8  make  assumptions  about  the  type  of  the  input.  In  contrast,
the  linear-time  selection  algorithms  in  this  chapter  do  not  require  any
assumptions  about  the  input’s  type,  only  that  the  elements  are  distinct
and  can  be  pairwise  compared  according  to  a  linear  order.  The
algorithms in this chapter are not subject to the Ω(n lg n) lower bound,
because they manage to solve the selection problem without sorting all
the  elements.  Thus,  solving  the  selection  problem  by  sorting  and
indexing,  as  presented
is
asymptotically inefﬁcient in the comparison model.

introduction  to  this  chapter,

in  the

Exercises

9.3-1
In  the  algorithm  SELECT,  the  input  elements  are  divided  into  groups
of 5. Show that the algorithm works in linear time if the input elements
are divided into groups of 7 instead of 5.

9.3-2
Suppose that the preprocessing in lines 1–10 of SELECT is replaced by
a base case for n ≥ n0, where n0 is a suitable constant; that g is chosen as
⌊r  –  p  +  1)/5⌋;  and  that  the  elements  in  A[5g  :  n]  belong  to  no  group.
Show  that  although  the  recurrence  for  the  running  time  becomes
messier, it still solves to Θ(n).

9.3-3
Show  how  to  use  SELECT  as  a  subroutine  to  make  quicksort  run  in
O(n lg n) time in the worst case, assuming that all elements are distinct.

Figure  9.4  Professor  Olay  needs  to  determine  the  position  of  the  east-west  oil  pipeline  that
minimizes the total length of the north-south spurs.

★ 9.3-4
Suppose  that  an  algorithm  uses  only  comparisons  to  ﬁnd  the  ith
smallest element in a set of n elements. Show that it can also ﬁnd the i –
1 smaller elements and the n – i larger elements without performing any
additional comparisons.

9.3-5
Show  how  to  determine  the  median  of  a  5-element  set  using  only  6
comparisons.

9.3-6
You have a “black-box” worst-case linear-time median subroutine. Give
a simple, linear-time algorithm that solves the selection problem for an
arbitrary order statistic.

9.3-7
Professor  Olay  is  consulting  for  an  oil  company,  which  is  planning  a
large  pipeline  running  east  to  west  through  an  oil  ﬁeld  of  n  wells.  The
company wants to connect a spur pipeline from each well directly to the
main pipeline along a shortest route (either north or south), as shown in
Figure 9.4. Given the x- and y-coordinates of the wells, how should the
professor pick an optimal location of the main pipeline to minimize the

total length of the spurs? Show how to determine an optimal location in
linear time.

9.3-8
The kth quantiles of an n-element set are the k – 1 order statistics that
divide the sorted set into k equal-sized sets (to within 1). Give an O(n lg
k)-time algorithm to list the kth quantiles of a set.

9.3-9
Describe  an  O(n)-time  algorithm  that,  given  a  set  S  of  n  distinct
numbers and a positive integer k ≤ n, determines the k numbers in S that
are closest to the median of S.

9.3-10
Let  X[1  :  n]  and  Y  [1  :  n]  be  two  arrays,  each  containing  n  numbers
already  in  sorted  order.  Give  an  O(lg  n)-time  algorithm  to  ﬁnd  the
median  of  all  2n  elements  in  arrays  X  and  Y.  Assume  that  all  2n
numbers are distinct.

Problems

9-1     Largest i numbers in sorted order
You are given a set of n numbers, and you wish to ﬁnd the i largest in
sorted  order  using  a  comparison-based  algorithm.  Describe  the
algorithm that implements each of the following methods with the best
asymptotic  worst-case  running  time,  and  analyze  the  running  times  of
the algorithms in terms of n and i.

a. Sort the numbers, and list the i largest.

b. Build a max-priority queue from the numbers, and call EXTRACT-

MAX i times.

c. Use an order-statistic algorithm to ﬁnd the ith largest number,
partition around that number, and sort the i largest numbers.

9-2     Variant of randomized selection

Professor Mendel has proposed simplifying RANDOMIZED-SELECT
by  eliminating  the  check  for  whether  i  and  k  are  equal.  The  simpliﬁed
procedure is SIMPLER-RANDOMIZED-SELECT.

SIMPLER-RANDOMIZED-SELECT(A, p, r, i)

1 if p == r
2

return A[p]

// 1 ≤ i ≤ r – p + 1 means that i
= 1

3 q = RANDOMIZED-PARTITION(A, p, r)
4 k = q – p + 1
5 if i ≤ k
6

SIMPLER-RANDOMIZED-

return

SELECT(A, p, q, i)

7 else

return

SIMPLER-RANDOMIZED-

SELECT(A, q + 1, r, i – k)

a. Argue that in the worst case, SIMPLER-RANDOMIZED-SELECT

never terminates.

b. Prove that the expected running time of SIMPLER-

RANDOMIZED-SELECT is still O(n).

9-3     Weighted median
Consider n elements x1, x2, … , xn with positive weights w1, w2, … , wn
.  The  weighted  (lower)  median  is  an  element  xk
such  that
satisfying

and

For example, consider the following elements xi and weights wi:

1
3

2
8

7
i
6
xi
wi 0.12 0.35 0.025 0.08 0.15 0.075 0.2

5
4

3
2

6
1

4
5

For these elements, the median is x5 = 4, but the weighted median is x7
=  6.  To  see  why  the  weighted  median  is  x7,  observe  that  the  elements
less than x7 are x1, x3, x4, x5, and x6, and the sum w1 + w3 + w4 + w5
+  w6  =  0.45,  which  is  less  than  1/2.  Furthermore,  only  element  x2  is
greater than x7, and w2 = 0.35, which is no greater than 1/2.

a. Argue that the median of x1, x2, … , xn is the weighted median of

the xi with weights wi = 1/n for i = 1, 2, … , n.

b. Show how to compute the weighted median of n elements in O(n lg n)

worst-case time using sorting.

c. Show how to compute the weighted median in Θ(n) worst-case time
using a linear-time median algorithm such as SELECT from Section
9.3.

The  post-ofﬁce  location  problem  is  deﬁned  as  follows.  The  input  is  n
points p1, p2, … , pn with associated weights w1, w2, … , wn. A solution
is a point p (not necessarily one of the input points) that minimizes the
, where d(a, b) is the distance between points a and b.
sum

d. Argue that the weighted median is a best solution for the one-

dimensional post-ofﬁce location problem, in which points are simply
real numbers and the distance between points a and b is d(a, b) = |a –
b|.

e. Find the best solution for the two-dimensional post-ofﬁce location
problem, in which the points are (x, y) coordinate pairs and the
distance between points a = (x1, y1) and b = (x2, y2) is the Manhattan
distance given by d(a, b) = |x1 – x2| + |y1 – y2|.

9-4     Small order statistics

Let’s  denote  by  S(n)  the  worst-case  number  of  comparisons  used  by
SELECT to select the ith order statistic from n numbers. Although S(n)
= Θ(n), the constant hidden by the Θ-notation is rather large. When i is
small  relative  to  n,  there  is  an  algorithm  that  uses  SELECT  as  a
subroutine but makes fewer comparisons in the worst case.

a. Describe an algorithm that uses Ui(n) comparisons to ﬁnd the ith

smallest of n elements, where

(Hint: Begin with ⌊n/2⌋ disjoint pairwise comparisons, and recurse on
the set containing the smaller element from each pair.)

b. Show that, if i < n/2, then Ui(n) = n + O(S(2i) lg(n/i)).

c. Show that if i is a constant less than n/2, then Ui(n) = n + O(lg n).

d. Show that if i = n/k for k ≥ 2, then Ui(n) = n + O(S(2n/k) lg k).

9-5     Alternative analysis of randomized selection

In this problem, you will use indicator random variables to analyze the
procedure RANDOMIZED-SELECT in a manner akin to our analysis
of RANDOMIZED-QUICKSORT in Section 7.4.2.

As in the quicksort analysis, we assume that all elements are distinct,
and  we  rename  the  elements  of  the  input  array  A  as  z1,  z2,  …  ,  zn,
where  zi  is  the  ith  smallest  element.  Thus  the  call  RANDOMIZED-
SELECT(A, 1, n, i) returns zi.

For 1 ≤ j < k ≤ n, let

Xijk = I {zj is compared with zk sometime during the execution of the

algorithm to ﬁnd zi}.

a. Give an exact expression for E [Xijk]. (Hint: Your expression may

have different values, depending on the values of i, j, and k.)

b. Let Xi denote the total number of comparisons between elements of

array A when ﬁnding zi. Show that

c. Show that E [Xi] ≤ 4n.

d. Conclude that, assuming all elements of array A are distinct,

RANDOMIZED-SELECT runs in O(n) expected time.

9-6     Select with groups of 3

Exercise 9.3-1 asks you to show that the SELECT algorithm still runs in
linear  time  if  the  elements  are  divided  into  groups  of  7.  This  problem
asks about dividing into groups of 3.

a. Show that SELECT runs in linear time if you divide the elements into

groups whose size is any odd constant greater than 3.

b. Show that SELECT runs in O(n lg n) time if you divide the elements

into groups of size 3.

Because  the  bound  in  part  (b)  is  just  an  upper  bound,  we  do  not
know  whether  the  groups-of-3  strategy  actually  runs  in  O(n)  time.  But
by  repeating  the  groups-of-3  idea  on  the  middle  group  of  medians,  we
can pick a pivot that guarantees O(n) time. The SELECT3 algorithm on
the  next  page  determines  the  ith  smallest  of  an  input  array  of  n  >  1
distinct elements.

c. Describe in English how the SELECT3 algorithm works. Include in

your description one or more suitable diagrams.

d. Show that SELECT3 runs in O(n) time in the worst case.

Chapter notes

The  worst-case  linear-time  median-ﬁnding  algorithm  was  devised  by
Blum,  Floyd,  Pratt,  Rivest,  and  Tarjan  [62].  The  fast  randomized

version is due to Hoare [218]. Floyd and Rivest [147] have developed an
improved  randomized  version  that  partitions  around  an  element
recursively selected from a small sample of the elements.

SELECT3(A, p, r, i)
  1 while (r – p + 1) mod 9 ≠ 0
for j = p + 1 to r
  2
if A[p] > A[j]

  3

// put the minimum into A[p]

  4

  5

  6

  7

exchange A[p] with A[j]

// If we want the minimum of A[p : r], we’re done.
if i == 1

return A[p]

  9

  8

// Otherwise, we want the (i – 1)st element of A[p + 1 : r].
p = p + 1
i = i – 1
10
11 g = (r – p + 1)/3
12 for j = p to p + g – 1
13
14 // All group medians now lie in the middle third of A[p : r].
15 g′ = g/3

sort 〈A[j], A[j + g], A[j + 2g]〉 in place

number

of

// number of 3-element groups
// run through the groups

3-element

//
subgroups
// sort the subgroups

sort 〈A[j], A[j + g′], A[j + 2g′]〉 in place

16 for j = p + g to p + g + g′ – 1
17
18 // All subgroup medians now lie in the middle ninth of A[p : r].
19 //  Find  the  pivot  x  recursively  as  the  median  of  the  subgroup

medians.

20 x = SELECT3(A, p + 4g′, p + 5g′ – 1, ⌈g′/2⌉)
21 q  =  PARTITION-AROUND(A,  p,

// partition around the pivot

r, x)

22 // The rest is just like lines 19–24 of SELECT.
23 k = q – p + 1
24 if i == k
25
26 elseif i < k
27

return SELECT3(A, p, q – 1, i)

return A[q]

// the pivot value is the answer

28 else return SELECT3(A, q + 1, r, i – k)

It  is  still  unknown  exactly  how  many  comparisons  are  needed  to
determine  the  median.  Bent  and  John  [48]  gave  a  lower  bound  of  2n
comparisons  for  median  ﬁnding,  and  Schönhage,  Paterson,  and
Pippenger  [397]  gave  an  upper  bound  of  3n.  Dor  and  Zwick  have
improved on both of these bounds. Their upper bound [123] is slightly
less  than  2.95n,  and  their  lower  bound  [124]  is  (2  +  ϵ)n,  for  a  small
positive constant ϵ, thereby improving slightly on related work by Dor
et  al.  [122].  Paterson  [354]  describes  some  of  these  results  along  with
other related work.

Problem 9-6 was inspired by a paper by Chen and Dumitrescu [84].

1 As in the footnote on page 182, you can enforce the assumption that the numbers are distinct
by converting each input value A[i] to an ordered pair (A[i], i) with (A[i], i) < (A[j], j) if either
A[i] < A[j] or A[i] = A[j] and i < j.
2 We could also use the Akra-Bazzi method from Section 4.7, which involves calculus, to solve
this  recurrence.  Indeed,  a  similar  recurrence  (4.24)  on  page  117  was  used  to  illustrate  that
method.

Part III    Data Structures

