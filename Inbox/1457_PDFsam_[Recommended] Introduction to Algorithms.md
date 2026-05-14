★ A.1-11
Evaluate the product

.

A.2 Bounding summations

You can choose from several techniques to bound the summations that
describe  the  running  times  of  algorithms.  Here  are  some  of  the  most
frequently used methods.

Mathematical induction

The  most  basic  way  to  evaluate  a  series  is  to  use  mathematical
induction.  As  an  example,  let’s  prove  that  the  arithmetic  series
evaluates to n(n + 1)/2. For n = 1, we have that n(n + 1)/2 = 1 · 2/2 = 1,
.  With  the  inductive  assumption  that  it  holds  for  n,
which  equals
we prove that it holds for n + 1. We have

You  don’t  always  need  to  guess  the  exact  value  of  a  summation  in
order to use mathematical induction. Instead, you can use induction to
prove  an  upper  or  lower  bound  on  a  summation.  As  an  example,  let’s
prove the asymptotic upper bound
. More speciﬁcally, we’ll
 for some constant c. For the initial condition n =
prove that
0, we have
 as long as c ≥ 1. Assuming that the bound holds
for n, we prove that it holds for n + 1. We have

as long as (1/3 + 1/c) ≤ 1 or, equivalently, c ≥ 3/2. Thus,
we wished to show.

, as

You  need  to  take  care  when  using  asymptotic  notation  to  prove
bounds  by  induction.  Consider  the  following  fallacious  proof  that
.  Assuming  that  the  bound  holds  for

.  Certainly,

n, we now prove it for n + 1:

The bug in the argument is that the “constant” hidden by the “big-oh”
grows with n and thus is not constant. We have not shown that the same
constant works for all n.

Bounding the terms

You can sometimes obtain a good upper bound on a series by bounding
each  term  of  the  series,  and  it  often  sufﬁces  to  use  the  largest  term  to
bound the others. For example, a quick upper bound on the arithmetic
series (A.1) is

In general, for a series

, if we let amax = max {ak : 1 ≤ k ≤ n}, then

The technique of bounding each term in a series by the largest term
is a weak method when the series can in fact be bounded by a geometric

,  suppose  that  ak+1/ak  ≤  r  for  all  k  ≥  0,
series.  Given  the  series
where  0  <  r  <  1  is  a  constant.  You  can  bound  the  sum  by  an  inﬁnite
decreasing geometric series, since ak ≤ a0rk, and thus

You  can  apply  this  method  to  bound  the  summation

order to start the summation at k = 0, rewrite it as
ﬁrst term (a0) is 1/3, and the ratio (r) of consecutive terms is

.  In
. The

for all k ≥ 0. Thus, we have

A common bug in applying this method is to show that the ratio of
consecutive terms is less than 1 and then to assume that the summation
is  bounded  by  a  geometric  series.  An  example  is  the  inﬁnite  harmonic
series, which diverges since

The ratio of the (k+1)st and kth terms in this series is k/(k+1) < 1, but
the series is not bounded by a decreasing geometric series. To bound a
series  by  a  geometric  series,  you  need  to  show  that  there  is  an  r  <  1,
which is a constant, such that the ratio of all pairs of consecutive terms

never  exceeds  r.  In  the  harmonic  series,  no  such  r  exists  because  the
ratio becomes arbitrarily close to 1.

Splitting summations

One  way  to  obtain  bounds  on  a  difﬁcult  summation  is  to  express  the
series as the sum of two or more series by partitioning the range of the
index and then to bound each of the resulting series. For example, let’s
ﬁnd a lower bound on the arithmetic series
, which we have already
seen has an upper bound of n2. You might attempt to bound each term
in  the  summation  by  the  smallest  term,  but  since  that  term  is  1,  you
would  get  a  lower  bound  of  n  for  the  summation—far  off  from  the
upper bound of n2.

You  can  obtain  a  better  lower  bound  by  ﬁrst  splitting  the

summation. Assume for convenience that n is even, so that

which is an asymptotically tight bound, since

.

For a summation arising from the analysis of an algorithm, you can
sometimes  split  the  summation  and  ignore  a  constant  number  of  the
initial  terms.  Generally,  this  technique  applies  when  each  term  ak  in  a
summation
  is  independent  of  n.  Then  for  any  constant  k0  >  0,
you can write

since the initial terms of the summation are all constant and there are a
constant  number  of  them.  You  can  then  use  other  methods  to  bound

.  This  technique  applies  to  inﬁnite  summations  as  well.  For
. The ratio of

example, let’s ﬁnd an asymptotic upper bound on
consecutive terms is

if k ≥ 3. Thus, you can split the summation into

The  technique  of  splitting  summations  can  help  determine
asymptotic bounds in much more difﬁcult situations. For example, here
is one way to obtain a bound of O(lg n) on the harmonic series (A.9):

The  idea  is  to  split  the  range  1  to  n  into  ⌊lg  n⌋  +  1  pieces  and  upper-
bound the contribution of each piece by 1. For i = 0, 1, … , ⌊lg n⌋, the
ith piece consists of the terms starting at 1/2i and going up to but not
including 1/2i+1. The last piece might contain terms not in the original
harmonic series, giving

Approximation by integrals

When  a  summation  has  the  form
is  a
monotonically increasing function, you can approximate it by integrals:

,  where  f  (k)

Figure  A.1  justiﬁes  this  approximation.  The  summation  is  represented
as  the  area  of  the  rectangles  in  the  ﬁgure,  and  the  integral  is  the  blue
region  under  the  curve.  When  f  (k)  is  a  monotonically  decreasing
function, you can use a similar method to provide the bounds

The  integral  approximation  (A.19)  can  be  used  to  prove  the  tight
bounds  in  inequality  (A.10)  for  the  nth  harmonic  number.  The  lower
bound is

For the upper bound, the integral approximation gives

Exercises

A.2-1
Show that

 is bounded above by a constant.

A.2-2
Find an asymptotic upper bound on the summation

Figure A.1 Approximation of
 by integrals. The area of each rectangle is shown within
the rectangle, and the total rectangle area represents the value of the summation. The integral is
represented  by  the  blue  area  under  the  curve.  Comparing  areas  in  (a)  gives  the  lower  bound
.  Shifting  the  rectangles  one  unit  to  the  right  gives  the  upper  bound
 in (b).

A.2-3
Show  that  the  nth  harmonic  number  is  Ω(lg  n)  by  splitting  the
summation.

A.2-4

Approximate

 with an integral.

A.2-5
Why  can’t  you  use  the  integral  approximation  (A.19)  directly  on

 to obtain an upper bound on the nth harmonic number?

Problems

A-1 Bounding summations
Give asymptotically tight bounds on the following summations. Assume
that r ≥ 0 and s ≥ 0 are constants.

a.

b.

c.

Appendix notes

Knuth  [259]  provides  an  excellent  reference  for  the  material  presented
here. You can ﬁnd basic properties of series in any good calculus book,
such as Apostol [19] or Thomas et al. [433].

