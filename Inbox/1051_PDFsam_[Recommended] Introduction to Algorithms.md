28        Matrix Operations

Because  operations  on  matrices  lie  at  the  heart  of  scientific  computing,
efficient  algorithms  for  working  with  matrices  have  many  practical
applications.  This  chapter  focuses  on  how  to  multiply  matrices  and  solve
sets  of  simultaneous  linear  equations.  Appendix  D  reviews  the  basics  of
matrices.

Section  28.1  shows  how  to  solve  a  set  of  linear  equations  using  LUP
decompositions. Then, Section 28.2 explores the close relationship between
multiplying  and  inverting  matrices.  Finally,  Section  28.3  discusses  the
important  class  of  symmetric  positive-definite  matrices  and  shows  how  to
use them to find a least-squares solution to an overdetermined set of linear
equations.

One  important  issue  that  arises  in  practice  is  numerical  stability.
Because  actual  computers  have  limits  to  how  precisely  they  can  represent
floating-point  numbers,  round-off  errors  in  numerical  computations  may
become  amplified  over  the  course  of  a  computation,  leading  to  incorrect
results. Such computations are called numerically unstable. Although we’ll
briefly consider numerical stability on occasion, we won’t focus on it in this
chapter. We refer you to the excellent book by Higham [216] for a thorough
discussion of stability issues.

28.1    Solving systems of linear equations

Numerous applications need to solve sets of simultaneous linear equations.
A  linear  system  can  be  cast  as  a  matrix  equation  in  which  each  matrix  or

vector element belongs to a field, typically the real numbers ℝ. This section
discusses how to solve a system of linear equations using a method called
LUP decomposition.

The process starts with a set of linear equations in n unknowns x1, x2,

… , xn:

A solution to the equations (28.1) is a set of values for x1, x2, … , xn that
satisfy all of the equations simultaneously. In this section, we treat only the
case in which there are exactly n equations in n unknowns.

Next, rewrite equations (28.1) as the matrix-vector equation

or, equivalently, letting A = (aij), x = (xi), and b = (bi), as

If A is nonsingular, it possesses an inverse A−1, and

is the solution vector. We can prove that x is the unique solution to equation
(28.2)  as  follows.  If  there  are  two  solutions,  x  and  x′,  then  Ax  =  Ax′  =  b
and, letting I denote an identity matrix,

x = Ix

= (A−1A)x
= A−1(Ax)
= A−1(Ax′)

= (A−1A)x′
= Ix′
= x′.

This  section  focuses  on  the  case  in  which  A  is  nonsingular  or,
equivalently  (by  Theorem  D.1  on  page  1220),  the  rank  of  A  equals  the
number n of unknowns. There are other possibilities, however, which merit
a brief discussion. If the number of equations is less than the number n of
unknowns—or,  more  generally,  if  the  rank  of  A  is  less  than  n—then  the
system  is  underdetermined.  An  underdetermined  system  typically  has
infinitely  many  solutions,  although  it  may  have  no  solutions  at  all  if  the
equations are inconsistent. If the number of equations exceeds the number n
of  unknowns,  the  system  is  overdetermined,  and  there  may  not  exist  any
solutions.  Section  28.3  addresses  the  important  problem  of  finding  good
approximate solutions to overdetermined systems of linear equations.

Let’s return to the problem of solving the system Ax = b of n equations
in  n  unknowns.  One  option  is  to  compute  A−1  and  then,  using  equation
(28.3),  multiply  b  by  A−1,  yielding  x  =  A−1b.  This  approach  suffers  in
practice  from  numerical  instability.  Fortunately,  another  approach—LUP
decomposition—is  numerically  stable  and  has  the  further  advantage  of
being faster in practice.

Overview of LUP decomposition
The  idea  behind  LUP  decomposition  is  to  find  three  n  ×  n  matrices  L,  U,
and P such that

where

L is a unit lower-triangular matrix,
U is an upper-triangular matrix, and
P is a permutation matrix.

We  call  matrices  L,  U,  and  P  satisfying  equation  (28.4)  an  LUP
decomposition of the matrix A. We’ll show that every nonsingular matrix A
possesses such a decomposition.

Computing  an  LUP  decomposition  for  the  matrix  A  has  the  advantage
that linear systems can be efficiently solved when they are triangular, as is
the case for both matrices L and U. If you have an LUP decomposition for
A, you can solve equation (28.2), Ax = b, by solving only triangular linear
systems,  as  follows.  Multiply  both  sides  of  Ax  =  b  by  P,  yielding  the
equivalent  equation  PAx  =  Pb.  By  Exercise  D.1-4  on  page  1219,
multiplying  both  sides  by  a  permutation  matrix  amounts  to  permuting  the
equations  (28.1).  By  the  decomposition  (28.4),  substituting  LU  for  PA
gives
LUx = Pb.

You can now solve this equation by solving two triangular linear systems.
Define  y  =  Ux,  where  x  is  the  desired  solution  vector.  First,  solve  the
lower-triangular system

for  the  unknown  vector  y  by  a  method  called  “forward  substitution.”
Having solved for y, solve the upper-triangular system

for the unknown x by a method called “back substitution.” Why does this
process solve Ax = b? Because the permutation matrix P is invertible (see
Exercise D.2-3 on page 1223), multiplying both sides of equation (28.4) by
P −1 gives P−1PA = P−1LU, so that

Hence, the vector x that satisfies Ux = y is the solution to Ax = b:

Ax = P−1LUx (by equation (28.7))

= P−1Ly

(by equation (28.6))

= P−1Pb

(by equation (28.5))

= b.

The  next  step  is  to  show  how  forward  and  back  substitution  work  and

then attack the problem of computing the LUP decomposition itself.

Forward and back substitution

Forward substitution can solve the lower-triangular system (28.5) in Θ(n2)
time, given L, P, and b. An array π[1 : n] provides a more compact format
to represent the permutation P than an n × n matrix that is mostly 0s. For i =
1, 2, … , n, the entry π[i] indicates that Pi,π[i] = 1 and Pij = 0 for j ≠ π[i].
Thus,  PA  has  aπ[i],j  in  row  i  and  column  j,  and  Pb  has  bπ[i]  as  its  ith
element.  Since  L  is  unit  lower-triangular,  the  matrix  equation  Ly  =  Pb  is
equivalent to the n equations

   y1
l21y1 + y2
l31y1 + l32y2 + y3

= bπ[1],
= bπ[2],
= bπ[3],
⋮

ln1y1 + ln2y2 + ln3y3 + ⋯ + yn = bπ[n].

The first equation gives y1 = bπ[1] directly. Knowing the value of y1, you
can substitute it into the second equation, yielding
y2 = bπ[2] − l21y1.
Next, you can substitute both y1 and y2 into the third equation, obtaining
y3 = bπ[3] − (l31y1 + l32y2).
In general, you substitute y1, y2, … , yi−1 “forward” into the ith equation
to solve for yi:

Once you’ve solved for y, you can solve for x in equation (28.6) using
back substitution, which is similar to forward substitution. This time, you
solve  the  nth  equation  first  and  work  backward  to  the  first  equation.  Like
forward  substitution,  this  process  runs  in  Θ(n2)  time.  Since  U  is  upper-
triangular, the matrix equation Ux = y is equivalent to the n equations

u11x1 + u12x2 + ⋯
+
u22x2 + ⋯ +

u1,n−2xn−2 +

u1,n−1xn−1 +

u1nxn = y1,

u2,n−2xn−2 +

u2,n−1xn−1 +

un−2,n−2xn−2
+

un−2,n−1xn−1
+
un−1,n−1xn−1
+

u2nxn = y2,
⋮

un−2,nxn = yn−2,

un−1,nxn = yn−1,

un,nxn = yn.

Thus, you can solve for xn, xn−1, … , x1 successively as follows:

= yn/un,n,

xn
xn−1 = (yn−1 − un−1,nxn)/un−1,n−1,
xn−2 = (yn−2 − (un−2,n−1xn−1 + un−2,nxn))/un−2,n−2,

⋮

or, in general,

Given  P,  L,  U,  and  b,  the  procedure  LUP-SOLVE  on  the  next  page
solves for x by combining forward and back substitution. The permutation

matrix  P  is  represented  by  the  array  π.  The  procedure  first  solves  for  y
using  forward  substitution  in  lines  2–3,  and  then  it  solves  for  x  using
backward substitution in lines 4–5. Since the summation within each of the
for loops includes an implicit loop, the running time is Θ(n2).

As an example of these methods, consider the system of linear equations

defined by Ax = b, where

LUP-SOLVE(L, U, π, b, n)
1 let x and y be new vectors of length n
2 for i = 1 to n
3
4 for i = n downto 1
5
6 return x

and we want to solve for the unknown x. The LUP decomposition is

(You might want to verify that PA = LU.) Using forward substitution, solve
Ly = Pb for y:

obtaining

by  computing  first  y1,  then  y2,  and  finally  y3.  Then,  using  back
substitution, solve Ux = y for x:

thereby obtaining the desired answer

by computing first x3, then x2, and finally x1.

Computing an LU decomposition
Given  an  LUP  decomposition  for  a  nonsingular  matrix  A,  you  can  use
forward  and  back  substitution  to  solve  the  system  Ax  =  b  of  linear
equations. Now let’s see how to efficiently compute an LUP decomposition
for  A. We  start  with  the  simpler  case  in  which  A  is  an  n  ×  n  nonsingular
matrix and P is absent (or, equivalently, P = In, the n × n identity matrix),
so that A = LU. We call the two matrices L and U an LU decomposition of
A.

To create an LU decomposition, we’ll use a process known as Gaussian
elimination.  Start  by  subtracting  multiples  of  the  first  equation  from  the
other equations in order to remove the first variable from those equations.
Then  subtract  multiples  of  the  second  equation  from  the  third  and
subsequent equations so that now the first and second variables are removed
from  them.  Continue  this  process  until  the  system  that  remains  has  an
upper-triangular  form—this  is  the  matrix  U.  The  matrix  L  comprises  the
row multipliers that cause variables to be eliminated.

To implement this strategy, let’s start with a recursive formulation. The
input is an n × n nonsingular matrix A. If n = 1, then nothing needs to be
done: just choose L = I1 and U = A. For n > 1, break A into four parts:

where v = (a21, a31, … , an1) is a column (n−1)-vector, wT = (a12, a13, …
, a1n)T is a row (n − 1)-vector, and A′ is an (n − 1) × (n − 1) matrix. Then,
using matrix algebra (verify the equations by simply multiplying through),
factor A as

The  0s  in  the  first  and  second  matrices  of  equation  (28.9)  are  row  and
column (n − 1)-vectors, respectively. The term vwT/a11 is an (n − 1) × (n −
1) matrix formed by taking the outer product of v and w and dividing each
element of the result by a11. Thus it conforms in size to the matrix A′ from
which it is subtracted. The resulting (n − 1) × (n − 1) matrix

is called the Schur complement of A with respect to a11.

We  claim  that  if  A  is  nonsingular,  then  the  Schur  complement  is
nonsingular, too. Why? Suppose that the Schur complement, which is (n −
1) × (n − 1), is singular. Then by Theorem D.1, it has row rank strictly less
than  n  −  1.  Because  the  bottom  n  −  1  entries  in  the  first  column  of  the
matrix

are all 0, the bottom n − 1 rows of this matrix must have row rank strictly
less than n − 1. The row rank of the entire matrix, therefore, is strictly less
than  n. Applying  Exercise  D.2-8  on  page  1223  to  equation  (28.9),  A  has
rank strictly less than n, and from Theorem D.1, we derive the contradiction
that A is singular.

Because  the  Schur  complement  is  nonsingular,  it,  too,  has  an  LU

decomposition, which we can find recursively. Let’s say that

A′ − vwT/a11 = L′U′,
where  L′  is  unit  lower-triangular  and  U′  is  upper-triangular.  The  LU
decomposition of A is then A = LU, with

as shown by

Because  L′  is  unit  lower-triangular,  so  is  L,  and  because  U′  is  upper-
triangular, so is U.

Of course, if a11 = 0, this method doesn’t work, because it divides by 0.
It also doesn’t work if the upper leftmost entry of the Schur complement A′
−  vwT/a11  is  0,  since  the  next  step  of  the  recursion  will  divide  by  it. The
denominators in each step of LU decomposition are called pivots, and they
occupy  the  diagonal  elements  of  the  matrix  U.  The  permutation  matrix  P
included in LUP decomposition provides a way to avoid dividing by 0, as
we’ll  see  below.  Using  permutations  to  avoid  division  by  0  (or  by  small
numbers, which can contribute to numerical instability), is called pivoting.

An  important  class  of  matrices  for  which  LU  decomposition  always
works  correctly  is  the  class  of  symmetric  positive-definite  matrices.  Such
matrices require no pivoting to avoid dividing by 0 in the recursive strategy
outlined  above.  We  will  prove  this  result,  as  well  as  several  others,  in
Section 28.3.

The  pseudocode  in  the  procedure  LU-DECOMPOSITION  follows  the
recursive strategy, except that an iteration loop replaces the recursion. (This
transformation is a standard optimization for a “tail-recursive” procedure—
one  whose  last  operation  is  a  recursive  call  to  itself.  See  Problem  7-5  on

page  202.)  The  procedure  initializes  the  matrix  U  with  0s  below  the
diagonal  and  matrix  L  with  1s  on  its  diagonal  and  0s  above  the  diagonal.
Each  iteration  works  on  a  square  submatrix,  using  its  upper  leftmost
element  as  the  pivot  to  compute  the  v  and  w  vectors  and  the  Schur
complement,  which  becomes  the  square  submatrix  worked  on  by  the  next
iteration.

LU-DECOMPOSITION(A, n)
  1 let L and U be new n × n matrices
  2 initialize U with 0s below the diagonal
  3 initialize L with 1s on the diagonal and 0s above the diagonal
  4 for k = 1 to n
ukk = akk
  5
for i = k + 1 to n
lik = aik/akk
uki = aki
for i = k + 1 to n

// aik holds vi
// aki holds wi
// compute the Schur complement …

  7

  9

  8

  6

10

for j = k + 1 to n

aij = aij − likukj

11
12 return L and U

// … and store it back into A

Each recursive step in the description above takes place in one iteration
of the outer for loop of lines 4–11. Within this loop, line 5 determines the
pivot to be ukk = akk. The for loop in lines 6–8 (which does not execute
when k = n) uses the v and w vectors to update L and U. Line 7 determines
the below-diagonal elements of L, storing vi/akk in lik, and line 8 computes
the  above-diagonal  elements  of  U,  storing  wi  in  uki.  Finally,  lines  9–11
compute  the  elements  of  the  Schur  complement  and  store  them  back  into
the  matrix  A.  (There  is  no  need  to  divide  by  akk  in  line  11  because  that

already  happened  when  line  7  computed  lik.)  Because  line  11  is  triply
nested, LU-DECOMPOSITION runs in Θ(n3) time.

Figure  28.1  illustrates  the  operation  of  LU-DECOMPOSITION.  It
shows  a  standard  optimization  of  the  procedure  that  stores  the  significant
elements of L and U in place in the matrix A. Each element aij corresponds
to either lij (if i > j) or uij (if i ≤ j), so that the matrix A holds both L and U
when  the  procedure  terminates.  To  obtain  the  pseudocode  for  this
the  LU-DECOMPOSITION
optimization  from
procedure, just replace each reference to l or u by a. You can verify that this
transformation preserves correctness.

the  pseudocode  for

Figure 28.1 The operation of LU-DECOMPOSITION. (a) The matrix A. (b) The result of the first
iteration of the outer for loop of lines 4–11. The element a11 = 2 highlighted in blue is the pivot, the
tan  column  is  v/a11,  and  the  tan  row  is  wT.  The  elements  of  U  computed  thus  far  are  above  the
horizontal  line,  and  the  elements  of  L  are  to  the  left  of  the  vertical  line.  The  Schur  complement
matrix  A′  −  vwT/a11  occupies  the  lower  right.  (c)  The  result  of  the  next  iteration  of  the  outer  for
loop, on the Schur complement matrix from part (b). The element a22 = 4 highlighted in blue is the
pivot, and the tan column and row are v/a22 and wT (in the partitioning of the Schur complement),
respectively. Lines divide the matrix into the elements of U computed so far (above), the elements of
L computed so far (left), and the new Schur complement (lower right). (d) After the next iteration,
the matrix A is factored. The element 3 in the new Schur complement becomes part of U when the
recursion terminates.) (e) The factorization A = LU.

Computing an LUP decomposition

If the diagonal of the matrix given to LU-DECOMPOSITION contains any
0s,  then  the  procedure  will  attempt  to  divide  by  0,  which  would  cause
disaster.  Even  if  the  diagonal  contains  no  0s,  but  does  have  numbers  with
small  absolute  values,  dividing  by  such  numbers  can  cause  numerical
instabilities.  Therefore,  LUP  decomposition  pivots  on  entries  with  the
largest absolute values that it can find.

In LUP decomposition, the input is an n × n nonsingular matrix A, with
a goal of finding a permutation matrix P, a unit lower-triangular matrix L,
and  an  upper-triangular  matrix  U  such  that  PA  =  LU.  Before  partitioning
the  matrix  A,  as  LU  decomposition  does,  LUP  decomposition  moves  a
nonzero element, say ak1, from somewhere in the first column to the (1, 1)
position  of
the  greatest  numerical  stability,  LUP
decomposition  chooses  the  element  in  the  first  column  with  the  greatest
absolute value as ak1. (The first column cannot contain only 0s, for then A
would  be  singular,  because  its  determinant  would  be  0,  by  Theorems  D.4
and  D.5  on  page  1221.)  In  order  to  preserve  the  set  of  equations,  LUP
decomposition  exchanges  row  1  with  row  k,  which  is  equivalent  to
multiplying  A  by  a  permutation  matrix  Q  on  the  left  (Exercise  D.1-4  on
page 1219). Thus, the analog to equation (28.8) expresses QA as

the  matrix.  For

where  v  =  (a21,  a31,  …  ,  an1),  except  that  a11  replaces  ak1;  wT  =  (ak2,
ak3, … , akn)T; and A′ is an (n − 1) × (n − 1) matrix. Since ak1 ≠ 0, the
analog to equation (28.9) guarantees no division by 0:

Just  as  in  LU  decomposition,  if  A  is  nonsingular,  then  the  Schur
complement  A′  −  vwT/ak1  is  nonsingular,  too.  Therefore,  you  can

recursively  find  an  LUP  decomposition  for  it,  with  unit  lower-triangular
matrix L′, upper-triangular matrix U′, and permutation matrix P′, such that

P′(A′ − vwT/ak1) = L′U′.

Define

which  is  a  permutation  matrix,  since  it  is  the  product  of  two  permutation
matrices (Exercise D.1-4 on page 1219). This definition of P gives

which  yields  the  LUP  decomposition.  Because  L′  is  unit  lower-triangular,
so is L, and because U′ is upper-triangular, so is U.

Notice that in this derivation, unlike the one for LU decomposition, both
the  column  vector  v/ak1  and  the  Schur  complement  A′  −  vwT/ak1  are
the  permutation  matrix  P′.  The  procedure  LUP-
multiplied  by
DECOMPOSITION gives the pseudocode for LUP decomposition.

LUP-DECOMPOSITION(A, n)
  1 let π[1 : n] be a new array
  2 for i = 1 to n
π[i] = i
  3
  4 for k = 1 to n

// initialize π to the identity permutation

  5

  6

  7

  8

  9

10

11

12

13

14

15

16

17

18

p = 0
for i = k to n
if |aik| > p
p = |aik|
k′ = i

if p == 0

// find largest absolute value in column k

// row number of the largest found so far

error “singular matrix”

exchange π[k] with π[k′]
for i = 1 to n

exchange aki with ak′i // exchange rows k and k′

for i = k + 1 to n
aik = aik/akk
for j = k + 1 to n

aij = aij − aikakj

// compute L and U in place in A

implementation  of

Like  LU-DECOMPOSITION,  the  LUP-DECOMPOSITION  procedure
replaces  the  recursion  with  an  iteration  loop.  As  an  improvement  over  a
direct
the  procedure  dynamically
the  recursion,
maintains the permutation matrix P as an array π, where π[i] = j means that
the  ith  row  of  P  contains  a  1  in  column  j.  The  LUP-DECOMPOSITION
procedure also implements the improvement mentioned earlier, computing
L and U in place in the matrix A. Thus, when the procedure terminates,

Figure  28.2  illustrates  how  LUP-DECOMPOSITION  factors  a  matrix.
Lines  2–3  initialize  the  array  π  to  represent  the  identity  permutation.  The
outer  for  loop  of  lines  4–18  implements  the  recursion,  finding  an  LUP
decomposition of the (n − k + 1) × (n − k + 1) submatrix whose upper left is
in  row  k  and  column  k.  Each  time  through  the  outer  loop,  lines  5–9
determine  the  element  ak′k  with  the  largest  absolute  value  of  those  in  the
current first column (column k) of the (n − k + 1) × (n − k + 1) submatrix

that the procedure is currently working on. If all elements in the current first
column are 0, lines 10–11 report that the matrix is singular. To pivot, line 12
exchanges π[k′] with π[k], and lines 13–14 exchange the kth and k′th rows
of A, thereby making the pivot element akk. (The entire rows are swapped
because  in  the  derivation  of  the  method  above,  not  only  is  A′  −  vwT/ak1
multiplied  by  P′,  but  so  is  v/ak1.)  Finally,  the  Schur  complement  is
computed by lines 15–18 in much the same way as it is computed by lines
6–11 of LU-DECOMPOSITION, except that here the operation is written to
work in place.

Figure  28.2  The  operation  of  LUP-DECOMPOSITION.  (a)  The  input  matrix  A  with  the  identity
permutation  of  the  rows  in  yellow  on  the  left.  The  first  step  of  the  algorithm  determines  that  the
element 5 highlighted in blue in the third row is the pivot for the first column. (b) Rows 1 and 3 are
swapped and the permutation is updated. The tan column and row represent v and wT. (c) The vector
v is replaced by v/5, and the lower right of the matrix is updated with the Schur complement. Lines
divide the matrix into three regions: elements of U (above), elements of L (left), and elements of the
Schur complement (lower right). (d)–(f) The second step. (g)–(i) The third step. No further changes
occur on the fourth (final) step. (j) The LUP decomposition PA = LU.

Because of its triply nested loop structure, LUP-DECOMPOSITION has

that  of  LU-
a  running
DECOMPOSITION. Thus, pivoting costs at most a constant factor in time.

the  same  as

time  of  Θ(n3),  which

is

Exercises

28.1-1
Solve the equation

by using forward substitution.

28.1-2
Find an LU decomposition of the matrix

28.1-3
Solve the equation

by using an LUP decomposition.

28.1-4
Describe the LUP decomposition of a diagonal matrix.

28.1-5
Describe the LUP decomposition of a permutation matrix, and prove that it
is unique.

28.1-6
Show that for all n ≥ 1, there exists a singular n × n matrix that has an LU
decomposition.

28.1-7
In  LU-DECOMPOSITION,  is  it  necessary  to  perform  the  outermost  for
loop iteration when k = n? How about in LUP-DECOMPOSITION?

28.2    Inverting matrices

Although you can use equation (28.3) to solve a system of linear equations
by  computing  a  matrix  inverse,  in  practice  you  are  better  off  using  more

numerically  stable  techniques,  such  as  LUP  decomposition.  Sometimes,
however,  you  really  do  need  to  compute  a  matrix  inverse.  This  section
shows how to use LUP decomposition to compute a matrix inverse. It also
proves that matrix multiplication and computing the inverse of a matrix are
equivalently  hard  problems,  in  that  (subject  to  technical  conditions)  an
algorithm for one can solve the other in the same asymptotic running time.
Thus,  you  can  use  Strassen’s  algorithm  (see  Section  4.2)  for  matrix
multiplication  to  invert  a  matrix.  Indeed,  Strassen’s  original  paper  was
motivated by the idea that a set of a linear equations could be solved more
quickly than by the usual method.

Computing a matrix inverse from an LUP decomposition
Suppose that you have an LUP decomposition of a matrix A in the form of
three  matrices  L,  U,  and  P  such  that  PA  =  LU.  Using  LUP-SOLVE,  you
can  solve  an  equation  of  the  form  Ax  =  b  in  Θ(n2)  time.  Since  the  LUP
decomposition  depends  on  A  but  not  b,  you  can  run  LUP-SOLVE  on  a
second  set  of  equations  of  the  form  Ax  =  b′  in  Θ(n2)  additional  time.  In
general,  once  you  have  the  LUP  decomposition  of  A,  you  can  solve,  in
Θ(kn2) time, k versions of the equation Ax = b that differ only in the vector
b.

Let’s think of the equation

which defines the matrix X, the inverse of A, as a set of n distinct equations
of the form Ax = b. To be precise, let Xi denote the ith column of X, and
recall  that  the  unit  vector  ei  is  the  ith  column  of  In.  You  can  then  solve
equation (28.11) for X by using the LUP decomposition for A to solve each
equation
AXi = ei

separately for Xi. Once you have the LUP decomposition, you can compute
each of the n columns Xi in Θ(n2) time, and so you can compute X from the
LUP  decomposition  of  A  in  Θ(n3)  time.  Since  you  find  the  LUP
decomposition of A in Θ(n3) time, you can compute the inverse A−1 of a
matrix A in Θ(n3) time.

Matrix multiplication and matrix inversion

the

let’s  see  how

Now
theoretical  speedups  obtained  for  matrix
multiplication  translate  to  speedups  for  matrix  inversion.  In  fact,  we’ll
prove  something  stronger:  matrix  inversion  is  equivalent  to  matrix
multiplication, in the following sense. If M(n) denotes the time to multiply
two  n  ×  n  matrices,  then  a  nonsingular  n  ×  n  matrix  can  be  inverted  in
O(M(n)) time. Moreover, if I(n) denotes the time to invert a nonsingular n
× n matrix, then two n × n matrices can be multiplied in O(I(n)) time. We
prove these results as two separate theorems.

Theorem 28.1 (Multiplication is no harder than inversion)
If an n × n matrix can be inverted in I(n) time, where I(n) = Ω(n2) and I(n)
satisfies  the  regularity  condition  I(3n)  =  O(I(n)),  then  two  n  ×  n  matrices
can be multiplied in O(I(n)) time.

Proof   Let A and B be n × n matrices. To compute their product C = AB,
define the 3n × 3n matrix D by

The inverse of D is

and  thus  to  compute  the  product  AB,  just  take  the  upper  right  n  ×  n
submatrix of D−1.

Constructing  matrix  D  takes  Θ(n2)  time,  which  is  O(I(n))  from  the
assumption  that  I(n)  =  Ω(n2),  and  inverting  D  takes  O(I(3n))  =  O(I(n))
time, by the regularity condition on I(n). We thus have M(n) = O(I(n)).

▪
Note  that  I(n)  satisfies  the  regularity  condition  whenever  I(n)  =  Θ(nc
dn) for any constants c > 0 and d ≥ 0.
The proof that matrix inversion is no harder than matrix multiplication
relies on some properties of symmetric positive-definite matrices proved in
Section 28.3.

lg

Theorem 28.2 (Inversion is no harder than multiplication)
Suppose that two n × n real matrices can be multiplied in M(n) time, where
M(n) = Ω(n2) and M(n) satisfies the following two regularity conditions:

1. M(n + k) = O(M(n)) for any k in the range 0 ≤ k < n, and
2. M(n/2) ≤ cM(n) for some constant c < 1/2.

Then  the  inverse  of  any  real  nonsingular  n×n  matrix  can  be  computed  in
O(M(n)) time.

Proof   Let A be an n × n matrix with real-valued entries that is nonsingular.
Assume that n is an exact power of 2 (i.e., n = 2
 for some integer l); we’ll
see at the end of the proof what to do if n is not an exact power of 2.

l

For  the  moment,  assume  that  the  n  ×  n  matrix  A  is  symmetric  and
positive-definite. Partition each of A and its inverse A−1 into four n/2 × n/2
submatrices:

Then, if we let

be the Schur complement of A with respect to B (we’ll see more about this
form of Schur complement in Section 28.3), we have

since  AA−1  =  In,  as  you  can  verify  by  performing  the  matrix
multiplication. Because A is symmetric and positive-definite, Lemmas 28.4
and  28.5  in  Section  28.3  imply  that  B  and  S  are  both  symmetric  and
positive-definite.  By  Lemma  28.3  in  Section  28.3,  therefore,  the  inverses
B−1 and S−1 exist, and by Exercise D.2-6 on page 1223, B−1 and S−1 are
symmetric, so that (B−1)T = B−1 and (S−1)T = S−1. Therefore, to compute
the submatrices
R = B−1 + B−1CTS−1CB−1,
T = −B−1CTS−1,
U = −S−1CB−1, and
V = S−1

of A−1, do the following, where all matrices mentioned are n/2 × n/2:

1. Form the submatrices B, C, CT, and D of A.

2. Recursively compute the inverse B−1 of B.

3. Compute  the  matrix  product  W  =  CB−1,  and  then  compute  its
transpose  WT,  which  equals  B−1CT  (by  Exercise  D.1-2  on  page
1219 and (B−1)T = B−1).

4. Compute the matrix product X = WCT, which equals CB−1CT, and

then compute the matrix S = D − X = D − CB−1CT.

5. Recursively compute the inverse S−1 of S.

6. Compute  the  matrix  product  Y  =  S−1W,  which  equals  S−1CB−1,
and  then  compute  its  transpose  YT,  which  equals  B−1CTS−1  (by
Exercise D.1-2, (B−1)T = B−1, and (S−1)T = S−1).

7. Compute

the  matrix  product  Z  =  WTY,  which  equals

B−1CTS−1CB−1.

8. Set R = B−1 + Z.

9. Set T = −YT.
10. Set U = −Y.

11. Set V = S−1.

Thus,  to  invert  an  n×n  symmetric  positive-definite  matrix,  invert  two
n/2×n/2 matrices in steps 2 and 5; perform four multiplications of n/2 × n/2
matrices in steps 3, 4, 6, and 7; plus incur an additional cost of O(n2) for
extracting  submatrices  from  A,  inserting  submatrices  into  A−1,  and
performing a constant number of additions, subtractions, and transposes on
n/2 × n/2 matrices. The running time is given by the recurrence

The second line follows from the assumption that M(n) = Ω(n2) and from
the  second  regularity  condition  in  the  statement  of  the  theorem,  which
implies that 4M(n/2) < 2M(n). Because M(n) = Ω(n2), case 3 of the master
theorem  (Theorem  4.1)  applies  to  the  recurrence  (28.15),  giving  the
O(M(n)) result.

It remains to prove how to obtain the same asymptotic running time for
matrix  multiplication  as  for  matrix  inversion  when  A  is  invertible  but  not

symmetric and positive-definite. The basic idea is that for any nonsingular
matrix A, the matrix ATA is symmetric (by Exercise D.1-2) and positive-
definite  (by Theorem  D.6  on  page  1222). The  trick,  then,  is  to  reduce  the
problem of inverting A to the problem of inverting ATA.

The  reduction  is  based  on  the  observation  that  when  A  is  an  n  ×  n

nonsingular matrix, we have

A−1 = (ATA)−1AT,

since  ((ATA)−1AT)A  =  (ATA)−1(ATA)  =  In  and  a  matrix  inverse  is
unique. Therefore, to compute A−1, first multiply AT by A to obtain ATA,
then  invert  the  symmetric  positive-definite  matrix  ATA  using  the  above
divide-and-conquer algorithm, and finally multiply the result by AT. Each
of  these  three  steps  takes  O(M(n))  time,  and  thus  any  nonsingular  matrix
with real entries can be inverted in O(M(n)) time.

The above proof assumed that A is an n × n matrix, where n is an exact
power of 2. If n is not an exact power of 2, then let k < n be such that n + k
is an exact power of 2, and define the (n + k) × (n + k) matrix A′ as

Then the inverse of A′ is

Apply the method of the proof to A′ to compute the inverse of A′, and take
the first n rows and n columns of the result as the desired answer A−1. The
first regularity condition on M(n) ensures that enlarging the matrix in this
way increases the running time by at most a constant factor.

▪

The proof of Theorem 28.2 suggests how to solve the equation Ax = b
by using LU decomposition without pivoting, so long as A is nonsingular.

Let y = ATb. Multiply both sides of the equation Ax = b by AT, yielding
(ATA)x = ATb = y. This transformation doesn’t affect the solution x, since
AT  is  invertible.  Because  ATA  is  symmetric  positive-definite,  it  can  be
factored by computing an LU decomposition. Then, use forward and back
substitution  to  solve  for  x  in  the  equation  (ATA)x  =  y.  Although  this
method
the  procedure  LUP-
DECOMPOSITION works much better. LUP decomposition requires fewer
arithmetic  operations  by  a  constant  factor,  and  it  has  somewhat  better
numerical properties.

theoretically  correct,

in  practice

is

Exercises

28.2-1
Let M(n) be the time to multiply two n × n matrices, and let S(n) denote the
time required to square an n × n matrix. Show that multiplying and squaring
matrices  have  essentially  the  same  difficulty:  an  M(n)-time  matrix-
multiplication algorithm implies an O(M(n))-time squaring algorithm, and
implies  an  O(S(n))-time  matrix-
an  S(n)-time  squaring  algorithm
multiplication algorithm.

28.2-2
Let M(n) be the time to multiply two n × n matrices. Show that an M(n)-
time  matrix-multiplication  algorithm  implies  an  O(M(n))-time  LUP-
decomposition algorithm. (The LUP decomposition your method produces
need  not  be
the  LUP-
the
the  same  as
DECOMPOSITION procedure.)

result  produced  by

28.2-3
Let M(n) be the time to multiply two n × n boolean matrices, and let T(n)
be the time to find the transitive closure of an n × n boolean matrix. (See
Section  23.2.)  Show  that  an  M(n)-time  boolean  matrix-multiplication
algorithm implies an O(M(n) lg n)-time transitive-closure algorithm, and a

T(n)-time  transitive-closure  algorithm  implies  an  O(T  (n))-time  boolean
matrix-multiplication algorithm.

28.2-4
Does  the  matrix-inversion  algorithm  based  on  Theorem  28.2  work  when
matrix elements are drawn from the field of integers modulo 2? Explain.

★ 28.2-5
Generalize  the  matrix-inversion  algorithm  of  Theorem  28.2  to  handle
matrices  of  complex  numbers,  and  prove  that  your  generalization  works
correctly.  (Hint:  Instead  of  the  transpose  of  A,  use  the  conjugate
transpose A*, which you obtain from the transpose of A by replacing every
entry  with  its  complex  conjugate.  Instead  of  symmetric  matrices,  consider
Hermitian matrices, which are matrices A such that A = A*.)

28.3    Symmetric positive-definite matrices and least-squares

approximation

Symmetric  positive-definite  matrices  have  many  interesting  and  desirable
properties. An n × n matrix A is symmetric positive-definite if A = AT(A is
symmetric)  and  xTAx  >  0  for  all  n-vectors  x  ≠  0  (A  is  positive-definite).
Symmetric  positive-definite  matrices  are  nonsingular,  and  an  LU
decomposition on them will not divide by 0. This section proves these and
several  other  important  properties  of  symmetric  positive-definite  matrices.
We’ll also see an interesting application to curve fitting by a least-squares
approximation.

The first property we prove is perhaps the most basic.

Lemma 28.3
Any positive-definite matrix is nonsingular.

Proof   Suppose that a matrix A is singular. Then by Corollary D.3 on page
1221, there exists a nonzero vector x such that Ax = 0. Hence, xTAx = 0,
and A cannot be positive-definite.

▪

The  proof  that  an  LU  decomposition  on  a  symmetric  positive-definite
matrix  A  won’t  divide  by  0  is  more  involved.  We  begin  by  proving
properties about certain submatrices of A. Define the kth leading submatrix
of  A  to  be  the  matrix  Ak  consisting  of  the  intersection  of  the  first  k  rows
and first k columns of A.

Lemma 28.4
If  A  is  a  symmetric  positive-definite  matrix,  then  every  leading  submatrix
of A is symmetric and positive-definite.

Proof   Since A is symmetric, each leading submatrix Ak is also symmetric.
We’ll  prove  that  Ak  is  positive-definite  by  contradiction.  If  Ak  is  not
positive-definite, then there exists a k-vector xk ≠ 0 such that
. Let
A be n × n, and

for submatrices B (which is (n−k)×k) and C (which is (n−k)×(n−k)). Define
the n-vector

, where n − k 0s follow xk. Then we have

which contradicts A being positive-definite.

We now turn to some essential properties of the Schur complement. Let
A  be  a  symmetric  positive-definite  matrix,  and  let  Ak  be  a  leading  k  ×  k
submatrix  of  A.  Partition  A  once  again  according  to  equation  (28.16).

▪

Equation (28.10) generalizes to define the Schur complement S of A with
respect to Ak as

(By Lemma 28.4, Ak is symmetric and positive-definite, and therefore,
exists by Lemma 28.3, and S is well defined.) The earlier definition (28.10)
of the Schur complement is consistent with equation (28.17) by letting k =
1.

The  next  lemma  shows  that  the  Schur-complement  matrices  of
symmetric  positive-definite  matrices  are
themselves  symmetric  and
positive-definite. We used this result in Theorem 28.2, and its corollary will
help  prove  that  LU  decomposition  works  for  symmetric  positive-definite
matrices.

Lemma 28.5 (Schur complement lemma)
If  A  is  a  symmetric  positive-definite  matrix  and  Ak  is  a  leading  k  ×  k
submatrix  of  A,  then  the  Schur  complement  S  of  A  with  respect  to  Ak  is
symmetric and positive-definite.

Proof   Because A is symmetric, so is the submatrix C. By Exercise D.2-6
on  page  1223,  the  product
  are
symmetric, then by Exercise D.1-1 on page 1219, so is S.

  is  symmetric.  Since  C  and

It remains to show that S is positive-definite. Consider the partition of A
given in equation (28.16). For any nonzero vector x, we have xTAx > 0 by
the assumption that A is positive-definite. Let the subvectors y and z consist
of  the  first  k  and  last  n  −  k  elements  in  x,  respectively,  and  thus  they  are
compatible with Ak and C, respectively. Because

 exists, we have

This last equation, which you can verify by multiplying through, amounts to
“completing the square” of the quadratic form. (See Exercise 28.3-2.)

Since xTAx > 0 holds for any nonzero x, pick any nonzero z and then
, which causes the first term in equation (28.18) to vanish,

choose
leaving

as  the  value  of  the  expression.  For  any  z  ≠  0,  we  therefore  have  zTSz  =
xTAx > 0, and thus S is positive-definite.

▪

Corollary 28.6
LU  decomposition  of  a  symmetric  positive-definite  matrix  never  causes  a
division by 0.

Proof   Let A be an n × n symmetric positive-definite matrix. In fact, we’ll
prove  a  stronger  result  than  the  statement  of  the  corollary:  every  pivot  is
strictly positive. The first pivot is a11. Let e1 be the length-n unit vector ( 1
0 0 ⋯ 0 )T, so that
, which is positive because e1 is nonzero and
A is positive definite. Since the first step of LU decomposition produces the
Schur complement of A with respect to A1 = (a11), Lemma 28.5 implies by
induction that all pivots are positive.

▪

Least-squares approximation

One important application of symmetric positive-definite matrices arises in
fitting  curves  to  given  sets  of  data  points.  You  are  given  a  set  of  m  data
points
(x1, y1), (x2, y2), … , (xm, ym),
where you know that the yi are subject to measurement errors. You wish to
determine a function F(x) such that the approximation errors

are  small  for  i  =  1,  2,  …  ,  m. The  form  of  the  function  F  depends  on  the
problem  at  hand.  Let’s  assume  that  it  has  the  form  of  a  linearly  weighted
sum

where  the  number  n  of  summands  and  the  specific  basis  functions  fj  are
chosen  based  on  knowledge  of  the  problem  at  hand. A  common  choice  is
fj(x) = xj−1, which means that
F(x) = c1 + c2x + c3x2 + ⋯ + cnxn−1
is a polynomial of degree n − 1 in x. Thus, if you are given m data points
(x1, y1), (x2, y2), … , (xm, ym), you need to calculate n coefficients c1, c2,
… , cn that minimize the approximation errors η1, η2, … , ηm.

By  choosing  n  =  m,  you  can  calculate  each  yi  exactly  in  equation
(28.19).  Such  a  high-degree  polynomial  F  “fits  the  noise”  as  well  as  the
data, however, and generally gives poor results when used to predict y for
previously unseen values of x. It is usually better to choose n significantly
smaller than m and hope that by choosing the coefficients cj well, you can
obtain  a  function  F  that  finds  the  significant  patterns  in  the  data  points
without  paying  undue  attention  to  the  noise.  Some  theoretical  principles
exist for choosing n, but they are beyond the scope of this text. In any case,
once  you  choose  a  value  of  n  that  is  less  than  m,  you  end  up  with  an
overdetermined  set  of  equations  whose  solution  you  wish  to  approximate.
Let’s see how to do so.
Let

denote the matrix of values of the basis functions at the given points, that is,
aij = fj(xi). Let c = (ck) denote the desired n-vector of coefficients. Then,

is the m-vector of “predicted values” for y. Thus,

η = Ac − y

is the m-vector of approximation errors.

To minimize approximation errors, let’s minimize the norm of the error

vector η, which gives a least-squares solution, since

art

Because

art

to minimize ∥η∥, differentiate ∥η∥2 with respect to each ck and then set the
result to 0:

art
The  n  equations  (28.20)  for  k  =  1,  2,  …  ,  n  are  equivalent  to  the  single
matrix equation

(Ac − y)T A = 0

or, equivalently (using Exercise D.1-2 on page 1219), to

AT(Ac − y) = 0,

which implies

art

In  statistics,  equation  (28.21)  is  called  the  normal  equation.  The  matrix
ATA is symmetric by Exercise D.1-2, and if A has full column rank, then
by  Theorem  D.6  on  page  1222,  ATA  is  positive-definite  as  well.  Hence,
(ATA)−1 exists, and the solution to equation (28.21) is

art

where the matrix A+ = ((ATA)−1AT) is the pseudoinverse of the matrix A.
The  pseudoinverse  naturally  generalizes  the  notion  of  a  matrix  inverse  to
the  case  in  which  A  is  not  square.  (Compare  equation  (28.22)  as  the
approximate solution to Ac = y with the solution A−1b as the exact solution
to Ax = b.)

As  an  example  of  producing  a  least-squares  fit,  suppose  that  you  have

five data points

(x1, y1) = (−1, 2),
(x2, y2) = (1, 1),
(x3, y3) = (2, 1),
(x4, y4) = (3, 0),
(x5, y5) = (5, 3),

shown as orange dots in Figure 28.3, and you want to fit these points with a
quadratic polynomial
F(x) = c1 + c2x + c3x2.
Start with the matrix of basis-function values

art

whose pseudoinverse is

art

Figure 28.3 The least-squares fit of a quadratic polynomial to the set of five data points {(−1, 2), (1,
1), (2, 1), (3, 0), (5, 3)}. The orange dots are the data points, and the blue dots are their estimated
values  predicted  by  the  polynomial  F(x)  =  1.2  −  0.757x  +  0.214x2,  the  quadratic  polynomial  that
minimizes the sum of the squared errors, plotted in blue. Each orange line shows the error for one
data point.

art

Multiplying y by A+ gives the coefficient vector

art

which corresponds to the quadratic polynomial

F(x) = 1.200 − 0.757x + 0.214x2

as the closest-fitting quadratic to the given data, in a least-squares sense.

As  a  practical  matter,  you  would  typically  solve  the  normal  equation
(28.21) by multiplying y by AT and then finding an LU decomposition of
ATA. If A has full rank, the matrix ATA is guaranteed to be nonsingular,
because  it  is  symmetric  and  positive-definite.  (See  Exercise  D.1-2  and
Theorem D.6.)

art

Figure 28.4 A least-squares fit of a curve of the form

c1 + c2x + c3x2 + c4 sin(2πx) + c5 cos(2πx)

for the carbon-dioxide concentrations measured in Mauna Loa, Hawaii from 19901 to 2019, where x
is  the  number  of  years  elapsed  since  1990.  This  curve  is  the  famous  “Keeling  curve,”  illustrating
curve-fitting  to  nonpolynomial  formulas.  The  sine  and  cosine  terms  allow  modeling  of  seasonal
variations in CO2 concentrations. The red curve shows the measured CO2 concentrations. The best
fit, shown in black, has the form

352.83 + 1.39x + 0.02x2 + 2.83 sin(2πx) − 0.94 cos(2πx).

We close this section with an example in Figure 28.4, illustrating that a
curve can also fit a nonpolynomial function. The curve confirms one aspect
of climate change: that carbon dioxide (CO2) concentrations have steadily
increased over a period of 29 years. Linear and quadratic terms model the
annual increase, and sine and cosine terms model seasonal variations.

Exercises

28.3-1
Prove that every diagonal element of a symmetric positive-definite matrix is
positive.

28.3-2
Let
art  be  a  2  ×  2  symmetric  positive-definite  matrix.  Prove  that  its
determinant  ac  −  b2  is  positive  by  “completing  the  square”  in  a  manner
similar to that used in the proof of Lemma 28.5.

28.3-3
Prove  that  the  maximum  element  in  a  symmetric  positive-definite  matrix
lies on the diagonal.

28.3-4
Prove  that  the  determinant  of  each  leading  submatrix  of  a  symmetric
positive-definite matrix is positive.

28.3-5
Let  Ak  denote  the  kth  leading  submatrix  of  a  symmetric  positive-definite
matrix  A.  Prove  that  det(Ak)/det(Ak−1)  is  the  kth  pivot  during  LU
decomposition, where, by convention, det(A0) = 1.

28.3-6
Find the function of the form
F(x) = c1 + c2x lg x + c3ex
that is the best least-squares fit to the data points

(1, 1), (2, 1), (3, 3), (4, 8).

28.3-7
Show that the pseudoinverse A+ satisfies the following four equations:

AA+A = A,

A+AA+ = A+,
(AA+)T = AA+,
(A+A)T = A+A.

Problems

28-1     Tridiagonal systems of linear equations
Consider the tridiagonal matrix

art

a. Find an LU decomposition of A.

b. Solve the equation Ax = ( 1 1 1 1 1 )T by using forward and back

substitution.

c. Find the inverse of A.

d. Show how to solve the equation Ax = b for any n × n symmetric positive-

definite, tridiagonal matrix A and any n-vector b in O(n) time by
performing an LU decomposition. Argue that any method based on
forming A−1 is asymptotically more expensive in the worst case.
e. Show how to solve the equation Ax = b for any n × n nonsingular,

tridiagonal matrix A and any n-vector b in O(n) time by performing an
LUP decomposition.

28-2     Splines

A  practical  method  for  interpolating  a  set  of  points  with  a  curve  is  to  use
cubic splines. You are given a set {(xi, yi) : i = 0, 1, … , n} of n + 1 point-
value pairs, where x0 < x1 < ⋯ < xn. Your goal is to fit a piecewise-cubic
curve  (spline)  f(x)  to  the  points.  That  is,  the  curve  f(x)  is  made  up  of  n
cubic  polynomials  fi(x)  =  ai  +  bix  +  cix2  +  dix3  for  i  =  0,  1,  …  ,  n  −  1,
where  if  x  falls  in  the  range  xi  ≤  x  ≤  xi+1,  then  the  value  of  the  curve  is
given by f(x) = fi(x − xi). The points xi at which the cubic polynomials are
“pasted” together are called knots. For simplicity, assume that xi = i for i =
0, 1, … , n.

To ensure continuity of f(x), require that

= fi(0) = yi,

f(xi)
f(xi+1) = fi(1) = yi+1

for  i  =  0,  1,  …  ,  n  −  1.  To  ensure  that  f(x)  is  sufficiently  smooth,  also
require the first derivative to be continuous at each knot:

art

for i = 0, 1, … , n − 2.

a. Suppose that for i = 0, 1, … , n, in addition to the point-value pairs {(xi,

yi)}, you are also given the first derivative Di = f′(xi) at each knot.
Express each coefficient ai, bi, ci, and di in terms of the values yi, yi+1,
Di, and Di+1. (Remember that xi = i.) How quickly can you compute the
4n coefficients from the point-value pairs and first derivatives?

The  question  remains  of  how  to  choose  the  first  derivatives  of  f(x)  at  the
knots. One method is to require the second derivatives to be continuous at
the knots:

art

for  i  =  0,  1,  …  ,  n−2.  At  the  first  and  last  knots,  assume  that

art  and

. These assumptions make f(x) a natural cubic spline.

b. Use the continuity constraints on the second derivative to show that for i

= 1, 2, … , n − 1,

c. Show that

art

art

d. Rewrite equations (28.23)–(28.25) as a matrix equation involving the
vector D = (D0 D1 D2 ⋯ Dn)T of unknowns. What attributes does the
matrix in your equation have?

e. Argue that a natural cubic spline can interpolate a set of n + 1 point-value

pairs in O(n) time (see Problem 28-1).

f. Show how to determine a natural cubic spline that interpolates a set of n +

1 points (xi, yi) satisfying x0 < x1 < ⋯ < xn, even when xi is not
necessarily equal to i. What matrix equation must your method solve, and
how quickly does your algorithm run?

Chapter notes

Many excellent texts describe numerical and scientific computation in much
greater  detail  than  we  have  room  for  here.  The  following  are  especially
readable:  George  and  Liu  [180],  Golub  and  Van  Loan  [192],  Press,
Teukolsky, Vetterling, and Flannery [365, 366], and Strang [422, 423].

Golub and Van Loan [192] discuss numerical stability. They show why
det(A)  is  not  necessarily  a  good  indicator  of  the  stability  of  a  matrix  A,
proposing instead to use ∥A∥∞ ∥A−1∥∞, where
art. They also address
the question of how to compute this value without actually computing A−1.
Gaussian elimination, upon which the LU and LUP decompositions are
based,  was  the  first  systematic  method  for  solving  linear  systems  of

equations. It was also one of the earliest numerical algorithms. Although it
was  known  earlier,  its  discovery  is  commonly  attributed  to  C.  F.  Gauss
(1777–1855).  In  his  famous  paper  [424],  Strassen  showed  that  an  n×n
matrix can be inverted in O(nlg 7) time. Winograd [460] originally proved
that  matrix  multiplication  is  no  harder  than  matrix  inversion,  and  the
converse is due to Aho, Hopcroft, and Ullman [5].
important  matrix  decomposition

the  singular  value
decomposition, or SVD. The SVD factors an m × n matrix A into
art,
where Σ is an m×n matrix with nonzero values only on the diagonal, Q1 is
m×m  with  mutually  orthonormal  columns,  and  Q2  is  n  ×  n,  also  with
mutually orthonormal columns. Two vectors are orthonormal if their inner
product  is  0  and  each  vector  has  a  norm  of  1. The  books  by  Strang  [422,
423] and Golub and Van Loan [192] contain good treatments of the SVD.

Another

is

Strang [423] has an excellent presentation of symmetric positive-definite

matrices and of linear algebra in general.

1 The year in which Introduction to Algorithms was first published.

