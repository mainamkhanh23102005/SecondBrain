27        Online Algorithms

Most  problems  described  in  this  book  have  assumed  that  the  entire
input  was  available  before  the  algorithm  executes.  In  many  situations,
however,  the  input  becomes  available  not  in  advance,  but  only  as  the
algorithm executes. This idea was implicit in much of the discussion of
data  structures  in  Part  III.  The  reason  that  you  want  to  design,  for
example,  a  data  structure  that  can  handle  n  INSERT,  DELETE,  and
SEARCH  operations  in  O(lg  n)  time  per  operation  is  most  likely
because  you  are  going  to  receive  n  such  operation  requests  without
knowing in advance what operations will be coming. This idea was also
implicit  in  amortized  analysis  in  Chapter  16,  where  we  saw  how  to
maintain  a  table  that  can  grow  or  shrink  in  response  to  a  sequence  of
insertion  and  deletion  operations,  yet  with  a  constant  amortized  cost
per operation.

An online algorithm receives its input progressively over time, rather
than  having  the  entire  input  available  at  the  start,  as  in  an  ofﬂine
algorithm.  Online  algorithms  pertain  to  many  situations  in  which
information  arrives  gradually.  A  stock  trader  must  make  decisions
today, without knowing what the prices will be tomorrow, yet wants to
achieve  good  returns.  A  computer  system  must  schedule  arriving  jobs
without knowing what work will need to be done in the future. A store
must  decide  when  to  order  more  inventory  without  knowing  what  the
future  demand  will  be.  A  driver  for  a  ride-hailing  service  must  decide
whether to pick up a fare without knowing who will request rides in the
future.  In  each  of  these  situations,  and  many  more,  algorithmic
decisions must be made without knowledge of the future.

There  are  several  approaches  for  dealing  with  unknown  future
inputs. One approach is to form a probabilistic model of future inputs
and  design  an  algorithm  that  assumes  future  inputs  conform  to  the
model. This technique is common, for example, in the ﬁeld of queuing
theory, and it is also related to machine learning. Of course, you might
not  be  able  to  develop  a  workable  probabilistic  model,  or  even  if  you
can, some inputs might not conform to it. This chapter takes a different
approach.  Instead  of  assuming  anything  about  the  future  input,  we
employ  a  conservative  strategy  of  limiting  how  poor  a  solution  any
input can entail.

This  chapter,  therefore,  adopts  a  worst-case  approach,  designing
online  algorithms  that  guarantee  the  quality  of  the  solution  for  all
possible  future  inputs.  We’ll  analyze  online  algorithms  by  comparing
the solution produced by the online algorithm with a solution produced
by  an  optimal  algorithm  that  knows  the  future  inputs,  and  taking  a
worst-case  ratio  over  all  possible  instances.  We  call  this  methodology
competitive  analysis.  We’ll  use  a  similar  approach  when  we  study
approximation  algorithms  in  Chapter  35,  where  we’ll  compare  the
solution  returned  by  an  algorithm  that  might  be  suboptimal  with  the
value of the optimal solution, and determine a worst-case ratio over all
possible instances.

We start with a “toy” problem: deciding between whether to take the
introduce  the  basic
elevator  or  the  stairs.  This  problem  will
methodology  of  thinking  about  online  algorithms  and  how  to  analyze
them  via  competitive  analysis.  We  will  then  look  at  two  problems  that
use  competitive  analysis.  The  ﬁrst  is  how  to  maintain  a  search  list  so
that the access time is not too large, and the second is about strategies
for deciding which cache blocks to evict from a cache or other kind of
fast computer memory.

27.1    Waiting for an elevator

Our  ﬁrst  example  of  an  online  algorithm  models  a  problem  that  you
likely  have  encountered  yourself:  whether  you  should  wait  for  an
elevator  to  arrive  or  just  take  the  stairs.  Suppose  that  you  enter  a

building  and  wish  to  visit  an  ofﬁce  that  is  k  ﬂoors  up.  You  have  two
choices:  walk  up  the  stairs  or  take  the  elevator.  Let’s  assume,  for
convenience,  that  you  can  climb  the  stairs  at  the  rate  of  one  ﬂoor  per
minute. The elevator travels much faster than you can climb the stairs: it
can ascend all k ﬂoors in just one minute. Your dilemma is that you do
not know how long it will take for the elevator to arrive at the ground
ﬂoor and pick you up. Should you take the elevator or the stairs? How
do you decide?

Let’s  analyze  the  problem.  Taking  the  stairs  takes  k  minutes,  no
matter  what.  Suppose  you  know  that  the  elevator  takes  at  most  B  −  1
minutes to arrive for some value of B that is considerably higher than k.
(The  elevator  could  be  going  up  when  you  call  for  it  and  then  stop  at
several ﬂoors on its way down.) To keep things simple, let’s also assume
that  the  number  of  minutes  for  the  elevator  to  arrive  is  an  integer.
Therefore,  waiting  for  the  elevator  and  taking  it  k  ﬂoors  up  takes
anywhere from one minute (if the elevator is already at the ground ﬂoor)
to (B − 1) + 1 = B minutes (the worst case). Although you know B and
k,  you  don’t  know  how  long  the  elevator  will  take  to  arrive  this  time.
You  can  use  competitive  analysis  to  inform  your  decision  regarding
whether  to  take  the  stairs  or  elevator.  In  the  spirit  of  competitive
analysis, you want to be sure that, no matter what the future brings (i.e.,
how  long  the  elevator  takes  to  arrive),  you  will  not  wait  much  longer
than a seer who knows when the elevator will arrive.

Let us ﬁrst consider what the seer would do. If the seer knows that
the elevator is going to arrive in at most k − 1 minutes, the seer waits for
the  elevator,  and  otherwise,  the  seer  takes  the  stairs.  Letting  m  denote
the number of minutes it takes for the elevator to arrive at the ground
ﬂoor, we can express the time that the seer spends as the function

We  typically  evaluate  online  algorithms  by  their  competitive  ratio.
Let U denote the set (universe) of all possible inputs, and consider some
input  I  ∈  U.  For  a  minimization  problem,  such  as  the  stairs-versus-
elevator  problem,  if  an  online  algorithm  A  produces  a  solution  with

value A(I) on input I and the solution from an algorithm F that knows
the future has value F(I) on the same input, then the competitive ratio
of algorithm A is

max {A(I)/F(I) : I ∈ U}.
If an online algorithm has a competitive ratio of c, we say that it is c-
competitive. The competitive ratio is always at least 1, so that we want
an online algorithm with a competitive ratio as close to 1 as possible.

In  the  stairs-versus-elevator  problem,  the  only  input  is  the  time  for
the  elevator  to  arrive.  Algorithm  F  knows  this  information,  but  an
online  algorithm  has  to  make  a  decision  without  knowing  when  the
elevator  will  arrive.  Consider  the  algorithm  “always  take  the  stairs,”
which  always  takes  exactly  k  minutes.  Using  equation  (27.1),  the
competitive ratio is

Enumerating the terms in equation (27.2) gives the competitive ratio as

so  that  the  competitive  ratio  is  k.  The  maximum  is  achieved  when  the
elevator  arrives  immediately.  In  this  case,  taking  the  stairs  requires  k
minutes, but the optimal solution takes just 1 minute.

Now let’s consider the opposite approach: “always take the elevator.”
If it takes m minutes for the elevator to arrive at the ground ﬂoor, then
this  algorithm  will  always  take  m  +  1  minutes.  Thus  the  competitive
ratio becomes

max {(m + 1)/t(m) : 0 ≤ m ≤ B − 1},

which we can again enumerate as

Now the maximum is achieved when the elevator takes B − 1 minutes to
arrive, compared with the optimal approach of taking the stairs, which
requires k minutes.

Hence, the algorithm “always take the stairs” has competitive ratio k,
and the algorithm “always take the elevator” has competitive ratio B/k.
Because  we  prefer  the  algorithm  with  smaller  competitive  ratio,  if  k  =
10  and  B  =  300,  we  prefer  “always  take  the  stairs,”  with  competitive
ratio  10,  over  “always  take  the  elevator,”  with  competitive  ratio  30.
Taking  the  stairs  is  not  always  better,  or  necessarily  more  often  better.
It’s just that taking the stairs guards better against the worst-case future.
These two approaches of always taking the stairs and always taking
the  elevator  are  extreme  solutions,  however.  Instead,  you  can  “hedge
your  bets”  and  guard  even  better  against  a  worst-case  future.  In
particular,  you  can  wait  for  the  elevator  for  a  while,  and  then  if  it
doesn’t arrive, take the stairs. How long is “a while”? Let’s say that “a
while”  is  k  minutes.  Then  the  time  h(m)  required  by  this  hedging
strategy, as a function of the number m of minutes before the elevator
arrives, is

In the second case, h(m) = 2k because you wait for k minutes and then
climb the stairs for k minutes. The competitive ratio is now

max {h(m)/t(m) : 0 ≤ m ≤ B − 1}.

Enumerating this ratio yields

The competitive ratio is now independent of k and B.

This example illustrates a common philosophy in online algorithms:
we  want  an  algorithm  that  guards  against  any  possible  worst  case.
Initially,  waiting  for  the  elevator  guards  against  the  case  when  the
elevator  arrives  quickly,  but  eventually  switching  to  the  stairs  guards
against the case when the elevator takes a long time to arrive.

Exercises

27.1-1

Suppose that when hedging your bets, you wait for p minutes, instead of
for k minutes, before taking the stairs. What is the competitive ratio as a
function  of  p  and  k?  How  should  you  choose  p  to  minimize  the
competitive ratio?

27.1-2
Imagine that you decide to take up downhill skiing. Suppose that a pair
of skis costs r dollars to rent for a day and b dollars to buy, where b > r.
If  you  knew  in  advance  how  many  days  you  would  ever  ski,  your
decision whether to rent or buy would be easy. If you’ll ski for at least
⌈b/r⌉  days,  then  you  should  buy  skis,  and  otherwise  you  should  rent.
This  strategy  minimizes  the  total  that  you  ever  spend.  In  reality,  you
don’t know in advance how many days you’ll eventually ski. Even after
you have skied several times, you still don’t know how many more times
you’ll  ever  ski.  Yet  you  don’t  want  to  waste  your  money.  Give  and
analyze  an  algorithm  that  has  a  competitive  ratio  of  2,  that  is,  an
algorithm  guaranteeing  that,  no  matter  how  many  times  you  ski,  you
never  spend  more  than  twice  what  you  would  have  spent  if  you  knew
from the outset how many times you’ll ski.

27.1-3
In “concentration solitaire,” a game for one person, you have n pairs of
matching cards. The backs of the cards are all the same, but the fronts
contain  pictures  of  animals.  One  pair  has  pictures  of  aardvarks,  one
pair  has  pictures  of  bears,  one  pair  has  pictures  of  camels,  and  so  on.
At  the  start  of  the  game,  the  cards  are  all  placed  face  down.  In  each
round,  you  can  turn  two  cards  face  up  to  reveal  their  pictures.  If  the
pictures match, then you remove that pair from the game. If they don’t
match,  then  you  turn  both  of  them  over,  hiding  their  pictures  once
again.  The  game  ends  when  you  have  removed  all  n  pairs,  and  your
score  is  how  many  rounds  you  needed  to  do  so.  Suppose  that  you  can
remember  the  picture  on  every  card  that  you  have  seen.  Give  an
algorithm to play concentration solitaire that has a competitive ratio of
2.

27.2    Maintaining a search list

The  next  example  of  an  online  algorithm  pertains  to  maintaining  the
order of elements in a linked list, as in Section 10.2. This problem often
arises  in  practice  for  hash  tables  when  collisions  are  resolved  by
chaining  (see  Section  11.2),  since  each  slot  contains  a  linked  list.
Reordering the linked list of elements in each slot of the hash table can
boost the performance of searches measurably.

The list-maintenance problem can be set up as follows. You are given
a  list  L  of  n  elements  {x1,  x2,  …  ,  xn}.  We’ll  assume  that  the  list  is
doubly  linked,  although  the  algorithms  and  analysis  work  just  as  well
for singly linked lists. Denote the position of element xi in the list L by
rL(xi), where 1 ≤ rL(xi) ≤ n. Calling LIST-SEARCH(L, xi) on page 260
thus takes Θ(rL(xi)) time.

If you know in advance something about the distribution of search
requests, then it makes sense to arrange the list ahead of time to put the
more frequently searched elements closer to the front, which minimizes
the total cost (see Exercise 27.2-1). If instead you don’t know anything
about the search sequence, then no matter how you arrange the list, it is
possible that every search is for whatever element appears at the tail of
the list. The total searching time would then be Θ(nm), where m is the
number of searches.

If  you  notice  patterns  in  the  access  sequence  or  you  observe
differences in the frequencies in which elements are accessed, then you
might want to rearrange the list as you perform searches. For example,
if you discover that every search is for a particular element, you could
move  that  element  to  the  front  of  the  list.  In  general,  you  could
rearrange the list after each call to LIST-SEARCH. But how would you
do so without knowing the future? After all, no matter how you move
elements around, every search could be for the last element.

But it turns out that some search sequences are “easier” than others.
Rather than just evaluate performance on the worst-case sequence, let’s
compare  a  reorganization  scheme  with  whatever  an  optimal  ofﬂine
algorithm  would  do  if  it  knew  the  search  sequence  in  advance.  That
way,  if  the  sequence  is  fundamentally  hard,  the  optimal  ofﬂine

algorithm will also ﬁnd it hard, but if the sequence is easy, we can hope
to do reasonably well.

To ease analysis, we’ll drop the asymptotic notation and say that the
cost  is  just  i  to  search  for  the  ith  element  in  the  list.  Let’s  also  assume
that the only way to reorder the elements in the list is by swapping two
adjacent elements in the list. Because the list is doubly linked, each swap
incurs  a  cost  of  1.  Thus,  for  example,  a  search  for  the  sixth  element
followed by moving it forward two places (entailing two swaps) incurs a
total  cost  8.  The  goal  is  to  minimize  the  total  cost  of  calls  to  LIST-
SEARCH plus the total number of swaps performed.

The online algorithm that we’ll explore is MOVE-TO-FRONT(L, x).
This procedure ﬁrst searches for x in the doubly linked list L, and then
it moves x to the front of the list.1 If x is located at position r = rL(x)
before  the  call,  MOVE-TO-FRONT  swaps  x  with  the  element  in
position r − 1, then with the element in position r − 2, and so on, until it
ﬁnally swaps x with the element in position 1. Thus if the call MOVE-
TO-FRONT(L, 8) executes on the list L = 〈5, 3, 12, 4, 8, 9, 22〉, the list
becomes 〈8, 5, 3, 12, 4, 9, 22〉. The call MOVE-TO-FRONT(L, k) costs
2rL(k) − 1: it costs rL(k) to search for k, and it costs 1 for each of the
rL(k) − 1 swaps that move k to the front of the list.

Figure  27.1  The  costs  incurred  by  the  procedures  FORESEE  and  MOVE-TO-FRONT  when
searching for the elements 5, 3, 4, and 4, starting with the list L = 〈1, 2, 3, 4, 5〉. If FORESEE
instead moved 3 to the front after the search for 5, the cumulative cost would not change, nor
would the cumulative cost change if 4 moved to the second position after the search for 5.

We’ll see that MOVE-TO-FRONT has a competitive ratio of 4. Let’s
think about what this means. MOVE-TO-FRONT performs a series of
operations on a doubly linked list, accumulating cost. For comparison,

suppose  that  there  is  an  algorithm  FORESEE  that  knows  the  future.
Like  MOVE-TO-FRONT,  it  also  searches  the  list  and  moves  elements
around, but after each call it optimally rearranges the list for the future.
(There  may  be  more  than  one  optimal  order.)  Thus  FORESEE  and
MOVE-TO-FRONT maintain different lists of the same elements.

Consider the example shown in Figure 27.1. Starting with the list 〈1,
2,  3,  4,  5〉,  four  searches  occur,  for  the  elements  5,  3,  4,  and  4.  The
hypothetical procedure FORESEE, after searching for 3, moves 4 to the
front of the list, knowing that a search for 4 is imminent. It thus incurs
a swap cost of 3 upon its second call, after which no further swap costs
accrue. MOVE-TO-FRONT incurs swap costs in each step, moving the
found element to the front. In this example, MOVE-TO-FRONT has a
higher cost in each step, but that is not necessarily always the case.

The  key  to  proving  the  competitive  bound  is  to  show  that  at  any
point,  the  total  cost  of  MOVE-TO-FRONT  is  not  much  higher  than
that of FORESEE. Surprisingly, we can determine a bound on the costs
incurred  by  MOVE-TO-FRONT  relative  to  FORESEE  even  though
MOVE-TO-FRONT cannot see the future.

If  we  compare  any  particular  step,  MOVE-TO-FRONT  and
FORESEE  may  be  operating  on  very  different  lists  and  do  very
different things. If we focus on the search for 4 above, we observe that
FORESEE  actually  moves  it  to  the  front  of  the  list  early,  paying  to
move  the  element  to  the  front  before  it  is  accessed.  To  capture  this
concept, we use the idea of an inversion: a pair of elements, say a and b,
in which a appears before b in one list, but b appears before a in another
list. For two lists L and L′, let I(L, L′), called the inversion count, denote
the  number  of  inversions  between  the  two  lists,  that  is,  the  number  of
pairs of elements whose order differs in the two lists. For example, with
lists  L  =  〈5,3,1,4,2〉  and  L′  =  〈3,1,2,4,5〉,  then  out  of  the
  pairs,
exactly ﬁve of them—(1, 5), (2, 4), (2, 5), (3, 5), (4, 5)—are inversions,
since these pairs, and only these pairs, appear in different orders in the
two lists. Thus the inversion count is I(L, L′) = 5.

In order to analyze the algorithm, we deﬁne the following notation.
 be the list maintained by MOVE-TO-FRONT immediately after
 be FORESEE’s list immediately after

Let
the ith search, and similarly, let

  and

  be  the  costs  incurred  by  MOVE-TO-
the  ith  search.  Let
FRONT and FORESEE on their ith calls, respectively. We don’t know
how  many  swaps  FORESEE  performs  in  its  ith  call,  but  we’ll  denote
that number by ti. Therefore, if the ith operation is a search for element
x, then

In order to compare these costs more carefully, let’s break down the
elements  into  subsets,  depending  on  their  positions  in  the  two  lists
before the ith search, relative to the element x being searched for in the
ith search. We deﬁne three sets:

BB = {elements before x in both

 and

},

BA = {elements before x in

 but after x in

AB = {elements after x in

 but before x in

},

}.

We can now relate the position of element x in
of these sets:

 and

 to the sizes

When  a  swap  occurs  in  one  of  the  lists,  it  changes  the  relative
positions  of  the  two  elements  involved,  which  in  turn  changes  the
inversion  count.  Suppose  that  elements  x  and  y  are  swapped  in  some
list.  Then  the  only  possible  difference  in  the  inversion  count  between
this list and any other list depends on whether (x, y) is an inversion. In
fact,  the  inversion  count  of  (x,  y)  with  respect  to  any  other  list  must
change.  If  (x,  y)  is  an  inversion  before  the  swap,  it  no  longer  is
afterward, and vice versa. Therefore, if two consecutive elements x and
y swap positions in a list L, then for any other list L′, the value of the
inversion count I(L, L′) either increases by 1 or decreases by 1.

As we compare MOVE-TO-FRONT and FORESEE searching and
modifying  their  lists,  we’ll  think  about  MOVE-TO-FRONT  executing
on its list for the ith time and then FORESEE executing on its list for
the  ith  time.  After  MOVE-TO-FRONT  has  executed  for  the  ith  time

and  before  FORESEE  has  executed  for  the  ith  time,  we’ll  compare
 (the inversion count immediately before the ith call of MOVE-
TO-FRONT)  with
  (the  inversion  count  after  the  ith  call  of
MOVE-TO-FRONT  but  before  the  ith  call  of  FORESEE).  We’ll
concern ourselves later with what FORESEE does.

Let  us  analyze  what  happens  to  the  inversion  count  after  executing
the  ith  call  of  MOVE-TO-FRONT,  and  suppose  that  it  searches  for
element  x.  More  precisely,  we’ll  compute
,  the
change  in  the  inversion  count,  which  gives  a  rough  idea  of  how  much
MOVE-TO-FRONT’s  list  becomes  more  or  less  like  FORESEE’s  list.
After  searching,  MOVE-TO-FRONT  performs  a  series  of  swaps  with
 that precedes x. Using the notation
each of the elements on the list
above,  the  number  of  such  swaps  is  |BB|  +  |BA|.  Bearing  in  mind  that
the list
 has yet to be changed by the ith call of FORESEE, let’s see
how the inversion count changes.

 and

precedes x in both

. After the swap, x precedes y in

Consider  a  swap  with  an  element  y  ∈  BB.  Before  the  swap,  y
, and
  does  not  change.  Therefore,  the  inversion  count  increases  by  1  for
each  element  in  BB.  Now  consider  a  swap  with  an  element  z  ∈  BA.
.  After  the
Before  the  swap,  z  precedes  x  in
swap, x precedes z in both lists. Therefore, the inversion count decreases
by  1  for  each  element  in  BA.  Thus  altogether,  the  inversion  count
increases by

  but  x  precedes  z  in

We  have  laid  the  groundwork  needed  to  analyze  MOVE-TO-

FRONT.

Theorem 27.1
Algorithm MOVE-TO-FRONT has a competitive ratio of 4.

Proof   The proof uses a potential function, as described in Chapter 16
on amortized analysis. The value Φi of the potential function after the
ith  calls  of  MOVE-TO-FRONT  and  FORESEE  depends  on  the
inversion count:

(Intuitively,  the  factor  of  2  embodies  the  notion  that  each  inversion
represents a cost of 2 for MOVE-TO-FRONT relative to FORESEE: 1
for searching and 1 for swapping.) By equation (27.7), after the ith call
of  MOVE-TO-FRONT,  but  before  the  ith  call  of  FORESEE,  the
potential  increases  by  2(|BB|  −  |BA|).  Since  the  inversion  count  of  the
two  lists  is  nonnegative,  we  have  Φi  ≥  0  for  all  i  ≥  0.  Assuming  that
MOVE-TO-FRONT and FORESEE start with the same list, the initial
potential Φ0 is 0, so that Φi ≥ Φ0 for all i.

Drawing from equation (16.2) on page 456, the amortized cost

 of

the ith MOVE-TO-FRONT operation is

where
given by equation (27.3):

,  the  actual  cost  of  the  ith  MOVE-TO-FRONT  operation,  is

Now, let’s consider the potential change Φi − Φi−1. Since both LM and
LF  change,  let’s  consider  the  changes  to  one  list  at  a  time.  Recall  that
when MOVE-TO-FRONT moves element x to the front, it increases the
potential  by  exactly  2(|BB|  −  |BA|).  We  now  consider  how  the  optimal
algorithm  FORESEE  changes  its  list  LF:  it  performs  ti  swaps.  Each
swap  performed  by  FORESEE  either  increases  or  decreases  the
potential  by  2,  and  thus  the  increase  in  potential  by  FORESEE  in  the
ith call can be at most 2ti. We therefore have

We now ﬁnish the proof as in Chapter 16 by showing that the total
amortized  cost  provides  an  upper  bound  on  the  total  actual  cost,
because  the  initial  potential  function  is  0  and  the  potential  function  is
always  nonnegative.  By  equation  (16.3)  on  page  456,  for  any  sequence
of m MOVE-TO-FRONT operations, we have

Therefore, we have

Thus the total cost of the m MOVE-TO-FRONT operations is at most
4  times  the  total  cost  of  the  m  FORESEE  operations,  so  MOVE-TO-
FRONT is 4-competitive.

▪

Isn’t  it  amazing  that  we  can  compare  MOVE-TO-FRONT  with  the
optimal algorithm FORESEE when we have no idea of the swaps that
FORESEE makes? We were able to relate the performance of MOVE-
TO-FRONT  to  the  optimal  algorithm  by  capturing  how  particular
properties  (swaps  in  this  case)  must  evolve  relative  to  the  optimal
algorithm, without actually knowing the optimal algorithm.

The online algorithm MOVE-TO-FRONT has a competitive ratio of
4:  on  any  input  sequence,  it  incurs  a  cost  at  most  4  times  that  of  any
other algorithm. On a particular input sequence, it could cost much less
than 4 times the optimal algorithm, perhaps even matching the optimal
algorithm.

Exercises

27.2-1
You are given a set S = {x1, x2, … , xn} of n elements, and you wish to
make a static list L (no rearranging once the list is created) containing
the  elements  of  S  that  is  good  for  searching.  Suppose  that  you  have  a
probability  distribution,  where  p(xi)  is  the  probability  that  a  given
search  searches  for  element  xi.  Argue  that  the  expected  cost  for  m
searches is

Prove that this sum is minimized when the elements of L are sorted in
decreasing order with respect to p(xi).

27.2-2
Professor Carnac claims that since FORESEE is an optimal algorithm
that knows the future, then at each step it must incur no more cost than
MOVE-TO-FRONT.  Either  prove  that  Professor  Carnac  is  correct  or
provide a counterexample.

27.2-3
Another way to maintain a linked list for efﬁcient searching is for each
element  to  maintain  a  frequency  count:  the  number  of  times  that  the
element  has  been  searched  for.  The  idea  is  to  rearrange  list  elements
after  searches  so  that  the  list  is  always  sorted  by  decreasing  frequency
count, from largest to smallest. Either show that this algorithm is O(1)-
competitive, or prove that it is not.

27.2-4
The  model  in  this  section  charged  a  cost  of  1  for  each  swap.  We  can
consider an alternative cost model in which, after accessing x, you can
move  x  anywhere  earlier  in  the  list,  and  there  is  no  cost  for  doing  so.
The only cost is the cost of the actual accesses. Show that MOVE-TO-
FRONT is 2-competitive in this cost model, assuming that the number
large.  (Hint:  Use  the  potential  function
requests

is  sufﬁciently

.)

27.3    Online caching

In Section 15.4, we studied the caching problem, in which blocks of data
from the main memory of a computer are stored in the cache: a small
but faster memory. In that section, we studied the ofﬂine version of the
problem,  in  which  we  assumed  that  we  knew  the  sequence  of  memory
requests  in  advance,  and  we  designed  an  algorithm  to  minimize  the
number of cache misses. In almost all computer systems, caching is, in
fact, an online problem. We do not generally know the series of cache
requests  in  advance;  they  are  presented  to  the  algorithm  only  as  the
requests for blocks are actually made. To gain a better understanding of
this  more  realistic  scenario,  we  analyze  online  algorithms  for  caching.
We will ﬁrst see that all deterministic online algorithms for caching have
a  lower  bound  of  Ω(k)  for  the  competitive  ratio,  where  k  is  the  size  of
the cache. We will then present an algorithm with a competitive ratio of
Θ(n), where the input size is n, and one with a competitive ratio of O(k),
which  matches  the  lower  bound.  We  will  end  by  showing  how  to  use
randomization  to  design  an  algorithm  with  a  much  better  competitive
ratio  of  Θ(lg  k).  We  will  also  discuss  the  assumptions  that  underlie
randomized online algorithms, via the notion of an adversary, such as
we saw in Chapter 11 and will see in Chapter 31.

You can ﬁnd the terminology used to describe the caching problem

in Section 15.4, which you might wish to review before proceeding.

27.3.1    Deterministic caching algorithms
In  the  caching  problem,  the  input  comprises  a  sequence  of  n  memory
requests,  for  data  in  blocks  b1,  b2,  …  ,  bn,  in  that  order.  The  blocks
requested  are  not  necessarily  distinct:  each  block  may  appear  multiple
times within the request sequence. After block bi is requested, it resides
in a cache that can hold up to k blocks, where k is a ﬁxed cache size. We
assume  that  n  >  k,  since  otherwise  we  are  assured  that  the  cache  can
hold all the requested blocks at once. When a block bi is requested, if it
is  already  in  the  cache,  then  a  cache  hit  occurs  and  the  cache  remains
unchanged.  If  bi  is  not  in  the  cache,  then  a  cache  miss  occurs.  If  the

cache contains fewer than k blocks upon a cache miss, block bi is placed
into  the  cache,  which  now  contains  one  block  more  than  before.  If  a
cache miss occurs with an already full cache, however, some block must
be evicted from the cache before bi can enter. Thus, a caching algorithm
must  decide  which  block  to  evict  from  the  cache  upon  a  cache  miss
when  the  cache  is  full.  The  goal  is  to  minimize  the  number  of  cache
misses  over  the  entire  request  sequence.  The  caching  algorithms
considered in this chapter differ only in which block they decide to evict
upon a cache miss. We do not consider abilities such as prefetching, in
which a block is brought into the cache before an upcoming request in
order to avert a future cache miss.

There are many online caching policies to determine which block to

evict, including the following:

First-in,  ﬁrst-out  (FIFO):  evict  the  block  that  has  been  in  the
cache the longest time.

Last-in,  ﬁrst-out  (LIFO):  evict  the  block  that  has  been  in  the
cache the shortest time.

Least  Recently  Used  (LRU):  evict  the  block  whose  last  use  is
furthest in the past.

Least  Frequently  Used  (LFU):  evict  the  block  that  has  been
accessed the fewest times, breaking ties by choosing the block that
has been in the cache the longest.

To  analyze  these  algorithms,  we  assume  that  the  cache  starts  out
empty, so that no evictions occur during the ﬁrst k requests. We wish to
compare the performance of an online algorithm to an optimal ofﬂine
algorithm that knows the future requests. As we will soon see, all these
deterministic  online  algorithms  have  a  lower  bound  of  Ω(k)  for  their
competitive  ratio.  Some  deterministic  algorithms  also  have  a
competitive  ratio  with  an  O(k)  upper  bound,  but  some  other
deterministic  algorithms  are  considerably  worse,  having  a  competitive
ratio of Θ(n/k).

We now proceed to analyze the LIFO and LRU policies. In addition
to assuming that n > k, we will assume that at least k distinct blocks are

requested. Otherwise, the cache never ﬁlls up and no blocks are evicted,
so  that  all  algorithms  exhibit  the  same  behavior.  We  begin  by  showing
that LIFO has a large competitive ratio.

Theorem 27.2
LIFO has a competitive ratio of Θ(n/k) for the online caching problem
with n requests and a cache of size k.

Proof   We ﬁrst show a lower bound of Ω(n/k). Suppose that the input
consists  of  k  +  1  blocks,  numbered  1,  2,  …  ,  k  +  1,  and  the  request
sequence is

1, 2, 3, 4, … , k, k + 1, k, k + 1, k, k + 1, … ,

where after the initial 1, 2, … , k, k + 1, the remainder of the sequence
alternates between k and k + 1, with a total of n requests. The sequence
ends  on  block  k  if  n  and  k  are  either  both  even  or  both  odd,  and
otherwise, the sequence ends on block k+1. That is, bi = i for i = 1, 2, …
k−1, bi = k+1 for i = k+1, k+3, … and bi = k for i = k, k + 2, …. How
many  blocks  does  LIFO  evict?  After  the  ﬁrst  k  requests  (which  are
considered to be cache misses), the cache is ﬁlled with blocks 1, 2, … , k.
The  (k  +  1)st  request,  which  is  for  block  k  +  1,  causes  block  k  to  be
evicted. The (k + 2)nd request, which is for block k, forces block k + 1
to  be  evicted,  since  that  block  was  just  placed  into  the  cache.  This
behavior  continues,  alternately  evicting  blocks  k  and  k+1  for  the
remaining requests. LIFO, therefore, suffers a cache miss on every one
of the n requests.

The optimal ofﬂine algorithm knows the entire sequence of requests
in advance. Upon the ﬁrst request of block k + 1, it just evicts any block
except block k, and then it never evicts another block. Thus, the optimal
ofﬂine  algorithm  evicts  only  once.  Since  the  ﬁrst  k  requests  are
considered cache misses, the total number of cache misses is k + 1. The
competitive ratio, therefore, is n/(k + 1), or Ω(n/k).

For  the  upper  bound,  observe  that  on  any  input  of  size  n,  any
caching  algorithm  incurs  at  most  n  cache  misses.  Because  the  input
contains at least k distinct blocks, any caching algorithm, including the

optimal ofﬂine algorithm, must incur at least k cache misses. Therefore,
LIFO has a competitive ratio of O(n/k).

▪

We  call  such  a  competitive  ratio  unbounded,  because  it  grows  with
the  input  size.  Exercise  27.3-2  asks  you  to  show  that  LFU  also  has  an
unbounded competitive ratio.

FIFO and LRU have a much better competitive ratio of Θ(k). There
is  a  big  difference  between  competitive  ratios  of  Θ(n/k)  and  Θ(k).  The
cache size k is independent of the input sequence and does not grow as
more requests arrive over time. A competitive ratio that depends on n,
on  the  other  hand,  does  grow  with  the  size  of  the  input  sequence  and
thus  can  get  quite  large.  It  is  preferable  to  use  an  algorithm  with  a
competitive  ratio  that  does  not  grow  with  the  input  sequence’s  size,
when possible.

We  now  show  that  LRU  has  a  competitive  ratio  of  Θ(k),  ﬁrst

showing the upper bound.

Theorem 27.3
LRU  has  a  competitive  ratio  of  O(k)  for  the  online  caching  problem
with n requests and a cache of size k.

Proof      To  analyze  LRU,  we  will  divide  the  sequence  of  requests  into
epochs. Epoch 1 begins with the ﬁrst request. Epoch i, for i > 1, begins
upon encountering the (k + 1)st distinct request since the beginning of
epoch i − 1. Consider the following example of requests with k = 3:

The  ﬁrst  k  =  3  distinct  requests  are  for  blocks  1,  2  and  5,  so  epoch  2
begins with the ﬁrst request for block 4. In epoch 2, the ﬁrst 3 distinct
requests are for blocks 4, 1, and 2. Requests for these blocks recur until
the request for block 3, and with this request epoch 3 begins. Thus, this
example has four epochs:

Now we consider the behavior of LRU. In each epoch, the ﬁrst time
a request for a particular block appears, it may cause a cache miss, but

subsequent  requests  for  that  block  within  the  epoch  cannot  cause  a
cache miss, since the block is now one of the k most recently used. For
example,  in  epoch  2,  the  ﬁrst  request  for  block  4  causes  a  cache  miss,
but  the  subsequent  requests  for  block  4  do  not.  (Exercise  27.3-1  asks
you to show the contents of the cache after each request.) In epoch 3,
requests for blocks 3 and 5 cause cache misses, but the request for block
4 does not, because it was recently accessed in epoch 2. Since only the
ﬁrst request for a block within an epoch can cause a cache miss and the
cache holds k blocks, each epoch incurs at most k cache misses.

Now  consider  the  behavior  of  the  optimal  algorithm.  The  ﬁrst
request  in  each  epoch  must  cause  a  cache  miss,  even  for  an  optimal
algorithm. The miss occurs because, by the deﬁnition of an epoch, there
must  have  been  k  other  blocks  accessed  since  the  last  access  to  this
block.

Since, for each epoch, the optimal algorithm incurs at least one miss

and LRU incurs at most k, the competitive ratio is at most k/1 = O(k).

▪

Exercise  27.3-3  asks  you  to  show  that  FIFO  also  has  a  competitive

ratio of O(k).

We could show lower bounds of Ω(k) on LRU and FIFO, but in fact,
we  can  make  a  much  stronger  statement:  any  deterministic  online
caching  algorithm  must  have  a  competitive  ratio  of  Ω(k).  The  proof
relies on an adversary who knows the online algorithm being used and
can  tailor  the  future  requests  to  cause  the  online  algorithm  to  incur
more cache misses than the optimal ofﬂine algorithm.

Consider  a  scenario  in  which  the  cache  has  size  k  and  the  set  of
possible blocks to request is {1, 2, … , k + 1}. The ﬁrst k requests are
for blocks 1, 2, … , k, so that both the adversary and the deterministic
online algorithm place these blocks into the cache. The next request is
for block k + 1. In order to make room in the cache for block k + 1, the
online  algorithm  evicts  some  block  b1  from  the  cache.  The  adversary,
knowing that the online algorithm has just evicted block b1, makes the
next  request  be  for  b1,  so  that  the  online  algorithm  must  evict  some
other  block  b2  to  clear  room  in  the  cache  for  b1.  As  you  might  have

guessed,  the  adversary  makes  the  next  request  be  for  block  b2,  so  that
the  online  algorithm  evicts  some  other  block  b3  to  make  room  for  b2.
The  online  algorithm  and  the  adversary  continue  in  this  manner.  The
online  algorithm  incurs  a  cache  miss  on  every  request  and  therefore
incurs n cache misses over the n requests.

Now  let’s  consider  an  optimal  ofﬂine  algorithm,  which  knows  the
future. As discussed in Section 15.4, this algorithm is known as furthest-
in-future, and it always evicts the block whose next request is furthest in
the  future.  Since  there  are  only  k  +  1  unique  blocks,  when  furthest-in-
future evicts a block, we know that it will not be accessed during at least
the  next  k  requests.  Thus,  after  the  ﬁrst  k  cache  misses,  the  optimal
algorithm incurs a cache miss at most once every k requests. Therefore,
the number of cache misses over n requests is at most k + n/k.

Since  the  deterministic  online  algorithm  incurs  n  cache  misses  and
the  optimal  ofﬂine  algorithm  incurs  at  most  k  +  n/k  cache  misses,  the
competitive ratio is at least

For n ≥ k2, the above expression is at least

Thus,  for  sufﬁciently  long  request  sequences,  we  have  shown  the
following:

Theorem 27.4
Any  deterministic  online  algorithm  for  caching  with  a  cache  size  of  k
has competitive ratio Ω(k).

▪

Although  we  can  analyze  the  common  caching  strategies  from  the
point  of  view  of  competitive  analysis,  the  results  are  somewhat
unsatisfying.  Yes,  we  can  distinguish  between  algorithms  with  a
competitive ratio of Θ(k) and those with unbounded competitive ratios.
In the end, however, all of these competitive ratios are rather high. The

online  algorithms  we  have  seen  so  far  are  deterministic,  and  it  is  this
property that the adversary is able to exploit.

27.3.2    Randomized caching algorithms

If  we  don’t  limit  ourselves  to  deterministic  online  algorithms,  we  can
use  randomization  to  develop  an  online  caching  algorithm  with  a
signiﬁcantly smaller competitive ratio. Before describing the algorithm,
let’s  discuss  randomization  in  online  algorithms  in  general.  Recall  that
we  analyze  online  algorithms  with  respect  to  an  adversary  who  knows
the  online  algorithm  and  can  design  requests  knowing  the  decisions
made  by  the  online  algorithm.  With  randomization,  we  must  ask
whether  the  adversary  also  knows  the  random  choices  made  by  the
online algorithm. An adversary who does not know the random choices
is  oblivious,  and  an  adversary  who  knows  the  random  choices  is
nonoblivious.  Ideally,  we  prefer  to  design  algorithms  against  a
nonoblivious  adversary,  as  this  adversary  is  stronger  than  an  oblivious
one.  Unfortunately,  a  nonoblivious  adversary  mitigates  much  of  the
power  of  randomness,  as  an  adversary  who  knows  the  outcome  of
random  choices  typically  can  act  as  if  the  online  algorithm  is
deterministic.  The  oblivious  adversary,  on  the  other  hand,  does  not
know  the  random  choices  of  the  online  algorithm,  and  that  is  the
adversary we typically use.

As  a  simple  illustration  of  the  difference  between  an  oblivious  and
nonoblivious adversary, imagine that you are ﬂipping a fair coin n times,
and  the  adversary  wants  to  know  how  many  heads  you  ﬂipped.  A
nonoblivious adversary knows, after each ﬂip, whether the coin came up
heads  or  tails,  and  hence  knows  how  many  heads  you  ﬂipped.  An
oblivious adversary, on the other hand, knows only that you are ﬂipping
a  fair  coin  n  times.  The  oblivious  adversary,  therefore,  can  reason  that
the  number  of  heads  follows  a  binomial  distribution,  so  that  the
expected number of heads is n/2 (by equation (C.41) on page 1199) and
the variance is n/4 (by equation (C.44) on page 1200). But the oblivious
adversary has no way of knowing exactly how many heads you actually
ﬂipped.

Let’s  return  to  caching.  We’ll  start  with  a  deterministic  algorithm
and then randomize it. The algorithm we’ll use is an approximation of
LRU  called  MARKING.  Rather  than  “least  recently  used,”  think  of
MARKING  as  simply  “recently  used.”  MARKING  maintains  a  1-bit
attribute  mark  for  each  block  in  the  cache.  Initially,  all  blocks  in  the
cache  are  unmarked.  When  a  block  is  requested,  if  it  is  already  in  the
cache, it is marked. If the request is a cache miss, MARKING checks to
see whether there are any unmarked blocks in the cache. If all blocks are
marked,  then  they  are  all  changed  to  unmarked.  Now,  regardless  of
whether all blocks in the cache were marked when the request occurred,
there  is  at  least  one  unmarked  block  in  the  cache,  and  so  an  arbitrary
unmarked  block  is  evicted,  and  the  requested  block  is  placed  into  the
cache and marked.

How should the block to evict from among the unmarked blocks in
the cache be chosen? The procedure RANDOMIZED-MARKING on
the next page shows the process when the block is chosen randomly. The
procedure takes as input a block b being requested.

RANDOMIZED-MARKING(b)
1if block b resides in the cache,
2
3else
4

b.mark = 1

if all blocks b′ in the cache have b′.mark = 1

5

6

7

8

9

unmark all blocks b′ in the cache, setting b′.mark = 0

select an unmarked block u with u.mark = 0 uniformly at random
evict block u
place block b into the cache
b.mark = 1

For  the  purpose  of  analysis,  we  say  that  a  new  epoch  begins
immediately  after  each  time  line  5  executes.  An  epoch  starts  with  no
marked blocks in the cache. The ﬁrst time a block is requested during an
epoch, the number of marked blocks increases by 1, and any subsequent
requests  to  that  block  do  not  change  the  number  of  marked  blocks.
Therefore, the number of marked blocks monotonically increases within

an  epoch.  Under  this  view,  epochs  are  the  same  as  in  the  proof  of
Theorem  27.3:  with  a  cache  that  holds  k  blocks,  an  epoch  comprises
requests  for  k  distinct  blocks  (possibly  fewer  for  the  ﬁnal  epoch),  and
the next epoch begins upon a request for a block not in those k.

Because  we  are  going  to  analyze  a  randomized  algorithm,  we  will
compute  the  expected  competitive  ratio.  Recall  that  for  an  input  I,  we
denote  the  solution  value  of  an  online  algorithm  A  by  A(I)  and  the
solution  value  of  an  optimal  algorithm  F  by  F(I).  Online  algorithm  A
has an expected competitive ratio c if for all inputs I, we have

where the expectation is taken over the random choices made by A.

Although the deterministic MARKING algorithm has a competitive
ratio of Θ(k) (Theorem 27.4 provides the lower bound and see Exercise
27.3-4 for the upper bound), RANDOMIZED-MARKING has a much
smaller  expected  competitive  ratio,  namely  O(lg  k).  The  key  to  the
improved competitive ratio is that the adversary cannot always make a
request for a block that is not in the cache, since an oblivious adversary
does not know which blocks are in the cache.

Theorem 27.5
RANDOMIZED-MARKING  has  an  expected  competitive  ratio  of
O(lg  k)  for  the  online  caching  problem  with  n  requests  and  a  cache  of
size k, against an oblivious adversary.

Before proving Theorem 27.5, we prove a basic probabilistic fact.

Lemma 27.6
Suppose that a bag contains x + y balls: x − 1 blue balls, y white balls,
and  1  red  ball.  You  repeatedly  choose  a  ball  at  random  and  remove  it
from the bag until you have chosen a total of m balls that are either blue
or red, where m ≤ x. You set aside each white ball you choose. Then, one
of the balls chosen is the red ball with probability m/x.

Proof   Choosing a white ball does not affect how many blue or red balls
are  chosen  in  any  way.  Therefore,  we  can  continue  the  analysis  as  if

there were no white balls and the bag contains just x − 1 blue balls and
1 red ball.

Let A be the event that the red ball is not chosen, and let Ai be the
event that the ith draw does not choose the red ball. By equation (C.22)
on page 1190, we have

The probability Pr{A1} that the ﬁrst ball is blue equals (x − 1)/x, since
initially  there  are  x  −  1  blue  balls  and  1  red  ball.  More  generally,  we
have

since  the  ith  draw  is  from  x  −  i  blue  balls  and  1  red  ball.  Equations
(27.13) and (27.14) give

The right-hand side of equation (27.15) is a telescoping product, similar
to  the  telescoping  series  in  equation  (A.12)  on  page  1143.  The
numerator  of  one  term  equals  the  denominator  of  the  next,  so  that
everything except the ﬁrst denominator and last numerator cancel, and
we obtain Pr{A} = (x − m)/x. Since we actually want to compute Pr{Ā}
= 1 − Pr{A}, that is, the probability that the red ball is chosen, we get
Pr{Ā} = 1 − (x − m)/x = m/x.

▪

Now we can prove Theorem 27.5.

Proof      We’ll  analyze  RANDOMIZED-MARKING  one  epoch  at  a
time.  Within  epoch  i,  any  request  for  a  block  b  that  is  not  the  ﬁrst
request for block b in epoch i must result in a cache hit, since after the
ﬁrst  request  in  epoch  i,  block  b  resides  in  the  cache  and  is  marked,  so
that  it  cannot  be  evicted  during  the  epoch.  Therefore,  since  we  are

counting  cache  misses,  we’ll  consider  only  the  ﬁrst  request  for  each
block within each epoch, disregarding all other requests.

We  can  classify  the  requests  in  an  epoch  as  either  old  or  new.  If
block  b  resides  in  the  cache  at  the  start  of  epoch  i,  each  request  for
block b during epoch i is an old request. Old requests in epoch i are for
blocks requested in epoch i − 1. If a request in epoch i is not old, it is a
new  request,  and  it  is  for  a  block  not  requested  in  epoch  i  −  1.  All
requests in epoch 1 are new. For example, let’s look again at the request
sequence in example (27.11):

1, 2, 1, 5

4, 4, 1, 2, 4, 2

3, 4, 5

2, 2, 1, 2, 2.

Since  we  can  disregard  all  requests  for  a  block  within  an  epoch  other
than  the  ﬁrst  request,  to  analyze  the  cache  behavior,  we  can  view  this
request sequence as just

1, 2, 5

4, 1, 2

3, 4, 5

2, 1.

All three requests in epoch 1 are new. In epoch 2, the requests for blocks
1  and  2  are  old,  but  the  request  for  block  4  is  new.  In  epoch  3,  the
request for block 4 is old, and the requests for blocks 3 and 5 are new.
Both requests in epoch 4 are new.

Within an epoch, each new request must cause a cache miss since, by
deﬁnition, the block is not already in the cache. An old request, on the
other hand, may or may not cause a cache miss. The old block is in the
cache at the beginning of the epoch, but other requests might cause it to
be evicted. Returning to our example, in epoch 2, the request for block 4
must cause a cache miss, as this request is new. The request for block 1,
which is old, may or may not cause a cache miss. If block 1 was evicted
when block 4 was requested, then a cache miss occurs and block 1 must
be brought back into the cache. If instead block 1 was not evicted when
block 4 was requested, then the request for block 1 results in a cache hit.
The  request  for  block  2  could  incur  a  cache  miss  under  two  scenarios.
One is if block 2 was evicted when block 4 was requested. The other is if
block 1 was evicted when block 4 was requested, and then block 2 was
evicted when block 1 was requested. We see that, within an epoch, each
ensuing old request has an increasing chance of causing a cache miss.

Because  we  consider  only  the  ﬁrst  request  for  each  block  within  an
epoch, we assume that each epoch contains exactly k requests, and each
request  within  an  epoch  is  for  a  unique  block.  (The  last  epoch  might
contain fewer than k requests. If it does, just add dummy requests to ﬁll
it out to k requests.) In epoch i, denote the number of new requests by ri
≥  1  (an  epoch  must  contain  at  least  one  new  request),  so  that  the
number  of  old  requests  is  k  −  ri.  As  mentioned  above,  a  new  request
always incurs a cache miss.

Let us now focus on an arbitrary epoch i to obtain a bound on the
expected number of cache misses within that epoch. In particular, let’s
think  about  the  jth  old  request  within  the  epoch,  where  1  ≤  j  <  k.
Denote by bij the block requested in the jth old request of epoch i, and
denote by nij and oij the number of new and old requests, respectively,
that occur within epoch i but before the jth old request. Because j − 1
old requests occur before the jth old request, we have oij = j − 1. We will
show  that  the  probability  of  a  cache  miss  upon  the  j  th  old  request  is
nij/(k − oij), or nij/(k − j + 1).

Start by considering the ﬁrst old request, for block bi,1. What is the
probability that this request causes a cache miss? It causes a cache miss
precisely  when  one  of  the  ni,1  previous  requests  resulted  in  bi,1  being
evicted.  We  can  determine  the  probability  that  bi,1  was  chosen  for
eviction by using Lemma 27.6: consider the k blocks in the cache to be k
balls, with block bi,1 as the red ball, the other k − 1 blocks as the k − 1
blue balls, and no white balls. Each of the ni,1 requests chooses a block
to  evict  with  equal  probability,  corresponding  to  drawing  balls  ni,1
times. Thus, we can apply Lemma 27.6 with x = k, y = 0, and m = ni,1,
deriving  the  probability  of  a  cache  miss  upon  the  ﬁrst  old  request  as
ni,1/k, which equals nij/(k − j + 1) since j = 1.

In order to determine the probability of a cache miss for subsequent
old  requests,  we’ll  need  an  additional  observation.  Let’s  consider  the
second old request, which is for block bi,2. This request causes a cache
miss  precisely  when  one  of  the  previous  requests  evicts  bi,2.  Let’s

consider  two  cases,  based  on  the  request  for  bi,1.  In  the  ﬁrst  case,
suppose that the request for bi,1 did not cause an eviction, because bi,1
was already in the cache. Then, the only way that bi,2 could have been
evicted is by one of the ni,2 new requests that precedes it. What is the
probability that this eviction happens? There are ni,2 chances for bi,2 to
be evicted, but we also know that there is one block in the cache, namely
bi,1, that is not evicted. Thus, we can again apply Lemma 27.6, but with
bi,1  as  the  white  ball,  bi,2  as  the  red  ball,  the  remaining  blocks  as  the
blue balls, and drawing balls ni,2 times. Applying Lemma 27.6, with x =
k − 1, y = 1, and m = ni,2, we ﬁnd that the probability of a cache miss is
ni,2/(k  −  1).  In  the  second  case,  the  request  for  bi,1  does  cause  an
eviction,  which  can  happen  only  if  one  of  the  new  requests  preceding
the request for bi,1 evicts bi,1. Then, the request for bi,1 brings bi,1 back
into the cache and evicts some other block. In this case, we know that
of  the  new  requests,  one  of  them  did  not  result  in  bi,2  being  evicted,
since bi,1 was evicted. Therefore, ni,2 − 1 new requests could evict bi,2,
as could the request for bi,1, so that the number of requests that could
evict bi,2 is ni,2. Each such request evicts a block chosen from among k
−  1  blocks,  since  the  request  that  resulted  in  evicting  bi,1  did  not  also
cause bi,2 to be evicted. Therefore, we can apply Lemma 27.6, with x =
k  −  1,  y  =  1,  and  m  =  ni,2,  and  get  that  the  probability  of  a  miss  is
ni,2/(k − 1). In both cases the probability is the same, and it equals nij/(k
− j + 1) since j = 2.

More  generally,  oij  old  requests  occur  before  the  jth  old  request.
Each  of  these  prior  old  requests  either  caused  an  eviction  or  did  not.
For  those  that  caused  an  eviction,  it  is  because  they  were  evicted  by  a
previous  request,  and  for  those  that  did  not  cause  an  eviction,  it  is
because they were not evicted by any previous request. In either case, we
can decrease the number of blocks that the random process is choosing
from by 1 for each old request, and thus oij requests cannot cause bij to
be  evicted.  Therefore,  we  can  use  Lemma  27.6  to  determine  the

probability that bij was evicted by a previous request, with x = k − oij, y
= oij and m = nij. Thus, we have proven our claim that the probability
of  a  cache  miss  on  the  jth  request  for  an  old  block  is  nij/(k  −  oij),  or
nij/(k − j + 1). Since nij ≤ ri (recall that ri is the number of new requests
during  epoch  i),  we  have  an  upper  bound  of  ri/(k  −  j  +  1)  on  the
probability that the jth old request incurs a cache miss.

We can now compute the expected number of misses during epoch i
using  indicator  random  variables,  as  introduced  in  Section  5.2.  We
deﬁne indicator random variables

Yij = I{the jth old request in epoch i incurs a cache miss},

Zij = I{the j th new request in epoch i incurs a cache miss}.

We have Zij = 1 for j = 1, 2, … , ri, since every new request results in a
cache  miss.  Let  Xi  be  the  random  variable  denoting  the  number  of
cache misses during epoch i, so that

and so

where Hk is the kth harmonic number.

To compute the expected total number of cache misses, we sum over
all  epochs.  Let  p  denote  the  number  of  epochs  and  X  be  the  random
variable denoting the number of cache misses. Then, we have
,
so that

To complete the analysis, we need to understand the behavior of the
optimal  ofﬂine  algorithm.  It  could  make  a  completely  different  set  of
decisions  from  those  made  by  RANDOMIZED-MARKING,  and  at
any point its cache may look nothing like the cache of the randomized
algorithm.  Yet,  we  want  to  relate  the  number  of  cache  misses  of  the
optimal ofﬂine algorithm to the value in inequality (27.17), in order to
have  a  competitive  ratio  that  does  not  depend  on
.  Focusing  on
individual  epochs  won’t  sufﬁce.  At  the  beginning  of  any  epoch,  the
ofﬂine  algorithm  might  have  loaded  the  cache  with  exactly  the  blocks
that will be requested in that epoch. Therefore, we cannot take any one
epoch  in  isolation  and  claim  that  an  ofﬂine  algorithm  must  suffer  any
cache misses during that epoch.

If  we  consider  two  consecutive  epochs,  however,  we  can  better
analyze the optimal ofﬂine algorithm. Consider two consecutive epochs,
i −1 and i. Each contains k requests for k different blocks. (Recall our
assumption  that  all  requests  are  ﬁrst  requests  in  an  epoch.)  Epoch  i
contains  ri  requests  for  new  blocks,  that  is,  blocks  that  were  not
requested during epoch i − 1. Therefore, the number of distinct requests
during  epochs  i−1  and  i  is  exactly  k+ri.  No  matter  what  the  cache
contents  were  at  the  beginning  of  epoch  i  −  1,  after  k  +  ri  distinct
requests, there must be at least ri cache misses. There could be more, but

there  is  no  way  to  have  fewer.  Letting  mi  denote  the  number  of  cache
misses of the ofﬂine algorithm during epoch i, we have just argued that

The total number of cache misses of the ofﬂine algorithm is

The  justiﬁcation  m1  =  r1  for  the  last  equality  follows  because,  by  our
assumptions,  the  cache  starts  out  empty  and  every  request  incurs  a
cache miss in the ﬁrst epoch, even for the optimal ofﬂine adversary.

To  conclude  the  analysis,  because  we  have  an  upper  bound  of
 on the expected number of cache misses for RANDOMIZED-
MARKING  and  a  lower  bound  of
  on  the  number  of  cache
misses for the optimal ofﬂine algorithm, the expected competitive ratio
is at most

Exercises

27.3-1
For  the  cache  sequence  (27.10),  show  the  contents  of  the  cache  after
each request and count the number of cache misses. How many misses

▪

does each epoch incur?

27.3-2
Show that LFU has a competitive ratio of Θ(n/k) for the online caching
problem with n requests and a cache of size k.

27.3-3
Show that FIFO has a competitive ratio of O(k) for the online caching
problem with n requests and a cache of size k.

27.3-4
Show  that  the  deterministic  MARKING  algorithm  has  a  competitive
ratio of O(k) for the online caching problem with n requests and a cache
of size k.

27.3-5
Theorem 27.4 shows that any deterministic online algorithm for caching
has  a  competitive  ratio  of  Ω(k),  where  k  is  the  cache  size.  One  way  in
which  an  algorithm  might  be  able  to  perform  better  is  to  have  some
ability  to  know  what  the  next  few  requests  will  be.  We  say  that  an
algorithm is l-lookahead if it has the ability to look ahead at the next l
requests. Prove that for every constant l ≥ 0 and every cache size k ≥1,
every deterministic l-lookahead algorithm has competitive ratio Ω(k).

Problems

27-1     Cow-path problem
The  Appalachian  Trail  (AT)  is  a  marked  hiking  trail  in  the  eastern
United  States  extending  between  Springer  Mountain  in  Georgia  and
Mount  Katahdin  in  Maine.  The  trail  is  about  2,190  miles  long.  You
decide  that  you  are  going  to  hike  the  AT  from  Georgia  to  Maine  and
back. You plan to learn more about algorithms while on the trail, and
so  you  bring  along  your  copy  of  Introduction  to  Algorithms  in  your
backpack.2 You have already read through this chapter before starting
out.  Because  the  beauty  of  the  trail  distracts  you,  you  forget  about
reading this book until you have reached Maine and hiked halfway back

to  Georgia.  At  that  point,  you  decide  that  you  have  already  seen  the
trail  and  want  to  continue  reading  the  rest  of  the  book,  starting  with
Chapter 28. Unfortunately, you ﬁnd that the book is no longer in your
pack.  You  must  have  left  it  somewhere  along  the  trail,  but  you  don’t
know  where.  It  could  be  anywhere  between  Georgia  and  Maine.  You
want to ﬁnd the book, but now that you have learned something about
online algorithms, you want your algorithm for ﬁnding it to have a good
competitive  ratio.  That  is,  no  matter  where  the  book  is,  if  its  distance
from you is x miles away, you would like to be sure that you do not walk
more than cx miles to ﬁnd it, for some constant c. You do not know x,
though you may assume that x ≥ 1.3

What algorithm should you use, and what constant c can you prove
bounds  the  total  distance  cx  that  you  would  have  to  walk?  Your
algorithm should work for a trail of any length, not just the 2,190-mile-
long AT.

27-2     Online scheduling to minimize average completion time
Problem 15-2 discusses scheduling to minimize average completion time
on one machine, without release times and preemption and with release
times  and  preemption.  Now  you  will  develop  an  online  algorithm  for
nonpreemptively  scheduling  a  set  of  tasks  with  release  times.  Suppose
you  are  given  a  set  S  =  {a1,  a2,  …  ,  an}  of  tasks,  where  task  ai  has
release  time  ri,  before  which  it  cannot  start,  and  requires  pi  units  of
processing time to complete once it has started. You have one computer
on  which  to  run  the  tasks.  Tasks  cannot  be  preempted,  which  is  to  say
that once started, a task must run to completion without interruption.
(See  Problem  15-2  on  page  446  for  a  more  detailed  description  of  this
problem.) Given a schedule, let Ci be the completion time of task ai, that
is, the time at which task ai completes processing. Your goal is to ﬁnd a
schedule  that  minimizes  the  average  completion  time,  that  is,  to
minimize

.

In  the  online  version  of  this  problem,  you  learn  about  task  i  only
when  it  arrives  at  its  release  time  ri,  and  at  that  point,  you  know  its

processing time pi. The ofﬂine version of this problem is NP-hard (see
Chapter 34), but you will develop a 2-competitive online algorithm.

a. Show that, if there are release times, scheduling by shortest

processing time (when the machine becomes idle, start the already
released task with the smallest processing time that has not yet run) is
not d-competitive for any constant d.

In  order  to  develop  an  online  algorithm,  consider  the  preemptive
version of this problem, which is discussed in Problem 15-2(b). One way
to  schedule  is  to  run  the  tasks  according  to  the  shortest  remaining
processing  time  (SRPT)  order.  That  is,  at  any  point,  the  machine  is
running  the  available  task  with  the  smallest  amount  of  remaining
processing time.

b. Explain how to run SRPT as an online algorithm.

c. Suppose that you run SRPT and obtain completion times

.

Show that

where the
schedule.

 are the completion times in an optimal nonpreemptive

Consider the (ofﬂine) algorithm COMPLETION-TIME-SCHEDULE.

COMPLETION-TIME-SCHEDULE(S)
1 compute  an  optimal  schedule  for  the  preemptive  version  of  the

problem

2 renumber  the  tasks  so  that  the  completion  times  in  the  optimal
preemptive  schedule  are  ordered  by  their  completion  times

3 greedily  schedule  the  tasks  nonpreemptively  in  the  renumbered

 in SRPT order

order a1, … , an

4 let C1, … , Cn be the completion times of renumbered tasks a1, … ,

an in this nonpreemptive schedule

5 return C1, … , Cn

d. Prove that

e. Prove that

 for i = 1, … , n.

 for i = 1, … , n.

f. Algorithm COMPLETION-TIME-SCHEDULE is an ofﬂine

algorithm. Explain how to modify it to produce an online algorithm.

g. Combine parts (c)–(f) to show that the online version of
COMPLETION-TIME-SCHEDULE is 2-competitive.

Chapter notes

Online  algorithms  are  widely  used  in  many  domains.  Some  good
overviews  include  the  textbook  by  Borodin  and  El-Yaniv  [68],  the
collection of surveys edited by Fiat and Woeginger [142], and the survey
by Albers [14].

The  move-to-front  heuristic  from  Section  27.2  was  analyzed  by
Sleator and Tarjan [416, 417] as part of their early work on amortized
analysis. This rule works quite well in practice.

Competitive  analysis  of  online  caching  also  originated  with  Sleator
and  Tarjan  [417].  The  randomized  marking  algorithm  was  proposed
and  analyzed  by  Fiat  et  al.  [141].  Young  [464]  surveys  online  caching
and  paging  algorithms,  and  Buchbinder  and  Naor  [76]  survey  primal-
dual online algorithms.

Speciﬁc types of online algorithms are described using other names.
Dynamic  graph  algorithms  are  online  algorithms  on  graphs,  where  at
each step a vertex or edge undergoes modiﬁcation. Typically a vertex or
edge is either inserted or deleted, or some associated property, such as
edge  weight,  changes.  Some  graph  problems  need  to  be  solved  again
after  each  change  to  the  graph,  and  a  good  dynamic  graph  algorithm
will not need to solve from scratch. For example, edges are inserted and
deleted, and after each change to the graph, the minimum spanning tree
is  recomputed.  Exercise  21.2-8  asks  such  a  question.  Similar  questions
can  be  asked  for  other  graph  algorithms,  such  as  shortest  paths,

connectivity, or matching. The ﬁrst paper in this ﬁeld is credited to Even
and Shiloach [138], who study how to maintain a shortest-path tree as
edges  are  being  deleted  from  a  graph.  Since  then  hundreds  of  papers
have been published. Demetrescu et al. [110] survey early developments
in dynamic graph algorithms.

For  massive  data  sets,  the  input  data  might  be  too  large  to  store.
Streaming  algorithms  model  this  situation  by  requiring  the  memory
used by an algorithm to be signiﬁcantly smaller than the input size. For
example, you may have a graph with n vertices and m edges with m ≫ n,
but the memory allowed may be only O(n). Or you may have n numbers,
but  the  memory  allowed  may  only  be  O(lg  n)  or
.  A  streaming
algorithm  is  measured  by  the  number  of  passes  made  over  the  data  in
addition to the running time of the algorithm. McGregor [322] surveys
streaming  algorithms  for  graphs  and  Muthukrishnan  [341]  surveys
general streaming algorithms.

1  The  path-compression  heuristic  in  Section  19.3  resembles  MOVE-TO-FRONT,  although  it
would be more accurately expressed as “move-to-next-to-front.” Unlike MOVE-TO-FRONT in
a doubly linked list, path compression can relocate multiple elements to become “next-to-front.”
2 This book is heavy. We do not recommend that you carry it on a long hike.
3 In case you’re wondering what this problem has to do with cows, some papers about it frame
the problem as a cow looking for a ﬁeld in which to graze.

