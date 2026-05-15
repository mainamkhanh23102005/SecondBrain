symmetry, a R b implies b R a. Transitivity, therefore, implies a R a. Is
the professor correct?

B.3 Functions

Given  two  sets  A  and  B,  a  function  f  is  a  binary  relation  on  A  and  B
such that for all a ∈ A, there exists precisely one b ∈ B such that (a, b)
∈  f.  The  set  A  is  called  the  domain  of  f,  and  the  set  B  is  called  the
codomain of f. We sometimes write f : A → B, and if (a, b) ∈ f, we write
b = f (a), since the choice of a uniquely determines b.

Intuitively, the function f assigns an element of B to each element of
A.  No  element  of  A  is  assigned  two  different  elements  of  B,  but  the
same element of B can be assigned to two different elements of A. For
example, the binary relation

f = {(a, b) : a, b ∈ ℕ and b = a mod 2}
is  a  function  f  :  →  {0,  1},  since  for  each  natural  number  a,  there  is
exactly one value b in {0, 1} such that b = a mod 2. For this example, 0
= f (0), 1 = f (1), 0 = f (2), 1 = f (3), etc. In contrast, the binary relation

g = {(a, b) : a, b ∈ ℕ and a + b is even}
is not a function, since (1, 3) and (1, 5) are both in g, and thus for the
choice a = 1, there is not precisely one b such that (a, b) ∈ g.

Given a function f : A → B, if b = f (a), we say that a is the argument
of f and that b is the value of f at a. We can deﬁne a function by stating
its value for every element of its domain. For example, we might deﬁne f
(n) = 2n for n ∈ ℕ, which means f = {(n, 2n) : n ∈ ℕ}. Two functions f
and g are equal if they have the same domain and codomain and if f (a)
= g(a) for all a in the domain.

A ﬁnite sequence of length n is a function f whose domain is the set
of  n  integers  {0,  1,  …  ,  n  −  1}.  We  often  denote  a  ﬁnite  sequence  by
listing its values in angle brackets: 〈f (0), f (1), … , f (n−1)〉. An inﬁnite
sequence  is  a  function  whose  domain  is  the  set  ℕ  of  natural  numbers.
For  example,  the  Fibonacci  sequence,  deﬁned  by  recurrence  (3.31),  is
the inﬁnite sequence 〈0, 1, 1, 2, 3, 5, 8, 13, 21,…〉.

When  the  domain  of  a  function  f  is  a  Cartesian  product,  we  often
omit the extra parentheses surrounding the argument of f. For example,
if we have a function f : A1 × A2 × … An → B, we write b = f (a1, a2, …
an)  instead  of  writing  b  =  f  ((a1,  a2,  …  an)).  We  also  call  each  ai  an
argument  to  the  function  f,  though  technically  f  has  just  a  single
argument, which is the n-tuple (a1, a2, … an).

If f : A → B is a function and b = f (a), then we sometimes say that b
is the image of a under f. The image of a set A′ ⊆ A under f is deﬁned
by

f (A′) = {b ∈ B : b = f (a) for some a ∈ A′}.
The range of f is the image of its domain, that is, f (A). For example, the
range of the function f : ℕ → ℕ deﬁned by f (n) = 2n is f(ℕ) = {m : m =
2n  for  some  n  ∈  ℕ},  in  other  words,  the  set  of  nonnegative  even
integers.

A  function  is  a  surjection  if  its  range  is  its  codomain.  For  example,
the  function  f  (n)  =  ⌊n/2⌋  is  a  surjective  function  from  ℕ  to  ℕ,  since
every  element  in  ℕ  appears  as  the  value  of  f  for  some  argument.  In
contrast, the function f (n) = 2n is not a surjective function from ℕ to
ℕ,  since  no  argument  to  f  can  produce  any  odd  natural  number  as  a
value. The function f (n) = 2n is, however, a surjective function from the
natural  numbers  to  the  even  numbers.  A  surjection  f  :  A  →  B  is
sometimes described as mapping A onto B. When we say that f is onto,
we mean that it is surjective.

A  function  f  :  A  →  B  is  an  injection  if  distinct  arguments  to  f
produce  distinct  values,  that  is,  if  a  ≠  a′  implies  f  (a)  ≠  f  (a′).  For
example,  the  function  f  (n)  =  2n  is  an  injective  function  from  ℕ  to  ℕ,
since each even number b is the image under f of at most one element of
the domain, namely b/2. The function f (n) = ⌊n/2⌋ is not injective, since
the  value  1  is  produced  by  two  arguments:  f  (2)  =  1  and  f  (3)  =  1.  An
injection is sometimes called a one-to-one function.

A function f : A → B is a bijection if it is injective and surjective. For

example, the function f (n) = (−1)n

⌈n/2⌉ is a bijection from ℕ to ℤ:

0 → 0,
1 → −1,
2 → 1,
3 → −2,
4 → 2,

⋮

The  function  is  injective,  since  no  element  of  ℤ  is  the  image  of  more
than one element of ℕ. It is surjective, since every element of ℤ appears
as the image of some element of ℕ. Hence, the function is bijective. A
bijection is sometimes called a one-to-one correspondence, since it pairs
elements in the domain and codomain. A bijection from a set A to itself
is sometimes called a permutation.

When a function f is bijective, we deﬁne its inverse f−1 as

f −1(b) = a if and only if f (a) = b.
For example, the inverse of the function f (n) = (−1)n

⌈n/2⌉ is

Exercises

B.3-1
Let  A  and  B  be  ﬁnite  sets,  and  let  f  :  A  →  B  be  a  function.  Show  the
following:

a. If f is injective, then |A| ≤ |B|.

b. If f is surjective, then |A| ≥ |B|.

B.3-2
Is  the  function  f  (x)  =  x  +  1  bijective  when  the  domain  and  the
codomain  are  the  set  ℕ?  Is  it  bijective  when  the  domain  and  the
codomain are the set ℤ?

