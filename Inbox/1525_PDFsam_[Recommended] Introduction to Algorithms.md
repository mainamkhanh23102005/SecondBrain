Show that for 0 ≤ k ≤ n,

b(k; n, 1/2) ≤ 2n H(k/n)−n,

where H(x) is the entropy function (C.8) on page 1182.

★ C.4-9
Consider  n  Bernoulli  trials,  where  for  i  =  1,  2,  …  ,  n,  the  ith  trial  has
probability pi of success, and let X be the random variable denoting the
total number of successes. Let p ≥ pi for all i = 1, 2, … , n. Prove that for
1 ≤ k ≤ n,

★ C.4-10
Let X be the random variable for the total number of successes in a set
A of n Bernoulli trials, where the ith trial has a probability pi of success,
and let X′ be the random variable for the total number of successes in a
second set A′ of n Bernoulli trials, where the ith trial has a probability

 of success. Prove that for 0 ≤ k ≤ n,

Pr {X′ ≥ k} ≥ Pr {X ≥ k}.
(Hint: Show how to obtain the Bernoulli trials in A′ by an experiment
involving the trials of A, and use the result of Exercise C.3-7.)

★ C.5 The tails of the binomial distribution

The probability of having at least, or at most, k successes in n Bernoulli
trials, each with probability p of success, is often of more interest than
the  probability  of  having  exactly  k  successes.  In  this  section,  we
investigate the tails of the binomial distribution: the two regions of the
distribution b(k; n, p) that are far from the mean np. We’ll prove several
important bounds on (the sum of all terms in) a tail.

We ﬁrst provide a bound on the right tail of the distribution b(k; n,
p).  To  determine  bounds  on  the  left  tail,  simply  invert  the  roles  of
successes and failures.

Theorem C.2
Consider  a  sequence  of  n  Bernoulli  trials,  where  success  occurs  with
probability p. Let X be the random variable denoting the total number
of successes. Then for 0 ≤ k ≤ n, the probability of at least k successes is

Proof   For S ⊆ {1, 2, … , n}, let AS denote the event that the ith trial is
a success for every i ∈ S. Since Pr {AS} = pk, where |S| = k, we have

▪

The  following  corollary  restates  the  theorem  for  the  left  tail  of  the
binomial  distribution.  In  general,  we’ll  leave  it  to  you  to  adapt  the
proofs from one tail to the other.

Corollary C.3
Consider  a  sequence  of  n  Bernoulli  trials,  where  success  occurs  with
probability p. If X is the random variable denoting the total number of
successes, then for 0 ≤ k ≤ n, the probability of at most k successes is

▪

Our  next  bound  concerns  the  left  tail  of  the  binomial  distribution.
Its  corollary  shows  that,  far  from  the  mean,  the  left  tail  diminishes
exponentially.

Theorem C.4
Consider  a  sequence  of  n  Bernoulli  trials,  where  success  occurs  with
probability  p  and  failure  with  probability  q  =  1  −  p.  Let  X  be  the
random variable denoting the total number of successes. Then for 0 < k
< np, the probability of fewer than k successes is

Proof   We bound the series
 by a geometric series using the
technique  from  Section  A.2,  page  1147.  For  i  =  1,  2,  …  ,  k,  equation
(C.45) gives

If we let

it follows that

b(i − 1; n, p) < xb(i; n, p)

for 0 < i ≤ k. Iteratively applying this inequality k − i times gives

b(i; n, p) < xk−i b(k; n, p)

for 0 ≤ i < k, and hence

▪

Corollary C.5
Consider  a  sequence  of  n  Bernoulli  trials,  where  success  occurs  with
probability  p  and  failure  with  probability  q  =  1  −  p.  Then  for  0  <  k  ≤
np/2,  the  probability  of  fewer  than  k  successes  is  less  than  half  the
probability of fewer than k + 1 successes.

Proof   Because k ≤ np/2, we have

since  q  ≤  1.  Letting  X  be  the  random  variable  denoting  the  number  of
successes, Theorem C.4 and inequality (C.46) imply that the probability
of fewer than k successes is

Thus we have

since

.

▪

Bounds on the right tail follow similarly. Exercise C.5-2 asks you to

prove them.

Corollary C.6
Consider  a  sequence  of  n  Bernoulli  trials,  where  success  occurs  with
probability p. Let X be the random variable denoting the total number
of  successes.  Then  for  np  <  k  <  n,  the  probability  of  more  than  k
successes is

Corollary C.7

▪

Consider  a  sequence  of  n  Bernoulli  trials,  where  success  occurs  with
probability p and failure with probability q = 1 − p. Then for (np + n)/2
<  k  <  n,  the  probability  of  more  than  k  successes  is  less  than  half  the
probability of more than k − 1 successes.

▪

The  next  theorem  considers  n  Bernoulli  trials,  each  with  a
probability pi of success, for i = 1, 2, … , n. As the subsequent corollary
shows, we can use the theorem to provide a bound on the right tail of
the binomial distribution by setting pi = p for each trial.

Theorem C.8
Consider a sequence of n Bernoulli trials, where in the ith trial, for i = 1,
2,  …  ,  n,  success  occurs  with  probability  pi  and  failure  occurs  with
probability  qi  =  1  −  pi.  Let  X  be  the  random  variable  describing  the
total number of successes, and let μ = E[X]. Then for r > μ,

Proof   Since for any α > 0, the function eαx strictly increases in x,

where  we  will  determine  α  later.  Using  Markov’s  inequality  (C.34),  we
obtain

The  bulk  of  the  proof  consists  of  bounding  E[eα(X−μ)]  and
substituting a suitable value for α in inequality (C.48). First, we evaluate
E[eα(X−μ)].  Using  the  technique  of  indicator  random  variables  (see
Section 5.2), let Xi = I {the ith Bernoulli trial is a success} for i = 1, 2,
…  ,  n.  That  is,  Xi  is  the  random  variable  that  is  1  if  the  ith  Bernoulli
trial is a success and 0 if it is a failure. Thus, we have

and by linearity of expectation,

which implies

To evaluate E[eα(X−μ)], we substitute for X − μ, obtaining

which  follows  from  equation  (C.27),  since  the  mutual  independence  of
the  random  variables  Xi  implies  the  mutual  independence  of  the
random  variables
  (see  Exercise  C.3-5).  By  the  deﬁnition  of
expectation,

where exp(x) denotes the exponential function: exp(x) = ex. (Inequality
.
(C.49)  follows  from  the  inequalities  α  >  0,  qi  ≤  1,
The last line follows from inequality (3.14) on page 66.) Consequently,

,  and

since
and (C.50), it follows that

. Therefore, from equation (C.47) and inequalities (C.48)

Choosing α = ln(r/μ) (see Exercise C.5-7), we obtain

▪

When  applied  to  Bernoulli  trials  in  which  each  trial  has  the  same
probability  of  success,  Theorem  C.8  yields  the  following  corollary
bounding the right tail of a binomial distribution.

Corollary C.9
Consider  a  sequence  of  n  Bernoulli  trials,  where  in  each  trial  success
occurs with probability p and failure occurs with probability q = 1 − p.
Then for r > np,

Proof   By equation (C.41), we have μ = E[X] = np.

▪

Exercises

★ C.5-1
Which is more likely: getting exactly n heads in 2n ﬂips of a fair coin, or
n heads in n ﬂips of a fair coin?

★ C.5-2
Prove Corollaries C.6 and C.7.

★ C.5-3
Show that

for all a > 0 and all k such that 0 < k < na/(a + 1).

★ C.5-4
Prove that if 0 < k < np, where 0 < p < 1 and q = 1 − p, then

★ C.5-5
Use Theorem C.8 to show that

for r > n − μ. Similarly, use Corollary C.9 to show that

for r > n − np.

★ C.5-6
Consider a sequence of n Bernoulli trials, where in the ith trial, for i = 1,
2,  …  ,  n,  success  occurs  with  probability  pi  and  failure  occurs  with
probability  qi  =  1  −  pi.  Let  X  be  the  random  variable  describing  the
total number of successes, and let μ = E[X]. Show that for r ≥ 0,

(Hint: Prove that
of Theorem C.8, using this inequality in place of inequality (C.49).)

. Then follow the outline of the proof

★ C.5-7

Show  that  choosing  α  =  ln(r/μ)  minimizes  the  right-hand  side  of
inequality (C.51).

Problems

C-1 The Monty Hall problem
Imagine that you are a contestant in the 1960s game show Let’s Make a
Deal,  hosted  by  emcee  Monty  Hall.  A  valuable  prize  is  hidden  behind
one of three doors and comparatively worthless prizes behind the other
two  doors.  You  will  win  the  valuable  prize,  typically  an  automobile  or
other expensive product, if you select the correct door. After you have
picked  one  door,  but  before  the  door  has  been  opened,  Monty,  who
knows  which  door  hides  the  automobile,  directs  his  assistant  Carol
Merrill to open one of the other doors, revealing a goat (not a valuable
prize). He asks whether you would like to stick with your current choice
or to switch to the other closed door. What should you do to maximize
your chances of winning the automobile and not the other goat?

The  answer  to  this  question—stick  or  switch?—has  been  heavily
debated, in part because the problem setup is ambiguous. We’ll explore
different subtle assumptions.

a. Suppose that your ﬁrst pick is random, with probability 1/3 of

choosing the right door. Moreover, you know that Monty always gives
every contestant (and will give you) the opportunity to switch. Prove
that it is better to switch than stick. What is your probability of
winning the automobile?

This  answer  is  the  one  typically  given,  even  though  the  original
statement  of  the  problem  rarely  mentions  the  assumption  that  Monty
always  offers  the  contestant  the  opportunity  to  switch.  But,  as  the
remainder  of  this  problem  will  elucidate,  your  best  strategy  may  be
different if this unstated assumption does not hold. In fact, in the real
game show, after a contestant picked a door, Monty sometimes simply
asked Carol to open the door that the contestant had chosen.

Let’s  model  the

interactions  between  you  and  Monty  as  a
probabilistic experiment, where you both employ randomized strategies.

Speciﬁcally, after you pick a door, Monty offers you the opportunity to
switch  with  probability  pright  if  you  picked  the  right  door  and  with
if  you  picked  the  wrong  door.  Given  the
probability  pwrong
opportunity to switch, you randomly choose to switch with probability
pswitch.  For  example,  if  Monty  always  offers  you  the  opportunity  to
switch, then his strategy is given by pright = pwrong = 1. If you always
switch, then your strategy is given by pswitch = 1.

The  game  can  now  be  viewed  as  an  experiment  consisting  of  ﬁve

steps:

1. You pick a door at random, choosing the automobile (right) with

probability 1/3 or a goat (wrong) with probability 2/3.

2. Carol opens one of the two closed doors, revealing a goat.

3. Monty offers you the opportunity to switch with probability pright if
your choice is right and with probability pwrong if your choice is
wrong.

4. If Monty makes you an offer in step 3, you switch with probability

pswitch.

5. Carol opens the door you’ve chosen, revealing either an automobile

(you win) or a goat (you lose).

Let’s  now  analyze  this  game  and  understand  how  the  choices  of

pright, pwrong, and pswitch inﬂuence the probability of winning.

b. What are the six outcomes in the sample space for this game? Which
outcomes correspond to you winning the automobile? What are the
probabilities in terms of pright, pwrong, and pswitch of each
outcome? Organize your answers into a table.

c. Use the results of your table (or other means) to prove that the

probability of winning the automobile is

Suppose that Monty knows the probability pswitch that you switch, and
his goal is to minimize your chance of winning.

d. If pswitch > 0 (you switch with a positive probability), what is

Monty’s best strategy, that is, his best choice for pright and pwrong?

e. If pswitch = 0 (you always stick), argue that all of Monty’s possible

strategies are optimal for him.

Suppose  that  now  Monty’s  strategy  is  ﬁxed,  with  particular  values  for
pright and pwrong.

f. If you know pright and pwrong, what is your best strategy for

choosing your probability pswitch of switching as a function of pright
and pwrong?

g. If you don’t know pright and pwrong, what choice of pswitch

maximizes the minimum probability of winning over all the choices of
pright and pwrong?

Let’s return to the original problem as stated, where Monty has given
you  the  option  of  switching,  but  you  have  no  knowledge  of  Monty’s
possible motivations or strategies.

h. Argue that the conditional probability of winning the automobile

given that Monty offers you the opportunity to switch is

Explain why pright + 2pwrong ≠ 0.

i. What is the value of expression (C.52) when pswitch = 1/2? Show that
choosing pswitch < 1/2 or pswitch > 1/2 allows Monty to select values
for pright and pwrong that yield a lower value for expression (C.52)
than choosing pswitch = 1/2.

j. Suppose that you don’t know Monty’s strategy. Explain why choosing

to switch with probability 1/2 is a good strategy for the original

problem as stated. Summarize what you have learned overall from this
problem.

C-2 Balls and bins

This  problem  investigates  the  effect  of  various  assumptions  on  the
number of ways of placing n balls into b distinct bins.

a. Suppose that the n balls are distinct and that their order within a bin

does not matter. Argue that the number of ways of placing the balls in
the bins is bn.

b. Suppose that the balls are distinct and that the balls in each bin are

ordered. Prove that there are exactly (b + n − 1)!/(b − 1)! ways to place
the balls in the bins. (Hint: Consider the number of ways of arranging
n distinct balls and b − 1 indistinguishable sticks in a row.)

c. Suppose that the balls are identical, and hence their order within a
bin does not matter. Show that the number of ways of placing the
balls in the bins is
many are repeated if the balls are made identical?)

. (Hint: Of the arrangements in part (b), how

d. Suppose that the balls are identical and that no bin may contain more
than one ball, so that n ≤ b. Show that the number of ways of placing
the balls is

.

e. Suppose that the balls are identical and that no bin may be left empty.
Assuming that n ≥ b, show that the number of ways of placing the
balls is

.

Appendix notes

The  ﬁrst  general  methods  for  solving  probability  problems  were
discussed  in  a  famous  correspondence  between  B.  Pascal  and  P.  de
Fermat,  which  began  in  1654,  and  in  a  book  by  C.  Huygens  in  1657.
Rigorous probability theory began with the work of J. Bernoulli in 1713
and  A.  De  Moivre  in  1730.  Further  developments  of  the  theory  were
provided by P.-S. Laplace, S.-D. Poisson, and C. F. Gauss.

Sums  of  random  variables  were  originally  studied  by  P.  L.
Chebyshev  and  A.  A.  Markov.  A.  N.  Kolmogorov  axiomatized
probability theory in 1933. Chernoff [91] and Hoeffding [222] provided
bounds  on  the  tails  of  distributions.  Seminal  work  in  random
combinatorial structures was done by P. Erdős.

Knuth  [259]  and  Liu  [302]  are  good  references  for  elementary
combinatorics  and  counting.  Standard  textbooks  such  as  Billingsley
[56],  Chung  [93],  Drake  [125],  Feller  [139],  and  Rozanov  [390]  offer
comprehensive introductions to probability.

1 For a general probability distribution, there may be some subsets of the sample space S that
are  not  considered  to  be  events.  This  situation  usually  arises  when  the  sample  space  is
uncountably inﬁnite. The main requirement for what subsets are events is that the set of events
of a sample space must be closed under the operations of taking the complement of an event,
forming  the  union  of  a  ﬁnite  or  countable  number  of  events,  and  taking  the  intersection  of  a
ﬁnite or countable number of events. Most of the probability distributions we see in this book
are  over  ﬁnite  or  countable  sample  spaces,  and  we  generally  consider  all  subsets  of  a  sample
space  to  be  events.  A  notable  exception  is  the  continuous  uniform  probability  distribution,
which we’ll see shortly.

