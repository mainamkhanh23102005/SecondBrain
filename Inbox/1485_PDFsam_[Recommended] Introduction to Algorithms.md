B.4-4
Verify that in an undirected graph, the “is reachable from” relation is an
equivalence  relation  on  the  vertices  of  the  graph.  Which  of  the  three
properties  of  an  equivalence  relation  hold  in  general  for  the  “is
reachable from” relation on the vertices of a directed graph?

B.4-5
What  is  the  undirected  version  of  the  directed  graph  in  Figure  B.2(a)?
What is the directed version of the undirected graph in Figure B.2(b)?

B.4-6
Show  how  a  bipartite  graph  can  represent  a  hypergraph  by  letting
incidence  in  the  hypergraph  correspond  to  adjacency  in  the  bipartite
graph. (Hint: Let one set of vertices in the bipartite graph correspond to
vertices  of  the  hypergraph,  and  let  the  other  set  of  vertices  of  the
bipartite graph correspond to hyperedges.)

B.5 Trees

As with graphs, there are many related, but slightly different, notions of
trees.  This  section  presents  deﬁnitions  and  mathematical  properties  of
several kinds of trees. Sections 10.3 and 20.1 describe how to represent
trees in computer memory.

B.5.1 Free trees
As deﬁned in Section B.4, a free tree is a connected, acyclic, undirected
graph. We often omit the adjective “free” when we say that a graph is a
tree. If an undirected graph is acyclic but possibly disconnected, it is a
forest. Many algorithms that work for trees also work for forests. Figure
B.4(a) shows a free tree, and Figure B.4(b) shows a forest. The forest in
Figure  B.4(b)  is  not  a  tree  because  it  is  not  connected.  The  graph  in
Figure  B.4(c)  is  connected  but  neither  a  tree  nor  a  forest,  because  it
contains a cycle.

The  following  theorem  captures  many  important  facts  about  free

trees.

Theorem B.2 (Properties of free trees)

Figure B.4 (a) A free tree. (b) A forest. (c) A graph that contains a cycle and is therefore neither a
tree nor a forest.

Let  G  =  (V,  E)  be  an  undirected  graph.  The  following  statements  are
equivalent.

1. G is a free tree.

2. Any two vertices in G are connected by a unique simple path.

3. G is connected, but if any edge is removed from E, the resulting

graph is disconnected.

4. G is connected, and |E| = |V | − 1.

5. G is acyclic, and |E| = |V | − 1.

6. G  is  acyclic,  but  if  any  edge  is  added  to  E,  the  resulting  graph

contains a cycle.

Figure B.5 A step in the proof of Theorem B.2: if (1) G is a free tree, then (2) any two vertices in
G are connected by a unique simple path. Assume for the sake of contradiction that vertices u
and v are connected by two distinct simple paths. These paths ﬁrst diverge at vertex w, and they
ﬁrst  reconverge  at  vertex  z.  The  path  p′  concatenated  with  the  reverse  of  the  path  p″  forms  a
cycle, which yields the contradiction.

Proof      (1)  ⇒  (2):  Since  a  tree  is  connected,  any  two  vertices  in  G  are
connected  by  at  least  one  simple  path.  Suppose  for  the  sake  of
contradiction that vertices u and v are connected by two distinct simple
paths as shown in Figure B.5. Let w be the vertex at which the paths ﬁrst
diverge. That is, if we call the paths p1 and p2, then w is the ﬁrst vertex
on both p1 and p2 whose successor on p1 is x and whose successor on
p2  is  y,  where  x  ≠  y.  Let  z  be  the  ﬁrst  vertex  at  which  the  paths
reconverge, that is, z is the ﬁrst vertex following w on p1 that is also on
p2. Let p′ = w → x ⇝ z be the subpath of p1 from w through x to z, so
,  and  let  p″  =  w  →  y  ⇝  z  be  the  subpath  of  p2
that
from w through y to z, so that
. Paths p′ and p″ share no
vertices  except  their  endpoints.  Then,  as  Figure  B.5  shows,  the  path
obtained  by  concatenating  p′  and  the  reverse  of  p″  is  a  cycle,  which
contradicts  our  assumption  that  G  is  a  tree.  Thus,  if  G  is  a  tree,  there
can be at most one simple path between two vertices.

(2) ⇒ (3): If any two vertices in G are connected by a unique simple
path,  then  G  is  connected.  Let  (u,  v)  be  any  edge  in  E.  This  edge  is  a
path from u to v, and so it must be the unique path from u to v. If (u, v)
were to be removed from G, there would be no path from u to v, and G
would be disconnected.

(3) ⇒ (4): By assumption, the graph G is connected, so Exercise B.4-3
gives that |E| ≥ |V| − 1. We prove |E| ≤ |V| − 1 by induction on |V|. The
base cases are when |V| = 1 or |V| = 2, and in either case, |E| = |V| − 1.
For  the  inductive  step,  suppose  that  |V|  ≥  3  for  graph  G  and  that  any
graph G′ = (V′, E′), where |V′| < |V|, that satisﬁes (3) also satisﬁes |E′| ≤
|V′| − 1. Removing an arbitrary edge from G separates the graph into k
≥  2  connected  components  (actually  k  =  2).  Each  component  satisﬁes
(3), or else G would not satisfy (3). Consider each connected component
Vi,  with  edge  set  Ei,  as  a  separate  free  tree.  Then,  because  each
|V|  vertices,  the  inductive
connected  component  has  fewer  than
hypothesis implies that |Ei| ≤ |Vi| − 1. Thus, the number of edges in all k
connected components combined is at most |V| − k ≤ |V| − 2. Adding in
the removed edge yields |E| ≤ |V| − 1.

(4)  ⇒  (5):  Suppose  that  G  is  connected  and  that  |E|  =  |V|  −  1.  We
must  show  that  G  is  acyclic.  Suppose  that  G  has  a  cycle  containing  k
vertices v1, v2, … , vk, and without loss of generality assume that this
cycle  is  simple.  Let  Gk  =  (Vk,  Ek)  be  the  subgraph  of  G  consisting  of
the cycle, so that |Vk| = |Ek| = k. If k < |V|, then because G is connected,
there must be a vertex vk+1∈ V − Vk that is adjacent to some vertex vi
∈  Vk.  Deﬁne  Gk+1  =  (Vk+1,  Ek+1)  to  be  the  subgraph  of  G  with
Vk+1 = Vk ∪ {vk+1} and Ek+1 = Ek ∪ {(vi, vk+1)}. Note that |Vk+1|
=  |Ek+1|  =  k  +  1.  If  k  +  1  <  |V|,  then  continue,  deﬁning  Gk+2  in  the
same  manner,  and  so  forth,  until  we  obtain  Gn  =  (Vn,  En),  where  n  =
|V|, Vn = V, and |En| = |Vn| = |V|. Since Gn is a subgraph of G, we have
En  ⊆  E,  and  hence  |E|  ≥  |En|  =  |Vn|  =  |V|,  which  contradicts  the
assumption that |E| = |V| − 1. Thus, G is acyclic.

(5) ⇒ (6): Suppose that G is acyclic and that |E| = |V| − 1. Let k be
the number of connected components of G. Each connected component
is a free tree by deﬁnition, and since (1) implies (5), the sum of all edges
in all connected components of G is |V| − k. Consequently, k must equal
1, and G is in fact a tree. Since (1) implies (2), any two vertices in G are
connected by a unique simple path. Thus, adding any edge to G creates
a cycle.

(6)  ⇒  (1):  Suppose  that  G  is  acyclic  but  that  adding  any  edge  to  E
creates  a  cycle.  We  must  show  that  G  is  connected.  Let  u  and  v  be
arbitrary vertices in G. If u and v are not already adjacent, adding the
edge (u, v) creates a cycle in which all edges but (u, v) belong to G. Thus,
the cycle minus edge (u, v) must contain a path from u to v, and since u
and v were chosen arbitrarily, G is connected.

▪

B.5.2 Rooted and ordered trees

A rooted tree is a free tree in which one of the vertices is distinguished
from the others. We call the distinguished vertex the root of the tree. We
often  refer  to  a  vertex  of  a  rooted  tree  as  a  node5  of  the  tree.  Figure
B.6(a) shows a rooted tree on a set of 12 nodes with root 7.

Figure  B.6  Rooted  and  ordered  trees.  (a)  A  rooted  tree  with  height  4.  The  tree  is  drawn  in  a
standard  way:  the  root  (node  7)  is  at  the  top,  its  children  (nodes  with  depth  1)  are  beneath  it,
their  children  (nodes  with  depth  2)  are  beneath  them,  and  so  forth.  If  the  tree  is  ordered,  the
relative left-to-right order of the children of a node matters; otherwise, it doesn’t. (b) Another
rooted tree. As a rooted tree, it is identical to the tree in (a), but as an ordered tree it is different,
since the children of node 3 appear in a different order.

Consider a node x in a rooted tree T with root r. We call any node y
on  the  unique  simple  path  from  r  to  x  an  ancestor  of  x.  If  y  is  an
ancestor  of  x,  then  x  is  a  descendant  of  y.  (Every  node  is  both  an
ancestor and a descendant of itself.) If y is an ancestor of x and x ≠ y,
then y is a proper ancestor of x and x is a proper descendant of y. The
subtree rooted at x is the tree induced by descendants of x, rooted at x.
For  example,  the  subtree  rooted  at  node  8  in  Figure  B.6(a)  contains
nodes 8, 6, 5, and 9.

If the last edge on the simple path from the root r of a tree T to a
node x is (y, x), then y is the parent of x, and x is a child of y. The root
is the only node in T with no parent. If two nodes have the same parent,
they are siblings. A node with no children is a leaf or external node. A
nonleaf node is an internal node.

The number of children of a node x in a rooted tree T is the degree
of x.6 The length of the simple path from the root r to a node x is the
depth of x in T. A level of a tree consists of all nodes at the same depth.
The  height  of  a  node  in  a  tree  is  the  number  of  edges  on  the  longest
simple downward path from the node to a leaf, and the height of a tree
is the height of its root. The height of a tree is also equal to the largest
depth of any node in the tree.

An  ordered  tree  is  a  rooted  tree  in  which  the  children  of  each  node
are ordered. That is, if a node has k children, then there is a ﬁrst child, a
second child, and so on, up to and including a kth child. The two trees
in Figure B.6 are different when considered to be ordered trees, but the
same when considered to be just rooted trees.

B.5.3 Binary and positional trees

We deﬁne binary trees recursively. A binary tree T is a structure deﬁned
on a ﬁnite set of nodes that either

contains no nodes, or

is composed of three disjoint sets of nodes: a root node, a binary
tree called its left subtree, and a binary tree called its right subtree.

The  binary  tree  that  contains  no  nodes  is  called  the  empty  tree  or  null
tree, sometimes denoted NIL. If the left subtree is nonempty, its root is
called the left child of the root of the entire tree. Likewise, the root of a
nonnull right subtree is the right child of the root of the entire tree. If a
subtree  is  the  null  tree  NIL,  we  say  that  the  child  is  absent  or  missing.
Figure B.7(a) shows a binary tree.

A binary tree is not simply an ordered tree in which each node has
degree at most 2. For example, in a binary tree, if a node has just one
child, the position of the child—whether it is the left child or the right
child—matters. In an ordered tree, there is no distinguishing a sole child
as  being  either  left  or  right.  Figure  B.7(b)  shows  a  binary  tree  that
differs  from  the  tree  in  Figure  B.7(a)  because  of  the  position  of  one
node. Considered as ordered trees, however, the two trees are identical.

One way to represent the positioning information in a binary tree is
by the internal nodes of an ordered tree, as shown in Figure B.7(c). The
idea  is  to  replace  each  missing  child  in  the  binary  tree  with  a  node
having no children. These leaf nodes are drawn as squares in the ﬁgure.
The tree that results is a full binary tree: each node is either a leaf or has
degree  exactly  2.  No  nodes  have  degree  1.  Consequently,  the  order  of
the children of a node preserves the position information.

Figure B.7 Binary trees. (a) A binary tree drawn in a standard way. The left child of a node is
drawn beneath the node and to the left. The right child is drawn beneath and to the right. (b) A
binary tree different from the one in (a). In (a), the left child of node 7 is 5 and the right child is
absent. In (b), the left child of node 7 is absent and the right child is 5. As ordered trees, these
trees are the same, but as binary trees, they are distinct. (c) The binary tree in (a) represented by
the internal nodes of a full binary tree: an ordered tree in which each internal node has degree 2.
The leaves in the tree are shown as squares.

The  positioning  information  that  distinguishes  binary  trees  from
ordered trees extends to trees with more than two children per node. In
a positional tree, the children of a node are labeled with distinct positive
integers.  The  ith  child  of  a  node  is  absent  if  no  child  is  labeled  with
integer  i.  A  k-ary  tree  is  a  positional  tree  in  which  for  every  node,  all
children with labels greater than k are missing. Thus, a binary tree is a
k-ary tree with k = 2.

A complete k-ary tree is a k-ary tree in which all leaves have the same
depth and all internal nodes have degree k. Figure B.8 shows a complete
binary tree of height 3. How many leaves does a complete k-ary tree of
height h have? The root has k children at depth 1, each of which has k
children at depth 2, etc. Thus, the number of nodes at depth d is kd. In a
complete k-ary tree with height h, the leaves are at depth h, so that there
are kh leaves. Consequently, the height of a complete k-ary tree with n
leaves is logkn. A complete k-ary tree of height h has

internal nodes. Thus, a complete binary tree has 2h − 1 internal nodes.

Figure B.8 A complete binary tree of height 3 with 8 leaves and 7 internal nodes.

Exercises

B.5-1
Draw all the free trees composed of the three vertices x, y, and z. Draw
all the rooted trees with nodes x, y, and z with x as the root. Draw all
the ordered trees with nodes x, y, and z with x as the root. Draw all the
binary trees with nodes x, y, and z with x as the root.

B.5-2
Let G = (V, E) be a directed acyclic graph in which there is a vertex v0
∈ V such that there exists a unique path from v0 to every vertex v ∈ V.
Prove that the undirected version of G forms a tree.

B.5-3
Show by induction that the number of degree-2 nodes in any nonempty
binary  tree  is  one  less  than  the  number  of  leaves.  Conclude  that  the
number  of  internal  nodes  in  a  full  binary  tree  is  one  less  than  the
number of leaves.

B.5-4
Prove that for any integer k ≥ 1, there is a full binary tree with k leaves.

B.5-5
Use  induction  to  show  that  a  nonempty  binary  tree  with  n  nodes  has
height at least ⌊lg n⌋.

★ B.5-6
The internal path length of a full binary tree is the sum, taken over all
internal  nodes  of  the  tree,  of  the  depth  of  each  node.  Likewise,  the
external path length is the sum, taken over all leaves of the tree, of the
depth  of  each  leaf.  Consider  a  full  binary  tree  with  n  internal  nodes,
internal path length i, and external path length e. Prove that e = i + 2n.

★ B.5-7
Associate a “weight” w(x) = 2−d with each leaf x of depth d in a binary
tree  T,  and  let  L  be  the  set  of  leaves  of  T.  Prove  the  Kraft  inequality:
Σx∈L w(x) ≤ 1.

★ B.5-8
Show  that  if  L  ≥  2,  then  every  binary  tree  with  L  leaves  contains  a
subtree having between L/3 and 2L/3 leaves, inclusive.

Problems

B-1 Graph coloring
A k-coloring of undirected graph G = (V, E) is a function c : V → {1, 2,
… , k} such that c(u) ≠ c(v) for every edge (u, v) ∈ E. In other words, the
numbers  1,  2,  …  ,  k  represent  the  k  colors,  and  adjacent  vertices  must
have different colors.

a. Show that any tree is 2-colorable.

b. Show that the following are equivalent:

1. G is bipartite.

2. G is 2-colorable.

3. G has no cycles of odd length.

c. Let d be the maximum degree of any vertex in a graph G. Prove that

G can be colored with d + 1 colors.

d. Show that if G has O(|V|) edges, then G can be colored with

colors.

B-2 Friendly graphs

Reword each of the following statements as a theorem about undirected
graphs, and then prove it. Assume that friendship is symmetric but not
reﬂexive.

a. Any group of at least two people contains at least two people with the

same number of friends in the group.

b. Every group of six people contains either at least three mutual friends

or at least three mutual strangers.

c. Any group of people can be partitioned into two subgroups such that

at least half the friends of each person belong to the subgroup of
which that person is not a member.

d. If everyone in a group is the friend of at least half the people in the

group, then the group can be seated around a table in such a way that
everyone is seated between two friends.

B-3 Bisecting trees
Many  divide-and-conquer  algorithms  that  operate  on  graphs  require
that the graph be bisected into two nearly equal-sized subgraphs, which
are  induced  by  a  partition  of  the  vertices.  This  problem  investigates
bisections  of  trees  formed  by  removing  a  small  number  of  edges.  We
require  that  whenever  two  vertices  end  up  in  the  same  subtree  after
removing edges, then they must belong to the same partition.

a. Show that the vertices of any n-vertex binary tree can be partitioned
into two sets A and B, such that |A| ≤ 3n/4 and |B| ≤ 3n/4, by removing
a single edge.

b. Show that the constant 3/4 in part (a) is optimal in the worst case by

giving an example of a simple binary tree whose most evenly balanced
partition upon removal of a single edge has |A| = 3n/4.

c. Show that by removing at most O(lg n) edges, we can partition the

vertices of any n-vertex binary tree into two sets A and B such that |A|
= ⌊n/2⌋ and |B| = ⌈n/2⌉.

Appendix notes

G.  Boole  pioneered  the  development  of  symbolic  logic,  and  he
introduced many of the basic set notations in a book published in 1854.
Modern  set  theory  was  created  by  G.  Cantor  during  the  period  1874–
1895. Cantor focused primarily on sets of inﬁnite cardinality. The term
“function” is attributed to G. W. Leibniz, who used it to refer to several
kinds  of  mathematical  formulas.  His  limited  deﬁnition  has  been
generalized  many  times.  Graph  theory  originated  in  1736,  when  L.
Euler proved that it was impossible to cross each of the seven bridges in
the city of Königsberg exactly once and return to the starting point.

The  book  by  Harary  [208]  provides  a  useful  compendium  of  many

deﬁnitions and results from graph theory.

1 A variation of a set, which can contain the same object more than once, is called a multiset.
2 Some authors start the natural numbers with 1 instead of 0. The modern trend seems to be to
start with 0.
3 To be precise, in order for the “ﬁt inside” relation to be a partial order, we need to view a box
as ﬁtting inside itself.
4 Some authors refer to what we call a path as a “walk” and to what we call a simple path as just
a “path.”
5  The  term  “node”  is  often  used  in  the  graph  theory  literature  as  a  synonym  for  “vertex.”  We
reserve the term “node” to mean a vertex of a rooted tree.
6 The degree of a node depends on whether we consider T to be a rooted tree or a free tree. The
degree of a vertex in a free tree is, as in any undirected graph, the number of adjacent vertices.
In a rooted tree, however, the degree is the number of children—the parent of a node does not
count toward its degree.

