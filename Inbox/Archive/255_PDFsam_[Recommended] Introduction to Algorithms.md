7          Quicksort

The quicksort algorithm has a worst-case running time of Θ(n2) on an
input  array  of  n  numbers.  Despite  this  slow  worst-case  running  time,
quicksort  is  often  the  best  practical  choice  for  sorting  because  it  is
remarkably  efﬁcient  on  average:  its  expected  running  time  is  Θ(n  lg  n)
when  all  numbers  are  distinct,  and  the  constant  factors  hidden  in  the
Θ(n  lg  n)  notation  are  small.  Unlike  merge  sort,  it  also  has  the
advantage of sorting in place (see page 158), and it works well even in
virtual-memory environments.

Our  study  of  quicksort  is  broken  into  four  sections.  Section  7.1
describes the algorithm and an important subroutine used by quicksort
for  partitioning.  Because  the  behavior  of  quicksort  is  complex,  we’ll
start with an intuitive discussion of its performance in Section 7.2 and
analyze  it  precisely  at  the  end  of  the  chapter.  Section  7.3  presents  a
randomized version of quicksort. When all elements are distinct,1 this
randomized  algorithm  has  a  good  expected  running  time  and  no
particular input elicits its worst-case behavior. (See Problem 7-2 for the
case  in  which  elements  may  be  equal.)  Section  7.4  analyzes  the
randomized algorithm, showing that it runs in Θ(n2) time in the worst
case and, assuming distinct elements, in expected O(n lg n) time.

7.1      Description of quicksort

Quicksort,  like  merge  sort,  applies  the  divide-and-conquer  method
introduced  in  Section  2.3.1.  Here  is  the  three-step  divide-and-conquer
process for sorting a subarray A[p : r]:

Divide by partitioning (rearranging) the array A[p : r] into two (possibly
empty) subarrays A[p : q – 1] (the low side) and A[q + 1 : r] (the high
side) such that each element in the low side of the partition is less than
or equal to the pivot A[q], which is, in turn, less than or equal to each
element in the high side. Compute the index q of the pivot as part of
this partitioning procedure.

Conquer  by  calling  quicksort  recursively  to  sort  each  of  the  subarrays

A[p : q – 1] and A[q + 1 : r].

Combine  by  doing  nothing:  because  the  two  subarrays  are  already
sorted, no work is needed to combine them. All elements in A[p : q –
1] are sorted and less than or equal to A[q], and all elements in A[q + 1
: r] are sorted and greater than or equal to the pivot A[q]. The entire
subarray A[p : r] cannot help but be sorted!

The  QUICKSORT  procedure  implements  quicksort.  To  sort  an
entire n-element array A[1 : n], the initial call is QUICKSORT (A, 1, n).

QUICKSORT(A, p, r)

1 if p < r
2

// Partition the subarray around the pivot, which ends up in A[q].
q = PARTITION(A, p, r)
QUICKSORT(A, p, q – 1)
QUICKSORT(A, q + 1, r)

// recursively sort the low side
// recursively sort the high side

3

4

5

Partitioning the array

The  key  to  the  algorithm  is  the  PARTITION  procedure  on  the  next
page, which rearranges the subarray A[p : r] in place, returning the index
of the dividing point between the two sides of the partition.

Figure  7.1  shows  how  PARTITION  works  on  an  8-element  array.
PARTITION  always  selects  the  element  x  =  A[r]  as  the  pivot.  As  the

procedure runs, each element falls into exactly one of four regions, some
of which may be empty. At the start of each iteration of the for loop in
lines 3–6, the regions satisfy certain properties, shown in Figure 7.2. We
state these properties as a loop invariant:

PARTITION(A, p, r)
1 x = A[r]
2 i = p – 1
3 for j = p to r – 1

if A[j] ≤ x

4

5

6

i = i + 1
exchange  A[i]  with

// the pivot
// highest index into the low side
//  process  each  element  other  than  the
pivot

// does this element belong on the low

side?

// index of a new slot in the low side

// put this element there

A[j]

7 exchange A[i + 1] with A[r]//  pivot  goes  just  to  the  right  of  the  low

8 return i + 1

side
// new index of the pivot

At the beginning of each iteration of the loop of lines 3–6, for
any array index k, the following conditions hold:

1. if p ≤ k ≤ i, then A[k] ≤ x (the tan region of Figure 7.2);

2. if i + 1 ≤ k ≤ j – 1, then A[k] > x (the blue region);

3. if k = r, then A[k] = x (the yellow region).

We  need  to  show  that  this  loop  invariant  is  true  prior  to  the  ﬁrst
iteration,  that  each  iteration  of  the  loop  maintains  the  invariant,  that
the  loop  terminates,  and  that  correctness  follows  from  the  invariant
when the loop terminates.

Initialization:  Prior  to  the  ﬁrst  iteration  of  the  loop,  we  have  i  =  p  –  1
and  j  =  p.  Because  no  values  lie  between  p  and  i  and  no  values  lie
between i + 1 and j – 1, the ﬁrst two conditions of the loop invariant
are  trivially  satisﬁed.  The  assignment  in  line  1  satisﬁes  the  third
condition.

Maintenance: As Figure 7.3 shows, we consider two cases, depending on
the  outcome  of  the  test  in  line  4.  Figure  7.3(a)  shows  what  happens
when A[j] > x: the only action in the loop is to increment j. After j has
been  incremented,  the  second  condition  holds  for  A[j  –  1]  and  all
other  entries  remain  unchanged.  Figure  7.3(b)  shows  what  happens
when  A[j]  ≤  x:  the  loop  increments  i,  swaps  A[i]  and  A[j],  and  then
increments  j.  Because  of  the  swap,  we  now  have  that  A[i]  ≤  x,  and
condition 1 is satisﬁed. Similarly, we also have that A[j – 1] > x, since
the  item  that  was  swapped  into  A[j  –  1]  is,  by  the  loop  invariant,
greater than x.

Termination: Since the loop makes exactly r – p iterations, it terminates,
whereupon j = r. At that point, the unexamined subarray A[j : r – 1] is
empty, and every entry in the array belongs to one of the other three
sets described by the invariant. Thus, the values in the array have been
partitioned into three sets: those less than or equal to x (the low side),
those greater than x (the high side), and a singleton set containing x
(the pivot).

Figure 7.1 The operation of PARTITION on a sample array. Array entry A[r] becomes the pivot
element x. Tan array elements all belong to the low side of the partition, with values at most x.
Blue elements belong to the high side, with values greater than x. White elements have not yet
been put into either side of the partition, and the yellow element is the pivot x. (a) The initial
array  and  variable  settings.  None  of  the  elements  have  been  placed  into  either  side  of  the
partition. (b) The value 2 is “swapped with itself ” and put into the low side. (c)–(d) The values 8
and 7 are placed into to high side. (e) The values 1 and 8 are swapped, and the low side grows. (f)
The values 3 and 7 are swapped, and the low side grows. (g)–(h) The high side of the partition
grows to include 5 and 6, and the loop terminates. (i) Line 7 swaps the pivot element so that it
lies between the two sides of the partition, and line 8 returns the pivot’s new index.

The ﬁnal two lines of PARTITION ﬁnish up by swapping the pivot
with the leftmost element greater than x, thereby moving the pivot into
its correct place in the partitioned array, and then returning the pivot’s
new index. The output of PARTITION now satisﬁes the speciﬁcations
given for the divide step. In fact, it satisﬁes a slightly stronger condition:

after line 3 of QUICKSORT, A[q] is strictly less than every element of
A[q + 1 : r].

Figure 7.2 The four regions maintained by the procedure PARTITION on a subarray A[p : r].
The tan values in A[p : i] are all less than or equal to x, the blue values in A[i + 1 : j – 1] are all
greater than x, the white values in A[j : r – 1] have unknown relationships to x, and A[r] = x.

Figure 7.3 The two cases for one iteration of procedure PARTITION. (a) If A[j] > x, the only
action  is  to  increment  j,  which  maintains  the  loop  invariant.  (b)  If  A[j]  ≤  x,  index  i  is
incremented, A[i] and A[j] are swapped, and then j is incremented. Again, the loop invariant is
maintained.

Exercise  7.1-3  asks  you  to  show  that  the  running  time  of

PARTITION on a subarray A[p : r] of n = r – p + 1 elements is Θ(n).

Exercises

7.1-1

Using Figure 7.1 as a model, illustrate the operation of PARTITION on
the array A = 〈13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11〉.

7.1-2
What  value  of  q  does  PARTITION  return  when  all  elements  in  the
subarray A[p : r] have the same value? Modify PARTITION so that q =
⌊(p  +  r)/2⌋  when  all  elements  in  the  subarray  A[p  :  r]  have  the  same
value.

7.1-3
Give  a  brief  argument  that  the  running  time  of  PARTITION  on  a
subarray of size n is Θ(n).

7.1-4
Modify QUICKSORT to sort into monotonically decreasing order.

7.2      Performance of quicksort

The  running  time  of  quicksort  depends  on  how  balanced  each
partitioning  is,  which  in  turn  depends  on  which  elements  are  used  as
pivots.  If  the  two  sides  of  a  partition  are  about  the  same  size—the
partitioning is balanced—then the algorithm runs asymptotically as fast
as  merge  sort.  If  the  partitioning  is  unbalanced,  however,  it  can  run
asymptotically  as  slowly  as  insertion  sort.  To  allow  you  to  gain  some
intuition  before  diving  into  a  formal  analysis,  this  section  informally
investigates how quicksort performs under the assumptions of balanced
versus unbalanced partitioning.

But ﬁrst, let’s brieﬂy look at the maximum amount of memory that
quicksort  requires.  Although  quicksort  sorts  in  place  according  to  the
deﬁnition on page 158, the amount of memory it uses—aside from the
array being sorted—is not constant. Since each recursive call requires a
constant  amount  of  space  on  the  runtime  stack,  outside  of  the  array
being  sorted,  quicksort  requires  space  proportional  to  the  maximum
depth of the recursion. As we’ll see now, that could be as bad as Θ(n) in
the worst case.

Worst-case partitioning

The  worst-case  behavior  for  quicksort  occurs  when  the  partitioning
produces one subproblem with n – 1 elements and one with 0 elements.
(See  Section  7.4.1.)  Let  us  assume  that  this  unbalanced  partitioning
arises in each recursive call. The partitioning costs Θ(n) time. Since the
recursive call on an array of size 0 just returns without doing anything,
T (0) = Θ(1), and the recurrence for the running time is

T (n) = T (n – 1) + T (0) + Θ(n)
= T (n – 1) + Θ(n).

By summing the costs incurred at each level of the recursion, we obtain
an  arithmetic  series  (equation  (A.3)  on  page  1141),  which  evaluates  to
Θ(n2).  Indeed,  the  substitution  method  can  be  used  to  prove  that  the
recurrence T (n) = T (n – 1) + Θ(n) has the solution T (n) = Θ(n2). (See
Exercise 7.2-1.)

Thus, if the partitioning is maximally unbalanced at every recursive
level  of  the  algorithm,  the  running  time  is  Θ(n2).  The  worst-case
running  time  of  quicksort  is  therefore  no  better  than  that  of  insertion
sort.  Moreover,  the  Θ(n2)  running  time  occurs  when  the  input  array  is
already  completely  sorted—a  situation  in  which  insertion  sort  runs  in
O(n) time.

Best-case partitioning

In
two
the  most  even  possible  split,  PARTITION  produces
subproblems,  each  of  size  no  more  than  n/2,  since  one  is  of  size  ⌊(n  –
1)/2⌋ ≤ n/2 and one of size ⌈(n – 1)/2⌉ – 1 ≤ n/2. In this case, quicksort
runs  much  faster.  An  upper  bound  on  the  running  time  can  then  be
described by the recurrence

T (n) = 2T (n/2) + Θ(n).
By  case  2  of  the  master  theorem  (Theorem  4.1  on  page  102),  this
recurrence has the solution T (n) = Θ(n lg n). Thus, if the partitioning is

equally balanced at every level of the recursion, an asymptotically faster
algorithm results.

Balanced partitioning

As the analyses in Section 7.4 will show, the average-case running time
of quicksort is much closer to the best case than to the worst case. By
appreciating how the balance of the partitioning affects the recurrence
describing the running time, we can gain an understanding of why.

Suppose,  for  example,  that  the  partitioning  algorithm  always
produces  a  9-to-1  proportional  split,  which  at  ﬁrst  blush  seems  quite
unbalanced. We then obtain the recurrence

T (n) = T (9n/10) + T (n/10) + Θ(n),
on  the  running  time  of  quicksort.  Figure  7.4  shows  the  recursion  tree
for  this  recurrence,  where  for  simplicity  the  Θ(n)  driving  function  has
been  replaced  by  n,  which  won’t  affect  the  asymptotic  solution  of  the
recurrence  (as  Exercise  4.7-1  on  page  118  justiﬁes).  Every  level  of  the
tree has cost n, until the recursion bottoms out in a base case at depth
log10 n = Θ(lg n), and then the levels have cost at most n. The recursion
terminates  at  depth  log10/9  n  =  Θ(lg  n).  Thus,  with  a  9-to-1
proportional  split  at  every  level  of  recursion,  which  intuitively  seems
highly unbalanced, quicksort runs in O(n lg n) time—asymptotically the
same as if the split were right down the middle. Indeed, even a 99-to-1
split  yields  an  O(n  lg  n)  running  time.  In  fact,  any  split  of  constant
proportionality yields a recursion tree of depth Θ(lg n), where the cost
at each level is O(n). The running time is therefore O(n lg n) whenever
the split has constant proportionality. The ratio of the split affects only
the constant hidden in the O-notation.

Figure 7.4 A recursion tree for QUICKSORT in which PARTITION always produces a 9-to-1
split, yielding a running time of O(n lg n). Nodes show subproblem sizes, with per-level costs on
the right.

Intuition for the average case

To  develop  a  clear  notion  of  the  expected  behavior  of  quicksort,  we
must  assume  something  about  how  its  inputs  are  distributed.  Because
quicksort determines the sorted order using only comparisons between
input  elements,  its  behavior  depends  on  the  relative  ordering  of  the
values  in  the  array  elements  given  as  the  input,  not  on  the  particular
values in the array. As in the probabilistic analysis of the hiring problem
in  Section  5.2,  assume  that  all  permutations  of  the  input  numbers  are
equally likely and that the elements are distinct.

When  quicksort  runs  on  a  random  input  array,  the  partitioning  is
highly unlikely to happen in the same way at every level, as our informal
analysis  has  assumed.  We  expect  that  some  of  the  splits  will  be
reasonably  well  balanced  and  that  some  will  be  fairly  unbalanced.  For
example,  Exercise  7.2-6  asks  you  to  show  that  about  80%  of  the  time
PARTITION produces a split that is at least as balanced as 9 to 1, and

about 20% of the time it produces a split that is less balanced than 9 to
1.

Figure 7.5 (a) Two levels of a recursion tree for quicksort. The partitioning at the root costs n
and produces a “bad” split: two subarrays of sizes 0 and n – 1. The partitioning of the subarray
of size n – 1 costs n – 1 and produces a “good” split: subarrays of size (n – 1)/2 – 1 and (n – 1)/2.
(b) A single level of a recursion tree that is well balanced. In both parts, the partitioning cost for
the subproblems shown with blue shading is Θ(n). Yet the subproblems remaining to be solved
in (a), shown with tan shading, are no larger than the corresponding subproblems remaining to
be solved in (b).

In  the  average  case,  PARTITION  produces  a  mix  of  “good”  and
“bad”  splits.  In  a  recursion  tree  for  an  average-case  execution  of
PARTITION,  the  good  and  bad  splits  are  distributed  randomly
throughout the tree. Suppose for the sake of intuition that the good and
bad splits alternate levels in the tree, and that the good splits are best-
case  splits  and  the  bad  splits  are  worst-case  splits.  Figure  7.5(a)  shows
the splits at two consecutive levels in the recursion tree. At the root of
the tree, the cost is n for partitioning, and the subarrays produced have
sizes n – 1 and 0: the worst case. At the next level, the subarray of size n
– 1 undergoes best-case partitioning into subarrays of size (n – 1)/2 – 1
and (n – 1)/2. Let’s assume that the base-case cost is 1 for the subarray
of size 0.

The  combination  of  the  bad  split  followed  by  the  good  split
produces  three  subarrays  of  sizes  0,  (n  –  1)/2  –  1,  and  (n  –  1)/2  at  a
combined partitioning cost of Θ(n) + Θ(n – 1) = Θ(n). This situation is
at  most  a  constant  factor  worse  than  that  in  Figure  7.5(b),  namely,
where a single level of partitioning produces two subarrays of size (n –
1)/2,  at  a  cost  of  Θ(n).  Yet  this  latter  situation  is  balanced!  Intuitively,
the Θ(n – 1) cost of the bad split in Figure 7.5(a) can be absorbed into
the Θ(n) cost of the good split, and the resulting split is good. Thus, the

running time of quicksort, when levels alternate between good and bad
splits, is like the running time for good splits alone: still O(n lg n), but
with a slightly larger constant hidden by the O-notation. We’ll analyze
the  expected  running  time  of  a  randomized  version  of  quicksort
rigorously in Section 7.4.2.

Exercises

7.2-1
Use the substitution method to prove that the recurrence T (n) = T (n –
1) + Θ(n) has the solution T (n) = Θ(n2), as claimed at the beginning of
Section 7.2.

7.2-2
What is the running time of QUICKSORT when all elements of array
A have the same value?

7.2-3
Show that the running time of QUICKSORT is Θ(n2) when the array A
contains distinct elements and is sorted in decreasing order.

7.2-4
Banks often record transactions on an account in order of the times of
the transactions, but many people like to receive their bank statements
with checks listed in order by check number. People usually write checks
in  order  by  check  number,  and  merchants  usually  cash  them  with
reasonable  dispatch.  The  problem  of  converting  time-of-transaction
ordering to check-number ordering is therefore the problem of sorting
almost-sorted
the  procedure
input.  Explain  persuasively  why
INSERTION-SORT  might  tend  to  beat  the  procedure  QUICKSORT
on this problem.

7.2-5
Suppose  that  the  splits  at  every  level  of  quicksort  are  in  the  constant
proportion  α  to  β,  where  α  +  β  =  1  and  0  <  α  ≤  β  <  1.  Show  that  the
minimum depth of a leaf in the recursion tree is approximately log1/α n

and  that  the  maximum  depth  is  approximately  log1/β  n.  (Don’t  worry
about integer round-off.)

7.2-6
Consider an array with distinct elements and for which all permutations
of the elements are equally likely. Argue that for any constant 0 < α ≤
1/2, the probability is approximately 1 – 2α that PARTITION produces
a split at least as balanced as 1 – α to α.

7.3      A randomized version of quicksort

In  exploring  the  average-case  behavior  of  quicksort,  we  have  assumed
that  all  permutations  of  the  input  numbers  are  equally  likely.  This
assumption  does  not  always  hold,  however,  as,  for  example,  in  the
situation laid out in the premise for Exercise 7.2-4. Section 5.3 showed
that judicious randomization can sometimes be added to an algorithm
to  obtain  good  expected  performance  over  all  inputs.  For  quicksort,
randomization  yields  a  fast  and  practical  algorithm.  Many  software
libraries  provide  a  randomized  version  of  quicksort  as  their  algorithm
of choice for sorting large data sets.

In Section 5.3, the RANDOMIZED-HIRE-ASSISTANT procedure
explicitly  permutes  its  input  and  then  runs  the  deterministic  HIRE-
ASSISTANT  procedure.  We  could  do  the  same  for  quicksort  as  well,
but  a  different  randomization  technique  yields  a  simpler  analysis.
Instead  of  always  using  A[r]  as  the  pivot,  a  randomized  version
randomly  chooses  the  pivot  from  the  subarray  A[p  :  r],  where  each
element  in  A[p  :  r]  has  an  equal  probability  of  being  chosen.  It  then
exchanges that element with A[r] before partitioning. Because the pivot
is  chosen  randomly,  we  expect  the  split  of  the  input  array  to  be
reasonably well balanced on average.

The changes to PARTITION and QUICKSORT are small. The new
partitioning  procedure,  RANDOMIZED-PARTITION,  simply  swaps
before  performing  the  partitioning.  The  new  quicksort  procedure,
RANDOMIZED-QUICKSORT,  calls  RANDOMIZED-PARTITION

instead  of  PARTITION.  We’ll  analyze  this  algorithm  in  the  next
section.

RANDOMIZED-PARTITION(A, p, r)
1 i = RANDOM(p, r)
2 exchange A[r] with A[i]
3 return PARTITION(A, p, r)

RANDOMIZED-QUICKSORT(A, p, r)
1 if p < r
2

q = RANDOMIZED-PARTITION(A, p, r)
RANDOMIZED-QUICKSORT(A, p, q – 1)
RANDOMIZED-QUICKSORT(A, q + 1, r)

3

4

Exercises

7.3-1
Why  do  we  analyze  the  expected  running  time  of  a  randomized
algorithm and not its worst-case running time?

7.3-2
When RANDOMIZED-QUICKSORT runs, how many calls are made
to  the  random-number  generator  RANDOM  in  the  worst  case?  How
about in the best case? Give your answer in terms of Θ-notation.

7.4      Analysis of quicksort

Section 7.2 gave some intuition for the worst-case behavior of quicksort
and  for  why  we  expect  the  algorithm  to  run  quickly.  This  section
analyzes  the  behavior  of  quicksort  more  rigorously.  We  begin  with  a
to  either  QUICKSORT  or
worst-case  analysis,  which  applies
RANDOMIZED-QUICKSORT, and conclude with an analysis of the
expected running time of RANDOMIZED-QUICKSORT.

7.4.1    Worst-case analysis

We saw in Section 7.2 that a worst-case split at every level of recursion
in  quicksort  produces  a  Θ(n2)  running  time,  which,  intuitively,  is  the
worst-case running time of the algorithm. We now prove this assertion.

We’ll use the substitution method (see Section 4.3) to show that the
running time of quicksort is O(n2). Let T (n) be the worst-case time for
the  procedure  QUICKSORT  on  an  input  of  size  n.  Because  the
procedure PARTITION produces two subproblems with total size n – 1,
we obtain the recurrence

We  guess  that  T  (n)  ≤  cn2  for  some  constant  c  >  0.  Substituting  this
guess into recurrence (7.1) yields

T (n) ≤ max {cq2 + c(n – 1 – q)2 : 0 ≤ q ≤ n – 1} + Θ(n)
= c · max {q2 + (n – 1 – q)2 : 0 ≤ q ≤ n – 1} + Θ(n).

Let’s focus our attention on the maximization. For q = 0, 1, … , n –

1, we have

q2 + (n – 1 – q)2 = q2 + (n – 1)2 – 2q(n – 1) + q2

= (n – 1)2 + 2q(q – (n – 1))
≤ (n – 1)2

because q ≤ n – 1 implies that 2q(q – (n – 1)) ≤ 0. Thus every term in the
maximization is bounded by (n – 1)2.

Continuing with our analysis of T (n), we obtain

T (n) ≤ c(n – 1)2 + Θ(n)

≤ cn2 – c(2n – 1) + Θ(n)
≤ cn2,

by picking the constant c large enough that the c(2n – 1) term dominates
the  Θ(n)  term.  Thus  T  (n)  =  O(n2).  Section  7.2  showed  a  speciﬁc  case
where  quicksort  takes  Ω(n2)  time:  when  partitioning  is  maximally
unbalanced. Thus, the worst-case running time of quicksort is Θ(n2).

7.4.2    Expected running time
We  have  already  seen  the  intuition  behind  why  the  expected  running
time of RANDOMIZED-QUICKSORT is O(n lg n): if, in each level of
recursion, the split induced by RANDOMIZED-PARTITION puts any
constant fraction of the elements on one side of the partition, then the
recursion  tree  has  depth  Θ(lg  n)  and  O(n)  work  is  performed  at  each
level.  Even  if  we  add  a  few  new  levels  with  the  most  unbalanced  split
possible  between  these  levels,  the  total  time  remains  O(n  lg  n).  We  can
analyze  the  expected  running  time  of  RANDOMIZED-QUICKSORT
precisely by ﬁrst understanding how the partitioning procedure operates
and then using this understanding to derive an O(n lg n) bound on the
expected running time. This upper bound on the expected running time,
combined  with  the  Θ(n  lg  n)  best-case  bound  we  saw  in  Section  7.2,
yields a Θ(n lg n) expected running time. We assume throughout that the
values of the elements being sorted are distinct.

Running time and comparisons

can

respects.  We

The  QUICKSORT  and  RANDOMIZED-QUICKSORT  procedures
differ  only  in  how  they  select  pivot  elements.  They  are  the  same  in  all
therefore  analyze  RANDOMIZED-
other
QUICKSORT  by  considering  the  QUICKSORT  and  PARTITION
procedures,  but  with  the  assumption  that  pivot  elements  are  selected
randomly from the subarray passed to RANDOMIZED-PARTITION.
Let’s start by relating the asymptotic running time of QUICKSORT to
the  number  of  times  elements  are  compared  (all  in  line  4  of
PARTITION),  understanding  that  this  analysis  also  applies  to
RANDOMIZED-QUICKSORT.  Note  that  we  are  counting  the
number of times that array elements are compared, not comparisons of
indices.

Lemma 7.1
The running time of QUICKSORT on an n-element array is O(n + X),
where X is the number of element comparisons performed.

Proof      The  running  time  of  QUICKSORT  is  dominated  by  the  time
spent in the PARTITION procedure. Each time PARTITION is called,
it selects a pivot element, which is never included in any future recursive
calls to QUICKSORT and PARTITION. Thus, there can be at most n
calls  to  PARTITION  over  the  entire  execution  of  the  quicksort
it  also
algorithm.  Each  time  QUICKSORT  calls  PARTITION,
recursively  calls  itself  twice,  so  there  are  at  most  2n  calls  to  the
QUICKSORT procedure itself.

One  call  to  PARTITION  takes  O(1)  time  plus  an  amount  of  time
that is proportional to the number of iterations of the for loop in lines
3–6. Each iteration of this for loop performs one comparison in line 4,
comparing  the  pivot  element  to  another  element  of  the  array  A.
Therefore,  the  total  time  spent  in  the  for  loop  across  all  executions  is
proportional to X. Since there are at most n calls to PARTITION and
the time spent outside the for loop is O(1) for each call, the total time
spent  in  PARTITION  outside  of  the  for  loop  is  O(n).  Thus  the  total
time for quicksort is O(n + X).

▪

Our goal for analyzing RANDOMIZED-QUICKSORT, therefore, is
to compute the expected value E [X] of the random variable X denoting
the total number of comparisons performed in all calls to PARTITION.
To do so, we must understand when the quicksort algorithm compares
two  elements  of  the  array  and  when  it  does  not.  For  ease  of  analysis,
let’s  index  the  elements  of  the  array  A  by  their  position  in  the  sorted
output,  rather  than  their  position  in  the  input.  That  is,  although  the
elements in A may start out in any order, we’ll refer to them by z1, z2,
…  ,  zn,  where  z1  <  z2  <  ⋯  <  zn,  with  strict  inequality  because  we
assume that all elements are distinct. We denote the set {zi, zi + 1, … ,
zj} by Zij.

The next lemma characterizes when two elements are compared.

Lemma 7.2
During  the  execution  of  RANDOMIZED-QUICKSORT  on  an  array
of n distinct elements z1 < z2 < ⋯ < zn, an element zi is compared with
an element zj, where i < j, if and only if one of them is chosen as a pivot
before any other element in the set Zij. Moreover, no two elements are
ever compared twice.

Proof   Let’s look at the ﬁrst time that an element x ∈ Zij is chosen as a
pivot  during  the  execution  of  the  algorithm.  There  are  three  cases  to
consider. If x is neither zi nor zj—that is, zi < x < zj—then zi and zj are
not  compared  at  any  subsequent  time,  because  they  fall  into  different
sides of the partition around x. If x = zi, then PARTITION compares zi
with  every  other  item  in  Zij.  Similarly,  if  x  =  zj,  then  PARTITION
compares zj with every other item in Zij. Thus, zi and zj are compared if
and only if the ﬁrst element to be chosen as a pivot from Zij is either zi
or zj. In the latter two cases, where one of zi and zj is chosen as a pivot,
since  the  pivot  is  removed  from  future  comparisons,  it  is  never
compared again with the other element.

▪

As an example of this lemma, consider an input to quicksort of the
numbers  1  through  10  in  some  arbitrary  order.  Suppose  that  the  ﬁrst
pivot  element  is  7.  Then  the  ﬁrst  call  to  PARTITION  separates  the
numbers into two sets: {1, 2, 3, 4, 5, 6} and {8, 9, 10}. In the process,
the pivot element 7 is compared with all other elements, but no number
from the ﬁrst set (e.g., 2) is or ever will be compared with any number
from the second set (e.g., 9). The values 7 and 9 are compared because 7
is the ﬁrst item from Z7,9 to be chosen as a pivot. In contrast, 2 and 9
are never compared because the ﬁrst pivot element chosen from Z2,9 is
7.

The  next  lemma  gives  the  probability  that  two  elements  are

compared.

Lemma 7.3

execution  of

the  procedure  RANDOMIZED-
Consider  an
QUICKSORT  on  an  array  of  n  distinct  elements  z1  <  z2  <  ⋯  <  zn.
Given two arbitrary elements zi and zj where i < j, the probability that
they are compared is 2/(j – i + 1).

Proof      Let’s  look  at  the  tree  of  recursive  calls  that  RANDOMIZED-
QUICKSORT  makes,  and  consider  the  sets  of  elements  provided  as
input to each call. Initially, the root set contains all the elements of Zij,
since the root set contains every element in A. The elements belonging
to  Zij  all  stay  together  for  each  recursive  call  of  RANDOMIZED-
QUICKSORT  until  PARTITION  chooses  some  element  x  ∈  Zij  as  a
pivot. From that point on, the pivot x appears in no subsequent input
set. The ﬁrst time that RANDOMIZED-SELECT chooses a pivot x ∈
Zij from a set containing all the elements of Zij, each element in Zij is
equally likely to be x because the pivot is chosen uniformly at random.
Since  |Zij|  =  j  –  i  +  1,  the  probability  is  1/(j  –  i  +  1)  that  any  given
element in Zij is the ﬁrst pivot chosen from Zij. Thus, by Lemma 7.2, we
have

Pr  {zi  is  compared  with
zj}

=

Pr  {zi  or  zj  is  the  ﬁrst  pivot  chosen  from
Zij}

= Pr {zi is the ﬁrst pivot chosen from Zij}

+  Pr  {zj  is  the  ﬁrst  pivot  chosen  from
Zij}

=

,

where the second line follows from the ﬁrst because the two events are
mutually exclusive.

▪

We can now complete the analysis of randomized quicksort.

Theorem 7.4

The  expected  running  time  of  RANDOMIZED-QUICKSORT  on  an
input of n distinct elements is O(n lg n).

Proof      The  analysis  uses  indicator  random  variables  (see  Section  5.2).
Let the n distinct elements be z1 < z2 < ⋯ < zn, and for 1 ≤ i < j ≤ n,
deﬁne  the  indicator  random  variable  Xij  =  I  {zi  is  compared  with  zj}.
From  Lemma  7.2,  each  pair  is  compared  at  most  once,  and  so  we  can
express X as follows:

By taking expectations of both sides and using linearity of expectation
(equation (C.24) on page 1192) and Lemma 5.1 on page 130, we obtain

We can evaluate this sum using a change of variables (k = j – i) and the
bound on the harmonic series in equation (A.9) on page 1142:

This  bound  and  Lemma  7.1  allow  us  to  conclude  that  the  expected
running time of RANDOMIZED-QUICKSORT is O(n lg n) (assuming
that the element values are distinct).

▪

Exercises

7.4-1
Show that the recurrence

T (n) = max {T (q) + T (n – q – 1) : 0 ≤ q ≤ n – 1} + Θ(n)
has a lower bound of T (n) = Ω (n2).

7.4-2
Show that quicksort’s best-case running time is Ω(n lg n).

7.4-3
Show that the expression q2 + (n – q – 1)2 achieves its maximum value
over q = 0, 1, … , n – 1 when q = 0 or q = n – 1.

7.4-4
Show  that  RANDOMIZED-QUICKSORT’s  expected  running  time  is
Ω(n lg n).

7.4-5

Coarsening the recursion, as we did in Problem 2-1 for merge sort, is a
common way to improve the running time of quicksort in practice. We
modify the base case of the recursion so that if the array has fewer than
k  elements,  the  subarray  is  sorted  by  insertion  sort,  rather  than  by
continued  recursive  calls  to  quicksort.  Argue  that  the  randomized
version  of  this  sorting  algorithm  runs  in  O(nk  +  n  lg(n/k))  expected
time. How should you pick k, both in theory and in practice?

★ 7.4-6
Consider  modifying  the  PARTITION  procedure  by  randomly  picking
three  elements  from  subarray  A[p  :  r]  and  partitioning  about  their
median  (the  middle  value  of  the  three  elements).  Approximate  the
probability of getting worse than an α-to-(1–α) split, as a function of α
in the range 0 < α < 1/2.

Problems

7-1     Hoare partition correctness
The  version  of  PARTITION  given  in  this  chapter  is  not  the  original
partitioning  algorithm.  Here  is  the  original  partitioning  algorithm,
which is due to C. A. R. Hoare.

HOARE-PARTITION(A, p, r)
  1 x = A[p]
i = p – 1
  2
j = r + 1
  3
  4 while TRUE
  5

repeat

  6

  7

  8

  9

10

11

12

j = j – 1
until A[j] ≤ x
repeat

i = i + 1
until A[i] ≥ x
if i < j

exchange A[i] with A[j]

13

else return j

a. Demonstrate the operation of HOARE-PARTITION on the array A
= 〈13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21〉, showing the values of the array
and the indices i and j after each iteration of the while loop in lines 4–
13.

b. Describe how the PARTITION procedure in Section 7.1 differs from

HOARE-PARTITION when all elements in A[p : r] are equal.
Describe a practical advantage of HOARE-PARTITION over
PARTITION for use in quicksort.

The  next  three  questions  ask  you  to  give  a  careful  argument  that  the
procedure  HOARE-PARTITION
is  correct.  Assuming  that  the
subarray A[p : r] contains at least two elements, prove the following:

c. The indices i and j are such that the procedure never accesses an

element of A outside the subarray A[p : r].

d. When HOARE-PARTITION terminates, it returns a value j such that

p ≤ j < r.

e. Every element of A[p : j] is less than or equal to every element of A[j

+ 1 : r] when HOARE-PARTITION terminates.

The  PARTITION  procedure  in  Section  7.1  separates  the  pivot  value
(originally  in  A[r])  from  the  two  partitions  it  forms.  The  HOARE-
PARTITION  procedure,  on  the  other  hand,  always  places  the  pivot
value (originally in A[p]) into one of the two partitions A[p : j] and A[j +
1 : r]. Since p ≤ j < r, neither partition is empty.

f. Rewrite the QUICKSORT procedure to use HOARE-PARTITION.

7-2     Quicksort with equal element values
The analysis of the expected running time of randomized quicksort in
Section 7.4.2 assumes that all element values are distinct. This problem
examines what happens when they are not.

a. Suppose that all element values are equal. What is randomized

quicksort’s running time in this case?

b. The PARTITION procedure returns an index q such that each

element of A[p : q – 1] is less than or equal to A[q] and each element
of A[q + 1 : r] is greater than A[q]. Modify the PARTITION
procedure to produce a procedure PARTITION′ (A, p, r), which
permutes the elements of A[p : r] and returns two indices q and t,
where p ≤ q ≤ t ≤ r, such that

all elements of A[q : t] are equal,
each element of A[p : q – 1] is less than A[q], and
each element of A[t + 1 : r] is greater than A[q].

Like PARTITION, your PARTITION′ procedure should take Θ(r – p)
time.

c. Modify the RANDOMIZED-PARTITION procedure to call

PARTITION′, and name the new procedure RANDOMIZED-
PARTITION′. Then modify the QUICKSORT procedure to produce
a procedure QUICKSORT′ (A, p, r) that calls RANDOMIZED-
PARTITION′ and recurses only on partitions where elements are not
known to be equal to each other.

d. Using QUICKSORT′, adjust the analysis in Section 7.4.2 to avoid the

assumption that all elements are distinct.

7-3     Alternative quicksort analysis

An  alternative  analysis  of  the  running  time  of  randomized  quicksort
focuses on the expected running time of each individual recursive call to
RANDOMIZED-QUICKSORT,  rather  than  on  the  number  of
comparisons performed. As in the analysis of Section 7.4.2, assume that
the values of the elements are distinct.

a. Argue that, given an array of size n, the probability that any

particular element is chosen as the pivot is 1/n. Use this probability to
deﬁne indicator random variables Xi = I {ith smallest element is
chosen as the pivot}. What is E [Xi]?

b. Let T (n) be a random variable denoting the running time of

quicksort on an array of size n. Argue that

c. Show how to rewrite equation (7.2) as

d. Show that

for n ≥ 2. (Hint: Split the summation into two parts, one summation
for q = 1, 2, … , ⌈n/2⌉ – 1 and one summation for q = ⌈n/2⌉ , … , n –
1.)

e. Using the bound from equation (7.4), show that the recurrence in

equation (7.3) has the solution E [T (n)] = O(n lg n). (Hint: Show, by
substitution, that E [T (n)] ≤ an lg n for sufﬁciently large n and for
some positive constant a.)

7-4     Stooge sort
Professors  Howard,  Fine,  and  Howard  have  proposed  a  deceptively
simple  sorting  algorithm,  named  stooge  sort  in  their  honor,  appearing
on the following page.

a. Argue that the call STOOGE-SORT(A, 1, n) correctly sorts the array

A[1 : n].

b. Give a recurrence for the worst-case running time of STOOGE-

SORT and a tight asymptotic (Θ-notation) bound on the worst-case
running time.

c. Compare the worst-case running time of STOOGE-SORT with that

of insertion sort, merge sort, heapsort, and quicksort. Do the
professors deserve tenure?

STOOGE-SORT(A, p, r)

1

2

3

4

5

6

7

if A[p] > A[r]

exchange A[p] with A[r]

if p + 1 < r

k = ⌊(r – p + 1)/3⌋
STOOGE-SORT(A, p, r

// round down
// ﬁrst two-thirds

– k)

STOOGE-SORT(A,  p

// last two-thirds

+ k, r)

STOOGE-SORT(A, p, r

– k)

//  ﬁrst  two-thirds
again

7-5 Stack depth for quicksort
The  QUICKSORT  procedure  of  Section  7.1  makes  two  recursive  calls
to itself. After QUICKSORT calls PARTITION, it recursively sorts the
low side of the partition and then it recursively sorts the high side of the
partition.  The  second  recursive  call  in  QUICKSORT  is  not  really
necessary,  because  the  procedure  can  instead  use  an  iterative  control
structure.  This
tail-recursion
elimination, is provided automatically by good compilers. Applying tail-
the  TRE-
recursion  elimination
QUICKSORT procedure.

transforms  QUICKSORT

transformation

technique,

called

into

TRE-QUICKSORT(A, p, r)
1 while p < r
2

// Partition and then sort the low side.
q = PARTITION(A, p, r)
TRE-QUICKSORT(A, p, q – 1)
p = q + 1

3

4

5

a. Argue that TRE-QUICKSORT(A, 1, n) correctly sorts the array A[1 :

n].

Compilers  usually  execute  recursive  procedures  by  using  a  stack  that
contains pertinent information, including the parameter values, for each
recursive call. The information for the most recent call is at the top of
the stack, and the information for the initial call is at the bottom. When
a procedure is called, its information is pushed onto the stack, and when
it  terminates,  its  information  is  popped.  Since  we  assume  that  array
parameters  are  represented  by  pointers,  the  information  for  each
procedure call on the stack requires O(1) stack space. The stack depth is
the  maximum  amount  of  stack  space  used  at  any  time  during  a
computation.

b. Describe a scenario in which TRE-QUICKSORT’s stack depth is

Θ(n) on an n-element input array.

c. Modify TRE-QUICKSORT so that the worst-case stack depth is Θ(lg
n). Maintain the O(n lg n) expected running time of the algorithm.

7-6     Median-of-3 partition
One  way  to  improve  the  RANDOMIZED-QUICKSORT  procedure  is
to  partition  around  a  pivot  that  is  chosen  more  carefully  than  by
picking  a  random  element  from  the  subarray.  A  common  approach  is
the  median-of-3  method:  choose  the  pivot  as  the  median  (middle
element)  of  a  set  of  3  elements  randomly  selected  from  the  subarray.
(See Exercise 7.4-6.) For this problem, assume that the n elements in the
input  subarray  A[p  :  r]  are  distinct  and  that  n  ≥  3.  Denote  the  sorted
version of A[p : r] by z1, z2, … , zn. Using the median-of-3 method to
choose the pivot element x, deﬁne pi = Pr {x = zi}.

a. Give an exact formula for pi as a function of n and i for i = 2, 3, … , n

– 1. (Observe that p1 = pn = 0.)

b. By what amount does the median-of-3 method increase the likelihood
of choosing the pivot to be x = z⌊(n + 1)/2⌋, the median of A[p : r],

compared with the ordinary implementation? Assume that n → ∞,
and give the limiting ratio of these probabilities.

c. Suppose that we deﬁne a “good” split to mean choosing the pivot as x

= zi, where n/3 ≤ i ≤ 2n/3. By what amount does the median-of-3
method increase the likelihood of getting a good split compared with
the ordinary implementation? (Hint: Approximate the sum by an
integral.)

d. Argue that in the Ω(n lg n) running time of quicksort, the median-of-

3 method affects only the constant factor.

7-7     Fuzzy sorting of intervals
Consider  a  sorting  problem  in  which  you  do  not  know  the  numbers
exactly. Instead, for each number, you know an interval on the real line
to which it belongs. That is, you are given n closed intervals of the form
[ai, bi], where ai ≤ bi. The goal is to fuzzy-sort these intervals: to produce
a permutation 〈i1, i2, … , in〉 of the intervals such that for j = 1, 2, … ,
n, there exist

 satisfying c1 ≤ c2 ≤ ⋯ ≤ cn.

a. Design a randomized algorithm for fuzzy-sorting n intervals. Your
algorithm should have the general structure of an algorithm that
quicksorts the left endpoints (the ai values), but it should take
advantage of overlapping intervals to improve the running time. (As
the intervals overlap more and more, the problem of fuzzy-sorting the
intervals becomes progressively easier. Your algorithm should take
advantage of such overlapping, to the extent that it exists.)

b. Argue that your algorithm runs in Θ(n lg n) expected time in general,
but runs in Θ(n) expected time when all of the intervals overlap (i.e.,
when there exists a value x such that x ∈ [ai, bi] for all i). Your
algorithm should not be checking for this case explicitly, but rather, its
performance should naturally improve as the amount of overlap
increases.

Chapter notes

Quicksort was invented by Hoare [219], and his version of PARTITION
appears in Problem 7-1. Bentley [51, p. 117] attributes the PARTITION
procedure given in Section 7.1 to N. Lomuto. The analysis in Section 7.4
based  on  an  analysis  due  to  Motwani  and  Raghavan  [336].  Sedgewick
[401]  and  Bentley  [51]  provide  good  references  on  the  details  of
implementation and how they matter.

McIlroy  [323]  shows  how  to  engineer  a  “killer  adversary”  that
produces an array on which virtually any implementation of quicksort
takes Θ(n2) time.

1 You can enforce the assumption that the values in an array A are distinct at the cost of Θ(n)
additional space and only constant overhead in running time by converting each input value A[i]
to an ordered pair (A[i], i) with (A[i], i) < (A[j], j) if A[i] < A[j] or if A[i] = A[j] and i < j. There
are also more practical variants of quicksort that work well when elements are not distinct.

