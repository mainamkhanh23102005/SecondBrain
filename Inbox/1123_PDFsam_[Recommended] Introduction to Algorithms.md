30        Polynomials and the FFT

The  straightforward  method  of  adding  two  polynomials  of  degree  n  takes
Θ(n) time, but the straightforward method of multiplying them takes Θ(n2)
time.  This  chapter  will  show  how  the  fast  Fourier  transform,  or  FFT,  can
reduce the time to multiply polynomials to Θ(n lg n).

The most common use for Fourier transforms, and hence the FFT, is in
signal  processing.  A  signal  is  given  in  the  time  domain:  as  a  function
mapping  time  to  amplitude.  Fourier  analysis  expresses  the  signal  as  a
weighted  sum  of  phase-shifted  sinusoids  of  varying  frequencies.  The
weights  and  phases  associated  with  the  frequencies  characterize  the  signal
in the frequency domain. Among the many everyday applications of FFT’s
are  compression  techniques  used  to  encode  digital  video  and  audio
information, including MP3 files. Many fine books delve into the rich area
of signal processing, and the chapter notes reference a few of them.

Polynomials

A  polynomial  in  the  variable  x  over  an  algebraic  field  F  represents  a
function A(x) as a formal sum:

The  values  a0,  a1,  …  ,  an−1  are  the  coefficients  of  the  polynomial.  The
coefficients and x are drawn from a field F, typically the set ℂ of complex
numbers. A polynomial A(x) has degree k if its highest nonzero coefficient
is ak, in which case we say that degree(A) = k. Any integer strictly greater

than  the  degree  of  a  polynomial  is  a  degree-bound  of  that  polynomial.
Therefore,  the  degree  of  a  polynomial  of  degree-bound  n  may  be  any
integer between 0 and n − 1, inclusive.

A variety of operations extend to polynomials. For polynomial addition,
if  A(x)  and  B(x)  are  polynomials  of  degree-bound  n,  their  sum  is  a
polynomial C(x), also of degree-bound n, such that C(x) = A(x)+B(x) for all
x in the underlying field. That is, if

then

where  cj  =  aj  +  bj  for  j  =  0,  1,  …  ,  n  −  1.  For  example,  given  the
polynomials  A(x)  =  6x3  +  7x2  −  10x  +  9  and  B(x)  =  −2x3  +  4x  −  5,  their
sum is C(x) = 4x3 + 7x2 − 6x + 4.

For  polynomial  multiplication,  if  A(x)  and  B(x)  are  polynomials  of
degree-bound n, their product C(x) is a polynomial of degree-bound 2n − 1
such  that  C(x)  =  A(x)B(x)  for  all  x  in  the  underlying  field.  You  probably
have  multiplied  polynomials  before,  by  multiplying  each  term  in  A(x)  by
each  term  in  B(x)  and  then  combining  terms  with  equal  powers.  For
example, you can multiply A(x) = 6x3 + 7x2 − 10x + 9 and B(x) = −2x3 + 4x
− 5 as follows:

Another way to express the product C(x) is

where

(By the definition of degree, ak = 0 for all k > degree(A) and bk = 0 for all k
> degree(B).) If A is a polynomial of degree-bound na and B is a polynomial
of degree-bound nb, then C must be a polynomial of degree-bound na + nb
−  1,  because  degree(C)  =  degree(A)  +  degree(B).  Since  a  polynomial  of
degree-bound  k  is  also  a  polynomial  of  degree-bound  k  +  1,  we  normally
make  the  somewhat  simpler  statement  that  the  product  polynomial  C  is  a
polynomial of degree-bound na + nb.

Chapter outline

Section  30.1  presents  two  ways  to  represent  polynomials:  the  coefficient
representation  and  the  point-value  representation.  The  straightforward
method  for  multiplying  polynomials  of  degree  n—equations  (30.1)  and
(30.2)—takes Θ(n2) time with polynomials represented in coefficient form,
but  only  Θ(n)  time  with  point-value  form.  Converting  between  the  two
representations,  however,  reduces  the  time  to  multiply  polynomials  to  just
Θ(n  lg  n).  To  see  why  this  approach  works,  you  must  first  understand
complex roots of unity, which Section 30.2 covers. Section 30.2 then uses
the FFT and its inverse to perform the conversions. Because the FFT is used
so  often  in  signal  processing,  it  is  often  implemented  as  a  circuit  in
hardware, and Section 30.3 illustrates the structure of such circuits.

This  chapter  relies  on  complex  numbers,  and  within  this  chapter  the

symbol i denotes

 exclusively.

30.1    Representing polynomials

The  coefficient  and  point-value  representations  of  polynomials  are  in  a
sense equivalent: a polynomial in point-value form has a unique counterpart
in  coefficient  form.  This  section  introduces  the  two  representations  and
shows  how  to  combine  them  in  order  to  multiply  two  degree-bound  n
polynomials in Θ(n lg n) time.

Coefficient representation

A  coefficient  representation  of  a  polynomial
  of  degree-
bound n is a vector of coefficients a = (a0, a1, … , an−1). Matrix equations
in this chapter generally treat vectors as column vectors.

The  coefficient  representation  is  convenient  for  certain  operations  on
polynomials. For example, the operation of evaluating the polynomial A(x)
at a given point x0 consists of computing the value of A(x0). To evaluate a
polynomial in Θ(n) time, use Horner’s rule:

Similarly, adding two polynomials represented by the coefficient vectors a
=  (a0,  a1,  …  ,  an−1)  and  b  =  (b0,  b1,  …  ,  bn−1)  takes  Θ(n)  time:  just
produce the coefficient vector c = (c0, c1, … , cn−1), where cj = aj + bj for
j = 0, 1, … , n− 1.

Now,  consider  multiplying  two  degree-bound  n  polynomials  A(x)  and
B(x)  represented  in  coefficient  form.  The  method  described  by  equations
(30.1) and (30.2) takes Θ(n2) time, since it multiplies each coefficient in the
vector  a  by  each  coefficient  in  the  vector  b. The  operation  of  multiplying
polynomials  in  coefficient  form  seems  to  be  considerably  more  difficult
than  that  of  evaluating  a  polynomial  or  adding  two  polynomials.  The
resulting  coefficient  vector  c,  given  by  equation  (30.2),  is  also  called  the
convolution  of  the  input  vectors  a  and  b,  denoted  c  =  a  ⊗  b.  Since
multiplying  polynomials  and  computing  convolutions  are  fundamental
computational  problems  of  considerable  practical  importance,  this  chapter
concentrates on efficient algorithms for them.

Point-value representation

A point-value representation of a polynomial A(x) of degree-bound n is a
set of n point-value pairs

{(x0, y0), (x1, y1), … , (xn−1, yn−1)}

such that all of the xk are distinct and

for  k  =  0,  1,  …  ,  n  −  1.  A  polynomial  has  many  different  point-value
representations, since any set of n distinct points x0, x1, … , xn−1 can serve
as a basis for the representation.

Computing  a  point-value  representation  for  a  polynomial  given  in
coefficient form is in principle straightforward, since all you have to do is
select n distinct points x0, x1, … , xn−1 and then evaluate A(xk) for k = 0, 1,
… , n − 1. With Horner’s method, evaluating a polynomial at n points takes
Θ(n2) time. We’ll see later that if you choose the points xk cleverly, you can
accelerate this computation to run in Θ(n lg n) time.

The  inverse  of  evaluation—determining  the  coefficient  form  of  a
polynomial  from  a  point-value  representation—is  interpolation.  The
following theorem shows that interpolation is well defined when the desired
interpolating  polynomial  must  have  a  degree-bound  equal  to  the  given
number of point-value pairs.

Theorem 30.1 (Uniqueness of an interpolating polynomial)
For  any  set  {(x0,  y0),  (x1,  y1),  …  ,  (xn−1,  yn−1)}  of  n  point-value  pairs
such that all the xk values are distinct, there is a unique polynomial A(x) of
degree-bound n such that yk = A(xk) for k = 0, 1, … , n − 1.

Proof   The proof relies on the existence of the inverse of a certain matrix.
Equation (30.3) is equivalent to the matrix equation

The matrix on the left is denoted V(x0, x1, … , xn−1) and is known as a
Vandermonde  matrix.  By  Problem  D-1  on  page  1223,  this  matrix  has
determinant

and  therefore,  by  Theorem  D.5  on  page  1221,  it  is  invertible  (that  is,
nonsingular) if the xk are distinct. To solve for the coefficients aj uniquely
given  the  point-value  representation,  use  the  inverse  of  the  Vandermonde
matrix:
a = V(x0, x1, … , xn−1)−1y.

▪

The  proof  of  Theorem  30.1  describes  an  algorithm  for  interpolation
based on solving the set (30.4) of linear equations. Section 28.1 shows how
to solve these equations in O(n3) time.

A  faster  algorithm  for  n-point  interpolation  is  based  on  Lagrange’s

formula:

You  might  want  to  verify  that  the  right-hand  side  of  equation  (30.5)  is  a
polynomial  of  degree-bound  n  that  satisfies  A(xk)  =  yk  for  all  k.  Exercise
30.1-5  asks  you  how  to  compute  the  coefficients  of  A  using  Lagrange’s
formula in Θ(n2) time.

Thus,  n-point  evaluation  and  interpolation  are  well-defined  inverse
operations  that  transform  between  the  coefficient  representation  of  a
polynomial  and  a  point-value  representation.1  The  algorithms  described
above for these problems take Θ(n2) time.

The  point-value  representation  is  quite  convenient  for  many  operations
on  polynomials.  For  addition,  if  C(x)  =  A(x)  +  B(x),  then  C(xk)  =  A(xk)  +
B(xk) for any point xk. More precisely, given point-value representations for
A,

{(x0, y0), (x1, y1), … , (xn−1, yn−1)},

and for B,

where  A  and  B  are  evaluated  at  the  same  n  points,  then  a  point-value
representation for C is

Thus  the  time  to  add  two  polynomials  of  degree-bound  n  in  point-value
form is Θ(n).

Similarly,  the  point-value  representation  is  convenient  for  multiplying
polynomials. If C(x) = A(x)B(x), then C(xk) = A(xk)B(xk) for any point xk,
and  to  obtain  a  point-value  representation  for  C,  just  pointwise  multiply  a
point-value  representation  for  A  by  a  point-value  representation  for  B.
Polynomial  multiplication  differs  from  polynomial  addition  in  one  key
aspect, however: degree(C) = degree(A) + degree(B), so that if A and B have
degree-bound  n,  then  C  has  degree-bound  2n.  A  standard  point-value
representation  for  A  and  B  consists  of  n  point-value  pairs  for  each
polynomial.  Multiplying  these  together  gives  n  point-value  pairs,  but  2n
pairs  are  necessary  to  interpolate  a  unique  polynomial  C  of  degree-bound
2n.  (See  Exercise  30.1-4.)  Instead,  begin  with  “extended”  point-value
representations  for  A  and  for  B  consisting  of  2n  point-value  pairs  each.
Given an extended point-value representation for A,

{(x0, y0), (x1, y1), … , (x2n−1, y2n−1)},

and a corresponding extended point-value representation for B,

then a point-value representation for C is

Given  two  input  polynomials  in  extended  point-value  form,  multiplying
them to obtain the point-value form of the result takes just Θ(n) time, much
less  than  the  Θ(n2)  time  required  to  multiply  polynomials  in  coefficient
form.

Finally, let’s consider how to evaluate a polynomial given in point-value
form  at  a  new  point.  For  this  problem,  the  simplest  approach  known  is  to
first convert the polynomial to coefficient form and then evaluate it at the
new point.

Fast multiplication of polynomials in coefficient form

Can  the  linear-time  multiplication  method  for  polynomials  in  point-value
form  expedite  polynomial  multiplication  in  coefficient  form?  The  answer
hinges  on  whether  it  is  possible  convert  a  polynomial  quickly  from
coefficient form to point-value form (evaluate) and vice versa (interpolate).

Figure 30.1 A graphical outline of an efficient polynomial-multiplication process. Representations on
the top are in coefficient form, and those on the bottom are in point-value form. The arrows from left
to right correspond to the multiplication operation. The ω2n terms are complex (2n)th roots of unity.

Any points can serve as evaluation points, but certain evaluation points
allow conversion between representations in only Θ(n lg n) time. As we’ll
see  in  Section  30.2,  if  “complex  roots  of  unity”  are  the  evaluation  points,
then the discrete Fourier transform (or DFT) evaluates and the inverse DFT
interpolates.  Section  30.2  shows  how  the  FFT  accomplishes  the  DFT  and
inverse DFT operations in Θ(n lg n) time.

Figure  30.1  shows  this  strategy  graphically.  One  minor  detail  concerns
degree-bounds.  The  product  of  two  polynomials  of  degree-bound  n  is  a
polynomial of degree-bound 2n. Before evaluating the input polynomials A
and  B,  therefore,  first  double  their  degree-bounds  to  2n  by  adding  n  high-
order coefficients of 0. Because the vectors have 2n elements, use “complex
(2n)th roots of unity,” which are denoted by the ω2n terms in Figure 30.1.

The  following  procedure  takes  advantage  of  the  FFT  to  multiply  two
polynomials A(x) and B(x) of degree-bound n in Θ(n lg n)-time, where the
input  and  output  representations  are  in  coefficient  form.  The  procedure
assumes that n is an exact power of 2, so if it isn’t, just add high-order zero
coefficients.

1. Double  degree-bound:  Create  coefficient  representations  of  A(x)
and  B(x)  as  degree-bound  2n  polynomials  by  adding  n  high-order
zero coefficients to each.

2. Evaluate: Compute point-value representations of A(x) and B(x) of
length  2n  by  applying  the  FFT  of  order  2n  on  each  polynomial.
These representations contain the values of the two polynomials at
the (2n)th roots of unity.

3. Pointwise  multiply:  Compute  a  point-value  representation  for  the
polynomial  C(x)  =  A(x)B(x)  by  multiplying  these  values  together
pointwise.  This  representation  contains  the  value  of  C(x)  at  each
(2n)th root of unity.

4. Interpolate: Create the coefficient representation of the polynomial
C(x)  by  applying  the  FFT  on  2n  point-value  pairs  to  compute  the
inverse DFT.

Steps (1) and (3) take Θ(n) time, and steps (2) and (4) take Θ(n lg n) time.
Thus,  once  we  show  how  to  use  the  FFT,  we  will  have  proven  the
following.

Theorem 30.2
Two  polynomials  of  degree-bound  n  with  both  the  input  and  output
representations in coefficient form can be multiplied in Θ(n lg n) time.

▪

Exercises

30.1-1
Multiply the polynomials A(x) = 7x3 − x2 + x − 10 and B(x) = 8x3 − 6x + 3
using equations (30.1) and (30.2).

30.1-2
Another  way  to  evaluate  a  polynomial  A(x)  of  degree-bound  n  at  a  given
point x0 is to divide A(x) by the polynomial (x − x0), obtaining a quotient
polynomial q(x) of degree-bound n − 1 and a remainder r, such that

A(x) = q(x)(x − x0) + r.

Then  we  have  A(x0)  =  r.  Show  how  to  compute  the  remainder  r  and  the
coefficients of q(x) from x0 and the coefficients of A in Θ(n) time.

30.1-3
Given a polynomial
. Show how to
, define
derive  a  point-value  representation  for  Arev(x)  from  a  point-value
representation for A(x), assuming that none of the points is 0.

30.1-4
Prove  that  n  distinct  point-value  pairs  are  necessary  to  uniquely  specify  a
polynomial  of  degree-bound  n,  that  is,  if  fewer  than  n  distinct  point-value
pairs are given, they fail to specify a unique polynomial of degree-bound n.
(Hint:  Using Theorem  30.1,  what  can  you  say  about  a  set  of  n  −  1  point-
value pairs to which you add one more arbitrarily chosen point-value pair?)

30.1-5
Show how to use equation (30.5) to interpolate in Θ(n2) time. (Hint: First
compute  the  coefficient  representation  of  the  polynomial  ∏j(x  −  xj)  and
then  divide  by  (x  −  xk)  as  necessary  for  the  numerator  of  each  term  (see
Exercise  30.1-2).  You  can  compute  each  of  the  n  denominators  in  O(n)
time.)

30.1-6
Explain what is wrong with the “obvious” approach to polynomial division
using  a  point-value  representation:  dividing  the  corresponding  y  values.
Discuss separately the case in which the division comes out exactly and the
case in which it doesn’t.

30.1-7
Consider  two  sets  A  and  B,  each  having  n  integers  in  the  range  from  0  to
10n. The Cartesian sum of A and B is defined by

C = {x + y : x ∈ A and y ∈ B}.

The  integers  in  C  lie  in  the  range  from  0  to  20n.  Show  how,  in  O(n  lg  n)
time, to find the elements of C and the number of times each element of C

is  realized  as  a  sum  of  elements  in  A  and  B.  (Hint:  Represent  A  and  B  as
polynomials of degree at most 10n.)

30.2    The DFT and FFT

In Section 30.1, we claimed that by computing the DFT and its inverse by
using  the  FFT,  it  is  possible  to  evaluate  and  interpolate  a  degree  n
polynomial  at  the  complex  roots  of  unity  in  Θ(n  lg  n)  time.  This  section
defines  complex  roots  of  unity,  studies  their  properties,  defines  the  DFT,
and then shows how the FFT computes the DFT and its inverse in Θ(n lg n)
time.

Complex roots of unity

A complex nth root of unity is a complex number ω such that

ωn = 1.

There are exactly n complex nth roots of unity: e2πik/n for k = 0, 1, … , n −
1.  To  interpret  this  formula,  use  the  definition  of  the  exponential  of  a
complex number:

eiu = cos(u) + i sin(u).

Figure  30.2  shows  that  the  n  complex  roots  of  unity  are  equally  spaced
around the circle of unit radius centered at the origin of the complex plane.
The value

Figure 30.2 The values of
root of unity.

 in the complex plane, where ω8 = e2πi/8 is the principal 8th

is the principal nth root of unity.2 All other complex nth roots of unity are
powers of ωn.

The n complex nth roots of unity,

form  a  group  under  multiplication  (see  Section  31.3).  This  group  has  the
same  structure  as  the  additive  group  (ℤn,  +)  modulo  n,  since
.  The  following
implies  that
lemmas furnish some essential properties of the complex nth roots of unity.

.  Similarly,

Lemma 30.3 (Cancellation lemma)
For any integers n > 0, k ≥ 0, and d > 0,

Proof   The lemma follows directly from equation (30.6), since

Corollary 30.4

▪

For any even integer n > 0,

Proof   The proof is left as Exercise 30.2-1.

▪

Lemma 30.5 (Halving lemma)
If n > 0 is even, then the squares of the n complex nth roots of unity are the
n/2 complex (n/2)th roots of unity.

Proof   By the cancellation lemma,
 for any nonnegative integer k.
Squaring all of the complex nth roots of unity produces each (n/2)th root of
unity exactly twice, since

 and

Thus
30.4  to  prove  this  property,  since
thus

.

 have the same square. We could also have used Corollary
,  and
  implies

▪

As  we’ll  see,  the  halving  lemma  is  essential  to  the  divide-and-conquer
approach for converting between coefficient and point-value representations
of polynomials, since it guarantees that the recursive subproblems are only
half as large.

Lemma 30.6 (Summation lemma)
For any integer n ≥ 1 and nonzero integer k not divisible by n,

Proof   Equation (A.6) on page 1142 applies to complex values as well as to
reals, giving

To  see  that  the  denominator  is  not  0,  note  that
divisible by n, which the lemma statement prohibits.

  only  when  k  is

▪

The DFT

Recall the goal of evaluating a polynomial

,

of degree-bound n at
 (that is, at the n complex nth roots of
unity).3  The  polynomial  A  is  given  in  coefficient  form:  a  =  (a0,  a1,  …  ,
an−1). Let us define the results yk, for k = 0, 1, … , n − 1, by

,

The vector y = (y0, y1, … , yn−1) is the discrete Fourier transform (DFT)
of the coefficient vector a = (a0, a1, … , an−1). We also write y = DFTn(a).

The FFT

The fast Fourier transform (FFT) takes advantage of the special properties
of  the  complex  roots  of  unity  to  compute  DFTn(a)  in  Θ(n  lg  n)  time,  as
opposed  to  the  Θ(n2)  time  of  the  straightforward  method.  Assume
throughout  that  n  is  an  exact  power  of  2. Although  strategies  for  dealing
with  sizes  that  are  not  exact  powers  of  2  are  known,  they  are  beyond  the
scope of this book.

The FFT method employs a divide-and-conquer strategy, using the even-
indexed  and  odd-indexed  coefficients  of  A(x)  separately  to  define  the  two
new polynomials Aeven(x) and Aodd(x) of degree-bound n/2:
Aeven(x) = a0 + a2x + a4x2 + ⋯ + an−2xn/2−1,
Aodd(x) = a1 + a3x + a5x2 + ⋯ + an−1xn/2−1.
Note that Aeven contains all the even-indexed coefficients of A (the binary
representation of the index ends in 0) and Aodd contains all the odd-indexed
coefficients (the binary representation of the index ends in 1). It follows that

so that the problem of evaluating A(x) at

,

 reduces to

1. evaluating the degree-bound n/2 polynomials Aeven(x) and Aodd(x)

at the points

and then

2. combining the results according to equation (30.9).

By the halving lemma, the list of values (30.10) consists not of n distinct
values  but  only  of  the  n/2  complex  (n/2)th  roots  of  unity,  with  each  root
occurring  exactly  twice.  Therefore,  the  FFT  recursively  evaluates  the
polynomials  Aeven  and  Aodd  of  degree-bound  n/2  at  the  n/2  complex
(n/2)th roots of unity. These subproblems have exactly the same form as the
original  problem,  but  are  half  the  size,  dividing  an  n-element  DFTn
computation
computations.  This
two  n/2-element  DFTn/2
decomposition is the basis for the FFT procedure on the next page, which
computes the DFT of an n-element vector a = (a0, a1, … , an−1), where n
is an exact power of 2.

into

The FFT procedure works as follows. Lines 1–2 represent the base case
of  the  recursion. The  DFT  of  1  element  is  the  element  itself,  since  in  this
case

y0 =

= a0 · 1
= a0.

Lines  5–6  define  the  coefficient  vectors  for  the  polynomials  Aeven  and
Aodd.  Lines  3,  4,  and  12  guarantee  that  ω  is  updated  properly  so  that
. (Keeping a running value of ω
whenever lines 10–11 are executed,
from  iteration  to  iteration  saves  time  over  computing
  from  scratch  each
time  through  the  for  loop.4)  Lines  7–8  perform  the  recursive  DFTn/2
computations, setting, for k = 0, 1, … , n/2 − 1,

FFT(a, n)
  1if n == 1
  2

return a
  3ωn = e2πi/n
  4ω = 1
  5aeven = (a0, a2, … , an−2)
  6aodd = (a1, a3, … , an−1)
  7yeven = FFT(aeven, n/2)
  8yodd = FFT(aodd, n/2)
  9for k = 0 to n/2 − 1
10

11
12 ω = ωωn
13return y

// DFT of 1 element is the element itself

// at this point,

or, since

 by the cancellation lemma,

Lines 10–11 combine the results of the recursive DFTn/2 calculations. For
the first n/2 results y0, y1, … , yn/2−1, line 10 yields

For yn/2, yn/2+1, … , yn−1, letting k = 0, 1, … , n/2 − 1, line 11 yields

Thus the vector y returned by FFT is indeed the DFT of the input vector a.

Lines 10 and 11 multiply each value

, for k = 0, 1, … , n/2 − 1.
,  and  line  11  subtracts  it.  Because  each
 appears in both its positive and negative forms, we call the factors

Line  10  adds  this  product  to
factor

 by

 twiddle factors.

To determine the running time of the procedure FFT, note that exclusive
of the recursive calls, each invocation takes Θ(n) time, where n is the length
of the input vector. The recurrence for the running time is therefore

T(n) = 2T(n/2) + Θ(n)

= Θ(n lg n),

by case 2 of the master theorem (Theorem 4.1). Thus the FFT can evaluate
a polynomial of degree-bound n at the complex nth roots of unity in Θ(n lg
n) time.

Interpolation at the complex roots of unity

The  polynomial  multiplication  scheme  entails  converting  from  coefficient
form to point-value form by evaluating the polynomial at the complex roots
of  unity,  pointwise  multiplying,  and  finally  converting  from  point-value
form  back  to  coefficient  form  by  interpolating.  We’ve  just  seen  how  to

evaluate, so now we’ll see how to interpolate the complex roots of unity by
a polynomial. To interpolate, we’ll write the DFT as a matrix equation and
then look at the form of the matrix inverse.

From equation (30.4), we can write the DFT as the matrix product y =
Vna, where Vn is a Vandermonde matrix containing the appropriate powers
of ωn:

The (k, j) entry of Vn is
entries of Vn form a multiplication table for factors 0 to n − 1.

, for j, k = 0, 1, … , n − 1. The exponents of the

For the inverse operation, which we write as

, multiply y by

the matrix

, the inverse of Vn.

Theorem 30.7
For j, k = 0, 1, … , n − 1, the (j, k) entry of

 is

.

Proof   We show that
entry of

:

, the n × n identity matrix. Consider the (k, k′)

This summation equals 1 if k′ = k, and it is 0 otherwise by the summation
lemma (Lemma 30.6). Note that in order for the summation lemma to apply,
k′ − k must not be divisible by n. Indeed, it is not, since −(n − 1) ≤ k′ − k ≤ n
− 1.

▪

With the inverse matrix

 defined,

 is given by

for j = 0, 1, … , n − 1. By comparing equations (30.8) and (30.11), you can
see  that  if  you  modify  the  FFT  algorithm  to  switch  the  roles  of  a  and  y,
replace ωn by
, and divide each element of the result by n, you get the
inverse DFT (see Exercise 30.2-4). Thus,
time as well.

 is computable in Θ(n lg n)

Thus,  the  FFT  and  the  inverse  FFT  provide  a  way  to  transform  a
polynomial  of  degree-bound  n  back  and  forth  between  its  coefficient
representation  and  a  point-value  representation  in  only  Θ(n  lg  n)  time.  In
the  context  of  polynomial  multiplication,  we  have  shown  the  following
about the convolution a ⊗ b of vectors a and b:

Theorem 30.8 (Convolution theorem)
For any two vectors a and b of length n, where n is an exact power of 2,

where the vectors a and b are padded with 0s to length 2n and · denotes the
componentwise product of two 2n-element vectors.

▪

Exercises

30.2-1
Prove Corollary 30.4.

30.2-2
Compute the DFT of the vector (0, 1, 2, 3).

30.2-3
Do Exercise 30.1-1 by using the Θ(n lg n)-time scheme.

30.2-4
Write pseudocode to compute

 in Θ(n lg n) time.

30.2-5
Describe the generalization of the FFT procedure to the case in which n is
an exact power of 3. Give a recurrence for the running time, and solve the
recurrence.

★ 30.2-6
Instead of performing an n-element FFT over the field of complex numbers
(where n is an exact power of 2), let’s use the ring ℤm of integers modulo
m, where m = 2tn/2 + 1 and t is an arbitrary positive integer. We can use ω =
2t instead of ωn as a principal nth root of unity, modulo m. Prove that the
DFT and the inverse DFT are well defined in this system.

30.2-7
Given  a  list  of  values  z0,  z1,  …  ,  zn−1  (possibly  with  repetitions),  show
how to find the coefficients of a polynomial P(x) of degree-bound n + 1 that
has  zeros  only  at  z0,  z1,  …  ,  zn−1  (possibly  with  repetitions).  Your
procedure should run in O(n lg2 n) time. (Hint: The polynomial P(x) has a
zero at zj if and only if P(x) is a multiple of (x − zj).)

★ 30.2-8
The  chirp  transform  of  a  vector  a  =  (a0,  a1,  …  ,  an−1)  is  the  vector  y  =
(y0, y1, … , yn−1), where
 and z is any complex number. The
DFT is therefore a special case of the chirp transform, obtained by taking z
= ωn. Show how to evaluate the chirp transform for any complex number z
in O(n lg n) time. (Hint: Use the equation

to view the chirp transform as a convolution.)

30.3    FFT circuits

Many  of  the  FFT’s  applications  in  signal  processing  require  the  utmost
speed,  and  so  the  FFT  is  often  implemented  as  a  circuit  in  hardware. The

FFT’s  divide-and-conquer  structure  enables  the  circuit  to  have  a  parallel
structure  so  that  the  depth  of  the  circuit—the  maximum  number  of
computational elements between any output and any input that can reach it
—is  Θ(lg  n).  Moreover,  the  structure  of  the  FFT  circuit  has  several
interesting mathematical properties, which we won’t go into here.

Butterfly operations

Notice  that  the  for  loop  of  lines  9–12  of  the  FFT  procedure  computes  the
 twice per iteration: once in line 10 and once in line 11. A good
value
optimizing  compiler  produces  code
this  common
subexpression just once, storing its value into a temporary variable, so that
lines 10–11 are treated like the three lines

that  evaluates

,  storing  the
This  operation,  multiplying  the  twiddle  factor
product into the temporary variable t, and adding and subtracting t from
,
is known as a butterfly operation. Figure 30.3 shows it as a circuit, and you
can  see  how  it  vaguely  resembles  the  shape  of  a  butterfly.  (Although  less
colorfully, it could have been called a “bowtie” operation.)

  by

Figure  30.3  A  circuit  for  a  butterfly  operation.  (a)  The  two  input  values  enter  from  the  left,  the
,  and  the  sum  and  difference  are  output  on  the  right.  (b) A
twiddle  factor
simplified drawing of a butterfly operation, which we’ll use when drawing the parallel FFT circuit.

  is  multiplied  by

Figure  30.4  The  schema  for  the  conquer  and  combine  steps  of  an  n-input,  n-output  FFT  circuit,
FFTn, shown for n = 8. Inputs enter from the left, and outputs exit from the right. The input values
first go through two FFTn/2 circuits, and then n/2 butterfly circuits combine the results. Only the top
and bottom wires entering a butterfly interact with it: wires that pass through the middle of a butterfly
do not affect that butterfly, nor are their values changed by that butterfly.

Recursive circuit structure

The  FFT  procedure  follows  the  divide-and-conquer  strategy  that  we  first
saw in Section 2.3.1:

Divide  the  n-element  input  vector  into  its  n/2  even-indexed  and  n/2  odd-

indexed elements.

Conquer by recursively computing the DFTs of the two subproblems, each

of size n/2.

Combine by performing n/2 butterfly operations. These butterfly operations

work with twiddle factors

,

.

The  circuit  schema  in  Figure  30.4  follows  the  conquer  and  combine
steps of this pattern for an FFT circuit with n inputs and n outputs, denoted
by FFTn. Each line is a wire that carries a value. Inputs enter from the left,
one  per  wire,  and  outputs  exit  from  the  right.  The  conquer  step  runs  the
inputs through two FFTn/2 circuits, which are also constructed recursively.

The  values  produced  by  the  two  FFTn/2  circuits  feed  into  n/2  butterfly
circuits,  with  twiddle  factors
,  to  combine  the  results.  The
base case of the recursion occurs when n = 1, where the sole output value
equals the sole input value. An FFT1 circuit, therefore, does nothing, and so
the  smallest  nontrivial  FFT  circuit  is  FFT2,  a  single  butterfly  operation
whose twiddle factor is

,

.

Figure  30.5  The  tree  of  input  vectors  to  the  recursive  calls  of  the  FFT  procedure.  The  initial
invocation is for n = 8.

Permuting the inputs

How does the divide step enter into the circuit design? Let’s examine how
input  vectors  to  the  various  recursive  calls  of  the  FFT  procedure  relate  to
the  original  input  vector,  so  that  the  circuit  can  emulate  the  divide  step  at
the start for all levels of recursion. Figure 30.5 arranges the input vectors to
the  recursive  calls  in  an  invocation  of  FFT  in  a  tree  structure,  where  the
initial call is for n = 8. The tree has one node for each call of the procedure,
labeled  by  the  elements  of  the  initial  call  as  they  appear  in  the
corresponding input vector. Each FFT invocation makes two recursive calls,
unless  it  has  received  a  1-element  vector. The  first  call  appears  in  the  left
child, and the second call appears in the right child.

Looking  at  the  tree,  observe  that  if  you  arrange  the  elements  of  the
initial  vector  a  into  the  order  in  which  they  appear  in  the  leaves,  you  can
trace  the  execution  of  the  FFT  procedure,  but  bottom  up  instead  of  top
down. First, take the elements in pairs, compute the DFT of each pair using
one butterfly operation, and replace the pair with its DFT. The vector then
holds  n/2  two-element  DFTs.  Next,  take  these  n/2  DFTs  in  pairs  and
compute the DFT of the four vector elements they come from by executing

two  butterfly  operations,  replacing  two  two-element  DFTs  with  one  four-
element  DFT.  The  vector  then  holds  n/4  four-element  DFTs.  Continue  in
this  manner  until  the  vector  holds  two  (n/2)-element  DFTs,  which  n/2
butterfly operations combine into the final n-element DFT. In other words,
you can start with the elements of the initial vector a, but rearranged as in
the  leaves  of  Figure  30.5,  and  then  feed  them  directly  into  a  circuit  that
follows the schema in Figure 30.4.

Let’s  think  about  the  permutation  that  rearranges  the  input  vector.  The
order  in  which  the  leaves  appear  in  Figure  30.5  is  a  bit-reversal
permutation.  That  is,  letting  rev(k)  be  the  lg  n-bit  integer  formed  by
reversing the bits of the binary representation of k, then vector element ak
moves to position rev(k). In Figure 30.5, for example, the leaves appear in
the order 0, 4, 2, 6, 1, 5, 3, 7. This sequence in binary is 000, 100, 010, 110,
001,  101,  011,  111,  and  you  can  obtain  it  by  reversing  the  bits  of  each
number in the sequence 0, 1, 2, 3, 4, 6, 7 or, in binary, 000, 001, 010, 011,
100,  101,  110,  111.  To  see  in  general  that  the  input  vector  should  be
rearranged  by  a  bit-reversal  permutation,  note  that  at  the  top  level  of  the
tree,  indices  whose  low-order  bit  is  0  go  into  the  left  subtree  and  indices
whose  low-order  bit  is  1  go  into  the  right  subtree.  Stripping  off  the  low-
order bit at each level, continue this process down the tree, until you get the
order given by the bit-reversal permutation at the leaves.

The full FFT circuit

Figure 30.6 depicts the entire circuit for n = 8. The circuit begins with a bit-
reversal  permutation  of  the  inputs,  followed  by  lg  n  stages,  each  stage
consisting  of  n/2  butterflies  executed  in  parallel.  Assuming  that  each
butterfly  circuit  has  constant  depth,  the  full  circuit  has  depth  Θ(lg  n).  The
butterfly  operations  at  each  level  of  recursion  in  the  FFT  procedure  are
independent, and so the circuit performs them in parallel. The figure shows
wires running from left to right, carrying values through the lg n stages. For
s = 1, 2, … , lg n, stage s consists of n/2s groups of butterflies, with 2s−1
butterflies  per  group.  The  twiddle  factors  in  stage  s  are
,
where m = 2s.

,

Exercises

30.3-1
Show the values on the wires for each butterfly input and output in the FFT
circuit of Figure 30.6, given the input vector (0, 2, 3, −1, 4, 5, 7, 9).

30.3-2
Consider an FFTn circuit, such as in Figure 30.6, with wires 0, 1, … , n−1
(wire j has output yj) and stages numbered as in the figure. Stage s, for s =
1,  2  …  ,  lg  n,  consists  of  n/2s  groups  of  butterflies. Which  two  wires  are
inputs and outputs for the jth butterfly circuit in the gth group in stage s?

30.3-3
Consider a b-bit integer k in the range 0 ≤ k < 2b. Treating k as a b-element
vector  over  {0,  1},  describe  a  b  ×  b  matrix  M  such  that  the  matrix-vector
product Mk is the binary representation of rev(k).

Figure 30.6 A full circuit that computes the FFT in parallel, here shown for n = 8 inputs. It has lg n
stages, and each stage comprises n/2 butterflies that can operate in parallel. As in Figure 30.4, only
the top and bottom wires entering a butterfly interact with it. For example, the top butterfly in stage 2
has inputs and outputs only on wires 0 and 2 (the wires with outputs y0 and y2, respectively). This
circuit has depth Θ(lg n) and performs Θ(n lg n) butterfly operations altogether.

30.3-4

Write  pseudocode  for  the  procedure  BIT-REVERSE-PERMUTATION(a,
n), which performs the bit-reversal permutation on a vector a of length n in-
place. Assume  that  you  may  call  the  procedure  BIT-REVERSE-OF(k,  b),
which returns an integer that is the b-bit reversal of the nonnegative integer
k, where 0 ≤ k < 2b.

★ 30.3-5
Suppose  that  the  adders  within  the  butterfly  operations  of  a  given  FFT
circuit sometimes fail in such a manner that they always produce a 0 output,
independent of their inputs. In addition, suppose that exactly one adder has
failed,  but  you  don’t  know  which  one.  Describe  how  you  can  identify  the
failed adder by supplying inputs to the overall FFT circuit and observing the
outputs. How efficient is your method?

Problems

30-1     Divide-and-conquer multiplication

a. Show how to multiply two linear polynomials ax + b and cx + d using

only three multiplications. (Hint: One of the multiplications is (a + b) · (c
+ d).)

b. Give two divide-and-conquer algorithms for multiplying two

polynomials of degree-bound n in Θ(nlg 3) time. The first algorithm
should divide the input polynomial coefficients into a high half and a low
half, and the second algorithm should divide them according to whether
their index is odd or even.

c. Show how to multiply two n-bit integers in O(nlg 3) steps, where each

step operates on at most a constant number of 1-bit values.

30-2     Multidimensional fast Fourier transform

The  1-dimensional  discrete  Fourier  transform  defined  by  equation  (30.8)
generalizes  to  d  dimensions.  The  input  is  a  d-dimensional  array  A  =
(aj1,j2,…,jd
) whose dimensions are n1, n2, … , nd, where n1n2 ⋯ nd = n.
The d-dimensional discrete Fourier transform is defined by the equation

for 0 ≤ k1 < n1, 0 ≤ k2 < n2, … , 0 ≤ kd < nd.

a. Show how to produce a d-dimensional DFT by computing 1-dimensional
DFTs on each dimension in turn. That is, first compute n/n1 separate 1-
dimensional DFTs along dimension 1. Then, using the result of the DFTs
along dimension 1 as the input, compute n/n2 separate 1-dimensional
DFTs along dimension 2. Using this result as the input, compute n/n3
separate 1-dimensional DFTs along dimension 3, and so on, through
dimension d.

b. Show that the ordering of dimensions does not matter, so that if you

compute the 1-dimensional DFTs in any order of the d dimensions, you
compute the d-dimensional DFT.

c. Show that if you compute each 1-dimensional DFT by computing the fast
Fourier transform, the total time to compute a d-dimensional DFT is O(n
lg n), independent of d.

30-3     Evaluating all derivatives of a polynomial at a point
Given a polynomial A(x) of degree-bound n, we define its tth derivative by

In this problem, you will show how to determine A(t)(x0) for t = 0, 1, … , n
−  1,  given  the  coefficient  representation  (a0,  a1,  …  ,  an−1)  of  A(x)  and  a
point x0.

a. Given coefficients b0, b1, … , bn−1 such that

show how to compute A(t)(x0), for t = 0, 1, … , n − 1, in O(n) time.

b. Explain how to find b0, b1, … , bn−1 in O(n lg n) time, given

for k = 0, 1, … , n − 1.

c. Prove that

where f(j) = aj · j! and

d. Explain how to evaluate

 for k = 0, 1, … , n − 1 in O(n lg n)

time. Conclude that you can evaluate all nontrivial derivatives of A(x) at
x0 in O(n lg n) time.

30-4     Polynomial evaluation at multiple points
Problem 2-3 showed how to evaluate a polynomial of degree-bound n at a
single point in O(n) time using Horner’s rule. This chapter described how to
evaluate such a polynomial at all n complex roots of unity in O(n lg n) time
using the FFT. Now, you will show how to evaluate a polynomial of degree-
bound n at n arbitrary points in O(n lg2 n) time.

To do so, assume that you can compute the polynomial remainder when
one such polynomial is divided by another in O(n lg n) time. For example,
the remainder of 3x3 + x2 − 3x + 1 when divided by x2 + x + 2 is

(3x3 + x2 − 3x + 1) mod (x2 + x + 2) = −7x + 5.

Given the coefficient representation of a polynomial

 and
n points x0, x1, … , xn−1, your goal is to compute the n values A(x0), A(x1),
… , A(xn−1). For 0 ≤ i ≤ j ≤ n − 1, define the polynomials
and Qij(x) = A(x) mod Pij(x). Note that Qij(x) has degree at most j − i.

a. Prove that A(x) mod (x − z) = A(z) for any point z.

b. Prove that Qkk(x) = A(xk) and that Q0,n−1(x) = A(x).

c. Prove that for i ≤ k ≤ j, we have both Qik(x) = Qij(x) mod Pik(x) and

Qkj(x) = Qij(x) mod Pkj(x).
d. Give an O(n lg2 n)-time algorithm to evaluate A(x0), A(x1), … , A(xn−1).

30-5     FFT using modular arithmetic
As  defined,  the  discrete  Fourier  transform  requires  computation  with
complex numbers, which can result in a loss of precision due to round-off
errors.  For  some  problems,  the  answer  is  known  to  contain  only  integers,
and a variant of the FFT based on modular arithmetic can guarantee that the
answer  is  calculated  exactly.  An  example  of  such  a  problem  is  that  of
multiplying  two  polynomials  with  integer  coefficients.  Exercise  30.2-6
gives one approach, using a modulus of length Ω(n) bits to handle a DFT on
n points. This problem explores another approach that uses a modulus of the
more  reasonable  length  O(lg  n),  but  it  requires  that  you  understand  the
material of Chapter 31. Let n be an exact power of 2.

a. You wish to search for the smallest k such that p = kn + 1 is prime. Give a
simple heuristic argument why you might expect k to be approximately ln
n. (The value of k might be much larger or smaller, but you can
reasonably expect to examine O(lg n) candidate values of k on average.)
How does the expected length of p compare to the length of n?

Let g be a generator of

, and let w = gk mod p.

b. Argue that the DFT and the inverse DFT are well-defined inverse

operations modulo p, where w is used as a principal nth root of unity.

c. Show how to make the FFT and its inverse work modulo p in O(n lg n)
time, where operations on words of O(lg n) bits take unit time. Assume
that the algorithm is given p and w.

d. Compute the DFT modulo p = 17 of the vector (0, 5, 3, 7, 7, 2, 1, 6).

(Hint: Verify and use the fact that g = 3 is a generator of

.)

Chapter notes

Van Loan’s book [442] provides an outstanding treatment of the fast Fourier
transform.  Press,  Teukolsky,  Vetterling,  and  Flannery  [365,  366]  offer  a
good  description  of  the  fast  Fourier  transform  and  its  applications.  For  an
excellent introduction to signal processing, a popular FFT application area,
see the texts by Oppenheim and Schafer [347] and Oppenheim and Willsky
[348]. The Oppenheim and Schafer book also shows how to handle cases in
which n is not an exact power of 2.

Fourier analysis is not limited to 1-dimensional data. It is widely used in
image processing to analyze data in two or more dimensions. The books by
Gonzalez  and  Woods  [194]  and  Pratt  [363]  discuss  multidimensional
Fourier  transforms  and  their  use  in  image  processing,  and  books  by
Tolimieri, An, and Lu [439] and Van Loan [442] discuss the mathematics of
multidimensional fast Fourier transforms.

Cooley  and  Tukey  [101]  are  widely  credited  with  devising  the  FFT  in
the 1960s. The FFT had in fact been discovered many times previously, but
its  importance  was  not  fully  realized  before  the  advent  of  modern  digital
computers.  Although  Press,  Teukolsky,  Vetterling,  and  Flannery  attribute
the  origins  of  the  method  to  Runge  and  König  in  1924,  an  article  by
Heideman,  Johnson,  and  Burrus  [211]  traces  the  history  of  the  FFT  as  far
back as C. F. Gauss in 1805.

Frigo and Johnson [161] developed a fast and flexible implementation of
the  FFT,  called  FFTW  (“fastest  Fourier  transform  in  the West”).  FFTW  is
designed  for  situations  requiring  multiple  DFT  computations  on  the  same
problem  size.  Before  actually  computing  the  DFTs,  FFTW  executes  a
“planner,”  which,  by  a  series  of  trial  runs,  determines  how  best  to
decompose  the  FFT  computation  for  the  given  problem  size  on  the  host
machine.  FFTW  adapts  to  use  the  hardware  cache  efficiently,  and  once
subproblems are small enough, FFTW solves them with optimized, straight-
line code. Moreover, FFTW has the advantage of taking Θ(n lg n) time for
any problem size n, even when n is a large prime.

Although  the  standard  Fourier  transform  assumes  that  the  input
represents  points  that  are  uniformly  spaced  in  the  time  domain,  other
techniques  can  approximate  the  FFT  on  “nonequispaced”  data. The  article
by Ware [449] provides an overview.

1 Interpolation is a notoriously tricky problem from the point of view of numerical stability. Although
the approaches described here are mathematically correct, small differences in the inputs or round-off
errors during computation can cause large differences in the result.
2 Many other authors define ωn differently: ωn = e−2πi/n. This alternative definition tends to be used
for signal-processing applications. The underlying mathematics is substantially the same with either
definition of ωn.
3 The length n is actually what Section 30.1 referred to as 2n, since the degree-bound of the given
polynomials  doubles  prior  to  evaluation.  In  the  context  of  polynomial  multiplication,  therefore,  we
are actually working with complex (2n)th roots of unity.
4 The downside of iteratively updating ω is that round-off errors can accumulate, especially for larger
input sizes. Several techniques to limit the magnitude of FFT round-off errors have been proposed,
but are beyond the scope of this book. If several FFTs are going to be run on inputs of the same size,
then it might be worthwhile to directly precompute a table of all n/2 values of

.

