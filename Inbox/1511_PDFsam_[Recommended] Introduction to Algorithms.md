C.2-5
Prove that for any collection of events A1, A2, … , An,

★ C.2-6
Show how to construct a set of n events that are pairwise independent
but such that no subset of k > 2 of them is mutually independent.

★ C.2-7
Two events A and B are conditionally independent, given C, if

Pr {A ∩ B | C} = Pr {A | C} · Pr {B | C}.
Give  a  simple  but  nontrivial  example  of  two  events  that  are  not
independent but are conditionally independent given a third event.

★ C.2-8
Professor Gore teaches a music class on rhythm in which three students
—Jeff, Tim, and Carmine—are in danger of failing. Professor Gore tells
the  three  that  one  of  them  will  pass  the  course  and  the  other  two  will
fail. Carmine asks Professor Gore privately which of Jeff and Tim will
fail, arguing that since he already knows at least one of them will fail,
the  professor  won’t  be  revealing  any  information  about  Carmine’s
outcome. In a breach of privacy law, Professor Gore tells Carmine that
Jeff will fail. Carmine feels somewhat relieved now, ﬁguring that either
he  or  Tim  will  pass,  so  that  his  probability  of  passing  is  now  1/2.  Is
Carmine correct, or is his chance of passing still 1/3? Explain.

C.3 Discrete random variables

A (discrete) random variable X is a function from a ﬁnite or countably
inﬁnite sample space S to the real numbers. It associates a real number
with each possible outcome of an experiment, which allows us to work
with  the  probability  distribution  induced  on  the  resulting  set  of

numbers. Random variables can also be deﬁned for uncountably inﬁnite
sample  spaces,  but  they  raise  technical  issues  that  are  unnecessary  to
address for our purposes. Therefore we’ll assume that random variables
are discrete.

For a random variable X and a real number x, we deﬁne the event X

= x to be {s ∈ S : X(s) = x}, and thus

The function

f(x) = Pr {X = x}

is  the  probability  density  function  of  the  random  variable  X.  From  the
probability axioms, Pr {X = x} ≥ 0 and ∑x Pr {X = x} = 1.

As an example, consider the experiment of rolling a pair of ordinary,
6-sided  dice.  There  are  36  possible  outcomes  in  the  sample  space.
Assume  that  the  probability  distribution  is  uniform,  so  that  each
outcome  s  ∈  S  is  equally  likely:  Pr  {s}  =  1/36.  Deﬁne  the  random
variable  X  to  be  the  maximum  of  the  two  values  showing  on  the  dice.
We have Pr {X = 3} = 5/36, since X assigns a value of 3 to 5 of the 36
possible outcomes, namely, (1, 3), (2, 3), (3, 3), (3, 2), and (3, 1).

We can deﬁne several random variables on the same sample space. If

X and Y are random variables, the function

f(x, y) = Pr {X = x and Y = y}

is the joint probability density function of X and Y. For a ﬁxed value y,

and similarly, for a ﬁxed value x,

Using the deﬁnition (C.16) of conditional probability on page 1187, we
have

We deﬁne two random variables X and Y to be independent if for all x
and y, the events X = x and Y = y are independent or, equivalently, if
for all x and y, we have Pr {X = x and Y = y} = Pr {X = x} Pr {Y = y}.

Given a set of random variables deﬁned over the same sample space,
we  can  deﬁne  new  random  variables  as  sums,  products,  or  other
functions of the original variables.

Expected value of a random variable

The simplest, and often the most useful, summary of the distribution of
a  random  variable  is  the  “average”  of  the  values  it  takes  on.  The
expected  value  (or,  synonymously,  expectation  or  mean)  of  a  discrete
random variable X is

which  is  well  deﬁned  if  the  sum  is  ﬁnite  or  converges  absolutely.
Sometimes the expectation of X is denoted by μX or, when the random
variable is apparent from context, simply by μ.

Consider  a  game  in  which  you  ﬂip  two  fair  coins.  You  earn  $3  for
each head but lose $2 for each tail. The expected value of the random
variable X representing your earnings is

E[X] = 6 · Pr {2 H’s} + 1 · Pr {1 H, 1 T} − 4 · Pr {2 T’s}

= 6 · (1/4) + 1 · (1/2) − 4 · (1/4)
= 1.

Linearity of expectation says that the expectation of the sum of two

random variables is the sum of their expectations, that is,

whenever E[X] and E[Y] are deﬁned. Linearity of expectation applies to
a  broad  range  of  situations,  holding  even  when  X  and  Y  are  not
independent.  It  also  extends  to  ﬁnite  and  absolutely  convergent
summations  of  expectations.  Linearity  of  expectation  is  the  key
property  that  enables  us  to  perform  probabilistic  analyses  by  using
indicator random variables (see Section 5.2).

If X is any random variable, any function g(x) deﬁnes a new random

variable g(X). If the expectation of g(X) is deﬁned, then

Letting g(x) = ax, we have for any constant a,

Consequently,  expectations  are  linear:  for  any  two  random  variables  X
and Y and any constant a,

When two random variables X and Y are independent and each has

a deﬁned expectation,

In  general,  when  n  random  variables  X1,  X2,  …  ,  Xn  are  mutually
independent,

When  a  random  variable  X  takes  on  values  from  the  set  of  natural
numbers ℕ = {0, 1, 2, …}, we have a nice formula for its expectation:

since each term Pr {X ≥ i} is added in i times and subtracted out i − 1
times (except Pr {X ≥ 0}, which is added in 0 times and not subtracted

out at all).

A function f(x) is convex if

for all x and y and for all 0 ≤ λ ≤ 1. Jensen’s inequality says that when a
convex function f(x) is applied to a random variable X,

provided that the expectations exist and are ﬁnite.

Variance and standard deviation

The expected value of a random variable does not express how “spread
out” the variable’s values are. For example, consider random variables X
and Y for which Pr {X = 1/4} = Pr {X = 3/4} = 1/2 and Pr {Y = 0} = Pr
{Y = 1} = 1/2. Then both E[X] and E[Y] are 1/2, yet the actual values
taken on by Y are further from the mean than the actual values taken
on by X.

The  notion  of  variance  mathematically  expresses  how  far  from  the
mean  a  random  variable’s  values  are  likely  to  be.  The  variance  of  a
random variable X with mean E[X] is

To  justify  the  equation  E[E2[X]]  =  E2[X],  note  that  because  E[X]  is  a
real  number  and  not  a  random  variable,  so  is  E2[X].  The  equation
E[XE[X]]  =  E2[X]  follows  from  equation  (C.25),  with  a  =  E[X].
Rewriting  equation  (C.31)  yields  an  expression  for  the  expectation  of
the square of a random variable:

The  variance  of  a  random  variable  X  and  the  variance  of  aX  are

related (see Exercise C.3-10):

Var[aX] = a2Var[X].

When X and Y are independent random variables,

Var[X + Y] = Var[X] + Var[Y].

In  general,  if  n  random  variables  X1,  X2,  …  ,  Xn  are  pairwise
independent, then

The standard deviation of a random variable X is the nonnegative square
root of the variance of X. The standard deviation of a random variable
X is sometimes denoted σX or simply σ when the random variable X is
understood  from  context.  With  this  notation,  the  variance  of  X  is
denoted σ

2.

Exercises

C.3-1

You roll two ordinary, 6-sided dice. What is the expectation of the sum
of the two values showing? What is the expectation of the maximum of
the two values showing?

C.3-2
An  array  A[1  :  n]  contains  n  distinct  numbers  that  are  randomly
ordered,  with  each  permutation  of  the  n  numbers  being  equally  likely.
What  is  the  expectation  of  the  index  of  the  maximum  element  in  the
array? What is the expectation of the index of the minimum element in
the array?

C.3-3
A  carnival  game  consists  of  three  dice  in  a  cage.  A  player  can  bet  a
dollar on any of the numbers 1 through 6. The cage is shaken, and the
payoff is as follows. If the player’s number doesn’t appear on any of the
dice,  the  player  loses  the  dollar.  Otherwise,  if  the  player’s  number

appears on exactly k of the three dice, for k = 1, 2, 3, the player keeps
the  dollar  and  wins  k  more  dollars.  What  is  the  expected  gain  from
playing the carnival game once?

C.3-4

Argue that if X and Y are nonnegative random variables, then

E[max {X, Y}] ≤ E[X] + E[Y].

★ C.3-5
Let X and Y be independent random variables. Prove that f(X) and g(Y)
are independent for any choice of functions f and g.

★ C.3-6
Let X be a nonnegative random variable, and suppose that E[X] is well
deﬁned. Prove Markov’s inequality:

for all t > 0.

★ C.3-7
Let S be a sample space, and let X and X′ be random variables such that
X(s) ≥ X′(s) for all s ∈ S. Prove that for any real constant t,
Pr {X ≥ t} ≥ Pr {X′ ≥ t}.

C.3-8
Which is larger: the expectation of the square of a random variable, or
the square of its expectation?

C.3-9

Show  that  for  any  random  variable  X  that  takes  on  only  the  values  0
and 1, we have Var[X] = E[X] E [1 − X].

C.3-10

