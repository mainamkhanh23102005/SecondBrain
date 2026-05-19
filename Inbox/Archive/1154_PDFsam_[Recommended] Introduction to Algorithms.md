31        Number-Theoretic Algorithms

Number  theory  was  once  viewed  as  a  beautiful  but  largely  useless
subject  in  pure  mathematics.  Today  number-theoretic  algorithms  are
used widely, due in large part to the invention of cryptographic schemes
based  on  large  prime  numbers.  These  schemes  are  feasible  because  we
can  ﬁnd  large  primes  quickly,  and  they  are  secure  because  we  do  not
know  how  to  factor  the  product  of  large  primes  (or  solve  related
problems,  such  as  computing  discrete  logarithms)  efﬁciently.  This
chapter presents some of the number theory and related algorithms that
underlie such applications.

We  start  in  Section  31.1  by  introducing  basic  concepts  of  number
theory,  such  as  divisibility,  modular  equivalence,  and  unique  prime
factorization. Section 31.2 studies one of the world’s oldest algorithms:
Euclid’s  algorithm  for  computing  the  greatest  common  divisor  of  two
integers,  and  Section  31.3  reviews  concepts  of  modular  arithmetic.
Section  31.4  then  explores  the  set  of  multiples  of  a  given  number  a,
modulo  n,  and  shows  how  to  ﬁnd  all  solutions  to  the  equation  ax  =  b
(mod n) by using Euclid’s algorithm. The Chinese remainder theorem is
presented  in  Section  31.5.  Section  31.6  considers  powers  of  a  given
number  a,  modulo  n,  and  presents  a  repeated-squaring  algorithm  for
efﬁciently  computing  ab  mod  n,  given  a,  b,  and  n.  This  operation  is  at
the  heart  of  efﬁcient  primality  testing  and  of  much  modern
cryptography,  such  as  the  RSA  public-key  cryptosystem  described  in
Section 31.7. We wrap up in Section 31.8, which examines a randomized

primality test. This test ﬁnds large primes efﬁciently, an essential step in
creating keys for the RSA cryptosystem.

Size of inputs and cost of arithmetic computations

Because we’ll be working with large integers, we need to adjust how to
think  about  the  size  of  an  input  and  about  the  cost  of  elementary
arithmetic operations.

In this chapter, a “large input” typically means an input containing
“large integers” rather than an input containing “many integers” (as for
sorting).  Thus,  the  size  of  an  input  depends  on  the  number  of  bits
required to represent that input, not just the number of integers in the
input. An algorithm with integer inputs a1, a2, …, ak is a polynomial-
time algorithm if it runs in time polynomial in 1g a1, 1g a2, …, 1g ak,
that is, polynomial in the lengths of its binary-encoded inputs.

Most  of  this  book  considers  the  elementary  arithmetic  operations
(multiplications,  divisions,  or  computing  remainders)  as  primitive
operations  that  take  one  unit  of  time.  Counting  the  number  of  such
arithmetic  operations  that  an  algorithm  performs  provides  a  basis  for
making a reasonable estimate of the algorithm’s actual running time on
a  computer.  Elementary  operations  can  be  time-consuming,  however,
when their inputs are large. It thus becomes appropriate to measure how
many  bit  operations  a  number-theoretic  algorithm  requires.  In  this
model,  multiplying  two  β-bit  integers  by  the  ordinary  method  uses
2)  bit  operations.  Similarly,  dividing  a  β-bit  integer  by  a  shorter
Θ(β
integer  or  taking  the  remainder  of  a  β-bit  integer  when  divided  by  a
2) time by simple algorithms. (See Exercise
shorter integer requires Θ(β
31.1-12.) Faster methods are known. For example, a simple divide-and-
conquer  method  for  multiplying  two  β-bit  integers  has  a  running  time
1g  3),  and  O(β  1g  β  1g  1g  β)  time  is  possible.  For  practical
of  Θ(β
2)  algorithm  is  often  best,  and  we  use  this
purposes,  however,  the  Θ(β
bound as a basis for our analyses. In this chapter, we’ll usually analyze
algorithms  in  terms  of  both  the  number  of  arithmetic  operations  and
the number of bit operations they require.

31.1    Elementary number-theoretic notions

This section provides a brief review of notions from elementary number
theory concerning the set ℤ = {…, –2, –1, 0, 1, 2, …} of integers and
the set ℕ = {0, 1, 2, …} of natural numbers.

Divisibility and divisors

The notion of one integer being divisible by another is key to the theory
of numbers. The notation d | a (read “d divides a”) means that a = kd for
some integer k. Every integer divides 0. If a > 0 and d | a, then |d| ≤ |a|.
If d | a, then we also say that a is a multiple of d. If d does not divide a,
we write d ∤ a.

If d | a and d ≥ 0, then d is a divisor of a. Since d | a if and only if –d |
a,  without  loss  of  generality,  we  deﬁne  the  divisors  of  a  to  be
nonnegative, with the understanding that the negative of any divisor of
a  also  divides  a.  A  divisor  of  a  nonzero  integer  a  is  at  least  1  but  not
greater than |a|. For example, the divisors of 24 are 1, 2, 3, 4, 6, 8, 12,
and 24.

Every positive integer a is divisible by the trivial divisors 1 and a. The
nontrivial divisors of a are the factors of a. For example, the factors of
20 are 2, 4, 5, and 10.

Prime and composite numbers

An integer a > 1 whose only divisors are the trivial divisors 1 and a is a
prime  number  or,  more  simply,  a  prime.  Primes  have  many  special
properties and play a critical role in number theory. The ﬁrst 20 primes,
in order, are

2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71.

Exercise 31.1-2 asks you to prove that there are inﬁnitely many primes.
An  integer  a  >  1  that  is  not  prime  is  a  composite  number  or,  more
simply, a composite. For example, 39 is composite because 3 | 39. We call
the integer 1 a unit, and it is neither prime nor composite. Similarly, the
integer 0 and all negative integers are neither prime nor composite.

The division theorem, remainders, and modular equivalence

Given  an  integer  n,  we  can  partition  the  integers  into  those  that  are
multiples  of  n  and  those  that  are  not  multiples  of  n.  Much  number
theory  is  based  upon  reﬁning  this  partition  by  classifying  the  integers
that are not multiples of n according to their remainders when divided
by n. The following theorem provides the basis for this reﬁnement. We
omit the proof (but see, for example, Niven and Zuckerman [345]).

Theorem 31.1 (Division theorem)
For any integer a and any positive integer n, there exist unique integers
q and r such that 0 ≤ r < n and a = qn + r.

▪

The  value  q  =  ⌊a/n⌋  is  the  quotient  of  the  division.  The  value  r  =  a
mod n is the remainder (or residue) of the division, so that n | a if and
only if a mod n = 0.

The  integers  partition  into  n  equivalence  classes  according  to  their
remainders  modulo  n.  The  equivalence  class  modulo  n  containing  an
integer a is

[a]n = {a + kn : k ∈ ℤ}.

For example, [3]7 = {…, –11, –4, 3, 10, 17, …}, and [–4]7 and [10]7 also
denote this set. With the notation deﬁned on page 64, writing a ∈ [b]n is
the  same  as  writing  a  =  b  (mod  n).  The  set  of  all  such  equivalence
classes is

When you see the deﬁnition

it  as  equivalent  to  equation  (31.1)  with  the
you  should  read
understanding that 0 represents [0]n, 1 represents [1]n, and so on. Each
class  is  represented  by  its  smallest  nonnegative  element.  You  should
keep the underlying equivalence classes in mind, however. For example,

if we refer to –1 as a member of ℤn, we are really referring to [n – 1]n,
since –1 = n – 1 (mod n).

Common divisors and greatest common divisors

If  d  is  a  divisor  of  a  and  d  is  also  a  divisor  of  b,  then  d  is  a  common
divisor of a and b. For example, the divisors of 30 are 1, 2, 3, 5, 6, 10,
15, and 30, and so the common divisors of 24 and 30 are 1, 2, 3, and 6.
Any pair of integers has a common divisor of 1.

An important property of common divisors is that

More generally, for any integers x and y,

Also, if a | b, then either |a| ≤ |b| or b = 0, which implies that

The  greatest  common  divisor  of  two  integers  a  and  b  which  are  not
both 0, denoted by gcd(a, b), is the largest of the common divisors of a
and b. For example, gcd(24, 30) = 6, gcd(5, 7) = 1, and gcd(0, 9) = 9. If
a and b are both nonzero, then gcd(a, b) is an integer between 1 and min
{|a|, |b|}. We deﬁne gcd(0, 0) to be 0, so that standard properties of the
gcd function (such as equation (31.9) below) hold universally.

Exercise 31.1-9 asks you to prove the following elementary properties

of the gcd function:

The  following  theorem  provides  an  alternative  and  useful  way  to

characterize gcd(a, b).

Theorem 31.2

If a and b are any integers, not both zero, then gcd(a, b) is the smallest
positive element of the set {ax + by : x, y ∈ ℤ} of linear combinations
of a and b.

Proof   Let s be the smallest positive such linear combination of a and b,
and let s = ax + by for some x, y ∈ ℤ. Let q = ⌊a/s⌋. Equation (3.11) on
page 64 then implies

a mod s = a – qs

= a – q(ax + by)

= a (1 – qx) + b (–qy),

so that a mod s is a linear combination of a and b as well. Because s is
the  smallest  positive  such  linear  combination  and  0  ≤  a  mod  s  <  s
(inequality (3.12) on page 64), a mod s cannot be positive. Hence, a mod
s = 0. Therefore, we have that s | a and, by analogous reasoning, s | b.
Thus,  s  is  a  common  divisor  of  a  and  b,  so  that  gcd(a,  b)  ≥  s.  By
deﬁnition,  gcd(a,  b)  divides  both  a  and  b,  and  s  is  deﬁned  as  a  linear
combination of a and b. Equation (31.4) therefore implies that gcd(a, b)
| s. But gcd(a, b) | s and s > 0 imply that gcd(a, b) ≤ s. Combining gcd(a,
b)  ≥  s  and  gcd(a,  b)  ≤  s  yields  gcd(a,  b)  =  s.  We  conclude  that  s,  the
smallest  positive  linear  combination  of  a  and  b,  is  also  their  greatest
common divisor.

▪

Theorem 31.2 engenders three useful corollaries.

Corollary 31.3
For any integers a and b, if d | a and d | b, then d | gcd(a, b).

Proof   This corollary follows from equation (31.4) and Theorem 31.2,
because gcd(a, b) is a linear combination of a and b,

▪

Corollary 31.4
For all integers a and b and any nonnegative integer n, we have

gcd(an, bn) = n gcd(a, b).

Proof   If n = 0, the corollary is trivial. If n > 0, then gcd(an, bn) is the
smallest  positive  element  of  the  set  {anx  +  bny  :  x,  y  ∈  ℤ},  which  in
turn is n times the smallest positive element of the set {ax + by : x, y ∈
ℤ}.

▪

Corollary 31.5
For all positive integers n, a, and b, if n | ab and gcd(a, n) = 1, then n | b.

Proof   Exercise 31.1-5 asks you to provide the proof.

▪

Relatively prime integers

Two integers a and b are relatively prime if their only common divisor is
1,  that  is,  if  gcd(a,  b)  =  1.  For  example,  8  and  15  are  relatively  prime,
since the divisors of 8 are 1, 2, 4, and 8, and the divisors of 15 are 1, 3,
5,  and  15.  The  following  theorem  states  that  if  two  integers  are  each
relatively prime to an integer p, then their product is relatively prime to
p.

Theorem 31.6
For any integers a, b, and p, we have gcd(ab, p) = 1 if and only if gcd(a,
p) = 1 and gcd(b, p) = 1 both hold.

Proof   If gcd(a, p) = 1 and gcd(b, p) = 1, then it follows from Theorem
31.2 that there exist integers x, y, x′, and y′ such that

ax + py = 1,
bx′ + py′ = 1.

Multiplying these equations and rearranging gives

ab(xx′) + p(ybx′ + y′ax + pyy′) = 1.
Since  1  is  thus  a  positive  linear  combination  of  ab  and  p,  it  is  the
smallest  positive  linear  combination.  Applying  Theorem  31.2  implies
gcd(ab, p) = 1, completing the proof in this direction.

Conversely,  if  gcd(ab,  p)  =  1,  then  Theorem  31.2  implies  that  there

exist integers x and y such that

abx + py = 1.

Writing  abx  as  a(bx)  and  applying  Theorem  31.2  again  proves  that
gcd(a, p) = 1. Proving that gcd(b, p) = 1 is similar.

▪

Integers n1, n2, …, nk are pairwise relatively prime if gcd(ni, nj) = 1

for 1 ≤ i < j ≤ k.

Unique prime factorization

An  elementary  but  important  fact  about  divisibility  by  primes  is  the
following.

Theorem 31.7
For all primes p and all integers a and b, if p | ab, then p | a or p | b (or
both).

Proof   Assume for the purpose of contradiction that p | ab, but that p ∤
a and p ∤ b. Because p > 1 and ab = kp for some k ∈ ℤ, equation (31.10)
gives that gcd(ab, p) = p. We also have that gcd(a, p) = 1 and gcd(b, p) =
1, since the only divisors of p are 1 and p, and we assumed that p divides
neither  a  nor  b.  Theorem  31.6  then  implies  that  gcd(ab,  p)  =  1,
contradicting gcd(ab, p) = p. This contradiction completes the proof.

▪

A consequence of Theorem 31.7 is that any composite integer can be
uniquely factored into a product of primes. Exercise 31.1-11 asks you to
provide a proof.

Theorem 31.8 (Unique prime factorization)
There is exactly one way to write any composite integer a as a product
of the form

where  the  pi  are  prime,  p1  <  p2  <  …  <  pr,  and  the  ei  are  positive
integers.

As an example, the unique prime factorization of the number 6000 is

▪

24 · 31 · 53.

Exercises

31.1-1
Prove that if a > b > 0 and c = a + b, then c mod a = b.

31.1-2
Prove  that  there  are  inﬁnitely  many  primes.  (Hint:  Show  that  none  of
the primes p1, p2, …, pk divide (p1p2 ⋯ pk) + 1.)

31.1-3
Prove that if a | b and b | c, then a | c.

31.1-4
Prove that if p is prime and 0 < k < p, then gcd(k, p) = 1.

31.1-5
Prove Corollary 31.5.

31.1-6
Prove  that  if  p  is  prime  and  0  <  k  <  p,  then
integers a and b and all primes p,

(a + b)p = ap + bp (mod p).

.  Conclude  that  for  all

31.1-7
Prove that if a and b are any positive integers such that a | b, then

(x mod b) mod a = x mod a

for any x. Prove, under the same assumptions, that

x = y (mod b) implies x = y (mod a)

for any integers x and y.

31.1-8
For  any  integer  k  >  0,  an  integer  n  is  a  kth  power  if  there  exists  an
integer a such that ak = n. Furthermore, n > 1 is a nontrivial power if it
is a kth power for some integer k > 1. Show how to determine whether a
given β-bit integer n is a nontrivial power in time polynomial in β.

31.1-9
Prove equations (31.6)–(31.10).

31.1-10
Show  that  the  gcd  operator  is  associative.  That  is,  prove  that  for  all
integers a, b, and c, we have

gcd(a, gcd(b, c)) = gcd(gcd(a, b), c).

★ 31.1-11
Prove Theorem 31.8.

31.1-12
Give  efﬁcient  algorithms  for  the  operations  of  dividing  a  β-bit  integer
by a shorter integer and of taking the remainder of a β-bit integer when
2) time.
divided by a shorter integer. Your algorithms should run in Θ(β

31.1-13
Give an efﬁcient algorithm to convert a given β-bit (binary) integer to a
decimal  representation.  Argue  that  if  multiplication  or  division  of
integers whose length is at most β takes M(β) time, where M(β) = Ω(β),
then you can convert binary to decimal in O(M(β) 1g β) time. (Hint: Use
a divide-and-conquer approach, obtaining the top and bottom halves of
the result with separate recursions.)

31.1-14
Professor Marshall sets up n lightbulbs in a row. The lightbulbs all have
switches, so that if he presses a bulb, it toggles on if it was off and off if
it was on. The lightbulbs all start off. For i = 1, 2, 3, …, n, the professor

presses  bulb  i,  2i,  3i,  ….  After  the  last  press,  which  lightbulbs  are  on?
Prove your answer.

31.2    Greatest common divisor

In this section, we describe Euclid’s algorithm for efﬁciently computing
the  greatest  common  divisor  of  two  integers.  When  we  analyze  the
running  time,  we’ll  see  a  surprising  connection  with  the  Fibonacci
numbers, which yield a worst-case input for Euclid’s algorithm.

We  restrict  ourselves  in  this  section  to  nonnegative  integers.  This
restriction  is  justiﬁed  by  equation  (31.8),  which  states  that  gcd(a,  b)  =
gcd(|a|, |b|).

In principle, for positive integers a and b, their prime factorizations

sufﬁce to compute gcd(a, b). Indeed, if

with 0 exponents being used to make the set of primes p1, p2, …, pr the
same for both a and b, then, as Exercise 31.2-1 asks you to show,

The best algorithms to date for factoring do not run in polynomial time.
Thus,  this  approach  to  computing  greatest  common  divisors  seems
unlikely to yield an efﬁcient algorithm.

Euclid’s algorithm for computing greatest common divisors relies on

the following theorem.

Theorem 31.9 (GCD recursion theorem)
For any nonnegative integer a and any positive integer b,

gcd(a, b) = gcd(b, a mod b).

Proof      We  will  show  that  gcd(a,  b)  and  gcd(b,  a  mod  b)  divide  each
other. Since they are both nonnegative, equation (31.5) then implies that
they must be equal.

We ﬁrst show that gcd(a, b) | gcd(b, a mod b). If we let d = gcd(a, b),
then d | a and d | b. By equation (3.11) on page 64, a mod b = a – qb,
where q = ⌊a/b⌋. Since a mod b is thus a linear combination of a and b,
equation (31.4) implies that d | (a mod b). Therefore, since d | b and d | (a
mod b), Corollary 31.3 implies that d | gcd(b, a mod b), that is,

Showing  that  gcd(b,  a  mod  b)  |  gcd(a,  b)  is  almost  the  same.  If  we
now let d = gcd(b, a mod b), then d | b and d | (a mod b). Since a = qb +
(a mod b), where q = ⌊a/b⌋, we have that a is a linear combination of b
and (a mod b). By equation (31.4), we conclude that d | a. Since d | b and
d | a, we have that d | gcd(a, b) by Corollary 31.3, so that

Using  equation  (31.5)  to  combine  equations  (31.14)  and  (31.15)
completes the proof.

▪

Euclid’s algorithm

Euclid’s  Elements  (circa  300  B.C.E.)  describes  the  following  gcd
algorithm,  although  its  origin  might  be  even  earlier.  The  recursive
procedure  EUCLID  implements  Euclid’s  algorithm,  based  directly  on
Theorem 31.9. The inputs a and b are arbitrary nonnegative integers.

EUCLID(a, b)

1 if b == 0
2
3 else return EUCLID(b, a mod b)

return a

For example, here is how the procedure computes gcd(30, 21):

EUCLID(30, 21) = EUCLID(21, 9)

= EUCLID(9, 3)
= EUCLID(3, 0)

= 3.

This computation calls EUCLID recursively three times.

The  correctness  of  EUCLID  follows  from  Theorem  31.9  and  the
property that if the algorithm returns a in line 2, then b = 0, so that by
equation (31.9), gcd(a, b) = gcd(a, 0) = a. The algorithm cannot recurse
indeﬁnitely,  since  the  second  argument  strictly  decreases  in  each
recursive  call  and  is  always  nonnegative.  Therefore,  EUCLID  always
terminates with the correct answer.

The running time of Euclid’s algorithm

Let’s analyze the worst-case running time of EUCLID as a function of
the  size  of  a  and  b.  The  overall  running  time  of  EUCLID  is
proportional  to  the  number  of  recursive  calls  it  makes.  The  analysis
assumes  that  a  >  b  ≥  0,  that  is,  the  ﬁrst  argument  is  greater  than  the
second  argument.  Why?  If  b  =  a  >  0,  then  a  mod  b  =  0  and  the
procedure  terminates  after  one  recursive  call.  If  b  >  a  ≥  0,  then  the
procedure makes just one more recursive call than when a > b, because
in  this  case  EUCLID(a,  b)  immediately  makes  the  recursive  call
EUCLID(b, a), and now the ﬁrst argument is greater than the second.

Our  analysis  relies  on  the  Fibonacci  numbers  Fk,  deﬁned  by  the

recurrence equation (3.31) on page 69.

Lemma 31.10
If a > b ≥ 1 and the call EUCLID(a, b) performs k ≥ 1 recursive calls,
then a ≥ Fk+2 and b ≥ Fk+1.

Proof   The proof proceeds by induction on k. For the base case of the
induction, let k = 1. Then, b ≥ 1 = F2, and since a > b, we must have a ≥
2 = F3. Since b > (a mod b), in each recursive call the ﬁrst argument is
strictly  larger  than  the  second.  The  assumption  that  a  >  b  therefore
holds for each recursive call.

Assuming inductively that the lemma holds if the procedure makes k
– 1 recursive calls, we shall prove that the lemma holds for k recursive
calls. Since k > 0, we have b > 0, and EUCLID(a, b) calls EUCLID(b, a

mod  b)  recursively,  which  in  turn  makes  k  –  1  recursive  calls.  The
inductive  hypothesis  then  implies  that  b  ≥  Fk+1  (thus  proving  part  of
the lemma), and a mod b ≥ Fk. We have

b + (a mod b) = b + (a – b ⌊a/b⌋) (by equation (3.11))

≤ a,

since a > b > 0 implies ⌊a/b⌋ ≥ 1. Thus,

a ≥ b + (a mod b)
≥ Fk+1 + Fk
= Fk+2.

▪

The following theorem is an immediate corollary of this lemma.

Theorem 31.11 (Lamé’s theorem)
For  any  integer  k  ≥  1,  if  a  >  b  ≥  1  and  b  <  Fk+1,  then  the  call
EUCLID(a, b) makes fewer than k recursive calls.

▪

To show that the upper bound of Theorem 31.11 is the best possible,
we’ll  show  that  the  call  EUCLID(Fk+1,  Fk)  makes  exactly  k  –  1
recursive calls when k ≥ 2. We use induction on k. For the base case, k =
2,  and  the  call  EUCLID(F3,  F2)  makes  exactly  one  recursive  call,  to
EUCLID(1, 0). (We have to start at  k = 2, because when  k = 1 we do
not  have  F2  >  F1.)  For  the  inductive  step,  assume  that  EUCLID(Fk,
Fk−1) makes exactly k – 2 recursive calls. For k > 2, we have Fk > Fk−1
> 0 and Fk+1 = Fk + Fk−1, and so by Exercise 31.1-1, we have Fk+1
mod  Fk  =  Fk−1.  Because  EUCLID(a,  b)  calls  EUCLID(b,  a  mod  b)
when b > 0, the call EUCLID(Fk+1, Fk) recurses one time more than
the  call  EUCLID(Fk,  Fk−1),  or  exactly  k  –  1  times,  which  meets  the
upper bound given by Theorem 31.11.

Since  Fk  is  approximately

,  where  ϕ  is  the  golden  ratio
  deﬁned  by  equation  (3.32)  on  page  69,  the  number  of
recursive calls in EUCLID is O(1g b). (See Exercise 31.2-5 for a tighter
bound.)  Therefore,  a  call  of  EUCLID  on  two  β-bit  numbers  performs
3)  bit  operations  (assuming  that
O(β)  arithmetic  operations  and  O(β
2) bit operations).
multiplication and division of β-bit numbers take O(β
2) bound on the number of bit
Problem 31-2 asks you to prove an O(β
operations.

The extended form of Euclid’s algorithm

By  rewriting  Euclid’s  algorithm,  we  can  gain  additional  useful
information.  Speciﬁcally,  let’s  extend  the  algorithm  to  compute  the
integer coefﬁcients x and y such that

where  either  or  both  of  x  and  y  may  be  zero  or  negative.  These
coefﬁcients will prove useful later for computing modular multiplicative
inverses. The procedure EXTENDED-EUCLID takes as input a pair of
nonnegative  integers  and  returns  a  triple  of  the  form  (d,  x,  y)  that
satisﬁes equation (31.16). As an example, Figure 31.1 traces out the call
EXTENDED-EUCLID(99, 78).

EXTENDED-EUCLID(a, b)
1 if b == 0
2
3 else (d′, x′, y′) = EXTENDED-EUCLID(b, a mod b)
4

return (a, 1, 0)

(d, x, y) = (d′, y′, x′ – ⌊a/b⌋ y′)
return (d, x, y)

5

The  EXTENDED-EUCLID  procedure

is  a  variation  of  the
EUCLID procedure. Line 1 is equivalent to the test “b == 0” in line 1
of EUCLID. If b = 0, then EXTENDED-EUCLID returns not only d
= a in line 2, but also the coefﬁcients x = 1 and y = 0, so that a = ax +

by. If b ≠ 0, EXTENDED-EUCLID ﬁrst computes (d′, x′, y′) such that
d′ = gcd(b, a mod b) and

As  in  the  EUCLID  procedure,  we  have  d  =  gcd(a,  b)  =  d′  =  gcd(b,  a
mod b). To obtain x and y such that d = ax + by, let’s rewrite equation
(31.17), setting d = d′ and using equation (3.11):

Figure  31.1  How  EXTENDED-EUCLID  computes  gcd(99,  78).  Each  line  shows  one  level  of
the recursion: the values of the inputs a and b, the computed value ⌊a/b⌋, and the values d, x,
and y returned. The triple (d, x, y) returned becomes the triple (d′, x′, y′) used at the next higher
level of recursion. The call EXTENDED-EUCLID(99, 78) returns (3, –11, 14), so that gcd(99,
78) = 3 = 99 · (–11) + 78 · 14.

d = bx′ + (a – b ⌊a/b⌋)y′
= ay′ + b(x′ – ⌊a/b⌋ y′).

Thus, choosing x = y′ and y = x′ – ⌊a/b⌋ y′ satisﬁes the equation d = ax
+ by, thereby proving the correctness of EXTENDED-EUCLID.

Since the number of recursive calls made in EUCLID is equal to the
number of recursive calls made in EXTENDED-EUCLID, the running
times of EUCLID and EXTENDED-EUCLID are the same, to within
a constant factor. That is, for a > b > 0, the number of recursive calls is
O(1g b).

Exercises

31.2-1
Prove that equations (31.11) and (31.12) imply equation (31.13).

31.2-2

Compute the values (d, x, y) that the call EXTENDED-EUCLID(899,
493) returns.

31.2-3
Prove that for all integers a, k, and n,

Use equation (31.18) to show that a = 1 (mod n) implies gcd(a, n) = 1.

31.2-4
Rewrite EUCLID in an iterative form that uses only a constant amount
of memory (that is, stores only a constant number of integer values).

31.2-5
If a > b ≥ 0, show that the call EUCLID (a, b) makes at most 1 + logϕ b
recursive calls. Improve this bound to 1 + logϕ(b/gcd(a, b)).

31.2-6
What  does  EXTENDED-EUCLID(Fk+1,  Fk)  return?  Prove  your
answer correct.

31.2-7
Deﬁne  the  gcd  function  for  more  than  two  arguments  by  the  recursive
equation  gcd(a0,  a1,  …,  an)  =  gcd(a0,  gcd(a1,  a2,  …,  an)).  Show  that
the  gcd  function  returns  the  same  answer  independent  of  the  order  in
which  its  arguments  are  speciﬁed.  Also  show  how  to  ﬁnd  integers  x0,
x1,  …,  xn  such  that  gcd(a0,  a1,  …,  an)  =  a0x0  +  a1x1  +  ⋯  +  anxn.
Show that the number of divisions performed by your algorithm is O(n
+ 1g(max {a0, a1, …, an})).

31.2-8
The least common multiple 1cm(a1, a2, …, an) of integers a1, a2, …, an
is  the  smallest  nonnegative  integer  that  is  a  multiple  of  each  ai.  Show
how to compute 1cm(a1, a2, …, an) efﬁciently using the (two-argument)
gcd operation as a subroutine.

31.2-9
Prove that n1, n2, n3, and n4 are pairwise relatively prime if and only if

gcd(n1n2, n3n4) = gcd(n1n3, n2n4) = 1.

More generally, show that n1, n2, …, nk are pairwise relatively prime if
and  only  if  a  set  of  ⌈1g  k⌉  pairs  of  numbers  derived  from  the  ni  are
relatively prime.

31.3    Modular arithmetic

Informally, you can think of modular arithmetic as arithmetic as usual
over the integers, except that when working modulo n, then every result
x is replaced by the element of {0, 1, …, n – 1} that is equivalent to x,
modulo  n  (so  that  x  is  replaced  by  x  mod  n).  This  informal  model
sufﬁces  if  you  stick  to  the  operations  of  addition,  subtraction,  and
multiplication.  A  more  formal  model  for  modular  arithmetic,  which
follows, is best described within the framework of group theory.

Finite groups

A group (S, ⊕) is a set S together with a binary operation ⊕ deﬁned on
S for which the following properties hold:

1. Closure: For all a, b ∈ S, we have a ⊕ b ∈ S.
2. Identity: There exists an element e ∈ S, called the identity of the

group, such that e ⊕ a = a ⊕ e = a for all a ∈ S.

3. Associativity: For all a, b, c ∈ S, we have (a ⊕ b) ⊕ c = a ⊕ (b ⊕

c).

4. Inverses:  For  each  a  ∈  S,  there  exists  a  unique  element  b  ∈  S,

called the inverse of a, such that a ⊕ b = b ⊕ a = e.

As  an  example,  consider  the  familiar  group  (ℤ,  +)  of  the  integers  ℤ
under the operation of addition: 0 is the identity, and the inverse of a is
–a. An abelian group (S, ⊕) satisﬁes the commutative law a ⊕ b = b ⊕ a

for all a, b ∈ S. The size of group (S, ⊕) is |S|, and if |S| < ∞, then (S,
⊕) is a ﬁnite group.

The groups deﬁned by modular addition and multiplication

We  can  form  two  ﬁnite  abelian  groups  by  using  addition  and
multiplication modulo n, where n is a positive integer. These groups are
based  on  the  equivalence  classes  of  the  integers  modulo  n,  deﬁned  in
Section 31.1.

To deﬁne a group on ℤn, we need suitable binary operations, which
we  obtain  by  redeﬁning  the  ordinary  operations  of  addition  and
multiplication. We can deﬁne addition and multiplication operations for
ℤn,  because  the  equivalence  class  of  two  integers  uniquely  determines
the equivalence class of their sum or product. That is, if a = a′ (mod n)
and b = b′ (mod n), then

a + b = a′ + b′ (mod n),
(mod n).
ab

= a′b′

Thus, we deﬁne addition and multiplication modulo n, denoted +n and
·n, by

(We can deﬁne subtraction similarly on ℤn by [a]n –n [b]n = [a – b]n, but
division  is  more  complicated,  as  we’ll  see.)  These  facts  justify  the
common  and  convenient  practice  of  using  the  smallest  nonnegative
element of each equivalence class as its representative when performing
computations  in  ℤn.  We  add,  subtract,  and  multiply  as  usual  on  the
representatives, but we replace each result x by the representative of its
class, that is, by x mod n.

Figure 31.2 Two ﬁnite groups. Equivalence classes are denoted by their representative elements.
.
(a) The group (ℤ6, +6). (b) The group

Using  this  deﬁnition  of  addition  modulo  n,  we  deﬁne  the  additive
group modulo n as (ℤn, +n). The size of the additive group modulo n is |
ℤn| = n. Figure 31.2(a) gives the operation table for the group (ℤ6, +6).

Theorem 31.12
The system (ℤn, +n) is a ﬁnite abelian group.

Proof   Equation (31.19) shows that (ℤn, +n) is closed. Associativity and
commutativity of +n follow from the associativity and commutativity of
+:

([a]n +n [b]n) +n [c]n = [a + b]n +n [c]n

= [(a + b) + c]n
= [a + (b + c)]n
= [a]n +n [b + c]n
= [a]n +n ([b]n +n [c]n),

[a]n +n [b]n = [a + b]n
= [b + a]n

= [b]n +n [a]n.

The  identity  element  of  (ℤn,  +n)  is  0  (that  is,  [0]n).  The  (additive)
inverse of an element a (that is, of [a]n) is the element –a (that is, [–a]n
or [n – a]n), since [a]n +n [–a]n = [a – a]n = [0]n.

▪
Using  the  deﬁnition  of  multiplication  modulo  n,  we  deﬁne  the
.  The  elements  of  this  group  are
 of elements in ℤn that are relatively prime to n, so that each

multiplicative  group  modulo  n  as
the set
one has a unique inverse, modulo n:

To see that
 is well deﬁned, note that for 0 ≤ a < n, we have a = (a +
kn) (mod n) for all integers k. By Exercise 31.2-3, therefore, gcd(a, n) = 1
implies gcd(a + kn, n) = 1 for all integers k. Since [a]n = {a + kn : k ∈
 is well deﬁned. An example of such a group is
ℤ}, the set

where  the  group  operation  is  multiplication  modulo  15.  (We  have
denoted an element [a]15 as a, and thus, for example, we denote [7]15 as
7.)  Figure  31.2(b)  shows  the  group
.  For  example,  8  ·  11  =  13
(mod 15), working in

. The identity for this group is 1.

Theorem 31.13
The system

 is a ﬁnite abelian group.

Proof      Theorem  31.6  implies  that
  is  closed.  Associativity  and
commutativity can be proved for ·n as they were for +n in the proof of
Theorem  31.12.  The  identity  element  is  [1]n.  To  show  the  existence  of
  and  let  (d,  x,  y)  be  returned  by
inverses,  let  a  be  an  element  of
EXTENDED-EUCLID(a, n). Then we have d = 1, since

, and

or equivalently,

ax = 1 (mod n).

Thus [x]n is a multiplicative inverse of [a]n, modulo n. Furthermore, we
. To see why, equation (31.20) demonstrates that the
claim that
smallest  positive  linear  combination  of  x  and  n  must  be  1.  Therefore,
Theorem  31.2  implies  that  gcd(x,  n)  =  1.  We  defer  the  proof  that
inverses are uniquely deﬁned until Corollary 31.26 in Section 31.4.

▪

As an example of computing multiplicative inverses, suppose that a
= 5 and n = 11. Then EXTENDED-EUCLID(a, n) returns (d, x, y) =
(1,  –2,  1),  so  that  1  =  5  ·  (–2)  +  11  ·  1.  Thus,  [–2]11  (i.e.,  [9]11)  is  the
multiplicative inverse of [5]11.

When working with the groups (ℤn, +n) and

 in the remainder
of  this  chapter,  we  follow  the  convenient  practice  of  denoting
equivalence  classes  by  their  representative  elements  and  denoting  the
operations  +n  and  ·n  by  the  usual  arithmetic  notations  +  and  ·  (or
juxtaposition, so that ab = a · b) respectively. Furthermore, equivalences
modulo n may also be interpreted as equations in ℤn. For example, the
following two statements are equivalent:

ax = b (mod n)

and

[a]n ·n [x]n = [b]n.

As  a  further  convenience,  we  sometimes  refer  to  a  group  (S,  ⊕)
merely as S when the operation ⊕ is understood from context. We may
,
thus  refer  to  the  groups  (ℤn,  +n)  and
respectively.

  as  just  ℤn  and

n).  Division  in

We denote the (multiplicative) inverse of an element a by (a−1 mod
  is  deﬁned  by  the  equation  a/b  =  ab−1  (mod  n).  For
 we have that 7−1 = 13 (mod 15), since 7 · 13 = 91 = 1

example, in
(mod 15), so that 2/7 = 2 · 13 = 11 (mod 15).

The  size  of

  is  denoted  ϕ(n).  This  function,  known  as  Euler’s  phi

function, satisﬁes the equation

so  that  p  runs  over  all  the  primes  dividing  n  (including  n  itself,  if  n  is
prime). We won’t prove this formula here. Intuitively, begin with a list of
the n remainders {0, 1, …, n – 1} and then, for each prime p that divides
n, cross out every multiple of p in the list. For example, since the prime
divisors of 45 are 3 and 5,

If p is prime, then

, and

If n is composite, then ϕ(n) < n – 1, although it can be shown that

for  n  ≥  3,  where  γ  =  0.5772156649  …  is  Euler’s  constant.  A  somewhat
simpler (but looser) lower bound for n > 5 is

The lower bound (31.23) is essentially the best possible, since

Subgroups

If (S, ⊕) is a group, S′ ⊆ S, and (S′, ⊕) is also a group, then (S′, ⊕) is a
subgroup of (S, ⊕). For example, the even integers form a subgroup of
the  integers  under  the  operation  of  addition.  The  following  theorem,
whose  proof  we  leave  as  Exercise  31.3-3,  provides  a  useful  tool  for
recognizing subgroups.

Theorem  31.14  (A  nonempty  closed  subset  of  a  ﬁnite  group  is  a
subgroup)
If (S, ⊕) is a ﬁnite group and S′ is any nonempty subset of S such that a
⊕ b ∈ S′ for all a, b ∈ S′, then (S′, ⊕) is a subgroup of (S, ⊕).

▪

For example, the set {0, 2, 4, 6} forms a subgroup of ℤ8, since it is
nonempty and closed under the operation + (that is, it is closed under
+8).

The  following  theorem,  whose  proof  is  omitted,  provides  an

extremely useful constraint on the size of a subgroup.

Theorem 31.15 (Lagrange’s theorem)
If (S, ⊕) is a ﬁnite group and (S′, ⊕) is a subgroup of (S, ⊕), then |S′| is
a divisor of |S|.

▪

A subgroup S′ of a group S is a proper subgroup if S′ ≠ S. We’ll use
the  following  corollary  in  the  analysis  in  Section  31.8  of  the  Miller-
Rabin primality test procedure.

Corollary 31.16
If S′ is a proper subgroup of a ﬁnite group S, then |S′| ≤ |S|/2.

▪

Subgroups generated by an element

Theorem 31.14 affords us a straightforward way to produce a subgroup
of a ﬁnite group (S, ⊕): choose an element a and take all elements that
can be generated from a using the group operation. Speciﬁcally, deﬁne
a(k) for k ≥ 1 by

For example, taking a = 2 in the group ℤ6 yields the sequence

a(1), a(2), a(3), … = 2, 4, 0, 2, 4, 0, 2, 4, 0, ….
We have a(k) = ka mod n in the group ℤn, and a(k) = ak mod n in the
. We deﬁne the subgroup generated by a, denoted 〈a〉 or (〈a〉, ⊕),
group
by

〈a〉 = {a(k) : k ≥ 1}.

We say that a generates the subgroup 〈a〉 or that a is a generator of 〈a〉.
Since  S  is  ﬁnite,  〈a〉  is  a  ﬁnite  subset  of  S,  possibly  including  all  of  S.
Since the associativity of ⊕ implies
a(i) ⊕ a(j) = a(i+j),
〈a〉  is  closed  and  therefore,  by  Theorem  31.14,  〈a〉  is  a  subgroup  of  S.
For example, in ℤ6, we have

〈0〉 = {0},
〈1〉 = {0, 1, 2, 3, 4, 5},
〈2〉 = {0, 2, 4}.

Similarly, in

, we have

〈1〉 = {1},
〈2〉 = {1, 2, 4},
〈3〉 = {1, 2, 3, 4, 5, 6}.

The  order  of  a  (in  the  group  S),  denoted  ord(a),  is  deﬁned  as  the
smallest  positive  integer  t  such  that  a(t)  =  e.  (Recall  that  e  ∈  S  is  the
group identity.)

Theorem 31.17
For any ﬁnite group (S, ⊕) and any a ∈ S, the order of a is equal to the
size of the subgroup it generates, or ord(a) = |〈a〉|.

Proof   Let t = ord(a). Since a(t) = e and a(t+k) = a(t) ⊕ a(k) = a(k) for
k ≥ 1, if i > t, then a(i) = a(j) for some j < i. Therefore, as we generate
elements by a, we see no new elements after a(t). Thus, 〈a〉 = {a(1), a(2),
…,  a(t)},  and  so  |〈a〉|  ≤  t.  To  show  that  |〈a〉|  ≥  t,  we  show  that  each
element  of  the  sequence  a(1),  a(2),  …,  a(t)  is  distinct.  Suppose  for  the
purpose of contradiction that a(i) = a(j) for some i and j satisfying 1 ≤ i
< j ≤ t. Then, a(i+k) = a(j+k) for k ≥ 0. But this equation implies that
a(i+(t–j)) = a(j+(t–j)) = e, a contradiction, since i + (t – j) < t but t is the
least  positive  value  such  that  a(t)  =  e.  Therefore,  each  element  of  the
sequence  a(1),  a(2),  …,  a(t)  is  distinct,  and  |〈a〉|  ≥  t.  We  conclude  that
ord(a) = |〈a〉|.

▪

Corollary 31.18
The sequence a(1), a(2), … is periodic with period t = ord(a), that is, a(i)
= a(j) if and only if i = j (mod t).

▪
Consistent with the above corollary, we deﬁne a(0) as e and a(i) as a(i

mod t), where t = ord(a), for all integers i.

Corollary 31.19
If (S, ⊕) is a ﬁnite group with identity e, then for all a ∈ S,
a(|S|) = e.

Proof      Lagrange’s  theorem  (Theorem  31.15)  implies  that  ord(a)  |  |S|,
and so |S| = 0 (mod t), where t = ord(a). Therefore, a(|S|) = a(0) = e.

▪

Exercises

31.3-1
Draw  the  group  operation  tables  for  the  groups  (ℤ4,  +4)  and
.
Show  that  these  groups  are  isomorphic  by  exhibiting  a  one-to-one
correspondence f between ℤ4 and
 such that a+b = c (mod 4) if and
only if f(a)·f(b) = f(c) (mod 5).

31.3-2
List all subgroups of ℤ9 and of  art.

31.3-3
Prove Theorem 31.14.

31.3-4
Show that if p is prime and e is a positive integer, then
ϕ(pe) = pe–1(p – 1).
31.3-5
Show  that  for  any  integer  n  >  1  and  for  any  art,  the  function  art
deﬁned by fa(x) = ax mod n is a permutation of

.

31.4    Solving modular linear equations

We now consider the problem of ﬁnding solutions to the equation

where  a  >  0  and  n  >  0.  This  problem  has  several  applications.  For
example, we’ll use it in Section 31.7 as part of the procedure to ﬁnd keys
in  the  RSA  public-key  cryptosystem.  We  assume  that  a,  b,  and  n  are
given,  and  we  wish  to  ﬁnd  all  values  of  x,  modulo  n,  that  satisfy
equation  (31.26).  The  equation  may  have  zero,  one,  or  more  than  one
such solution.

art

Let 〈a〉 denote the subgroup of ℤn generated by a. Since 〈a〉 = {a(x) :
x > 0} = {ax mod n : x > 0}, equation (31.26) has a solution if and only
if [b] ∈ 〈a〉. Lagrange’s theorem (Theorem 31.15) tells us that |〈a〉| must
be  a  divisor  of  n.  The  following  theorem  gives  us  a  precise
characterization of 〈a〉.

Theorem 31.20
For any positive integers a and n, if d = gcd(a, n), then we have

〈a〉 = 〈d〉

= {0, d, 2d, …, ((n/d) – 1)d}

in ℤn, and thus

|〈a〉| = n/d.

Proof      We  begin  by  showing  that  d  ∈  〈a〉.  Recall  that  EXTENDED-
EUCLID(a, n) returns a triple (d, x, y) such that ax + ny = d. Thus, ax
= d (mod n), so that d ∈ 〈a〉. In other words, d is a multiple of a in ℤn.

Since  d  ∈  〈a〉,  it  follows  that  every  multiple  of  d  belongs  to  〈a〉,
because any multiple of a multiple of a is itself a multiple of a. Thus,
〈a〉 contains every element in {0, d, 2d, …, ((n/d) – 1)d}. That is, 〈d〉 ⊆
〈a〉.

We now show that 〈a〉 ⊆ 〈d〉. If m ∈ 〈a〉, then m = ax mod n for some
integer x, and so m = ax + ny for some integer y. Because d = gcd(a, n),
we know that d | a and d | n, and so d | m by equation (31.4). Therefore,
m ∈ 〈d〉.

Combining  these  results,  we  have  that  〈a〉  =  〈d〉.  To  see  that  |〈a〉|  =
n/d, observe that there are exactly n/d multiples of d between 0 and n –
1, inclusive.

▪

Corollary 31.21
The equation ax = b (mod n) is solvable for the unknown x if and only
if d | b, where d = gcd(a, n).

Proof   The equation ax = b (mod n) is solvable if and only if [b] ∈ 〈a〉,
which is the same as saying

(b mod n) ∈ {0, d, 2d, …, ((n/d) – 1)d},
by Theorem 31.20. If 0 ≤ b < n, then b ∈ 〈a〉 if and only if d | b, since
the members of 〈a〉 are precisely the multiples of d. If b < 0 or b ≥ n, the
corollary then follows from the observation that d | b if and only if d | (b
mod n), since b and b mod n differ by a multiple of n, which is itself a
multiple of d.

▪

Corollary 31.22
The equation ax = b (mod n) either has d distinct solutions modulo n,
where d = gcd(a, n), or it has no solutions.

Proof      If  ax  =  b  (mod  n)  has  a  solution,  then  b  ∈  〈a〉.  By  Theorem
31.17, ord(a) = |〈a〉|, and so Corollary 31.18 and Theorem 31.20 imply
that the sequence ai mod n, for i = 0, 1, …, is periodic with period |〈a〉| =
n/d. If b ∈ 〈a〉, then b appears exactly d times in the sequence ai mod n,
for i = 0, 1, …, n – 1, since the length-(n/d) block of values 〈a〉 repeats
exactly  d  times  as  i  increases  from  0  to  n–1.  The  indices  x  of  the  d
positions for which ax mod n = b are the solutions of the equation ax =
b (mod n).

▪

Theorem 31.23
Let  d  =  gcd(a,  n),  and  suppose  that  d  =  ax′  +  ny′  for  some  integers  x′
and y′ (for example, as computed by EXTENDED-EUCLID). If d | b,
then the equation ax = b (mod n) has as one of its solutions the value
x0, where

x0 = x′(b/d) mod n.

Proof   We have

ax0 = ax′(b/d) (mod n)

= d(b/d)
= b

(mod n) (because ax′ = d (mod n))
(mod n),

and thus x0 is a solution to ax = b (mod n).

▪

Theorem 31.24
Suppose  that  the  equation  ax  =  b  (mod  n)  is  solvable  (that  is,  d  |  b,
where d = gcd(a, n)) and that x0 is any solution to this equation. Then,
this equation has exactly d distinct solutions, modulo n, given by xi = x0
+ i(n/d) for i = 0, 1, …, d – 1.

Proof      Because  n/d  >  0  and  0  ≤  i(n/d)  <  n  for  i  =  0,  1,  …,  d  –  1,  the
values x0, x1, …, xd–1 are all distinct, modulo n. Since x0 is a solution
of ax = b (mod n), we have ax0 mod n = b (mod n). Thus, for i = 0, 1,
…, d – 1, we have

axi  mod
n

= a(x0 + in/d) mod n

= (ax0 + ain/d) mod n
= ax0 mod n (because d | a implies that ain/d is a multiple of

n)

= b (mod n),

and  hence  axi  =  b  (mod  n),  making  xi  a  solution,  too.  By  Corollary
31.22, the equation ax = b (mod n) has exactly d solutions, so that x0,
x1, …, xd–1 must be all of them.

▪

We  have  now  developed  the  mathematics  needed  to  solve  the
equation  ax  =  b  (mod  n).  The  procedure  MODULAR-LINEAR-
EQUATION-SOLVER prints all solutions to this equation. The inputs
a and n are arbitrary positive integers, and b is an arbitrary integer.

MODULAR-LINEAR-EQUATION-SOLVER(a, b, n)
1 (d, x′, y′) = EXTENDED-EUCLID(a, n)
2 if d | b
3

x0 = x′(b/d) mod n
for i = 0 to d – 1

4

print (x0 + i(n/d)) mod n

5
6 else print “no solutions”

As  an  example  of  the  operation  of  MODULAR-LINEAR-
EQUATION-SOLVER, consider the equation 14x = 30 (mod 100) (and
thus  a  =  14,  b  =  30,  and  n  =  100).  Calling  EXTENDED-EUCLID  in
line 1 gives (d, x′, y′) = (2, –7, 1). Since 2 | 30, lines 3–5 execute. Line 3
computes x0 = (–7)(15) mod 100 = 95. The for loop of lines 4–5 prints
the two solutions, 95 and 45.

The

procedure  MODULAR-LINEAR-EQUATION-SOLVER
works as follows. The call to EXTENDED-EUCLID in line 1 returns a
triple (d, x′, y′) such that d = gcd(a, n) and d = ax′ + ny′. Therefore, x′ is
a solution to the equation ax′ = d (mod n). If d does not divide b, then
the equation ax = b (mod n) has no solution, by Corollary 31.21. Line 2
checks to see whether d | b, and if not, line 6 reports that there are no
solutions. Otherwise, line 3 computes a solution x0 to ax = b (mod n),
as  Theorem  31.23  suggests.  Given  one  solution,  Theorem  31.24  states
that  adding  multiples  of  (n/d),  modulo  n,  yields  the  other  d  –  1
solutions. The for loop of lines 4–5 prints out all d solutions, beginning
with x0 and spaced n/d apart, modulo n.

MODULAR-LINEAR-EQUATION-SOLVER  performs  O(1g  n  +
since  EXTENDED-EUCLID
gcd(a,  n))  arithmetic  operations,
performs  O(1g  n)  arithmetic  operations,  and  each  iteration  of  the  for
loop of lines 4–5 performs a constant number of arithmetic operations.
The  following  corollaries  of  Theorem  31.24  give  specializations  of

particular interest.

Corollary 31.25

For any n > 1, if gcd(a, n) = 1, then the equation ax = b (mod n) has a
unique solution, modulo n.

▪

If  b  =  1,  a  common  case  of  considerable  interest,  the  x  that  solves

the equation is a multiplicative inverse of a, modulo n.

Corollary 31.26
For any n > 1, if gcd(a, n) = 1, then the equation ax = 1 (mod n) has a
unique solution, modulo n. Otherwise, it has no solution.

▪
Thanks  to  Corollary  31.26,  the  notation  a−1  mod  n  refers  to  the
multiplicative inverse of a, modulo n, when a and n are relatively prime.
If gcd(a, n) = 1, then the unique solution to the equation ax = 1 (mod n)
is the integer x returned by EXTENDED-EUCLID, since the equation

gcd(a, n) = 1 = ax + ny

implies  ax  =  1  (mod  n).  Thus,  EXTENDED-EUCLID  can  compute
a−1 mod n efﬁciently.

Exercises

31.4-1
Find all solutions to the equation 35x = 10 (mod 50).

31.4-2
Prove that the equation ax = ay (mod n) implies x = y (mod n) whenever
gcd(a,  n)  =  1.  Show  that  the  condition  gcd(a,  n)  =  1  is  necessary  by
supplying a counterexample with gcd(a, n) > 1.

31.4-3
Consider the following change to line 3 of the procedure MODULAR-
LINEAR-EQUATION-SOLVER:

3 x0 = x′(b/d) mod (n/d)

With this change, will the procedure still work? Explain why or why not.

★ 31.4-4
Let  p  be  prime  and  f(x)  =  (f0  +  f1x  +  ⋯  +  ftxt)  (mod  p)  be  a
polynomial of degree t, with coefﬁcients fi drawn from ℤp. We say that
a ∈ ℤp is a zero of f if f(a) = 0 (mod p). Prove that if a is a zero of f,
then f(x) = (x – a)g(x) (mod p) for some polynomial g(x) of degree t – 1.
Prove  by  induction  on  t  that  if  p  is  prime,  then  a  polynomial  f(x)  of
degree t can have at most t distinct zeros modulo p.

31.5    The Chinese remainder theorem

Around  100  C.E.,  the  Chinese  mathematician  Sun-Tsŭ  solved  the
problem  of  ﬁnding  those  integers  x  that  leave  remainders  2,  3,  and  2
when  divided  by  3,  5,  and  7  respectively.  One  such  solution  is  x  =  23,
and all solutions are of the form 23+105k for arbitrary integers k. The
“Chinese  remainder  theorem”  provides  a  correspondence  between  a
system  of  equations  modulo  a  set  of  pairwise  relatively  prime  moduli
(for  example,  3,  5,  and  7)  and  an  equation  modulo  their  product  (for
example, 105).

The Chinese remainder theorem has two major applications. Let the
integer n be factored as n = n1n2 ⋯ nk, where the factors ni are pairwise
relatively  prime.  First,  the  Chinese  remainder  theorem  is  a  descriptive
“structure  theorem”  that  describes  the  structure  of  ℤn  as  identical  to
that  of  the  Cartesian  product
art  with  componentwise  addition
and  multiplication  modulo  ni  in  the  ith  component.  Second,  this
description helps in designing efﬁcient algorithms, since working in each
of the systems
art can be more efﬁcient (in terms of bit operations)
than working modulo n.

Theorem 31.27 (Chinese remainder theorem)
Let n = n1n2 ⋯ nk, where the ni are pairwise relatively prime. Consider
the correspondence

where  art, and

ai = a mod ni

for  i  =  1,  2,  …,  k.  Then,  mapping  (31.27)  is  a  one-to-one  mapping
art.  Operations
(bijection)  between  ℤn  and  the  Cartesian  product
performed on the elements of ℤn can be equivalently performed on the
corresponding  k-tuples  by  performing  the  operations  independently  in
each coordinate position in the appropriate system. That is, if

a ↔ (a1, a2, …, ak),
b ↔ (b1, b2, …, bk),

then

art

Proof      Let’s  see  how  to  translate  between  the  two  representations.
Going from a to (a1, a2, …, ak) requires only k “mod” operations. The
reverse—computing a from inputs (a1, a2, …, ak)—is only slightly more
complicated.

We  begin  by  deﬁning  mi  =  n/ni  for  i  =  1,  2,  …,  k.  Thus,  mi  is  the
product of all of the nj’s other than ni: mi = n1n2 ⋯ ni−1ni+1 ⋯ nk. We
next deﬁne

for i = 1, 2, …, k. Equation (31.31) is well deﬁned: since mi and ni are
relatively  prime  (by  Theorem  31.6),  Corollary  31.26  guarantees  that
art mod ni exists. Here is how to compute a as a function of the ai and

ci:

art

art

We now show that equation (31.32) ensures that a = ai (mod ni) for i
= 1, 2, …, k. If j ≠ i, then mj = 0 (mod ni), which implies that cj = mj = 0
(mod ni). Note also that ci = 1 (mod ni), from equation (31.31). We thus
have the appealing and useful correspondence

ci ↔ (0, 0, …, 0, 1, 0, …, 0),

a vector that has 0s everywhere except in the ith coordinate, where it has
a 1. The ci thus form a “basis” for the representation, in a certain sense.
For each i, therefore, we have

art

which is what we wished to show: our method of computing a from the
ai’s produces a result a that satisﬁes the constraints a = ai (mod ni) for i
= 1, 2, …, k. The correspondence is one-to-one, since we can transform
in  both  directions.  Finally,  equations  (31.28)–(31.30)  follow  directly
from Exercise 31.1-7, since x mod ni = (x mod n) mod ni for any x and i
= 1, 2, …, k.

▪

We’ll use the following corollaries later in this chapter.

Corollary 31.28
If n1, n2, …, nk are pairwise relatively prime and n = n1n2 ⋯ nk, then
for any integers a1, a2, …, ak, the set of simultaneous equations

x = ai (mod ni),

for i = 1, 2, …, k, has a unique solution modulo n for the unknown x.

▪

Corollary 31.29
If n1, n2, …, nk are pairwise relatively prime and n = n1n2 ⋯ nk, then
for all integers x and a,

x = a (mod ni)

for i = 1, 2, …, k if and only if

x = a (mod n).

As an example of the application of the Chinese remainder theorem,

suppose that you are given the two equations

▪

a = 2 (mod 5),
a = 3 (mod 13),

so that a1 = 2, n1 = m2 = 5, a2 = 3, and n2 = m1 = 13, and you wish to
compute a mod 65, since n = n1n2 = 65. Because 13−1 = 2 (mod 5) and
5−1 = 8 (mod 13), you compute

c1 = 13 · (2 mod 5) = 26,
c2 = 5 · (8 mod 13) = 40,

and

a = 2 · 26 + 3 · 40 (mod 65)
(mod 65)
(mod 65).

= 52 + 120
= 42

art

Figure 31.3 An illustration of the Chinese remainder theorem for n1 = 5 and n2 = 13. For this
example, c1 = 26 and c2 = 40. In row i, column j is shown the value of a, modulo 65, such that a
mod 5 = i and a mod 13 = j. Note that row 0, column 0 contains a 0. Similarly, row 4, column 12
contains a 64 (equivalent to −1). Since c1 = 26, moving down a row increases a by 26. Similarly,
c2 = 40 means that moving right by a column increases a by 40. Increasing a by 1 corresponds
to moving diagonally downward and to the right, wrapping around from the bottom to the top
and from the right to the left.

See  Figure  31.3  for  an  illustration  of  the  Chinese  remainder  theorem,
modulo 65.

Thus,  you  can  work  modulo  n  by  working  modulo  n  directly  or  by
working  in  the  transformed  representation  using  separate  modulo  ni
computations, as convenient. The computations are entirely equivalent.

Exercises

31.5-1
Find all solutions to the equations x = 4 (mod 5) and x = 5 (mod 11).

31.5-2
Find all integers x that leave remainders 1, 2, and 3 when divided by 9,
8, and 7, respectively.

31.5-3
Argue  that,  under  the  deﬁnitions  of  Theorem  31.27,  if  gcd(a,  n)  =  1,
then

31.5-4
Under the deﬁnitions of Theorem 31.27, prove that for any polynomial
f,  the  number  of  roots  of  the  equation  f(x)  =  0  (mod  n)  equals  the
product of the number of roots of each of the equations f(x) = 0 (mod
n1), f(x) = 0 (mod n2), …, f(x) = 0 (mod nk).

31.6    Powers of an element

Along  with  considering  the  multiples  of  a  given  element  a,  modulo  n,
we often consider the sequence of powers of a, modulo n, where  art:

a0, a1, a2, a3, …,

modulo n. Indexing from 0, the 0th value in this sequence is a0 mod n =
1, and the ith value is ai mod n. For example, the powers of 3 modulo 7
are

art

and the powers of 2 modulo 7 are

art

In this section, let 〈a〉 denote the subgroup of

art generated by a
through  repeated  multiplication,  and  let  ordn(a)  (the  “order  of  a,
art. For example, 〈2〉 = {1, 2,
modulo n”) denote the order of a in
art,  and  ord7(2)  =  3.  Using  the  deﬁnition  of  the  Euler  phi
4}  in
art (see Section 31.3), we now translate
function ϕ(n) as the size of
art to obtain Euler’s theorem
Corollary 31.19 into the notation of
and  specialize  it  to
art,  where  p  is  prime,  to  obtain  Fermat’s
theorem.

Theorem 31.30 (Euler’s theorem)
For any integer n > 1,

art

Theorem 31.31 (Fermat’s theorem)
If p is prime, then

art

Proof   By equation (31.22), ϕ(p) = p – 1 if p is prime.

▪

▪

art, then every element in

Fermat’s  theorem  applies  to  every  element  in  ℤp  except  0,  since
art. For all a ∈ ℤp, however, we have ap = a (mod p) if p is prime.
art is a power of g, modulo n,
If
and g is a primitive root or a generator of
art. For example, 3 is a
primitive  root,  modulo  7,  but  2  is  not  a  primitive  root,  modulo  7.  If
art is cyclic. We omit
the  proof  of  the  following  theorem,  which  is  proven  by  Niven  and
Zuckerman [345].

art possesses a primitive root, the group

Theorem 31.32

The values of n > 1 for which  art is cyclic are 2, 4, pe, and 2pe, for all
primes p > 2 and all positive integers e.

▪

If g is a primitive root of

art,
then  there  exists  a  z  such  that  gz  =  a  (mod  n).  This  z  is  a  discrete
logarithm  or  an  index  of  a,  modulo  n,  to  the  base  g.  We  denote  this
value as indn,g(a).

art and a is any element of

Theorem 31.33 (Discrete logarithm theorem)
If g is a primitive root of  art, then the equation gx = gy (mod n) holds
if and only if the equation x = y (mod ϕ(n)) holds.

Proof   Suppose ﬁrst that x = y (mod ϕ(n)). Then, we have x = y + kϕ(n)
for some integer k, and thus

gx

(mod n)

= gy+kϕ(n)
= gy · (gϕ(n))k (mod n)
= gy · 1k
= gy

(mod n).

(mod n) (by Euler’s theorem)

Conversely,  suppose  that  gx  =  gy  (mod  n).  Because  the  sequence  of
powers  of  g  generates  every  element  of  〈g〉  and  |〈g〉|  =  ϕ(n),  Corollary
31.18  implies  that  the  sequence  of  powers  of  g  is  periodic  with  period
ϕ(n). Therefore, if gx = gy (mod n), we must have x = y (mod ϕ(n)).

▪

Let’s  now  turn  our  attention  to  the  square  roots  of  1,  modulo  a
prime  power.  The  following  properties  will  be  useful  to  justify  the
primality-testing algorithm in Section 31.8.

Theorem 31.34
If p is an odd prime and e ≥ 1, then the equation

has only two solutions, namely x = 1 and x = −1.

Proof   By Exercise 31.6-2, equation (31.33) is equivalent to

pe | (x − 1)(x + 1).

Since  p  >  2,  we  can  have  p  |  (x  −  1)  or  p  |  (x  +  1),  but  not  both.
(Otherwise, by property (31.3), p would also divide their difference (x +
1) – (x − 1) = 2.) If p ∤ (x – 1), then gcd(pe, x − 1) = 1, and by Corollary
31.5,  we  would  have  pe  |  (x  +  1).  That  is,  x  =  −1  (mod  pe).
Symmetrically, if p ∤ (x + 1), then gcd(pe, x + 1) = 1, and Corollary 31.5
implies that pe | (x − 1), so that x = 1 (mod pe). Therefore, either x = −1
(mod pe) or x = 1 (mod pe).

▪

A number x is a nontrivial square root of 1, modulo n, if it satisﬁes the
equation  x2  =  1  (mod  n)  but  x  is  equivalent  to  neither  of  the  two
“trivial” square roots: 1 or −1, modulo n. For example, 6 is a nontrivial
square  root  of  1,  modulo  35.  We’ll  use  the  following  corollary  to
Theorem  31.34  in  Section  31.8  to  prove  the  Miller-Rabin  primality-
testing procedure correct.

Corollary 31.35
If  there  exists  a  nontrivial  square  root  of  1,  modulo  n,  then  n  is
composite.

Proof      By  the  contrapositive  of  Theorem  31.34,  if  there  exists  a
nontrivial square root of 1, modulo n, then n cannot be an odd prime or
a  power  of  an  odd  prime.  Nor  can  n  be  2,  because  if  x2  =  1  (mod  2),
then x = 1 (mod 2), and therefore, all square roots of 1, modulo 2, are
trivial.  Thus,  n  cannot  be  prime.  Finally,  we  must  have  n  >  1  for  a
nontrivial square root of 1 to exist. Therefore, n must be composite.

▪

Raising to powers with repeated squaring

A  frequently  occurring  operation  in  number-theoretic  computations  is
raising one number to a power modulo another number, also known as
modular  exponentiation.  More  precisely,  we  would  like  an  efﬁcient  way
to compute ab mod n, where a and b are nonnegative integers and n is a
positive  integer.  Modular  exponentiation  is  an  essential  operation  in
many  primality-testing
the  RSA  public-key
cryptosystem.  The  method  of  repeated  squaring  solves  this  problem
efﬁciently.

routines  and

in

Repeated squaring is based on the following formula to compute ab

for nonnegative integers a and b:

art

The  last  case,  where  b  is  odd,  reduces  to  the  one  of  the  ﬁrst  two
cases,  since  if  b  is  odd,  then  b  −  1  is  even.  The  recursive  procedure
MODULAR-EXPONENTIATION on the next page computes ab mod
n  using  equation  (31.34),  but  performing  all  computations  modulo  n.
The  term  “repeated  squaring”  comes  from  squaring  the  intermediate
result d = ab/2 in line 5. Figure 31.4 shows the values of the parameter
b,  the  local  variable  d,  and  the  value  returned  at  each  level  of  the
recursion  for  the  call  MODULAR-EXPONENTIATION(7,560,561),
which returns the result 1.

art

Figure  31.4  The  values  of  the  parameter  b,  the  local  variable  d,  and  the  value  returned  for
recursive calls of MODULAR-EXPONENTIATION with parameter values a = 7, b = 560, and
n = 561. The value returned by each recursive call is assigned directly to d. The result of the call
with a = 7, b = 560, and n = 561 is 1.

MODULAR-EXPONENTIATION(a, b, n)
1 if b == 0
2
3 elseif b mod 2 == 0

return 1

4

d  =  MODULAR-EXPONENTIATION(a,  b/2,

n)

return (d · d) mod n

5
6 else d = MODULAR-EXPONENTIATION(a, b −

is

is

//  b
even

//  b
odd

1, n)

7

return (a · d) mod n

The total number of recursive calls depends on the number of bits of
b  and  the  values  of  these  bits.  Assume  that  b  >  0  and  that  the  most
signiﬁcant bit of b is a 1. Each 0 generates one recursive call (in line 4),
and each 1 generates two recursive calls (one in line 6 followed by one in
line 4 because if b is odd, then b − 1 is even). If the inputs a, b, and n
are  β-bit  numbers,  then  there  are  between  β  and  2β  −  1  recursive  calls
altogether,  the  total  number  of  arithmetic  operations  required  is  O(β),
and the total number of bit operations required is O(β

3).

Exercises

31.6-1
art.  Pick  the
Draw  a  table  showing  the  order  of  every  element  in
smallest  primitive  root  g  and  compute  a  table  giving  ind11,g(x)  for  all

art.

31.6-2
Show that x2 = 1 (mod pe) is equivalent to pe | (x − 1)(x + 1).

31.6-3
Rewrite the third case of MODULAR-EXPONENTIATION, where b
is odd, so that if b has β bits and the most signiﬁcant bit is 1, then there
are always exactly β recursive calls.

31.6-4
Give  a  nonrecursive
EXPONENTIATION.

31.6-5

(i.e.,

iterative)  version  of  MODULAR-

Assuming that you know ϕ(n), explain how to compute a−1 mod n for
any  art using the procedure MODULAR-EXPONENTIATION.

31.7    The RSA public-key cryptosystem

With a public-key cryptosystem, you can encrypt messages sent between
two communicating parties so that an eavesdropper who overhears the
encrypted  messages  will  not  be  able  to  decode,  or  decrypt,  them.  A
public-key cryptosystem also enables a party to append an unforgeable
“digital signature” to the end of an electronic message. Such a signature
is  the  electronic  version  of  a  handwritten  signature  on  a  paper
document.  It  can  be  easily  checked  by  anyone,  forged  by  no  one,  yet
loses its validity if any bit of the message is altered. It therefore provides
authentication of both the identity of the signer and the contents of the
signed  message.  It  is  the  perfect  tool  for  electronically  signed  business
contracts,  electronic  checks,  electronic  purchase  orders,  and  other
electronic communications that parties wish to authenticate.

The  RSA  public-key  cryptosystem  relies  on  the  dramatic  difference
between  the  ease  of  ﬁnding  large  prime  numbers  and  the  difﬁculty  of
factoring  the  product  of  two  large  prime  numbers.  Section  31.8
describes an efﬁcient procedure for ﬁnding large prime numbers.

Public-key cryptosystems

In  a  public-key  cryptosystem,  each  participant  has  both  a  public  key
and a secret key. Each key is a piece of information. For example, in the
RSA  cryptosystem,  each  key  consists  of  a  pair  of  integers.  The
participants  “Alice”  and  “Bob”  are  traditionally  used  in  cryptography
examples. We denote the public keys for Alice and Bob as PA and PB,
respectively,  and  likewise  the  secret  keys  are  SA  for  Alice  and  SB  for
Bob.

Each participant creates his or her own public and secret keys. Secret
keys are kept secret, but public keys can be revealed to anyone or even
published.  In  fact,  it  is  often  convenient  to  assume  that  everyone’s

public key is available in a public directory, so that any participant can
easily obtain the public key of any other participant.

art

Figure 31.5 Encryption in a public key system. Bob encrypts the message M using Alice’s public
key  PA  and  transmits  the  resulting  ciphertext  C  =  PA(M)  over  a  communication  channel  to
Alice. An eavesdropper who captures the transmitted ciphertext gains no information about M.
Alice receives C and decrypts it using her secret key to obtain the original message M = SA(C).

The  public  and  secret  keys  specify  functions  that  can  be  applied  to
any  message.  Let  D  denote  the  set  of  permissible  messages.  For
example,  D  might  be  the  set  of  all  ﬁnite-length  bit  sequences.  The
simplest, and original, formulation of public-key cryptography requires
one-to-one  functions  from  D  to  itself,  based  on  the  public  and  secret
keys.  We  denote  the  function  based  on  Alice’s  public  key  PA  by  PA()
and  the  function  based  on  her  secret  key  SA  by  SA().  The  functions
PA()  and  SA()  are  thus  permutations  of  D.  We  assume  that  the
functions  PA()  and  SA()  are  efﬁciently  computable  given  the
corresponding keys PA and SA.

The public and secret keys for any participant are a “matched pair”

in that they specify functions that are inverses of each other. That is,

art

for any message M ∈ D. Transforming M with the two keys PA and SA
successively, in either order, yields back the original message M.

A  public-key  cryptosystem  requires  that  Alice,  and  only  Alice,  be
able to compute the function SA() in any practical amount of time. This
assumption  is  crucial  to  keeping  encrypted  messages  sent  to  Alice
private  and  to  knowing  that  Alice’s  digital  signatures  are  authentic.
Alice  must  keep  her  key  SA  secret.  If  she  does  not,  whoever  else  has
access to SA can decrypt messages intended only for Alice and can also
forge  her  digital  signature.  The  assumption  that  only  Alice  can
reasonably  compute  SA()  must  hold  even  though  everyone  knows  PA

and  can  compute  PA(),  the  inverse  function  to  SA(),  efﬁciently.  These
requirements appear formidable, but we’ll see how to satisfy them.

In a public-key cryptosystem, encryption works as shown in Figure
31.5. Suppose that Bob wishes to send Alice a message M encrypted so
that it looks like

Figure 31.6 Digital signatures in a public-key system. Alice signs the message M′ by appending
her digital signature σ = SA(M′) to it. She transmits the message/signature pair (M′, σ) to Bob,
who veriﬁes it by checking the equation M′ = PA(σ). If the equation holds, he accepts (M′, σ) as
a message that Alice has signed.

unintelligible gibberish to an eavesdropper. The scenario for sending the
message goes as follows.

Bob  obtains  Alice’s  public  key  PA,  perhaps  from  a  public
directory or perhaps directly from Alice.
Bob  computes  the  ciphertext  C  =  PA(M)  corresponding  to  the
message M and sends C to Alice.

When  Alice  receives  the  ciphertext  C,  she  applies  her  secret  key
SA to retrieve the original message: SA(C) = SA(PA(M)) = M.

Because  SA()  and  PA()  are  inverse  functions,  Alice  can  compute  M
from  C.  Because  only  Alice  is  able  to  compute  SA(),  only  Alice  can
compute  M  from  C.  Because  Bob  encrypts  M  using  PA(),  only  Alice
can understand the transmitted message.

Digital  signatures  can  be  implemented  within  this  formulation  of  a
public-key  cryptosystem.  (There  are  other  ways  to  construct  digital
signatures,  but  we  won’t  go  into  them  here.)  Suppose  now  that  Alice

wishes  to  send  Bob  a  digitally  signed  response  M′.  Figure  31.6  shows
how the digital-signature scenario proceeds.

Alice  computes  her  digital  signature  σ  for  the  message  M′  using
her secret key SA and the equation σ = SA(M′).
Alice sends the message/signature pair (M′, σ) to Bob.
When  Bob  receives  (M′,  σ),  he  can  verify  that  it  originated  from
Alice  by  using  Alice’s  public  key  to  verify  the  equation  M′  =
PA(σ). (Presumably, M′ contains Alice’s name, so that Bob knows
whose  public  key  to  use.)  If  the  equation  holds,  then  Bob
concludes that the message M′ was actually signed by Alice. If the
equation fails to hold, Bob concludes either that the information
he received was corrupted by transmission errors or that the pair
(M′, σ) is an attempted forgery.

Because a digital signature provides both authentication of the signer’s
identity and authentication of the contents of the signed message, it is
analogous to a handwritten signature at the end of a written document.
A  digital  signature  must  be  veriﬁable  by  anyone  who  has  access  to
the  signer’s  public  key.  A  signed  message  can  be  veriﬁed  by  one  party
and  then  passed  on  to  other  parties  who  can  also  verify  the  signature.
For  example,  the  message  might  be  an  electronic  check  from  Alice  to
Bob.  After  Bob  veriﬁes  Alice’s  signature  on  the  check,  he  can  give  the
check to his bank, who can then also verify the signature and effect the
appropriate funds transfer.

A signed message may or may not be encrypted. The message can be
“in  the  clear”  and  not  protected  from  disclosure.  By  composing  the
above  protocols  for  encryption  and  for  signatures,  Alice  can  create  a
message  to  Bob  that  is  both  signed  and  encrypted.  Alice  ﬁrst  appends
her  digital  signature  to  the  message  and  then  encrypts  the  resulting
message/signature pair with Bob’s public key. Bob decrypts the received
message with his secret key to obtain both the original message and its
digital signature. Bob can then verify the signature using Alice’s public
key.  The  corresponding  combined  process  using  paper-based  systems

would be to sign the paper document and then seal the document inside
a paper envelope that is opened only by the intended recipient.

The RSA cryptosystem

In  the  RSA  public-key  cryptosystem,  a  participant  creates  a  public  key
and a secret key with the following procedure:

1. Select at random two large prime numbers p and q such that p ≠

q. The primes p and q might be, say, 1024 bits each.

2. Compute n = pq.

3. Select  a  small  odd  integer  e  that  is  relatively  prime  to  ϕ(n),

which, by equation (31.21), equals (p – 1)(q – 1).

4. Compute  d  as  the  multiplicative  inverse  of  e,  modulo  ϕ(n).
(Corollary 31.26 guarantees that d exists and is uniquely deﬁned.
You can use the technique of Section 31.4 to compute d, given e
and ϕ(n).)

5. Publish the pair P = (e, n) as the participant’s RSA public key.

6. Keep  secret  the  pair  S  =  (d,  n)  as  the  participant’s  RSA  secret

key.

For this scheme, the domain D is the set ℤn. To transform a message

M associated with a public key P = (e, n), compute

art

To  transform  a  ciphertext  C  associated  with  a  secret  key  S  =  (d,  n),
compute

These  equations  apply  to  both  encryption  and  signatures.  To  create  a
signature, the signer’s secret key is applied to the message to be signed,
rather than to a ciphertext. To verify a signature, the public key of the
signer  is  applied  to  the  signature  rather  than  to  a  message  to  be
encrypted.

art

To  implement  the  public-key  and  secret-key  operations  (31.37)  and
(31.38), you can use the procedure MODULAR-EXPONENTIATION
described  in  Section  31.6.  To  analyze  the  running  time  of  these
operations, assume that the public key (e, n) and secret key (d, n) satisfy
1g e = O(1), 1g d ≤ β, and 1g n ≤ β. Then, applying a public key requires
2) bit operations. Applying a
O(1) modular multiplications and uses O(β
3)  bit
secret  key  requires  O(β)  modular  multiplications,  using  O(β
operations.

Theorem 31.36 (Correctness of RSA)
The  RSA  equations  (31.37)  and  (31.38)  deﬁne  inverse  transformations
of ℤn satisfying equations (31.35) and (31.36).

Proof   From equations (31.37) and (31.38), we have that for any M ∈
ℤn,

P(S(M)) = S(P(M)) = Med (mod n).

Since e and d are multiplicative inverses modulo ϕ(n) = (p – 1)(q – 1),
ed = 1 + k(p – 1)(q – 1)

for some integer k. But then, if M ≠ 0 (mod p), we have

Med = M(Mp–1)k(q–1)

(mod p)

= M((M mod p)p–1)k(q–1) (mod p)
= M(1)k(q–1)
= M

(mod p)

(mod p) (by Theorem 31.31)

Also, Med = M (mod p) if M = 0 (mod p). Thus,

Med = M (mod p)

for all M. Similarly,

Med = M (mod q)

for all M. Thus, by Corollary 31.29 to the Chinese remainder theorem,

Med = M (mod n)

for all M.

▪

The  security  of  the  RSA  cryptosystem  rests  in  large  part  on  the
difﬁculty  of  factoring  large  integers.  If  an  adversary  can  factor  the
modulus n in a public key, then the adversary can derive the secret key
from the public key, using the knowledge of the factors p and q in the
same  way  that  the  creator  of  the  public  key  used  them.  Therefore,  if
factoring large integers is easy, then breaking the RSA cryptosystem is
easy.  The  converse  statement,  that  if  factoring  large  integers  is  hard,
then breaking RSA is hard, is unproven. After two decades of research,
however, no easier method has been found to break the RSA public-key
cryptosystem than to factor the modulus n. And factoring large integers
is surprisingly difﬁcult. By randomly selecting and multiplying together
two  1024-bit  primes,  you  can  create  a  public  key  that  cannot  be
“broken” in any feasible amount of time with current technology. In the
absence  of  a  fundamental  breakthrough  in  the  design  of  number-
theoretic  algorithms,  and  when  implemented  with  care  following
recommended standards, the RSA cryptosystem is capable of providing
a high degree of security in applications.

In  order  to  achieve  security  with  the  RSA  cryptosystem,  however,
you  should  use  integers  that  are  quite  long—more  than  1000  bits—to
resist possible advances in the art of factoring. In 2021, RSA moduli are
commonly in the range of 2048 to 4096 bits. To create moduli of such
sizes, you must ﬁnd large primes efﬁciently. Section 31.8 addresses this
problem.

For  efﬁciency,  RSA

in  a  “hybrid”  or  “key-
is  often  used
management”  mode  with  fast  cryptosystems  that  are  not  public-key
cryptosystems.  With  such  a  symmetric-key  system,  the  encryption  and
decryption keys are identical. If Alice wishes to send a long message M
to Bob privately, she selects a random key K for the fast symmetric-key
cryptosystem and encrypts M using K, obtaining ciphertext C, where C
is as long as M, but K is quite short. Then she encrypts K using Bob’s

public RSA key. Since K is short, computing PB(K) is fast (much faster
than  computing  PB(M)).  She  then  transmits  (C,  PB(K))  to  Bob,  who
decrypts PB(K) to obtain K and then uses K to decrypt C, obtaining M.
A  similar  hybrid  approach  creates  digital  signatures  efﬁciently.  This
approach combines RSA with a public collision-resistant hash function h
—a function that is easy to compute but for which it is computationally
infeasible to ﬁnd two messages M and M′ such that h(M) = h(M′). The
value  h(M)  is  a  short  (say,  256-bit)  “ﬁngerprint”  of  the  message  M.  If
Alice wishes to sign a message M, she ﬁrst applies h to M to obtain the
ﬁngerprint h(M), which she then encrypts with her secret key. She sends
(M, SA(h(M))) to Bob as her signed version of M. Bob can verify the
signature  by  computing  h(M)  and  verifying  that  PA  applied  to
SA(h(M))  as  received  equals  h(M).  Because  no  one  can  create  two
messages  with  the  same  ﬁngerprint,  it  is  computationally  infeasible  to
alter a signed message and preserve the validity of the signature.

One  way  to  distribute  public  keys  uses  certiﬁcates.  For  example,
assume that there is a “trusted authority” T whose public key is known
by everyone. Alice can obtain from T a signed message (her certiﬁcate)
stating  that  “Alice’s  public  key  is  PA.”  This  certiﬁcate  is  “self-
authenticating”  since  everyone  knows  PT.  Alice  can  include  her
certiﬁcate  with  her  signed  messages,  so  that  the  recipient  has  Alice’s
public  key  immediately  available  in  order  to  verify  her  signature.
Because her key was signed by T, the recipient knows that Alice’s key is
really Alice’s.

Exercises

31.7-1
Consider an RSA key set with p = 11, q = 29, n = 319, and e = 3. What
value of d should be used in the secret key? What is the encryption of
the message M = 100?

31.7-2

Prove  that  if  Alice’s  public  exponent  e  is  3  and  an  adversary  obtains
Alice’s  secret  exponent  d,  where  0  <  d  <  ϕ(n),  then  the  adversary  can
factor Alice’s modulus n in time polynomial in the number of bits in n.
(Although  you  are  not  asked  to  prove  it,  you  might  be  interested  to
know  that  this  result  remains  true  even  if  the  condition  e  =  3  is
removed. See Miller [327].)

★ 31.7-3
Prove that RSA is multiplicative in the sense that

PA(M1)PA(M2) = PA(M1M2) (mod n).

Use  this  fact  to  prove  that  if  an  adversary  had  a  procedure  that  could
efﬁciently decrypt 1% of messages from ℤn encrypted with PA, then the
adversary  could  employ  a  probabilistic  algorithm  to  decrypt  every
message encrypted with PA with high probability.

★ 31.8    Primality testing

This section shows how to ﬁnd large primes. We begin with a discussion
of  the  density  of  primes,  proceed  to  examine  a  plausible,  but
incomplete, approach to primality testing, and then present an effective
randomized primality test due to Miller and Rabin.

The density of prime numbers

Many  applications,  such  as  cryptography,  call  for  ﬁnding  large
“random” primes. Fortunately, large primes are not too rare, so that it is
feasible  to  test  random  integers  of  the  appropriate  size  until  you  ﬁnd
one  that  is  prime.  The  prime  distribution  function  π(n)  speciﬁes  the
number of primes that are less than or equal to n. For example, π(10) =
4, since there are 4 prime numbers less than or equal to 10, namely, 2, 3,
5,  and  7.  The  prime  number  theorem  gives  a  useful  approximation  to
π(n).

Theorem 31.37 (Prime number theorem)

art

▪

The approximation n/ln n gives reasonably accurate estimates of π(n)
even for small n. For example, it is off by less than 6% at n = 109, where
π(n) = 50,847,534 and n/ln n ≈ 48,254,942. (To a number theorist, 109 is
a small number.)

The  process  of  randomly  selecting  an  integer  n  and  determining
whether  it  is  prime  is  really  just  a  Bernoulli  trial  (see  Section  C.4).  By
the  prime  number  theorem,  the  probability  of  a  success—that  is,  the
probability  that  n  is  prime—is  approximately  1/ln  n.  The  geometric
distribution says how many trials must occur to obtain a success, and by
equation  (C.36)  on  page  1197,  the  expected  number  of  trials  is
approximately  ln  n.  Thus,  in  order  to  ﬁnd  a  prime  that  has  the  same
length  as  n  by  testing  integers  chosen  randomly  near  n,  the  expected
number  examined  would  be  approximately  ln  n.  For  example,  the
expectation  is  that  ﬁnding  a  1024-bit  prime  would  require  testing
approximately  ln  21024  ≈  710  randomly  chosen  1024-bit  numbers  for
primality.  (Of  course,  to  cut  this  ﬁgure  in  half,  choose  only  odd
integers.)

The  remainder  of  this  section  shows  how  to  determine  whether  a
large odd integer n is prime. For notational convenience, we assume that
n has the prime factorization

art

where r ≥ 1, p1, p2, …, pr are the prime factors of n, and e1, e2, …, er
are positive integers. The integer n is prime if and only if r = 1 and e1 =
1.

One simple approach to the problem of testing for primality is trial
art, skipping
division: try dividing n by each integer 2, 3, 5, 7, 9, …,
even integers greater than 2. We can conclude that n is prime if and only
if none of the trial divisors divides n. Assuming that each trial division
art,  which  is
takes  constant  time,  the  worst-case  running  time  is
exponential  in  the  length  of  n.  (Recall  that  if  n  is  encoded  in  binary

art.) Thus, trial division
using β bits, then β = ⌈1g(n + 1)⌉, and so
works  well  only  if  n  is  very  small  or  happens  to  have  a  small  prime
factor. When it works, trial division has the advantage that it not only
determines  whether  n  is  prime  or  composite,  it  also  determines  one  of
n’s prime factors if n is composite.

This  section  focuses  on  ﬁnding  out  whether  a  given  number  n  is
prime.  If  n  is  composite,  we  won’t  worry  about  ﬁnding  its  prime
factorization.  Computing  the  prime  factorization  of  a  number  is
computationally expensive. You might be surprised that it turns out to
be much easier to ascertain whether a given number is prime than it is
to determine the prime factorization of the number if it is not prime.

Pseudoprimality testing

We’ll start with a method for primality testing that “almost works” and,
in fact, is good enough for many practical applications. Later on, we’ll
reﬁne  this  method  to  remove  the  small  defect.  Let
  denote  the
nonzero elements of ℤn:

art

If n is prime, then  art.

We say that n is a base-a pseudoprime if n is composite and

art

Fermat’s  theorem  (Theorem  31.31  on  page  932)  implies  that  if  n  is
prime, then n satisﬁes equation (31.39) for every a in  art. Thus, if there
is  any
art  such  that  n  does  not  satisfy  equation  (31.39),  then  n  is
certainly composite. Surprisingly, the converse almost holds, so that this
criterion  forms  an  almost  perfect  test  for  primality.  Instead  of  trying
every value of  art, test to see whether n satisﬁes equation (31.39) for
just  a  =  2.  If  not,  then  declare  n  to  be  composite  by  returning
COMPOSITE.  Otherwise,  return  PRIME,  guessing  that  n  is  prime
(when,  in  fact,  all  we  know  is  that  n  is  either  prime  or  a  base-2
pseudoprime).

The  procedure  PSEUDOPRIME  on  the  next  page  pretends  in  this
manner to check whether n is prime. It uses the procedure MODULAR-

EXPONENTIATION from Section 31.6. It assumes that the input n is
an odd integer greater than 2. This procedure can make errors, but only
of  one  type.  That  is,  if  it  says  that  n  is  composite,  then  it  is  always
correct. If it says that n is prime, however, then it makes an error only if
n is a base-2 pseudoprime.

How often does PSEUDOPRIME err? Surprisingly rarely. There are
only  22  values  of  n  less  than  10,000  for  which  it  errs,  the  ﬁrst  four  of
which are 341, 561, 645,

PSEUDOPRIME(n)
1 if MODULAR-EXPONENTIATION(2, n – 1, n) ≠ 1 (mod n)
2
3 else return PRIME

// deﬁnitely
// we hope!

return COMPOSITE

and  1105.  We  won’t  prove  it,  but  the  probability  that  this  program
makes  an  error  on  a  randomly  chosen  β-bit  number  goes  to  0  as  β
approaches ∞. Using more precise estimates due to Pomerance [361] of
the number of base-2 pseudoprimes of a given size, a randomly chosen
512-bit number that is called prime by PSEUDOPRIME has less than
one  chance  in  1020  of  being  a  base-2  pseudoprime,  and  a  randomly
chosen 1024-bit number that is called prime has less than one chance in
1041 of being a base-2 pseudoprime. Thus, if you are merely trying to
ﬁnd  a  large  prime  for  some  application,  for  all  practical  purposes  you
almost never go wrong by choosing large numbers at random until one
of  them  causes  PSEUDOPRIME  to  return  PRIME.  But  when  the
numbers being tested for primality are not randomly chosen, you might
need  a  better  approach  for  testing  primality.  As  we’ll  see,  a  little  more
cleverness,  and  some  randomization,  will  yield  a  primality-testing
method that works well on all inputs.

Since PSEUDOPRIME checks equation (31.39) for only a = 2, you
might  think  that  you  could  eliminate  all  the  errors  by  simply  checking
equation  (31.39)  for  a  second  base  number,  say  a  =  3.  Better  yet,  you
could check equation (31.39) for even more values of a. Unfortunately,
even  checking  for  several  values  of  a  does  not  eliminate  all  errors,

because there exist composite integers n, known as Carmichael numbers,
art.  (The  equation  does  fail
that  satisfy  equation  (31.39)  for  all
when gcd(a, n) > 1—that is, when
art—but demonstrating that n is
composite by ﬁnding such an a can be difﬁcult if n has only large prime
factors.)  The  ﬁrst  three  Carmichael  numbers  are  561,  1105,  and  1729.
Carmichael numbers are extremely rare. For example, only 255 of them
are less than 100,000,000. Exercise 31.8-2 helps explain why they are so
rare.

Let’s  see  how  to  improve  the  primality  test  so  that  Carmichael

numbers won’t fool it.

The Miller-Rabin randomized primality test

The  Miller-Rabin  primality  test  overcomes  the  problems  of  the  simple
procedure PSEUDOPRIME with two modiﬁcations:

It tries several randomly chosen base values a instead of just one
base value.

While  computing  each  modular  exponentiation,  it  looks  for  a
nontrivial  square  root  of  1,  modulo  n,  during  the  ﬁnal  set  of
squarings.  If  it  ﬁnds  one,  it  stops  and  returns  COMPOSITE.
Corollary 31.35 from Section 31.6 justiﬁes detecting composites in
this manner.

The  pseudocode  for  the  Miller-Rabin  primality  test  appears  in  the
procedures  MILLER-RABIN  and  WITNESS.  The  input  n  >  2  to
MILLER-RABIN is the odd number to be tested for primality, and s is
the  number  of  randomly  chosen  base  values  from
art  to  be  tried.
The code uses the random-number generator RANDOM described on
page  129:  RANDOM(2,  n  –  2)  returns  a  randomly  chosen  integer  a
satisfying 2 ≤ a ≤ n – 2. (This range of values avoids having a = ≥1 (mod
n).) The call of the auxiliary procedure WITNESS(a, n) returns TRUE
if and only if a is a “witness” to the compositeness of n—that is, if it is
possible  using  a  to  prove  (in  a  manner  that  we  will  see)  that  n  is
composite.  The  test  WITNESS(a,  n)  is  an  extension  of,  but  more
effective  than,  the  test  in  equation  (31.39)  that  formed  the  basis  for
PSEUDOPRIME, using a = 2.

Let’s ﬁrst understand how WITNESS works, and then we’ll see how
the Miller-Rabin primality test uses it. Let n – 1 = 2tu where t ≥ 1 and u
is  odd.  That  is,  the  binary  representation  of  n  –  1  is  the  binary
representation  of  the  odd  integer  u  followed  by  exactly  t  zeros.
art, so that one way to compute an−1 mod n is to ﬁrst

Therefore,
compute au mod n and then square the result t times successively.

MILLER-RABIN(n, s)
1 for j = 1 to s
2

a = RANDOM(2, n – 2)
if WITNESS(a, n)

3

// n > 2 is odd

return COMPOSITE// deﬁnitely

4
5 return PRIME

// almost surely

WITNESS(a, n)
1 let t and u be such that t ≥ 1, u is odd, and n – 1 = 2tu
2 x0 = MODULAR-EXPONENTIATION(a, u, n)
3 for i = 1 to t
4

art
if xi == 1 and xi–1 ≠ 1 and xi–1 ≠ n – 1

5

6

return TRUE

//  found  a  nontrivial  square  root
of 1

7 if xt ≠ 1
8

return TRUE

9 return FALSE

composite,
//
PSEUDOPRIME

as

in

This  pseudocode  for  WITNESS  computes  an–1  mod  n  by  ﬁrst
computing  the  value  x0  =  au  mod  n  in  line  2  and  then  repeatedly
squaring the result t times in the for loop of lines 3–6. By induction on i,
the  sequence  x0,  x1,  …,  xt  of  values  computed  satisﬁes  the  equation
art for i = 0, 1, …, t, so that in particular xt = an–1 (mod n). After

line 4 performs a squaring step, however, the loop will terminate early if
lines  5–6  detect  that  a  nontrivial  square  root  of  1  has  just  been
discovered. (We’ll explain these tests shortly.) If so, the procedure stops
and returns TRUE. Lines 7–8 return TRUE if the value computed for
xt  =  an–1  (mod  n)  is  not  equal  to  1,  just  as  the  PSEUDOPRIME
procedure  returns  COMPOSITE  in  this  case.  Line  9  returns  FALSE  if
lines 6 or 8 have not returned TRUE.

The following lemma proves the correctness of WITNESS.

Lemma 31.38
If WITNESS(a, n) returns TRUE, then a proof that n is composite can
be constructed using a as a witness.

Proof      If  WITNESS  returns  TRUE  from  line  8,  it’s  because  line  7
determined that xt = an–1 mod n ≠ 1. If n is prime, however, Fermat’s
theorem (Theorem 31.31) says that an–1 = 1 (mod n) for all  art. Since
art if n is prime, Fermat’s theorem also says that an–1 = 1 (mod n) for
all  art. Therefore, n cannot be prime, and the equation an–1 mod n ≠ 1
proves this fact.

If WITNESS returns TRUE from line 6, then it has discovered that
xi–1 is a nontrivial square root of 1, modulo n, since we have that xi–1 ≠
art. Corollary 31.35 on page 934 states that only if
±1 (mod n) yet
n is composite can there exist a nontrivial square root of 1, modulo n,
so that demonstrating that xi–1 is a nontrivial square root of 1, modulo
n proves that n is composite.

▪

Thus,  if  the  call  WITNESS(a,  n)  returns  TRUE,  then  n  is  surely
composite, and the witness a, along with the reason that the procedure
returns  TRUE  (did  it  return  from  line  6  or  from  line  8?),  provides  a
proof that n is composite.

Let’s explore an alternative view of the behavior of WITNESS as a
function of the sequence X = 〈x0, x1, …, xt〉. We’ll ﬁnd this view useful
later  on,  when  we  analyze  the  error  rate  of  the  Miller-Rabin  primality

test.  Note  that  if  xi  =  1  for  some  0  ≤  i  <  t,  WITNESS  might  not
compute  the  rest  of  the  sequence.  If  it  were  to  do  so,  however,  each
value xi+1, xi+2, …, xt would be 1, so we can consider these positions
in the sequence X as being all 1s. There are four cases:

1. X  =  〈…,  d〉,  where  d  ≠  1:  the  sequence  X  does  not  end  in  1.
Return TRUE in line 8, since a is a witness to the compositeness
of n (by Fermat’s Theorem).

2. X = 〈1, 1, …, 1〉: the sequence X is all 1s. Return FALSE, since a

is not a witness to the compositeness of n.

3. X = 〈…, –1, 1, …, 1〉: the sequence X ends in 1, and the last non-
1  is  equal  to  –1.  Return  FALSE,  since  a  is  not  a  witness  to  the
compositeness of n.

4. X = 〈…, d, 1, …, 1〉, where d ≠ ±1: the sequence X ends in 1, but
the last non-1 is not –1. Return TRUE in line 6: a is a witness to
the compositeness of n, since d is a nontrivial square root of 1.

Now,  let’s  examine  the  Miller-Rabin  primality  test  based  on  how  it
uses  the  WITNESS  procedure.  As  before,  assume  that  n  is  an  odd
integer greater than 2.

The  procedure  MILLER-RABIN  is  a  probabilistic  search  for  a
proof that n is composite. The main loop (beginning on line 1) picks up
to s random values of a from
art, except for 1 and n – 1 (line 2). If
it  picks  a  value  of  a  that  is  a  witness  to  the  compositeness  of  n,  then
MILLER-RABIN  returns  COMPOSITE  on  line  4.  Such  a  result  is
always  correct,  by  the  correctness  of  WITNESS.  If  MILLER-RABIN
ﬁnds no witness in s trials, then the procedure assumes that it found no
witness  because  no  witnesses  exist,  and  therefore  it  assumes  that  n  is
prime. We’ll see that this result is likely to be correct if s is large enough,
but there is still a tiny chance that the procedure could be unlucky in its
choice of s random values of a, so that even though the procedure failed
to ﬁnd a witness, at least one witness exists.

To  illustrate  the  operation  of  MILLER-RABIN,  let  n  be  the
Carmichael number 561, so that n – 1 = 560 = 24 · 35, t = 4, and u = 35.

of

how

561).

(mod

Because

If  the  procedure  chooses  a  =  7  as  a  base,  the  column  for  b  =  35  in
Figure 31.4 (Section 31.6) shows that WITNESS computes x0 = a35 =
the  MODULAR-
241
EXPONENTIATION  procedure  operates  recursively  on  its  parameter
b, the ﬁrst four columns in Figure 31.4 represent the factor 24 of 560—
the  rightmost  four  zeros  in  the  binary  representation  of  560—reading
these  four  zeros  from  right  to  left  in  the  binary  representation.  Thus
WITNESS computes the sequence X = 〈241, 298, 166, 67, 1〉. Then, in
the  last  squaring  step,  WITNESS  discovers  that  a280  is  a  nontrivial
square root of 1 since a280 = 67 (mod n) and (a280)2 = a560 = 1 (mod
n). Therefore, a = 7 is a witness to the compositeness of n, WITNESS(7,
n) returns TRUE, and MILLER-RABIN returns COMPOSITE.

If  n  is  a  β-bit  number,  MILLER-RABIN  requires  O(sβ)  arithmetic
3) bit operations, since it requires asymptotically no

operations and O(sβ
more work than s modular exponentiations.

Error rate of the Miller-Rabin primality test

If MILLER-RABIN returns PRIME, then there is a very slim chance
that  it  has  made  an  error.  Unlike  PSEUDOPRIME,  however,  the
chance of error does not depend on n: there are no bad inputs for this
procedure.  Rather,  it  depends  on  the  size  of  s  and  the  “luck  of  the
draw”  in  choosing  base  values  a.  Moreover,  since  each  test  is  more
stringent  than  a  simple  check  of  equation  (31.39),  we  can  expect  on
general  principles  that  the  error  rate  should  be  small  for  randomly
chosen  integers  n.  The  following  theorem  presents  a  more  precise
argument.

Theorem 31.39
If n is an odd composite number, then the number of witnesses to the
compositeness of n is at least (n – 1)/2.

Proof   The proof shows that the number of nonwitnesses is at most (n –
1)/2, which implies the theorem.

We  start  by  claiming  that  any  nonwitness  must  be  a  member  of
art.  Why?  Consider  any  nonwitness  a.  It  must  satisfy  an–1  =  1
(mod n) or, equivalently, a · an−2 = 1 (mod n). Thus the equation ax = 1
(mod n) has a solution, namely an−2. By Corollary 31.21 on page 924,
gcd(a, n) | 1, which in turn implies that gcd(a, n) = 1. Therefore, a is a
member of

art, and all nonwitnesses belong to

art.

contained in

art  (recall  that  B  is  a  proper  subgroup  of

To  complete  the  proof,  we  show  that  not  only  are  all  nonwitnesses
art, they are all contained in a proper subgroup B of
art  when  B  is
art). By Corollary 31.16
art but B is not equal to
subgroup of
, we obtain |B| ≤ (n –
art. Since
on page 921, we then have
1)/2. Therefore, if all nonwitnesses are contained in a proper subgroup
of
art, then the number of nonwitnesses is at most (n – 1)/2, so that
the number of witnesses must be at least (n – 1)/2.

To  ﬁnd  a  proper  subgroup  B  of

art  containing  all  of  the

nonwitnesses, we consider two cases.

Case 1: There exists an

art such that

xn–1 ≠ 1 (mod n).

In  other  words,  n  is  not  a  Carmichael  number.  Since,  as  noted  earlier,
Carmichael numbers are extremely rare, case 1 is the more typical case
(e.g.,  when  n  has  been  chosen  randomly  and  is  being  tested  for
primality).
Let

art. The set B must be nonempty, since 1 ∈ B. The set B is
closed  under  multiplication  modulo  n,  and  so  B  is  a  subgroup  of
art  by  Theorem  31.14.  Every  nonwitness  belongs  to  B,  since  a

nonwitness a satisﬁes an–1 = 1 (mod n). Since
a proper subgroup of
Case 2: For all

art.

art,

art, we have that B is

art

In other words, n is a Carmichael number. This case is extremely rare in
practice.  Unlike  a  pseudoprimality  test,  however,  the  Miller-Rabin  test

can  efﬁciently  determine  that  Carmichael  numbers  are  composite,  as
we’re about to see.

In this case, n cannot be a prime power. To see why, suppose to the
contrary  that  n  =  pe,  where  p  is  a  prime  and  e  >  1.  We  derive  a
contradiction as follows. Since we assume that n is odd, p must also be
art is a cyclic group:
odd. Theorem 31.32 on page 933 implies that
it contains a generator g such that
art. (The formula for ϕ(n) comes
from equation (31.21) on page 920.) By equation (31.40), we have gn–1
=  1  (mod  n).  Then  the  discrete  logarithm  theorem  (Theorem  31.33  on
page 933, taking y = 0) implies that n – 1 = 0 (mod ϕ (n)), or
(p – 1)pe−1 | pe – 1.

This statement is a contradiction for e > 1, since (p – 1)pe−1 is divisible
by the prime p, but pe – 1 is not. Thus n is not a prime power.

Since  the  odd  composite  number  n  is  not  a  prime  power,  we
decompose  it  into  a  product  n1n2,  where  n1  and  n2  are  odd  numbers
greater  than  1  that  are  relatively  prime  to  each  other.  (There  may  be
several  ways  to  decompose  n,  and  it  does  not  matter  which  one  we
art and
choose. For example, if

, then we can choose

art.)

Recall that t and u are such that n – 1 = 2tu, where t ≥ 1 and u is odd,
and  that  for  an  input  a,  the  procedure  WITNESS  computes  the
sequence

art

where all computations are performed modulo n.
Let us call a pair (v, j) of integers acceptable if

art, and

art

Acceptable pairs certainly exist, since u is odd. Choose v = n – 1 and j =
0, and let u = 2k + 1, so that  art. Taking this number modulo n gives
(n – 1)2k+1 = (n – 1)2k · (n – 1) = (–1)2k · –1 = −1 (mod n). Thus, (n – 1,
0) is an acceptable pair. Now pick the largest possible j such that there

exists  an  acceptable  pair  (v,  j),  and  ﬁx  v  so  that  (v,  j)  is  an  acceptable
pair. Let

art

Since  B  is  closed  under  multiplication  modulo  n,  it  is  a  subgroup  of
art. By Theorem 31.15 on page 921, therefore, |B| divides  art. Every
nonwitness must be a member of B, since the sequence X produced by a
nonwitness must either be all 1s or else contain a –1 no later than the jth
position,  by  the  maximality  of  j.  (If  (a,  j′)  is  acceptable,  where  a  is  a
nonwitness, we must have j′ ≤ j by how we chose j.)

,  and  hence  that  B  is  a  proper  subgroup  of

We  now  use  the  existence  of  v  to  demonstrate  that  there  exists  a
art.  Since
art  by  Corollary  31.29  to  the  Chinese
remainder theorem. By Corollary 31.28, there exists a w simultaneously
satisfying the equations

art,  we  also  have

w = v (mod n1),
w = 1 (mod n2).

Therefore,

art

Corollary 31.29 gives that  art implies  art and also that  art implies

art. Hence, we conclude that  art, and so w ∉ B.
It  remains  to  show  that

.  We  start  by  working  separately
art, we have
modulo n1 and modulo n2. Working modulo n1, since
that gcd(v, n) = 1. Also, we have gcd(v, n1) = 1, since if v does not have
any  common  divisors  with  n,  then  it  certainly  does  not  have  any
common divisors with n1. Since w = v (mod n1), we see that gcd(w, n1)
= 1. Working modulo n2, we have w = 1 (mod n2) implies gcd(w, n2) = 1
by  Exercise  31.2-3.  Since  gcd(w,  n1)  =  1  and  gcd(w,  n2)  =  1,  Theorem
31.6 on page 908 yields gcd(w, n1n2) = gcd(w, n) = 1. That is,

art.

Therefore,  we  have

which  includes  all  nonwitnesses,  is  a  proper  subgroup  of
therefore has size at most (n – 1)/2.

art,  and  we  can  conclude  in  case  2  that  B,
art  and

In either case, the number of witnesses to the compositeness of n is

at least (n – 1)/2.

▪

Theorem 31.40
For  any  odd  integer  n  >  2  and  positive  integer  s,  the  probability  that
MILLER-RABIN(n, s) errs is at most 2–s.

Proof   By Theorem 31.39, if n is composite, then each execution of the
for loop of lines 1–4 of MILLER-RABIN has a probability of at least
1/2  of  discovering  a  witness  to  the  compositeness  of  n.  MILLER-
RABIN makes an error only if it is so unlucky as to miss discovering a
witness to the compositeness of n on each of the s iterations of the main
loop. The probability of such a sequence of misses is at most 2–s.

▪
If n is prime, MILLER-RABIN always reports PRIME, and if n is
composite,  the  chance  that  MILLER-RABIN  reports  PRIME  is  at
most 2−s.

When  applying  MILLER-RABIN  to  a  large  randomly  chosen
integer n, however, we need to consider as well the prior probability that
n  is  prime,  in  order  to  correctly  interpret  MILLER-RABIN’s  result.
Suppose that we ﬁx a bit length β and choose at random an integer n of
length β bits to be tested for primality, so that β ≈ 1g n ≈ 1.443 ln n. Let
A  denote  the  event  that  n  is  prime.  By  the  prime  number  theorem
(Theorem 31.37), the probability that n is prime is approximately

Pr {A} ≈ 1/ln n

≈ 1.443/β.

Now let B denote the event that MILLER-RABIN returns PRIME. We
art  (or
have  that
equivalently, that  art).

art  (or  equivalently,  that  Pr{B  |  A}  =  1)  and

But  what  is  Pr{A  |  B},  the  probability  that  n  is  prime,  given  that
MILLER-RABIN  has  returned  PRIME?  By  the  alternate  form  of

Bayes’s  theorem  (equation  (C.20)  on  page  1189)  and  approximating

art, we have

art

This  probability  does  not  exceed  1/2  until  s  exceeds  1g(ln  n  –  1).
Intuitively,  that  many  initial  trials  are  needed  just  for  the  conﬁdence
derived  from  failing  to  ﬁnd  a  witness  to  the  compositeness  of  n  to
overcome  the  prior  bias  in  favor  of  n  being  composite.  For  a  number
with β = 1024 bits, this initial testing requires about

lg(ln n – 1) ≈ lg(β/1.443)
≈ 9

trials.  In  any  case,  choosing  s  =  50  should  sufﬁce  for  almost  any
imaginable application.

In  fact,  the  situation  is  much  better.  If  you  are  trying  to  ﬁnd  large
primes  by  applying  MILLER-RABIN  to  large  randomly  chosen  odd
integers,  then  choosing  a  small  value  of  s  (say  3)  is  unlikely  to  lead  to
erroneous results, though we won’t prove it here. The reason is that for a
randomly  chosen  odd  composite  integer  n,  the  expected  number  of
nonwitnesses  to  the  compositeness  of  n  is  likely  to  be  considerably
smaller than (n – 1)/2.

If the integer n is not chosen randomly, however, the best that can be
proven is that the number of nonwitnesses is at most (n – 1)/4, using an
improved  version  of  Theorem  31.39.  Furthermore,  there  do  exist
integers n for which the number of nonwitnesses is (n – 1)/4.

Exercises

31.8-1
Prove that if an odd integer n > 1 is not a prime or a prime power, then
there exists a nontrivial square root of 1, modulo n.

★ 31.8-2
It is possible to strengthen Euler’s theorem (Theorem 31.30) slightly to
the form

art

where  art and λ(n) is deﬁned by

art

Prove that λ(n) | ϕ(n). A composite number n is a Carmichael number if
λ(n)  |  n  –  1.  The  smallest  Carmichael  number  is  561  =  3  ·  11  ·  17,  for
which  λ(n)  =  1cm(2,  10,  16)  =  80,  which  divides  560.  Prove  that
Carmichael  numbers  must  be  both  “square-free”  (not  divisible  by  the
square of any prime) and the product of at least three primes. (For this
reason, they are not common.)

31.8-3
Prove that if x is a nontrivial square root of 1, modulo n, then gcd(x −
1, n) and gcd(x + 1, n) are both nontrivial divisors of n.

Problems

31-1     Binary gcd algorithm
Most computers can perform the operations of subtraction, testing the
parity (odd or even) of a binary integer, and halving more quickly than
computing  remainders.  This  problem  investigates  the  binary  gcd
algorithm,  which  avoids  the  remainder  computations  used  in  Euclid’s
algorithm.

a. Prove that if a and b are both even, then gcd(a, b) = 2 · gcd(a/2, b/2).

b. Prove that if a is odd and b is even, then gcd(a, b) = gcd(a, b/2).

c. Prove that if a and b are both odd, then gcd(a, b) = gcd((a – b)/2, b).

d. Design an efﬁcient binary gcd algorithm for input integers a and b,

where a ≥ b, that runs in O(1g a) time. Assume that each subtraction,
parity test, and halving takes unit time.

31-2     Analysis of bit operations in Euclid’s algorithm
a. Consider the ordinary “paper and pencil” algorithm for long division:
dividing a by b, which yields a quotient q and remainder r. Show that
this method requires O((1 + 1g q)1g b) bit operations.

b. Deﬁne μ(a, b) = (1 + 1g a)(1 + 1g b). Show that the number of bit
operations performed by EUCLID in reducing the problem of
computing gcd(a, b) to that of computing gcd(b, a mod b) is at most
c(μ(a, b) – μ(b, a mod b)) for some sufﬁciently large constant c > 0.

c. Show that EUCLID(a, b) requires O(μ(a, b)) bit operations in general
2) bit operations when applied to two β-bit inputs.

and O(β

31-3     Three algorithms for Fibonacci numbers
This  problem  compares  the  efﬁciency  of  three  methods  for  computing
the nth Fibonacci number Fn, given n. Assume that the cost of adding,
subtracting, or multiplying two numbers is O(1), independent of the size
of the numbers.

a. Show that the running time of the straightforward recursive method

for computing Fn based on recurrence (3.31) on page 69 is exponential
in n. (See, for example, the FIB procedure on page 751.)

b. Show how to compute Fn in O(n) time using memoization.

c. Show how to compute Fn in O(1g n) time using only integer addition
and multiplication. (Hint: Consider the matrix art and its powers.)

d. Assume now that adding two β-bit numbers takes Θ(β) time and that
2) time. What is the running
multiplying two β-bit numbers takes Θ(β
time of these three methods under this more reasonable cost measure
for the elementary arithmetic operations?

31-4     Quadratic residues
Let p be an odd prime. A number  art is a quadratic residue modulo p,
if the equation x2 = a (mod p) has a solution for the unknown x.

a. Show that there are exactly (p – 1)/2 quadratic residues, modulo p.

b. If p is prime, we deﬁne the Legendre symbol art, for art, to be 1 if a is
a quadratic residue, modulo p, and –1 otherwise. Prove that if art,
then

art

Give an efﬁcient algorithm that determines whether a given number a
is  a  quadratic  residue,  modulo  p.  Analyze  the  efﬁciency  of  your
algorithm.

c. Prove that if p is a prime of the form 4k + 3 and a is a quadratic

residue in art, then ak+1 mod p is a square root of a, modulo p. How
much time is required to ﬁnd the square root of a quadratic residue a,
modulo p?

d. Describe an efﬁcient randomized algorithm for ﬁnding a

nonquadratic residue, modulo an arbitrary prime p, that is, a member
of art that is not a quadratic residue. How many arithmetic operations
does your algorithm require on average?

Chapter notes

Knuth  [260]  contains  a  good  discussion  of  algorithms  for  ﬁnding  the
greatest  common  divisor,  as  well  as  other  basic  number-theoretic
algorithms. Dixon [121] gives an overview of factorization and primality
testing.  Bach  [33],  Riesel  [378],  and  Bach  and  Shallit  [34]  provide
overviews  of  the  basics  of  computational  number  theory;  Shoup  [411]
provides  a  more  recent  survey.  The  conference  proceedings  edited  by
Pomerance [362] contains several excellent survey articles.

Knuth [260] discusses the origin of Euclid’s algorithm. It appears in
Book  7,  Propositions  1  and  2,  of  the  Greek  mathematician  Euclid’s
Elements,  which  was  written  around  300  B.C.E.  Euclid’s  description
may have been derived from an algorithm due to Eudoxus around 375
B.C.E.  Euclid’s  algorithm  may  hold  the  honor  of  being  the  oldest
nontrivial  algorithm,  rivaled  only  by  an  algorithm  for  multiplication
known  to  the  ancient  Egyptians.  Shallit  [407]  chronicles  the  history  of
the analysis of Euclid’s algorithm.

Knuth  attributes  a  special  case  of  the  Chinese  remainder  theorem
(Theorem  31.27)  to  the  Chinese  mathematician  Sun-Tsŭ,  who  lived
sometime between 200 B.C.E. and 200 C.E.—the date is quite uncertain.

The  same  special  case  was  given  by  the  Greek  mathematician
Nichomachus  around  100  C.E.  It  was  generalized  by  Qin  Jiushao  in
1247. The Chinese remainder theorem was ﬁnally stated and proved in
its full generality by L. Euler in 1734.

The randomized primality-testing algorithm presented here is due to
Miller  [327]  and  Rabin  [373]  and  is  the  fastest  randomized  primality-
testing  algorithm  known,  to  within  constant  factors.  The  proof  of
Theorem 31.40 is a slight adaptation of one suggested by Bach [32]. A
proof  of  a  stronger  result  for  MILLER-RABIN  was  given  by  Monier
[332, 333]. For many years primality-testing was the classic example of a
problem  where  randomization  appeared  to  be  necessary  to  obtain  an
efﬁcient  (polynomial-time)  algorithm.  In  2002,  however,  Agrawal,
Kayal,  and  Saxena  [4]  surprised  everyone  with  their  deterministic
polynomial-time  primality-testing  algorithm.  Until  then,  the  fastest
deterministic  primality  testing  algorithm  known,  due  to  Cohen  and
Lenstra  [97],  ran  in  (1g  n)O(1g1g1g  n)  time  on  input  n,  which  is  just
for  practical  purposes,
slightly
randomized  primality-testing  algorithms  remain  more  efﬁcient  and  are
generally preferred.

superpolynomial.  Nonetheless,

Beauchemin, Brassard, Crépeau, Goutier, and Pomerance [40] nicely

discuss the problem of ﬁnding large “random” primes.

The  concept  of  a  public-key  cryptosystem  is  due  to  Difﬁe  and
Hellman [115]. The RSA cryptosystem was proposed in 1977 by Rivest,
Shamir,  and  Adleman  [380].  Since  then,  the  ﬁeld  of  cryptography  has
blossomed. Our understanding of the RSA cryptosystem has deepened,
and  modern  implementations  use  signiﬁcant  reﬁnements  of  the  basic
techniques presented here. In addition, many new techniques have been
developed  for  proving  cryptosystems  to  be  secure.  For  example,
Goldwasser  and  Micali  [190]  show  that  randomization  can  be  an
effective tool in the design of secure public-key encryption schemes. For
signature  schemes,  Goldwasser,  Micali,  and  Rivest  [191]  present  a
digital-signature  scheme  for  which  every  conceivable  type  of  forgery  is
provably  as  difﬁcult  as  factoring.  Katz  and  Lindell  [253]  provide  an
overview of modern cryptography.

The best algorithms for factoring large numbers have a running time
that grows roughly exponentially with the cube root of the length of the
number  n  to  be  factored.  The  general  number-ﬁeld  sieve  factoring
algorithm  (as  developed  by  Buhler,  Lenstra,  and  Pomerance  [77]  as  an
extension of the ideas in the number-ﬁeld sieve factoring algorithm by
Pollard [360] and Lenstra et al. [295] and reﬁned by Coppersmith [102]
and  others)  is  perhaps  the  most  efﬁcient  such  algorithm  in  general  for
large  inputs.  Although  it  is  difﬁcult  to  give  a  rigorous  analysis  of  this
algorithm, under reasonable assumptions we can derive a running-time
estimate of L(1/3, n)1.902+o(1), where

art.

The elliptic-curve method due to Lenstra [296] may be more effective
for some inputs than the number-ﬁeld sieve method, since it can ﬁnd a
small prime factor p quite quickly. With this method, the time to ﬁnd p
is estimated to be

art.

