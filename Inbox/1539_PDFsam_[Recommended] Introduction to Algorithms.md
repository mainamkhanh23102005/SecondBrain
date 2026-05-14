D Matrices

Matrices  arise  in  numerous  applications,  including,  but  by  no  means
limited to, scientiﬁc computing. If you have seen matrices before, much
of the material in this appendix will be familiar to you, but some of it
might  be  new.  Section  D.1  covers  basic  matrix  deﬁnitions  and
operations, and Section D.2 presents some basic matrix properties.

D.1 Matrices and matrix operations

This  section  reviews  some  basic  concepts  of  matrix  theory  and  some
fundamental properties of matrices.

Matrices and vectors

A matrix is a rectangular array of numbers. For example,

is a 2 × 3 matrix A = (aij), where for i = 1, 2 and j = 1, 2, 3, the element
of  the  matrix  in  row  i  and  column  j  is  denoted  by  aij.  By  convention,
uppercase
letters  denote  matrices  and  corresponding  subscripted
lowercase letters denote their elements. We denote the set of all m × n

matrices with real-valued entries by ℝ
× n matrices with entries drawn from a set S by Sm×n.

m×n and, in general, the set of m

The  transpose  of  a  matrix  A  is  the  matrix  AT  obtained  by
exchanging  the  rows  and  columns  of  A.  For  the  matrix  A  of  equation
(D.1),

A vector is a one-dimensional array of numbers. For example,

is a vector of size 3. We sometimes call a vector of length n an n-vector.
By convention, lowercase letters denote vectors, and the ith element of a
size-n vector x is denoted by xi, for i = 1, 2, … , n. We take the standard
form of a vector to be as a column vector equivalent to an n × 1 matrix,
whereas  the  corresponding  row  vector  is  obtained  by  taking  the
transpose:

xT = ( 2 3 5 ).

The unit vector ei is the vector whose ith element is 1 and all of whose
other  elements  are  0.  Usually,  the  context  makes  the  size  of  a  unit
vector clear.

A zero matrix is a matrix all of whose entries are 0. Such a matrix is
often  denoted  0,  since  the  ambiguity  between  the  number  0  and  a
matrix of 0s can usually be resolved from context. If a matrix of 0s is
intended, then the size of the matrix also needs to be derived from the
context.

Square matrices

Square  n  ×  n  matrices  arise  frequently.  Several  special  cases  of  square
matrices are of particular interest:

1. A diagonal matrix has aij = 0 whenever i ≠ j. Because all of the off-

diagonal elements are 0, a succinct way to specify the matrix lists only
the elements along the diagonal:

2. The n × n identity matrix In is a diagonal matrix with 1s along the

diagonal:

When I appears without a subscript, its size derives from the context.
The ith column of an identity matrix is the unit vector ei.

3. A tridiagonal matrix T is one for which tij = 0 if |i − j | > 1. Nonzero

entries appear only on the main diagonal, immediately above the main
diagonal (ti,i+1 for i = 1, 2, … , n − 1), or immediately below the main
diagonal (ti+1,i for i = 1, 2, … , n − 1):

4. An upper-triangular matrix U is one for which uij = 0 if i > j. All

entries below the diagonal are 0:

An upper-triangular matrix is unit upper-triangular if it has all 1s
along the diagonal.

5. A lower-triangular matrix L is one for which lij = 0 if i < j. All entries

above the diagonal are 0:

A lower-triangular matrix is unit lower-triangular if it has all 1s along
the diagonal.

6. A permutation matrix P has exactly one 1 in each row or column, and

0s elsewhere. An example of a permutation matrix is

Such a matrix is called a permutation matrix because multiplying a
vector x by a permutation matrix has the effect of permuting
(rearranging) the elements of x. Exercise D.1-4 explores additional
properties of permutation matrices.

7. A symmetric matrix A satisﬁes the condition A = AT. For example,

is a symmetric matrix.

Basic matrix operations

The  elements  of  a  matrix  or  vector  are  scalar  numbers  from  a  number
system,  such  as  the  real  numbers,  the  complex  numbers,  or  integers
modulo  a  prime.  The  number  system  deﬁnes  how  to  add  and  multiply
to  encompass  addition  and
scalars.  These  deﬁnitions  extend
multiplication of matrices.

We deﬁne matrix addition as follows. If A = (aij) and B = (bij) are m
×  n  matrices,  then  their  matrix  sum  C  =  (cij)  =  A  +  B  is  the  m  ×  n
matrix deﬁned by

cij = aij + bij

for  i  =  1,  2,  …  ,  m  and  j  =  1,  2,  …  ,  n.  That  is,  matrix  addition  is
performed  componentwise.  A  zero  matrix  is  the  identity  for  matrix
addition:

A + 0 = A = 0 + A.

If is λ a scalar number and A = (aij) is a matrix, then λA = (λaij) is
the scalar multiple of A obtained by multiplying each of its elements by
λ. As a special case, we deﬁne the negative of a matrix A = (aij) to be −1
· A = −A, so that the ijth entry of −A is −aij. Thus,

A + (−A) = 0 = (−A) + A.

The negative of a matrix deﬁnes matrix subtraction: A − B = A + (−B).

We deﬁne matrix multiplication as follows. Start with two matrices A
and B that are compatible in the sense that the number of columns of A
equals the number of rows of B. (In general, an expression containing a
matrix  product  AB  is  always  assumed  to  imply  that  matrices  A  and  B
are compatible.) If A = (aik) is a p × q matrix and B = (bkj) is a q × r
matrix, then their matrix product C = AB is the p × r matrix C = (cij),
where

for  i  =  1,  2,  …  ,  m  and  j  =  1,  2,  …  ,  p.  The  procedure
RECTANGULAR-MATRIX-MULTIPLY  on  page  374  implements
matrix multiplication in the straightforward manner based on equation
(D.2), assuming that C is initialized to 0, using pqr multiplications and
p(q − 1)r additions for a running time of Θ(pqr). If the matrices are n×n
square  matrices,  so  that  n  =  p  =  q  =  r,  the  pseudocode  reduces  to
MATRIX-MULTIPLY  on  page  81,  whose  running  time  is  Θ(n3).

(Section  4.2  describes  an  asymptotically  faster  Θ(nlg7)-time  algorithm
due to V. Strassen.)

Matrices have many (but not all) of the algebraic properties typical

of numbers. Identity matrices are identities for matrix multiplication:

ImA = AIn = A

for  any  m  ×  n  matrix  A.  Multiplying  by  a  zero  matrix  gives  a  zero
matrix:

A · 0 = 0.

Matrix multiplication is associative:

A(BC) = (AB)C

for  compatible  matrices  A,  B,  and  C.  Matrix  multiplication  distributes
over addition:

A(B + C) = AB + AC,
(B + C)D = BD + CD.

For  n  >  1,  multiplication  of  n  ×  n  matrices  is  not  commutative.  For

 and

example, if

, then
We deﬁne matrix-vector products or vector-vector products as if the
vector were the equivalent n × 1 matrix (or a 1 × n matrix, in the case of
a row vector). Thus, if A is an m × n matrix and x is an n-vector, then
Ax is an m-vector. If x and y are n-vectors, then

 and

.

is a scalar number (actually a 1 × 1 matrix) called the inner product of x
and y. We also use the notation 〈x, y〉 to denote xTy. The inner-product
operator  is  commutative:  〈x,  y〉  =  〈y,  x〉.  The  matrix  xyT  is  an  n  ×  n
matrix  Z  called  the  outer  product  of  x  and  y,  where  zij  =  xiyj.  The
(euclidean) norm ∥x∥ of an n-vector x is deﬁned by

