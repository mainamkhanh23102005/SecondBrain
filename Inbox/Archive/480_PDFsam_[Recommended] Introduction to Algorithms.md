Introduction

This  part  covers  three  important  techniques  used  in  designing  and
analyzing  efﬁcient  algorithms:  dynamic  programming  (Chapter  14),
greedy  algorithms  (Chapter  15),  and  amortized  analysis  (Chapter  16).
Earlier parts have presented other widely applicable techniques, such as
divide-and-conquer, randomization, and how to solve recurrences. The
techniques in this part are somewhat more sophisticated, but you will be
able  to  use  them  solve  many  computational  problems.  The  themes
introduced in this part will recur later in this book.

Dynamic programming typically applies to optimization problems in
which  you  make  a  set  of  choices  in  order  to  arrive  at  an  optimal
solution,  each  choice  generates  subproblems  of  the  same  form  as  the
original  problem,  and  the  same  subproblems  arise  repeatedly.  The  key
strategy  is  to  store  the  solution  to  each  such  subproblem  rather  than
recompute  it.  Chapter  14  shows  how  this  simple  idea  can  sometimes
polynomial-time
transform
algorithms.

exponential-time

algorithms

into

Like  dynamic-programming  algorithms,  greedy  algorithms  typically
apply  to  optimization  problems  in  which  you  make  a  set  of  choices  in
order to arrive at an optimal solution. The idea of a greedy algorithm is
to  make  each  choice  in  a  locally  optimal  manner,  resulting  in  a  faster
algorithm  than  you  get  with  dynamic  programming.  Chapter  15  will
help you determine when the greedy approach works.

The  technique  of  amortized  analysis  applies  to  certain  algorithms
that perform a sequence of similar operations. Instead of bounding the
cost of the sequence of operations by bounding the actual cost of each
operation separately, an amortized analysis provides a worst-case bound
on  the  actual  cost  of  the  entire  sequence.  One  advantage  of  this
approach  is  that  although  some  operations  might  be  expensive,  many
others might be cheap. You can use amortized analysis when designing
algorithms,  since  the  design  of  an  algorithm  and  the  analysis  of  its
running time are often closely intertwined. Chapter 16 introduces three
ways to perform an amortized analysis of an algorithm.

