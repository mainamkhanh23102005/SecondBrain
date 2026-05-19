Introduction

This  part  presents  several  algorithms  that  solve  the  following  sorting
problem:

Input: A sequence of n numbers 〈a1, a2, … , an〉.

Output: A permutation (reordering)

 of the input sequence

such that

.

The  input  sequence  is  usually  an  n-element  array,  although  it  may  be
represented in some other fashion, such as a linked list.

The structure of the data
In practice, the numbers to be sorted are rarely isolated values. Each is
usually part of a collection of data called a record. Each record contains
a  key,  which  is  the  value  to  be  sorted.  The  remainder  of  the  record
consists of satellite data, which are usually carried around with the key.
In  practice,  when  a  sorting  algorithm  permutes  the  keys,  it  must

permute  the  satellite  data  as  well.  If  each  record  includes  a  large
amount of satellite data, it often pays to permute an array of pointers
to the records rather than the records themselves in order to minimize
data movement.

In  a  sense,  it  is  these  implementation  details  that  distinguish  an
algorithm from a full-blown program. A sorting algorithm describes the
method  to  determine  the  sorted  order,  regardless  of  whether  what’s
being  sorted  are  individual  numbers  or  large  records  containing  many
bytes of satellite data. Thus, when focusing on the problem of sorting,
we typically assume that the input consists only of numbers. Translating
an algorithm for sorting numbers into a program for sorting records is
conceptually straightforward, although in a given engineering situation
other subtleties may make the actual programming task a challenge.

Why sorting?

Many computer scientists consider sorting to be the most fundamental
problem in the study of algorithms. There are several reasons:

Sometimes  an  application  inherently  needs  to  sort  information.
For example, in order to prepare customer statements, banks need
to sort checks by check number.

Algorithms often use sorting as a key subroutine. For example, a
program  that  renders  graphical  objects  which  are  layered  on  top
of  each  other  might  have  to  sort  the  objects  according  to  an
“above” relation so that it can draw these objects from bottom to
top. We will see numerous algorithms in this text that use sorting
as a subroutine.

We  can  draw  from  among  a  wide  variety  of  sorting  algorithms,
and they employ a rich set of techniques. In fact, many important
techniques  used  throughout  algorithm  design  appear  in  sorting
algorithms  that  have  been  developed  over  the  years.  In  this  way,
sorting is also a problem of historical interest.

We can prove a nontrivial lower bound for sorting (as we’ll do in
Chapter  8).  Since  the  best  upper  bounds  match  the  lower  bound
asymptotically,  we  can  conclude  that  certain  of  our  sorting

algorithms are asymptotically optimal. Moreover, we can use the
lower bound for sorting to prove lower bounds for various other
problems.

Many  engineering  issues  come  to  the  fore  when  implementing
sorting  algorithms.  The  fastest  sorting  program  for  a  particular
situation  may  depend  on  many  factors,  such  as  prior  knowledge
about  the  keys  and  satellite  data,  the  memory  hierarchy  (caches
and  virtual  memory)  of  the  host  computer,  and  the  software
environment.  Many  of  these  issues  are  best  dealt  with  at  the
algorithmic level, rather than by “tweaking” the code.

Sorting algorithms

We  introduced  two  algorithms  that  sort  n  real  numbers  in  Chapter  2.
Insertion sort takes Θ(n2) time in the worst case. Because its inner loops
are  tight,  however,  it  is  a  fast  sorting  algorithm  for  small  input  sizes.
Moreover,  unlike  merge  sort,  it  sorts  in  place,  meaning  that  at  most  a
constant number of elements of the input array are ever stored outside
the  array,  which  can  be  advantageous  for  space  efﬁciency.  Merge  sort
has  a  better  asymptotic  running  time,  Θ(n  lg  n),  but  the  MERGE
procedure  it  uses  does  not  operate  in  place.  (We’ll  see  a  parallelized
version of merge sort in Section 26.3.)

This  part  introduces  two  more  algorithms  that  sort  arbitrary  real
numbers. Heapsort, presented in Chapter 6, sorts n numbers in place in
O(n lg n) time. It uses an important data structure, called a heap, which
can also implement a priority queue.

Quicksort, in Chapter 7, also sorts n numbers in place, but its worst-
case  running  time  is  Θ(n2).  Its  expected  running  time  is  Θ(n  lg  n),
however,  and  it  generally  outperforms  heapsort  in  practice.  Like
insertion  sort,  quicksort  has  tight  code,  and  so  the  hidden  constant
factor in its running time is small. It is a popular algorithm for sorting
large arrays.

Insertion  sort,  merge  sort,  heapsort,  and  quicksort  are  all
comparison sorts: they determine the sorted order of an input array by
comparing elements. Chapter 8 begins by introducing the decision-tree

model  in  order  to  study  the  performance  limitations  of  comparison
sorts.  Using  this  model,  we  prove  a  lower  bound  of  Ω(n  lg  n)  on  the
worst-case  running  time  of  any  comparison  sort  on  n  inputs,  thus
showing  that  heapsort  and  merge  sort  are  asymptotically  optimal
comparison sorts.

Chapter  8  then  goes  on  to  show  that  we  might  be  able  to  beat  this
lower bound of Ω(n lg n) if an algorithm can gather information about
the sorted order of the input by means other than comparing elements.
The  counting  sort  algorithm,  for  example,  assumes  that  the  input
numbers  belong  to  the  set  {0,  1,  …  ,  k}.  By  using  array  indexing  as  a
tool for determining relative order, counting sort can sort n numbers in
Θ(k + n) time. Thus, when k = O(n), counting sort runs in time that is
linear in the size of the input array. A related algorithm, radix sort, can
be used to extend the range of counting sort. If there are n integers to
sort,  each  integer  has  d  digits,  and  each  digit  can  take  on  up  to  k
possible values, then radix sort can sort the numbers in Θ(d(n + k)) time.
When  d  is  a  constant  and  k  is  O(n),  radix  sort  runs  in  linear  time.  A
third  algorithm,  bucket  sort,  requires  knowledge  of  the  probabilistic
distribution  of  numbers  in  the  input  array.  It  can  sort  n  real  numbers
uniformly  distributed  in  the  half-open  interval  [0,  1)  in  average-case
O(n) time.

The table on the following page summarizes the running times of the
sorting  algorithms  from  Chapters  2  and  6–8.  As  usual,  n  denotes  the
number of items to sort. For counting sort, the items to sort are integers
in  the  set  {0,  1,  …  ,  k}.  For  radix  sort,  each  item  is  a  d-digit  number,
where each digit takes on k possible values. For bucket sort, we assume
that  the  keys  are  real  numbers  uniformly  distributed  in  the  half-open
interval [0, 1). The rightmost column gives the average-case or expected
running  time,  indicating  which  one  it  gives  when  it  differs  from  the
worst-case  running  time.  We  omit  the  average-case  running  time  of
heapsort because we do not analyze it in this book.

Algorithm

Worst-case
running time

Average-case/expected
running time

Θ(n2)

Θ(n2)

Insertion
sort
Merge sort
Heapsort

Quicksort

Θ(n lg n)
O(n lg n)
Θ(n2)
Θ(k + n)

Counting
sort
Radix sort
Bucket sort Θ(n2)

Θ(d(n + k))

Θ(n lg n)
—
Θ(n lg n) (expected)

Θ(k + n)

Θ(d(n + k))
Θ(n) (average-case)

Order statistics
The ith order statistic of a set of n numbers is the ith smallest number in
the  set.  You  can,  of  course,  select  the  ith  order  statistic  by  sorting  the
input and indexing the ith element of the output. With no assumptions
about the input distribution, this method runs in Ω(n lg n) time, as the
lower bound proved in Chapter 8 shows.

Chapter  9  shows  how  to  ﬁnd  the  ith  smallest  element  in  O(n)  time,
even  when  the  elements  are  arbitrary  real  numbers.  We  present  a
randomized algorithm with tight pseudocode that runs in Θ(n2) time in
the worst case, but whose expected running time is O(n). We also give a
more complicated algorithm that runs in O(n) worst-case time.

Background
Although most of this part does not rely on difﬁcult mathematics, some
sections do require mathematical sophistication. In particular, analyses
of  quicksort,  bucket  sort,  and  the  order-statistic  algorithm  use
probability,  which  is  reviewed  in  Appendix  C,  and  the  material  on
probabilistic analysis and randomized algorithms in Chapter 5.

