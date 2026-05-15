32        String Matching

Text-editing  programs  frequently  need  to  ﬁnd  all  occurrences  of  a
pattern  in  the  text.  Typically,  the  text  is  a  document  being  edited,  and
the  pattern  searched  for  is  a  particular  word  supplied  by  the  user.
Efﬁcient  algorithms  for  this  problem—called  “string  matching”—can
greatly aid the responsiveness of the text-editing program. Among their
many  other  applications,  string-matching  algorithms  search  for
particular patterns in DNA sequences. Internet search engines also use
them to ﬁnd web pages relevant to queries.

The string-matching problem can be stated formally as follows. The
text is given as an array T[1 : n] of length n, and the pattern is an array
P[1 : m] of length m ≤ n. The elements of P and T are characters drawn
from  an  alphabet  ∑,  which  is  a  ﬁnite  set  of  characters.  For  example,  ∑
could  be  the  set  {0,  1},  or  it  could  be  the  set  {a,  b,  …,  z}.  The
character arrays P and T are often called strings of characters.

As  Figure  32.1  shows,  pattern  P  occurs  with  shift  s  in  text  T  (or,
equivalently, that pattern P occurs beginning at position s + 1 in text T)
if 0 ≤ s ≤ n – m and T[s + 1:s + m] = P[1:m], that is, if T[s + j] = P[j], for
1  ≤  j  ≤  m.  If  P  occurs  with  shift  s  in  T,  then  s  is  a  valid  shift,  and
otherwise,  s  is  an  invalid  shift.  The  string-matching  problem  is  the
problem of ﬁnding all valid shifts with which a given pattern P occurs in
a given text T.

Figure 32.1 An example of the string-matching problem to ﬁnd all occurrences of the pattern P
= abaa in the text T = abcabaabcabac. The pattern occurs only once in the text, at shift s =
3, which is a valid shift. A vertical line connects each character of the pattern to its matching
character in the text, and all matched characters are shaded blue.

Except  for  the  naive  brute-force  algorithm  in  Section  32.1,  each
string-matching algorithm in this chapter performs some preprocessing
based  on  the  pattern  and  then  ﬁnds  all  valid  shifts.  We  call  this  latter
phase  “matching.”  Here  are  the  preprocessing  and  matching  times  for
each  of  the  string-matching  algorithms  in  this  chapter.  The  total
running  time  of  each  algorithm  is  the  sum  of  the  preprocessing  and
matching times:

Algorithm
Naive
Rabin-Karp
Finite automaton
Knuth-Morris-Pratt
Sufﬁx array1

Preprocessing time Matching time
O((n – m + 1)m)
O((n – m + 1)m)
Θ(n)
Θ(n)
O(m 1g n + km)

0
Θ(m)
O(m |∑|)
Θ(m)
O(n 1g n)

Section  32.2  presents  an  interesting  string-matching  algorithm,  due  to
Rabin and Karp. Although the Θ((n – m + 1)m) worst-case running time
of  this  algorithm  is  no  better  than  that  of  the  naive  method,  it  works
much  better  on  average  and  in  practice.  It  also  generalizes  nicely  to
other  pattern-matching  problems.  Section  32.3  then  describes  a  string-
matching  algorithm  that  begins  by  constructing  a  ﬁnite  automaton
speciﬁcally designed to search for occurrences of the given pattern P in
a text. This algorithm takes O(m |∑|) preprocessing time, but only Θ(n)
matching  time.  Section  32.4  presents  the  similar,  but  much  cleverer,
Knuth-Morris-Pratt  (or  KMP)  algorithm,  which  has  the  same  Θ(n)
matching time, but it reduces the preprocessing time to only Θ(m).

A  completely  different  approach  appears  in  Section  32.5,  which
examines  sufﬁx  arrays  and  the  longest  common  preﬁx  array.  You  can

use these arrays not only to ﬁnd a pattern in a text, but also to answer
other  questions,  such  as  what  is  the  longest  repeated  substring  in  the
text and what is the longest common substring between two texts. The
algorithm to form the sufﬁx array in Section 32.5 takes O(n 1g n) time
and,  given  the  sufﬁx  array,  the  section  shows  how  to  compute  the
longest common preﬁx array in O(n) time.

Notation and terminology

We  denote  by  ∑*  (read  “sigma-star”)  the  set  of  all  ﬁnite-length  strings
formed  using  characters  from  the  alphabet  ∑.  This  chapter  considers
only  ﬁnite-length  strings.  The  0-length  empty  string,  denoted  ϵ,  also
belongs to ∑*. The length of a string x is denoted |x|. The concatenation
of two strings x and y, denoted xy, has length |x| + |y| and consists of
the characters from x followed by the characters from y.

Figure 32.2 A graphical proof of Lemma 32.1. Suppose that x ⊐ z and y ⊐ z. The three parts of
the ﬁgure illustrate the three cases of the lemma. Vertical lines connect matching regions (shown
in blue) of the strings. (a) If |x| ≤ |y|, then x ⊐ y. (b) If |x| ≥ |y|, then y ⊐ x. (c) If |x| = |y|, then x
= y.

A string w is a preﬁx of a string x, denoted w ⊏ x, if x = wy for some
string y ∈ ∑*. Note that if w ⊏ x, then |w| ≤ |x|. Similarly, a string w is a
sufﬁx of a string x, denoted w ⊐ x, if x = yw for some y ∈ ∑*. As with a
preﬁx,  w  ⊐  x  implies  |w|  ≤  |x|.  For  example,  ab  ⊏  abcca  and  cca  ⊐

abcca.  A  string  w  is  a  proper  preﬁx  of  x  if  w  ⊏  x  and  |w|  <  |x|,  and
likewise  for  a  proper  sufﬁx.  The  empty  string  ϵ  is  both  a  sufﬁx  and  a
preﬁx of every string. For any strings x and y and any character a, we
have x ⊐ y if and only if xa ⊐ ya. The ⊏ and ⊐ relations are transitive.
The following lemma will be useful later.

Lemma 32.1 (Overlapping-sufﬁx lemma)
Suppose that x, y, and z are strings such that x ⊐ z and y ⊐ z. If |x| ≤
|y|, then x ⊐ y. If |x| ≥ |y|, then y ⊐ x. If |x| = |y|, then x = y.

Proof   See Figure 32.2 for a graphical proof.

▪

For convenience, denote the k-character preﬁx P[1:k] of the pattern
P[1:m] by P[:k]. Thus, we can write P[:0] = ϵ and P[:m] = P = P[1:m].
Similarly, denote the k-character preﬁx of the text T by T[:k]. Using this
notation, we can state the string-matching problem as that of ﬁnding all
shifts s in the range 0 ≤ s ≤ n – m such that P ⊐ T[:s + m].

Our pseudocode allows two equal-length strings to be compared for
equality as a primitive operation. If the strings are compared from left
to  right  and  the  comparison  stops  when  a  mismatch  is  discovered,  we
assume  that  the  time  taken  by  such  a  test  is  a  linear  function  of  the
number of matching characters discovered. To be precise, the test “x ==
y”  is  assumed  to  take  Θ(t)  time,  where  t  is  the  length  of  the  longest
string z such that z ⊏ x and z ⊏ y.

32.1    The naive string-matching algorithm

The  NAIVE-STRING-MATCHER  procedure  ﬁnds  all  valid  shifts
using a loop that checks the condition P[1:m] = T[s+1:s+m] for each of
the n−m+1 possible values of s.

NAIVE-STRING-MATCHER(T, P, n, m)
1 for s = 0 to n – m
2

if P[1:m] == T[s + 1:s + m]

3

print “Pattern occurs with shift” s

Figure 32.3 portrays the naive string-matching procedure as sliding a
“template” containing the pattern over the text, noting for which shifts
all of the characters on the template equal the corresponding characters
in  the  text.  The  for  loop  of  lines  1–3  considers  each  possible  shift
explicitly. The test in line 2 determines whether the current shift is valid.
This  test  implicitly  loops  to  check  corresponding  character  positions
until  all  positions  match  successfully  or  a  mismatch  is  found.  Line  3
prints out each valid shift s.

n  (a  string  of  na’s)  and  the  pattern  a

Procedure  NAIVE-STRING-MATCHER  takes  O((n  –  m  +  1)m)
time, and this bound is tight in the worst case. For example, consider the
m.  For  each  of  the
text  string  a
n−m+1  possible  values  of  the  shift  s,  the  implicit  loop  on  line  2  to
compare corresponding characters must execute m times to validate the
shift.  The  worst-case  running  time  is  thus  Θ((n  −  m  +  1)m),  which  is
Θ(n2)  if  m  =  ⌊n/2⌋.  Because  it  requires  no  preprocessing,  NAIVE-
STRING-MATCHER’s running time equals its matching time.

NAIVE-STRING-MATCHER is far from an optimal procedure for
this  problem.  Indeed,  this  chapter  will  show  that  the  Knuth-Morris-
Pratt  algorithm  is  much  better  in  the  worst  case.  The  naive  string-
matcher  is  inefﬁcient  because  it  entirely  ignores  information  gained
about  the  text  for  one  value  of  s  when  it  considers  other  values  of  s.
Such  information  can  be  quite  valuable,  however.  For  example,  if  P  =
aaab and s = 0 is valid, then none of the shifts 1, 2, or 3 are valid, since
T[4] = b. The following sections examine several ways to make effective
use of this sort of information.

Figure 32.3 The operation of the NAIVE-STRING-MATCHER procedure for the pattern P =
aab and the text T = acaabc. Imagine the pattern P as a template that slides next to the text.
(a)–(d)  The  four  successive  alignments  tried  by  the  naive  string  matcher.  In  each  part,  vertical
lines  connect  corresponding  regions  found  to  match  (shown  in  blue),  and  a  red  jagged  line
connects the ﬁrst mismatched character found, if any. The algorithm ﬁnds one occurrence of the
pattern, at shift s = 2, shown in part (c).

Exercises

32.1-1
Show the comparisons the naive string matcher makes for the pattern P
= 0001 in the text T = 000010001010001.

32.1-2
Suppose that all characters in the pattern P are different. Show how to
accelerate NAIVE-STRING-MATCHER to run in O(n) time on an n-
character text T.

32.1-3
Suppose that pattern P and text T are randomly chosen strings of length
m  and  n,  respectively,  from  the  d-ary  alphabet  ∑d  =  {0,  1,  …,  d  –  1},
where  d  ≥  2.  Show  that  the  expected  number  of  character-to-character
comparisons made by the implicit loop in line 2 of the naive algorithm
is

over all executions of this loop. (Assume that the naive algorithm stops
comparing  characters  for  a  given  shift  once  it  ﬁnds  a  mismatch  or
matches  the  entire  pattern.)  Thus,  for  randomly  chosen  strings,  the
naive algorithm is quite efﬁcient.

32.1-4
Suppose that the pattern P may contain occurrences of a gap character
♢   that  can  match  an  arbitrary  string  of  characters  (even  one  of  0
length).  For  example,  the  pattern  ab ♢ ba ♢ c  occurs  in  the  text
cabccbacbacab as

and as

The  gap  character  may  occur  an  arbitrary  number  of  times  in  the
pattern but not at all in the text. Give a polynomial-time algorithm to
determine  whether  such  a  pattern  P  occurs  in  a  given  text  T,  and
analyze the running time of your algorithm.

32.2    The Rabin-Karp algorithm

Rabin  and  Karp  proposed  a  string-matching  algorithm  that  performs
well in practice and that also generalizes to other algorithms for related
problems, such as two-dimensional pattern matching. The Rabin-Karp
algorithm uses Θ(m) preprocessing time, and its worst-case running time
is  Θ((n−m+1)m).  Based  on  certain  assumptions,  however,  its  average-
case running time is better.

This  algorithm  makes  use  of  elementary  number-theoretic  notions
such  as  the  equivalence  of  two  numbers  modulo  a  third  number.  You
might want to refer to Section 31.1 for the relevant deﬁnitions.

For  expository  purposes,  let’s  assume  that  ∑  =  {0,  1,  2,  …,  9},  so
that  each  character  is  a  decimal  digit.  (In  the  general  case,  you  can
assume that each character is a digit in radix-d notation, so that it has a
numerical  value  in  the  range  0  to  d  –  1,  where  d  =  |∑|.)  You  can  then
view  a  string  of  k  consecutive  characters  as  representing  a  length-k
decimal number. For example, the character string 31415 corresponds
to the decimal number 31,415. Because we interpret the input characters

as both graphical symbols and digits, it will be convenient in this section
to denote them as digits in standard text font.

Given a pattern P[1:m], let p denote its corresponding decimal value.
In a similar manner, given a text T[1:n], let ts denote the decimal value
of  the  length-m  substring  T[s  +  1:s  +  m],  for  s  =  0,  1,  …,  n  –  m.
Certainly, ts = p if and only if T [s + 1:s + m] = P[1:m], and thus, s is a
valid  shift  if  and  only  if  ts  =  p.  If  you  could  compute  p  in  Θ(m)  time
and  all  the  ts  values  in  a  total  of  Θ(n  –  m  +  1)  time,2  then  you  could
determine  all  valid  shifts  s  in  Θ(m)+Θ(n  −  m  +  1)  =  Θ(n)  time  by
comparing p with each of the ts values. (For the moment, let’s not worry
about  the  possibility  that  p  and  the  ts  values  might  be  very  large
numbers.)

Indeed,  you  can  compute  p  in  Θ(m)  time  using  Horner’s  rule  (see

Problem 2-3):

Similarly, you can compute t0 from T[1:m] in Θ(m) time.

To compute the remaining values t1, t2, …, tn–m in Θ(n – m) time,

observe that you can compute ts+1 from ts in constant time, since

Subtracting  10m−1T  [s  +  1]  removes  the  high-order  digit  from  ts,
multiplying the result by 10 shifts the number left by one digit position,
and adding T[s + m + 1] brings in the appropriate low-order digit. For
example, suppose that m = 5, ts = 31415, and the new low-order digit is
T[s + 5 + 1] = 2. The high-order digit to remove is T[s + 1] = 3, and so

ts+1 = 10 (31415 − 10000 · 3) + 2

= 14152.

If you precompute the constant 10m−1 (which you can do in O(1g m)
time using the techniques of Section 31.6, although for this application

a  straightforward  O(m)-time  method  sufﬁces),  then  each  execution  of
equation (32.1) takes a constant number of arithmetic operations. Thus,
you can compute p in Θ(m) time, and you can compute all of t0, t1, …,
tn−m in Θ(n −  m + 1) time. Therefore, you can ﬁnd all occurrences of
the pattern P[1:m] in the text T[1: n] with Θ(m) preprocessing time and
Θ(n − m + 1) matching time.

This  scheme  works  well  if  P  is  short  enough  and  the  alphabet  ∑  is
small enough that arithmetic operations on p and ts take constant time.
But what if P is long, or if the size of ∑ means that instead of powers of
10 in equation (32.1) you have to use powers of a larger number (such
as powers of 256 for the extended ASCII character set)? Then the values
of  p  and  ts  might  be  too  large  to  work  with  in  constant  time.
Fortunately, this problem can be solved, as Figure 32.4 shows: compute
p  and  the  ts  values  modulo  a  suitable  modulus  q.  You  can  compute  p
modulo q in Θ(m) time and all the ts values modulo q in Θ(n − m + 1)
time.  With  |∑|  =  10,  if  you  choose  the  modulus  q  as  a  prime  such  that
10q  just  ﬁts  within  one  computer  word,  then  you  can  perform  all  the
necessary  computations  with  single-precision  arithmetic.  In  general,
with a d-ary alphabet {0, 1, …, d – 1}, choose q so that dq ﬁts within a
computer  word  and  adjust  the  recurrence  equation  (32.1)  to  work
modulo q, so that it becomes

Figure 32.4 The Rabin-Karp algorithm. Each character is a decimal digit. Values are computed
modulo 13. (a) A text string. A window of length 5 is shaded blue. The numerical value of the
blue  number,  computed  modulo  13,  yields  the  value  7.  (b)  The  same  text  string  with  values
computed modulo 13 for each possible position of a length-5 window. Assuming the pattern P
=  31415,  look  for  windows  whose  value  modulo  13  is  7,  since  31415  =  7  (mod  13).  The
algorithm ﬁnds two such windows, shaded blue in the ﬁgure. The ﬁrst, beginning at text position
7, is indeed an occurrence of the pattern. The second window, beginning at text position 13, is a
spurious hit. (c) How to compute the value for a window in constant time, given the value for
the  previous  window.  The  ﬁrst  window  has  value  31415.  Dropping  the  high-order  digit  3,
shifting  left  (multiplying  by  10),  and  then  adding  in  the  low-order  digit  2  gives  the  new  value
14152. Because all computations are performed modulo 13, the value for the ﬁrst window is 7,
and the value for the new window is 8.

where  h  =  dm−1  mod  q  is  the  value  of  the  digit  “1”  in  the  high-order
position of an m-digit text window.

The  solution  of  working  modulo  q  is  not  perfect,  however:  ts  =  p
(mod q) does not automatically mean that ts = p. On the other hand, if
ts  ≠  p  (mod  q),  then  you  deﬁnitely  know  that  ts  ≠  p,  so  that  shift  s  is
invalid. Thus you can use the test ts = p (mod q) as a fast heuristic test
to rule out invalid shifts. If ts = p (mod q)—a hit—then you need to test
further  to  see  whether  s  is  really  valid  or  you  just  have  a  spurious  hit.
This additional test explicitly checks the condition P[1:m] = T[s + 1:s +
m]. If q is large enough, then you would hope that spurious hits occur
infrequently enough that the cost of the extra checking is low.

The procedure RABIN-KARP-MATCHER on the next page makes
these  ideas  precise.  The  inputs  to  the  procedure  are  the  text  T,  the
pattern  P,  their  lengths  n  and  m,  the  radix  d  to  use  (which  is  typically
taken to be |∑|), and the prime q to use. The procedure works as follows.
All characters are interpreted as radix-d digits. The subscripts on t are
provided  only  for  clarity:  the  procedure  works  correctly  if  all  the
subscripts  are  dropped.  Line  1  initializes  h  to  the  value  of  the  high-
order digit position of an m-digit window. Lines 2–6 compute p as the
value of P[1:m] mod q and t0 as the value of T[1:m] mod q. The for loop
of  lines  7–12  iterates  through  all  possible  shifts  s,  maintaining  the
following invariant:

Whenever line 8 is executed, ts = T[s + 1:s + m] mod q.

If a hit occurs because p = ts in line 8, then line 9 determines whether s
is  a  valid  shift  or  the  hit  was  spurious  via  the  test  P[1:m]  ==  T[s  +1:s
+m].  Line  10  prints  out  any  valid  shifts  that  are  found.  If  s  <  n  –  m
(checked in line 11), then the for loop will iterate at least one more time,
and so line 12 ﬁrst executes to ensure that the loop invariant holds upon
the next iteration. Line 12 computes the value of ts+1 mod q from the
value of ts mod q in constant time using equation (32.2) directly.

RABIN-KARP-MATCHER takes Θ(m) preprocessing time, and its
matching time is Θ((n − m + 1)m) in the worst case, since (like the naive
string-matching algorithm) the Rabin-Karp algorithm explicitly veriﬁes

every  valid  shift.  If  P  =  a
Θ((n−m+1)m) time, since each of the n−m+1 possible shifts is valid.

m  and  T  =  a

n,  then  verifying  takes

In  many  applications,  you  expect  few  valid  shifts—perhaps  some
constant c of them. In such applications, the expected matching time of
the algorithm is only O((n−m+1)+cm) = O(n+m), plus the time required
to  process  spurious  hits.  We  can  base  a  heuristic  analysis  on  the
assumption that reducing values modulo q acts like a random mapping
from  ∑*  to  ℤq.  The  expected  number  of  spurious  hits  is  then  O(n/q),
because  we  can  estimate  the  chance  that  an  arbitrary  ts  will  be
equivalent  to  p,  modulo  q,  as  1/q.  Since  there  are  O(n)  positions  at
which the test of line 8 fails (actually, at most n − m + 1 positions) and
checking each hit takes O(m) time in line 9, the expected matching time
taken by the Rabin-Karp algorithm is

RABIN-KARP-MATCHER(T, P, n, m, d, q)
  1 h = dm−1 mod q
  2 p = 0
  3 t0 = 0
  4 for i = 1 to m
  5

p = (dp + P[i]) mod q
t0 = (dt0 + T[i]) mod q

  6
  7 for s = 0 to n – m

// preprocessing

if p == ts

if  P[1:m]  ==  T[s  +  1:s  +

m]
print “Pattern occurs with shift” s

if s < n – m

  8

  9

10

11

12

//  matching—try  all  possible
shifts
// a hit?
// valid shift?

O(n) + O(m(v + n/q)),

where  v  is  the  number  of  valid  shifts.  This  running  time  is  O(n)  if  v  =
O(1)  and  you  choose  q  ≥  m.  That  is,  if  the  expected  number  of  valid

shifts is small (O(1)) and you choose the prime q to be larger than the
length of the pattern, then you can expect the Rabin-Karp procedure to
use only O(n + m) matching time. Since m ≤ n, this expected matching
time is O(n).

Exercises

32.2-1
Working modulo q = 11, how many spurious hits does the Rabin-Karp
matcher encounter in the text T = 3141592653589793 when looking for
the pattern P = 26?

32.2-2
Describe  how  to  extend  the  Rabin-Karp  method  to  the  problem  of
searching a text string for an occurrence of any one of a given set of k
patterns.  Start  by  assuming  that  all  k  patterns  have  the  same  length.
Then  generalize  your  solution  to  allow  the  patterns  to  have  different
lengths.

32.2-3
Show how to extend the Rabin-Karp method to handle the problem of
looking for a given m × m pattern in an n × n array of characters. (The
pattern  may  be  shifted  vertically  and  horizontally,  but  it  may  not  be
rotated.)

32.2-4
Alice has a copy of a long n-bit ﬁle A = 〈an–1, an–2, …, a0〉, and Bob
similarly has an n-bit ﬁle B = 〈bn–1, bn–2, …, b0〉. Alice and Bob wish
to know if their ﬁles are identical. To avoid transmitting all of A or B,
they  use  the  following  fast  probabilistic  check.  Together,  they  select  a
prime q > 1000n and randomly select an integer x from {0, 1, …, q – 1}.
Letting

Alice evaluates A(x) and Bob evaluates B(x). Prove that if A ≠ B, there
is at most one chance in 1000 that A(x) = B(x), whereas if the two ﬁles
are  the  same,  A(x)  is  necessarily  the  same  as  B(x).  (Hint:  See  Exercise
31.4-4.)

32.3    String matching with ﬁnite automata

Many  string-matching  algorithms  build  a  ﬁnite  automaton—a  simple
machine for processing information—that scans the text string T for all
occurrences  of  the  pattern  P.  This  section  presents  a  method  for
building  such  an  automaton.  These  string-matching  automata  are
efﬁcient: they examine each text character exactly once, taking constant
time  per  text  character.  The  matching  time  used—after  preprocessing
the pattern to build the automaton—is therefore Θ(n). The time to build
the automaton, however, can be large if ∑ is large. Section 32.4 describes
a clever way around this problem.

We  begin  this  section  with  the  deﬁnition  of  a  ﬁnite  automaton.  We
then examine a special string-matching automaton and show how to use
it  to  ﬁnd  occurrences  of  a  pattern  in  a  text.  Finally,  we’ll  see  how  to
construct the string-matching automaton for a given input pattern.

Finite automata

A ﬁnite automaton M, illustrated in Figure 32.5, is a 5-tuple (Q, q0, A, ∑,
δ), where

Q is a ﬁnite set of states,
q0 ∈ Q is the start state,
A ⊆ Q is a distinguished set of accepting states,
∑ is a ﬁnite input alphabet,
δ is a function from Q × ∑ into Q, called the transition function of
M.

Figure 32.5 A simple two-state ﬁnite automaton with state set Q = {0, 1}, start state q0 = 0, and
input  alphabet  ∑  =  {a,  b}.  (a)  A  tabular  representation  of  the  transition  function  δ.  (b)  An
equivalent state-transition diagram. State 1, in orange, is the only accepting state. Directed edges
represent transitions. For example, the edge from state 1 to state 0 labeled b indicates that δ(1, b)
= 0. This automaton accepts those strings that end in an odd number of a’s. More precisely, it
k, where k is
accepts a string x if and only if x = yz, where y = ϵ or y ends with a b, and z = a
odd. For example, on input abaaa, including the start state, this automaton enters the sequence
of states 〈0, 1, 0, 1, 0, 1〉, and so it accepts this input. For input abbaa, it enters the sequence of
states 〈0, 1, 0, 0, 1, 0〉, and so it rejects this input.

The ﬁnite automaton begins in state q0 and reads the characters of
its  input  string  one  at  a  time.  If  the  automaton  is  in  state  q  and  reads
input character a, it moves (“makes a transition”) from state q to state
δ(q, a). Whenever its current state q is a member of A, the machine M
has  accepted  the  string  read  so  far.  An  input  that  is  not  accepted  is
rejected.

A  ﬁnite  automaton  M  induces  a  function  ϕ,  called  the  ﬁnal-state
function,  from  ∑*  to  Q  such  that  ϕ(w)  is  the  state  M  ends  up  in  after
reading the string w. Thus, M accepts a string w if and only if ϕ(w) ∈
A. We deﬁne the function ϕ recursively, using the transition function:

ϕ(ϵ) = q0,
ϕ(wa) = δ(ϕ(w), a) for w ∈ ∑*, a ∈ ∑.

String-matching automata

For a given pattern P, a preprocessing step constructs a string-matching
automaton  speciﬁc  to  P.  The  automaton  then  searches  the  text  string
for  occurrences  of  P.  Figure  32.6  illustrates  the  automaton  for  the
pattern P = ababaca. From now on, let’s assume that P is ﬁxed, and

for  brevity,  we  won’t  bother  to  indicate  the  dependence  upon  P  in  our
notation.

In order to specify the string-matching automaton corresponding to
a given pattern P[1:m], we ﬁrst deﬁne an auxiliary function σ, called the
sufﬁx function corresponding to the pattern P. The function σ maps ∑*
to  {0,  1,  …,  m}  such  that  σ(x)  is  the  length  of  the  longest  preﬁx  of  P
that is also a sufﬁx of x:

Figure  32.6  (a)  A  state-transition  diagram  for  the  string-matching  automaton  that  accepts  all
strings ending in the string ababaca. State 0 is the start state, and state 7 (in orange) is the only
accepting state. The transition function δ is deﬁned by equation (32.4), and a directed edge from
state i to state j labeled a represents δ(i, a) = j. The right-going edges forming the “spine” of the
automaton,  shown  in  blue,  correspond  to  successful  matches  between  pattern  and  input
characters. Except for the edges from state 7 to states 1 and 2, the left-going edges correspond to
mismatches.  Some  edges  corresponding  to  mismatches  are  omitted:  by  convention,  if  a  state  i
has no outgoing edge labeled a for some a ∈ ∑, then δ(i, a) = 0. (b) The corresponding transition
function  δ,  and  the  pattern  string  P  =  ababaca.  The  entries  corresponding  to  successful
matches  between  pattern  and  input  characters  are  shown  in  blue.  (c)  The  operation  of  the
automaton  on  the  text  T  =  abababacaba.  Under  each  text  character  T[i]  appears  the  state
ϕ(T[:i])  that  the  automaton  is  in  after  processing  the  preﬁx  T[:i].  The  substring  of  the  pattern
that  occurs  in  the  text  is  highlighted  in  blue.  The  automaton  ﬁnds  this  one  occurrence  of  the
pattern, ending in position 9.

The sufﬁx function σ is well deﬁned since the empty string P[:0] = ϵ is a
sufﬁx of every string. As examples, for the pattern P = ab, we have σ(ε)
= 0, σ(ccaca) = 1, and σ(ccab) = 2. For a pattern P of length m, we
have  σ(x)  =  m  if  and  only  if  P  ⊐  x.  From  the  deﬁnition  of  the  sufﬁx
function, x ⊐ y implies σ(x) ≤ σ(y) (see Exercise 32.3-4).

We  are  now  ready  to  deﬁne  the  string-matching  automaton  that

corresponds to a given pattern P[1:m]:

The state set Q is {0, 1, …, m}. The start state q0 is state 0, and
state m is the only accepting state.
The transition function δ is deﬁned, for any state q and character
a, by

As the automaton consumes characters of the text T, it is trying to
build a match of the pattern P against the most recently seen characters
of  T.  At  any  time,  the  state  number  q  gives  the  length  of  the  longest
preﬁx  of  P  that  matches  the  most  recently  seen  text  characters.
Whenever the automaton reaches state m, the m most recently seen text
characters  match  the  ﬁrst  m  characters  of  P.  Since  P  has  length  m,
reaching  state  m  means  that  the  m  most  recently  seen  text  characters
match the entire pattern, so that the automaton has found a match.

With  this  intuition  behind  the  design  of  the  automaton,  here  is  the
reasoning  behind  deﬁning  δ(q,  a)  =  σ(P[:q]a).  Suppose  that  the
automaton  is  in  state  q  after  reading  the  ﬁrst  i  characters  of  the  text,
that  is,  q  =  ϕ(T[:i]).  The  intuitive  idea  then  says  that  q  also  equals  the
length  of  the  longest  preﬁx  of  P  that  matches  a  sufﬁx  of  T[:i]  or,
equivalently, that q = σ(T[:i]). Thus, since ϕ(T[:i]) and σ(T[:i]) both equal
q,  we  will  see  (in  Theorem  32.4  on  page  973)  that  the  automaton
maintains the following invariant:

If the automaton is in state q and reads the next character T[i + 1] = a,
then the transition should lead to the state corresponding to the longest
preﬁx of P that is a sufﬁx of T[:i]a. That state is σ(T[:i]a), and equation
(32.5) gives ϕ(T[:i]a) = σ(T[:i]a). Because P[:q] is the longest preﬁx of P
that  is  a  sufﬁx  of  T[:i],  the  longest  preﬁx  of  P  that  is  a  sufﬁx  of  T[:i]a
has  length  not  only  σ(T[:i]a),  but  also  σ(P[:q]a),  and  so  ϕ(T[:i]a)  =
σ(P[:q]a). (Lemma 32.3 on page 972 will prove that σ(T[:i]a) = σ(P[:q]a).)
Thus,  when  the  automaton  is  in  state  q,  the  transition  function  δ  on
character a should take the automaton to state δ(q, a) = δ(ϕ(T[:i]), a) =

ϕ(T[:i]a)  =  σ(P[:q]a)  (with  the  last  equality  following  from  equation
(32.5)).

There  are  two  cases  to  consider,  depending  on  whether  the  next
character continues to match the pattern. In the ﬁrst case, a = P[q + 1],
so  that  the  character  a  continues  to  match  the  pattern.  In  this  case,
because δ(q, a) = q + 1, the transition continues to go along the “spine”
of the automaton (the blue edges in Figure 32.6(a)). In the second case,
a  ≠  P[q  +  1],  so  that  a  does  not  extend  the  match  being  built.  In  this
case, we need to ﬁnd the longest preﬁx of P that is also a sufﬁx of T[:i]a,
which  will  have  length  at  most  q.  The  preprocessing  step  matches  the
pattern  against  itself  when  creating  the  string-matching  automaton,  so
that the transition function can quickly identify the longest such smaller
preﬁx of P.

Let’s  look  at  an  example.  Consider  state  5  in  the  string-matching
automaton  of  Figure  32.6.  In  state  5,  the  ﬁve  most  recently  read
characters  of  T  are  ababa,  the  characters  along  the  spine  of  the
automaton that reach state 5. If the next character of T is c, then the
most recently read characters of T are ababac, which is the preﬁx of P
with length 6. The automaton should continue along the spine to state
6. This is the ﬁrst case, in which the match continues, and δ(5, c) = 6. To
illustrate the second case, suppose that in state 5, the next character of
T is b, so the most recently read characters of T are ababab. Here, the
longest preﬁx of P that matches the most recently read characters of T
—that is, a sufﬁx of the portion of T read so far—is abab, with length
4, so δ(5, b) = 4.

efﬁcient

procedure

To clarify the operation of a string-matching automaton, the simple
and
FINITE-AUTOMATON-MATCHER
simulates  the  behavior  of  such  an  automaton  (represented  by  its
transition function δ) in ﬁnding occurrences of a pattern P of length m
in  an  input  text  T[1:n].  As  for  any  string-matching  automaton  for  a
pattern of length m, the state set Q is {0, 1, …, m}, the start state is 0,
and the only accepting state is state m. From the simple loop structure
of FINITE-AUTOMATON-MATCHER, you can see that its matching
time on a text string of length n is Θ(n), assuming that each lookup of
the  transition  function  δ  takes  constant  time.  This  matching  time,

however,  does  not  include  the  preprocessing  time  required  to  compute
the transition function. We address this problem later, after ﬁrst proving
that  the  procedure  FINITE-AUTOMATON-MATCHER  operates
correctly.

FINITE-AUTOMATON-MATCHER(T, δ, n, m)
1 q = 0
2 for i = 1 to n
3

q = δ(q, T[i])
if q == m

4

5

print “Pattern occurs with shift” i – m

Let’s  examine  how  the  automaton  operates  on  an  input  text  T[1:n].
We  will  prove  that  the  automaton  is  in  state  σ(T[:i])  after  reading
character T[i]. Since σ(T[:i]) = m if and only if P ⊐ T[:i], the machine is
in the accepting state m if and only if it has just read the pattern P. We
start with two lemmas about the sufﬁx function σ.

Lemma 32.2 (Sufﬁx-function inequality)
For any string x and character a, we have σ(xa) ≤ σ(x) + 1.

Figure  32.7  An  illustration  for  the  proof  of  Lemma  32.2.  The  ﬁgure  shows  that  r  ≤  σ(x)  +  1,
where r = σ(xa).

Figure  32.8  An  illustration  for  the  proof  of  Lemma  32.3.  The  ﬁgure  shows  that  r  =  σ(P[:q]a),
where q = σ(x) and r = σ(xa).

Proof      Referring  to  Figure  32.7,  let  r  =  σ(xa).  If  r  =  0,  then  the
conclusion  σ(xa)  =  r  ≤  σ(x)+1  is  trivially  satisﬁed  since  σ(x)  is
nonnegative. Now assume that r > 0. Then, P[:r] ⊐ xa, by the deﬁnition
of σ. Thus, P[:r − 1] ⊐ x, by dropping the a from both the end of P[:r]
and the end of xa. Therefore, r – 1 ≤ σ(x), since σ(x) is the largest k such
that P[:k] ⊐ x, and thus σ(xa) = r ≤ σ(x) + 1.

▪

Lemma 32.3 (Sufﬁx-function recursion lemma)
For any string x and character a, if q = σ(x), then σ(xa) = σ(P[:q]a).

Proof   The deﬁnition of σ gives that P[:q] ⊐ x. As Figure 32.8 shows,
we also have P[:q]a ⊐ xa. Let r = σ(xa). Then P[:r] ⊐ xa and, by Lemma
32.2, r ≤ q + 1. Thus, we have |P[:r]| = r ≤ q + 1 = |P[:q]a|. Since P[:q]a ⊐
xa,  P[:r]  ⊐  xa,  and  |P[:r]|  ≤  |P[:q]a|,  Lemma  32.1  on  page  959  implies
that P[:r] ⊐ P[:q]a. Therefore, r ≤ (P[:q]a), that is, σ(xa) ≤ σ(P[:q]a). But
we also have σ(P[:q]a) ≤ σ(xa), since P[:q]a ⊐ xa. Thus, σ(xa) = σ(P[:q]a).
▪
We  are  now  ready  to  prove  the  main  theorem  characterizing  the
behavior  of  a  string-matching  automaton  on  a  given  input  text.  As
noted above, this theorem shows that the automaton is merely keeping
track, at each step, of the longest preﬁx of the pattern that is a sufﬁx of
what has been read so far. In other words, the automaton maintains the
invariant (32.5).

Theorem 32.4
If  ϕ  is  the  ﬁnal-state  function  of  a  string-matching  automaton  for  a
given pattern P and T[1:n] is an input text for the automaton, then

ϕ(T[:i]) = σ(T[:i])
for i = 0, 1, …, n.

Proof   The proof is by induction on i. For i = 0, the theorem is trivially
true, since T[:0] = ε. Thus, ϕ(T[:0]) = 0 = σ(T[:0]).

Now assume that ϕ(T[:i]) = σ(T[:i]). We will prove that ϕ(T[:i + 1]) =
σ(T[:i + 1]). Let q denote ϕ(T[:i]), so that q = σ(T[:i]), and let a denote
T[i + 1]. Then,

ϕ(T[:i + 1]) = ϕ(T[:i]a)

(by the deﬁnitions of T[:i + 1] and a)

= δ(ϕ(T[:i]), a) (by the deﬁnition of ϕ)
(by the deﬁnition of q)
= δ(q, a)
(by the deﬁnition (32.4) of δ)
= σ(P[:q]a)
(by Lemma 32.3)
= σ(T[:i]a)
(by the deﬁnition of T[:i + 1]).
= (T[:i + 1])

▪

By Theorem 32.4, if the machine enters state q on line 3, then q is the
largest value such that P[:q] ⊐ T[:i]. Thus, in line 4, q = m if and only if
the  machine  has  just  read  an  occurrence  of  the  pattern  P.  Therefore,
FINITE-AUTOMATON-MATCHER operates correctly.

Computing the transition function

The  procedure  COMPUTE-TRANSITION-FUNCTION  on
the
following page computes the transition function δ from a given pattern
P[1:m]. It computes δ(q, a) in a straightforward manner according to its
deﬁnition in equation (32.4). The nested loops beginning on lines 1 and
2 consider all states q and all characters a, and lines 3–6 set δ(q, a) to be
the  largest  k  such  that  P[:k]  ⊐  P[:q]a.  The  code  starts  with  the  largest

conceivable  value  of  k,  which  is  q+1,  unless  q  =  m,  in  which  case  k
cannot  be  larger  than  m.  It  then  decreases  k  until  P[:k]  is  a  sufﬁx  of
P[:q]a,  which  must  eventually  occur,  since  P[:0]  =  ε  is  a  sufﬁx  of  every
string.

COMPUTE-TRANSITION-FUNCTION(P, ∑, m)
1 for q = 0 to m
2

for each character a ∈ ∑
k = min {m, q + 1}
while P[:k] is not a sufﬁx of P[:q]a

3

4

5

k = k – 1

δ(q, a) = k

6
7 return δ

The  running  time  of  COMPUTE-TRANSITION-FUNCTION  is
O(m3 |∑|), because the outer loops contribute a factor of m |∑|, the inner
while loop can run at most m + 1 times, and the test for whether P[:k] is
a  sufﬁx  of  P[:q]a  on  line  4  can  require  comparing  up  to  m  characters.
Much  faster  procedures  exist.  By  utilizing  some  cleverly  computed
information about the pattern P (see Exercise 32.4-8), the time required
to compute δ from P improves to O(m |∑|). This improved procedure for
computing  δ  provides  a  way  to  ﬁnd  all  occurrences  of  a  length-m
pattern in a length-n text over an alphabet ∑ with O(m |∑|) preprocessing
time and Θ(n) matching time.

Exercises

32.3-1
Draw a state-transition diagram for the string-matching automaton for
the  pattern  P  =  aabab  over  the  alphabet  ∑  =  {a,  b}  and  illustrate  its
operation on the text string T = aaababaabaababaab.

32.3-2
Draw a state-transition diagram for the string-matching automaton for
the pattern P = ababbabbababbababbabb over the alphabet ∑ = {a,

b}.

32.3-3
A pattern P is nonoverlappable if P[:k] ⊐ P[:q] implies k = 0 or k = q.
Describe the state-transition diagram of the string-matching automaton
for a nonoverlappable pattern.

32.3-4
Let x and y be preﬁxes of the pattern P. Prove that x ⊐ y implies σ(x) ≤
σ(y).

★ 32.3-5
Given  two  patterns  P  and  P′,  describe  how  to  construct  a  ﬁnite
automaton  that  determines  all  occurrences  of  either  pattern.  Try  to
minimize the number of states in your automaton.

32.3-6
Given a pattern P containing gap characters (see Exercise 32.1-4), show
how  to  build  a  ﬁnite  automaton  that  can  ﬁnd  an  occurrence  of  P  in  a
text T in O(n) matching time, where n = |T|.

★ 32.4 The Knuth-Morris-Pratt algorithm

Knuth,  Morris,  and  Pratt  developed  a  linear-time  string  matching
algorithm  that  avoids  computing  the  transition  function  δ  altogether.
Instead,  the  KMP  algorithm  uses  an  auxiliary  function  π,  which  it
precomputes  from  the  pattern  in  Θ(m)  time  and  stores  in  an  array
π[1:m].  The  array  π  allows  the  algorithm  to  compute  the  transition
function  δ  efﬁciently  (in  an  amortized  sense)  “on  the  ﬂy”  as  needed.
Loosely speaking, for any state q = 0, 1, …, m and any character a ∈ ∑,
the  value  π[q]  contains  the  information  needed  to  compute  δ(q,  a)  but
that does not depend on a. Since the array π has only m entries, whereas
δ  has  Θ(m  |∑|)  entries,  the  KMP  algorithm  saves  a  factor  of  |∑|  in  the
preprocessing  time  by  computing  π  rather  than  δ.  Like  the  procedure
has
FINITE-AUTOMATON-MATCHER,
completed, the KMP algorithm uses Θ(n) matching time.

preprocessing

once

The preﬁx function for a pattern

The preﬁx function π for a pattern encapsulates knowledge about how
the  pattern  matches  against  shifts  of  itself.  The  KMP  algorithm  takes
advantage of this information to avoid testing useless shifts in the naive
pattern-matching  algorithm  and  to  avoid  precomputing  the  full
transition function δ for a string-matching automaton.

Consider  the  operation  of  the  naive  string  matcher.  Figure  32.9(a)
shows  a  particular  shift  s  of  a  template  containing  the  pattern  P  =
ababaca  against  a  text  T.  For  this  example,  q  =  5  of  the  characters
have  matched  successfully,  but  the  6th  pattern  character  fails  to  match
the  corresponding  text  character.  The  information  that  q  characters
have matched successfully determines the corresponding text characters.
Because these q text characters match, certain shifts must be invalid. In
the example of the ﬁgure, the shift s + 1 is necessarily invalid, since the
ﬁrst  pattern  character  (a)  would  be  aligned  with  a  text  character  that
does  not  match  the  ﬁrst  pattern  character,  but  does  match  the  second
pattern character (b). The shift s′ = s + 2 shown in part (b) of the ﬁgure,
however,  aligns  the  ﬁrst  three  pattern  characters  with  three  text
characters that necessarily match.

More  generally,  suppose  that  you  know  that  P[:q]  ⊐  T[:s  +  q]  or,
equivalently,  that  P[1:q]  =  T[s  +  1:s  +  q].  You  want  to  shift  P  so  that
some shorter preﬁx P[:k] of P matches a sufﬁx of T[:s +q], if possible.
You might have more than one choice for how much to shift, however.
In Figure 32.9(b), shifting P by 2 positions works, so that P[:3] ⊐ T[:s +
q],  but  so  does  shifting  P  by  4  positions,  so  that  P[:1]  ⊐  T[:s  +q]  in
Figure 32.9(c). If more than one shift amount works, you should choose
the smallest shift amount so that you do not miss any potential matches.
Put more precisely, you want to answer this question:

Given that pattern characters P[1:q] match text characters T[s +
1:s + q] (that is, P[:q] ⊐ T[:s + q]), what is the least shift s′ > s
such that for some k < q,

(that is, P[:k] ⊐ T[:s′ + k]), where s′ + k = s + q?

Here’s another way to look at this question. If you know P[:q] ⊐ T[:s
+ q], then how do you ﬁnd the longest proper preﬁx P[:k] of P[:q] that is
also a sufﬁx of T[:s + q]? These questions are equivalent because given s
and q, requiring s′ + k = s + q means that ﬁnding the smallest shift s′ (2
in Figure 32.9(b)) is tantamount to ﬁnding the longest preﬁx length k (3
in Figure 32.9(b)). If you add the difference q – k in the lengths of these
preﬁxes of P to the shift s, you get the new shift s′, so that s′ = s + (q –
k).  In  the  best  case,  k  =  0,  so  that  s′  =  s  +  q,  immediately  ruling  out
shifts  s  +  1,  s  +  2,  …,  s  +  q  −  1.  In  any  case,  at  the  new  shift  s′,  it  is
redundant to compare the ﬁrst k characters of P with the corresponding
characters of T, since equation (32.6) guarantees that they match.

As  Figure  32.9(d)  demonstrates,  you  can  precompute  the  necessary
information by comparing the pattern against itself. Since T[s′ + 1:s′ +
k] is part of the matched portion of the text, it is a sufﬁx of the string
P[:q]. Therefore, think of equation (32.6) as asking for the greatest k < q
such that P[:k] ⊐ P[:q]. Then, the new shift s′ = s + (q – k) is the next
potentially valid shift. It will be convenient to store, for each value of q,
the  number  k  of  matching  characters  at  the  new  shift  s′,  rather  than
storing, say, the amount s′ – s to shift by.

Let’s look at the precomputed information a little more formally. For
a given pattern P[1:m], the preﬁx function for P is the function π : {1, 2,
…, m} → {0, 1, …, m –} such that

π[q] = max{k : k < q and P[:k] ⊐ P[:q]}.
That is, π[q] is the length of the longest preﬁx of P that is a proper sufﬁx
of  P[:q].  Here  is  the  complete  preﬁx  function  π  for  the  pattern
ababaca:

Figure 32.9 The preﬁx function π. (a) The pattern P = ababaca aligns with a text T so that the
ﬁrst  q  =  5  characters  match.  Matching  characters,  in  blue,  are  connected  by  blue  lines.  (b)
Knowing these particular 5 matched characters (P[:5]) sufﬁces to deduce that a shift of s + 1 is
invalid,  but  that  a  shift  of  s′  =  s  +  2  is  consistent  with  everything  known  about  the  text  and
therefore is potentially valid. The preﬁx P[:k], where k = 3, aligns with the text seen so far. (c) A
shift of s + 4 is also potentially valid, but it leaves only the preﬁx P[:1] aligned with the text seen
so  far.  (d)  To  precompute  useful  information  for  such  deductions,  compare  the  pattern  with
itself.  Here,  the  longest  preﬁx  of  P  that  is  also  a  proper  sufﬁx  of  P[:5]  is  P[:3].  The  array  π
represents this precomputed information, so that π[5] = 3. Given that q characters have matched
successfully at shift s, the next potentially valid shift is at s′ = s + (q – π[q]) as shown in part (b).

The  procedure  KMP-MATCHER  on  the  following  page  gives  the
Knuth-Morris-Pratt  matching  algorithm.  The  procedure  follows  from
FINITE-AUTOMATON-MATCHER for the most part. To compute π,
KMP-MATCHER calls the auxiliary procedure COMPUTE-PREFIX-
FUNCTION.  These  two  procedures  have  much  in  common,  because
both match a string against the pattern P: KMP-MATCHER matches
the  text  T  against  P,  and  COMPUTE-PREFIX-FUNCTION  matches
P against itself.

Next, let’s analyze the running times of these procedures. Then we’ll

prove them correct, which will be more complicated.

Running-time analysis

The  running  time  of  COMPUTE-PREFIX-FUNCTION  is  Θ(m),
which  we  show  by  using  the  aggregate  method  of  amortized  analysis
(see Section 16.1). The only tricky part is showing that the while loop of
lines  5–6  executes  O(m)  times  altogether.  Starting  with  some
observations  about  k,  we’ll  show  that  it  makes  at  most  m–1  iterations.
First,  line  3  starts  k  at  0,  and  the  only  way  that  k  increases  is  by  the
increment operation in line 8, which executes at most once per iteration
of the for loop of lines 4–9. Thus, the total increase in k is at most m–1.
Second, since k < q upon entering the for loop and each iteration of the
loop increments q, we always have k < q. Therefore, the assignments in
lines  2  and  9  ensure  that  π[q]  <  q  for  all  q  =  1,  2,  …,  m,  which  means
that each iteration of the while loop decreases k. Third, k never becomes
negative. Putting these facts together, we see that the total decrease in k
from  the  while  loop  is  bounded  from  above  by  the  total  increase  in  k
over all iterations of the for loop, which is m – 1. Thus, the while loop
iterates  at  most  m  –  1  times  in  all,  and  COMPUTE-PREFIX-
FUNCTION runs in Θ(m) time.

KMP-MATCHER(T, P, n, m)
  1 π = COMPUTE-PREFIX-FUNCTION(P, m)
  2 q = 0
  3 for i = 1 to n
  4

while q > 0 and P[q + 1] ≠ T[i]

// number of characters matched
// scan the text from left to right

  5

  6

  7

  8

  9

10

q = π[q]

// next character does not match

if P[q + 1] == T[i]

if q == m

q = q + 1

// next character matches
// is all of P matched?
print “Pattern occurs with shift” i – m
q = π[q]

// look for the next match

COMPUTE-PREFIX-FUNCTION(P, m)
  1 let π[1:m] be a new array
  2 π[1] = 0
  3 k = 0
  4 for q = 2 to m

  5

  6

  7

  8

while k > 0 and P[k + 1] ≠ P[q]

k = π[k]

if P[k + 1] == P[q]

k = k + 1

π[q] = k

  9
10 return π

Exercise  32.4-4  asks  you  to  show,  by  a  similar  aggregate  analysis,

that the matching time of KMP-MATCHER is Θ(n).

Figure 32.10 An illustration of Lemma 32.5 for the pattern P = ababaca and q = 5. (a) The π
function for the given pattern. Since π[5] = 3, π[3] = 1, and π[1]= 0, iterating π gives π*[5] = {3, 1,
0}. (b) Sliding the template containing the pattern P to the right and noting when some preﬁx
P[:k] of P matches up with some proper sufﬁx of P[:5]. Matches occur when k = 3, 1, and 0. In
the ﬁgure, the ﬁrst row gives P, and the vertical red line is drawn just after P[:5]. Successive rows
show  all  the  shifts  of  P  that  cause  some  preﬁx  P[:k]  of  P  to  match  some  sufﬁx  of  P[:5].
Successfully  matched  characters  are  shown  in  blue.  Blue  lines  connect  aligned  matching
characters. Thus, {k : k < 5 and P[:k] ⊐ P[:5]} = {3, 1, 0}. Lemma 32.5 claims that π*[q] = {k : k
< q and P[:k] ⊐ P[:q]} for all q.

Compared  with  FINITE-AUTOMATON-MATCHER,  by  using  π
rather  than  δ,  the  KMP  algorithm  reduces  the  time  for  preprocessing
the  pattern  from  O(m  |∑|)  to  Θ(m),  while  keeping  the  actual  matching
time bounded by Θ(n).

Correctness of the preﬁx-function computation

We’ll  see  a  little  later  that  the  preﬁx  function  π  helps  to  simulate  the
transition function δ in a string-matching automaton. But ﬁrst, we need

to  prove  that  the  procedure  COMPUTE-PREFIX-FUNCTION  does
indeed compute the preﬁx function correctly. Doing so requires ﬁnding
all  preﬁxes  P[:k]  that  are  proper  sufﬁxes  of  a  given  preﬁx  P[:q].  The
value  of  π[q]  gives  us  the  length  of  the  longest  such  preﬁx,  but  the
following  lemma,  illustrated  in  Figure  32.10,  shows  that  iterating  the
preﬁx function π generates all the preﬁxes P[:k] that are proper sufﬁxes
of P[:q]. Let

π*[q] = {π[q], π(2)[q], π(3)[q], …, π(t)[q]},

where π(i)[q] is deﬁned in terms of functional iteration, so that π(0)[q] =
q and π(i)[q] = π[π(i−1)[q]] for i ≥ 1 (so that π[q] = π(1)[q]), and where the
sequence in π*[q] stops upon reaching π(t)[q] = 0 for some t ≥ 1.

Lemma 32.5 (Preﬁx-function iteration lemma)
Let P be a pattern of length m with preﬁx function π. Then, for q = 1, 2,
…, m, we have π*[q] = {k : k < q and P[:k] ⊐ P[:q]}.

Proof      We  ﬁrst  prove  that  π*[q]  ⊆  {k  :  k  <  q  and  P[:k]  ⊐  P[:q]}  or,
equivalently,

If i ∈ π*[q], then i = π(u)[q] for some u > 0. We prove equation (32.7)
by  induction  on  u.  For  u  =  1,  we  have  i  =  π[q],  and  the  claim  follows
since  i  <  q  and  P[:π[q]]  ⊐  P[:q]  by  the  deﬁnition  of  π.  Now  consider
some u ≥ 1 such that both π(u)[q] and π(u+1)[q] belong to π*[q]. Let i =
π(u)[q], so that π[i] = π(u+1)[q]. The inductive hypothesis is that P[:i] ⊐
P[:q]. Because the relations < and ⊐ are transitive, we have π[i] < i < q
and P[:π[i]] ⊐ P[:i] ⊐ P[:q], which establishes equation (32.7) for all i in
π*[q]. Therefore, π*[q] ⊆ {k : k < q and P[:k] ⊐ P[:q]}.

We  now  prove  that  {k  :  k  <  q  and  P[:k]  ⊐  P[:q]}  ⊆  π*[q]  by
contradiction. Suppose to the contrary that the set {k : k < q and P[:k]
⊐ P[:q]} – π*[q] is nonempty, and let j be the largest number in the set.
Because π[q] is the largest value in {k : k < q and P[:k] ⊐ P[:q]} and π*

[q] ∈ π*[q], it must be the case that j < [q]. Having established that π*[q]
contains at least one integer greater than j, let j′ denote the smallest such
integer. (We can choose j′ = π[q] if no other number in π*[q] is greater
than j.) We have P[:j] ⊐ P[:q] because j ∈ {k : k < q and P[:k] ⊐ P[:q]},
and  from  j′  ∈  π*[q]  and  equation  (32.7),  we  have  P[:j′]  ⊐  P[:q].  Thus,
P[:j] ⊐ P[:j′] by Lemma 32.1, and j is the largest value less than j′ with
this property. Therefore, we must have π[j′] = j and, since j′ ∈ π*[q], we
must have j ∈ π*[q] as well. This contradiction proves the lemma.

▪

The  algorithm  COMPUTE-PREFIX-FUNCTION  computes  π[q],
in order, for q = 1, 2, …, m. Setting π[1] to 0 in line 2 of COMPUTE-
PREFIX-FUNCTION is certainly correct, since π[q] < q for all q. We’ll
use  the  following  lemma  and  its  corollary  to  prove  that  COMPUTE-
PREFIX-FUNCTION computes π[q] correctly for q > 1.

Lemma 32.6
Let P be a pattern of length m, and let π be the preﬁx function for P.
For q = 1, 2, …, m, if π[q] > 0, then π[q] – 1 ∈ π*[q – 1].

Proof   Let r = π[q] > 0, so that r < q and P[:r] ⊐ P[:q], and thus, r – 1 <
q – 1 and P[:r – 1] ⊐ P[:q – 1] (by dropping the last character from P[:r]
and P[:q], which we can do because r > 0). By Lemma 32.5, therefore, r
– 1 ∈ π*[q – 1]. Thus, we have π[q] – 1 = r – 1 ∈ π*[q – 1].

▪

For q = 2, 3, …, m, deﬁne the subset Eq–1 ⊆ π*[q – 1] by

Eq–1 = {k ∈ π*[q – 1]: P[k + 1] = P[q]}

= {k : k < q – 1 and P[:k] ⊐ P[:q – 1] and P[k + 1] = P[q]}

(by Lemma 32.5)

= {k : k < q – 1 and P[:k + 1] ⊐ P[:q]}.

The set Eq–1 consists of the values k < q – 1 for which P[:k] ⊐ P[:q – 1]
and for which, because P[k + 1] = P[q], we have P[:k + 1] ⊐ P[:q]. Thus,

Eq–1 consists of those values k ∈ π*[q – 1] such that extending P[:k] to
P[:k + 1] produces a proper sufﬁx of P[:q].

Corollary 32.7
Let P be a pattern of length m, and let π be the preﬁx function for P.
Then, for q = 2, 3, …, m,

art

Proof   If Eq–1 is empty, there is no k ∈ π*[q – 1] (including k = 0) such
that  extending  P[:k]  to  P[:k  +  1]  produces  a  proper  sufﬁx  of  P[:q].
Therefore, π[q]= 0.

If, instead, Eq–1 is nonempty, then for each k ∈ Eq–1, we have k + 1

< q and P[:k + 1] ⊐ P[:q]. Therefore, the deﬁnition of π[q] gives

art

Note  that  π[q]  >  0.  Let  r  =  π[q]  –  1,  so  that  r  +  1  =  π[q]  >  0,  and
therefore P[:r + 1] ⊐ P[:q]. If a nonempty string is a sufﬁx of another,
then the two strings must have the same last character. Since r + 1 > 0,
the preﬁx P[:r + 1] is nonempty, and so P[r + 1] = P[q]. Furthermore, r
∈ π*[q – 1] by Lemma 32.6. Therefore, r ∈ Eq–1, and so π[q] – 1 = r ≤
max Eq–1 or, equivalently,

Combining equations (32.8) and (32.9) completes the proof.

art

▪

We  now  ﬁnish  the  proof  that  COMPUTE-PREFIX-FUNCTION
computes π correctly. The key is to combine the deﬁnition of Eq–1 with
the  statement  of  Corollary  32.7,  so  that  π[q]  equals  1  plus  the  greatest
value of k in π*[q – 1] such that P[k + 1] = P[q]. First, in COMPUTE-
PREFIX-FUNCTION, k = π[q – 1] at the start of each iteration of the
for loop of lines 4–9. This condition is enforced by lines 2 and 3 when
the loop is ﬁrst entered, and it remains true in each successive iteration
because of line 9. Lines 5–8 adjust k so that it becomes the correct value
of π[q]. The while loop of lines 5–6 searches through all values k ∈ π*[q

–  1]  in  decreasing  order  to  ﬁnd  the  value  of  π[q].  The  loop  terminates
either  because  k  reaches  0  or  P[k  +  1]  =  P[q].  Because  the  “and”
operator short-circuits, if the loop terminates because P[k + 1] = P[q],
then k must have also been positive, and so k is the greatest value in Eq–
1. In this case, lines 7–9 set π[q] to k + 1, according to Corollary 32.7. If,
instead,  the  while  loop  terminates  because  k  =  0,  then  there  are  two
possibilities.  If  P[1]  =  P[q],  then  Eq–1  =  {0},  and  lines  7–9  set  both  k
and π[q] to 1. If k = 0 and P[1] ≠ P[q], however, then Eq–1 = ø;. In this
case,  line  9  sets  π[q]  to  0,  again  according  to  Corollary  32.7,  which
completes  the  proof  of  the  correctness  of  COMPUTE-PREFIX-
FUNCTION.

Correctness of the Knuth-Morris-Pratt algorithm

You can think of the procedure KMP-MATCHER as a reimplemented
version  of  the  procedure  FINITE-AUTOMATON-MATCHER,  but
using  the  preﬁx  function  π  to  compute  state  transitions.  Speciﬁcally,
we’ll  prove  that  in  the  ith  iteration  of  the  for  loops  of  both  KMP-
MATCHER and FINITE-AUTOMATON-MATCHER, the state q has
the  same  value  upon  testing  for  equality  with  m  (at  line  8  in  KMP-
MATCHER  and  at  line  4  in  FINITE-AUTOMATON-MATCHER).
Once we have argued that KMP-MATCHER simulates the behavior of
the  correctness  of  KMP-
FINITE-AUTOMATON-MATCHER,
MATCHER follows from the correctness of FINITE-AUTOMATON-
MATCHER  (though  we’ll  see  a  little  later  why  line  10  in  KMP-
MATCHER is necessary).

let’s

take  a  moment

Before  formally  proving  that  KMP-MATCHER  correctly  simulates
to
FINITE-AUTOMATON-MATCHER,
understand how the preﬁx function π replaces the δ transition function.
Recall that when a string-matching automaton is in state q and it scans
a character a = T[i], it moves to a new state δ(q, a). If a = P[q + 1], so
that  a  continues  to  match  the  pattern,  then  the  state  number  is
incremented: δ(q, a) = q + 1. Otherwise, a ≠ P[q + 1], so that a does not
continue to match the pattern, and the state number does not increase: 0
≤  δ(q,  a)  ≤  q.  In  the  ﬁrst  case,  when  a  continues  to  match,  KMP-

MATCHER  moves  to  state  q  +  1  without  referring  to  the  π  function:
the while loop test in line 4 immediately comes up false, the test in line 6
comes up true, and line 7 increments q.

The  π  function  comes  into  play  when  the  character  a  does  not
continue to match the pattern, so that the new state δ(q, a) is either q or
to  the  left  of  q  along  the  spine  of  the  automaton.  The  while  loop  of
lines  4–5  in  KMP-MATCHER  iterates  through  the  states  in  π*[q],
stopping either when it arrives in a state, say q′, such that a matches P[q′
+ 1] or q′ has gone all the way down to 0. If a matches P[q′ + 1], then
line  7  sets  the  new  state  to  q′+1,  which  should  equal  δ(q,  a)  for  the
simulation  to  work  correctly.  In  other  words,  the  new  state  δ(q,  a)
should be either state 0 or a state numbered 1 more than some state in
π*[q].

Let’s look at the example in Figures 32.6 and 32.10, which are for the
pattern  P  =  ababaca.  Suppose  that  the  automaton  is  in  state  q  =  5,
having matched ababa. The states in π*[5] are, in descending order, 3,
1,  and  0.  If  the  next  character  scanned  is  c,  then  you  can  see  that  the
automaton moves to state δ(5, c) = 6 in both FINITE-AUTOMATON-
MATCHER (line 3) and KMP-MATCHER (line 7). Now suppose that
the  next  character  scanned  is  instead  b,  so  that  the  automaton  should
move  to  state  δ(5,  b)  =  4.  The  while  loop  in  KMP-MATCHER  exits
after executing line 5 once, and the automaton arrives in state q′ = π[5]
= 3. Since P[q′ + 1] = P[4] = b, the test in line 6 comes up true, and the
automaton moves to the new state q′ + 1 = 4 = δ(5, b). Finally, suppose
that  the  next  character  scanned  is  instead  a,  so  that  the  automaton
should move to state δ(5, a) = 1. The ﬁrst three times that the test in line
4 executes, the test comes up true. The ﬁrst time ﬁnds that P[6] = c ≠ a,
and the automaton moves to state π[5] = 3 (the ﬁrst state in π*[5]). The
second time ﬁnds that P[4] = b ≠ a, and the automaton moves to state
π[3] = 1 (the second state in π*[5]). The third time ﬁnds that P[2] = b ≠
a,  and  the  automaton  moves  to  state  π[1]  =  0  (the  last  state  in  π*[5]).
The while loop exits once it arrives in state q′ = 0. Now line 6 ﬁnds that
P[q′ + 1] = P[1] = a, and line 7 moves the automaton to the new state q′
+ 1 = 1 = δ(5, a).

Thus,  the  intuition  is  that  KMP-MATCHER  iterates  through  the
states  in  π*[q]  in  decreasing  order,  stopping  at  some  state  q′  and  then
possibly  moving  to  state  q′+1.  Although  that  might  seem  like  a  lot  of
in  mind  that
work
asymptotically,  KMP-MATCHER
than  FINITE-
AUTOMATON-MATCHER.

just  to  simulate  computing  δ(q,  a),  bear
is  no  slower

We  are  now  ready  to  formally  prove  the  correctness  of  the  Knuth-
Morris-Pratt algorithm. By Theorem 32.4, we have that q = σ(T[:i]) after
each  time  line  3  of  FINITE-AUTOMATON-MATCHER  executes.
Therefore, it sufﬁces to show that the same property holds with regard
to the for loop in KMP-MATCHER. The proof proceeds by induction
on the number of loop iterations. Initially, both procedures set q to 0 as
they enter their respective for loops for the ﬁrst time. Consider iteration
i of the for loop in KMP-MATCHER. By the inductive hypothesis, the
state number q equals σ(T[:i – 1]) at the start of the loop iteration. We
need to show that when line 8 is reached, the new value of q is σ(T[:i]).
(Again, we’ll handle line 10 separately.)

Considering  q  to  be  the  state  number  at  the  start  of  the  for  loop
iteration,  when  KMP-MATCHER  considers  the  character  T[i],  the
longest preﬁx of P that is a sufﬁx of T[:i] is either P[:q + 1] (if P[q + 1] =
T[i])  or  some  preﬁx  (not  necessarily  proper,  and  possibly  empty)  of
P[:q].  We  consider  separately  the  three  cases  in  which  σ(T[:i])  =  0,
σ(T[:i]) = q + 1, and 0 < σ(T[:i]) ≤ q.

If σ(T[:i]) = 0, then P[:0] = ϵ is the only preﬁx of P that is a sufﬁx
of T[:i]. The while loop of lines 4–5 iterates through each value q′
in π*[q], but although P[:q′] ⊐ P[:q] ⊐ T[:i – 1] for every q′ ∈ π*[q]
(because < are ⊐ are transitive relations), the loop never ﬁnds a q′
such that P[q′ + 1] = T[i]. The loop terminates when q reaches 0,
and of course line 7 does not execute. Therefore, q = 0 at line 8, so
that now q = σ(T[:i]).
If σ(T[:i]) = q+1, then P[q+1] = T[i], and the while loop test in line
4  fails  the  ﬁrst  time  through.  Line  7  executes,  incrementing  the
state number to q + 1, which equals σ(T[:i]).
If 0 < σ(T[:i]) ≤ q′, then the while loop of lines 4–5 iterates at least
once,  checking  in  decreasing  order  each  value  in  π*[q]  until  it

stops at some q′ < q. Thus, P[:q′] is the longest preﬁx of P[:q] for
which P[q′ + 1] = T[i], so that when the while loop terminates, q′ +
1  =  σ(P[:q]T[i]).  Since  q  =  σ(T[:i  –  1]),  Lemma  32.3  implies  that
σ(T[:i – 1]T[i]) = σ(P[:q]T[i]). Thus we have

q′ + 1 = σ(P[:q]T[i])

= σ(T[:i – 1]T[i])
= σ(T[:i])

when the while loop terminates. After line 7 increments q, the new
state number q equals σ(T[:i]).

Line 10 is necessary in KMP-MATCHER, because otherwise, line 4
might try to reference P[m + 1] after ﬁnding an occurrence of P. (The
argument that q = σ(T[:i – 1]) upon the next execution of line 4 remains
valid  by  the  hint  given  in  Exercise  32.4-8:  that  δ(m,  a)  =  δ(π[m],  a)  or,
equivalently,  σ(Pa)  =  σ(P[:π[m]]a)  for  any  a  ∈  ∑.)  The  remaining
argument  for  the  correctness  of  the  Knuth-Morris-Pratt  algorithm
follows from the correctness of FINITE-AUTOMATON-MATCHER,
since we have shown that KMP-MATCHER simulates the behavior of
FINITE-AUTOMATON-MATCHER.

Exercises

32.4-1
Compute
preﬁx
ababbabbabbababbabb.

the

function

π

for

the

pattern

32.4-2
Give  an  upper  bound  on  the  size  of  π*[q]  as  a  function  of  q.  Give  an
example to show that your bound is tight.

32.4-3
Explain how to determine the occurrences of pattern P in the text T by
examining  the  π  function  for  the  string  PT  (the  string  of  length  m+n
that is the concatenation of P and T).

32.4-4

Use  an  aggregate  analysis  to  show  that  the  running  time  of  KMP-
MATCHER is Θ(n).

32.4-5
Use  a  potential  function  to  show  that  the  running  time  of  KMP-
MATCHER is Θ(n).

32.4-6
Show  how  to  improve  KMP-MATCHER  by  replacing  the  occurrence
of π in line 5 (but not line 10) by π′, where π′ is deﬁned recursively for q
= 1, 2, …, m – 1 by the equation

art

Explain  why  the  modiﬁed  algorithm  is  correct,  and  explain  in  what
sense this change constitutes an improvement.

32.4-7
Give  a  linear-time  algorithm  to  determine  whether  a  text  T  is  a  cyclic
rotation  of  another  string  T′.  For  example,  braze  and  zebra  are
cyclic rotations of each other.

★ 32.4-8
Give an O(m |∑|)-time algorithm for computing the transition function δ
for the string-matching automaton corresponding to a given pattern P.
(Hint: Prove that δ(q, a) = δ(π[q], a) if q = m or P[q + 1] ≠ a.)

32.5    Sufﬁx arrays

The algorithms we have seen thus far in this chapter can efﬁciently ﬁnd
all occurrences of a pattern in a text. That is, however, all they can do.
This  section  presents  a  different  approach—sufﬁx  arrays—with  which
you can ﬁnd all occurrences of a pattern in a text, but also quite a bit
more.  A  sufﬁx  array  won’t  ﬁnd  all  occurrences  of  a  pattern  as  quickly
as,  say,  the  Knuth-Morris-Pratt  algorithm,  but  its  additional  ﬂexibility
makes it well worth studying.

art

Figure  32.11  The  sufﬁx  array  SA,  rank  array  rank,  longest  common  preﬁx  array  LCP,  and
lexicographically sorted sufﬁxes of the text T = ratatat with length n = 7. The value of rank[i]
indicates the position of the sufﬁx T[i:] in the lexicographically sorted order: rank[SA[i]] = i for i
= 1, 2, …, n. The rank array is used to compute the LCP array.

A  sufﬁx  array

is  simply  a  compact  way  to  represent  the
lexicographically sorted order of all n sufﬁxes of a length-n text. Given
a text T[1:n], let T[i:] denote the sufﬁx T[i:n]. The sufﬁx array SA[1:n] of
T  is  deﬁned  such  that  if  SA[i]  =  j,  then  T[j:]  is  the  ith  sufﬁx  of  T  in
lexicographic order.3 That is, the ith sufﬁx of T in lexicographic order is
T[SA[i]:]. Along with the sufﬁx array, another useful array is the longest
common preﬁx array LCPOE[1:n]. The entry LCP[i] gives the length of
the  longest  common  preﬁx  between  the  ith  and  (i  –  1)st  sufﬁxes  in  the
sorted  order  (with  LCP[SA[1]]  deﬁned  to  be  0,  since  there  is  no  preﬁx
lexicographically smaller than T[SA[1]:]). Figure 32.11 shows the sufﬁx
array  and  longest  common  preﬁx  array  for  the  7-character  text
ratatat.

Given  the  sufﬁx  array  for  a  text,  you  can  search  for  a  pattern  via
binary  search  on  the  sufﬁx  array.  Each  occurrence  of  a  pattern  in  the
text  starts  some  sufﬁx  of  the  text,  and  because  the  sufﬁx  array  is  in
lexicographically  sorted  order,  all  occurrences  of  a  pattern  will  appear
at  the  start  of  consecutive  entries  of  the  sufﬁx  array.  For  example,  in
Figure  32.11,  the  three  occurrences  of  at  in  ratatat  appear  in
entries 1 through 3 of the sufﬁx array. If you ﬁnd the length-m pattern
in  the  length-n  sufﬁx  array  via  binary  search  (taking  O(m  1g  n)  time
because  each  comparison  takes  O(m)  time),  then  you  can  ﬁnd  all
occurrences  of  the  pattern  in  the  text  by  searching  backward  and
forward  from  that  spot  until  you  ﬁnd  a  sufﬁx  that  does  not  start  with
the  pattern  (or  you  go  beyond  the  bounds  of  the  sufﬁx  array).  If  the
pattern occurs k times, then the time to ﬁnd all k occurrences is O(m 1g
n + km).

With  the  longest  common  preﬁx  array,  you  can  ﬁnd  a  longest
repeated substring, that is, the longest substring that occurs more than
once in the text. If LCP[i] contains a maximum value in the LCP array,

then a longest repeated substring appears in T[SA[i]:SA[i] + LCP[i] – 1].
In the example of Figure 32.11, the LCP array has one maximum value:
LCP[3] = 4. Therefore, since SA[3] = 2, the longest repeated substring is
T[2:5]  =  atat.  Exercise  32.5-3  asks  you  to  use  the  sufﬁx  array  and
longest  common  preﬁx  array  to  ﬁnd  the  longest  common  substrings
between two texts. Next, we’ll see how to compute the sufﬁx array for an
n-character  text  in  O(n  1g  n)  time  and,  given  the  sufﬁx  array  and  the
text, how to compute the longest common preﬁx array in Θ(n) time.

Computing the sufﬁx array

There  are  several  algorithms  to  compute  the  sufﬁx  array  of  a  length-n
text.  Some  run  in  linear  time,  but  are  rather  complicated.  One  such
algorithm  is  given  in  Problem  32-2.  Here  we’ll  explore  a  simpler
algorithm that runs in Θ(n 1g n) time.

The  idea  behind  the  O(n  1g  n)-time  procedure  COMPUTE-
SUFFIX-ARRAY  on  the  following  page  is  to  lexicographically  sort
substrings  of  the  text  with  increasing  lengths.  The  procedure  makes
several  passes  over  the  text,  with  the  substring  length  doubling  each
time.  By  the  ⌈1g  n⌉th  pass,  the  procedure  is  sorting  all  the  sufﬁxes,
thereby  gaining  the  information  needed  to  construct  the  sufﬁx  array.
The  key  to  attaining  an  O(n  1g  n)-time  algorithm  will  be  to  have  each
pass after the ﬁrst sort in linear time, which will indeed be possible by
using radix sort.

art, so that s1 is

.  Now,  suppose  that
art. Then, regardless of

and s2. Decompose s1 into
concatenated  with
with

Let’s  start  with  a  simple  observation.  Consider  any  two  strings,  s1
art
art and
art  concatenated
art.  Likewise,  let  s2  be
art  is  lexicographically  smaller  than
, it must be the case that s1
art and
is lexicographically smaller than s2. For example, let s1 = aaz and s2 =
art
aba, and decompose s1 into
art,
and
art. Because
 is
it follows that s1 is lexicographically smaller than s2, even though
lexicographically smaller than

art and s2 into
art is lexicographically smaller than

art and

art.

Instead  of  comparing  substrings  directly,  COMPUTE-SUFFIX-
ARRAY  represents  substrings  of  the  text  with  integer  ranks.  Ranks
have the simple property that one substring is lexicographically smaller
then  another  if  and  only  if  it  has  a  smaller  rank.  Identical  substrings
have equal ranks.

Where  do  these  ranks  come  from?  Initially,  the  substrings  being
considered  are  just  single  characters  from  the  text.  Assume  that,  as  in
many  programming  languages,  there  is  a  function,  ord,  that  maps  a
character to its underlying encoding, which is a positive integer. The ord
function  could  be  the  ASCII  or  Unicode  encodings  or  any  other
function  that  produces  a  relative  ordering  of  the  characters.  For
example  if  all  the  characters  are  known  to  be  lowercase  letters,  then
ord(a) = 1, ord(b) = 2, …, ord(z) = 26 would work. Once the substrings
being considered contain multiple characters, their ranks will be positive
integers  less  than  or  equal  to  n,  coming  from  their  relative  order  after
being  sorted.  An  empty  substring  always  has  rank  0,  since  it  is
lexicographically less than any nonempty substring.

COMPUTE-SUFFIX-ARRAY(T, n)

  1

  2

  3

  4

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

allocate arrays substr-rank[1:n], rank[1:n], and SA[1:n]
for i = 1 to n

substr-rank[i].left-rank = ord(T[i])
if i < n

substr-rank[i].right-rank = ord(T[i + 1])

else substr-rank[i].right-rank = 0
substr-rank[i].index = i

sort  the  array  substr-rank  into  monotonically  increasing  order
based  on  the  left-rank  attributes,  using  the  right-rank
attributes to break ties; if still a tie, the order does not matter

l = 2
while l < n

MAKE-RANKS(substr-rank, rank, n)
for i = 1 to n

substr-rank[i].left-rank = rank[i]
if i + l ≤ n

15

16

17

18

19

20

21

22

substr-rank[i].right-rank = rank[i + l]

else substr-rank[i].right-rank = 0
substr-rank[i].index = i

sort  the  array  substr-rank  into  monotonically  increasing
order  based  on  the  left-rank  attributes,  using  the  right-
rank  attributes  to  break  ties;  if  still  a  tie,  the  order  does
not matter

l = 2l
for i = 1 to n

SA[i] = substr-rank[i].index

return SA

MAKE-RANKS(substr-rank, rank, n)

r = 1
rank[substr-rank[1].index] = r
for i = 2 to n

if substr-rank[i].left-rank ≠ substr-rank[i – 1].left-rank

or  substr-rank[i].right-rank  ≠  substr-rank[i  –  1].right-

rank

r = r + 1

rank[substr-rank[i].index] = r

  1

  2

  3

  4

  5

  6

art

Figure 32.12 The substr-rank array for indices i = 1, 2, …, 7 after the for loop of lines 2–7 and
after the sorting step in line 8 for input string T = ratatat.

The  COMPUTE-SUFFIX-ARRAY  procedure  uses  objects
internally  to  keep  track  of  the  relative  ordering  of  the  substrings
according to their ranks. When considering substrings of a given length,
the  procedure  creates  and  sorts  an  array  substr-rank[1:n]  of  n  objects,
each with the following attributes:

left-rank contains the rank of the left part of the substring.

right-rank contains the rank of the right part of the substring.

index  contains  the  index  into  the  text  T  of  where  the  substring
starts.

Before delving into the details of how the procedure works, let’s look
at  how  it  operates  on  the  input  text  ratatat,  with  n  =  7.  Assuming
that  the  ord  function  returns  the  ASCII  code  for  a  character,  Figure
32.12  shows  the  substr-rank  array  after  the  for  loop  of  lines  2–7  and
then after the sorting step in line 8. The left-rank and right-rank values
after lines 2–7 are the ranks of length-1 substrings in positions i and i +
1,  for  i  =  1,  2,  …,  n.  These  initial  ranks  are  the  ASCII  values  of  the
characters.  At  this  point,  the  left-rank  and  right-rank  values  give  the
ranks of the left and right part of each substring of length 2. Because
the substring starting at index 7 consists of only one character, its right
part is empty and so its right-rank is 0. After the sorting step in line 8,
the  substr-rank  array  gives  the  relative  lexicographic  order  of  all  the
substrings  of  length  2,  with  starting  points  of  these  substrings  in  the
index  attribute.  For  example,  the  lexicographically  smallest  length-2
substring  is  at,  which  starts  at  position  substr-rank[1].index,  which
equals 2. This substring also occurs at positions substr-rank[2].index = 4
and substr-rank[3].index = 6.

The  procedure  then  enters  the  while  loop  of  lines  10–19.  The  loop
variable  l  gives  an  upper  bound  on  the  length  of  substrings  that  have
been  sorted  thus  far.  Entering  the  while  loop,  therefore,  the  substrings
of length at most l = 2 are sorted. The call of MAKE-RANKS in line
11 gives each of these substrings its rank in the sorted order, from 1 up
to the number of unique length-2 substrings, based on the values it ﬁnds
in the substr-rank array. With l = 2, MAKE-RANKS sets rank[i] to be
the  rank  of  the  length-2  substring  T[i:i  +  1].  Figure  32.13  shows  these
new  ranks,  which  are  not  necessarily  unique.  For  example,  since  the
length-2 substring at occurs at positions 2, 4, and 6, MAKE-RANKS
ﬁnds  that  substr-rank[1],  substr-rank[2],  and  substr-rank[3]  have  equal
values  in  left-rank  and  in  right-rank.  Since  substr-rank[1].index  =  2,
substr-rank[2].index  =  4,  and  substr-rank[3].index  =  6,  and  since  at  is
the  smallest  substring  in  lexicographic  order,  MAKE-RANKS  sets
rank[2] = rank[4] = rank[6] = 1.

art

Figure  32.13  The  rank  array  after  line  11  and  the  substr-rank  array  after  lines  12–17  and  after
line 18 in the ﬁrst iteration of the while loop of lines 10–19, where l = 2.

This iteration of the while loop will sort the substrings of length at
most 4 based on the ranks from sorting the substrings of length at most
2.  The  for  loop  of  lines  12–17  reconstitutes  the  substr-rank  array,  with
substr-rank[i].left-rank  based  on  rank[i]  (the  rank  of  the  length-2
substring T[i:i+1]) and substr-rank[i].right-rank based on rank[i + 2] (the
rank of the length-2 substring T[i + 2:i + 3], which is 0 if this substring
starts  beyond  the  end  of  the  length-n  text).  Together,  these  two  ranks
give  the  relative  rank  of  the  length-4  substring  T[i:i  +  3].  Figure  32.13
shows  the  effect  of  lines  12–17.  The  ﬁgure  also  shows  the  result  of
sorting the substr-rank array in line 18, based on the left-rank attribute,
and  using  the  right-rank  attribute  to  break  ties.  Now  substr-rank  gives
the lexicographically sorted order of all substrings with length at most
4.

The next iteration of the while loop, with l = 4, sorts the substrings
of  length  at  most  8  based  on  the  ranks  from  sorting  the  substrings  of
length  at  most4  4.  Figure  32.14  shows  the  ranks  of  the  length-4
substrings  and  the  substr-rank  array  before  and  after  sorting.  This
iteration is the ﬁnal one, since with the length n of the text equaling 7,
the procedure has sorted all substrings.

art

Figure  32.14  The  rank  array  after  line  11  and  the  substr-rank  array  after  lines  12–17  and  after
line 18 in the second—and ﬁnal—iteration of the while loop of lines 10–19, where l = 4.

In  general,  as  the  loop  variable  l  increases,  more  and  more  of  the
right  parts  of  the  substrings  are  empty.  Therefore,  more  of  the  right-
rank values are 0. Because i is at most n within the loop of lines 12–17,
the left part of each substring is always nonempty, and so all left-rank
values are always positive.

This  example  illuminates  why  the  COMPUTE-SUFFIX-ARRAY
procedure works. The initial ranks established in lines 2–7 are simply the

ord  values  of  the  characters  in  the  text,  and  so  when  line  8  sorts  the
substr-rank array, its ordering corresponds to the lexicographic ordering
of the length-2 substrings. Each iteration of the while loop of lines 10–
19 takes sorted substrings of length l and produces sorted substrings of
length 2l. Once l reaches or exceeds n, all substrings have been sorted.

Within  an

iteration  of  the  while

loop,  the  MAKE-RANKS
procedure  “re-ranks”  the  substrings  that  were  sorted,  either  by  line  8
before the ﬁrst iteration or by line 18 in the previous iteration. MAKE-
RANKS takes a substr-rank array, which has been sorted, and ﬁlls in an
array rank[1:n] so that rank[i] is the rank of the ith substring represented
in the substr-rank array. Each rank is a positive integer, starting from 1,
and  going  up  to  the  number  of  unique  substrings  of  length  2l.
Substrings with equal values of left-rank and right-rank receive the same
rank.  Otherwise,  a  substring  that  is  lexicographically  smaller  than
another appears earlier in the substr-rank array, and it receives a smaller
rank. Once the substrings of length 2l are re-ranked, line 18 sorts them
by rank, preparing for the next iteration of the while loop.

Once l reaches or exceeds n and all substrings are sorted, the values
in  the  index  attributes  give  the  starting  positions  of  the  sorted
substrings.  These  indices  are  precisely  the  values  that  constitute  the
sufﬁx array.

Let’s  analyze  the  running  time  of  COMPUTE-SUFFIX-ARRAY.
Lines 1–7 take Θ(n) time. Line 8 takes O(n 1g n) time, using either merge
sort (see Section 2.3.1) or heapsort (see Chapter 6). Because the value of
l  doubles  in  each  iteration  of  the  while  loop  of  lines  10–19,  this  loop
makes  ⌈1g  n⌉  –  1  iterations.  Within  each  iteration,  the  call  of  MAKE-
RANKS takes Θ(n) time, as does the for loop of lines 12–17. Line 18,
like  line  8,  takes  O(n  1g  n)  time,  using  either  merge  sort  or  heapsort.
Finally, the for loop of lines 20–21 takes Θ(n) time. The total time works
out to O(n 1g2 n).

A simple observation allows us to reduce the running time to Θ(n 1g
n).  The  values  of  left-rank  and  right-rank  being  sorted  in  line  18  are
always  integers  in  the  range  0  to  n.  Therefore,  radix  sort  can  sort  the
substr-rank  array  in  Θ(n)  time  by  ﬁrst  running  counting  sort  (see
Chapter  8)  based  on  right-rank  and  then  running  counting  sort  based

on left-rank. Now each iteration of the while loop of lines 10–19 takes
only Θ(n) time, giving a total time of Θ(n 1g n).

Exercise  32.5-2  asks  you  to  make  a  simple  modiﬁcation  to
COMPUTE-SUFFIX-ARRAY  that  allows  the  while  loop  of  lines  10–
19 to iterate fewer than ⌈1g n⌉ – 1 times for certain inputs.

Computing the LCP array

Recall that LCP[i] is deﬁned as the length of the longest common preﬁx
of  the  (i  –  1)st  and  ith  lexicographically  smallest  sufﬁxes  T[SA[i  –  1]:]
and T[SA[i]:]. Because T[SA[1]:] is the lexicographically smallest sufﬁx,
we deﬁne LCP[1] to be 0.

In order to compute the LCP array, we need an array rank that is the
inverse  of  the  SA  array,  just  like  the  ﬁnal  rank  array  in  COMPUTE-
SUFFIX-ARRAY:  if  SA[i]  =  j,  then  rank[j]  =  i.  That  is,  we  have
rank[SA[i]] = i for i = 1, 2, …, n. For a sufﬁx T[i:], the value of rank[i]
gives  the  position  of  this  sufﬁx  in  the  lexicographically  sorted  order.
Figure  32.11  includes  the  rank  array  for  the  ratatat  example.  For
example,  the  sufﬁx  tat  is  T[5:].  To  ﬁnd  this  sufﬁx’s  position  in  the
sorted order, look up rank[5] = 6.

To  compute  the  LCP  array,  we  will  need  to  determine  where  in  the
lexicographically  sorted  order  a  sufﬁx  appears,  but  with  its  ﬁrst
character  removed.  The  rank  array  helps.  Consider  the  ith  smallest
sufﬁx,  which  is  T[SA[i]:].  Dropping  its  ﬁrst  character  gives  the  sufﬁx
T[SA[i] + 1:], that is, the sufﬁx starting at position SA[i] + 1 in the text.
The location of this sufﬁx in the sorted order is given by rank[SA[i] + 1].
For example, for the sufﬁx atat, let’s see where to ﬁnd tat (atat with
its  ﬁrst  character  removed)  in  the  lexicographically  sorted  order.  The
sufﬁx  atat  appears  in  position  2  of  the  sufﬁx  array,  and  SA[2]  =  4.
Thus,  rank[SA[2]  +  1]  =  rank[5]  =  6,  and  sure  enough  the  sufﬁx  tat
appears in location 6 in the sorted order.

The procedure COMPUTE-LCP on the next page produces the LCP

array. The following lemma helps show that the procedure is correct.

COMPUTE-LCP(T, SA, n)
  1 allocate arrays rank[1:n] and LCP[1:n]

rank[SA[i]] = i

  2 for i = 1 to n
  3
  4 LCP[1] = 0
  5 l = 0
  6 for i = 1 to n
  7

if rank[i] > 1

// by deﬁnition
// also by deﬁnition
// initialize length of LCP

  8

  9

10

11

12

13

j = SA[rank[i] – 1] // T[j:] precedes T[i:] lexicographically
m = max {i, j }
while m + l ≤ n and T[i + l] == T[j + l]

l = l + 1
LCP[rank[i]] = l
if l > 0

// next character is in common preﬁx
// length of LCP of T[j:] and T[i:]

14
15 return LCP

l = l – 1

// peel off ﬁrst character of common preﬁx

Lemma 32.8
Consider sufﬁxes T[i – 1:] and T[i:], which appear at positions rank[i – 1]
and rank[i], respectively, in the lexicographically sorted order of sufﬁxes.
If LCP[rank[i – 1]] = l > 1, then the sufﬁx T[i:], which is T[i – 1:] with its
ﬁrst character removed, has LCP[rank[i]] ≥ l – 1.

Proof      The  sufﬁx  T[i  –  1:]  appears  at  position  rank[i  –  1]  in  the
lexicographically sorted order. The sufﬁx immediately preceding it in the
sorted order appears at position rank[i – 1] – 1 and is T[SA[rank[i – 1] –
1]:].  By  assumption  and  the  deﬁnition  of  the  LCP  array,  these  two
sufﬁxes,  T[SA[rank[i–1]–1]:]  and  T[i–1:],  have  a  longest  common  preﬁx
of length l > 1. Removing the ﬁrst character from each of these sufﬁxes
gives the sufﬁxes T[SA[rank[i – 1] – 1] + 1:] and T[i:], respectively. These
sufﬁxes have a longest common preﬁx of length l – 1. If T[SA[rank[i – 1]
– 1] + 1:] immediately precedes T[i:] in the lexicographically sorted order
(that is, if rank[SA[rank[i – 1] – 1] + 1] = rank[i] – 1), then the lemma is
proven.

So now assume that T[SA[rank[i – 1] – 1] + 1:] does not immediately
precede  T[i:]  in  the  sorted  order.  Since  T[SA[rank[i  –  1]  –  1]:]
immediately  precedes  T[i–1:]  and  they  have  the  same  ﬁrst  l  >  1
characters,  T[SA[rank[i  –  1]  –  1]  +  1:]  must  appear  in  the  sorted  order

somewhere  before  T[i:],  with  one  or  more  other  sufﬁxes  intervening.
Each  of  these  sufﬁxes  must  start  with  the  same  l  –  1  characters  as
T[SA[rank[i – 1] – 1] + 1:] and T[i:], for otherwise it would appear either
before  T[SA[rank[i  –  1]  –  1]  +  1:]  or  after  T[i:].  Therefore,  whichever
sufﬁx  appears  in  position  rank[i]  –  1,  immediately  before  T[i:],  has  at
least its ﬁrst l – 1 characters in common with T[i:]. Thus, LCP[rank[i]] ≥
l – 1.

▪

The  COMPUTE-LCP  procedure  works  as  follows.  After  allocating
the rank and LCP arrays in line 1, lines 2–3 ﬁll in the rank array and line
4 pegs LCP[1] to 0, per the deﬁnition of the LCP array.

The for loop of lines 6–14 ﬁlls in the rest of the LCP array going by
decreasing-length sufﬁxes. That is, it ﬁlls the position of the LCP array
in  the  order  rank[1],  rank[2],  rank[3],  …,  rank[n],  with  the  assignment
occurring  in  line  12.  Upon  considering  a  sufﬁx  T[i:],  line  8  determines
the  sufﬁx  T[j:]  that  immediately  precedes  T[i:]  in  the  lexicographically
sorted order. At this point, the longest common preﬁx of T[j:] and T[i:]
has  length  at  least  l.  This  property  certainly  holds  upon  the  ﬁrst
iteration  of  the  for  loop,  when  l  =  0.  Assuming  that  line  12  sets
LCP[rank[i]] correctly, line 14 (which decrements l if it is positive) and
Lemma  32.8  maintain  this  property  for  the  next  iteration.  The  longest
common preﬁx of T[j:] and T[i:] might be even longer than the value of
l at the start of the iteration, however. Lines 9–11 increment l for each
additional character the preﬁxes have in common so that it achieves the
length  of  the  longest  common  preﬁx.  The  index  m  is  set  in  line  9  and
used in the test in line 10 to make sure that the test T[i + l] == T[j + l]
for extending the longest common preﬁx does not run off the end of the
text T. When the while loop of lines 10–11 terminates, l is the length of
the longest common preﬁx of T[j:] and T[i:].

As  a  simple  aggregate  analysis  shows,  the  COMPUTE-LCP
procedure runs in Θ(n) time. Each of the two for loops iterates n times,
and  so  it  remains  only  to  bound  the  total  number  of  iterations  by  the
while loop of lines 10–11. Each iteration increases l by 1, and the test m
+ l ≤ n ensures that l is always less than n. Because l has an initial value

of  0  and  decreases  at  most  n  –  1  times  in  line  14,  line  11  increments  l
fewer than 2n times. Thus, COMPUTE-LCP takes Θ(n) time.

Exercises

32.5-1
Show the substr-rank and rank arrays before each iteration of the while
loop  of  lines  10–19  and  after  the  last  iteration  of  the  while  loop,  the
sufﬁx  array  SA  returned,  and  the  sorted  sufﬁxes  when  COMPUTE-
SUFFIX-ARRAY  is  run  on  the  text  hippityhoppity.  Use  the
position of each letter in the alphabet as its ord value, so that ord(b) =
2. Then show the LCP array after each iteration of the for loop of lines
6–14  of  COMPUTE-LCP  given  the  text  hippityhoppity  and  its
sufﬁx array.

32.5-2
For  some  inputs,  the  COMPUTE-SUFFIX-ARRAY  procedure  can
produce  the  correct  result  with  fewer  than  ⌈1g  n⌉  –  1  iterations  of  the
while loop of lines 10–19. Modify COMPUTE-SUFFIX-ARRAY (and,
if  necessary,  MAKE-RANKS)  so  that  the  procedure  can  stop  before
making  all  ⌈1g  n⌉  –  1  iterations  in  some  cases.  Describe  an  input  that
allows  the  procedure  to  make  O(1)  iterations.  Describe  an  input  that
forces the procedure to make the maximum number of iterations.

32.5-3
Given two texts, T1 of length n1 and T2 of length n2, show how to use
the  sufﬁx  array  and  longest  common  preﬁx  array  to  ﬁnd  all  of  the
longest common substrings, that is, the longest substrings that appear in
both  T1  and  T2.  Your  algorithm  should  run  in  O(n  1g  n  +  kl)  time,
where  n  =  n1  +  n2  and  there  are  k  such  longest  substrings,  each  with
length l.

32.5-4
Professor  Markram  proposes  the  following  method  to  ﬁnd  the  longest
palindromes  in  a  string  T[1:n]  by  using  its  sufﬁx  array  and  LCP  array.

(Recall from Problem 14-2 that a palindrome is a nonempty string that
reads the same forward and backward.)

Let  @  be  a  character  that  does  not  appear  in  T.  Construct  the
text  T′  as  the  concatenation  of  T,  @,  and  the  reverse  of  T.
Denote the length of T′ by n′ = 2n + 1. Create the sufﬁx array
SA  and  LCP  array  LCP  for  T′.  Since  the  indices  for  a
palindrome  and  its  reverse  appear  in  consecutive  positions  in
the  sufﬁx  array,  ﬁnd  the  entries  with  the  maximum  LCP  value
LCP[i]  such  that  SA[i  –  1]  =  n′  –  SA[i]  –  LCP[i]  +  2.  (This
constraint  prevents  a  substring—and  its  reverse—from  being
construed as a palindrome unless it really is one.) For each such
index  i,  one  of  the  longest  palindromes  is  T′[SA[i]:SA[i]  +
LCP[i] – 1].

For example, if the text T is unreferenced, with n = 12, then the
text  T′  is  unreferenced@decnerefernu,  with  n′  =  25  and  the
following sufﬁx array and LCP array:

art

The maximum LCP value is achieved at LCP[21] = 5, and SA[20] = 3 =
n′ – SA[21] – LCP[21] + 2. The sufﬁxes of T′ starting at indices SA[20]
and SA[21] are referenced@decnerefernu and refernu, both of
which start with the length-5 palindrome refer.

Alas, this method is not foolproof. Give an input string T that causes
this method to give results that are shorter than the longest palindrome
contained  within  T,  and  explain  why  your  input  causes  the  method  to
fail.

Problems

32-1     String matching based on repetition factors
Let  yi  denote  the  concatenation  of  string  y  with  itself  i  times.  For
example,  (ab)3  =  ababab.  We  say  that  a  string  x  ∈  ∑*  has  repetition

factor r if x = yr for some string y ∈ ∑* and some r > 0. Let ρ(x) denote
the largest r such that x has repetition factor r.

a. Give an efﬁcient algorithm that takes as input a pattern P[1:m] and
computes the value ρ(P[:i]) for i = 1, 2, …, m. What is the running
time of your algorithm?

b. For any pattern P[1:m], let ρ*(P) be deﬁned as max {ρ(P[:i]) : 1 ≤ i ≤
m}. Prove that if the pattern P is chosen randomly from the set of all
binary strings of length m, then the expected value of ρ*(P) is O(1).
c. Argue that the procedure REPETITION-MATCHER correctly ﬁnds
all occurrences of pattern P[1:m] in text T[1:n] in O(ρ*(P)n + m) time.
(This algorithm is due to Galil and Seiferas. By extending these ideas
greatly, they obtained a linear-time string-matching algorithm that
uses only O(1) storage beyond what is required for P and T.)

REPETITION-MATCHER(T, P, n, m)
  1 k = 1 + ρ*(P)
  2 q = 0
  3 s = 0
  4 while s ≤ n – m
  5

if T[s + q + 1] == P[q + 1]

  6

  7

  8

  9

10

11

q = q + 1
if q == m

print “Pattern occurs with shift” s

if q == m or T[s + q + 1] ≠ P[q + 1]

s = s + max {1, ⌈q/k⌉}
q = 0

32-2     A linear-time sufﬁx-array algorithm
In this problem, you will develop and analyze a linear-time divide-and-
conquer  algorithm  to  compute  the  sufﬁx  array  of  a  text  T[1:n].  As  in
Section 32.5, assume that each character in the text is represented by an
underlying encoding, which is a positive integer.

The  idea  behind  the  linear-time  algorithm  is  to  compute  the  sufﬁx
array for the sufﬁxes starting at 2/3 of the positions in the text, recursing
as  needed,  use  the  resulting  information  to  sort  the  sufﬁxes  starting  at
the  remaining  1/3  of  the  positions,  and  then  merge  the  sorted
information in linear time to produce the full sufﬁx array.

For i = 1, 2, …, n, if i mod 3 equals 1 or 2, then i is a sample position,
and the sufﬁxes starting at such positions are sample sufﬁxes. Positions
3, 6, 9, … are nonsample positions, and the sufﬁxes starting at nonsample
positions are nonsample sufﬁxes.

The algorithm sorts the sample sufﬁxes, sorts the nonsample sufﬁxes
(aided  by  the  result  of  sorting  the  sample  sufﬁxes),  and  merges  the
sorted  sample  and  nonsample  sufﬁxes.  Using  the  example  text  T  =
bippityboppityboo, here is the algorithm in detail, listing substeps
of each of the above steps:

1. The sample sufﬁxes comprise about 2/3 of the sufﬁxes. Sort them by
the following substeps, which work with a heavily modiﬁed version of
T and may require recursion. In part (a) of this problem on page 999,
you will show that the orders of the sufﬁxes of T and the sufﬁxes of
the modiﬁed version of T are the same.

A. Construct two texts P1 and P2 made up of “metacharacters” that
are actually substrings of three consecutive characters from T. We
delimit each such metacharacter with parentheses. Construct

P1 = (T[1:3])(T[4:6])(T[7:9]) ⋯ (T[n′:n′ + 2]),

where n′ is the largest integer congruent to 1, modulo 3, that is less
than  or  equal  to  n  and  T  is  extended  beyond  position  n  with  the
special  character  Ø,  with  encoding  0.  With  the  example  text  T  =
bippityboppityboo, we get that
P1 = (bip) (pit) (ybo) (ppi) (tyb) (ooØ).
Similarly, construct

P2 = (T[2:4])(T[5:7])(T[8:10]) ⋯ (T[n″:n″ + 2]),

where n″ is the largest integer congruent to 2, modulo 3, that is less
than or equal to n. For our example, we have

P2 = (ipp) (ity) (bop) (pit) (ybo) (oØØ).

art

Figure  32.15  Computed  values  when  sorting  the  sample  sufﬁxes  of  the  linear-time  sufﬁx-array
algorithm for the text T = bippityboppityboo.

If n is a multiple of 3, append the metacharacter (ØØØ) to the end
of  P1.  In  this  way,  P1  is  guaranteed  to  end  with  a  metacharacter
containing Ø. (This property helps in part (a) of this problem.) The
text P2 may or may not end with a metacharacter containing Ø.

B. Concatenate P1 and P2 to form a new text P. Figure 32.15 shows P

for our example, along with the corresponding positions of T.

C. Sort and rank the unique metacharacters of P, with ranks starting
from 1. In the example, P has 10 unique metacharacters: in sorted
order, they are (bip), (bop), (ipp), (ity), (oØØ), (ooØ), (pit),
(ppi), (tyb), (ybo). The metacharacters (pit) and (ybo) each
appear twice.

D. As Figure 32.15 shows, construct a new “text” P′ by renaming each

metacharacter in P by its rank. If P contains k unique
metacharacters, then each “character” in P′ is an integer from 1 to
k. The sufﬁx arrays for P and P′ are identical.

E. Compute the sufﬁx array SAP′ of P′. If the characters of P′ (i.e.,

the ranks of metacharacters in P) are unique, then you can
compute its sufﬁx array directly, since the ordering of the individual
characters gives the sufﬁx array. Otherwise, recurse to compute the
sufﬁx array of P′, treating the ranks in P′ as the input characters in
the recursive call. Figure 32.15 shows the sufﬁx array SAP′ for our
example. Since the number of metacharacters in P, and hence the

length of P′, is approximately 2n/3, this recursive subproblem is
smaller than the current problem.

F. From SAP′ and the positions in T corresponding to the sample
positions, compute the list of positions of the sorted sample
sufﬁxes of the original text T. Figure 32.15 shows the list of
positions in T of the sorted sample sufﬁxes in our example.

2. The nonsample sufﬁxes comprise about 1/3 of the sufﬁxes. Using the
sorted sample sufﬁxes, sort the nonsample sufﬁxes by the following
substeps.

Figure 32.16 The ranks r1 through rn+3 for the text T = bippityboppityboo with n = 17.

G. Extending the text T by the two special characters ØØ, so that T

now has n + 2 characters, consider each sufﬁx T[i:] for i = 1, 2, …, n
+ 2. Assign a rank ri to each sufﬁx T[i:]. For the two special
characters ØØ, set rn+1 = rn+2 = 0. For the sample positions of T,
base the rank on the list of sorted sample positions of T. The rank
is currently undeﬁned for the nonsample positions of T. For these
positions, set ri = ☐. Figure 32.16 shows the ranks for T =
bippityboppityboo with n = 17.

H. Sort the nonsample sufﬁxes by comparing tuples (T[i], ri+1). In

our example, we get T[15:] < T[12:] < T[9:] < T[3:] < T[6:] because
(b, 6) < (i, 10) < (o, 9) < (p, 8) < (t, 12).

3. Merge the sorted sets of sufﬁxes. From the sorted set of sufﬁxes,

determine the sufﬁx array of T.

This completes the description of a linear-time algorithm for computing
sufﬁx arrays. The following parts of this problem ask you to show that

certain steps of this algorithm are correct and to analyze the algorithm’s
running time.

a. Deﬁne a nonempty sufﬁx at position i of the text P created in substep
B as all metacharacters from position i of P up to and including the
ﬁrst metacharacter of P in which Ø appears or the end of P. In the
example shown in Figure 32.15, the nonempty sufﬁxes of P starting at
positions 1, 4, and 11 of P are (bip) (pit) (ybo) (ppi) (tyb) (ooØ),
(ppi) (tyb) (ooØ), and (ybo) (oØØ), respectively. Prove that the order
of sufﬁxes of P is the same as the order of its nonempty sufﬁxes.
Conclude that the order of sufﬁxes of P gives the order of the sample
sufﬁxes of T. (Hint: If P contains duplicate metacharacters, consider
separately the cases in which two sufﬁxes both start in P1, both start
in P2, and one starts in P1 and the other starts in P2. Use the
property that Ø appears in the last metacharacter of P1.)

b. Show how to perform substep C in Θ(n) time, bearing in mind that in

a recursive call, the characters in T are actually ranks in P′ in the
caller.

c. Argue that the tuples in substep H are unique. Then show how to

perform this substep in Θ(n) time.

d. Consider two sufﬁxes T[i:] and T[j:], where T[i:] is a sample sufﬁx and

T[j:] is a nonsample sufﬁx. Show how to determine in Θ(1) time
whether T[i:] is lexicographically smaller than T[j:]. (Hint: Consider
separately the cases in which i mod 3 = 1 and i mod 3 = 2. Compare
tuples whose elements are characters in T and ranks as shown in
Figure 32.16. The number of elements per tuple may depend on
whether i mod 3 equals 1 or 2.) Conclude that step 3 can be performed
in Θ(n) time.

e. Justify the recurrence T(n) ≤ T (2n/3 + 2) + Θ(n) for the running time
of the full algorithm, and show that its solution is O(n). Conclude
that the algorithm runs in Θ(n) time.

32-3     Burrows-Wheeler transform

character

The  Burrows-Wheeler  transform,  or  BWT,  for  a  text  T  is  deﬁned  as
follows.  First,  append  a  new
compares  as
lexicographically  less  than  every  character  of  T,  and  denote  this
character by $ and the resulting string by T′. Letting n be the length of
T′,  create  n  rows  of  characters,  where  each  row  is  one  of  the  n  cyclic
rotations of T′. Next, sort the rows lexicographically. The BWT is then
the string of n characters in the rightmost column, read top to bottom.
For  example,  let  T  =  rutabaga,  so  that  T′  =  rutabaga$.  The

that

cyclic rotations are

rutabaga$
utabaga$r
tabaga$ru
abaga$rut
baga$ruta
aga$rutab
ga$rutaba
a$rutabag
$rutabaga
Sorting the rows and numbering the sorted rows gives

1 $rutabaga
2 a$rutabag
3 abaga$rut
4 aga$rutab
5 baga$ruta
6 ga$rutaba
7 rutabaga$
8 tabaga$ru
9 utabaga$r
The BWT is the rightmost column, agtbaa$ur. (The row numbering
will be helpful in understanding how to compute the inverse BWT.)

The  BWT  has  applications  in  bioinformatics,  and  it  can  also  be  a
step  in  text  compression.  That  is  because  it  tends  to  place  identical
characters together, as in the BWT of rutabaga, which places two of

the  instances  of  a  together.  When  identical  characters  are  placed
together,  or  even  nearby,  additional  means  of  compressing  become
available. Following the BWT, combinations of move-to-front encoding,
run-length  encoding,  and  Huffman  coding  (see  Section  15.3)  can
provide signiﬁcant text compression. Compression ratios with the BWT
tend improve as the text length increases.

a. Given the sufﬁx array for T′, show how to compute the BWT in Θ(n)

time.

In order to decompress, the BWT must be invertible. Assuming that
the alphabet size is constant, the inverse BWT can be computed in Θ(n)
time from the BWT. Let’s look at the BWT of rutabaga, denoting it
by  BWT[1:n].  Each  character  in  the  BWT  has  a  unique  lexicographic
rank from 1 to n. Denote the rank of BWT[i] by rank[i]. If a character
appears multiple times in the BWT, each instance of the character has a
rank  1  greater  than  the  previous  instance  of  the  character.  Here  are
BWT and rank for rutabaga:

art

For  example,  rank[1]  =  2  because  BWT[1]  =  a  and  the  only  character
that  precedes  the  ﬁrst  a  lexicographically  is  $  (which  we  deﬁned  to
precede all other characters, so that $ has rank 1). Next, we have rank[2]
=  6  because  BWT[2]  =  g  and  ﬁve  characters  in  the  BWT  precede  g
lexicographically: $, the three instances of a, and b. Jumping ahead to
rank[5]  =  3,  that  is  because  BWT[5]  =  a,  and  because  this  a  is  the
second  instance  of  a  in  the  BWT,  its  rank  value  is  1  greater  than  the
rank value for the previous instance of a, in position 1.

There  is  enough  information  in  BWT  and  rank  to  reconstruct  T′
from back to front. Suppose that you know the rank r of a character c
in T′. Then c is the ﬁrst character in row r of the sorted cyclic rotations.
The last character in row r must be the character that precedes c in T′.
But you know which character is the last character in row r, because it is
BWT[r]. To reconstruct T′ from back to front, start with $, which you
can  ﬁnd  in  BWT.  Then  work  backward  using  BWT  and  rank  to
reconstruct T′.

Let’s see how this strategy works for rutabaga. The last character
of T′, $, appears in position 7 of BWT. Since rank[7] = 1, row 1 of the
sorted cyclic rotations of T′ begins with $. The character that precedes
$ in T′ is the last character in row 1, which is BWT[1]: a. Now we know
that the last two characters of T′ are a$. Looking up rank[1], it equals
2, so that row 2 of the sorted cyclic rotations of T′ begins with a. The
last character in row 2 precedes a in T′, and that character is BWT[2] =
g.  Now  we  know  that  the  last  three  characters  of  T′  are  ga$.
Continuing  on,  we  have  rank[2]  =  6,  so  that  row  6  of  the  sorted  cyclic
rotations begins with g. The character preceding g in T′ is BWT[6] = a,
and so the last four characters of T′ are aga$. Because rank[6] = 4, a
begins  row  4  of  the  sorted  cyclic  rotations  of  T′.  The  character
preceding a in T′ is the last character in row 4, BWT[4] = b, and the last
ﬁve characters of T′ are baga$. And so on, until all n characters of T′
have been identiﬁed, from back to front.

b. Given the array BWT[1:n], write pseudcode to compute the array
rank[1:n] in Θ(n) time, assuming that the alphabet size is constant.

c. Given the arrays BWT[1:n] and rank[1:n], write pseudocode to

compute T′ in Θ(n) time.

Chapter notes

The  relation  of  string  matching  to  the  theory  of  ﬁnite  automata  is
discussed  by  Aho,  Hopcroft,  and  Ullman  [5].  The  Knuth-Morris-Pratt
algorithm [267] was invented independently by Knuth and Pratt and by
Morris, but they published their work jointly. Matiyasevich [317] earlier
discovered a similar algorithm, which applied only to an alphabet with
two  characters  and  was  speciﬁed  for  a  Turing  machine  with  a  two-
dimensional tape. Reingold, Urban, and Gries [377] give an alternative
treatment  of  the  Knuth-Morris-Pratt  algorithm.  The  Rabin-Karp
algorithm  was  proposed  by  Karp  and  Rabin  [250].  Galil  and  Seiferas
[173]  give  an  interesting  deterministic  linear-time  string-matching
algorithm  that  uses  only  O(1)  space  beyond  that  required  to  store  the
pattern and text.

The sufﬁx-array algorithm in Section 32.5 is by Manber and Myers
[312],  who  ﬁrst  proposed  the  notion  of  sufﬁx  arrays.  The  linear-time
algorithm to compute the longest common preﬁx array presented here is
by  Kasai  et  al.  [252].  Problem  32-2  is  based  on  the  DC3  algorithm  by
Kärkkäinen, Sanders, and Burkhardt [245]. For a survey of sufﬁx-array
algorithms, see the article by Puglisi, Smyth, and Turpin [370]. To learn
more about the Burrows-Wheeler transform from Problem 32-3, see the
articles by Burrows and Wheeler [78] and Manzini [314].

1 For sufﬁx arrays, the preprocessing time of O(n 1g n) comes from the algorithm presented in
Section 32.5. It can be reduced to Θ(n) by using the algorithm in Problem 32-2. The factor k in
the matching time denotes the number of occurrences of the pattern in the text.
2 We write Θ(n – m + 1) instead of Θ(n – m) because s takes on n − m + 1 different values. The
“+1”  is  signiﬁcant  in  an  asymptotic  sense  because  when  m  =  n,  computing  the  lone  ts  value
takes Θ(1) time, not Θ(0) time.
3 Informally, lexicographic order is “alphabetical order” in the underlying character set. A more
precise deﬁnition of lexicographic order appears in Problem 12-2 on page 327.
4  Why  keep  saying  “length  at  most”?  Because  for  a  given  value  of  l,  a  substring  of  length  l
starting at position i is T[i:i + l – 1]. If i + l − 1 > n, then the substring cuts off at the end of the
text.

