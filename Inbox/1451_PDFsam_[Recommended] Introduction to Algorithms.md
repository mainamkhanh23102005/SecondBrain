A Summations

When  an  algorithm  contains  an  iterative  control  construct  such  as  a
while  or  for  loop,  you  can  express  its  running  time  as  the  sum  of  the
times  spent  on  each  execution  of  the  body  of  the  loop.  For  example,
Section  2.2  argued  that  the  i  th  iteration  of  insertion  sort  took  time
proportional  to  i  in  the  worst  case.  Adding  up  the  time  spent  on  each
iteration  produced  the  summation  (or  series)
.  Evaluating  this
summation resulted in a bound of Θ(n2) on the worst-case running time
of the algorithm. This example illustrates why you should know how to
manipulate and bound summations.

Section  A.1  lists  several  basic  formulas  involving  summations.
Section  A.2  offers  useful  techniques  for  bounding  summations.  The
formulas in Section A.1 appear without proof, though proofs for some
of them appear in Section A.2 to illustrate the methods of that section.
You can ﬁnd most of the other proofs in any calculus text.

A.1 Summation formulas and properties

Given a sequence a1, a2, … , an of numbers, where n is a nonnegative
. If n
integer, the ﬁnite sum a1 + a2 + … + an can be expressed as
= 0, the value of the summation is deﬁned to be 0. The value of a ﬁnite
series is always well deﬁned, and the order in which its terms are added
does not matter.

Given an inﬁnite sequence a1, a2, … of numbers, we can write their
inﬁnite  sum  a1  +  a2  +  …  as
.  If  the
limit does not exist, the series diverges, and otherwise, it converges. The
terms of a convergent series cannot always be added in any order. You
can,  however,  rearrange  the  terms  of  an  absolutely  convergent  series,
that is, a series

 for which the series

,  which  means

 also converges.

Linearity

For any real number c and any ﬁnite sequences a1, a2, … , an and b1,
b2, … , bn,

The linearity property also applies to inﬁnite convergent series.

The

linearity  property  applies

to  summations

incorporating

asymptotic notation. For example,

In  this  equation,  the  Θ-notation  on  the  left-hand  side  applies  to  the
variable  k,  but  on  the  right-hand  side,
it  applies  to  n.  Such
manipulations also apply to inﬁnite convergent series.

Arithmetic series

The summation

is an arithmetic series and has the value

A  general  arithmetic  series  includes  an  additive  constant  a  ≥  0  and  a
constant  coefﬁcient  b  >  0  in  each  term,  but  has  the  same  total
asymptotically:

Sums of squares and cubes

The following formulas apply to summations of squares and cubes:

Geometric series

For real x ≠ 1, the summation

is a geometric series and has the value

The  inﬁnite  decreasing  geometric  series  occurs  when  the  summation  is
inﬁnite and |x| < 1:

If we assume that 00 = 1, these formulas apply even when x = 0.

Harmonic series

For positive integers n, the nth harmonic number is

Inequalities  (A.20)  and  (A.21)  on  page  1150  provide  the  stronger
bounds

Integrating and differentiating series

Integrating  or  differentiating  the  formulas  above  yields  additional
formulas.  For  example,  differentiating  both  sides  of  the  inﬁnite
geometric series (A.7) and multiplying by x gives

Telescoping series

For any sequence a0, a1, … , an,

since  each  of  the  terms  a1,  a2,  …  ,  an−1  is  added  in  exactly  once  and
subtracted out exactly once. We say that the sum telescopes. Similarly,

As an example of a telescoping sum, consider the series

Rewriting each term as

gives

Reindexing summations

A  series  can  sometimes  be  simpliﬁed  by  changing  its  index,  often
. Because
reversing the order of summation. Consider the series
the  terms  in  this  summation  are  an,  an−1,  …  ,  a0,  we  can  reverse  the
order of indices by letting j = n − k and rewrite this summation as

Generally, if the summation index appears in the body of the sum with
a minus sign, it’s worth thinking about reindexing.

As an example, consider the summation

The index k appears with a negative sign in 1/(n − k + 1). And indeed,
we can simplify this summation, this time setting j = n − k + 1, yielding

which is just the harmonic series (A.8).

Products

The ﬁnite product a1a2 … an can be expressed as

If n = 0, the value of the product is deﬁned to be 1. You can convert a
formula  with  a  product  to  a  formula  with  a  summation  by  using  the
identity

Exercises

A.1-1
Prove  that
summations.

  by  using  the  linearity  property  of

A.1-2
Find a simple formula for

.

A.1-3
Interpret the decimal number 111,111,111 in light of equation (A.6).

A.1-4
Evaluate the inﬁnite series

A.1-5
Let c ≥ 0 be a constant. Show that

.

.

A.1-6
Show that

 for |x| < 1.

A.1-7
Prove  that
and lower bounds separately.)

★ A.1-8
Show  that
series.

★ A.1-9
Show that

.

.  (Hint:  Show  the  asymptotic  upper

  by  manipulating  the  harmonic

★ A.1-10
Evaluate the sum

.

