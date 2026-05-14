23        All-Pairs Shortest Paths

In  this  chapter,  we  turn  to  the  problem  of  ﬁnding  shortest  paths
between  all  pairs  of  vertices  in  a  graph.  A  classic  application  of  this
problem  occurs  in  computing  a  table  of  distances  between  all  pairs  of
cities  for  a  road  atlas.  Classic  perhaps,  but  not  a  true  application  of
ﬁnding shortest paths between all pairs of vertices. After all, a road map
modeled as a graph has one vertex for every road intersection and one
edge  wherever  a  road  connects  intersections.  A  table  of  intercity
distances  in  an  atlas  might  include  distances  for  100  cities,  but  the
signal-controlled
United
intersections1 and many more uncontrolled intersections.

approximately

300,000

States

has

A  legitimate  application  of  all-pairs  shortest  paths  is  to  determine
the diameter of a network: the longest of all shortest paths. If a directed
graph  models  a  communication  network,  with  the  weight  of  an  edge
indicating the time required for a message to traverse a communication
link,  then  the  diameter  gives  the  longest  possible  transit  time  for  a
message in the network.

As in Chapter 22, the input is a weighted, directed graph G = (V, E)
with  a  weight  function  w  :  E  →  ℝ  that  maps  edges  to  real-valued
weights. Now the goal is to ﬁnd, for every pair of vertices u, v ∈ V, a
shortest  (least-weight)  path  from  u  to  v,  where  the  weight  of  a  path  is
the  sum  of  the  weights  of  its  constituent  edges.  For  the  all-pairs
problem, the output typically takes a tabular form in which the entry in
u’s row and v’s column is the weight of a shortest path from u to v.

You  can  solve  an  all-pairs  shortest-paths  problem  by  running  a
single-source  shortest-paths  algorithm  |V|  times,  once  with  each  vertex
as the source. If all edge weights are nonnegative, you can use Dijkstra’s
algorithm. If you implement the min-priority queue with a linear array,
the running time is O(V3 + VE) which is O(V3). The binary min-heap
implementation  of  the  min-priority  queue  yields  a  running  time  of
O(V(V + E) lg V). If |E| = Ω(V), the running time becomes O(VE lg V),
which is faster than O(V3) if the graph is sparse. Alternatively, you can
implement  the  min-priority  queue  with  a  Fibonacci  heap,  yielding  a
running time of O(V2 lg V + VE).

If  the  graph  contains  negative-weight  edges,  Dijkstra’s  algorithm
doesn’t work, but you can run the slower Bellman-Ford algorithm once
from  each  vertex.  The  resulting  running  time  is  O(V2E),  which  on  a
dense  graph  is  O(V4).  This  chapter  shows  how  to  guarantee  a  much
better  asymptotic  running  time.  It  also  investigates  the  relation  of  the
all-pairs shortest-paths problem to matrix multiplication.

Unlike the single-source algorithms, which assume an adjacency-list
representation  of  the  graph,  most  of  the  algorithms  in  this  chapter
represent  the  graph  by  an  adjacency  matrix.  (Johnson’s  algorithm  for
sparse graphs, in Section 23.3, uses adjacency lists.) For convenience, we
assume that the vertices are numbered 1, 2, … , |V|, so that the input is
an n × n matrix W = (wij) representing the edge weights of an n-vertex
directed graph G = (V, E), where

The  graph  may  contain  negative-weight  edges,  but  we  assume  for  the
time being that the input graph contains no negative-weight cycles.

The tabular output of each of the all-pairs shortest-paths algorithms
presented  in  this  chapter  is  an  n  ×  n  matrix.  The  (i,  j)  entry  of  the
output  matrix  contains  δ(i,  j),  the  shortest-path  weight  from  vertex  i  to
vertex j, as in Chapter 22.

A  full  solution  to  the  all-pairs  shortest-paths  problem  includes  not
only  the  shortest-path  weights  but  also  a  predecessor  matrix  Π  =  (πij),
where  πij  is  NIL  if  either  i  =  j  or  there  is  no  path  from  i  to  j,  and
otherwise πij is the predecessor of j on some shortest path from i. Just as
the  predecessor  subgraph  Gπ  from  Chapter  22  is  a  shortest-paths  tree
for a given source vertex, the subgraph induced by the ith row of the Π
matrix should be a shortest-paths tree with root i. For each vertex i ∈
V, the predecessor subgraph of G for i is Gπ,i = (Vπ,i, Eπ,i), where

Vπ,i = {j ∈ V : πij ≠ NIL} ∪ {i},
Eπ,i = {(πij, j) : j ∈ Vπ,i − {i}}.

If Gπ,i is a shortest-paths tree, then PRINT-ALL-PAIRS-SHORTEST-
PATH  on  the  following  page,  which  is  a  modiﬁed  version  of  the
PRINT-PATH procedure from Chapter 20, prints a shortest path from
vertex i to vertex j.

In order to highlight the essential features of the all-pairs algorithms
in  this  chapter,  we  won’t  cover  how  to  compute  predecessor  matrices
and  their  properties  as  extensively  as  we  dealt  with  predecessor
subgraphs in Chapter 22. Some of the exercises cover the basics.

PRINT-ALL-PAIRS-SHORTEST-PATH(Π, i, j)
1 if i == j
print i
2
3 elseif πij == NIL
4
5 else PRINT-ALL-PAIRS-SHORTEST-PATH(Π, i, πij)
6

print “no path from” i “to” j “exists”

print j

Chapter outline

Section  23.1  presents  a  dynamic-programming  algorithm  based  on
matrix multiplication to solve the all-pairs shortest-paths problem. The

technique of “repeated squaring” yields a running time of Θ(V3 lg V).
Section 23.2 gives another dynamic-programming algorithm, the Floyd-
Warshall algorithm, which runs in Θ(V3) time. Section 23.2 also covers
the problem of ﬁnding the transitive closure of a directed graph, which
is  related  to  the  all-pairs  shortest-paths  problem.  Finally,  Section  23.3
presents  Johnson’s  algorithm,  which  solves  the  all-pairs  shortest-paths
problem in O(V2 lg V + VE) time and is a good choice for large, sparse
graphs.

Before  proceeding,  we  need  to  establish  some  conventions  for
adjacency-matrix  representations.  First,  we  generally  assume  that  the
input graph G = (V, E) has n vertices, so that n = |V|. Second, we use the
convention of denoting matrices by uppercase letters, such as W, L, or
D,  and  their  individual  elements  by  subscripted  lowercase  letters,  such
as wij, lij, or dij. Finally, some matrices have parenthesized superscripts,
, to indicate iterates.
as in

 or

23.1    Shortest paths and matrix multiplication

This  section  presents  a  dynamic-programming  algorithm  for  the  all-
pairs  shortest-paths  problem  on  a  directed  graph  G  =  (V,  E).  Each
major  loop  of  the  dynamic  program  invokes  an  operation  similar  to
matrix  multiplication,  so  that  the  algorithm  looks  like  repeated  matrix
multiplication. We’ll start by developing a Θ(V4)-time algorithm for the
all-pairs  shortest-paths  problem,  and  then  we’ll  improve  its  running
time to Θ(V3 lg V).

Before proceeding, let’s brieﬂy recap the steps given in Chapter 14 for

developing a dynamic-programming algorithm:

1. Characterize the structure of an optimal solution.

2. Recursively deﬁne the value of an optimal solution.

3. Compute  the  value  of  an  optimal  solution  in  a  bottom-up

fashion.

We  reserve  the  fourth  step—constructing  an  optimal  solution  from
computed information—for the exercises.

The structure of a shortest path

Let’s  start  by  characterizing  the  structure  of  an  optimal  solution.
Lemma  22.1  tells  us  that  all  subpaths  of  a  shortest  path  are  shortest
paths. Consider a shortest path p from vertex i to vertex j, and suppose
that  p  contains  at  most  r  edges.  Assuming  that  there  are  no  negative-
weight  cycles,  r  is  ﬁnite.  If  i  =  j,  then  p  has  weight  0  and  no  edges.  If
vertices i and j are distinct, then decompose path p into
, where
path p′ now contains at most r − 1 edges. Lemma 22.1 says that p′ is a
shortest path from i to k, and so δ(i, j) = δ(i, k) + wkj.

A recursive solution to the all-pairs shortest-paths problem

Now, let
 be the minimum weight of any path from vertex i to vertex j
that contains at most r edges. When r = 0, there is a shortest path from i
to j with no edges if and only if i = j, yielding

For r ≥ 1, one way to achieve a minimum-weight path from i to j with at
most r edges is by taking a path containing at most r − 1 edges, so that
. Another way is by taking a path of at most r − 1 edges from i
to some vertex k and then taking the edge (k, j), so that
.
Therefore, to examine paths from i to j consisting of at most r edges, try
all possible predecessors k of j, giving the recursive deﬁnition

The last equality follows from the observation that wjj = 0 for all j.

What  are  the  actual  shortest-path  weights  δ(i,  j)?  If  the  graph
contains no negative-weight cycles, then whenever δ(i, j) < ∞, there is a
shortest path from vertex i to vertex j that is simple. (A path p from i to j
that  is  not  simple  contains  a  cycle.  Since  each  cycle’s  weight  is

nonnegative, removing all cycles from the path leaves a simple path with
weight no greater than p’s weight.) Because any simple path contains at
most n − 1 edges, a path from vertex i to vertex j with more than n − 1
edges  cannot  have  lower  weight  than  a  shortest  path  from  i  to  j.  The
actual shortest-path weights are therefore given by

Computing the shortest-path weights bottom up

Taking as input the matrix W = (wij), let’s see how to compute a series
of matrices L(0), L(1), … , L(n−1), where
 for r = 0, 1, … , n −
1.  The  initial  matrix  is  L(0)  given  by  equation  (23.2).  The  ﬁnal  matrix
L(n−1) contains the actual shortest-path weights.

The heart of the algorithm is the procedure EXTEND-SHORTEST-
PATHS,  which  implements  equation  (23.3)  for  all  i  and  j.  The  four
inputs  are  the  matrix  L(r−1)  computed  so  far;  the  edge-weight  matrix
W;  the  output  matrix  L(r),  which  will  hold  the  computed  result  and
whose  elements  are  all  initialized  to  ∞  before  invoking  the  procedure;
and the number n of vertices. The superscripts r and r − 1 help to make
the  correspondence  of  the  pseudocode  with  equation  (23.3)  plain,  but
they play no actual role in the pseudocode. The procedure extends the
shortest paths computed so far by one more edge, producing the matrix
L(r) of shortest-path weights from the matrix L(r−1) computed so far.
Its running time is Θ(n3) due to the three nested for loops.

EXTEND-SHORTEST-PATHS(L(r−1), W, L(r), n)
1 // Assume that the elements of L(r) are initialized to ∞.
2 for i = 1 to n
3

for j = 1 to n

for k = 1 to n

4

5

Let’s  now  understand  the  relation  of  this  computation  to  matrix
multiplication. Consider how to compute the matrix product C = A · B
of  two  n  ×  n  matrices  A  and  B.  The  straightforward  method  used  by
MATRIX-MULTIPLY  on  page  81  uses  a  triply  nested  loop  to
implement equation (4.1), which we repeat here for convenience:

for i, j = 1, 2, … , n. Now make the substitutions

l(r−1) → a,
w → b,
l(r) → c,
min → +,
+ → .

in  equation  (23.3).  You  get  equation  (23.5)!  Making  these  changes  to
EXTEND-SHORTEST-PATHS,  and  also  replacing  ∞  (the  identity  for
min)  by  0  (the  identity  for  +),  yields  the  procedure  MATRIX-
MULTIPLY.  We  can  see  that  the  procedure  EXTEND-SHORTEST-
PATHS(L(r−1),  W,  L(r),  n)  computes  the  matrix  “product”  L(r)  =
L(r−1). W using this unusual deﬁnition of matrix multiplication.2

Thus, we can solve the all-pairs shortest-paths problem by repeatedly
multiplying  matrices.  Each  step  extends  the  shortest-path  weights
computed  so  far  by  one  more  edge  using  EXTEND-SHORTEST-
PATHS(L(r−1),  W,  L(r),  n)  to  perform  the  matrix  multiplication.
Starting with the matrix L(0), we produce the following sequence of n −
1 matrices corresponding to powers of W:

L(1) = L(0) · W = W1,
L(2) = L(1) · W = W2,
L(3) = L(2) · W = W3,

⋮

L(n−1) = L(n−2) · W = Wn−1.

At  the  end,  the  matrix  L(n−1)  =  Wn−1  contains  the  shortest-path
weights.

The  procedure  SLOW-APSP  on  the  next  page  computes  this
sequence in Θ(n4) time. The procedure takes the n × n matrices W and
L(0)  as  inputs,  along  with  n.  Figure  23.1  illustrates  its  operation.  The
pseudocode  uses  two  n  ×  n  matrices  L  and  M  to  store  powers  of  W,
computing M = L · W on each iteration. Line 2 initializes L = L(0). For
each  iteration  r,  line  4  initializes  M  =  ∞,  where  ∞  in  this  context  is  a
matrix of scalar ∞ values. The rth iteration starts with the invariant L =
L(r−1) = Wr−1. Line 6 computes M = L · W = L(r−1) · W = Wr−1 · W
= Wr = L(r) so that the invariant can be restored for the next iteration
by line 7, which sets L = M. At the end, the matrix L = L(n−1) = Wn−1
of shortest-path weights is returned. The assignments to n × n matrices
in  lines  2,  4,  and  7  implicitly  run  doubly  nested  loops  that  take  Θ(n2)
time  for  each  assignment.  The  n  −  1  invocations  of  EXTEND-
SHORTEST-PATHS,  each  of  which  takes  Θ(n3)  time,  dominate  the
computation, yielding a total running time of Θ(n4).

Figure 23.1 A directed graph and the sequence of matrices L(r) computed by SLOW-APSP. You
might want to verify that L(5), deﬁned as L(4) · W, equals L(4), and thus L(r) = L(4) for all r ≥
4.

SLOW-APSP(W, L(0), n)
1 let L = (lij) and M = (mij) be new n × n matrices
2 L = L(0)
3 for r = 1 to n − 1
4 M = ∞       // initialize M
5

// Compute the matrix “product” M = L · W.
EXTEND-SHORTEST-PATHS(L, W, M, n)
L = M

6

7
8 return L

Improving the running time

Bear in mind that the goal is not to compute all the L(r) matrices: only
the matrix L(n−1) matters. Recall that in the absence of negative-weight
cycles,  equation  (23.4)  implies  L(r)  =  L(n−1)  for  all  integers  r  ≥  n  −  1.
Just  as  traditional  matrix  multiplication  is  associative,  so  is  matrix
multiplication
the  EXTEND-SHORTEST-PATHS
procedure  (see  Exercise  23.1-4).  In  fact,  we  can  compute  L(n−1)  with
only  ⌈lg(n  –  1)⌉  matrix  products  by  using  the  technique  of  repeated
squaring:

deﬁned

by

Since 2⌈lg(n – 1)⌉ ≥ n – 1, the ﬁnal product is

.

The  procedure  FASTER-APSP  implements  this  idea.  It  takes  just
the n × n matrix W and the size n as inputs. Each iteration of the while
loop  of  lines  4–8  starts  with  the  invariant  L  =  Wr,  which  it  squares
using  EXTEND-SHORTEST-PATHS  to  obtain  the  matrix  M  =  L2  =
(Wr)2 = W2r. At the end of each iteration, the value of r doubles, and

L  for  the  next  iteration  becomes  M,  restoring  the  invariant.  Upon
exiting the loop when r ≥ n − 1, the procedure returns L = Wr = L(r) =
L(n−1) by equation (23.4). As in SLOW-APSP, the assignments to n × n
matrices  in  lines  2,  5,  and  8  implicitly  run  doubly  nested  loops,  taking
Θ(n2) time for each assignment.

FASTER-APSP(W, n)
1 let L and M be new n × n matrices
2 L = W
3 r = 1
4 while r < n − 1
5 M = ∞
6

EXTEND-SHORTEST-PATHS(L,

L, M, n)

7

8

r = 2r
L = M

9 return L

// initialize M
// compute M = L2

//  ready  for  the  next
iteration

Because  each  of  the  ⌈lg(n  –  1)⌉  matrix  products  takes  Θ(n3)  time,
FASTER-APSP runs in Θ(n3 lg n) time. The code is tight, containing no
elaborate data structures, and the constant hidden in the Θ-notation is
therefore small.

Exercises

23.1-1
Run  SLOW-APSP  on  the  weighted,  directed  graph  of  Figure  23.2,
showing the matrices that result for each iteration of the loop. Then do
the same for FASTER-APSP.

Figure 23.2 A weighted, directed graph for use in Exercises 23.1-1, 23.2-1, and 23.3-1.

23.1-2
Why  is  it  convenient  for  both  SLOW-APSP  and  FASTER-APSP  that
wii = 0 for i = 1, 2, … , n?

23.1-3
What does the matrix

used  in  the  shortest-paths  algorithms  correspond  to  in  regular  matrix
multiplication?

23.1-4
Show  that  matrix  multiplication  deﬁned  by  EXTEND-SHORTEST-
PATHS is associative.

23.1-5
Show  how  to  express  the  single-source  shortest-paths  problem  as  a
product of matrices and a vector. Describe how evaluating this product
corresponds to a Bellman-Ford-like algorithm (see Section 22.1).

23.1-6
Argue  that  we  don’t  need  the  matrix  M  in  SLOW-APSP  because  by
substituting  L  for  M  and  leaving  out  the  initialization  of  M,  the  code
still  works  correctly.  (Hint:  Relate  line  5  of  EXTEND-SHORTEST-

PATHS  to  RELAX  on  page  610.)  Do  we  need  the  matrix  M  in
FASTER-APSP?

23.1-7
Suppose that you also want to compute the vertices on shortest paths in
the  algorithms  of  this  section.  Show  how  to  compute  the  predecessor
matrix Π from the completed matrix L of shortest-path weights in O(n3)
time.

23.1-8
You  can  also  compute  the  vertices  on  shortest  paths  along  with
  as  the  predecessor  of
computing  the  shortest-path  weights.  Deﬁne
vertex  j  on  any  minimum-weight  path  from  vertex  i  to  vertex  j  that
contains  at  most  r  edges.  Modify  the  EXTEND-SHORTEST-PATHS
(2),  …  ,
and  SLOW-APSP  procedures  to  compute  the  matrices  Π
Π

(n−1) as they compute the matrices L(1), L(2), … , L(n−1).

(1),  Π

23.1-9
Modify  FASTER-APSP  so  that  it  can  determine  whether  the  graph
contains a negative-weight cycle.

23.1-10
Give  an  efﬁcient  algorithm  to  ﬁnd  the  length  (number  of  edges)  of  a
minimum-length negative-weight cycle in a graph.

23.2    The Floyd-Warshall algorithm

Having already seen one dynamic-programming solution to the all-pairs
shortest-paths  problem,  in  this  section  we’ll  see  another:  the  Floyd-
Warshall  algorithm,  which  runs  in  Θ(V3)  time.  As  before,  negative-
weight  edges  may  be  present,  but  not  negative-weight  cycles.  As  in
Section  23.1,  we  develop  the  algorithm  by  following  the  dynamic-
programming  process.  After  studying  the  resulting  algorithm,  we
present a similar method for ﬁnding the transitive closure of a directed
graph.

The structure of a shortest path

In  the  Floyd-Warshall  algorithm,  we  characterize  the  structure  of  a
shortest  path  differently  from  how  we  characterized  it  in  Section  23.1.
The  Floyd-Warshall  algorithm  considers  the  intermediate  vertices  of  a
shortest path, where an intermediate vertex of a simple path p = 〈v1, v2,
… , vl〉 is any vertex of p other than v1 or vl, that is, any vertex in the set
{v2, v3, … , vl−1}.

The  Floyd-Warshall  algorithm  relies  on  the  following  observation.
Numbering the vertices of G by V = {1, 2, … , n}, take a subset {1, 2, …
,  k}  of  vertices  for  some  1  ≤  k  ≤  n.  For  any  pair  of  vertices  i,  j  ∈  V,
consider all paths from i to j whose intermediate vertices are all drawn
from  {1,  2,  …  ,  k},  and  let  p  be  a  minimum-weight  path  from  among
them.  (Path  p  is  simple.)  The  Floyd-Warshall  algorithm  exploits  a
relationship  between  path  p  and  shortest  paths  from  i  to  j  with  all
intermediate  vertices  in  the  set  {1,  2,  …  ,  k  −  1}.  The  details  of  the
relationship depend on whether k is an intermediate vertex of path p or
not.

Figure  23.3  Optimal  substructure  used  by  the  Floyd-Warshall  algorithm.  Path  p  is  a  shortest
path from vertex i to vertex j, and k is the highest-numbered intermediate vertex of p. Path p1,
the portion of path p from vertex i to vertex k, has all intermediate vertices in the set {1, 2, … , k
− 1}. The same holds for path p2 from vertex k to vertex j.

If k is not an intermediate vertex of path p, then all intermediate
vertices  of  path  p  belong  to  the  set  {1,  2,  …  ,  k  −  1}.  Thus  a
shortest  path  from  vertex  i  to  vertex  j  with  all  intermediate
vertices in the set {1, 2, … , k − 1} is also a shortest path from i to
j with all intermediate vertices in the set {1, 2, … , k}.

If  k  is  an  intermediate  vertex  of  path  p,  then  decompose  p  into
,  as  Figure  23.3  illustrates.  By  Lemma  22.1,  p1  is  a
shortest  path  from  i  to  k  with  all  intermediate  vertices  in  the  set
{1, 2, … , k}. In fact, we can make a slightly stronger statement.
Because  vertex  k  is  not  an  intermediate  vertex  of  path  p1,  all
intermediate  vertices  of  p1  belong  to  the  set  {1,  2,  …  ,  k  −  1}.
Therefore  p1  is  a  shortest  path  from  i  to  k  with  all  intermediate
vertices in the set {1, 2, … , k − 1}. Likewise, p2 is a shortest path
from  vertex  k  to  vertex  j  with  all  intermediate  vertices  in  the  set
{1, 2, … , k − 1}.

A recursive solution to the all-pairs shortest-paths problem

The above observations suggest a recursive formulation of shortest-path
estimates that differs from the one in Section 23.1. Let
 be the weight
of  a  shortest  path  from  vertex  i  to  vertex  j  for  which  all  intermediate
vertices belong to the set {1, 2, … , k}. When k = 0, a path from vertex i
to vertex j with no intermediate vertex numbered higher than 0 has no
intermediate vertices at all. Such a path has at most one edge, and hence

. Following the above discussion, deﬁne

 recursively by

Because for any path, all intermediate vertices belong to the set {1, 2, …
 for all i, j ∈ V.
 gives the ﬁnal answer:
, n}, the matrix

Computing the shortest-path weights bottom up

Based  on  recurrence  (23.6),  the  bottom-up  procedure  FLOYD-
WARSHALL  computes  the  values
  in  order  of  increasing  values  of
k.  Its  input  is  an  n  ×  n  matrix  W  deﬁned  as  in  equation  (23.1).  The
procedure returns the matrix D(n) of shortest-path weights. Figure 23.4
shows the matrices D(k) computed by the Floyd-Warshall algorithm for
the graph in Figure 23.1.

FLOYD-WARSHALL(W, n)
1 D(0) = W
2 for k = 1 to n
let
3
for i = 1 to n

4

 be a new n × n matrix

5

for j = 1 to n

6
7 return D(n)

The running time of the Floyd-Warshall algorithm is determined by
the triply nested for loops of lines 2–6. Because each execution of line 6
takes  O(1)  time,  the  algorithm  runs  in  Θ(n3)  time.  As  in  the  ﬁnal
algorithm  in  Section  23.1,  the  code  is  tight,  with  no  elaborate  data
structures, and so the constant hidden in the Θ-notation is small. Thus,
the Floyd-Warshall algorithm is quite practical for even moderate-sized
input graphs.

Constructing a shortest path

There are a variety of different methods for constructing shortest paths
in the Floyd-Warshall algorithm. One way is to compute the matrix D
of  shortest-path  weights  and  then  construct  the  predecessor  matrix  Π
from the D matrix. Exercise 23.1-7 asks you to implement this method
so  that  it  runs  in  O(n3)  time.  Given  the  predecessor  matrix  Π,  the
PRINT-ALL-PAIRS-SHORTEST-PATH  procedure  prints  the  vertices
on a given shortest path.

Alternatively,  the  predecessor  matrix  …  can  be  computed  while  the
algorithm  computes  the  matrices  D(0),  D(1),  …  ,  D(n).  Speciﬁcally,
(n)
compute a sequence of matrices Π
and
with all intermediate vertices in the set {1, 2, … , k}.

(0), Π
  is  the  predecessor  of  vertex  j  on  a  shortest  path  from  vertex  i

(n), where Π = Π

(1), … , Π

Figure 23.4 The sequence of matrices D(k) and Π
for the graph in Figure 23.1.

(k) computed by the Floyd-Warshall algorithm

Here’s  a  recursive  formulation  of

.  When  k  =  0,  a  shortest  path

from i to j has no intermediate vertices at all, and so

For k ≥ 1, if the path has k as an intermediate vertex, so that it is i ⇝ k
⇝  j  where  k  ≠  j,  then  choose  as  the  predecessor  of  j  on  this  path  the
same  vertex  as  the  predecessor  of  j  chosen  on  a  shortest  path  from  k
with  all  intermediate  vertices  in  the  set  {1,  2,  …  ,  k  −  1}.  Otherwise,
when  the  path  from  i  to  j  does  not  have  k  as  an  intermediate  vertex,

choose  the  same  predecessor  of  j  as  on  a  shortest  path  from  i  with  all
intermediate vertices in the set {1, 2, … , k − 1}. Formally, for k ≥ 1,

Exercise 23.2-3 asks you to show how to incorporate the Π

(k) matrix
computations  into  the  FLOYD-WARSHALL  procedure.  Figure  23.4
(k)  matrices  that  the  resulting  algorithm
shows  the  sequence  of  Π
computes  for  the  graph  of  Figure  23.1.  The  exercise  also  asks  for  the
more  difﬁcult  task  of  proving  that  the  predecessor  subgraph  Gπ,i  is  a
shortest-paths tree with root i. Exercise 23.2-7 asks for yet another way
to reconstruct shortest paths.

Transitive closure of a directed graph

Given a directed graph G = (V, E) with vertex set V = {1, 2, … , n}, you
might  wish  to  determine  simply  whether  G  contains  a  path  from  i  to  j
for all vertex pairs i, j ∈ V, without regard to edge weights. We deﬁne
the transitive closure of G as the graph G* = (V, E*), where

E* = {(i, j) : there is a path from vertex i to vertex j in G}.

One way to compute the transitive closure of a graph in Θ(n3) time is
to assign a weight of 1 to each edge of E and run the Floyd-Warshall
algorithm.  If  there  is  a  path  from  vertex  i  to  vertex  j,  you  get  dij  <  n.
Otherwise, you get dij = ∞.

There is another, similar way to compute the transitive closure of G
in  Θ(n3)  time,  which  can  save  time  and  space  in  practice.  This  method
substitutes  the  logical  operations  ∨  (logical  OR)  and  ∧  (logical  AND)
for  the  arithmetic  operations  min  and  +  in  the  Floyd-Warshall
 to be 1 if there exists a path
algorithm. For i, j, k = 1, 2, … , n, deﬁne
in graph G from vertex i to vertex j with all intermediate vertices in the
set {1, 2, … , k}, and 0 otherwise. To construct the transitive closure G*

=  (V,  E*),  put  edge  (i,  j)  into  E*  if  and  only  if
deﬁnition of

, analogous to recurrence (23.6), is

.  A  recursive

Figure  23.5  A  directed  graph  and  the  matrices  T(k)  computed  by  the  transitive-closure
algorithm.

and for k ≥ 1,

As  in  the  Floyd-Warshall  algorithm,  the  TRANSITIVE-CLOSURE
procedure computes the matrices

 in order of increasing k.

TRANSITIVE-CLOSURE(G, n)

 be a new n × n matrix

  1 let
  2 for i = 1 to n
  3

for j = 1 to n

if i == j or (i, j) ∈ G.E

  4

  5

else

  6
  7 for k = 1 to n
let
  8
for i = 1 to n

  9

 be a new n × n matrix

for j = 1 to n

10

11

12 return T(n)

shows

Figure  23.5

the  matrices  T(k)  computed  by

the
TRANSITIVE-CLOSURE  procedure  on  a  sample  graph.  The
TRANSITIVE-CLOSURE  procedure,
the  Floyd-Warshall
algorithm,  runs  in  Θ(n3)  time.  On  some  computers,  though,  logical
operations on single-bit values execute faster than arithmetic operations
on  integer  words  of  data.  Moreover,  because  the  direct  transitive-
closure  algorithm  uses  only  boolean  values  rather  than  integer  values,
its  space  requirement  is  less  than  the  Floyd-Warshall  algorithm’s  by  a
factor corresponding to the size of a word of computer storage.

like

Exercises

23.2-1
Run  the  Floyd-Warshall  algorithm  on  the  weighted,  directed  graph  of
Figure 23.2. Show the matrix D(k) that results for each iteration of the
outer loop.

23.2-2
Show  how  to  compute  the  transitive  closure  using  the  technique  of
Section 23.1.

23.2-3
Modify  the  FLOYD-WARSHALL  procedure  to  compute  the  Π
matrices according to equations (23.7) and (23.8). Prove rigorously that
for all i ∈ V, the predecessor subgraph Gπ,i is a shortest-paths tree with
 implies
root i. (Hint: To show that Gπ,i is acyclic, ﬁrst show that
,  according  to  the  deﬁnition  of

.  Then  adapt  the  proof

(k)

of Lemma 22.16.)

23.2-4
As it appears on page 657, the Floyd-Warshall algorithm requires Θ(n3)
 for i, j, k = 1, 2, … , n. Show that the procedure
space, since it creates

FLOYD-WARSHALL′,  which  simply  drops  all  the  superscripts,  is
correct, and thus only Θ(n2) space is required.

FLOYD-WARSHALL′(W, n)
1 D = W
2 for k = 1 to n
3

for i = 1 to n

4

for j = 1 to n

5
6 return D

dij = min {dij, dik + dkj}

23.2-5
Consider the following change to how equation (23.8) handles equality:

Is this alternative deﬁnition of the predecessor matrix Π correct?

23.2-6
Show how to use the output of the Floyd-Warshall algorithm to detect
the presence of a negative-weight cycle.

 for i,j,k = 1, 2, … , n, where

23.2-7
Another  way  to  reconstruct  shortest  paths  in  the  Floyd-Warshall
algorithm uses values
 is the highest-
numbered intermediate vertex of a shortest path from i to j in which all
intermediate  vertices  lie  in  the  set  {1,  2,  …  ,  k}.  Give  a  recursive
,  modify  the  FLOYD-WARSHALL  procedure  to
formulation  for
  values,  and  rewrite  the  PRINT-ALL-PAIRS-
compute  the
  as  an  input.
SHORTEST-PATH  procedure  to  take  the  matrix
How  is  the  matrix  Φ  like  the  s  table  in  the  matrix-chain  multiplication
problem of Section 14.2?

23.2-8

Give an O(VE)-time algorithm for computing the transitive closure of a
directed graph G = (V, E). Assume that |V| = O(E) and that the graph is
represented with adjacency lists.

23.2-9
Suppose that it takes f(|V|, |E|) time to compute the transitive closure of
a directed acyclic graph, where f is a monotonically increasing function
of both |V| and |E|. Show that the time to compute the transitive closure
G* = (V, E*) of a general directed graph G = (V, E) is then f(|V|, |E|) +
O(V + E*).

23.3    Johnson’s algorithm for sparse graphs

Johnson’s algorithm ﬁnds shortest paths between all pairs in O(V2 lg V
+  VE)  time.  For  sparse  graphs,  it  is  asymptotically  faster  than  either
repeated  squaring  of  matrices  or  the  Floyd-Warshall  algorithm.  The
algorithm either returns  a matrix of  shortest-path weights for all pairs
of  vertices  or  reports  that  the  input  graph  contains  a  negative-weight
cycle. Johnson’s algorithm uses as subroutines both Dijkstra’s algorithm
and the Bellman-Ford algorithm, which Chapter 22 describes.

Johnson’s algorithm uses the technique of reweighting, which works
as follows. If all edge weights w in a graph G = (V, E) are nonnegative,
Dijkstra’s algorithm can ﬁnd shortest paths between all pairs of vertices
by  running  it  once  from  each  vertex.  With  the  Fibonacci-heap  min-
priority queue, the running time of this all-pairs algorithm is O(V2 lg V
+  VE).  If  G  has  negative-weight  edges  but  no  negative-weight  cycles,
ﬁrst  compute  a  new  set  of  nonnegative  edge  weights  so  that  Dijkstra’s
algorithm  applies.  The  new  set  of  edge  weights  ŵ  must  satisfy  two
important properties:

1. For all pairs of vertices u, v ∈ V, a path p is a shortest path from
u to v using weight function w if and only if p is also a shortest
path from u to v using weight function ŵ.

2. For all edges (u, v), the new weight ŵ(u, v) is nonnegative.

As we’ll see in a moment, preprocessing G to determine the new weight
function ŵ takes O(VE) time.

Preserving shortest paths by reweighting

The following lemma shows how to reweight the edges to satisfy the ﬁrst
property above. We use δ to denote shortest-path weights derived from
weight  function  w  and
  to  denote  shortest-path  weights  derived  from
weight function ŵ.
Lemma 23.1 (Reweighting does not change shortest paths)
Given a weighted, directed graph G = (V, E) with weight function w : E
→ ℝ, let h : V → ℝ be any function mapping vertices to real numbers.
For each edge (u, v) ∈ E, deﬁne

Let p = 〈v0, v1, … , vk〉 be any path from vertex v0 to vertex vk. Then p
is a shortest path from v0 to vk with weight function w if and only if it
is  a  shortest  path  with  weight  function  ŵ.  That  is,  w(p)  =  δ(v0,  vk)  if
.  Furthermore,  G  has  a  negative-weight  cycle
and  only  if
using  weight  function  w  if  and  only  if  G  has  a  negative-weight  cycle
using weight function ŵ.

Proof   We start by showing that

We have

Therefore,  any  path  p  from  v0  to  vk  has  ŵ(p)  =  w(p)  +  h(v0)  −  h(vk).
Because h(v0) and h(vk) do not depend on the path, if one path from v0
to  vk  is  shorter  than  another  using  weight  function  w,  then  it  is  also
shorter using ŵ. Thus, w(p) = δ(v0, vk) if and only if

.

Finally,  we  show  that  G  has  a  negative-weight  cycle  using  weight
function  w  if  and  only  if  G  has  a  negative-weight  cycle  using  weight
function ŵ. Consider any cycle c = 〈v0, v1, … , vk〉, where v0 = vk. By
equation (23.11),

ŵ(c) = w(c) + h(v0) + h(vk)

= w(c),

and  thus  c  has  negative  weight  using  w  if  and  only  if  it  has  negative
weight using ŵ.

▪

Producing nonnegative weights by reweighting

Our next goal is to ensure that the second property holds: ŵ(u, v) must
be nonnegative for all edges (u, v) = E. Given a weighted, directed graph
G = (V, E) with weight function w : E → ℝ, we’ll see how to make a new
graph G′ = (V′, E′), where V′ = V ∪ {s} for some new vertex s ∉ V and
E′ = E ∪ {(s, v) : v = V }. To incorporate the new vertex s, extend the
weight function w so that w(s, v) = 0 for all v ∈ V. Since no edges enter
s,  no  shortest  paths  in  G′,  other  than  those  with  source  s,  contain  s.
Moreover,  G′  has  no  negative-weight  cycles  if  and  only  if  G  has  no
negative-weight cycles. Figure 23.6(a) shows the graph G′ corresponding
to the graph G of Figure 23.1.

Now  suppose  that  G  and  G′  have  no  negative-weight  cycles.  Deﬁne
the  function  h(v)  =  δ(s,  v)  for  all  v  ∈  V′.  By  the  triangle  inequality
(Lemma 22.10 on page 633), we have h(v) ≤ h(u) + w(u, v) for all edges
(u,  v)  ∈  E′.  Thus,  by  deﬁning  reweighted  edge  weights  ŵ  according  to
equation  (23.10),  we  have  ŵ(u,  v)  =  w(u,  v)  +  h(u)  −  h(v)  ≥  0,  thereby

satisfying the second property. Figure 23.6(b) shows the graph G′ from
Figure 23.6(a) with reweighted edges.

Computing all-pairs shortest paths

Johnson’s  algorithm  to  compute  all-pairs  shortest  paths  uses  the
Bellman-Ford  algorithm  (Section  22.1)  and  Dijkstra’s  algorithm
(Section 22.3) as subroutines. The pseudocode appears in the procedure
JOHNSON on page 666. It assumes implicitly that the edges are stored
in adjacency lists. The algorithm returns the usual |V| × |V| matrix D =
(dij),  where  dij  =  δ(i,  j),  or  it  reports  that  the  input  graph  contains  a
negative-weight  cycle.  As  is  typical  for  an  all-pairs  shortest-paths
algorithm, it assumes that the vertices are numbered from 1 to |V|.

Figure 23.6 Johnson’s all-pairs shortest-paths algorithm run on the graph of Figure 23.1. Vertex
numbers appear outside the vertices. (a) The graph G′ with the original weight function w. The
new vertex s is blue. Within each vertex v is h(v) = δ(s, v). (b) After reweighting each edge (u, v)
with  weight  function  ŵ(u,  v)  =  w(u,  v)  +  h(u)  −  h(v).  (c)–(g)  The  result  of  running  Dijkstra’s
algorithm on each vertex of G using weight function ŵ. In each part, the source vertex u is blue,
and blue edges belong to the shortest-paths tree computed by the algorithm. Within each vertex
  and  δ(u,  v),  separated  by  a  slash.  The  value  duv  =  δ(u,  v)  is  equal  to
v  are  the  values

.

JOHNSON(G, w)
  1 compute G′, where G′.V = G.V ∪ {s},

G′.E = G.E ∪ {(s, v) : v ∈ G.V}, and

w(s, v) = 0 for all v ∈ G.V

print “the input graph contains a negative-weight cycle”

  2 if BELLMAN-FORD(G′, w, s) == FALSE
  3
  4 else for each vertex v ∈ G′.V
  5

set h(v) to the value of δ(s, v)

computed by the Bellman-Ford algorithm

  6

  7

  8

  9

10

11

for each edge (u, v) ∈ G′.E

ŵ(u, v) = w(u, v) + h(u) − h(v)
let D = (duv) be a new n × n matrix
for each vertex u ∈ G.V

run DIJKSTRA(G, ŵ, u) to compute
for each vertex v ∈ G.V

 for all v ∈ G.V

12
13 return D

The  JOHNSON  procedure  simply  performs  the  actions  speciﬁed
earlier. Line 1 produces G′. Line 2 runs the Bellman-Ford algorithm on
G′  with  weight  function  w  and  source  vertex  s.  If  G′,  and  hence  G,
contains a negative-weight cycle, line 3 reports the problem. Lines 4–12
assume that G′ contains no negative-weight cycles. Lines 4–5 set h(v) to
the  shortest-path  weight  δ(s,  v)  computed  by  the  Bellman-Ford
algorithm  for  all  v  ∈  V′.  Lines  6–7  compute  the  new  weights  ŵ.  For
each pair of vertices u, v ∈ V, the for loop of lines 9–12 computes the
shortest-path  weight
  by  calling  Dijkstra’s  algorithm  once  from
each vertex in V. Line 12 stores in matrix entry duv the correct shortest-
path  weight  δ(u,  v),  calculated  using  equation  (23.11).  Finally,  line  13
returns  the  completed  D  matrix.  Figure  23.6  depicts  the  execution  of
Johnson’s algorithm.

If the min-priority queue in Dijkstra’s algorithm is implemented by a
Fibonacci heap, Johnson’s algorithm runs in O(V2 lg V + VE) time. The
simpler binary min-heap implementation yields a running time of O(VE
lg  V),  which  is  still  asymptotically  faster  than  the  Floyd-Warshall
algorithm if the graph is sparse.

Exercises

23.3-1
Use Johnson’s algorithm to ﬁnd the shortest paths between all pairs of
vertices  in  the  graph  of  Figure  23.2.  Show  the  values  of  h  and  ŵ
computed by the algorithm.

23.3-2
What is the purpose of adding the new vertex s to V, yielding V′?

23.3-3
Suppose that w(u, v) ≥ 0 for all edges (u, v) ∈ E. What is the relationship
between the weight functions w and ŵ?

23.3-4
Professor  Greenstreet  claims  that  there  is  a  simpler  way  to  reweight
edges  than  the  method  used  in  Johnson’s  algorithm.  Letting  w*  =  min
{w(u, v) : (u, v) ∈ E}, just deﬁne ŵ(u, v) = w(u, v) − w* for all edges (u,
v) ∈ E. What is wrong with the professor’s method of reweighting?

23.3-5
Show  that  if  G  contains  a  0-weight  cycle  c,  then  ŵ(u,  v)  =  0  for  every
edge (u, v) in c.

23.3-6
Professor Michener claims that there is no need to create a new source
vertex  in  line  1  of  JOHNSON.  He  suggests  using  G′  =  G  instead  and
letting s be any vertex. Give an example of a weighted, directed graph G
for  which  incorporating  the  professor’s  idea  into  JOHNSON  causes
incorrect answers. Assume that ∞ − ∞ is undeﬁned, and in particular, it
is  not  0.  Then  show  that  if  G  is  strongly  connected  (every  vertex  is
reachable from every other vertex), the results returned by JOHNSON
with the professor’s modiﬁcation are correct.

Problems

23-1     Transitive closure of a dynamic graph
You wish to maintain the transitive closure of a directed graph G = (V,
E) as you insert edges into E. That is, after inserting an edge, you update
the transitive closure of the edges inserted so far. Start with G having no
edges initially, and represent the transitive closure by a boolean matrix.

a. Show how to update the transitive closure G* = (V, E*) of a graph G

= (V, E) in O(V2) time when a new edge is added to G.

b. Give an example of a graph G and an edge e such that Ω(V2) time is
required to update the transitive closure after inserting e into G, no
matter what algorithm is used.

c. Give an algorithm for updating the transitive closure as edges are
inserted into the graph. For any sequence of r insertions, your
algorithm should run in time
update the transitive closure upon inserting the ith edge. Prove that
your algorithm attains this time bound.

, where ti is the time to

23-2     Shortest paths in ϵ-dense graphs
A graph G = (V, E) is ϵ-dense if |E| = Θ(V1+ϵ) for some constant in the
range 0 < ϵ ≤ 1. d-ary min-heaps (see Problem 6-2 on page 179) provide
a  way  to  match  the  running  times  of  Fibonacci-heap-based  shortest-
path algorithms on ϵ-dense graphs without using as complicated a data
structure.

a. What are the asymptotic running times for the operations INSERT,

EXTRACT-MIN, and DECREASE-KEY, as a function of d and the
number n of elements in a d-ary min-heap? What are these running
times if you choose d = Θ(nπ) for some constant 0 < α ≤ 1? Compare
these running times to the amortized costs of these operations for a
Fibonacci heap.

b. Show how to compute shortest paths from a single source on an ϵ-
dense directed graph G = (V, E) with no negative-weight edges in
O(E) time. (Hint: Pick d as a function of ϵ.)

c. Show how to solve the all-pairs shortest-paths problem on an ϵ-dense
directed graph G = (V, E) with no negative-weight edges in O(VE)
time.

d. Show how to solve the all-pairs shortest-paths problem in O(VE) time

on an ϵ-dense directed graph G = (V, E) that may have negative-
weight edges but has no negative-weight cycles.

Chapter notes

Lawler  [276]  has  a  good  discussion  of  the  all-pairs  shortest-paths
problem.  He  attributes  the  matrix-multiplication  algorithm  to  the
folklore.  The  Floyd-Warshall  algorithm  is  due  to  Floyd  [144],  who
based it on a theorem of Warshall [450] that describes how to compute
the transitive closure of boolean matrices. Johnson’s algorithm is taken
from [238].

Several  researchers  have  given  improved  algorithms  for  computing
shortest  paths  via  matrix  multiplication.  Fredman  [153]  shows  how  to
solve  the  all-pairs  shortest  paths  problem  using  O(V5/2)  comparisons
between  sums  of  edge  weights  and  obtains  an  algorithm  that  runs  in
O(V3lg  lg  V/lg  V/1/3)  time,  which  is  slightly  better  than  the  running
time  of  the  Floyd-Warshall  algorithm.  This  bound  has  been  improved
several times, and the fastest algorithm is now by Williams [457], with a
running time of

.

Another  line  of  research  demonstrates  how  to  apply  algorithms  for
fast  matrix  multiplication  (see  the  chapter  notes  for  Chapter  4)  to  the
all-pairs shortest paths problem. Let O(nω) be the running time of the
fastest algorithm for multiplying two n × n matrices. Galil and Margalit
[170,  171]  and  Seidel  [403]  designed  algorithms  that  solve  the  all-pairs
shortest  paths  problem  in  undirected,  unweighted  graphs  in  (Vωp(V))
time,  where
is
polylogarithmically bounded in n. In dense graphs, these algorithms are
faster than the O(VE) time needed to perform |V| breadth-ﬁrst searches.
Several  researchers  have  extended  these  results  to  give  algorithms  for

p(n)  denotes

a  particular

function

that

solving  the  all-pairs  shortest  paths  problem  in  undirected  graphs  in
which  the  edge  weights  are  integers  in  the  range  {1,  2,  …  ,  W}.  The
asymptotically  fastest  such  algorithm,  by  Shoshan  and  Zwick  [410],
runs in O(W Vωp(V W)) time. In directed graphs, the best algorithm to
date is due to Zwick [467] and runs in Õ(W1/(4−ω)V2+1/(4−ω)) time.

Karger, Koller, and Phillips [244] and independently McGeoch [320]
have given a time bound that depends on E*, the set of edges in E that
participate in some shortest path. Given a graph with nonnegative edge
weights,  their  algorithms  run  in  O(VE*  +  V2  lg  V)  time  and  improve
upon  running  Dijkstra’s  algorithm  |V|  times  when  |E*|  =  o(E).  Pettie
[355]  uses  an  approach  based  on  component  hierarchies  to  achieve  a
running time of O(VE + V2 lg lg V), and the same running time is also
achieved by Hagerup [205].

Baswana,  Hariharan,  and  Sen

[37]  examined  decremental
algorithms,  which  allow  a  sequence  of  intermixed  edge  deletions  and
queries,  for  maintaining  all-pairs  shortest  paths  and  transitive-closure
information.  When  a  path  exists,  their  randomized  transitive-closure
algorithm can fail to report it with probability 1/nc for an arbitrary c >
0. The query times are O(1) with high probability. For transitive closure,
the amortized time for each update is O(V4/3 lg1/3V). By comparison,
Problem  23-1,  in  which  edges  are  inserted,  asks  for  an  incremental
algorithm. For all-pairs shortest paths, the update times depend on the
queries. For queries just giving the shortest-path weights, the amortized
time per update is O(V3/E lg2V). To report the actual shortest path, the
amortized  update  time  is  min
.  Demetrescu  and
Italiano [111] showed how to handle update and query operations when
edges  are  both  inserted  and  deleted,  as  long  as  the  range  of  edge
weights is bounded.

Aho, Hopcroft, and Ullman [5] deﬁned an algebraic structure known
as a “closed semiring,” which serves as a general framework for solving
path  problems  in  directed  graphs.  Both  the  Floyd-Warshall  algorithm
and the transitive-closure algorithm from Section 23.2 are instantiations
of an all-pairs algorithm based on closed semirings. Maggs and Plotkin

[309]  showed  how  to  ﬁnd  minimum  spanning  trees  using  a  closed
semiring.

1  According  to  a  report  cited  by  U.S.  Department  of  Transportation  Federal  Highway
Administration,  “a  reasonable  ‘rule  of  thumb’  is  one  signalized  intersection  per  1,000
population.”
2 An algebraic semiring contains operations ⊕, which is commutative with identity I
, and ⊕,
⊕⊕x  =
with  identity  I
  for  all  x.  Standard  matrix  multiplication,  as  in  MATRIX-MULTIPLY,  uses  the
x⊕I
  =  I
semiring with + for ⊕, ⊕ for ⊕, 0 for I
. The procedure EXTEND-SHORTEST-
, and 1 for I
PATHS uses another semiring, known as the tropical semiring, with min for ⊕, + for ⊕, ∞ for
I
⊕

⊕
,  where  ⊕  distributes  over  ⊕  on  both  the  left  and  right,  and  where  I

, and 0 for I

⊕

⊕

⊕

⊕

⊕

⊕

.

