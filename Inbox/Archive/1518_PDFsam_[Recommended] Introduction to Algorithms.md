Prove that Var[aX] = a2Var[X] from the deﬁnition (C.31) of variance.

C.4 The geometric and binomial distributions

A  Bernoulli  trial  is  an  experiment  with  only  two  possible  outcomes:
success, which occurs with probability p, and failure, which occurs with
probability q = 1 − p. A coin ﬂip serves as an example where, depending
on  your  point  of  view,  heads  equates  to  success  and  tails  to  failure.
When  we  speak  of  Bernoulli  trials  collectively,  we  mean  that  the  trials
are mutually independent and, unless we speciﬁcally say otherwise, that
each has the same probability p for success. Two important distributions
arise from Bernoulli trials: the geometric distribution and the binomial
distribution.

The geometric distribution

Consider  a  sequence  of  Bernoulli  trials,  each  with  a  probability  p  of
success  and  a  probability  q  =  1  −  p  of  failure.  How  many  trials  occur
before  a  success?  Deﬁne  the  random  variable  X  to  be  the  number  of
trials needed to obtain a success. Then X has values in the range {1, 2,
…}, and for k ≥ 1,

Figure C.1 A geometric distribution with probability p = 1/3 of success and a probability q = 1 −
p of failure. The expectation of the distribution is 1/p = 3.

since  k  −  1  failures  occur  before  the  ﬁrst  success.  A  probability
distribution  satisfying  equation  (C.35)  is  said  to  be  a  geometric
distribution. Figure C.1 illustrates such a distribution.

Assuming that q < 1, we can calculate the expectation of a geometric

distribution:

Thus, on average, it takes 1/p trials before a success occurs, an intuitive
result. As Exercise C.4-3 asks you to show, the variance is

As  an  example,  suppose  that  you  repeatedly  roll  two  dice  until  you
obtain either a seven or an eleven. Of the 36 possible outcomes, 6 yield
a  seven  and  2  yield  an  eleven.  Thus,  the  probability  of  success  is  p  =
8/36  =  2/9,  and  you’d  have  to  roll  1/p  =  9/2  =  4.5  times  on  average  to
obtain a seven or eleven.

The binomial distribution

How  many  successes  occur  during  n  Bernoulli  trials,  where  a  success
occurs  with  probability  p  and  a  failure  with  probability  q  =  1  −  p?
Deﬁne the random variable X to be the number of successes in n trials.
Then X has values in the range {0, 1, … , n}, and for k = 0, 1, … , n,

since there are
 ways to pick which k of the n trials are successes, and
the  probability  that  each  occurs  is  pkqn−k.  A  probability  distribution
satisfying  equation  (C.38)  is  said  to  be  a  binomial  distribution.  For
convenience,  we  deﬁne  the  family  of  binomial  distributions  using  the
notation

Figure  C.2  illustrates  a  binomial  distribution.  The  name  “binomial”
comes  from  the  right-hand  side  of  equation  (C.38)  being  the  kth  term
of  the  expansion  of  (p  +q)n.  Consequently,  since  p  +  q  =  1,  equation
(C.4) on page 1181 gives

as axiom 2 of the probability axioms requires.

We  can  compute  the  expectation  of  a  random  variable  having  a
binomial  distribution  from  equations  (C.9)  and  (C.40).  Let  X  be  a

random variable that follows the binomial distribution b(k; n, p), and let
q = 1 − p. The deﬁnition of expectation gives

Figure  C.2  The  binomial  distribution  b(k;  15,  1/3)  resulting  from  n  =  15  Bernoulli  trials,  each
with probability p = 1/3 of success. The expectation of the distribution is np = 5.

Linearity of expectation produces the same result with substantially
less  algebra.  Let  Xi  be  the  random  variable  describing  the  number  of
successes in the ith trial. Then E[Xi] = p · 1 + q · 0 = p, and the expected
number of successes for n trials is

We  can  use  the  same  approach  to  calculate  the  variance  of  the
.  Since  Xi  takes  on
.

distribution.  By  equation  (C.31),
only  the  values  0  and  1,  we  have
Hence,

,  which  implies

To compute the variance of X, we take advantage of the independence
of the n trials. By equation (C.33), we have

As  Figure  C.2  shows,  the  binomial  distribution  b(k;  n,  p)  increases
with k until it reaches the mean np, and then it decreases. To prove that
the  distribution  always  behaves  in  this  manner,  examine  the  ratio  of
successive terms:

This  ratio  is  greater  than  1  precisely  when  (n  +  1)p  −  k  is  positive.
Consequently, b(k; n, p) > b(k − 1; n, p) for k < (n + 1)p (the distribution
increases),  and  b(k;  n,  p)  <  b(k  −  1;  n,  p)  for  k  >  (n  +  1)p  (the
distribution decreases). If (n + 1)p is an integer, then for k = (n + 1)p,
the ratio b(k; n, p)/b(k − 1; n, p) equals 1, so that b(k; n, p) = b(k − 1; n,
p). In this case, the distribution has two maxima: at k = (n+1)p and at
k−1 = (n+1)p−1 = np−q. Otherwise, it attains a maximum at the unique
integer k that lies in the range np − q < k < (n + 1)p.

The  following  lemma  provides  an  upper  bound  on  the  binomial

distribution.

Lemma C.1
Let n ≥ 0, let 0 < p < 1, let q = 1 − p, and let 0 ≤ k ≤ n. Then

Proof   We have

Exercises

▪

C.4-1
Verify axiom 2 of the probability axioms for the geometric distribution.

C.4-2
How  many  times  on  average  do  you  need  to  ﬂip  six  fair  coins  before
obtaining three heads and three tails?

C.4-3
Show that the variance of the geometric distribution is q/p2. (Hint: Use
Exercise A.1-6 on page 1144.)

C.4-4
Show that b(k; n, p) = b(n − k; n, q), where q = 1 − p.

C.4-5

Show that the value of the maximum of the binomial distribution b(k;
n, p) is approximately

, where q = 1 − p.

★ C.4-6
Show that the probability of no successes in n Bernoulli trials, each with
probability  p  =  1/n  of  success,  is  approximately  1/e.  Show  that  the
probability of exactly one success is also approximately 1/e.

★ C.4-7
Professor  Rosencrantz  ﬂips  a  fair  coin  n  times,  and  so  does  Professor
Guildenstern. Show that the probability that they get the same number
.  (Hint:  For  Professor  Rosencrantz,  call  a  head  a
of  heads  is
success, and for Professor Guildenstern, call a tail a success.) Use your
argument to verify the identity

★ C.4-8

