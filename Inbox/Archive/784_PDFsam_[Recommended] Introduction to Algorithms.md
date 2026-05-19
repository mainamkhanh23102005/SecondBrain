22        Single-Source Shortest Paths

Suppose  that  you  need  to  drive  from  Oceanside,  New  York,  to
Oceanside,  California,  by  the  shortest  possible  route.  Your  GPS
contains  information  about  the  entire  road  network  of  the  United
States,  including  the  road  distance  between  each  pair  of  adjacent
intersections. How can your GPS determine this shortest route?
One  possible  way  is  to  enumerate  all  the  routes  from  Oceanside,  New
York, to Oceanside, California, add up the distances on each route, and
select the shortest. But even disallowing routes that contain cycles, your
GPS would need to examine an enormous number of possibilities, most
of  which  are  simply  not  worth  considering.  For  example,  a  route  that
passes  through  Miami,  Florida,  is  a  poor  choice,  because  Miami  is
several hundred miles out of the way.

This  chapter  and  Chapter  23  show  how  to  solve  such  problems
efﬁciently. The input to a shortest-paths problem is a weighted, directed
graph G = (V, E), with a weight function w : E → ℝ mapping edges to
real-valued weights. The weight w(p) of path p = 〈v0, v1, … , vk〉 is the
sum of the weights of its constituent edges:

We deﬁne the shortest-path weight δ(u, v) from u to v by

A shortest path from vertex u to vertex v is then deﬁned as any path p
with weight w(p) = δ(u, v).

In  the  example  of  going  from  Oceanside,  New  York,  to  Oceanside,
California,  your  GPS  models  the  road  network  as  a  graph:  vertices
represent
intersections,  edges  represent  road  segments  between
intersections, and edge weights represent road distances. The goal is to
ﬁnd  a  shortest  path  from  a  given  intersection  in  Oceanside,  New  York
(say,  Brower  Avenue  and  Skillman  Avenue)  to  a  given  intersection  in
Oceanside, California (say, Topeka Street and South Horne Street).

Edge  weights  can  represent  metrics  other  than  distances,  such  as
time,  cost,  penalties,  loss,  or  any  other  quantity  that  accumulates
linearly along a path and that you want to minimize.

The  breadth-ﬁrst-search  algorithm  from  Section  20.2  is  a  shortest-
paths  algorithm  that  works  on  unweighted  graphs,  that  is,  graphs  in
which  each  edge  has  unit  weight.  Because  many  of  the  concepts  from
breadth-ﬁrst  search  arise  in  the  study  of  shortest  paths  in  weighted
graphs, you might want to review Section 20.2 before proceeding.

Variants

This chapter focuses on the single-source shortest-paths problem: given a
graph G = (V, E), ﬁnd a shortest path from a given source vertex s ∈ V
to every vertex v ∈ V. The algorithm for the single-source problem can
solve many other problems, including the following variants.

Single-destination  shortest-paths  problem:  Find  a  shortest  path  to  a
given destination vertex t from each vertex v. By reversing the direction
of  each  edge  in  the  graph,  you  can  reduce  this  problem  to  a  single-
source problem.

Single-pair  shortest-path  problem:  Find  a  shortest  path  from  u  to  v  for
given  vertices  u  and  v.  If  you  solve  the  single-source  problem  with
source  vertex  u,  you  solve  this  problem  also.  Moreover,  all  known
algorithms  for  this  problem  have  the  same  worst-case  asymptotic
running time as the best single-source algorithms.

All-pairs  shortest-paths  problem:  Find  a  shortest  path  from  u  to  v  for
every pair of vertices u and v. Although you can solve this problem by

running  a  single-source  algorithm  once  from  each  vertex,  you  often
can  solve  it  faster.  Additionally,  its  structure  is  interesting  in  its  own
right. Chapter 23 addresses the all-pairs problem in detail.

Optimal substructure of a shortest path

Shortest-paths algorithms typically rely on the property that a shortest
path between two vertices contains other shortest paths within it. (The
Edmonds-Karp  maximum-ﬂow  algorithm  in  Chapter  24  also  relies  on
this  property.)  Recall  that  optimal  substructure  is  one  of  the  key
indicators  that  dynamic  programming  (Chapter  14)  and  the  greedy
method (Chapter 15) might apply. Dijkstra’s algorithm, which we shall
see  in  Section  22.3,  is  a  greedy  algorithm,  and  the  Floyd-Warshall
algorithm,  which  ﬁnds  a  shortest  path  between  every  pair  of  vertices
(see Section 23.2), is a dynamic-programming algorithm. The following
lemma states the optimal-substructure property of shortest paths more
precisely.

Lemma 22.1 (Subpaths of shortest paths are shortest paths)
Given a weighted, directed graph G = (V, E) with weight function w : E
→ ℝ let p = 〈v0, v1, … , vk〉 be a shortest path from vertex v0 to vertex
vk and, for any i and j such that 0 ≤ i ≤ j ≤ k, let pij = 〈vi, vi+1, … , vj〉 be
the subpath of p from vertex vi to vertex vj. Then, pij is a shortest path
from vi to vj.

Proof   Decompose path p into
w(pij)  +  w(pjk).  Now,  assume  that  there  is  a  path
weight
weight
assumption that p is a shortest path from v0 to vk.

, so that w(p) = w(p0i) +
  from  vi  to  vj  with
 is a path from v0 to vk whose
  is  less  than  w(p),  which  contradicts  the

. Then,

Negative-weight edges

▪

Some instances of the single-source shortest-paths problem may include
edges whose weights are negative. If the graph G = (V, E) contains no
negative-weight  cycles  reachable  from  the  source  s,  then  for  all  v  ∈  V,
the  shortest-path  weight  δ(s,  v)  remains  well  deﬁned,  even  if  it  has  a
negative  value.  If  the  graph  contains  a  negative-weight  cycle  reachable
from  s,  however,  shortest-path  weights  are  not  well  deﬁned.  No  path
from s to a vertex on the cycle can be a shortest path—you can always
ﬁnd a path with lower weight by following the proposed “shortest” path
and  then  traversing  the  negative-weight  cycle.  If  there  is  a  negative-
weight cycle on some path from s to v, we deﬁne δ(s, v) = −∞.

Figure  22.1  illustrates  the  effect  of  negative  weights  and  negative-
weight  cycles  on  shortest-path  weights.  Because  there  is  only  one  path
from s to a (the path 〈s, a〉), we have δ(s, a) = w(s, a) = 3. Similarly, there
is only one path from s to b, and so δ(s, b) = w(s, a) + w(a, b) = 3 + (−4)
= −1. There are inﬁnitely many paths from s to c: 〈s, c〉, 〈s, c, d, c〉, 〈s, c,
d, c, d, c〉, and so on. Because the cycle 〈c, d, c〉 has weight 6 + (−3) = 3
> 0, the shortest path from s to c is 〈s, c〉, with weight δ(s, c) = w(s, c) =
5, and the shortest path from s to d is 〈s, c, d〉, with weight δ(s, d) = w(s,
c) + w(c, d) = 11. Analogously, there are inﬁnitely many paths from s to
e: 〈s, e〉, 〈s, e, f, e〉, 〈s, e, f, e, f, e〉, and so on. Because the cycle 〈e, f, e〉
has weight 3 + (−6) = −3 < 0, however, there is no shortest path from s
to  e.  By  traversing  the  negative-weight  cycle  〈e,  f,  e〉  arbitrarily  many
times,  you  can  ﬁnd  paths  from  s  to  e  with  arbitrarily  large  negative
weights,  and  so  δ(s,  e)  =  −∞.  Similarly,  δ(s,  f)  =  −∞.  Because  g  is
reachable from f, you can also ﬁnd paths with arbitrarily large negative
weights from s to g, and so δ(s, g) = −∞. Vertices h, i, and j also form a
negative-weight  cycle.  They  are  not  reachable  from  s,  however,  and  so
δ(s, h) = δ(s, i) = δ(s, j) = ∞.

Figure 22.1 Negative edge weights in a directed graph. The shortest-path weight from source s
appears within each vertex. Because vertices e and f form a negative-weight cycle reachable from
s,  they  have  shortest-path  weights  of  −∞.  Because  vertex  g  is  reachable  from  a  vertex  whose
shortest-path weight is −∞, it, too, has a shortest-path weight of −∞. Vertices such as h, i, and j
are  not  reachable  from  s,  and  so  their  shortest-path  weights  are  ∞,  even  though  they  lie  on  a
negative-weight cycle.

Some  shortest-paths  algorithms,  such  as  Dijkstra’s  algorithm,
assume that all edge weights in the input graph are nonnegative, as in a
road  network.  Others,  such  as  the  Bellman-Ford  algorithm,  allow
negative-weight edges in the input graph and produce a correct answer
as  long  as  no  negative-weight  cycles  are  reachable  from  the  source.
Typically,  if  there  is  such  a  negative-weight  cycle,  the  algorithm  can
detect and report its existence.

Cycles

Can  a  shortest  path  contain  a  cycle?  As  we  have  just  seen,  it  cannot
contain  a  negative-weight  cycle.  Nor  can  it  contain  a  positive-weight
cycle, since removing the cycle from the path produces a path with the
same source and destination vertices and a lower path weight. That is, if
p  =  〈v0,  v1,  …  ,  vk〉  is  a  path  and  c  =  〈vi,  vi+1,  …  ,  vj〉  is  a  positive-
weight cycle on this path (so that vi = vj and w(c) > 0), then the path p′
= 〈v0, v1, … , vi, vj+1, vj+2, … , vk〉 has weight w(p′) = w(p) − w(c) <
w(p), and so p cannot be a shortest path from v0 to vk.

That  leaves  only  0-weight  cycles.  You  can  remove  a  0-weight  cycle
from any path to produce another path whose weight is the same. Thus,
if there is a shortest path from a source vertex s to a destination vertex v
that contains a 0-weight cycle, then there is another shortest path from s

to  v  without  this  cycle.  As  long  as  a  shortest  path  has  0-weight  cycles,
you  can  repeatedly  remove  these  cycles  from  the  path  until  you  have  a
shortest  path  that  is  cycle-free.  Therefore,  without  loss  of  generality,
assume that shortest paths have no cycles, that is, they are simple paths.
Since any acyclic path in a graph G = (V, E) contains at most |V| distinct
vertices,  it  also  contains  at  most  |V|  −  1  edges.  Assume,  therefore,  that
any shortest path contains at most |V| − 1 edges.

Representing shortest paths

It  is  usually  not  enough  to  compute  only  shortest-path  weights.  Most
applications  of  shortest  paths  need  to  know  the  vertices  on  shortest
paths  as  well.  For  example,  if  your  GPS  told  you  the  distance  to  your
destination but not how to get there, it would not be terribly useful. We
represent  shortest  paths  similarly  to  how  we  represented  breadth-ﬁrst
trees in Section 20.2. Given a graph G = (V, E), maintain for each vertex
v  ∈  V  a  predecessor  v.π  that  is  either  another  vertex  or  NIL.  The
shortest-paths algorithms in this chapter set the π attributes so that the
chain  of  predecessors  originating  at  a  vertex  v  runs  backward  along  a
shortest path from s to v. Thus, given a vertex v for which v.π ≠ NIL, the
procedure  PRINT-PATH(G,  s,  v)  from  Section  20.2  prints  a  shortest
path from s to v.

In the midst of executing a shortest-paths algorithm, however, the π
values might not indicate shortest paths. The predecessor subgraph Gπ =
(Vπ,  Eπ)  induced  by  the  π  values  is  deﬁned  the  same  for  single-source
shortest paths as for breadth-ﬁrst search in equations (20.2) and (20.3)
on page 561:

Vπ = {v ∈ V : v.π ≠ NIL} ∪ {s},

Eπ = {(v.π, v) ∈ E : v ∈ Vπ − {s}}.

We’ll  prove  that  the  π  values  produced  by  the  algorithms  in  this
chapter  have  the  property  that  at  termination  Gπ  is  a  “shortest-paths
tree”—informally,  a  rooted  tree  containing  a  shortest  path  from  the
source s to every vertex that is reachable from s. A shortest-paths tree is
like  the  breadth-ﬁrst  tree  from  Section  20.2,  but  it  contains  shortest

paths  from  the  source  deﬁned  in  terms  of  edge  weights  instead  of
numbers of edges. To be precise, let G = (V, E) be a weighted, directed
graph with weight function w : E → ℝ, and assume that G contains no
negative-weight  cycles  reachable  from  the  source  vertex  s  ∈  V,  so  that
shortest  paths  are  well  deﬁned.  Ashortest-paths  tree  rooted  at  s  is  a
directed subgraph G′ = (V′, E′), where V′ ⊆ V and E′ ⊆ E, such that

1. V′ is the set of vertices reachable from s in G,
2. G′ forms a rooted tree with root s, and
3. for  all  v  ∈  V′,  the  unique  simple  path  from  s  to  v  in  G′  is  a

shortest path from s to v in G.

Figure  22.2  (a)  A  weighted,  directed  graph  with  shortest-path  weights  from  source  s.  (b)  The
blue edges form a shortest-paths tree rooted at the source s. (c) Another shortest-paths tree with
the same root.

Shortest  paths  are  not  necessarily  unique,  and  neither  are  shortest-
paths trees. For example, Figure 22.2 shows a weighted, directed graph
and two shortest-paths trees with the same root.

Relaxation

The algorithms in this chapter use the technique of relaxation. For each
vertex  v  ∈  V,  the  single-source  shortest  paths  algorithms  maintain  an
attribute v.d, which is an upper bound on the weight of a shortest path
from source s to v. We call v.d a shortest-path estimate. To initialize the
shortest-path  estimates  and  predecessors,  call  the  Θ(V)-time  procedure
INITIALIZE-SINGLE-SOURCE.  After  initialization,  we  have  v.π  =
NIL for all v ∈ V, s.d = 0 and v.d = ∞ for v ∈ V − {s}.

INITIALIZE-SINGLE-SOURCE(G, s)

1 for each vertex v ∈ G.V
2

v.d = ∞
v.π = NIL

3
4 s.d = 0

The  process  of  relaxing  an  edge  (u,  v)  consists  of  testing  whether
going through vertex u improves the shortest path to vertex v found so
far and, if so, updating v.d and v.π. A relaxation step might decrease the
value  of  the  shortest-path  estimate  v.d  and  update  v’s  predecessor
attribute v.π. The RELAX procedure on the following page performs a
relaxation  step  on  edge  (u,  v)  in  O(1)  time.  Figure  22.3  shows  two
examples  of  relaxing  an  edge,  one  in  which  a  shortest-path  estimate
decreases and one in which no estimate changes.

Figure 22.3 Relaxing an edge (u, v) with weight w(u, v) = 2. The shortest-path estimate of each
vertex appears within the vertex. (a) Because v.d > u.d + w(u, v) prior to relaxation, the value of
v.d decreases. (b) Since we have v.d ≤ u.d + w(u, v) before relaxing the edge, the relaxation step
leaves v.d unchanged.

RELAX(u, v, w)

1 if v.d > u.d + w(u, v)
v.d = u.d + w(u, v)
2
v.π = u

3

Each  algorithm

in  this  chapter  calls  INITIALIZE-SINGLE-
SOURCE  and  then  repeatedly  relaxes  edges.1  Moreover,  relaxation  is
the  only  means  by  which  shortest-path  estimates  and  predecessors

change.  The  algorithms  in  this  chapter  differ  in  how  many  times  they
relax  each  edge  and  the  order  in  which  they  relax  edges.  Dijkstra’s
algorithm  and  the  shortest-paths  algorithm  for  directed  acyclic  graphs
relax each edge exactly once. The Bellman-Ford algorithm relaxes each
edge |V| − 1 times.

Properties of shortest paths and relaxation

To  prove  the  algorithms  in  this  chapter  correct,  we’ll  appeal  to  several
properties  of  shortest  paths  and  relaxation.  We  state  these  properties
here,  and  Section  22.5  proves  them  formally.  For  your  reference,  each
property  stated  here  includes  the  appropriate  lemma  or  corollary
number  from  Section  22.5.  The  latter  ﬁve  of  these  properties,  which
refer  to  shortest-path  estimates  or  the  predecessor  subgraph,  implicitly
assume  that  the  graph  is  initialized  with  a  call  to  INITIALIZE-
SINGLE-SOURCE(G,  s)  and  that  the  only  way  that  shortest-path
estimates and the predecessor subgraph change are by some sequence of
relaxation steps.

Triangle inequality (Lemma 22.10)

For any edge (u, v) ∈ E, we have δ(s, v) ≤ δ(s, u) + w(u, v).

Upper-bound property (Lemma 22.11)

We  always  have  v.d  ≥  δ(s,  v)  for  all  vertices  v  ∈  V,  and  once  v.d
achieves the value δ(s, v), it never changes.

No-path property (Corollary 22.12)

If there is no path from s to v, then we always have v.d = δ(s, v) = ∞.

Convergence property (Lemma 22.14)

If s ⇝ u → v is a shortest path in G for some u, v ∈ V, and if u.d =
δ(s, u) at any time prior to relaxing edge (u, v), then v.d = δ(s, v) at
all times afterward.

Path-relaxation property (Lemma 22.15)

If p = 〈v0, v1, … , vk〉 is a shortest path from s = v0 to vk, and the
edges of p are relaxed in the order (v0, v1), (v1, v2), … , (vk−1, vk),
then  vk.d  =  δ(s,  vk).  This  property  holds  regardless  of  any  other

relaxation  steps  that  occur,  even  if  they  are  intermixed  with
relaxations of the edges of p.

Predecessor-subgraph property (Lemma 22.17)

Once  v.d  =  δ(s,  v)  for  all  v  ∈  V,  the  predecessor  subgraph  is  a
shortest-paths tree rooted at s.

Chapter outline

Section  22.1  presents  the  Bellman-Ford  algorithm,  which  solves  the
single-source shortest-paths problem in the general case in which edges
can  have  negative  weight.  The  Bellman-Ford  algorithm  is  remarkably
simple,  and  it  has  the  further  beneﬁt  of  detecting  whether  a  negative-
weight  cycle  is  reachable  from  the  source.  Section  22.2  gives  a  linear-
time  algorithm  for  computing  shortest  paths  from  a  single  source  in  a
directed  acyclic  graph.  Section  22.3  covers  Dijkstra’s  algorithm,  which
has a lower running time than the Bellman-Ford algorithm but requires
the edge weights to be nonnegative. Section 22.4 shows how to use the
Bellman-Ford algorithm to solve a special case of linear programming.
Finally,  Section  22.5  proves  the  properties  of  shortest  paths  and
relaxation stated above.

This  chapter  does  arithmetic  with  inﬁnities,  and  so  we  need  some
conventions for when ∞ or −∞ appears in an arithmetic expression. We
assume that for any real number a ≠ −∞, we have a + ∞ = ∞ + a = ∞.
Also, to make our proofs hold in the presence of negative-weight cycles,
we assume that for any real number a ≠ ∞, we have a + (−∞) = (−∞) + a
= −∞.

All  algorithms  in  this  chapter  assume  that  the  directed  graph  G  is
stored  in  the  adjacency-list  representation.  Additionally,  stored  with
each edge is its weight, so that as each algorithm traverses an adjacency
list, it can ﬁnd edge weights in O(1) time per edge.

22.1    The Bellman-Ford algorithm

The  Bellman-Ford  algorithm  solves  the  single-source  shortest-paths
problem  in  the  general  case  in  which  edge  weights  may  be  negative.

Given  a  weighted,  directed  graph  G  =  (V,  E)  with  source  vertex  s  and
weight  function  w  :  E  →  ℝ,  the  Bellman-Ford  algorithm  returns  a
boolean value indicating whether there is a negative-weight cycle that is
reachable  from  the  source.  If  there  is  such  a  cycle,  the  algorithm
indicates that no solution exists. If there is no such cycle, the algorithm
produces the shortest paths and their weights.

The  procedure  BELLMAN-FORD  relaxes  edges,  progressively
decreasing  an  estimate  v.d  on  the  weight  of  a  shortest  path  from  the
source s to each vertex v ∈ V until it achieves the actual shortest-path
weight  δ(s,  v).  The  algorithm  returns  TRUE  if  and  only  if  the  graph
contains no negative-weight cycles that are reachable from the source.

BELLMAN-FORD(G, w, s)
1 INITIALIZE-SINGLE-SOURCE(G, s)
2 for i = 1 to |G.V| − 1
3

for each edge (u, v) ∈ G.E

RELAX(u, v, w)

4
5 for each edge (u, v) = G.E
6

if v.d > u.d + w(u, v)
return FALSE

7
8 return TRUE

Figure 22.4 shows the execution of the Bellman-Ford algorithm on a
graph with 5 vertices. After initializing the d and π values of all vertices
in line 1, the algorithm makes |V| − 1 passes over the edges of the graph.
Each  pass  is  one  iteration  of  the  for  loop  of  lines  2–4  and  consists  of
relaxing each edge of the graph once. Figures 22.4(b)–(e) show the state
of  the  algorithm  after  each  of  the  four  passes  over  the  edges.  After
making  |V|  −  1  passes,  lines  5–8  check  for  a  negative-weight  cycle  and
return  the  appropriate  boolean  value.  (We’ll  see  a  little  later  why  this
check works.)

Figure 22.4 The execution of the Bellman-Ford algorithm. The source is vertex s. The d values
appear within the vertices, and blue edges indicate predecessor values: if edge (u, v) is blue, then
v.π = u. In this particular example, each pass relaxes the edges in the order (t, x), (t, y), (t, z), (x,
t), (y, x), (y, z), (z, x), (z, s), (s, t), (s, y). (a) The situation just before the ﬁrst pass over the edges.
(b)–(e)  The  situation  after  each  successive  pass  over  the  edges.  Vertices  whose  shortest-path
estimates and predecessors have changed due to a pass are highlighted in orange. The d and π
values  in  part  (e)  are  the  ﬁnal  values.  The  Bellman-Ford  algorithm  returns  TRUE  in  this
example.

The  Bellman-Ford  algorithm  runs  in  O(V2  +  VE)  time  when  the
graph is represented by adjacency lists, since the initialization in line 1
takes  Θ(V)  time,  each  of  the  |V|  −  1  passes  over  the  edges  in  lines  2–4
takes Θ(V + E) time (examining |V| adjacency lists to ﬁnd the |E| edges),
and the for loop of lines 5–7 takes O(V + E) time. Fewer than |V| − 1
passes  over  the  edges  sometimes  sufﬁce  (see  Exercise  22.1-3),  which  is
why  we  say  O(V2+VE)  time,  rather  than  Θ(V2+VE)  time.  In  the
frequent  case  where  |E|  =  Ω(V),  we  can  express  this  running  time  as
O(VE).  Exercise  22.1-5  asks  you  to  make  the  Bellman-Ford  algorithm
run in O(VE) time even when |E| = o(V).

To prove the correctness of the Bellman-Ford algorithm, we start by
showing  that  if  there  are  no  negative-weight  cycles,  the  algorithm
computes  correct  shortest-path  weights  for  all  vertices  reachable  from
the source.

Lemma 22.2
Let G = (V, E) be a weighted, directed graph with source vertex s and
weight  function  w  :  E  →  ℝ,  and  assume  that  G  contains  no  negative-
weight cycles that are reachable from s. Then, after the |V| − 1 iterations
of the for loop of lines 2–4 of BELLMAN-FORD, v.d = δ(s, v) for all
vertices v that are reachable from s.

Proof      We  prove  the  lemma  by  appealing  to  the  path-relaxation
property. Consider any vertex v that is reachable from s, and let p = 〈v0,
v1, … , vk〉, where v0 = s and vk = v, be any shortest path from s to v.
Because shortest paths are simple, p has at most |V| − 1 edges, and so k
≤  |V|  −  1.  Each  of  the  |V|  −  1  iterations  of  the  for  loop  of  lines  2–4
relaxes all |E| edges. Among the edges relaxed in the ith iteration, for i =
1, 2, … , k, is (vi−1, vi). By the path-relaxation property, therefore, v.d =
vk.d = δ(s, vk) = δ(s, v).

▪

Corollary 22.3
Let G = (V, E) be a weighted, directed graph with source vertex s and
weight function w : E → ℝ. Then, for each vertex v ∈ V, there is a path
from s to v if and only if BELLMAN-FORD terminates with v.d < ∞
when it is run on G.

Proof   The proof is left as Exercise 22.1-2.

▪

Theorem 22.4 (Correctness of the Bellman-Ford algorithm)
Let BELLMAN-FORD be run on a weighted, directed graph G = (V,
E) with source vertex s and weight function w : E → ℝ. If G contains no
negative-weight  cycles  that  are  reachable  from  s,  then  the  algorithm
returns TRUE, v.d = δ(s, v) for all vertices v ∈ V, and the predecessor
subgraph  Gπ  is  a  shortest-paths  tree  rooted  at  s.  If  G  does  contain  a
negative-weight  cycle  reachable  from  s,  then  the  algorithm  returns
FALSE.

Proof      Suppose  that  graph  G  contains  no  negative-weight  cycles  that
are  reachable  from  the  source  s.  We  ﬁrst  prove  the  claim  that  at
termination, v.d = δ(s, v) for all vertices v ∈ V. If vertex v is reachable
from s, then Lemma 22.2 proves this claim. If v is not reachable from s,
then  the  claim  follows  from  the  no-path  property.  Thus,  the  claim  is
proven.  The  predecessor-subgraph  property,  along  with  the  claim,
implies that Gπ is a shortest-paths tree. Now we use the claim to show
that  BELLMAN-FORD  returns  TRUE.  At  termination,  for  all  edges
(u, v) ∈ E we have

v.d = δ(s, v)

≤ δ(s, u) + w(u, v) (by the triangle inequality)
= u.d + w(u, v),

and so none of the tests in line 6 causes BELLMAN-FORD to return
FALSE. Therefore, it returns TRUE.

Now,  suppose  that  graph  G  contains  a  negative-weight  cycle
reachable from the source s. Let this cycle be c = 〈v0, v1, … , vk〉, where
v0 = vk, in which case we have

Assume  for  the  purpose  of  contradiction  that  the  Bellman-Ford
algorithm returns TRUE. Thus, vi.d ≤ vi−1.d + w(vi−1, vi) for i = 1, 2,
… , k. Summing the inequalities around cycle c gives

Since  v0  =  vk,  each  vertex  in  c  appears  exactly  once  in  each  of  the
, and so
summations

 and

Moreover, by Corollary 22.3, vi.d is ﬁnite for i = 1, 2, … , k. Thus,

which contradicts inequality (22.1). We conclude that the Bellman-Ford
algorithm returns TRUE if graph G contains no negative-weight cycles
reachable from the source, and FALSE otherwise.

▪

Exercises

22.1-1
Run the Bellman-Ford algorithm on the directed graph of Figure 22.4,
using vertex z as the source. In each pass, relax edges in the same order
as  in  the  ﬁgure,  and  show  the  d  and  π  values  after  each  pass.  Now,
change the weight of edge (z, x) to 4 and run the algorithm again, using
s as the source.

22.1-2
Prove Corollary 22.3.

22.1-3
Given  a  weighted,  directed  graph  G  =  (V,  E)  with  no  negative-weight
cycles,  let  m  be  the  maximum  over  all  vertices  v  ∈  V  of  the  minimum
number  of  edges  in  a  shortest  path  from  the  source  s  to  v.  (Here,  the
shortest path is by weight, not the number of edges.) Suggest a simple
change to the Bellman-Ford algorithm that allows it to terminate in m +
1 passes, even if m is not known in advance.

22.1-4
Modify  the  Bellman-Ford  algorithm  so  that  it  sets  v.d  to  −∞  for  all
vertices v for which there is a negative-weight cycle on some path from
the source to v.

22.1-5
Suppose that the graph given as input to the Bellman-Ford algorithm is
represented  with  a  list  of  |E|  edges,  where  each  edge  indicates  the

vertices  it  leaves  and  enters,  along  with  its  weight.  Argue  that  the
Bellman-Ford algorithm runs in O(VE) time without the constraint that
|E| = Ω(V). Modify the Bellman-Ford algorithm so that it runs in O(VE)
time  in  all  cases  when  the  input  graph  is  represented  with  adjacency
lists.

22.1-6
Let G = (V, E) be a weighted, directed graph with weight function w : E
→ ℝ. Give an O(VE)-time algorithm to ﬁnd, for all vertices v ∈ V, the
value δ*(v) = min {δ(u, v) : u ∈ V}.

22.1-7
Suppose that a weighted, directed graph G = (V, E) contains a negative-
weight cycle. Give an efﬁcient algorithm to list the vertices of one such
cycle. Prove that your algorithm is correct.

22.2    Single-source shortest paths in directed acyclic graphs

In  this  section,  we  introduce  one  further  restriction  on  weighted,
directed  graphs:  they  are  acyclic.  That  is,  we  are  concerned  with
weighted  dags.  Shortest  paths  are  always  well  deﬁned  in  a  dag,  since
even  if  there  are  negative-weight  edges,  no  negative-weight  cycles  can
exist. We’ll see that if the edges of a weighted dag G = (V, E) are relaxed
according  to  a  topological  sort  of  its  vertices,  it  takes  only  Θ(V  +  E)
time to compute shortest paths from a single source.

The  algorithm  starts  by  topologically  sorting  the  dag  (see  Section
20.4) to impose a linear ordering on the vertices. If the dag contains a
path from vertex u to vertex v, then u precedes v in the topological sort.
The DAG-SHORTEST-PATHS procedure makes just one pass over the
vertices in the topologically sorted order. As it processes each vertex, it
relaxes each edge that leaves the vertex. Figure 22.5 shows the execution
of this algorithm.

DAG-SHORTEST-PATHS(G, w, s)
1 topologically sort the vertices of G

2 INITIALIZE-SINGLE-SOURCE(G, s)
3 for each vertex u ∈ G.V, taken in topologically sorted order
4

for each vertex v in G.Adj[u]

5

RELAX(u, v, w)

Let’s  analyze  the  running  time  of  this  algorithm.  As  shown  in
Section 20.4, the topological sort of line 1 takes Θ(V + E) time. The call
of INITIALIZE-SINGLE-SOURCE in line 2 takes Θ(V) time. The for
loop of lines 3–5 makes one iteration per vertex. Altogether, the for loop
of lines 4–5 relaxes each edge exactly once. (We have used an aggregate
analysis  here.)  Because  each  iteration  of  the  inner  for  loop  takes  Θ(1)
time, the total running time is Θ(V + E), which is linear in the size of an
adjacency-list representation of the graph.

The  following  theorem  shows  that  the  DAG-SHORTEST-PATHS

procedure correctly computes the shortest paths.

Theorem 22.5
If  a  weighted,  directed  graph  G  =  (V,  E)  has  source  vertex  s  and  no
cycles,  then  at  the  termination  of  the  DAG-SHORTEST-PATHS
procedure,  v.d  =  δ(s,  v)  for  all  vertices  v  ∈  V,  and  the  predecessor
subgraph Gπ is a shortest-paths tree.

Proof      We  ﬁrst  show  that  v.d  =  δ(s,  v)  for  all  vertices  v  ∈  V  at
termination. If v is not reachable from s, then v.d = δ(s, v) = 1 by the no-
path property. Now, suppose that v is reachable from s, so that there is a
shortest  path  p  =  〈v0,  v1,  …  ,  vk〉,  where  v0  =  s  and  vk  =  v.  Because
DAG-SHORTEST-PATHS processes the vertices in topologically sorted
order, it relaxes the edges on p in the order (v0, v1), (v1, v2), … , (vk−1,
vk).  The  path-relaxation  property  implies  that  vi.d  =  δ(s,  vi)  at
termination  for  i  =  0,  1,  …  ,  k.  Finally,  by  the  predecessor-subgraph
property, Gπ is a shortest-paths tree.

▪

A  useful  application  of  this  algorithm  arises  in  determining  critical
paths  in  PERT  chart2  analysis.  A  job  consists  of  several  tasks.  Each

task takes a certain amount of time, and some tasks must be completed
before others can be started. For example, if the job is to build a house,
then  the  foundation  must  be  completed  before  starting  to  frame  the
exterior  walls,  which  must  be  completed  before  starting  on  the  roof.
Some  tasks  require  more  than  one  other  task  to  be  completed  before
they  can  be  started:  before  the  drywall  can  be  installed  over  the  wall
framing,  both  the  electrical  system  and  plumbing  must  be  installed.  A
dag models the tasks and dependencies. Edges represent tasks, with the
weight  of  an  edge  indicating  the  time  required  to  perform  the  task.
Vertices  represent  “milestones,”  which  are  achieved  when  all  the  tasks
represented  by  the  edges  entering  the  vertex  have  been  completed.  If
edge (u, v) enters vertex v and edge (v, x) leaves v, then task (u, v) must
be  completed  before  task  (v,  x)  is  started.  A  path  through  this  dag
represents  a  sequence  of  tasks  that  must  be  performed  in  a  particular
order. A critical path is a longest path through the dag, corresponding to
the longest time to perform any sequence of tasks. Thus, the weight of a
critical path provides a lower bound on the total time to perform all the
tasks,  even  if  as  many  tasks  as  possible  are  performed  simultaneously.
You can ﬁnd a critical path by either

negating  the  edge  weights  and  running  DAG-SHORTEST-
PATHS, or

running  DAG-SHORTEST-PATHS,  but  replacing  “∞”  by  “−∞”
in line 2 of INITIALIZE-SINGLE-SOURCE and “>” by “<” in
the RELAX procedure.

Figure 22.5 The execution of the algorithm for shortest paths in a directed acyclic graph. The
vertices are topologically sorted from left to right. The source vertex is s. The d values appear
within  the  vertices,  and  blue  edges  indicate  the  π  values.  (a)  The  situation  before  the  ﬁrst
iteration of the for loop of lines 3–5. (b)–(g) The situation after each iteration of the for loop of
lines 3–5. Blue vertices have had their outgoing edges relaxed. The vertex highlighted in orange
was used as u in that iteration. Each edge highlighted in orange caused a d value to change when
it was relaxed in that iteration. The values shown in part (g) are the ﬁnal values.

Exercises

22.2-1
Show the result of running DAG-SHORTEST-PATHS on the directed
acyclic graph of Figure 22.5, using vertex r as the source.

22.2-2
Suppose that you change line 3 of DAG-SHORTEST-PATHS to read

3 for the ﬁrst |V| − 1 vertices, taken in topologically sorted order

Show that the procedure remains correct.

22.2-3
An alternative way to represent a PERT chart looks more like the dag
of Figure 20.7 on page 574. Vertices represent tasks and edges represent
sequencing constraints, that is, edge (u, v) indicates that task u must be
performed  before  task  v.  Vertices,  not  edges,  have  weights.  Modify  the
DAG-SHORTEST-PATHS procedure so that it ﬁnds a longest path in a
directed acyclic graph with weighted vertices in linear time.

★ 22.2-4
Give  an  efﬁcient  algorithm  to  count  the  total  number  of  paths  in  a
directed  acyclic  graph.  The  count  should  include  all  paths  between  all
pairs of vertices and all paths with 0 edges. Analyze your algorithm.

22.3    Dijkstra’s algorithm

Dijkstra’s algorithm solves the single-source shortest-paths problem on
a  weighted,  directed  graph  G  =  (V,  E),  but  it  requires  nonnegative
weights on all edges: w(u, v) ≥ 0 for each edge (u, v) ∈ E. As we shall see,
with a good implementation, the running time of Dijkstra’s algorithm is
lower than that of the Bellman-Ford algorithm.

You  can  think  of  Dijkstra’s  algorithm  as  generalizing  breadth-ﬁrst
search  to  weighted  graphs.  A  wave  emanates  from  the  source,  and  the
ﬁrst time that a wave arrives at a vertex, a new wave emanates from that
vertex. Whereas breadth-ﬁrst search operates as if each wave takes unit
time  to  traverse  an  edge,  in  a  weighted  graph,  the  time  for  a  wave  to
traverse an edge is given by the edge’s weight. Because a shortest path in
a  weighted  graph  might  not  have  the  fewest  edges,  a  simple,  ﬁrst-in,
ﬁrst-out queue won’t sufﬁce for choosing the next vertex from which to
send out a wave.

Instead,  Dijkstra’s  algorithm  maintains  a  set  S  of  vertices  whose
ﬁnal  shortest-path  weights  from  the  source  s  have  already  been
determined. The algorithm repeatedly selects the vertex u ∈ V – S with
the minimum shortest-path estimate, adds u into S, and relaxes all edges
leaving  u.  The  procedure  DIJKSTRA  replaces  the  ﬁrst-in,  ﬁrst-out

queue  of  breadth-ﬁrst  search  by  a  min-priority  queue  Q  of  vertices,
keyed by their d values.

DIJKSTRA(G, w, s)
  1 INITIALIZE-SINGLE-SOURCE(G, s)
  2 S = Ø
  3 Q = Ø
  4 for each vertex u ∈ G.V
INSERT(Q, u)
  5
  6 while Q ≠ Ø
  7

u = EXTRACT-MIN(Q)
S = S ∪ {u}
for each vertex v in G.Adj[u]

RELAX(u, v, w)
if the call of RELAX decreased v.d
DECREASE-KEY(Q, v, v.d)

  8

  9

10

11

12

Dijkstra’s  algorithm  relaxes  edges  as  shown  in  Figure  22.6.  Line  1
initializes the d and π values in the usual way, and line 2 initializes the
set S to the empty set. The algorithm maintains the invariant that Q =
V − S at the start of each iteration of the while loop of lines 6–12. Lines
3–5 initialize the min-priority queue Q to contain all the vertices in V.
Since S = Ø at that time, the invariant is true upon ﬁrst reaching line 6.
Each time through the while loop of lines 6–12, line 7 extracts a vertex u
from  Q  =  V  −  S  and  line  8  adds  it  to  set  S,  thereby  maintaining  the
invariant. (The ﬁrst time through this loop,  u =  s.) Vertex  u, therefore,
has  the  smallest  shortest-path  estimate  of  any  vertex  in  V  −  S.  Then,
lines 9–12 relax each edge (u, v) leaving u, thus updating the estimate v.d
and the predecessor v.π if the shortest path to v found so far improves
by  going  through  u.  Whenever  a  relaxation  step  changes  the  d  and  π
values, the call to DECREASE-KEY in line 12 updates the min-priority
queue. The algorithm never inserts vertices into Q after the for loop of
lines  4–5,  and  each  vertex  is  extracted  from  Q  and  added  to  S  exactly
once, so that the while loop of lines 6–12 iterates exactly |V| times.

Figure  22.6  The  execution  of  Dijkstra’s  algorithm.  The  source  s  is  the  leftmost  vertex.  The
shortest-path  estimates  appear  within  the  vertices,  and  blue  edges  indicate  predecessor  values.
Blue vertices belong to the set S, and tan vertices are in the min-priority queue Q = V − S. (a)
The situation just before the ﬁrst iteration of the while loop of lines 6–12. (b)–(f) The situation
after each successive iteration of the while loop. In each part, the vertex highlighted in orange
was  chosen  as  vertex  u  in  line  7,  and  each  edge  highlighted  in  orange  caused  a  d  value  and  a
predecessor to change when the edge was relaxed. The d values and predecessors shown in part
(f) are the ﬁnal values.

Because  Dijkstra’s  algorithm  always  chooses  the  “lightest”  or
“closest” vertex in V − S to add to set S, you can think of it as using a
greedy strategy. Chapter 15 explains greedy strategies in detail, but you
need  not  have  read  that  chapter  to  understand  Dijkstra’s  algorithm.
Greedy strategies do not always yield optimal results in general, but as
the following theorem and its corollary show, Dijkstra’s algorithm does
indeed  compute  shortest  paths.  The  key  is  to  show  that  u.d  =  δ(s,  u)
each time it adds a vertex u to set S.

Figure 22.7 The proof of Theorem 22.6. Vertex u is selected to be added into set S in line 7 of
DIJKSTRA. Vertex y is the ﬁrst vertex on a shortest path from the source s to vertex u that is
not in set S, and x ∈ S is y’s predecessor on that shortest path. The subpath from y to u may or
may not re-enter set S.

Theorem 22.6 (Correctness of Dijkstra’s algorithm)
Dijkstra’s algorithm, run on a weighted, directed graph G = (V, E) with
nonnegative weight function w and source vertex s, terminates with u.d
= δ(s, u) for all vertices u ∈ V.

Proof   We will show that at the start of each iteration of the while loop
of  lines  6–12,  we  have  v.d  =  δ(s,  v)  for  all  v  ∈  S.  The  algorithm
terminates when S = V, so that v.d = δ(s, v) for all v ∈ V.

The  proof  is  by  induction  on  the  number  of  iterations  of  the  while
loop, which equals |S| at the start of each iteration. There are two bases:
for |S| = 0, so that S = Ø and the claim is trivially true, and for |S| = 1,
so that S = {s} and s.d = δ(s, s) = 0.

For  the  inductive  step,  the  inductive  hypothesis  is  that  v.d  =  δ(s,  v)
for all v ∈ S. The algorithm extracts vertex u from V − S. Because the
algorithm adds u into S, we need to show that u.d = δ(s, u) at that time.
If  there  is  no  path  from  s  to  u,  then  we  are  done,  by  the  no-path
property. If there is a path from s to u, then, as Figure 22.7 shows, let y
be the ﬁrst vertex on a shortest path from s to u that is not in S, and let
x ∈ S be the predecessor of y on that shortest path. (We could have y =
u or x = s.) Because y appears no later than u on the shortest path and
all  edge  weights  are  nonnegative,  we  have  δ(s,  y)  ≤  δ(s,  u).  Because  the
call of EXTRACT-MIN in line 7 returned u as having the minimum d
value  in  V  −  S,  we  also  have  u.d  ≤  y.d,  and  the  upper-bound  property
gives δ(s, u) ≤ u.d.

Since  x  ∈  S,  the  inductive  hypothesis  implies  that  x.d  =  δ(s,  x).
During the iteration of the while loop that added x into S, edge (x, y)
was relaxed. By the convergence property, y.d received the value of δ(s,
y) at that time. Thus, we have

δ(s, y) ≤ δ(s, u) ≤ u.d ≤ y.d and y.d = δ(s, y),
so that

δ(s, y) = δ(s, u) = u.d = y.d.
Hence, u.d = δ(s, u), and by the upper-bound property, this value never
changes again.

▪

Corollary 22.7
After Dijkstra’s algorithm is run on a weighted, directed graph G = (V,
E)  with  nonnegative  weight  function  w  and  source  vertex  s,  the
predecessor subgraph Gπ is a shortest-paths tree rooted at s.

Proof      Immediate  from  Theorem  22.6  and  the  predecessor-subgraph
property.

▪

Analysis

How fast is Dijkstra’s algorithm? It maintains the min-priority queue Q
by  calling  three  priority-queue  operations:  INSERT  (in  line  5),
EXTRACT-MIN  (in  line  7),  and  DECREASE-KEY  (in  line  12).  The
algorithm  calls  both  INSERT  and  EXTRACT-MIN  once  per  vertex.
Because each vertex u ∈ V is added to set S exactly once, each edge in
the adjacency list Adj[u] is examined in the for loop of lines 9–12 exactly
once  during  the  course  of  the  algorithm.  Since  the  total  number  of
edges in all the adjacency lists is |E|, this for loop iterates a total of |E|
times, and thus the algorithm calls DECREASE-KEY at most |E| times
overall. (Observe once again that we are using aggregate analysis.)

Just as in Prim’s algorithm, the running time of Dijkstra’s algorithm
depends on the speciﬁc implementation of the min-priority queue Q. A
simple implementation takes advantage of the vertices being numbered

1 to |V|: simply store v.d in the vth entry of an array. Each INSERT and
DECREASE-KEY  operation  takes  O(1)  time,  and  each  EXTRACT-
MIN  operation  takes  O(V)  time  (since  it  has  to  search  through  the
entire array), for a total time of O(V2 + E) = O(V2).

If  the  graph  is  sufﬁciently  sparse—in  particular,  E  =  o(V2/lg  V)—
you  can  improve  the  running  time  by  implementing  the  min-priority
queue  with  a  binary  min-heap  that  includes  a  way  to  map  between
vertices and their corresponding heap elements. Each EXTRACT-MIN
operation  then  takes  O(lg  V)  time.  As  before,  there  are  |V|  such
operations. The time to build the binary min-heap is O(V). (As noted in
Section  21.2,  you  don’t  even  need  to  call  BUILD-MIN-HEAP.)  Each
DECREASE-KEY  operation  takes  O(lg  V)  time,  and  there  are  still  at
most |E| such operations. The total running time is therefore O((V + E)
lg  V),  which  is  O(E  lg  V)  in  the  typical  case  that  |E|  =  Ω(V).  This
straightforward  O(V2)-time

time

the

running
improves  upon
implementation if E = o(V2/lg V).

By implementing the min-priority queue with a Fibonacci heap (see
page  478),  you  can  improve  the  running  time  to  O(V  lg  V  +  E).  The
amortized  cost  of  each  of  the  |V|  EXTRACT-MIN  operations  is  O(lg
V),  and  each  DECREASE-KEY  call,  of  which  there  are  at  most  |E|,
takes  only  O(1)  amortized  time.  Historically,  the  development  of
Fibonacci  heaps  was  motivated  by  the  observation  that  Dijkstra’s
algorithm  typically  makes  many  more  DECREASE-KEY  calls  than
EXTRACT-MIN  calls,  so  that  any  method  of  reducing  the  amortized
time of each DECREASE-KEY operation to o(lg V) without increasing
the amortized time of EXTRACT-MIN would yield an asymptotically
faster implementation than with binary heaps.

Dijkstra’s algorithm resembles both breadth-ﬁrst search (see Section
20.2) and Prim’s algorithm for computing minimum spanning trees (see
Section 21.2). It is like breadth-ﬁrst search in that set S corresponds to
the  set  of  black  vertices  in  a  breadth-ﬁrst  search.  Just  as  vertices  in  S
have their ﬁnal shortest-path weights, so do black vertices in a breadth-
ﬁrst  search  have  their  correct  breadth-ﬁrst  distances.  Dijkstra’s
algorithm  is  like  Prim’s  algorithm  in  that  both  algorithms  use  a  min-

priority queue to ﬁnd the “lightest” vertex outside a given set (the set S
in  Dijkstra’s  algorithm  and  the  tree  being  grown  in  Prim’s  algorithm),
add  this  vertex  into  the  set,  and  adjust  the  weights  of  the  remaining
vertices outside the set accordingly.

Exercises

22.3-1
Run  Dijkstra’s  algorithm  on  the  directed  graph  of  Figure  22.2,  ﬁrst
using vertex s as the source and then using vertex z as the source. In the
style  of  Figure  22.6,  show  the  d  and  π  values  and  the  vertices  in  set  S
after each iteration of the while loop.

22.3-2
Give  a  simple  example  of  a  directed  graph  with  negative-weight  edges
for  which  Dijkstra’s  algorithm  produces  an  incorrect  answer.  Why
doesn’t  the  proof  of  Theorem  22.6  go  through  when  negative-weight
edges are allowed?

22.3-3
Suppose that you change line 6 of Dijkstra’s algorithm to read

6   while |Q| > 1

This change causes the while loop to execute |V| − 1 times instead of |V|
times. Is this proposed algorithm correct?

22.3-4
Modify the DIJKSTRA procedure so that the priority queue Q is more
like the queue in the BFS procedure in that it contains only vertices that
have been reached from source s so far: Q ⊆ V − S and v ∈ Q implies
v.d ≠ ∞.

22.3-5
Professor  Gaedel  has  written  a  program  that  he  claims  implements
Dijkstra’s algorithm. The program produces v.d and v.π for each vertex
v  ∈  V.  Give  an  O(V  +  E)-time  algorithm  to  check  the  output  of  the
professor’s program. It should determine whether the d and π attributes

match those of some shortest-paths tree. You may assume that all edge
weights are nonnegative.

22.3-6
Professor  Newman  thinks  that  he  has  worked  out  a  simpler  proof  of
correctness for Dijkstra’s algorithm. He claims that Dijkstra’s algorithm
relaxes  the  edges  of  every  shortest  path  in  the  graph  in  the  order  in
which  they  appear  on  the  path,  and  therefore  the  path-relaxation
property  applies  to  every  vertex  reachable  from  the  source.  Show  that
the  professor  is  mistaken  by  constructing  a  directed  graph  for  which
Dijkstra’s algorithm relaxes the edges of a shortest path out of order.

22.3-7
Consider a directed graph G = (V, E) on which each edge (u, v) ∈ E has
an associated value r(u, v), which is a real number in the range 0 ≤ r(u, v)
≤  1  that  represents  the  reliability  of  a  communication  channel  from
vertex u to vertex v. Interpret r(u, v) as the probability that the channel
from  u  to  v  will  not  fail,  and  assume  that  these  probabilities  are
independent.  Give  an  efﬁcient  algorithm  to  ﬁnd  the  most  reliable  path
between two given vertices.

22.3-8
Let  G  =  (V,  E)  be  a  weighted,  directed  graph  with  positive  weight
function w : E → {1, 2, … , W} for some positive integer W, and assume
that  no  two  vertices  have  the  same  shortest-path  weights  from  source
vertex s. Now deﬁne an unweighted, directed graph G′ = (V ∪ V′, E′) by
replacing each edge (u, v) ∈ E with w(u, v) unit-weight edges in series.
How many vertices does G′ have? Now suppose that you run a breadth-
ﬁrst search on G′. Show that the order in which the breadth-ﬁrst search
of  G′  colors  vertices  in  V  black  is  the  same  as  the  order  in  which
Dijkstra’s  algorithm  extracts  the  vertices  of  V  from  the  priority  queue
when it runs on G.

22.3-9
Let G = (V, E) be a weighted, directed graph with nonnegative weight
function  w  :  E  →  {0,  1,  …  ,  W}  for  some  nonnegative  integer  W.

Modify Dijkstra’s algorithm to compute the shortest paths from a given
source vertex s in O(W V + E) time.

22.3-10
Modify your algorithm from Exercise 22.3-9 to run in O((V + E) lg W)
time.  (Hint:  How  many  distinct  shortest-path  estimates  can  V  −  S
contain at any point in time?)

22.3-11
Suppose  that  you  are  given  a  weighted,  directed  graph  G  =  (V,  E)  in
which edges that leave the source vertex s may have negative weights, all
other  edge  weights  are  nonnegative,  and  there  are  no  negative-weight
cycles.  Argue  that  Dijkstra’s  algorithm  correctly  ﬁnds  shortest  paths
from s in this graph.

22.3-12
Suppose that you have a weighted directed graph G = (V, E) in which all
edge  weights  are  positive  real  values  in  the  range  [C,  2C]  for  some
positive constant C. Modify Dijkstra’s algorithm so that it runs in O(V
+ E) time.

22.4    Difference constraints and shortest paths

Chapter  29  studies  the  general  linear-programming  problem,  showing
how to optimize a linear function subject to a set of linear inequalities.
This  section  investigates  a  special  case  of  linear  programming  that
reduces  to  ﬁnding  shortest  paths  from  a  single  source.  The  Bellman-
Ford  algorithm  then  solves  the  resulting  single-source  shortest-paths
problem, thereby also solving the linear-programming problem.

Linear programming

In the general linear-programming problem, the input is an m × n matrix
A, an m-vector b, and an n-vector c. The goal is to ﬁnd a vector x of n
elements  that  maximizes  the  objective  function
  subject  to  the  m
constraints given by Ax ≤ b.

The most popular method for solving linear programs is the simplex
algorithm,  which  Section  29.1  discusses.  Although  the  simplex
algorithm  does  not  always  run  in  time  polynomial  in  the  size  of  its
input,  there  are  other  linear-programming  algorithms  that  do  run  in
polynomial time. We offer here two reasons to understand the setup of
linear-programming  problems.  First,  if  you  know  that  you  can  cast  a
given problem as a polynomial-sized linear-programming problem, then
you  immediately  have  a  polynomial-time  algorithm  to  solve  the
problem. Second, faster algorithms exist for many special cases of linear
programming.  For  example,  the  single-pair  shortest-path  problem
(Exercise  22.4-4)  and  the  maximum-ﬂow  problem  (Exercise  24.1-5)  are
special cases of linear programming.

Sometimes the objective function does not matter: it’s enough just to
ﬁnd any feasible solution, that is, any vector x that satisﬁes Ax ≤ b, or to
determine  that  no  feasible  solution  exists.  This  section  focuses  on  one
such feasibility problem.

Systems of difference constraints

In  a  system  of  difference  constraints,  each  row  of  the
linear-
programming matrix A contains one 1 and one −1, and all other entries
of A are 0. Thus, the constraints given by Ax ≤ b are a set of mdifference
constraints  involving  n  unknowns,  in  which  each  constraint  is  a  simple
linear inequality of the form

xj − xi ≤ bk,

where 1 ≤ i, j ≤ n, i ≠ j, and 1 ≤ k ≤ m.

For example, consider the problem of ﬁnding a 5-vector x = (xi) that

satisﬁes

This  problem  is  equivalent  to  ﬁnding  values  for  the  unknowns  x1,  x2,
x3, x4, x5, satisfying the following 8 difference constraints:

One solution to this problem is x = (−5, −3, 0, −1, −4), which you can
verify  directly  by  checking  each  inequality.  In  fact,  this  problem  has
more  than  one  solution.  Another  is  x′  =  (0,  2,  5,  4,  1).  These  two
solutions  are  related:  each  component  of  x′  is  5  larger  than  the
corresponding component of x. This fact is not mere coincidence.

Lemma 22.8
Let x = (x1, x2, … , xn) be a solution to a system Ax ≤ b of difference
constraints, and let d be any constant. Then x + d = (x1 + d, x2 + d, … ,
xn + d) is a solution to Ax ≤ b as well.

Proof   For each xi and xj, we have (xj + d) − (xi + d) = xj − xi. Thus, if
x satisﬁes Ax ≤ b, so does x + d.

▪

Systems  of  difference  constraints  occur  in  various  applications.  For
example, the unknowns xi might be times at which events are to occur.
Each constraint states that at least a certain amount of time, or at most
a certain amount of time, must elapse between two events. Perhaps the
events are jobs to be performed during the assembly of a product. If the
manufacturer  applies  an  adhesive  that  takes  2  hours  to  set  at  time  x1
and has to wait until it sets to install a part at time x2, then there is a
constraint  that  x2  ≥  x1  +  2  or,  equivalently,  that  x1  −  x2  ≤  −2.
Alternatively,  the  manufacturer  might  require  the  part  to  be  installed
after the adhesive has been applied but no later than the time that the

adhesive has set halfway. In this case, there is a pair of constraints x2 ≥
x1 and x2 ≤ x1 + 1 or, equivalently, x1 − x2 ≤ 0 and x2 − x1 ≤ 1.

If  all  the  constraints  have  nonnegative  numbers  on  the  right-hand
side—that  is,  if  bi  ≥  0  for  i  =  1,  2,  …  ,  m—then  ﬁnding  a  feasible
solution is trivial: just set all the unknowns xi equal to each other. Then
all  the  differences  are  0,  and  every  constraint  is  satisﬁed.  The  problem
of  ﬁnding  a  feasible  solution  to  a  system  of  difference  constraints  is
interesting only if at least one constraint has bi < 0.

Constraint graphs

We  can  interpret  systems  of  difference  constraints  from  a  graph-
theoretic  point  of  view.  For  a  system  Ax  ≤  b  of  difference  constraints,
let’s view the m × n linear-programming matrix A as the transpose of an
incidence matrix (see Exercise 20.1-7) for a graph with n vertices and m
edges. Each vertex vi in the graph, for i = 1, 2, … , n, corresponds to one
of  the  n  unknown  variables  xi.  Each  directed  edge  in  the  graph
corresponds to one of the m inequalities involving two unknowns.

More  formally,  given  a  system  Ax  ≤  b  of  difference  constraints,  the
corresponding constraint graph is a weighted, directed graph G = (V, E),
where

V = {v0, v1, … , vn}

and

E = {(vi, vj) : xj − xi ≤ bk is a constraint}

   ∪ {(v0, v1), (v0, v2), (v0, v3), … , (v0, vn)}.

The  constraint  graph  includes  the  additional  vertex  v0,  as  we  shall  see
shortly, to guarantee that the graph has some vertex that can reach all
other  vertices.  Thus,  the  vertex  set  V  consists  of  a  vertex  vi  for  each
unknown  xi,  plus  an  additional  vertex  v0.  The  edge  set  E  contains  an
edge  for  each  difference  constraint,  plus  an  edge  (v0,  vi)  for  each
unknown xi. If xj − xi ≤ bk is a difference constraint, then the weight of

edge  (vi,  vj)  is  w(vi,  vj)  =  bk.  The  weight  of  each  edge  leaving  v0  is  0.
Figure  22.8  shows  the  constraint  graph  for  the  system  (22.2)–(22.9)  of
difference constraints.

Figure  22.8  The  constraint  graph  corresponding  to  the  system  (22.2)–(22.9)  of  difference
constraints. The value of δ(v0, vi) appears in each vertex vi. One feasible solution to the system
is x = (−5, −3, 0, −1, −4).

The  following  theorem  shows  how  to  solve  a  system  of  difference
constraints  by  ﬁnding  shortest-path  weights  in  the  corresponding
constraint graph.

Theorem 22.9
Given  a  system  Ax  ≤  b  of  difference  constraints,  let  G  =  (V,  E)  be  the
corresponding  constraint  graph.  If  G  contains  no  negative-weight
cycles, then

is  a  feasible  solution  for  the  system.  If  G  contains  a  negative-weight
cycle, then there is no feasible solution for the system.

Proof   We ﬁrst show that if the constraint graph contains no negative-
weight  cycles,  then  equation  (22.10)  gives  a  feasible  solution.  Consider
any edge (vi, vj) ∈ E. The triangle inequality implies that δ(v0, vj) ≤ δ(v0,
vi) + w(vi, vj), which is equivalent to δ(v0, vj)−δ(v0, vi) ≤ w(vi, vj). Thus,
letting xi = δ(v0, vi) and xj = δ(v0, vj) satisﬁes the difference constraint
xj − xi ≤ w(vi, vj) that corresponds to edge (vi, vj).

Now we show that if the constraint graph contains a negative-weight
cycle, then the system of difference constraints has no feasible solution.
Without loss of generality, let the negative-weight cycle be c = 〈v1, v2,
… , vk〉, where v1 = vk. (The vertex v0 cannot be on cycle c, because it
has no entering edges.) Cycle c corresponds to the following difference
constraints:

x2 − x1 ≤ w(v1, v2),
x3 − x2 ≤ w(v2, v3),

⋮
xk−1 − xk−2 ≤ w(vk−2, vk−1),
xk − xk−1 ≤ w(vk−1, vk).

We’ll assume that x has a solution satisfying each of these k inequalities
and  then  derive  a  contradiction.  The  solution  must  also  satisfy  the
inequality  that  results  from  summing  the  k  inequalities  together.  In
summing  the  left-hand  sides,  each  unknown  xi  is  added  in  once  and
subtracted  out  once  (remember  that  v1  =  vk  implies  x1  =  xk),  so  that
the  left-hand  side  sums  to  0.  The  right-hand  side  sums  to  the  weight
w(c) of the cycle, giving 0 ≤ w(c). But since c is a negative-weight cycle,
w(c) < 0, and we obtain the contradiction that 0 ≤ w(c) < 0.

▪

Solving systems of difference constraints

Theorem 22.9 suggests how to use the Bellman-Ford algorithm to solve
a  system  of  difference  constraints.  Because  the  constraint  graph
contains  edges  from  the  source  vertex  v0  to  all  other  vertices,  any
negative-weight cycle in the constraint graph is reachable from v0. If the
Bellman-Ford algorithm returns TRUE, then the shortest-path weights
give  a  feasible  solution  to  the  system.  In  Figure  22.8,  for  example,  the
shortest-path  weights  provide  the  feasible  solution  x  =  (−5,  −3,  0,  −1,
−4),  and  by  Lemma  22.8,  x  =  (d  −  5,  d  −  3,  d,  d  −  1,  d  −  4)  is  also  a

feasible  solution  for  any  constant  d.  If  the  Bellman-Ford  algorithm
returns FALSE, there is no feasible solution to the system of difference
constraints.

A  system  of  difference  constraints  with  m  constraints  on  n
unknowns produces a graph with n + 1 vertices and n + m edges. Thus,
the Bellman-Ford algorithm provides a way to solve the system in O((n
+ 1)(n + m)) = O(n2 + nm) time. Exercise 22.4-5 asks you to modify the
algorithm to run in O(nm) time, even if m is much less than n.

Exercises

22.4-1
Find a feasible solution or determine that no feasible solution exists for
the following system of difference constraints:

x1 − x2 ≤ 1,
x1 − x4 ≤ −4,
x2 − x3 ≤ 2,
x2 − x5 ≤ 7,
x2 − x6 ≤ 5,
x3 − x6 ≤ 10,
x4 − x2 ≤ 2,
x5 − x1 ≤ −1,
x5 − x4 ≤ 3,
x6 − x3 ≤ −8.

22.4-2
Find a feasible solution or determine that no feasible solution exists for
the following system of difference constraints:

x1 − x2 ≤ 4,
x1 − x5 ≤ 5,

x2 − x4 ≤ −6,
x3 − x2 ≤ 1,
x4 − x1 ≤ 3,
x4 − x3 ≤ 5,
x4 − x5 ≤ 10,
x5 − x3 ≤ −4,
x5 − x4 ≤ −8.

22.4-3
Can  any  shortest-path  weight  from  the  new  vertex  v0  in  a  constraint
graph be positive? Explain.

22.4-4
Express the single-pair shortest-path problem as a linear program.

22.4-5
Show how to modify the Bellman-Ford algorithm slightly so that when
using  it  to  solve  a  system  of  difference  constraints  with  m  inequalities
on n unknowns, the running time is O(nm).

22.4-6
Consider  adding  equality  constraints  of  the  form  xi  =  xj  +  bk  to  a
system  of  difference  constraints.  Show  how  to  solve  this  variety  of
constraint system.

22.4-7
Show  how  to  solve  a  system  of  difference  constraints  by  a  Bellman-
Ford-like  algorithm  that  runs  on  a  constraint  graph  without  the  extra
vertex v0.

★ 22.4-8
Let Ax ≤ b be a system of m difference constraints in n unknowns. Show
that  the  Bellman-Ford  algorithm,  when  run  on  the  corresponding
 subject to Ax ≤ b and xi ≤ 0 for all xi.
constraint graph, maximizes

★ 22.4-9
Show  that  the  Bellman-Ford  algorithm,  when  run  on  the  constraint
graph  for  a  system  Ax  ≤  b  of  difference  constraints,  minimizes  the
quantity (max {xi}−min {xi}) subject to Ax ≤ b. Explain how this fact
might come in handy if the algorithm is used to schedule construction
jobs.

22.4-10
Suppose  that  every  row  in  the  matrix  A  of  a  linear  program  Ax  ≤  b
corresponds  to  a  difference  constraint,  a  single-variable  constraint  of
the  form  xi  ≤  bk,  or  a  single-variable  constraint  of  the  form  −xi  ≤  bk.
Show how to adapt the Bellman-Ford algorithm to solve this variety of
constraint system.

22.4-11
Give  an  efﬁcient  algorithm  to  solve  a  system  Ax  ≤  b  of  difference
constraints when all of the elements of b are real-valued and all of the
unknowns xi must be integers.

★ 22.4-12
Give  an  efﬁcient  algorithm  to  solve  a  system  Ax  ≤  b  of  difference
constraints when all of the elements of b are real-valued and a speciﬁed
subset  of  some,  but  not  necessarily  all,  of  the  unknowns  xi  must  be
integers.

22.5    Proofs of shortest-paths properties

Throughout  this  chapter,  our  correctness  arguments  have  relied  on  the
triangle
inequality,  upper-bound  property,  no-path  property,
convergence  property,  path-relaxation  property,  and  predecessor-
subgraph  property.  We  stated  these  properties  without  proof  on  page
611. In this section, we prove them.

The triangle inequality

In  studying  breadth-ﬁrst  search  (Section  20.2),  we  proved  as  Lemma
20.1 a simple property of shortest distances in unweighted graphs. The
triangle inequality generalizes the property to weighted graphs.

Lemma 22.10 (Triangle inequality)
Let G = (V, E) be a weighted, directed graph with weight function w : E
→ ℝ and source vertex s. Then, for all edges (u, v) ∈ E,
δ(s, v) ≤ δ(s, u) + w(u, v).

Proof   Suppose that p is a shortest path from source s to vertex v. Then
p has no more weight than any other path from s to v. Speciﬁcally, path
p has no more weight than the particular path that takes a shortest path
from source s to vertex u and then takes edge (u, v).

Exercise  22.5-3  asks  you  to  handle  the  case  in  which  there  is  no

shortest path from s to v.

▪

Effects of relaxation on shortest-path estimates

The  next  group  of  lemmas  describes  how  shortest-path  estimates  are
affected  by  executing  a  sequence  of  relaxation  steps  on  the  edges  of  a
weighted,  directed  graph  that  has  been  initialized  by  INITIALIZE-
SINGLE-SOURCE.

Lemma 22.11 (Upper-bound property)
Let G = (V, E) be a weighted, directed graph with weight function w : E
→ ℝ. Let s ∈ V be the source vertex, and let the graph be initialized by
INITIALIZE-SINGLE-SOURCE(G,  s).  Then,  v.d  ≥  δ(s,  v)  for  all  v  ∈
V,  and  this  invariant  is  maintained  over  any  sequence  of  relaxation
steps  on  the  edges  of  G.  Moreover,  once  v.d  achieves  its  lower  bound
δ(s, v), it never changes.

Proof      We  prove  the  invariant  v.d  ≥  δ(s,  v)  for  all  vertices  v  ∈  V  by
induction over the number of relaxation steps.

For the base case, v.d ≥ δ(s, v) holds after initialization, since if v.d =
∞, then v.d ≥ δ(s, v) for all v ∈ V − {s}, and since s.d = 0 ≥ δ(s, s). (Note

that  δ(s,  s)  =  −∞  if  s  is  on  a  negative-weight  cycle  and  that  δ(s,  s)  =  0
otherwise.)

For the inductive step, consider the relaxation of an edge (u, v). By
the  inductive  hypothesis,  x.d  ≥  δ(s,  x)  for  all  x  ∈  V  prior  to  the
relaxation.  The  only  d  value  that  may  change  is  v.d.  If  it  changes,  we
have

v.d = u.d + w(u, v)

≥ δ(s, u) + w(u, v) (by the inductive hypothesis)
(by the triangle inequality),
≥ δ(s, v)

and so the invariant is maintained.

The  value  of  v.d  never  changes  once  v.d  =  δ(s,  v)  because,  having
achieved its lower bound, v.d cannot decrease since we have just shown
that v.d ≥ δ(s, v), and it cannot increase because relaxation steps do not
increase d values.

▪

Corollary 22.12 (No-path property)
Suppose  that  in  a  weighted,  directed  graph  G  =  (V,  E)  with  weight
function w : E → ℝ, no path connects a source vertex s ∈ V to a given
vertex  v  ∈  V.  Then,  after  the  graph  is  initialized  by  INITIALIZE-
SINGLE-SOURCE(G, s), we have v.d = δ(s, v) = ∞, and this equation is
maintained as an invariant over any sequence of relaxation steps on the
edges of G.

Proof   By the upper-bound property, we always have ∞ = δ(s, v) ≤ v.d,
and thus v.d = ∞ = δ(s, v).

▪

Lemma 22.13
Let G = (V, E) be a weighted, directed graph with weight function w : E
→ ℝ, and let (u, v) ∈ E. Then, immediately after edge (u, v) is relaxed
by a call of RELAX(u, v, w), we have v.d ≤ u.d + w(u, v).

Proof   If, just prior to relaxing edge (u, v), we have v.d > u.d + w(u, v),
then  v.d  =  u.d  +  w(u,  v)  afterward.  If,  instead,  v.d  ≤  u.d  +  w(u,  v)  just

before the relaxation, then neither u.d nor v.d changes, and so v.d ≤ u.d +
w(u, v) afterward.

▪

Lemma 22.14 (Convergence property)
Let G = (V, E) be a weighted, directed graph with weight function w : E
→ ℝ, let s ∈ V be a source vertex, and let s ⇝ u → v be a shortest path
in  G  for  some  vertices  u,  v  ∈  V.  Suppose  that  G  is  initialized  by
INITIALIZE-SINGLE-SOURCE(G,  s)  and  then  a  sequence  of
relaxation steps that includes the call RELAX(u, v, w) is executed on the
edges of G. If u.d = δ(s, u) at any time prior to the call, then v.d = δ(s, v)
at all times after the call.

Proof   By the upper-bound property, if u.d = δ(s, u) at some point prior
to relaxing edge (u, v), then this equation holds thereafter. In particular,
after edge (u, v) is relaxed, we have

v.d ≤ u.d + w(u, v)

(by Lemma 22.13)

= δ(s, u) + w(u, v)
= δ(s, u)

(by Lemma 22.1 on page 606).

The  upper-bound  property  gives  v.d  ≥  δ(s,  v),  from  which  we  conclude
that v.d = δ(s, v), and this equation is maintained thereafter.

▪

Lemma 22.15 (Path-relaxation property)
Let G = (V, E) be a weighted, directed graph with weight function w : E
→ ℝ, and let s ∈ V be a source vertex. Consider any shortest path p =
〈v0, v1, … , vk〉 from s = v0 to vk. If G is initialized by INITIALIZE-
SINGLE-SOURCE(G,  s)  and  then  a  sequence  of  relaxation  steps
occurs  that  includes,  in  order,  relaxing  the  edges  (v0,  v1),  (v1,  v2),  …  ,
(vk−1,  vk),  then  vk.d  =  δ(s,  vk)  after  these  relaxations  and  at  all  times
afterward.  This  property  holds  no  matter  what  other  edge  relaxations
occur, including relaxations that are intermixed with relaxations of the
edges of p.

Proof   We show by induction that after the ith edge of path p is relaxed,
we have vi.d = δ(s, vi). For the base case, i = 0, and before any edges of p
have been relaxed, we have from the initialization that v0.d = s.d = 0 =
δ(s,  s).  By  the  upper-bound  property,  the  value  of  s.d  never  changes
after initialization.

For  the  inductive  step,  assume  that  vi−1.d  =  δ(s,  vi−1).  What
happens  when  edge  (vi−1,  vi)  is  relaxed?  By  the  convergence  property,
after  this  relaxation,  we  have  vi.d  =  δ(s,  vi),  and  this  equation  is
maintained at all times thereafter.

▪

Relaxation and shortest-paths trees

We  now  show  that  once  a  sequence  of  relaxations  has  caused  the
shortest-path  estimates  to  converge  to  shortest-path  weights,  the
predecessor subgraph Gπ induced by the resulting π values is a shortest-
paths tree for G. We start with the following lemma, which shows that
the predecessor subgraph always forms a rooted tree whose root is the
source.

Lemma 22.16
Let G = (V, E) be a weighted, directed graph with weight function w : E
→  ℝ  let  s  ∈  V  be  a  source  vertex,  and  assume  that  G  contains  no
negative-weight cycles that are reachable from s. Then, after the graph is
initialized  by  INITIALIZE-SINGLE-SOURCE(G,  s),  the  predecessor
subgraph  Gπ  forms  a  rooted  tree  with  root  s,  and  any  sequence  of
relaxation steps on edges of G maintains this property as an invariant.

Proof      Initially,  the  only  vertex  in  Gπ  is  the  source  vertex,  and  the
lemma is trivially true. Consider a predecessor subgraph Gπ that arises
after  a  sequence  of  relaxation  steps.  We  ﬁrst  prove  that  Gπ  is  acyclic.
Suppose for the sake of contradiction that some relaxation step creates
a cycle in the graph Gπ. Let the cycle be c = 〈v0, v1, … , vk〉, where vk =

v0. Then, vi.π = vi−1 for i = 1, 2, … , k and, without loss of generality,
assume that relaxing edge (vk−1, vk) created the cycle in Gπ.

We  claim  that  all  vertices  on  cycle  c  are  reachable  from  the  source
vertex s. Why? Each vertex on c has a non-NIL predecessor, and so each
vertex  on  c  was  assigned  a  ﬁnite  shortest-path  estimate  when  it  was
assigned its non-NIL π value. By the upper-bound property, each vertex
on  cycle  c  has  a  ﬁnite  shortest-path  weight,  which  means  that  it  is
reachable from s.

We’ll  examine  the  shortest-path  estimates  on  cycle  c  immediately
before  the  call  RELAX(vk−1,  vk,  w)  and  show  that  c  is  a  negative-
weight  cycle,  thereby  contradicting  the  assumption  that  G  contains  no
negative-weight  cycles  that  are  reachable  from  the  source.  Just  before
the call, we have vi.π = vi−1 for i = 1, 2, … , k − 1. Thus, for i = 1, 2, … ,
k  −  1,  the  last  update  to  vi.d  was  by  the  assignment  vi.d  =
vi−1.d+w(vi−1,  vi).  If  vi−1.d  changed  since  then,
it  decreased.
Therefore, just before the call RELAX(vk−1, vk, w), we have

Because vk.π is changed by the call RELAX(vk−1, vk, w), immediately
beforehand we also have the strict inequality

vk.d > vk−1.d + wvk−1, vk):

Summing this strict inequality with the k − 1 inequalities (22.11), we

obtain the sum of the shortest-path estimates around cycle c:

But

Figure 22.9 Showing that a simple path in Gπ from source vertex s to vertex v is unique. If Gπ
contains two paths p1 (s ⇝ u ⇝ x → z ⇝ v) and p2 (s ⇝ u ⇝ y → z ⇝ v), where x ≠ y, then z.π = x
and z.π = y, a contradiction.

since each vertex in the cycle c appears exactly once in each summation.
This equation implies

Thus, the sum of weights around the cycle c is negative, which provides
the desired contradiction.

We  have  now  proven  that  Gπ  is  a  directed,  acyclic  graph.  To  show
that it forms a rooted tree with root s, it sufﬁces (see Exercise B.5-2 on
page 1175) to prove that for each vertex v ∈ Vπ, there is a unique simple
path from s to v in Gπ.

The  vertices  in  Vπ  are  those  with  non-NIL  values,  plus  s.  Exercise

22.5-6 asks you to prove that a path from s exists to each vertex in Vπ.

To  complete  the  proof  of  the  lemma,  we  now  show  that  for  any
vertex v ∈ Vπ, the graph Gπ contains at most one simple path from s to
v.  Suppose  otherwise.  That  is,  suppose  that,  as  Figure  22.9  illustrates,
Gπ  contains  two  simple  paths  from  s  to  some  vertex  v:  p1,  which  we
decompose into s ⇝ u ⇝ x → z ⇝ v, and p2, which we decompose into s
⇝ u ⇝ y → z ⇝ v, where x ≠ y (though u could be s and z could be v).
But then, z.π = x and z.π = y, which implies the contradiction that x =
y. We conclude that Gπ contains a unique simple path from s to v, and
thus Gπ forms a rooted tree with root s.

▪

We  can  now  show  that  if  all  vertices  have  been  assigned  their  true
shortest-path  weights  after  a  sequence  of  relaxation  steps,  then  the

predecessor subgraph Gπ is a shortest-paths tree.

Lemma 22.17 (Predecessor-subgraph property)
Let G = (V, E) be a weighted, directed graph with weight function w : E
→  ℝ,  let  s  ∈  V  be  a  source  vertex,  and  assume  that  G  contains  no
negative-weight  cycles  that  are  reachable  from  s.  Then,  after  a  call  to
INITIALIZE-SINGLE-SOURCE(G,  s)  followed  by  any  sequence  of
relaxation steps on edges of G that produces v.d = δ(s, v) for all v ∈ V,
the predecessor subgraph Gπ is a shortest-paths tree rooted at s.

Proof   We must prove that the three properties of shortest-paths trees
given on page 608 hold for Gπ. To show the ﬁrst property, we must show
that Vπ is the set of vertices reachable from s. By deﬁnition, a shortest-
path weight δ(s, v) is ﬁnite if and only if v is reachable from s, and thus
the  vertices  that  are  reachable  from  s  are  exactly  those  with  ﬁnite  d
values. But a vertex v ∈ V − {s} has been assigned a ﬁnite value for v.d
if  and  only  if  v.π  ≠  NIL,  since  both  assignments  occur  in  RELAX.
Thus, the vertices in Vπ are exactly those reachable from s.

The second property, that Gπ forms a rooted tree with root s, follows

directly from Lemma 22.16.

It  remains,  therefore,  to  prove  the  last  property  of  shortest-paths
  in  Gπ  is  a
trees:  for  each  vertex  v  ∈  Vπ,  the  unique  simple  path
shortest path from s to v in G. Let p = 〈v0, v1, … , vk〉, where v0 = s and
vk = v. Consider an edge (vi−1, vi) in path p. Because this edge belongs
to Gπ, the last relaxation that changed vi.d must have been of this edge.
After that relaxation, we had vi.d = vi−1.d + (vi−1, vi). Subsequently, an
edge entering vi−1 could have been relaxed, causing vi−1.d to decrease
further,  but  without  changing  vi.d.  Therefore,  we  have  vi.d  ≥  vi−1.d  +
w(vi−1, vi). Thus, for i = 1, 2, … , k, we have both vi.d = δ(s, vi) and vi.d
≥ vi−1.d + w(vi−1, vi), which together imply w(vi−1, vi) ≤ δ(s, vi) − δ(s,
vi−1). Summing the weights along path p yields

Thus,  we  have  w(p)  ≤  δ(s,  vk).  Since  δ(s,  vk)  is  a  lower  bound  on  the
weight of any path from s to vk, we conclude that w(p) = δ(s, vk), and p
is a shortest path from s to v = vk.

▪

Exercises

22.5-1
Give  two  shortest-paths  trees  for  the  directed  graph  of  Figure  22.2  on
page 609 other than the two shown.

22.5-2
Give an example of a weighted, directed graph G = (V, E) with weight
function  w  :  E  →  ℝ  and  source  vertex  s  such  that  G  satisﬁes  the
following property: For every edge (u, v) ∈ E, there is a shortest-paths
tree  rooted  at  s  that  contains  (u,  v)  and  another  shortest-paths  tree
rooted at s that does not contain (u, v).

22.5-3
Modify  the  proof  of  Lemma  22.10  to  handle  cases  in  which  shortest-
path weights are ∞ or −∞.

22.5-4
Let G = (V, E) be a weighted, directed graph with source vertex s, and
let  G  be  initialized  by  INITIALIZE-SINGLE-SOURCE(G,  s).  Prove
that if a sequence of relaxation steps sets s.π to a non-NIL value, then G
contains a negative-weight cycle.

22.5-5

Let  G  =  (V,  E)  be  a  weighted,  directed  graph  with  no  negative-weight
edges. Let s ∈ V be the source vertex, and suppose that v.π is allowed to
be the predecessor of v on any shortest path to v from source s if v ∈ V
− {s} is reachable from s, and NIL otherwise. Give an example of such
a  graph  G  and  an  assignment  of  π  values  that  produces  a  cycle  in  Gπ.
(By  Lemma  22.16,  such  an  assignment  cannot  be  produced  by  a
sequence of relaxation steps.)

22.5-6
Let G = (V, E) be a weighted, directed graph with weight function w : E
→ ℝ and no negative-weight cycles. Let s ∈ V be the source vertex, and
let  G  be  initialized  by  INITIALIZE-SINGLE-SOURCE(G,  s).  Use
induction to prove that for every vertex v ∈ Vπ, there exists a path from
s  to  v  in  Gπ  and  that  this  property  is  maintained  as  an  invariant  over
any sequence of relaxations.

22.5-7
Let G = (V, E) be a weighted, directed graph that contains no negative-
weight cycles. Let s ∈ V be the source vertex, and let G be initialized by
INITIALIZESINGLE-SOURCE(G,  s).  Prove  that  there  exists  a
sequence of |V| − 1 relaxation steps that produces v.d = δ(s, v) for all v
∈ V.

22.5-8
Let  G  be  an  arbitrary  weighted,  directed  graph  with  a  negative-weight
cycle  reachable  from  the  source  vertex  s.  Show  how  to  construct  an
inﬁnite  sequence  of  relaxations  of  the  edges  of  G  such  that  every
relaxation causes a shortest-path estimate to change.

Problems

22-1     Yen’s improvement to Bellman-Ford
The  Bellman-Ford  algorithm  does  not  specify  the  order  in  which  to
relax  edges  in  each  pass.  Consider  the  following  method  for  deciding
upon the order. Before the ﬁrst pass, assign an arbitrary linear order v1,

v2, … , v|V| to the vertices of the input graph G = (V, E). Then partition
the edge set E into Ef ∪ Eb, where Ef = {(vi, vj) ∈ E : i < j} and Eb =
{(vi,  vj)  ∈  E  :  i  >  j}.  (Assume  that  G  contains  no  self-loops,  so  that
every edge belongs to either Ef or Eb.) Deﬁne Gf = (V, Ef) and Gb = (V,
Eb).

a. Prove that Gf is acyclic with topological sort 〈v1, v2, … , v|V|〉 and

that Gb is acyclic with topological sort 〈v|V|, v|V|−1, … , v1〉.

Suppose that each pass of the Bellman-Ford algorithm relaxes edges in
the  following  way.  First,  visit  each  vertex  in  the  order  v1,  v2,  …  ,  v|V|,
relaxing edges of Ef that leave the vertex. Then visit each vertex in the
order v|V|, v|V|−1, …, v1, relaxing edges of Eb that leave the vertex.

b. Prove that with this scheme, if G contains no negative-weight cycles
that are reachable from the source vertex s, then after only ⌈|V| / 2⌉
passes over the edges, v.d = δ(s, v) for all vertices v ∈ V.

c. Does this scheme improve the asymptotic running time of the

Bellman-Ford algorithm?

22-2     Nesting boxes
A  d-dimensional  box  with  dimensions  (x1,  x2,  …  ,  xd)  nests  within
another  box  with  dimensions  (y1,  y2,  …  ,  yd)  if  there  exists  a
permutation  π  on  {1,  2,  …  ,  d}  such  that  xπ(1)  <  y1,  xπ(2)  <  y2,  …  ,
xπ(d) < yd.

a. Argue that the nesting relation is transitive.

b. Describe an efﬁcient method to determine whether one d-dimensional

box nests inside another.

c. You are given a set of n d-dimensional boxes {B1, B2, … , Bn}. Give

an efﬁcient algorithm to ﬁnd the longest sequence
boxes such that
 nests within
running time of your algorithm in terms of n and d.

 for j = 1, 2, … , k − 1. Express the

 of

22-3     Arbitrage
Arbitrage  is  the  use  of  discrepancies  in  currency  exchange  rates  to
transform one unit of a currency into more than one unit of the same
currency.  For  example,  suppose  that  one  U.S.  dollar  buys  64  Indian
rupees, one Indian rupee buys 1:8 Japanese yen, and one Japanese yen
buys  0:009  U.S.  dollars.  Then,  by  converting  currencies,  a  trader  can
start with 1 U.S. dollar and buy 64 × 1.8 × 0.009 = 1.0368 U.S. dollars,
thus turning a proﬁt of 3.68%.

Suppose that you are given n currencies c1, c2, … , cn and an n × n
table  R  of  exchange  rates,  such  that  1  unit  of  currency  ci  buys  R[i,  j]
units of currency cj.

a. Give an efﬁcient algorithm to determine whether there exists a

sequence of currencies

 such that

R[i1, i2] · R[i2, i3] … R[ik−1, ik] · R[ik, i1] > 1.

Analyze the running time of your algorithm.

b. Give an efﬁcient algorithm to print out such a sequence if one exists.

Analyze the running time of your algorithm.

22-4     Gabow’s scaling algorithm for single-source shortest paths

A  scaling  algorithm  solves  a  problem  by  initially  considering  only  the
highest-order  bit  of  each  relevant  input  value,  such  as  an  edge  weight,
assuming that these values are nonnegative integers. The algorithm then
reﬁnes  the  initial  solution  by  looking  at  the  two  highest-order  bits.  It
progressively  looks  at  more  and  more  high-order  bits,  reﬁning  the
solution  each  time,  until  it  has  examined  all  bits  and  computed  the
correct solution.

This  problem  examines  an  algorithm  for  computing  the  shortest
paths  from  a  single  source  by  scaling  edge  weights.  The  input  is  a
directed graph G = (V, E) with nonnegative integer edge weights w. Let
W = max {w(u, v) : (u, v) = E} be the maximum weight of any edge. In
this problem, you will develop an algorithm that runs in O(E lg W) time.
Assume that all vertices are reachable from the source.

The scaling algorithm uncovers the bits in the binary representation
of  the  edge  weights  one  at  a  time,  from  the  most  signiﬁcant  bit  to  the
least  signiﬁcant  bit.  Speciﬁcally,  let  k  =  ⌈lg(W  +  1)⌉  be  the  number  of
bits in the binary representation of W, and for i = 1, 2, … , k, let wi(u,v)
= ⌊w(u,v)/2k–i
⌋. That is, wi (u, v) is the “scaled-down” version of w(u, v)
given by the i most signiﬁcant bits of w(u, v). (Thus, wk(u, v) = w(u, v)
for all (u, v) ∈ E.) For example, if k = 5 and w(u, v) = 25, which has the
binary representation 〈11001〉, then w3(u, v) = 〈110〉 = 6. Also with k =
5, if w(u, v) = 〈00100〉 = 4, then w4(u, v) = 〈0010〉 = 2. Deﬁne δi(u, v) as
the shortest-path weight from vertex u to vertex v using weight function
wi, so that δk(u, v) = δ(u, v) for all u, v ∈ V. For a given source vertex s,
the  scaling  algorithm  ﬁrst  computes  the  shortest-path  weights  δ1(s,  v)
for all v ∈ V, then computes δ2(s, v) for all v ∈ V, and so on, until it
computes δk(s, v) for all v ∈ V. Assume throughout that |E| ≥ |V| − 1.
You  will  show  how  to  compute  δi  from  δi−1  in  O(E)  time,  so  that  the
entire algorithm takes O(kE) = O(E lg W) time.

a. Suppose that for all vertices v ∈ V, we have δ(s, v) ≤ |E|. Show how to

compute δ(s, v) for all v ∈ V in O(E) time.

b. Show how to compute δ1(s, v) for all v ∈ V in O(E) time.

Now focus on computing δi from δi−1.

c. Prove that for i = 2, 3, … , k, either wi(u, v) = 2wi−1(u, v) or wi(u, v) =

2wi−1(u, v) + 1. Then prove that

2δi−1(s, v) ≤ δi(s, v) ≤ 2δi−1(s, v) + |V| − 1

for all v ∈ V.

d. Deﬁne, for i = 2, 3, … , k and all (u, v) ∈ E,

ŵi(u, v) = wi(u, v) + 2δi−1(s, u) − 2δi−1(s, v).

Prove that for i = 2, 3, … , k and all u, v ∈ V, the “reweighted” value
ŵi(u, v) of edge (u, v) is a nonnegative integer.

e. Now deﬁne

 as the shortest-path weight from s to v using the

weight function ŵi. Prove that for i = 2, 3, … , k and all v ∈ V,

and that

.

f. Show how to compute δi(s, v) from δi−1(s, v) for all v ∈ V in O(E)
time. Conclude that you can compute δ(s, v) for all v ∈ V in O(E lg
W) time.

22-5     Karp’s minimum mean-weight cycle algorithm
Let G = (V, E) be a directed graph with weight function w : E → ℝ, and
let n = |V|. We deﬁne the mean weight of a cycle c = 〈e1, e2, … , ek〉 of
edges in E to be

Let  μ*  =  min  {μ(c)  :  c  is  a  directed  cycle  in  G}.  We  call  a  cycle  c  for
which μ(c) = μ* a minimum mean-weight cycle. This problem investigates
an efﬁcient algorithm for computing μ*.

Assume  without  loss  of  generality  that  every  vertex  v  ∈  V  is
reachable  from  a  source  vertex  s  ∈  V.  Let  δ(s,  v)  be  the  weight  of  a
shortest  path  from  s  to  v,  and  let  δk(s,  v)  be  the  weight  of  a  shortest
path from s to v consisting of exactly k edges. If there is no path from s
to v with exactly k edges, then δk(s, v) = ∞.

a. Show that if μ* = 0, then G contains no negative-weight cycles and

δ(s, v) = min {δk(s, v) : 0 ≤ k ≤ n − 1} for all vertices v ∈ V.

b. Show that if μ* = 0, then

for all vertices v ∈ V. (Hint: Use both properties from part (a).)
c. Let c be a 0-weight cycle, and let u and v be any two vertices on c.

Suppose that μ* = 0 and that the weight of the simple path from u to v
along the cycle is x. Prove that δ(s, v) = δ(s, u) + x. (Hint: The weight
of the simple path from v to u along the cycle is −x.)

d. Show that if μ* = 0, then on each minimum mean-weight cycle there

exists a vertex v such that

(Hint: Show how to extend a shortest path to any vertex on a
minimum mean-weight cycle along the cycle to make a shortest path
to the next vertex on the cycle.)

e. Show that if μ* = 0, then the minimum value of

taken over all vertices v ∈ V, equals 0.

f. Show that if you add a constant t to the weight of each edge of G,

then μ* increases by t. Use this fact to show that μ* equals the
minimum value of

taken over all vertices v ∈ V.

g. Give an O(VE)-time algorithm to compute μ*.

22-6     Bitonic shortest paths

is  bitonic

increases  and  then
A  sequence
monotonically  decreases,  or  if  by  a  circular  shift  it  monotonically
increases and then monotonically decreases. For example the sequences
〈1, 4, 6, 8, 3, −2〉, 〈9, 2, −4, −10, −5〉, and 〈1, 2, 3, 4〉 are bitonic, but 〈1,

it  monotonically

if

3,  12,  4,  2,  10〉  is  not  bitonic.  (See  Problem  14-3  on  page  407  for  the
bitonic euclidean traveling-salesperson problem.)

Suppose that you are given a directed graph G = (V, E) with weight
function w : E → ℝ, where all edge weights are unique, and you wish to
ﬁnd  single-source  shortest  paths  from  a  source  vertex  s.  You  are  given
one additional piece of information: for each vertex v ∈ V, the weights
of  the  edges  along  any  shortest  path  from  s  to  v  form  a  bitonic
sequence.

Give the most efﬁcient algorithm you can to solve this problem, and

analyze its running time.

Chapter notes

The shortest-path problem has a long history that is nicely desribed in
an  article  by  Schrijver  [400].  He  credits  the  general  idea  of  repeatedly
executing  edge  relaxations  to  Ford  [148].  Dijkstra’s  algorithm  [116]
appeared in 1959, but it contained no mention of a priority queue. The
Bellman-Ford  algorithm  is  based  on  separate  algorithms  by  Bellman
[45]  and  Ford  [149].  The  same  algorithm  is  also  attributed  to  Moore
[334].  Bellman  describes  the  relation  of  shortest  paths  to  difference
constraints. Lawler [276] describes the linear-time algorithm for shortest
paths in a dag, which he considers part of the folklore.

When  edge  weights  are  relatively  small  nonnegative  integers,  more
efﬁcient  algorithms  result  from  using  min-priority  queues  that  require
integer  keys  and  rely  on  the  sequence  of  values  returned  by  the
EXTRACT-MIN calls in Dijkstra’s algorithm monotonically increasing
over  time.  Ahuja,  Mehlhorn,  Orlin,  and  Tarjan  [8]  give  an  algorithm
 time on graphs with nonnegative edge weights,
that runs in
where W is the largest weight of any edge in the graph. The best bounds
are by Thorup [436], who gives an algorithm that runs in O(E lg lg V)
time, and by Raman [375], who gives an algorithm that runs in O(E + V
min  {(lg  V)1/3+ε,  (lg  W)1/4+ε})  time.  These  two  algorithms  use  an
amount  of  space  that  depends  on  the  word  size  of  the  underlying
machine. Although the amount of space used can be unbounded in the

size of the input, it can be reduced to be linear in the size of the input
using randomized hashing.

For  undirected  graphs  with  integer  weights,  Thorup  [435]  gives  an
algorithm that runs in O(V + E) time for single-source shortest paths. In
contrast  to  the  algorithms  mentioned  in  the  previous  paragraph,  the
sequence  of  values  returned  by  EXTRACT-MIN  calls  does  not
monotonically  increase  over  time,  and  so  this  algorithm  is  not  an
implementation  of  Dijkstra’s  algorithm.  Pettie  and  Ramachandran
[357]  remove  the  restriction  of  integer  weights  on  undirected  graphs.
Their  algorithm  entails  a  preprocessing  phase,  followed  by  queries  for
speciﬁc source vertices. Preprocessing takes O(MST(V, E) + min {V lg
V, V lg lg r}) time, where MST(V, E) is the time to compute a minimum
spanning  tree  and  r  is  the  ratio  of  the  maximum  edge  weight  to  the
takes
minimum  edge  weight.  After  preprocessing,  each  query
  is  the  inverse  of  Ackermann’s  function.
(See  the  chapter  notes  for  Chapter  19  for  a  brief  discussion  of
Ackermann’s function and its inverse.)

  time,  where

For graphs with negative edge weights, an algorithm due to Gabow
 time, and one by Goldberg [186]
and Tarjan [167] runs in
 time, where W = max {|w(u, v)| : (u, v) ∈ E}. There
runs in
has  also  been  some  progress  based  on  methods  that  use  continuous
optimization  and  electrical  ﬂows.  Cohen  et  al.  [98]  give  such  an
algorithm,  which  is  randomized  and  runs  in  Õ(E10/7  lg  W)  expected
time  (see  Problem  3-6  on  page  73  for  the  deﬁntion  of  Õ-notation).
There  is  also  a  pseudopolyomial-time  algorithm  based  on  fast  matrix
multiplication. Sankowski [394] and Yuster and Zwick [465] designed an
algorithm for shortest paths that runs in Õ(W Vω) time, where two n ×
n  matrices  can  be  multiplied  in  O(nω)  time,  giving  a  faster  algorithm
than  the  previously  mentioned  algorithms  for  small  values  of  W  on
dense graphs.

Cherkassky,  Goldberg,  and  Radzik

[89]  conducted  extensive
experiments comparing various shortest-path algorithms. Shortest-path
algorithms  are  widely  used  in  real-time  navigation  and  route-planning
applications.  Typically  based  on  Dijkstra’s  algorithm,  these  algorithms

use many clever ideas to be able to compute shortest paths on networks
with many millions of vertices and edges in fractions of a second. Bast
et al. [36] survey many of these developments.

1 It may seem strange that the term “relaxation” is used for an operation that tightens an upper
bound. The use of the term is historical. The outcome of a relaxation step can be viewed as a
relaxation of the constraint v.d ≤ u.d + w(u, v), which, by the triangle inequality (Lemma 22.10
on page 633), must be satisﬁed if u.d = δ(s, u) and v.d = δ(s, v). That is, if v.d ≤ u.d + w(u, v),
there is no “pressure” to satisfy this constraint, so the constraint is “relaxed.”
2 “PERT” is an acronym for “program evaluation and review technique.”

