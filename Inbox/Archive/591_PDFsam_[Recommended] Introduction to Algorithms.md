16        Amortized Analysis

Imagine  that  you  join  Buff’s  Gym.  Buff  charges  a  membership  fee  of
$60 per month, plus $3 for every time you use the gym. Because you are
disciplined,  you  visit  Buff’s  Gym  every  day  during  the  month  of
November.  On  top  of  the  $60  monthly  charge  for  November,  you  pay
another 3 × $30 = $90 that month. Although you can think of your fees
as a ﬂat fee of $60 and another $90 in daily fees, you can think about it
in another way. All together, you pay $150 over 30 days, or an average
of  $5  per  day.  When  you  look  at  your  fees  in  this  way,  you  are
amortizing the monthly fee over the 30 days of the month, spreading it
out at $2 per day.

You  can  do  the  same  thing  when  you  analyze  running  times.  In  an
amortized analysis, you average the time required to perform a sequence
of  data-structure  operations  over  all  the  operations  performed.  With
amortized  analysis,  you  show  that  if  you  average  over  a  sequence  of
operations, then the average cost of an operation is small, even though a
single  operation  within  the  sequence  might  be  expensive.  Amortized
analysis  differs  from  average-case  analysis  in  that  probability  is  not
involved. An amortized analysis guarantees the average performance of
each operation in the worst case.

The ﬁrst three sections of this chapter cover the three most common
techniques used in amortized analysis. Section 16.1 starts with aggregate
analysis, in which you determine an upper bound T (n) on the total cost
of a sequence of n operations. The average cost per operation is then T
(n)/n. You take the average cost as the amortized cost of each operation,
so that all operations have the same amortized cost.

Section 16.2 covers the accounting method, in which you determine
an amortized cost of each operation. When there is more than one type
of  operation,  each  type  of  operation  may  have  a  different  amortized
cost. The accounting method overcharges some operations early in the
sequence, storing the overcharge as “prepaid credit” on speciﬁc objects
in  the  data  structure.  Later  in  the  sequence,  the  credit  pays  for
operations that are charged less than they actually cost.

Section  16.3  discusses  the  potential  method,  which  is  like  the
accounting  method  in  that  you  determine  the  amortized  cost  of  each
operation  and  may  overcharge  operations  early  on  to  compensate  for
undercharges  later.  The  potential  method  maintains  the  credit  as  the
“potential  energy”  of  the  data  structure  as  a  whole  instead  of
associating the credit with individual objects within the data structure.

We’ll use use two examples in this chapter to examine each of these
is  a  stack  with  the  additional  operation
three  methods.  One
MULTIPOP, which pops several objects at once. The other is a binary
counter  that  counts  up  from  0  by  means  of  the  single  operation
INCREMENT.

While  reading  this  chapter,  bear  in  mind  that  the  charges  assigned
during an amortized analysis are for analysis purposes only. They need
not—and should not—appear in the code. If, for example, you assign a
credit  to  an  object  x  when  using  the  accounting  method,  you  have  no
need  to  assign  an  appropriate  amount  to  some  attribute,  such  as
x.credit, in the code.

When you perform an amortized analysis, you often gain insight into
a  particular  data  structure,  and  this  insight  can  help  you  optimize  the
design.  For  example,  Section  16.4  will  use  the  potential  method  to
analyze a dynamically expanding and contracting table.

16.1    Aggregate analysis

In aggregate analysis, you show that for all n, a sequence of n operations
takes T (n) worst-case time in total. In the worst case, the average cost,
or amortized cost, per operation is therefore T (n)/n. This amortized cost
applies  to  each  operation,  even  when  there  are  several  types  of

operations  in  the  sequence.  The  other  two  methods  we  shall  study  in
this  chapter,  the  accounting  method  and  the  potential  method,  may
assign different amortized costs to different types of operations.

Stack operations

As the ﬁrst example of aggregate analysis, let’s analyze stacks that have
been augmented with a new operation. Section 10.1.3 presented the two
fundamental stack operations, each of which takes O(1) time:

PUSH(S, x) pushes object x onto stack S.

POP(S) pops the top of stack S and returns the popped object. Calling

POP on an empty stack generates an error.

Figure 16.1 The action of MULTIPOP on a stack S, shown initially in (a). The top 4 objects are
popped  by  MULTIPOP(S,  4),  whose  result  is  shown  in  (b).  The  next  operation  is
MULTIPOP(S, 7), which empties the stack—shown in (c)—since fewer than 7 objects remained.

Since each of these operations runs in O(1) time, let us consider the cost
of  each  to  be  1.  The  total  cost  of  a  sequence  of  n  PUSH  and  POP
operations is therefore n, and the actual running time for n operations is
therefore Θ(n).

Now let’s add the stack operation MULTIPOP(S, k), which removes
the  k  top  objects  of  stack  S,  popping  the  entire  stack  if  the  stack
contains fewer than k objects. Of course, the procedure assumes that k
is  positive,  and  otherwise,  the  MULTIPOP  operation  leaves  the  stack
unchanged. In the pseudocode for MULTIPOP, the operation STACK-
EMPTY  returns  TRUE  if  there  are  no  objects  currently  on  the  stack,
and FALSE otherwise. Figure 16.1 shows an example of MULTIPOP.

MULTIPOP(S, k)

1 while not STACK-EMPTY(S) and k > 0
2

POP(S)
k = k − 1

3

What  is  the  running  time  of  MULTIPOP(S,  k)  on  a  stack  of  s
objects?  The  actual  running  time  is  linear  in  the  number  of  POP
operations  actually  executed,  and  thus  we  can  analyze  MULTIPOP  in
terms of the abstract costs of 1 each for PUSH and POP. The number
of  iterations  of  the  while  loop  is  the  number  min  {s,  k}  of  objects
popped off the stack. Each iteration of the loop makes one call to POP
in  line  2.  Thus,  the  total  cost  of  MULTIPOP  is  min  {s,  k},  and  the
actual running time is a linear function of this cost.

Now  let’s  analyze  a  sequence  of  n  PUSH,  POP,  and  MULTIPOP
operations  on  an  initially  empty  stack.  The  worst-case  cost  of  a
MULTIPOP operation in the sequence is O(n), since the stack size is at
most  n.  The  worst-case  time  of  any  stack  operation  is  therefore  O(n),
and  hence  a  sequence  of  n  operations  costs  O(n2),  since  the  sequence
contains at most n MULTIPOP operations costing O(n) each. Although
this  analysis  is  correct,  the  O(n2)  result,  which  came  from  considering
the worst-case cost of each operation individually, is not tight.

Yes,  a  single  MULTIPOP  might  be  expensive,  but  an  aggregate
analysis  shows  that  any  sequence  of  n  PUSH,  POP,  and  MULTIPOP
operations on an initially empty stack has an upper bound on its cost of
O(n).  Why?  An  object  cannot  be  popped  from  the  stack  unless  it  was
ﬁrst pushed. Therefore, the number of times that POP can be called on
a  nonempty  stack,  including  calls  within  MULTIPOP,  is  at  most  the
number  of  PUSH  operations,  which  is  at  most  n.  For  any  value  of  n,
any  sequence  of  n  PUSH,  POP,  and  MULTIPOP  operations  takes  a
total of O(n) time. Averaging over the n operations gives an average cost
per  operation  of  O(n)/n  =  O(1).  Aggregate  analysis  assigns  the
amortized  cost  of  each  operation  to  be  the  average  cost.  In  this
example, therefore, all three stack operations have an amortized cost of
O(1).

To recap: although the average cost, and hence the running time, of a
stack  operation  is  O(1),  the  analysis  did  not  rely  on  probabilistic
reasoning. Instead, the analysis yielded a worst-case bound of O(n) on a
sequence of n operations. Dividing this total cost by n yielded that the
average cost per operation—that is, the amortized cost—is O(1).

Incrementing a binary counter

As  another  example  of  aggregate  analysis,  consider  the  problem  of
implementing  a  k-bit  binary  counter  that  counts  upward  from  0.  An
array A[0 : k − 1] of bits represents the counter. A binary number x that
is stored in the counter has its lowest-order bit in A[0] and its highest-

order bit in A[k − 1], so that
. Initially, x = 0, and thus
A[i] = 0 for i = 0, 1, … , k − 1. To add 1 (modulo 2k) to the value in the
counter, call the INCREMENT procedure.

INCREMENT(A, k)

1 i = 0
2 while i < k and A[i] == 1
3

A[i] = 0
i = i + 1

4
5 if i < k
6

A[i] = 1

Figure  16.2  shows  what  happens  to  a  binary  counter  when
INCREMENT  is  called  16  times,  starting  with  the  initial  value  0  and
ending  with  the  value  16.  Each  iteration  of  the  while  loop  in  lines  2–4
adds  a  1  into  position  i.  If  A[i]  =  1,  then  adding  1  ﬂips  the  bit  to  0  in
position i and yields a carry of 1, to be added into position i + 1 during
the next iteration of the loop. Otherwise, the loop ends, and then, if i <
k, A[i] must be 0, so that line 6 adds a 1 into position i, ﬂipping the 0 to
a 1. If the loop ends with i = k, then the call of INCREMENT ﬂipped
all  k  bits  from  1  to  0.  The  cost  of  each  INCREMENT  operation  is
linear in the number of bits ﬂipped.

Figure  16.2  An  8-bit  binary  counter  as  its  value  goes  from  0  to  16  by  a  sequence  of  16
INCREMENT  operations.  Bits  that  ﬂip  to  achieve  the  next  value  are  shaded  in  blue.  The
running cost for ﬂipping bits is shown at the right. The total cost is always less than twice the
total number of INCREMENT operations.

As with the stack example, a cursory analysis yields a bound that is
correct  but  not  tight.  A  single  execution  of  INCREMENT  takes  Θ(k)
time  in  the  worst  case,  in  which  all  the  bits  in  array  A  are  1.  Thus,  a
sequence  of  n  INCREMENT  operations  on  an  initially  zero  counter
takes O(nk) time in the worst case.

Although a single call of INCREMENT might ﬂip all k bits, not all
bits  ﬂip  upon  each  call.  (Note  the  similarity  to  MULTIPOP,  where  a
single  call  might  pop  many  objects,  but  not  every  call  pops  many
objects.) As Figure 16.2 shows, A[0] does ﬂip each time INCREMENT
is called. The next bit up, A[1], ﬂips only every other time: a sequence of
n INCREMENT operations on an initially zero counter causes A[1] to
ﬂip ⌊n/2⌋ times. Similarly, bit A[2] ﬂips only every fourth time, or ⌊n/4⌋
times in a sequence of n INCREMENT operations. In general, for i = 0,
1, … , k − 1, bit A[i] ﬂips ⌊n/2i
⌋ times in a sequence of n INCREMENT
operations on an initially zero counter. For i ≥ k, bit A[i] does not exist,
and so it cannot ﬂip. The total number of ﬂips in the sequence is thus

by equation (A.7) on page 1142. Thus, a sequence of n INCREMENT
operations on an initially zero counter takes O(n) time in the worst case.
The  average  cost  of  each  operation,  and  therefore  the  amortized  cost
per operation, is O(n)/n = O(1).

Exercises

16.1-1
If the set of stack operations includes a MULTIPUSH operation, which
pushes  k  items  onto  the  stack,  does  the  O(1)  bound  on  the  amortized
cost of stack operations continue to hold?

16.1-2
Show  that  if  a  DECREMENT  operation  is  included  in  the  k-bit
counter example, n operations can cost as much as Θ(nk) time.

16.1-3
Use  aggregate  analysis  to  determine  the  amortized  cost  per  operation
for  a  sequence  of  n  operations  on  a  data  structure  in  which  the  ith
operation costs i if i is an exact power of 2, and 1 otherwise.

16.2    The accounting method

In  the  accounting  method  of  amortized  analysis,  you  assign  differing
charges  to  different  operations,  with  some  operations  charged  more  or
less than they actually cost. The amount that you charge an operation is
its amortized cost. When an operation’s amortized cost exceeds its actual
cost, you assign the difference to speciﬁc objects in the data structure as
credit. Credit can help pay for later operations whose amortized cost is
less than their actual cost. Thus, you can view the amortized cost of an
operation as being split between its actual cost and credit that is either
deposited or used up. Different operations may have different amortized

costs.  This  method  differs  from  aggregate  analysis,  in  which  all
operations have the same amortized cost.

You must choose the amortized costs of operations carefully. If you
want to use amortized costs to show that in the worst case the average
cost  per  operation  is  small,  you  must  ensure  that  the  total  amortized
cost of a sequence of operations provides an upper bound on the total
actual  cost  of  the  sequence.  Moreover,  as  in  aggregate  analysis,  the
upper bound must apply to all sequences of operations. Let’s denote the
actual cost of the ith operation by ci and the amortized cost of the ith
operation by ĉi. Then you need to have

for  all  sequences  of  n  operations.  The  total  credit  stored  in  the  data
structure is the difference between the total amortized cost and the total
actual  cost,  or
.  By  inequality  (16.1),  the  total  credit
associated  with  the  data  structure  must  be  nonnegative  at  all  times.  If
you  ever  allowed  the  total  credit  to  become  negative  (the  result  of
undercharging  early  operations  with  the  promise  of  repaying  the
account  later  on),  then  the  total  amortized  costs  incurred  at  that  time
would  be  below  the  total  actual  costs  incurred.  In  that  case,  for  the
sequence of operations up to that time, the total amortized cost would
not  be  an  upper  bound  on  the  total  actual  cost.  Thus,  you  must  take
care that the total credit in the data structure never becomes negative.

Stack operations

To illustrate the accounting method of amortized analysis, we return to
the stack example. Recall that the actual costs of the operations were

PUSH
POP
MULTIPOPmin  {s,

1,
1,

k},

where k is the argument supplied to MULTIPOP and s is the stack size
when it is called. Let us assign the following amortized costs:

2,
PUSH
POP
0,
MULTIPOP0.

The amortized cost of MULTIPOP is a constant (0), whereas the actual
cost  is  variable,  and  thus  all  three  amortized  costs  are  constant.  In
general, the amortized costs of the operations under consideration may
differ from each other, and they may even differ asymptotically.

Now  let’s  see  how  to  pay  for  any  sequence  of  stack  operations  by
charging  the  amortized  costs.  Let  $1  represent  each  unit  of  cost.  At
ﬁrst,  the  stack  is  empty.  Recall  the  analogy  of  Section  10.1.3  between
the  stack  data  structure  and  a  stack  of  plates  in  a  cafeteria.  Upon
pushing a plate onto the stack, use $1 to pay the actual cost of the push,
leaving a credit of $1 (out of the $2 charged). Place that $1 of credit on
top of the plate. At any point in time, every plate on the stack has $1 of
credit on it.

The $1 stored on the plate serves to prepay the cost of popping the
plate from the stack. A POP operation incurs no charge: pay the actual
cost of popping a plate by taking the $1 of credit off the plate. Thus, by
charging  the  PUSH  operation  a  little  bit  more,  we  can  view  the  POP
operation as free.

Moreover, the MULTIPOP operation also incurs no charge, since it’s
just  repeated  POP  operations,  each  of  which  is  free.  If  a  MULTIPOP
operation  pops  k  plates,  then  the  actual  cost  is  paid  by  the  k  dollars
stored on the k plates. Because each plate on the stack has $1 of credit
on  it,  and  the  stack  always  has  a  nonnegative  number  of  plates,  the
amount  of  credit  is  always  nonnegative.  Thus,  for  any  sequence  of  n
PUSH, POP, and MULTIPOP operations, the total amortized cost is an
upper bound on the total actual cost. Since the total amortized cost is
O(n), so is the total actual cost.

Incrementing a binary counter

As  another  illustration  of  the  accounting  method,  let’s  analyze  the
INCREMENT  operation  on  a  binary  counter  that  starts  at  0.  Recall
that the running time of this operation is proportional to the number of
bits ﬂipped, which serves as the cost for this example. Again, we’ll use
$1 to represent each unit of cost (the ﬂipping of a bit in this example).

For  the  amortized  analysis,  the  amortized  cost  to  set  a  0-bit  to  1  is
$2. When a bit is set to 1, $1 of the $2 pays to actually set the bit. The
second $1 resides on the bit as credit to be used later if and when the bit
is reset to 0. At any point in time, every 1-bit in the counter has $1 of
credit  on  it,  and  thus  resetting  a  bit  to  0  can  be  viewed  as  costing
nothing, and the $1 on the bit prepays for the reset.

Here is how to determine the amortized cost of INCREMENT. The
cost  of  resetting  the  bits  to  0  within  the  while  loop  is  paid  for  by  the
dollars on the bits that are reset. The INCREMENT procedure sets at
most  one  bit  to  1,  in  line  6,  and  therefore  the  amortized  cost  of  an
INCREMENT  operation  is  at  most  $2.  The  number  of  1-bits  in  the
counter  never  becomes  negative,  and  thus  the  amount  of  credit  stays
nonnegative  at  all  times.  Thus,  for  n  INCREMENT  operations,  the
total amortized cost is O(n), which bounds the total actual cost.

Exercises

16.2-1
You  perform  a  sequence  of  PUSH  and  POP  operations  on  a  stack
whose  size  never  exceeds  k.  After  every  k  operations,  a  copy  of  the
entire stack is made automatically, for backup purposes. Show that the
cost  of  n  stack  operations,  including  copying  the  stack,  is  O(n)  by
assigning suitable amortized costs to the various stack operations.

16.2-2
Redo Exercise 16.1-3 using an accounting method of analysis.

16.2-3
You wish not only to increment a counter but also to reset it to 0 (i.e.,
make all bits in it 0). Counting the time to examine or modify a bit as
Θ(1), show how to implement a counter as an array of bits so that any

sequence  of  n  INCREMENT  and  RESET  operations  takes  O(n)  time
on an initially zero counter. (Hint: Keep a pointer to the high-order 1.)

16.3    The potential method

Instead  of  representing  prepaid  work  as  credit  stored  with  speciﬁc
objects in the data structure, the potential method of amortized analysis
represents  the  prepaid  work  as  “potential  energy,”  or  just  “potential,”
which can be released to pay for future operations. The potential applies
to the data structure as a whole rather than to speciﬁc objects within the
data structure.

The potential method works as follows. Starting with an initial data
structure D0, a sequence of n operations occurs. For each i = 1, 2, … , n,
let ci be the actual cost of the ith operation and Di be the data structure
that  results  after  applying  the  ith  operation  to  data  structure  Di−1.  A
potential  function  Φ  maps  each  data  structure  Di  to  a  real  number
Φ(Di),  which  is  the  potential  associated  with  Di.  The  amortized  cost  ĉi
of the ith operation with respect to potential function Φ is deﬁned by

The amortized cost of each operation is therefore its actual cost plus the
change  in  potential  due  to  the  operation.  By  equation  (16.2),  the  total
amortized cost of the n operations is

The  second  equation  follows  from  equation  (A.12)  on  page  1143
because the Φ(Di) terms telescope.

If you can deﬁne a potential function Φ so that Φ(Dn) ≥ Φ(D0), then
 gives an upper bound on the total actual

the total amortized cost

.  In  practice,  you  don’t  always  know  how  many  operations
cost
might be performed. Therefore, if you require that Φ(Di) ≥ Φ(D0) for all
i, then you guarantee, as in the accounting method, that you’ve paid in
advance. It’s usually simplest to just deﬁne Φ(D0) to be 0 and then show
that Φ(Di) ≥ 0 for all i. (See Exercise 16.3-1 for an easy way to handle
cases in which Φ(D0) ≠ 0.)

Intuitively,  if  the  potential  difference  Φ(Di)  −  Φ(Di−1)  of  the  ith
operation  is  positive,  then  the  amortized  cost  ĉi  represents  an
overcharge to the ith operation, and the potential of the data structure
increases. If the potential difference is negative, then the amortized cost
represents an undercharge to the ith operation, and the decrease in the
potential pays for the actual cost of the operation.

The  amortized  costs  deﬁned  by  equations  (16.2)  and  (16.3)  depend
on the choice of the potential function Φ. Different potential functions
may  yield  different  amortized  costs,  yet  still  be  upper  bounds  on  the
actual  costs.  You  will  often  ﬁnd  trade-offs  that  you  can  make  in
choosing  a  potential  function.  The  best  potential  function  to  use
depends on the desired time bounds.

Stack operations

To illustrate the potential method, we return once again to the example
of  the  stack  operations  PUSH,  POP,  and  MULTIPOP.  We  deﬁne  the
potential function Φ on a stack to be the number of objects in the stack.
The  potential  of  the  empty  initial  stack  D0  is  Φ(D0)  =  0.  Since  the
number of objects in the stack is never negative, the stack Di that results
after the ith operation has nonnegative potential, and thus

Φ(Di) ≥ 0

= Φ(D0).

The  total  amortized  cost  of  n  operations  with  respect  to  Φ  therefore
represents an upper bound on the actual cost.

Now  let’s  compute  the  amortized  costs  of  the  various  stack
operations.  If  the  ith  operation  on  a  stack  containing  s  objects  is  a
PUSH operation, then the potential difference is

Φ(Di) − Φ(Di−1) = (s + 1) − s

= 1.

By equation (16.2), the amortized cost of this PUSH operation is

ĉi = ci + Φ(Di) − Φ(Di−1)

= 1 + 1
= 2.

ith  operation  on  the  stack  of  s  objects

Suppose  that  the
is
MULTIPOP(S,  k),  which  causes  k′  =  min  {s,  k}  objects  to  be  popped
off  the  stack.  The  actual  cost  of  the  operation  is  k′,  and  the  potential
difference is

Φ(Di) − Φ(Di−1) = −k′.

Thus, the amortized cost of the MULTIPOP operation is

ĉi = ci + Φ(Di) − Φ(Di−1)

= k′ − k′
= 0.

Similarly, the amortized cost of an ordinary POP operation is 0.

The amortized cost of each of the three operations is O(1), and thus
the  total  amortized  cost  of  a  sequence  of  n  operations  is  O(n).  Since
Φ(Di)  ≥  Φ(D0),  the  total  amortized  cost  of  n  operations  is  an  upper
bound  on  the  total  actual  cost.  The  worst-case  cost  of  n  operations  is
therefore O(n).

Incrementing a binary counter

As another example of the potential method, we revisit incrementing a
k-bit binary counter. This time, the potential of the counter after the ith

INCREMENT  operation  is  deﬁned  to  be  the  number  of  1-bits  in  the
counter after the ith operation, which we’ll denote by bi.

Here  is  how  to  compute  the  amortized  cost  of  an  INCREMENT
operation.  Suppose  that  the  ith  INCREMENT  operation  resets  ti  bits
to 0. The actual cost ci of the operation is therefore at most ti + 1, since
in addition to resetting ti bits, it sets at most one bit to 1. If bi = 0, then
the ith operation had reset all k bits to 0, and so bi−1 = ti = k. If bi > 0,
then bi = bi−1 −ti +1. In either case, bi ≤ bi−1 − ti + 1, and the potential
difference is

Φ(Di) − Φ(Di−1) ≤ (bi−1 − ti + 1) − bi−1
= 1 − ti.

The amortized cost is therefore

ĉi = ci + Φ(Di) − Φ(Di−1)
≤ (ti + 1) + (1 − ti)
= 2.

If the counter starts at 0, then Φ(D0) = 0. Since Φ(Di) ≥ 0 for all i, the
total amortized cost of a sequence of n INCREMENT operations is an
upper  bound  on  the  total  actual  cost,  and  so  the  worst-case  cost  of  n
INCREMENT operations is O(n).

The  potential  method  provides  a  simple  and  clever  way  to  analyze
the counter even when it does not start at 0. The counter starts with b0
1-bits, and after n INCREMENT operations it has bn 1-bits, where 0 ≤
b0, bn ≤ k. Rewrite equation (16.3) as

Since  Φ(D0)  =  b0,  Φ(Dn)  =  bn,  and  ĉi  ≤  2  for  all  1  ≤  i  ≤  n,  the  total
actual cost of n INCREMENT operations is

In particular, b0 ≤ k means that as long as k = O(n), the total actual cost
is  O(n).  In  other  words,  if  at  least  n  =  Ω(k)  INCREMENT  operations
occur,  the  total  actual  cost  is  O(n),  no  matter  what  initial  value  the
counter contains.

Exercises

16.3-1
Suppose you have a potential function Φ such that Φ(Di) ≥ Φ(D0) for all
i, but Φ(D0) ≠ 0. Show that there exists a potential function Φ′ such that
Φ′(D0) = 0, Φ′(Di) ≥ 0 for all i ≥ 1, and the amortized costs using Φ′ are
the same as the amortized costs using Φ.

16.3-2
Redo Exercise 16.1-3 using a potential method of analysis.

16.3-3
Consider  an  ordinary  binary  min-heap  data  structure  supporting  the
instructions INSERT and EXTRACT-MIN that, when there are n items
in the heap, implements each operation in O(lg n) worst-case time. Give
a potential function Φ such that the amortized cost of INSERT is O(lg
n)  and  the  amortized  cost  of  EXTRACT-MIN  is  O(1),  and  show  that
your  potential  function  yields  these  amortized  time  bounds.  Note  that
in the analysis, n is the number of items currently in the heap, and you
do not know a bound on the maximum number of items that can ever
be stored in the heap.

16.3-4
What  is  the  total  cost  of  executing  n  of  the  stack  operations  PUSH,
POP,  and  MULTIPOP,  assuming  that  the  stack  begins  with  s0  objects
and ﬁnishes with sn objects?

16.3-5
Show  how  to  implement  a  queue  with  two  ordinary  stacks  (Exercise
10.1-7)  so  that  the  amortized  cost  of  each  ENQUEUE  and  each
DEQUEUE operation is O(1).

16.3-6
Design  a  data  structure  to  support  the  following  two  operations  for  a
dynamic multiset S of integers, which allows duplicate values:

INSERT(S, x) inserts x into S.

DELETE-LARGER-HALF(S) deletes the largest ⌈|S|/2⌉ elements from

S.

Explain how to implement this data structure so that any sequence of m
INSERT  and  DELETE-LARGER-HALF  operations  runs  in  O(m)
time.  Your  implementation  should  also  include  a  way  to  output  the
elements of S in O(|S|) time.

16.4    Dynamic tables

When  you  design  an  application  that  uses  a  table,  you  do  not  always
know  in  advance  how  many  items  the  table  will  hold.  You  might
allocate space for the table, only to ﬁnd out later that it is not enough.
The program must then reallocate the table with a larger size and copy
all  items  stored  in  the  original  table  over  into  the  new,  larger  table.
Similarly,  if  many  items  have  been  deleted  from  the  table,  it  might  be
worthwhile  to  reallocate  the  table  with  a  smaller  size.  This  section
studies this problem of dynamically expanding and contracting a table.
Amortized analyses will show that the amortized cost of insertion and
deletion  is  only  O(1),  even  though  the  actual  cost  of  an  operation  is
large  when  it  triggers  an  expansion  or  a  contraction.  Moreover,  you’ll
see  how  to  guarantee  that  the  unused  space  in  a  dynamic  table  never
exceeds a constant fraction of the total space.

Let’s  assume  that  the  dynamic  table  supports  the  operations
TABLE-INSERT and TABLE-DELETE. TABLE-INSERT inserts into
the table an item that occupies a single slot, that is, a space for one item.

Likewise,  TABLE-DELETE  removes  an  item  from  the  table,  thereby
freeing  a  slot.  The  details  of  the  data-structuring  method  used  to
organize the table are unimportant: it could be a stack (Section 10.1.3),
a heap (Chapter 6), a hash table (Chapter 11), or something else.

It  is  convenient  to  use  a  concept  introduced  in  Section  11.2,  where
we  analyzed  hashing.  The  load  factor  α(T)  of  a  nonempty  table  T  is
deﬁned  as  the  number  of  items  stored  in  the  table  divided  by  the  size
(number  of  slots)  of  the  table.  An  empty  table  (one  with  no  slots)  has
size  0,  and  its  load  factor  is  deﬁned  to  be  1.  If  the  load  factor  of  a
dynamic table is bounded below by a constant, the unused space in the
table  is  never  more  than  a  constant  fraction  of  the  total  amount  of
space.

We start by analyzing a dynamic table that allows only insertion and
then move on to the more general case that supports both insertion and
deletion.

16.4.1    Table expansion

Let’s assume that storage for a table is allocated as an array of slots. A
table ﬁlls up when all slots have been used or, equivalently, when its load
factor is 1.1 In some software environments, upon an attempt to insert
an  item  into  a  full  table,  the  only  alternative  is  to  abort  with  an  error.
The  scenario  in  this  section  assumes,  however,  that  the  software
environment, like many modern ones, provides a memory-management
system  that  can  allocate  and  free  blocks  of  storage  on  request.  Thus,
upon inserting an item into a full table, the system can expand the table
by  allocating  a  new  table  with  more  slots  than  the  old  table  had.
Because the table must always reside in contiguous memory, the system
must allocate a new array for the larger table and then copy items from
the old table into the new table.

A common heuristic allocates a new table with twice as many slots as
the  old  one.  If  the  only  table  operations  are  insertions,  then  the  load
factor of the table is always at least 1/2, and thus the amount of wasted
space never exceeds half the total space in the table.

The TABLE-INSERT procedure on the following page assumes that
T  is  an  object  representing  the  table.  The  attribute  T.table  contains  a

pointer  to  the  block  of  storage  representing  the  table,  T.num  contains
the  number  of  items  in  the  table,  and  T.size  gives  the  total  number  of
slots in the table. Initially, the table is empty: T.num = T.size = 0.

There  are  two  types  of  insertion  here:  the  TABLE-INSERT
procedure itself and the elementary insertion into a table in lines 6 and
10.  We  can  analyze  the  running  time  of  TABLE-INSERT  in  terms  of
the  number  of  elementary  insertions  by  assigning  a  cost  of  1  to  each
elementary  insertion.  In  most  computing  environments,  the  overhead
for allocating an initial table in line 2 is constant and the overhead for
allocating and freeing storage in lines 5 and 7 is dominated by the cost
of  transfer-ring  items  in  line  6.  Thus,  the  actual  running  time  of
TABLE-INSERT  is  linear  in  the  number  of  elementary  insertions.  An
expansion occurs when lines 5–9 execute.

TABLE-INSERT(T, x)
  1 if T.size == 0
  2

allocate T.table with 1 slot
T.size = 1
  3
  4 if T.num == T.size
  5

  7

  6

allocate new-table with 2 · T.size slots
insert all items in T.table into new-table
free T.table
T.table = new-table
T.size = 2 · T.size
  9
10 insert x into T.table
11 T.num = T.num + 1

  8

Now,  we’ll  use  all  three  amortized  analysis  techniques  to  analyze  a
sequence of n TABLE-INSERT operations on an initially empty table.
First, we need to determine the actual cost ci of the ith operation. If the
current table has room for the new item (or if this is the ﬁrst operation),
then ci = 1, since the only elementary insertion performed is the one in
line  10.  If  the  current  table  is  full,  however,  and  an  expansion  occurs,
then ci = i: the cost is 1 for the elementary insertion in line 10 plus i − 1

for the items copied from the old table to the new table in line 6. For n
operations, the worst-case cost of an operation is O(n), which leads to
an upper bound of O(n2) on the total running time for n operations.

This  bound  is  not  tight,  because  the  table  rarely  expands  in  the
course of n TABLE-INSERT operations. Speciﬁcally, the ith operation
causes  an  expansion  only  when  i  −  1  is  an  exact  power  of  2.  The
amortized cost of an operation is in fact O(1), as an aggregate analysis
shows. The cost of the ith operation is

The total cost of n TABLE-INSERT operations is therefore

because at most n operations cost 1 each and the costs of the remaining
operations  form  a  geometric  series.  Since  the  total  cost  of  n  TABLE-
INSERT  operations  is  bounded  by  3n,  the  amortized  cost  of  a  single
operation is at most 3.

Figure  16.3  Analysis  of  table  expansion  by  the  accounting  method.  Each  call  of  TABLE-
INSERT charges $3 as follows: $1 to pay for the elementary insertion, $1 on the item inserted as
prepayment for it to be reinserted later, and $1 on an item that was already in the table, also as
prepayment for reinsertion. (a) The table immediately after an expansion, with 8 slots, 4 items
(tan slots), and no stored credit. (b)–(e) After each of 4 calls to TABLE-INSERT, the table has
one more item, with $1 stored on the new item and $1 stored on one of the 4 items that were
present immediately after the expansion. Slots with these new items are blue. (f) Upon the next
call to TABLE-INSERT, the table is full, and so it expands again. Each item had $1 to pay for it
to be reinserted. Now the table looks as it did in part (a), with no stored credit but 16 slots and 8
items.

The  accounting  method  can  provide  some  intuition  for  why  the
amortized  cost  of  a  TABLE-INSERT  operation  should  be  3.  You  can
think  of  each  item  paying  for  three  elementary  insertions:  inserting
itself  into  the  current  table,  moving  itself  the  next  time  that  the  table
expands, and moving some other item that was already in the table the
next time that the table expands. For example, suppose that the size of
the table is m immediately after an expansion, as shown in Figure 16.3
for  m  =  8.  Then  the  table  holds  m/2  items,  and  it  contains  no  credit.
Each  call  of  TABLE-INSERT  charges  $3.  The  elementary  insertion
that  occurs  immediately  costs  $1.  Another  $1  resides  on  the  item
inserted as credit. The third $1 resides as credit on one of the m/2 items
already  in  the  table.  The  table  will  not  ﬁll  again  until  another  m/2  −  1
items  have  been  inserted,  and  thus,  by  the  time  the  table  contains  m
items and is full, each item has $1 on it to pay for it to be reinserted it
during the expansion.

Now, let’s see how to use the potential method. We’ll use it again in
Section 16.4.2 to design a TABLE-DELETE operation that has an O(1)
amortized  cost  as  well.  Just  as  the  accounting  method  had  no  stored
credit  immediately  after  an  expansion—that  is,  when  T.num  =  T.size/2
—let’s  deﬁne  the  potential  to  be  0  when  T.num  =  T.size/2.  As
elementary  insertions  occur,  the  potential  needs  to  increase  enough  to
pay for all the reinsertions that will happen when the table next expands.
The  table  ﬁlls  after  another  T.size/2  calls  of  TABLE-INSERT,  when
T.num  =  T.size.  The  next  call  of  TABLE-INSERT  after  these  T.size/2
calls triggers an expansion with a cost of T.size to reinsert all the items.
Therefore,  over  the  course  of  T.size/2  calls  of  TABLE-INSERT,  the
potential  must  increase  from  0  to  T.size.  To  achieve  this  increase,  let’s
design the potential so that each call of TABLE-INSERT increases it by

until the table expands. You can see that the potential function

equals  0  immediately  after  the  table  expands,  when  T.num  =  T.size/2,
and  it  increases  by  2  upon  each  insertion  until  the  table  ﬁlls.  Once  the
table ﬁlls, that is, when T.num = T.size, the potential Φ(T) equals T.size.
The  initial  value  of  the  potential  is  0,  and  since  the  table  is  always  at
least  half  full,  T.num  ≥  T.size/2,  which  implies  that  Φ(T)  is  always
nonnegative.  Thus,  the  sum  of  the  amortized  costs  of  n  TABLE-
INSERT  operations  gives  an  upper  bound  on  the  sum  of  the  actual
costs.

To  analyze  the  amortized  costs  of  table  operations,  it  is  convenient
to  think  in  terms  of  the  change  in  potential  due  to  each  operation.
Letting  Φi  denote  the  potential  after  the  ith  operation,  we  can  rewrite
equation (16.2) as

ĉi = ci + Φi − Φi−1
= ci + ΔΦi,

where  ΔΦi  is  the  change  in  potential  due  to  the  ith  operation.  First,
consider  the  case  when  the  ith  insertion  does  not  cause  the  table  to
expand. In this case, ΔΦi is 2. Since the actual cost ci is 1, the amortized
cost is

ĉi = ci + ΔΦi
= 1 + 2

= 3.

Now,  consider  the  change  in  potential  when  the  table  does  expand
during  the  ith  insertion  because  it  was  full  immediately  before  the
insertion. Let numi denote the number of items stored in the table after
the ith operation and sizei denote the total size of the table after the ith
operation,  so  that  sizei−1  =  numi−1  =  i  −  1  and  therefore  Φi−1  =
2(sizei−1  −  sizei−1/2)  =  sizei−1  =  i  −  1.  Immediately  after  the
expansion,  the  potential  goes  down  to  0,  and  then  the  new  item  is
inserted, causing the potential to increase to Φi = 2. Thus, when the ith
insertion  triggers  an  expansion,  ΔΦi  =  2  −  (i  −  1)  =  3  −  i.  When  the
table  expands  in  the  ith  TABLE-INSERT  operation,  the  actual  cost  ci
equals  i  (to  reinsert  i  −  1  items  and  insert  the  ith  item),  giving  an
amortized cost of

ĉi = ci + ΔΦi
= i + (3 − i)
= 3.

Figure 16.4 plots the values of numi, sizei, and Φi against i. Notice how
the potential builds to pay for expanding the table.

Figure 16.4 The effect of a sequence of n TABLE-INSERT operations on the number numi of
items in the table (the brown line), the number sizei of slots in the table (the blue line), and the
potential  Φi  =  2(numi  −  sizei/2)  (the  red  line),  each  being  measured  after  the  ith  operation.
Immediately before an expansion, the potential has built up to the number of items in the table,
and therefore it can pay for moving all the items to the new table. Afterward, the potential drops
to 0, but it immediately increases by 2 upon insertion of the item that caused the expansion.

16.4.2    Table expansion and contraction

To  implement  a  TABLE-DELETE  operation,  it  is  simple  enough  to
remove the speciﬁed item from the table. In order to limit the amount of
wasted  space,  however,  you  might  want  to  contract  the  table  when  the
load factor becomes too small. Table contraction is analogous to table
expansion:  when  the  number  of  items  in  the  table  drops  too  low,
allocate a new, smaller table and then copy the items from the old table
into  the  new  one.  You  can  then  free  the  storage  for  the  old  table  by
returning it to the memory-management system. In order to not waste
space,  yet  keep  the  amortized  costs  low,  the  insertion  and  deletion
procedures should preserve two properties:

the  load  factor  of  the  dynamic  table  is  bounded  below  by  a
positive constant, as well as above by 1, and

the  amortized  cost  of  a  table  operation  is  bounded  above  by  a
constant.

The  actual  cost  of  each  operation  equals  the  number  of  elementary
insertions or deletions.

You might think that if you double the table size upon inserting an
item  into  a  full  table,  then  you  should  halve  the  size  when  deleting  an
item  that  would  cause  the  table  to  become  less  than  half  full.  This
strategy  does  indeed  guarantee  that  the  load  factor  of  the  table  never
drops below 1/2. Unfortunately, it can also cause the amortized cost of
an operation to be quite large. Consider the following scenario. Perform
n operations on a table T of size n/2, where n is an exact power of 2. The
ﬁrst n/2 operations are insertions, which by our previous analysis cost a
total of Θ(n). At the end of this sequence of insertions, T.num = T.size
= n/2. For the second n/2 operations, perform the following sequence:

insert,  delete,  delete,  insert,  insert,  delete,  delete,  insert,  insert,
….

The  ﬁrst  insertion  causes  the  table  to  expand  to  size  n.  The  two
deletions  that  follow  cause  the  table  to  contract  back  to  size  n/2.  Two
further  insertions  cause  another  expansion,  and  so  forth.  The  cost  of
each  expansion  and  contraction  is  Θ(n),  and  there  are  Θ(n)  of  them.
Thus, the total cost of the n operations is Θ(n2), making the amortized
cost of an operation Θ(n).

The  problem  with  this  strategy  is  that  after  the  table  expands,  not
enough  deletions  occur  to  pay  for  a  contraction.  Likewise,  after  the
table  contracts,  not  enough  insertions  take  place  to  pay  for  an
expansion.

How can we solve this problem? Allow the load factor of the table to
drop  below  1/2.  Speciﬁcally,  continue  to  double  the  table  size  upon
inserting an item into a full table, but halve the table size when deleting
an item causes the table to become less than 1/4 full, rather than 1/2 full
as before. The load factor of the table is therefore bounded below by the
constant 1/4, and the load factor is 1/2 immediately after a contraction.

An  expansion  or  contraction  should  exhaust  all  the  built-up
potential, so that immediately after expansion or contraction, when the
load factor is 1/2, the table’s potential is 0. Figure 16.5 shows the idea.
As the load factor deviates from 1/2, the potential increases so that by
the  time  an  expansion  or  contraction  occurs,  the  table  has  garnered
sufﬁcient  potential  to  pay  for  copying  all  the  items  into  the  newly
allocated  table.  Thus,  the  potential  function  should  grow  to  T.num  by
the  time  that  the  load  factor  has  either  increased  to  1  or  decreased  to
1/4.  Immediately  after  either  expanding  or  contracting  the  table,  the
load factor goes back to 1/2 and the table’s potential reduces back to 0.

Figure 16.5 How to think about the potential function Φ for table insertion and deletion. When
the load factor α is 1/2, the potential is 0. In order to accumulate sufﬁcient potential to pay for
reinserting  all  T.size  items  when  the  table  ﬁlls,  the  potential  needs  to  increase  by  2  upon  each
insertion  when  α  ≥  1/2.  Correspondingly,  the  potential  decreases  by  2  upon  each  deletion  that
leaves α ≥ 1/2. In order to accrue enough potential to cover the cost of reinserting all  T.size/4
items when the table contracts, the potential needs to increase by 1 upon each deletion when α <
1/2,  and  correspondingly  the  potential  decreases  by  1  upon  each  insertion  that  leaves  α  <  1/2.
The red area represents load factors less than 1/4, which are not allowed.

We  omit  the  code  for  TABLE-DELETE,  since  it  is  analogous  to
TABLE-INSERT.  We  assume  that  if  a  contraction  occurs  during
TABLE-DELETE, it occurs after the item is deleted from the table. The
analysis assumes that whenever the number of items in the table drops
to 0, the table occupies no storage. That is, if T.num = 0, then T.size =
0.

How do we design a potential function that gives constant amortized
time  for  both  insertion  and  deletion?  When  the  load  factor  is  at  least

1/2,  the  same  potential  function,  Φ(T)  =  2(T.num  −  T.size/2),  that  we
used  for  insertion  still  works.  When  the  table  is  at  least  half  full,  each
insertion increases the potential by 2 if the table does not expand, and
each  deletion  reduces  the  potential  by  2  if  it  does  not  cause  the  load
factor to drop below 1/2.

What about when the load factor is less than 1/2, that is, when 1/4 ≤
α(T)  <  1/2?  As  before,  when  α(T)  =  1/2,  so  that  T.num  =  T.size/2,  the
potential Φ(T) should be 0. To get the load factor from 1/2 down to 1/4,
T.size/4 deletions need to occur, at which time T.num = T.size/4. To pay
for  all  the  reinsertions,  the  potential  must  increase  from  0  to  T.size/4
over  these  T.size/4  deletions.  Therefore,  for  each  call  of  TABLE-
DELETE until the table contracts, the potential should increase by

Likewise, when α < 1/2, each call of TABLE-INSERT should decrease
the potential by 1. When 1/4 ≤ α(T) < 1/2, the potential function
Φ(T) = T.size/2 − T.num
produces this desired behavior.

Putting the two cases together, we get the potential function

The potential of an empty table is 0 and the potential is never negative.
Thus, the total amortized cost of a sequence of operations with respect
to  Φ  provides  an  upper  bound  on  the  actual  cost  of  the  sequence.
Figure  16.6  illustrates  how  the  potential  function  behaves  over  a
sequence of insertions and deletions.

Now,  let’s  determine  the  amortized  costs  of  each  operation.  As
before, let numi denote the number of items stored in the table after the
ith  operation,  sizei  denote  the  total  size  of  the  table  after  the  ith
operation, αi = numi/sizei denote the load factor after the ith operation,
Φi  denote  the  potential  after  the  ith  operation,  and  ΔΦi  denote  the

change in potential due to the ith operation. Initially, num0 = 0, size0 =
0, and Φ0 = 0.

The  cases  in  which  the  table  does  not  expand  or  contract  and  the
load factor does not cross α = 1/2 are straightforward. As we have seen,
if αi−1 ≥ 1/2 and the ith operation is an insertion that does not cause the
table to expand, then ΔΦi = 2. Likewise, if the ith operation is a deletion
and  αi  ≥  1/2,  then  ΔΦi  =  −2.  Furthermore,  if  αi−1  <  1/2  and  the  ith
operation is a deletion that does not trigger a contraction, then ΔΦi = 1,
and if the ith operation is an insertion and αi < 1/2, then ΔΦi = −1. In
other words, if no expansion or contraction occurs and the load factor
does not cross α = 1/2, then

if  the  load  factor  stays  at  or  above  1/2,  then  the  potential
increases by 2 for an insertion and decreases by 2 for a deletion,
and

if the load factor stays below 1/2, then the potential increases by 1
for a deletion and decreases by 1 for an insertion.

In  each  of  these  cases,  the  actual  cost  ci  of  the  ith  operation  is  just  1,
and so

Figure 16.6 The effect of a sequence of n TABLE-INSERT and TABLE-DELETE operations
on the number numi of items in the table (the brown line), the number sizei of slots in the table
(the blue line), and the potential (the red line)

where αi = numi/sizei, each measured after the ith operation. Immediately before an expansion
or contraction, the potential has built up to the number of items in the table, and therefore it
can pay for moving all the items to the new table.

if  the  ith  operation  is  an  insertion,  its  amortized  cost  ĉi  is  ci  +
ΔΦi,  which  is  1  +  2  =  3  if  the  load  factor  stays  at  or  above  1/2,
and 1 + (−1) = 0 if the load factor stays below 1/2, and

if the ith operation is a deletion, its amortized cost ĉi is ci + ΔΦi,
which is 1 + (−2) = −1 if the load factor stays at or above 1/2, and
1 + 1 = 2 if the load factor stays below 1/2.

Four cases remain: an insertion that takes the load factor from below
1/2 to 1/2, a deletion that takes the load factor from 1/2 to below 1/2, a
deletion  that  causes  the  table  to  contract,  and  an  insertion  that  causes
the  table  to  expand.  We  analyzed  that  last  case  at  the  end  of  Section
16.4.1 to show that its amortized cost is 3.

When the ith operation is a deletion that causes the table to contract,
we  have  numi−1  =  sizei−1/4  before  the  contraction,  then  the  item  is
deleted,  and  ﬁnally  numi  =  sizei/2  −  1  after  the  contraction.  Thus,  by
equation (16.5) we have

Φi−1 = sizei−1/2 − numi−1
= sizei−1/2 − sizei−1/4
= sizei−1/4,

which  also  equals  the  actual  cost  ci  of  deleting  one  item  and  copying
sizei−1/4 − 1 items into the new, smaller table. Since numi = sizei/2 − 1
after the operation has completed, αi < 1/2, and so

Φi = sizei/2 − numi

= 1,

giving  ΔΦi  =  1  −  sizei−1/4.  Therefore,  when  the  ith  operation  is  a
deletion that triggers a contraction, its amortized cost is

ĉi = ci + ΔΦi

= sizei−1/4 + (1 − sizei−1/4)
= 1.

Finally,  we  handle  the  cases  where  the  load  factor  ﬁts  one  case  of
equation  (16.5)  before  the  operation  and  the  other  case  afterward.  We
start  with  deletion,  where  we  have  numi−1  =  sizei−1/2,  so  that  αi−1  =
1/2,  beforehand,  and  numi  =  sizei/2−1,  so  that  αi  <  1/2  afterward.
Because αi−1 = 1/2, we have Φi−1 = 0, and because αi < 1/2, we have Φi
=  sizei/2  −  numi  =  1.  Thus  we  get  that  ΔΦi  =  1  −  0  =  1.  Since  the  ith
operation is a deletion that does not cause a contraction, the actual cost
ci equals 1, and the amortized cost ĉi is ci + ΔΦi = 1 + 1 = 2.

Conversely,  if  the  ith  operation  is  an  insertion  that  takes  the  load
factor  from  below  1/2  to  equaling  1/2,  the  change  in  potential  ΔΦi
equals −1. Again, the actual cost ci is 1, and now the amortized cost ĉi
is ci + ΔΦi = 1 + (−1) = 0.

In summary, since the amortized cost of each operation is bounded
above by a constant, the actual time for any sequence of n operations on
a dynamic table is O(n).

Exercises

16.4-1
Using the potential method, analyze the amortized cost of the ﬁrst table
insertion.

16.4-2
You wish to implement a dynamic, open-address hash table. Why might
you consider the table to be full when its load factor reaches some value
α that is strictly less than 1? Describe brieﬂy how to make insertion into
a dynamic, open-address hash table run in such a way that the expected
value  of  the  amortized  cost  per  insertion  is  O(1).  Why  is  the  expected
value  of  the  actual  cost  per  insertion  not  necessarily  O(1)  for  all
insertions?

16.4-3
Discuss how to use the accounting method to analyze both the insertion
and deletion operations, assuming that the table doubles in size when its
load  factor  exceeds  1  and  the  table  halves  in  size  when  its  load  factor
goes below 1/4.

16.4-4
Suppose that instead of contracting a table by halving its size when its
load  factor  drops  below  1/4,  you  contract  the  table  by  multiplying  its
size  by  2/3  when  its  load  factor  drops  below  1/3.  Using  the  potential
function

Φ(T) = |2(T.num − T.size/2)|,

show  that  the  amortized  cost  of  a  TABLE-DELETE  that  uses  this
strategy is bounded above by a constant.

Problems

16-1     Binary reﬂected Gray code
A  binary  Gray  code  represents  a  sequence  of  nonnegative  integers  in
binary such that to go from one integer to the next, exactly one bit ﬂips
every time. The binary reﬂected Gray code represents a sequence of the
integers  0  to  2k  −  1  for  some  positive  integer  k  according  to  the
following recursive method:

For k = 1, the binary reﬂected Gray code is 〈0, 1〉.

For  k  ≥  2,  ﬁrst  form  the  binary  reﬂected  Gray  code  for  k  −  1,
giving the 2k−1 integers 0 to 2k−1 − 1. Then form the reﬂection
of this sequence, which is just the sequence in reverse. (That is, the
j th integer in the sequence becomes the (2k−1 − j − 1)st integer in
the reﬂection). Next, add 2k−1 to each of the 2k−1 integers in the
reﬂected sequence. Finally, concatenate the two sequences.

For example, for k = 2, ﬁrst form the binary reﬂected Gray code 〈0,
1〉  for  k  =  1.  Its  reﬂection  is  the  sequence  〈1,  0〉.  Adding  2k−1  =  2  to
each  integer  in  the  reﬂection  gives  the  sequence  〈3,  2〉.  Concatenating
the two sequences gives 〈0, 1, 3, 2〉 or, in binary, 〈00, 01, 11, 10〉, so that
each  integer  differs  from  its  predecessor  by  exactly  one  bit.  For  k  =  3,
the reﬂection of the binary reﬂected Gray code for k = 2 is 〈2, 3, 1, 0〉
and  adding  2k−1  =  4  gives  〈6,  7,  5,  4〉.  Concatenating  produces  the
sequence  〈0,  1,  3,  2,  6,  7,  5,  4〉,  which  in  binary  is  〈000,  001,  011,  010,
110, 111, 101,100〉. In the binary reﬂected Gray code, only one bit ﬂips
even when wrapping around from the last integer to the ﬁrst.

a. Index the integers in a binary reﬂected Gray code from 0 to 2k − 1,
and consider the ith integer in the binary reﬂected Gray code. To go

from the (i −1)st integer to the ith integer in the binary reﬂected Gray
code, exactly one bit ﬂips. Show how to determine which bit ﬂips,
given the index i.

b. Assuming that given a bit number j, you can ﬂip bit j of an integer in
constant time, show how to compute the entire binary reﬂected Gray
code sequence of 2k numbers in Θ(2k) time.

16-2     Making binary search dynamic
Binary  search  of  a  sorted  array  takes  logarithmic  search  time,  but  the
time  to  insert  a  new  element  is  linear  in  the  size  of  the  array.  You  can
improve the time for insertion by keeping several sorted arrays.

Speciﬁcally,  suppose  that  you  wish  to  support  SEARCH  and
INSERT on a set of n elements. Let k = ⌈lg(n + 1)⌉, and let the binary
representation of n be 〈nk−1, nk−2, … , n0〉. Maintain k sorted arrays
A0, A1, … , Ak−1, where for i = 0, 1, … , k − 1, the length of array Ai is
2i. Each array is either full or empty, depending on whether ni = 1 or ni
=  0,  respectively.  The  total  number  of  elements  held  in  all  k  arrays  is

.  Although  each  individual  array  is  sorted,
therefore
elements  in  different  arrays  bear  no  particular  relationship  to  each
other.

a. Describe how to perform the SEARCH operation for this data

structure. Analyze its worst-case running time.

b. Describe how to perform the INSERT operation. Analyze its worst-
case and amortized running times, assuming that the only operations
are INSERT and SEARCH.

c. Describe how to implement DELETE. Analyze its worst-case and
amortized running times, assuming that there can be DELETE,
INSERT, and SEARCH operations.

16-3     Amortized weight-balanced trees
Consider an ordinary binary search tree augmented by adding to each
node x the attribute x.size, which gives the number of keys stored in the

subtree rooted at x. Let α be a constant in the range 1/2 ≤ α < 1. We say
that a given node x is α-balanced if x.left.size ≤ α · x.size and x.right.size
≤ α · x.size. The tree as a whole is α-balanced if every node in the tree is
α-balanced.  The  following  amortized  approach  to  maintaining  weight-
balanced trees was suggested by G. Varghese.

a. A 1/2-balanced tree is, in a sense, as balanced as it can be. Given a
node x in an arbitrary binary search tree, show how to rebuild the
subtree rooted at x so that it becomes 1/2-balanced. Your algorithm
should run in Θ(x.size) time, and it can use O(x.size) auxiliary storage.
b. Show that performing a search in an n-node α-balanced binary search

tree takes O(lg n) worst-case time.

For the remainder of this problem, assume that the constant α is strictly
greater  than  1/2.  Suppose  that  you  implement  INSERT  and  DELETE
as  usual  for  an  n-node  binary  search  tree,  except  that  after  every  such
operation,  if  any  node  in  the  tree  is  no  longer  α-balanced,  then  you
“rebuild” the subtree rooted at the highest such node in the tree so that
it becomes 1/2-balanced.

We’ll analyze this rebuilding scheme using the potential method. For

a node x in a binary search tree T, deﬁne

Δ(x) = |x.left.size − x.right.size|.
Deﬁne the potential of T as

where c is a sufﬁciently large constant that depends on α.
c. Argue that any binary search tree has nonnegative potential and also

that a 1/2-balanced tree has potential 0.

d. Suppose that m units of potential can pay for rebuilding an m-node
subtree. How large must c be in terms of α in order for it to take O(1)
amortized time to rebuild a subtree that is not α-balanced?

e. Show that inserting a node into or deleting a node from an n-node α-

balanced tree costs O(lg n) amortized time.

16-4     The cost of restructuring red-black trees
There  are  four  basic  operations  on  red-black  trees  that  perform
structural  modiﬁcations:  node  insertions,  node  deletions,  rotations,  and
color  changes.  We  have  seen  that  RB-INSERT  and  RB-DELETE  use
only O(1) rotations, node insertions, and node deletions to maintain the
red-black properties, but they may make many more color changes.

a. Describe a legal red-black tree with n nodes such that calling RB-

INSERT to add the (n + 1)st node causes Ω(lg n) color changes. Then
describe a legal red-black tree with n nodes for which calling RB-
DELETE on a particular node causes Ω(lg n) color changes.

Although the worst-case number of color changes per operation can be
logarithmic,  you  will  prove  that  any  sequence  of  m  RB-INSERT  and
RB-DELETE  operations  on  an  initially  empty  red-black  tree  causes
O(m) structural modiﬁcations in the worst case.

b. Some of the cases handled by the main loop of the code of both RB-
INSERT-FIXUP and RB-DELETE-FIXUP are terminating: once
encountered, they cause the loop to terminate after a constant number
of additional operations. For each of the cases of RB-INSERT-
FIXUP and RB-DELETE-FIXUP, specify which are terminating and
which are not. (Hint: Look at Figures 13.5, 13.6, and 13.7 in Sections
13.3 and 13.4.)

You will ﬁrst analyze the structural modiﬁcations when only insertions
are  performed.  Let  T  be  a  red-black  tree,  and  deﬁne  Φ(T)  to  be  the
number  of  red  nodes  in  T.  Assume  that  one  unit  of  potential  can  pay
for the structural modiﬁcations performed by any of the three cases of
RB-INSERT-FIXUP.

c. Let T′ be the result of applying Case 1 of RB-INSERT-FIXUP to T.

Argue that Φ(T′) = Φ(T) − 1.

d. We can break the operation of the RB-INSERT procedure into three
parts. List the structural modiﬁcations and potential changes resulting
from lines 1–16 of RB-INSERT, from nonterminating cases of RB-

INSERT-FIXUP, and from terminating cases of RB-INSERT-
FIXUP.

e. Using part (d), argue that the amortized number of structural
modiﬁcations performed by any call of RB-INSERT is O(1).

Next  you  will  prove  that  there  are  O(m)  structural  modiﬁcations  when
both insertions and deletions occur. Deﬁne, for each node x,

Now redeﬁne the potential of a red-black tree T as

and let T′ be the tree that results from applying any nonterminating case
of RB-INSERT-FIXUP or RB-DELETE-FIXUP to T.

f. Show that Φ(T′) ≤ Φ(T) − 1 for all nonterminating cases of RB-

INSERT-FIXUP. Argue that the amortized number of structural
modiﬁcations performed by any call of RB-INSERT-FIXUP is O(1).

g. Show that Φ(T′) ≤ Φ(T) − 1 for all nonterminating cases of RB-

DELETE-FIXUP. Argue that the amortized number of structural
modiﬁcations performed by any call of RB-DELETE-FIXUP is O(1).

h. Complete the proof that in the worst case, any sequence of m RB-
INSERT and RB-DELETE operations performs O(m) structural
modiﬁcations.

Chapter notes

Aho, Hopcroft, and Ullman [5] used aggregate analysis to determine the
running  time  of  operations  on  a  disjoint-set  forest.  We’ll  analyze  this
data  structure  using  the  potential  method  in  Chapter  19.  Tarjan  [430]
surveys  the  accounting  and  potential  methods  of  amortized  analysis

and presents several applications. He attributes the accounting method
to several authors, including M. R. Brown, R. E. Tarjan, S. Huddleston,
and K. Mehlhorn. He attributes the potential method to D. D. Sleator.
The term “amortized” is due to D. D. Sleator and R. E. Tarjan.

Potential  functions  are  also  useful  for  proving  lower  bounds  for
certain types of problems. For each conﬁguration of the problem, deﬁne
a potential function that maps the conﬁguration to a real number. Then
determine the potential Φinit of the initial conﬁguration, the potential
Φﬁnal of the ﬁnal conﬁguration, and the maximum change in potential
ΔΦmax due to any step. The number of steps must therefore be at least |
Φﬁnal  −  Φinit|  /  |  ΔΦmax|.  Examples  of  potential  functions  to  prove
lower bounds in I/O complexity appear in works by Cormen, Sundquist,
and  Wisniewski  [105],  Floyd  [146],  and  Aggarwal  and  Vitter  [3].
[271]  applied  potential
Krumme,  Cybenko,  and  Venkataraman
functions to prove lower bounds on gossiping: communicating a unique
item from each vertex in a graph to every other vertex.

1 In some situations, such as an open-address hash table, it’s better to consider a table to be full
if its load factor equals some constant strictly less than 1. (See Exercise 16.4-2.)

Part V    Advanced Data Structures

