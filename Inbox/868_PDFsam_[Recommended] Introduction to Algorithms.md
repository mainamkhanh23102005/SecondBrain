24        Maximum Flow

Just as you can model a road map as a directed graph in order to ﬁnd
the  shortest  path  from  one  point  to  another,  you  can  also  interpret  a
directed graph as a “ﬂow network” and use it to answer questions about
material  ﬂows.  Imagine  a  material  coursing  through  a  system  from  a
source, where the material is produced, to a sink, where it is consumed.
The  source  produces  the  material  at  some  steady  rate,  and  the  sink
consumes  the  material  at  the  same  rate.  The  “ﬂow”  of  the  material  at
any  point  in  the  system  is  intuitively  the  rate  at  which  the  material
moves.  Flow  networks  can  model  many  problems,  including  liquids
ﬂowing  through  pipes,  parts  through  assembly  lines,  current  through
electrical networks, and information through communication networks.
You can think of each directed edge in a ﬂow network as a conduit
for  the  material.  Each  conduit  has  a  stated  capacity,  given  as  a
maximum rate at which the material can ﬂow through the conduit, such
as  200  gallons  of  liquid  per  hour  through  a  pipe  or  20  amperes  of
electrical  current  through  a  wire.  Vertices  are  conduit  junctions,  and
other  than  the  source  and  sink,  material  ﬂows  through  the  vertices
without  collecting  in  them.  In  other  words,  the  rate  at  which  material
enters a vertex must equal the rate at which it leaves the vertex. We call
this  property  “ﬂow  conservation,”  and  it  is  equivalent  to  Kirchhoff’s
current law when the material is electrical current.

The  goal  of  the  maximum-ﬂow  problem  is  to  compute  the  greatest
rate for shipping material from the source to the sink without violating
any capacity constraints. It is one of the simplest problems concerning
ﬂow networks and, as we shall see in this chapter, this problem can be

solved  by  efﬁcient  algorithms.  Moreover,  other  network-ﬂow  problems
are  solvable  by  adapting  the  basic  techniques  used  in  maximum-ﬂow
algorithms.

This  chapter  presents  two  general  methods  for  solving  the
maximum-ﬂow  problem.  Section  24.1  formalizes  the  notions  of  ﬂow
networks  and  ﬂows,  formally  deﬁning  the  maximum-ﬂow  problem.
Section  24.2  describes  the  classical  method  of  Ford  and  Fulkerson  for
ﬁnding maximum ﬂows. We ﬁnish up with a simple application of this
method, ﬁnding a maximum matching in an undirected bipartite graph,
in Section 24.3. (Section 25.1 will give a more efﬁcient algorithm that is
speciﬁcally designed to ﬁnd a maximum matching in a bipartite graph.)

24.1    Flow networks

This  section  gives  a  graph-theoretic  deﬁnition  of  ﬂow  networks,
discusses  their  properties,  and  deﬁnes  the  maximum-ﬂow  problem
precisely. It also introduces some helpful notation.

Flow networks and ﬂows

A ﬂow network G = (V, E) is a directed graph in which each edge (u, v)
∈ E has a nonnegative capacity c(u, v) ≥ 0. We further require that if E
contains  an  edge  (u,  v),  then  there  is  no  edge  (v,  u)  in  the  reverse
direction. (We’ll see shortly how to work around this restriction.) If (u,
v) ∉ E, then for convenience we deﬁne c(u, v) = 0, and we disallow self-
loops. Each ﬂow network contains two distinguished vertices: a source s
and a sink t. For convenience, we assume that each vertex lies on some
path from the source to the sink. That is, for each vertex v ∈ V, the ﬂow
network contains a path s ⇝ v ⇝ t. Because each vertex other than s has
at least one entering edge, we have |E| ≥ |V | − 1. Figure 24.1 shows an
example of a ﬂow network.

Figure  24.1  (a)  A  ﬂow  network  G  =  (V,  E)  for  the  Lucky  Puck  Company’s  trucking  problem.
The Vancouver factory is the source s, and the Winnipeg warehouse is the sink t. The company
ships pucks through intermediate cities, but only c(u, v) crates per day can go from city u to city
v. Each edge is labeled with its capacity. (b) A ﬂow f in G with value |f | = 19. Each edge (u, v) is
labeled by f (u, v)/c(u, v). The slash notation merely separates the ﬂow and capacity and does not
indicate division.

We are now ready to deﬁne ﬂows more formally. Let G = (V, E) be a
ﬂow  network  with  a  capacity  function  c.  Let  s  be  the  source  of  the
network, and let t be the sink. A ﬂow in G is a real-valued function f : V
× V → ℝ that satisﬁes the following two properties:
Capacity constraint: For all u, v ∈ V, we require

0 ≤ f(u, v) ≤ c(u, v).

The ﬂow from one vertex to another must be nonnegative and must
not exceed the given capacity.

Flow conservation: For all u ∈ V − {s, t}, we require

The total ﬂow into a vertex other than the source or sink must equal
the  total  ﬂow  out  of  that  vertex—informally,  “ﬂow  in  equals  ﬂow
out.”

When (u, v) ∉ E, there can be no ﬂow from u to v, and f (u, v) = 0.

We  call  the  nonnegative  quantity  f  (u,  v)  the  ﬂow  from  vertex  u  to

vertex v. The value |f | of a ﬂow f is deﬁned as

that is, the total ﬂow out of the source minus the ﬂow into the source.
(Here,  the  |·|  notation  denotes  ﬂow  value,  not  absolute  value  or
cardinality.) Typically, a ﬂow network does not have any edges into the
source, and the ﬂow into the source, given by the summation Σv∈V f(v,
s),  is  0.  We  include  it,  however,  because  when  we  introduce  residual
networks later in this chapter, the ﬂow into the source can be positive. In
the maximum-ﬂow problem, the input is a ﬂow network G with source s
and sink t, and the goal is to ﬁnd a ﬂow of maximum value.

An example of ﬂow

A  ﬂow  network  can  model  the  trucking  problem  shown  in  Figure
24.1(a).  The  Lucky  Puck  Company  has  a  factory  (source  s)  in
Vancouver  that  manufactures  hockey  pucks,  and  it  has  a  warehouse
(sink  t)  in  Winnipeg  that  stocks  them.  Lucky  Puck  leases  space  on
trucks  from  another  ﬁrm  to  ship  the  pucks  from  the  factory  to  the
warehouse.  Because  the  trucks  travel  over  speciﬁed  routes  (edges)
between  cities  (vertices)  and  have  a  limited  capacity,  Lucky  Puck  can
ship at most c(u, v) crates per day between each pair of cities u and v in
Figure  24.1(a).  Lucky  Puck  has  no  control  over  these  routes  and
capacities, and so the company cannot alter the ﬂow network shown in
Figure  24.1(a).  They  need  to  determine  the  largest  number  p  of  crates
per day that they can ship and then to produce this amount, since there
is  no  point  in  producing  more  pucks  than  they  can  ship  to  their
warehouse.  Lucky  Puck  is  not  concerned  with  how  long  it  takes  for  a
given puck to get from the factory to the warehouse. They care only that
p  crates  per  day  leave  the  factory  and  p  crates  per  day  arrive  at  the
warehouse.

Figure  24.2  Converting  a  network  with  antiparallel  edges  to  an  equivalent  one  with  no
antiparallel  edges.  (a)  A  ﬂow  network  containing  both  the  edges  (v1,  v2)  and  (v2,  v1).  (b)  An
equivalent network with no antiparallel edges. A new vertex v′ was added, and edge (v1, v2) was
replaced by the pair of edges (v1, v′) and (v′, v2), both with the same capacity as (v1, v2).

A  ﬂow  in  this  network  models  the  “ﬂow”  of  shipments  because  the
number of crates shipped per day from one city to another is subject to
a  capacity  constraint.  Additionally,  the  model  must  obey  ﬂow
conservation,  for  in  a  steady  state,  the  rate  at  which  pucks  enter  an
intermediate  city  must  equal  the  rate  at  which  they  leave.  Otherwise,
crates would accumulate at intermediate cities.

Modeling problems with antiparallel edges

Suppose  that  the  trucking  ﬁrm  offers  Lucky  Puck  the  opportunity  to
lease space for 10 crates in trucks going from Edmonton to Calgary. It
might  seem  natural  to  add  this  opportunity  to  our  example  and  form
the  network  shown  in  Figure  24.2(a).  This  network  suffers  from  one
problem,  however:  it  violates  the  original  assumption  that  if  edge  (v1,
v2) ∈ E, then (v2, v1) ∉ E. We call the two edges (v1, v2) and (v2, v1)
antiparallel. Thus, to model a ﬂow problem with antiparallel edges, the
network  must  be  transformed  into  an  equivalent  one  containing  no
antiparallel  edges.  Figure  24.2(b)  displays  this  equivalent  network.  To
transform the network, choose one of the two antiparallel edges, in this
case (v1, v2), and split it by adding a new vertex v′ and replacing edge
(v1, v2) with the pair of edges (v1, v′) and (v′, v2). Also set the capacity
of  both  new  edges  to  the  capacity  of  the  original  edge.  The  resulting
network  satisﬁes  the  property  that  if  an  edge  belongs  to  the  network,

the  reverse  edge  does  not.  As  Exercise  24.1-1  asks  you  to  prove,  the
resulting network is equivalent to the original one.

Figure 24.3 Converting a multiple-source, multiple-sink maximum-ﬂow problem into a problem
with a single source and a single sink. (a) A ﬂow network with three sources S = {s1, s2, s3} and
two  sinks  T  =  {t1,  t2}.  (b)  An  equivalent  single-source,  single-sink  ﬂow  network.  Add  a
supersource s and an edge with inﬁnite capacity from s to each of the multiple sources. Also add
a supersink t and an edge with inﬁnite capacity from each of the multiple sinks to t.

Networks with multiple sources and sinks

A  maximum-ﬂow  problem  may  have  several  sources  and  sinks,  rather
than  just  one  of  each.  The  Lucky  Puck  Company,  for  example,  might
actually  have  a  set  of  m  factories  {s1,  s2,  …,  sm}  and  a  set  of  n
warehouses {t1, t2, …, tn}, as shown in Figure 24.3(a). Fortunately, this
problem is no harder than ordinary maximum ﬂow.

The  problem  of  determining  a  maximum  ﬂow  in  a  network  with
multiple  sources  and  multiple  sinks  reduces  to  an  ordinary  maximum-
ﬂow problem. Figure 24.3(b) shows how to convert the network from (a)
to an ordinary ﬂow network with only a single source and a single sink.
Add a supersource s and add a directed edge (s, si) with capacity c(s, si)
= ∞ for each i = 1, 2, …, m. Similarly, create a new supersink t and add a
directed  edge  (ti,  t)  with  capacity  c(ti,  t)  =  ∞  for  each  i  =  1,  2,  …,  n.
Intuitively,  any  ﬂow  in  the  network  in  (a)  corresponds  to  a  ﬂow  in  the
network  in  (b),  and  vice  versa.  The  single  supersource  s  provides  as
much ﬂow as desired for the multiple sources si, and the single supersink

t  likewise  consumes  as  much  ﬂow  as  desired  for  the  multiple  sinks  ti.
Exercise  24.1-2  asks  you  to  prove  formally  that  the  two  problems  are
equivalent.

Exercises

24.1-1
Show  that  splitting  an  edge  in  a  ﬂow  network  yields  an  equivalent
network. More formally, suppose that ﬂow network G contains edge (u,
v),  and  deﬁne  a  new  ﬂow  network  G′  by  creating  a  new  vertex  x  and
replacing (u, v) by new edges (u, x) and (x, v) with c(u, x) = c(x, v) = c(u,
v). Show that a maximum ﬂow in G′ has the same value as a maximum
ﬂow in G.

24.1-2
Extend  the  ﬂow  properties  and  deﬁnitions  to  the  multiple-source,
multiple-sink  problem.  Show  that  any  ﬂow  in  a  multiple-source,
multiple-sink  ﬂow  network  corresponds  to  a  ﬂow  of  identical  value  in
the single-source, single-sink network obtained by adding a supersource
and a supersink, and vice versa.

24.1-3
Suppose that a ﬂow network G = (V, E) violates the assumption that the
network  contains  a  path  s  ⇝  v  ⇝  t  for  all  vertices  v  ∈  V.  Let  u  be  a
vertex for which there is no path s ⇝ u ⇝ t. Show that there must exist a
maximum ﬂow f in G such that f (u, v) = f (v, u) = 0 for all vertices v ∈
V.

24.1-4
Let f be a ﬂow in a network, and let α be a real number. The scalar ﬂow
product, denoted αf, is a function from V × V to ℝ deﬁned by
(αf)(u, v) = α · f (u, v).
Prove that the ﬂows in a network form a convex set. That is, show that if
f1 and f2 are ﬂows, then so is αf1 + (1 − α) f2 for all α in the range 0 ≤ α
≤ 1.

24.1-5
State the maximum-ﬂow problem as a linear-programming problem.

24.1-6
Professor Adam has two children who, unfortunately, dislike each other.
The problem is so severe that not only do they refuse to walk to school
together,  but  in  fact  each  one  refuses  to  walk  on  any  block  that  the
other child has stepped on that day. The children have no problem with
their paths crossing at a corner. Fortunately both the professor’s house
and  the  school  are  on  corners,  but  beyond  that  he  is  not  sure  if  it  is
going  to  be  possible  to  send  both  of  his  children  to  the  same  school.
The  professor  has  a  map  of  his  town.  Show  how  to  formulate  the
problem  of  determining  whether  both  his  children  can  go  to  the  same
school as a maximum-ﬂow problem.

24.1-7
Suppose that, in addition to edge capacities, a ﬂow network has vertex
capacities. That is each vertex v has a limit l(v) on how much ﬂow can
pass through v. Show how to transform a ﬂow network G = (V, E) with
vertex capacities into an equivalent ﬂow network G′ = (V′, E′) without
vertex capacities, such that a maximum ﬂow in G′ has the same value as
a maximum ﬂow in G. How many vertices and edges does G′ have?

24.2    The Ford-Fulkerson method

This  section  presents  the  Ford-Fulkerson  method  for  solving  the
maximum-ﬂow  problem.  We  call  it  a  “method”  rather  than  an
“algorithm”  because  it  encompasses  several  implementations  with
differing running times. The Ford-Fulkerson method depends on three
important  ideas  that  transcend  the  method  and  are  relevant  to  many
ﬂow  algorithms  and  problems:  residual  networks,  augmenting  paths,
and  cuts.  These  ideas  are  essential  to  the  important  max-ﬂow  min-cut
theorem (Theorem 24.6), which characterizes the value of a maximum
ﬂow  in  terms  of  cuts  of  the  ﬂow  network.  We  end  this  section  by
presenting  one  speciﬁc  implementation  of  the  Ford-Fulkerson  method
and analyzing its running time.

The  Ford-Fulkerson  method  iteratively  increases  the  value  of  the
ﬂow. It starts with f (u, v) = 0 for all u, v ∈ V, giving an initial ﬂow of
value  0.  Each  iteration  increases  the  ﬂow  value  in  G  by  ﬁnding  an
“augmenting  path”  in  an  associated  “residual  network”  Gf.  The  edges
of the augmenting path in Gf indicate on which edges in G to update the
ﬂow in order to increase the ﬂow value. Although each iteration of the
Ford-Fulkerson method increases the value of the ﬂow, we’ll see that the
ﬂow on any particular edge of G may increase or decrease. Although it
might  seem  counterintuitive  to  decrease  the  ﬂow  on  an  edge,  doing  so
may enable ﬂow to increase on other edges, allowing more ﬂow to travel
from  the  source  to  the  sink.  The  Ford-Fulkerson  method,  given  in  the
procedure FORD-FULKERSON-METHOD, repeatedly augments the
ﬂow  until  the  residual  network  has  no  more  augmenting  paths.  The
max-ﬂow  min-cut  theorem  shows  that  upon  termination,  this  process
yields a maximum ﬂow.

FORD-FULKERSON-METHOD (G, s, t)
1 initialize ﬂow f to 0
2 while there exists an augmenting path p in the residual network Gf
3
4 return f

augment ﬂow f along p

In order to implement and analyze the Ford-Fulkerson method, we

need to introduce several additional concepts.

Residual networks

Intuitively, given a ﬂow network G and a ﬂow f, the residual network Gf
consists of edges whose capacities represent how the ﬂow can change on
edges  of  G.  An  edge  of  the  ﬂow  network  can  admit  an  amount  of
additional ﬂow equal to the edge’s capacity minus the ﬂow on that edge.
If  that  value  is  positive,  that  edge  goes  into  Gf  with  a  “residual
capacity” of cf (u, v) = c(u, v) − f (u, v). The only edges of G that belong

to Gf are those that can admit more ﬂow. Those edges (u, v) whose ﬂow
equals their capacity have cf (u, v) = 0, and they do not belong to Gf.

You might be surprised that the residual network Gf can also contain
edges that are not in G. As an algorithm manipulates the ﬂow, with the
goal of increasing the total ﬂow, it might need to decrease the ﬂow on a
particular  edge  in  order  to  increase  the  ﬂow  elsewhere.  In  order  to
represent a possible decrease in the positive ﬂow f (u, v) on an edge in G,
the residual network Gf contains an edge (v, u) with residual capacity cf
(v,  u)  =  f  (u,  v)—that  is,  an  edge  that  can  admit  ﬂow  in  the  opposite
direction to (u, v), at most canceling out the ﬂow on (u, v). These reverse
edges  in  the  residual  network  allow  an  algorithm  to  send  back  ﬂow  it
has  already  sent  along  an  edge.  Sending  ﬂow  back  along  an  edge  is
equivalent  to  decreasing  the  ﬂow  on  the  edge,  which  is  a  necessary
operation in many algorithms.

More formally, for a ﬂow network G = (V, E) with source s, sink t,
and a ﬂow f, consider a pair of vertices u, v ∈ V. We deﬁne the residual
capacity cf (u, v) by

In a ﬂow network, (u, v) ∈ E implies (v, u) ∉ E, and so exactly one case
in equation (24.2) applies to each ordered pair of vertices.

As  an  example  of  equation  (24.2),  if  c(u,  v)  =  16  and  f  (u,  v)  =  11,
then f (u, v) can increase by up to cf (u, v) = 5 units before exceeding the
capacity constraint on edge (u, v). Alternatively, up to 11 units of ﬂow
can return from v to u, so that cf (v, u) = 11.

Given a ﬂow network G = (V, E) and a ﬂow f, the residual network of

G induced by f is Gf = (V, Ef), where

Figure  24.4  (a)  The  ﬂow  network  G  and  ﬂow  f  of  Figure  24.1(b).  (b)  The  residual  network  Gf
with  augmenting  path  p,  having  residual  capacity  cf  (p)  =  cf  (v2,  v3)  =  4,  in  blue.  Edges  with
residual  capacity  equal  to  0,  such  as  (v1,  v3),  are  not  shown,  a  convention  we  follow  in  the
remainder  of  this  section.  (c)  The  ﬂow  in  G  that  results  from  augmenting  along  path  p  by  its
residual capacity 4. Edges carrying no ﬂow, such as (v3, v2), are labeled only by their capacity,
another convention we follow throughout. (d) The residual network induced by the ﬂow in (c).

That  is,  as  promised  above,  each  edge  of  the  residual  network,  or
residual  edge,  can  admit  a  ﬂow  that  is  greater  than  0.  Figure  24.4(a)
repeats  the  ﬂow  network  G  and  ﬂow  f  of  Figure  24.1(b),  and  Figure
24.4(b)  shows  the  corresponding  residual  network  Gf.  The  edges  in  Ef
are either edges in E or their reversals, and thus

|Ef| ≤ 2 |E|.

Observe  that  the  residual  network  Gf  is  similar  to  a  ﬂow  network
with  capacities  given  by  cf.  It  does  not  satisfy  the  deﬁnition  of  a  ﬂow
network,  however,  because  it  could  contain  antiparallel  edges.  Other
than this difference, a residual network has the same properties as a ﬂow
network,  and  we  can  deﬁne  a  ﬂow  in  the  residual  network  as  one  that
satisﬁes the deﬁnition of a ﬂow, but with respect to capacities cf in the
residual network Gf.

A ﬂow in a residual network provides a roadmap for adding ﬂow to
the  original  ﬂow  network.  If  f  is  a  ﬂow  in  G  and  f′  is  a  ﬂow  in  the

corresponding residual network Gf, we deﬁne f ↑ f′, the augmentation of
ﬂow f by f ′, to be a function from V × V to ℝ, deﬁned by

The  intuition  behind  this  deﬁnition  follows  the  deﬁnition  of  the
residual network. The ﬂow on (u, v) increases by f ′(u, v), but decreases
by  f  ′(v,  u)  because  pushing  ﬂow  on  the  reverse  edge  in  the  residual
network  signiﬁes  decreasing  the  ﬂow  in  the  original  network.  Pushing
ﬂow  on  the  reverse  edge  in  the  residual  network  is  also  known  as
cancellation.  For  example,  suppose  that  5  crates  of  hockey  pucks  go
from  u  to  v  and  2  crates  go  from  v  to  u.  That  is  equivalent  (from  the
perspective of the ﬁnal result) to sending 3 crates from u to v and none
from v to u. Cancellation of this type is crucial for any maximum-ﬂow
algorithm.

The following lemma shows that augmenting a ﬂow in G by a ﬂow in

Gf yields a new ﬂow in G with a greater ﬂow value.

Lemma 24.1
Let G = (V, E) be a ﬂow network with source s and sink t, and let f be a
ﬂow in G. Let Gf be the residual network of G induced by f, and let f ′
be a ﬂow in Gf. Then the function f ↑ f ′ deﬁned in equation (24.4) is a
ﬂow in G with value |f ↑ f ′| = |f | + |f ′|.

Proof   We ﬁrst verify that f ↑ f ′ obeys the capacity constraint for each
edge in E and ﬂow conservation at each vertex in V − {s, t}.

For the capacity constraint, ﬁrst observe that if (u, v) ∈ E, then cf (v,
u) = f (u, v). Because f ′ is a ﬂow in Gf, we have f ′(v, u) ≤ cf (v, u), which
gives f ′(v, u) ≤ f (u, v). Therefore,

(f ↑ f′)(u, v) = f (u, v) + f ′(u, v) − f ′(v, u) (by equation (24.4))

≥ f (u, v) + f ′(u, v) − f (u, v) (because f ′(v, u) ≤ f (u, v))
= f ′(u, v)
≥ 0.

In addition,

(f ↑ f′)(u, v)

= f (u, v) + f ′(u, v) − f ′(v, u) (by equation (24.4))
≤ f (u, v) + f ′(u, v)
≤ f (u, v) + cf (u, v)
= f (u, v) + c(u, v) − f (u, v)

(because ﬂows are nonnegative)
(capacity constraint)

(deﬁnition of cf)

= c(u, v).

To show that ﬂow conservation holds and that |f ↑ f ′| = |f | + |f ′|, we

ﬁrst prove the claim that for all u ∈ V, we have

Because  we  disallow  antiparallel  edges  in  G  (but  not  in  Gf),  we  know
that for each vertex u, there can be an edge (u, v) or (v, u) in G, but never
both. For a ﬁxed vertex u, deﬁne Vl(u) = {v : (u, v) ∈ E} to be the set of
vertices with edges in G leaving u, and deﬁne Ve(u) = {v : (v, u) ∈ E} to
be the set of vertices with edges in G entering u. We have Vl(u) ∪ Ve(u)
⊆ V and, because G contains no antiparallel edges, Vl(u) ∩ Ve(u) = ∅.
By the deﬁnition of ﬂow augmentation in equation (24.4), only vertices
v in Vl(u) can have positive (f ↑ f′)(u, v), and only vertices v in Ve(u) can
have positive (f ↑ f ′)(v, u). Starting from the left-hand side of equation
(24.5), we use this fact and then reorder and group terms, giving

In equation (24.6), all four summations can extend to sum over V, since
each additional term has value 0. (Exercise 24.2-1 asks you to prove this
formally.) Taking all four summations over V, instead of just subsets of
V, proves the claim in equation (24.5).

Now we are ready to prove ﬂow conservation for f ↑ f ′ and that |f ↑ f′|
= | f | + |f ′|. For the latter property, let u = s in equation (24.5). Then, we
have

For ﬂow conservation, observe that for any vertex u that is neither s nor
t,  ﬂow  conservation  for  f  and  f  ′  means  that  the  right-hand  side  of
equation (24.5) is 0, and thus Σv∈V (f ↑ f′)(u, v) = Σv∈V (f ↑ f′)(v, u).

▪

Augmenting paths

Given a ﬂow network G = (V, E) and a ﬂow f, an augmenting path p is a
simple path from s to t in the residual network Gf. By the deﬁnition of
the residual network, the ﬂow on an edge (u, v) of an augmenting path

may increase by up to cf (u, v) without violating the capacity constraint
on whichever of (u, v) and (v, u) belongs to the original ﬂow network G.
The blue path in Figure 24.4(b) is an augmenting path. Treating the
residual  network  Gf  in  the  ﬁgure  as  a  ﬂow  network,  the  ﬂow  through
each edge of this path can increase by up to 4 units without violating a
capacity constraint, since the smallest residual capacity on this path is cf
(v2, v3) = 4. We call the maximum amount by which we can increase the
ﬂow  on  each  edge  in  an  augmenting  path  p  the  residual  capacity  of  p,
given by

cf (p) = min {cf (u, v) : (u, v) is in p}.

The  following  lemma,  which  Exercise  24.2-7  asks  you  to  prove,  makes
the above argument more precise.

Lemma 24.2
Let G = (V, E) be a ﬂow network, let f be a ﬂow in G, and let p be an
augmenting path in Gf. Deﬁne a function fp : V × V → ℝ by

Then, fp is a ﬂow in Gf with value |fp| = cf (p) > 0.

▪
The  following  corollary  shows  that  augmenting  f  by  fp  produces
another ﬂow in G whose value is closer to the maximum. Figure 24.4(c)
shows  the  result  of  augmenting  the  ﬂow  f  from  Figure  24.4(a)  by  the
ﬂow fp in Figure 24.4(b), and Figure 24.4(d) shows the ensuing residual
network.

Corollary 24.3
Let G = (V, E) be a ﬂow network, let f be a ﬂow in G, and let p be an
augmenting  path  in  Gf.  Let  fp  be  deﬁned  as  in  equation  (24.7),  and
suppose that f is augmented by fp. Then the function f ↑ fp is a ﬂow in G
with value |f ↑ fp| = |f| + |fp| > |f|.

Proof   Immediate from Lemmas 24.1 and 24.2.

▪

Cuts of ﬂow networks

The  Ford-Fulkerson  method  repeatedly  augments  the  ﬂow  along
augmenting paths until it has found a maximum ﬂow. How do we know
that  when  the  algorithm  terminates,  it  has  actually  found  a  maximum
ﬂow? The max-ﬂow min-cut theorem, which we will prove shortly, tells
us that a ﬂow is maximum if and only if its residual network contains
no  augmenting  path.  To  prove  this  theorem,  though,  we  must  ﬁrst
explore the notion of a cut of a ﬂow network.

A cut (S, T) of ﬂow network G = (V, E) is a partition of V into S and
T = V − S such that s ∈ S and t ∈ T. (This deﬁnition is similar to the
deﬁnition of “cut” that we used for minimum spanning trees in Chapter
21,  except  that  here  we  are  cutting  a  directed  graph  rather  than  an
undirected graph, and we insist that s ∈ S and t ∈ T.) If f is a ﬂow, then
the net ﬂow f(S, T) across the cut (S, T) is deﬁned to be

The capacity of the cut (S, T) is

A minimum cut of a network is a cut whose capacity is minimum over
all cuts of the network.

You  probably  noticed  that  the  deﬁnitions  of  ﬂow  across  a  cut  and
capacity  of  a  cut  differ  in  that  ﬂow  counts  edges  going  in  both
directions across the cut, but capacity counts only edges going from the
source  side  of  the  cut  toward  the  sink  side.  This  asymmetry  is
intentional  and  important.  The  reason  for  this  difference  will  become
apparent later in this section.

Figure 24.5 shows the cut ({s, v1, v2}, {v3, v4, t}) in the ﬂow network

of Figure 24.1(b). The net ﬂow across this cut is

f (v1, v3) + f (v2, v4) − f (v3, v2) = 12 + 11 − 4

and the capacity of this cut is

= 19,

Figure 24.5 A cut (S, T) in the ﬂow network of Figure 24.1(b), where S = {s, v1, v2} and T =
{v3, v4, t}. The vertices in S are orange, and the vertices in T are tan. The net ﬂow across (S, T)
is f (S, T) = 19, and the capacity is c(S, T) = 26.

c(v1, v3) + c(v2, v4) = 12 + 14

= 26.

The  following  lemma  shows  that,  for  a  given  ﬂow  f,  the  net  ﬂow

across any cut is the same, and it equals |f|, the value of the ﬂow.

Lemma 24.4
Let f be a ﬂow in a ﬂow network G with source s and sink t, and let (S,
T) be any cut of G. Then the net ﬂow across (S, T) is f (S, T) =| f|.

Proof      For  any  vertex  u  ∈  V  −  {s,  t},  rewrite  the  ﬂow-conservation
condition as

Taking  the  deﬁnition  of|  f|  from  equation  (24.1)  and  adding  the  left-
hand side of equation (24.10), which equals 0, summed over all vertices
in S − {s}, gives

Expanding the right-hand summation and regrouping terms yields

Because  V  =  S  ∪  T  and  S  ∩  T  =  ∅,  splitting  each  summation  over  V
into summations over S and T gives

The two summations within the parentheses are actually the same, since
for  all  vertices  x,  y  ∈  S,  the  term  f  (x,  y)  appears  once  in  each
summation. Hence, these summations cancel, yielding

▪

A  corollary  to  Lemma  24.4  shows  how  cut  capacities  bound  the

value of a ﬂow.

Corollary 24.5
The value of any ﬂow f in a ﬂow network G is bounded from above by
the capacity of any cut of G.

Proof   Let (S, T) be any cut of G and let f be any ﬂow. By Lemma 24.4
and the capacity constraint,

▪

Corollary 24.5 yields the immediate consequence that the value of a
maximum ﬂow in a network is bounded from above by the capacity of a
minimum  cut  of  the  network.  The  important  max-ﬂow  min-cut
theorem,  which  we  now  state  and  prove,  says  that  the  value  of  a
maximum ﬂow is in fact equal to the capacity of a minimum cut.

Theorem 24.6 (Max-ﬂow min-cut theorem)
If f is a ﬂow in a ﬂow network G = (V, E) with source s and sink t, then
the following conditions are equivalent:

1. f is a maximum ﬂow in G.
2. The residual network Gf contains no augmenting paths.
3. |f| = c(S, T) for some cut (S, T) of G.

Proof      (1)  ⇒  (2):  Suppose  for  the  sake  of  contradiction  that  f  is  a
maximum  ﬂow  in  G  but  that  Gf  has  an  augmenting  path  p.  Then,  by
Corollary 24.3, the ﬂow found by augmenting f by fp, where fp is given
by  equation  (24.7),  is  a  ﬂow  in  G  with  value  strictly  greater  than  |f|,
contradicting the assumption that f is a maximum ﬂow.

(2) ⇒ (3): Suppose that Gf has no augmenting path, that is, that Gf

contains no path from s to t. Deﬁne

S = {v ∈ V : there exists a path from s to v in Gf }

and T = V − S. The partition (S, T) is a cut: we have s ∈ S trivially and
t ∉ S because there is no path from s to t in Gf. Now consider a pair of
vertices u ∈ S and v ∈ T. If (u, v) ∈ E, we must have f (u, v) = c(u, v),

since otherwise (u, v) ∈ Ef, which would place v in set S. If (v, u) ∈ E,
we must have f (v, u) = 0, because otherwise cf (u, v) = f (v, u) would be
positive and we would have (u, v) ∈ Ef, which again would place v in S.
Of course, if neither (u, v) nor (v, u) belongs to E, then f (u, v) = f (v, u)
= 0. We thus have

By Lemma 24.4, therefore, |f| = f (S, T) = c(S, T).

(3)  ⇒  (1):  By  Corollary  24.5,  |f|  ≤  c(S,  T)  for  all  cuts  (S,  T).  The

condition |f| = c(S, T) thus implies that f is a maximum ﬂow.

▪

The basic Ford-Fulkerson algorithm

Each  iteration  of  the  Ford-Fulkerson  method  ﬁnds  some  augmenting
path p and uses p to modify the ﬂow f. As Lemma 24.2 and Corollary
24.3 suggest, replacing f by f ↑ fp produces a new ﬂow whose value is |f|
+
|fp|.  The  procedure  FORD-FULKERSON  on  the  next  page
implements  the  method  by  updating  the  ﬂow  attribute  (u,  v).f  for  each
edge (u, v) ∈ E.1 It assumes implicitly that (u, v).f = 0 if (u, v) ∉ E. The
procedure  also  assumes  that  the  capacities  c(u,  v)  come  with  the  ﬂow
network, and that c(u, v) = 0 if (u, v) ∉ E. The procedure computes the
residual  capacity  cf  (u,  v)  in  accordance  with  the  formula  (24.2).  The
expression cf (p) in the code is just a temporary variable that stores the
residual capacity of the path p.

FORD-FULKERSON (G, s, t)
1 for each edge (u, v) ∈ G.E
2
3 while there exists a path p from s to t in the residual network Gf
4

cf (p) = min {cf (u, v) : (u, v) is in p}

(u, v).f = 0

5

6

7

for each edge (u, v) in p
if (u, v) ∈ G.E

(u, v).f = (u, v).f + cf (p)
else (v, u).f = (v, u).f − cf (p)

8
9 return f

The  FORD-FULKERSON  procedure  simply  expands  on  the
FORD-FULKERSON-METHOD  pseudocode  given  earlier.  Figure
24.6  shows  the  result  of  each  iteration  in  a  sample  run.  Lines  1–2
initialize the ﬂow f to 0. The while loop of lines 3–8 repeatedly ﬁnds an
augmenting  path  p  in  Gf  and  augments  ﬂow  f  along  p  by  the  residual
capacity  cf  (p).  Each  residual  edge  in  path  p  is  either  an  edge  in  the
original  network  or  the  reversal  of  an  edge  in  the  original  network.
Lines 6–8 update the ﬂow in each case appropriately, adding ﬂow when
the residual edge is an original edge and subtracting it otherwise. When
no augmenting paths exist, the ﬂow f is a maximum ﬂow.

Analysis of Ford-Fulkerson

time  of  FORD-FULKERSON  depends  on

the
The  running
augmenting  path  p  and  how  it’s  found  in  line  3.  If  the  edge  capacities
are  irrational  numbers,  it’s  possible  to  choose  the  augmenting  path  so
that the algorithm never terminates: the value of the ﬂow increases with
successive  augmentations,  but  never  converges  to  the  maximum  ﬂow
value. The good news is that if the algorithm ﬁnds the augmenting path
by using a breadth-ﬁrst search (which we saw in Section 20.2), it runs in
polynomial  time.  Before  proving  this  result,  we  obtain  a  simple  bound
for the case in which all capacities are integers and the algorithm ﬁnds
any augmenting path.

Figure 24.6 The execution of the basic Ford-Fulkerson algorithm. (a)–(e) Successive iterations
of the while loop. The left side of each part shows the residual network Gf from line 3 with a
blue  augmenting  path  p.  The  right  side  of  each  part  shows  the  new  ﬂow  f  that  results  from
augmenting  f  by  fp.  The  residual  network  in  (a)  is  the  input  ﬂow  network  G.  (f)  The  residual
network  at  the  last  while  loop  test.  It  has  no  augmenting  paths,  and  the  ﬂow  f  shown  in  (e)  is
therefore a maximum ﬂow. The value of the maximum ﬂow found is 23.

Figure 24.7 (a) A ﬂow network for which FORD-FULKERSON can take Θ(E | f*|) time, where
f* is a maximum ﬂow, shown here with |f*| = 2,000,000. The blue path is an augmenting path
with  residual  capacity  1.  (b)  The  resulting  residual  network,  with  another  augmenting  path
whose residual capacity is 1. (c) The resulting residual network.

In  practice,  the  maximum-ﬂow  problem  often  arises  with  integer
capacities. If the capacities are rational numbers, an appropriate scaling
transformation  can  make  them  all  integers.  If  f*  denotes  a  maximum
ﬂow in the transformed network, then a straightforward implementation
of FORD-FULKERSON executes the while loop of lines 3–8 at most
|f*|  times,  since  the  ﬂow  value  increases  by  at  least  1  unit  in  each
iteration.

A  good  implementation  should  perform  the  work  done  within  the
while  loop  efﬁciently.  It  should  represent  the  ﬂow  network  G  =  (V,  E)
with the right data structure and ﬁnd an augmenting path by a linear-
time  algorithm.  Let’s  assume  that  the  implementation  keeps  a  data
structure corresponding to a directed graph G′ = (V, E′), where E′ = {(u,
v) : (u, v) ∈ E or (v, u) ∈ E}. Edges in the network G are also edges in
G′,  making  it  straightforward  to  maintain  capacities  and  ﬂows  in  this
data structure. Given a ﬂow f on G, the edges in the residual network Gf
consist of all edges (u, v) of G′ such that cf (u, v) > 0, where cf conforms
to  equation  (24.2).  The  time  to  ﬁnd  a  path  in  a  residual  network  is
therefore  O(V  +  E′)  =  O(E)  using  either  depth-ﬁrst  search  or  breadth-
ﬁrst  search.  Each  iteration  of  the  while  loop  thus  takes  O(E)  time,  as
does the initialization in lines 1–2, making the total running time of the
FORD-FULKERSON algorithm O(E |f*|).

When  the  capacities  are  integers  and  the  optimal  ﬂow  value  |f*|  is
small,  the  running  time  of  the  Ford-Fulkerson  algorithm  is  good.
Figure 24.7(a) shows an example of what can happen on a simple ﬂow

network  for  which  |f*|  is  large.  A  maximum  ﬂow  in  this  network  has
value 2,000,000: 1,000,000 units of ﬂow traverse the path s → u → t, and
another  1,000,000  units  traverse  the  path  s  →  v  →  t.  If  the  ﬁrst
augmenting  path  found  by  FORD-FULKERSON  is  s  →  u  →  v  →  t,
shown  in  Figure  24.7(a),  the  ﬂow  has  value  1  after  the  ﬁrst  iteration.
The resulting residual network appears in Figure 24.7(b). If the second
iteration ﬁnds the augmenting path s → v → u → t, as shown in Figure
24.7(b),  the  ﬂow  then  has  value  2.  Figure  24.7(c)  shows  the  resulting
residual  network.  If  the  algorithm  continues  alternately  choosing  the
augmenting paths s → u → v → t and s → v → u → t, it performs a total
of 2,000,000 augmentations, increasing the ﬂow value by only 1 unit in
each.

The Edmonds-Karp algorithm

In  the  example  of  Figure  24.7,  the  algorithm  never  chooses  the
augmenting  path  with  the  fewest  edges.  It  should  have.  By  using
breadth-ﬁrst search to ﬁnd an augmenting path in the residual network,
the  algorithm  runs  in  polynomial  time,  independent  of  the  maximum
ﬂow  value.  We  call  the  Ford-Fulkerson  method  so  implemented  the
Edmonds-Karp algorithm.

Let’s  now  prove  that  the  Edmonds-Karp  algorithm  runs  in  O(VE2)
time.  The  analysis  depends  on  the  distances  to  vertices  in  the  residual
network  Gf.  The  notation  δf  (u,  v)  denotes  the  shortest-path  distance
from u to v in Gf, where each edge has unit distance.

Lemma 24.7
If  the  Edmonds-Karp  algorithm  is  run  on  a  ﬂow  network  G  =  (V,  E)
with source s and sink t, then for all vertices v ∈ V − {s, t}, the shortest-
path  distance  δf  (s,  v)
increases
monotonically with each ﬂow augmentation.

in  the  residual  network  Gf

Proof      We’ll  suppose  that  a  ﬂow  augmentation  occurs  that  causes  the
shortest-path distance from s to some vertex v ∈ V − {s, t} to decrease
and  then  derive  a  contradiction.  Let  f  be  the  ﬂow  just  before  an
augmentation  that  decreases  some  shortest-path  distance,  and  let  f′  be

the  ﬂow  just  afterward.  Let  v  be  a  vertex  with  the  minimum  δf′  (s,  v)
whose distance was decreased by the augmentation, so that δf′ (s, v) < δf
(s, v). Let p = s ⇝ u → v be a shortest path from s to v in Gf′, so that (u,
v) ∈ Ef′ and

Because of how we chose v, we know that the distance of vertex u from
the source s did not decrease, that is,

We  claim  that  (u,  v)  ∉  Ef.  Why?  If  we  have  (u,  v)  ∈  Ef,  then  we  also
have

δf (s, v) ≤ δf (s, u) + 1 (by Lemma 22.10, the triangle inequality)

≤ δf′ (s, u) + 1 (by inequality (24.12))
(by equation (24.11)),
= δf′ (s, v)

which contradicts our assumption that δf′ (s, v) < δf (s, v).

How  can  we  have  (u,  v)  ∉  Ef  and  (u,  v)  ∈  Ef′?  The  augmentation
must have increased the ﬂow from v to u, so that edge (v, u) was in the
augmenting path. The augmenting path was a shortest path from s to t
in Gf, and since any subpath of a shortest path is itself a shortest path,
this augmenting path includes a shortest path from s to u in Gf that has
(v, u) as its last edge. Therefore,

δf (s, v) = δf (s, u) − 1

≤ δf′ (s, u) − 1 (by inequality (24.12))
= δf′ (s, v) − 2 (by equation (24.11)),

so that δf′ (s, v) > δf (s, v), contradicting our assumption that δf′ (s, v) <
δf (s, v). We conclude that our assumption that such a vertex v exists is
incorrect.

▪

The next theorem bounds the number of iterations of the Edmonds-

Karp algorithm.

Theorem 24.8
If  the  Edmonds-Karp  algorithm  is  run  on  a  ﬂow  network  G  =  (V,  E)
with source s and sink t, then the total number of ﬂow augmentations
performed by the algorithm is O(VE).

Proof   We say that an edge (u, v) in a residual network Gf is critical on
an  augmenting  path  p  if  the  residual  capacity  of  p  is  the  residual
capacity  of  (u,  v),  that  is,  if  cf  (p)  =  cf  (u,  v).  After  ﬂow  is  augmented
along  an  augmenting  path,  any  critical  edge  on  the  path  disappears
from  the  residual  network.  Moreover,  at  least  one  edge  on  any
augmenting path must be critical. We’ll show that each of the |E| edges
can become critical at most |V|/2 times.

Let u and v be vertices in V that are connected by an edge in E. Since
augmenting paths are shortest paths, when (u, v) is critical for the ﬁrst
time, we have

δf (s, v) = δf (s, u) + 1.

Once the ﬂow is augmented, the edge (u, v) disappears from the residual
network.  It  cannot  reappear  later  on  another  augmenting  path  until
after  the  ﬂow  from  u  to  v  is  decreased,  which  occurs  only  if  (v,  u)
appears on an augmenting path. If f ′ is the ﬂow in G when this event
occurs, then we have
δf′ (s, u) = δf′ (s, v) + 1.
Since δf (s, v) ≤ δf′ (s, v) by Lemma 24.7, we have

δf′ (s, u) = δf′ (s, v) + 1
≥ δf (s, v) + 1
= δf (s, u) + 2.

Consequently, from the time (u, v) becomes critical to the time when
it next becomes critical, the distance of u from the source increases by at
least 2. The distance of u from the source is initially at least 0. Because
edge (u, v) is on an augmenting path, and augmenting paths end at t, we
know that u cannot be t, so that in any residual network that has a path
from s to u, the shortest such path has at most |V| − 2 edges. Thus, after
the ﬁrst time that (u, v) becomes critical, it can become critical at most
(|V|  −  2)/2  =  |V|/2  −  1  times  more,  for  a  total  of  at  most  |V|/2  times.
Since  there  are  O(E)  pairs  of  vertices  that  can  have  an  edge  between
them in a residual network, the total number of critical edges during the
entire  execution  of  the  Edmonds-Karp  algorithm  is  O(VE).  Each
augmenting  path  has  at  least  one  critical  edge,  and  hence  the  theorem
follows.

▪

Because  each  iteration  of  FORD-FULKERSON  takes  O(E)  time
when it uses breadth-ﬁrst search to ﬁnd the augmenting path, the total
running time of the Edmonds-Karp algorithm is O(VE2).

Exercises

24.2-1
Prove that the summations in equation (24.6) equal the summations on
the right-hand side of equation (24.5).

24.2-2
In Figure 24.1(b), what is the net ﬂow across the cut ({s, v2, v4}, {v1, v3,
t})? What is the capacity of this cut?

24.2-3
Show  the  execution  of  the  Edmonds-Karp  algorithm  on  the  ﬂow
network of Figure 24.1(a).

24.2-4
In the example of Figure 24.6, what is the minimum cut corresponding
to the maximum ﬂow shown? Of the augmenting paths appearing in the
example, which one cancels ﬂow?

24.2-5
The  construction  in  Section  24.1  to  convert  a  ﬂow  network  with
multiple sources and sinks into a single-source, single-sink network adds
edges with inﬁnite capacity. Prove that any ﬂow in the resulting network
has  a  ﬁnite  value  if  the  edges  of  the  original  network  with  multiple
sources and sinks have ﬁnite capacity.

24.2-6
Suppose that each source si in a ﬂow network with multiple sources and
sinks  produces  exactly  pi  units  of  ﬂow,  so  that  Σv∈V  f  (si,  v)  =  pi.
Suppose also that each sink tj consumes exactly qj units, so that Σv∈V f
(v,  tj)  =  qj,  where  Σi  pi  =  Σj  qj.  Show  how  to  convert  the  problem  of
ﬁnding a ﬂow f that obeys these additional constraints into the problem
of ﬁnding a maximum ﬂow in a single-source, single-sink ﬂow network.

24.2-7
Prove Lemma 24.2.

24.2-8
Suppose that we redeﬁne the residual network to disallow edges into s.
Argue  that  the  procedure  FORD-FULKERSON  still  correctly
computes a maximum ﬂow.

24.2-9
Suppose  that  both  f  and  f  ′  are  ﬂows  in  a  ﬂow  network.  Does  the
augmented  ﬂow  f  ↑  f  ′  satisfy  the  ﬂow  conservation  property?  Does  it
satisfy the capacity constraint?

24.2-10
Show how to ﬁnd a maximum ﬂow in a ﬂow network G = (V, E) by a
sequence  of  at  most  |E|  augmenting  paths.  (Hint:  Determine  the  paths
after ﬁnding the maximum ﬂow.)

24.2-11
The edge connectivity of an undirected graph is the minimum number k
of  edges  that  must  be  removed  to  disconnect  the  graph.  For  example,
the edge connectivity of a tree is 1, and the edge connectivity of a cyclic

chain of vertices is 2. Show how to determine the edge connectivity of
an undirected graph G = (V, E) by running a maximum-ﬂow algorithm
on at most |V| ﬂow networks, each having O(V + E) vertices and O(E)
edges.

24.2-12
You  are  given  a  ﬂow  network  G,  where  G  contains  edges  entering  the
source s. Let f be a ﬂow in G with |f| ≥ 0 in which one of the edges (v, s)
entering the source has f (v, s) = 1. Prove that there must exist another
ﬂow f ′ with f ′(v, s) = 0 such that |f| = |f′|. Give an O(E)-time algorithm
to compute f′, given f and assuming that all edge capacities are integers.

24.2-13
Suppose  that  you  wish  to  ﬁnd,  among  all  minimum  cuts  in  a  ﬂow
network  G  with  integer  capacities,  one  that  contains  the  smallest
number  of  edges.  Show  how  to  modify  the  capacities  of  G  to  create  a
new ﬂow network G′ in which any minimum cut in G′ is a minimum cut
with the smallest number of edges in G.

24.3    Maximum bipartite matching

Some combinatorial problems can be cast as maximum-ﬂow problems,
such as the multiple-source, multiple-sink maximum-ﬂow problem from
Section 24.1. Other combinatorial problems seem on the surface to have
little  to  do  with  ﬂow  networks,  but  they  can  in  fact  be  reduced  to
maximum-ﬂow  problems.  This  section  presents  one  such  problem:
ﬁnding a maximum matching in a bipartite graph. In order to solve this
problem, we’ll take advantage of an integrality property provided by the
Ford-Fulkerson method. We’ll also see how to use the Ford-Fulkerson
method  to  solve  the  maximum-bipartite-matching  problem  on  a  graph
G  =  (V,  E)  in  O(VE)  time.  Section  25.1  will  present  an  algorithm
speciﬁcally designed to solve this problem.

The maximum-bipartite-matching problem

Given an undirected graph G = (V, E), a matching is a subset of edges
M  ⊆  E  such  that  for  all  vertices  v  ∈  V,  at  most  one  edge  of  M  is
incident on v. We say that a vertex v ∈ V is matched by the matching M
if  some  edge  in  M  is  incident  on  v,  and  otherwise,  v  is  unmatched.  A
maximum  matching  is  a  matching  of  maximum  cardinality,  that  is,  a
matching M such that for any matching M′, we have |M| ≥ |M′|. In this
section,  we  restrict  our  attention  to  ﬁnding  maximum  matchings  in
bipartite graphs: graphs in which the vertex set can be partitioned into
V = L ∪ R, where L and R are disjoint and all edges in E go between L
and  R.  We  further  assume  that  every  vertex  in  V  has  at  least  one
incident  edge.  Figure  24.8  illustrates  the  notion  of  a  matching  in  a
bipartite graph.

The  problem  of  ﬁnding  a  maximum  matching  in  a  bipartite  graph
has many practical applications. As an example, consider matching a set
L of machines with a set R of tasks to be performed simultaneously. An
edge (u, v) in E signiﬁes that a particular machine u ∈ L is capable of
performing  a  particular  task  v  ∈  R.  A  maximum  matching  provides
work for as many machines as possible.

Figure 24.8 A bipartite graph G = (V, E) with vertex partition V = L ∪ R. (a) A matching with
cardinality  2,  indicated  by  blue  edges.  (b)  A  maximum  matching  with  cardinality  3.  (c)  The
corresponding ﬂow network G′ with a maximum ﬂow shown. Each edge has unit capacity. Blue
edges have a ﬂow of 1, and all other edges carry no ﬂow. The blue edges from L to R correspond
to those in the maximum matching from (b).

Finding a maximum bipartite matching

The  Ford-Fulkerson  method  provides  a  basis  for  ﬁnding  a  maximum
matching  in  an  undirected  bipartite  graph  G  =  (V,  E)  in  time
polynomial  in  |V|  and  |E|.  The  trick  is  to  construct  a  ﬂow  network  in
which  ﬂows  correspond  to  matchings,  as  shown  in  Figure  24.8(c).  We
deﬁne  the  corresponding  ﬂow  network  G′  =  (V′,  E′)  for  the  bipartite
graph G as follows. Let the source s and sink t be new vertices not in V,
and let V′ = V ∪ {s, t}. If the vertex partition of G is V = L ∪ R, the
directed edges of G′ are the edges of E, directed from L to R, along with
|V | new directed edges:

E′ = {(s, u) : u ∈ L}

∪ {(u, v) : u ∈ L, v ∈ R, and (u, v) ∈ E}
∪ {(v, t) : v ∈ R}.

To  complete  the  construction,  assign  unit  capacity  to  each  edge  in  E′.
Since each vertex in V has at least one incident edge, |E| ≥ |V|/2. Thus, |E|
≤ |E′| = |E| + |V| ≤ 3 |E|, and so |E′| = Θ(E).

The  following  lemma  shows  that  a  matching  in  G  corresponds
directly  to  a  ﬂow  in  G’s  corresponding  ﬂow  network  G′.  We  say  that  a
ﬂow  f  on  a  ﬂow  network  G  =  (V,  E)  is  integer-valued  if  f  (u,  v)  is  an
integer for all (u, v) ∈ V × V.
Lemma 24.9
Let  G  =  (V,  E)  be  a  bipartite  graph  with  vertex  partition  V  =  L  ∪  R,
and  let  G′  =  (V′,  E′)  be  its  corresponding  ﬂow  network.  If  M  is  a
matching in G, then there is an integer-valued ﬂow f in G′ with value |f|
=  |M|.  Conversely,  if  f  is  an  integer-valued  ﬂow  in  G′,  then  there  is  a
matching M in G with cardinality |M| = |f| consisting of edges (u, v) ∈ E
such that f (u, v) > 0.

Proof   We ﬁrst show that a matching M in G corresponds to an integer-
valued ﬂow f in G′. Deﬁne f as follows. If (u, v) ∈ M, then f (s, u) = f (u,
v) = f (v, t) = 1. For all other edges (u, v) ∈ E′, deﬁne f (u, v) = 0. It is
simple  to  verify  that  f  satisﬁes  the  capacity  constraint  and  ﬂow
conservation.

Intuitively, each edge (u, v) ∈ M corresponds to 1 unit of ﬂow in G′
that traverses the path s → u → v → t. Moreover, the paths induced by

edges in M are vertex-disjoint, except for s and t. The net ﬂow across cut
(L ∪ {s}, R ∪ {t}) is equal to |M|, and thus, by Lemma 24.4, the value
of the ﬂow is |f| = |M|.

To prove the converse, let f be an integer-valued ﬂow in G′ and, as in

the statement of the lemma, let

M = {(u, v) : u ∈ L, v ∈ R, and f (u, v) > 0}.
Each  vertex  u  ∈  L  has  only  one  entering  edge,  namely  (s,  u),  and  its
capacity  is  1.  Thus,  each  u  ∈  L  has  at  most  1  unit  of  ﬂow  entering  it,
and  if  1  unit  of  ﬂow  does  enter,  by  ﬂow  conservation,  1  unit  of  ﬂow
must leave. Furthermore, since the ﬂow f is integer-valued, for each u ∈
L, the 1 unit of ﬂow can enter on at most one edge and can leave on at
most  one  edge.  Thus,  1  unit  of  ﬂow  enters  u  if  and  only  if  there  is
exactly  one  vertex  v  ∈  R  such  that  f  (u,  v)  =  1,  and  at  most  one  edge
leaving each u ∈ L carries positive ﬂow. A symmetric argument applies
to each v ∈ R. The set M is therefore a matching.

To see that |M| = |f|, observe that of the edges (u, v) ∈ E′ such that u

∈ L and v ∈ R,

Consequently, f (L ∪ {s}, R ∪ {t}), the net ﬂow across cut (L ∪ {s}, R ∪
{t}), is equal to |M|. Lemma 24.4 gives that |f| = f (L ∪ {s}, R ∪ {t}) =
|M|.

▪

Based  on  Lemma  24.9,  we  would  like  to  conclude  that  a  maximum
matching in a bipartite graph G corresponds to a maximum ﬂow in its
corresponding ﬂow network G′, and therefore running a maximum-ﬂow
algorithm on G′ provides a maximum matching in G. The only hitch in
this reasoning is that the maximum-ﬂow algorithm might return a ﬂow
in G′ for which some f (u, v) is not an integer, even though the ﬂow value
|f|  must  be  an  integer.  The  following  theorem  shows  that  the  Ford-
Fulkerson method cannot produce a solution with this problem.

Theorem 24.10 (Integrality theorem)

If  the  capacity  function  c  takes  on  only  integer  values,  then  the
maximum  ﬂow  f  produced  by  the  Ford-Fulkerson  method  has  the
property  that  |f|  is  an  integer.  Moreover,  for  all  vertices  u  and  v,  the
value of f (u, v) is an integer.

Proof      Exercise  24.3-2  asks  you  to  provide  the  proof  by  induction  on
the number of iterations.

▪

We can now prove the following corollary to Lemma 24.9.

Corollary 24.11
The  cardinality  of  a  maximum  matching  M  in  a  bipartite  graph  G
equals the value of a maximum ﬂow f in its corresponding ﬂow network
G′.

Proof   We use the nomenclature from Lemma 24.9. Suppose that M is a
maximum matching in G and that the corresponding ﬂow f in G′ is not
maximum.  Then  there  is  a  maximum  ﬂow  f′  in  G′  such  that  |f′|  >  |f|.
Since the capacities in G′ are integer-valued, by Theorem 24.10, we can
assume that f′ is integer-valued. Thus, f′ corresponds to a matching M′
in G with cardinality |M′| = |f′| > |f| = |M|, contradicting our assumption
that M is a maximum matching. In a similar manner, we can show that
if f is a maximum ﬂow in G′, its corresponding matching is a maximum
matching on G.

▪

Thus,  to  ﬁnd  a  maximum  matching  in  a  bipartite  undirected  graph
G,  create  the  ﬂow  network  G′,  run  the  Ford-Fulkerson  method  on  G′,
and  convert  the  integer-valued  maximum  ﬂow  found  into  a  maximum
matching for G. Since any matching in a bipartite graph has cardinality
at most min {|L|, |R|} = O(V), the value of the maximum ﬂow in G′ is
O(V).  Therefore,  ﬁnding  a  maximum  matching  in  a  bipartite  graph
takes O(VE′) = O(VE) time, since |E′| = Θ(E).

Exercises

24.3-1

Run  the  Ford-Fulkerson  algorithm  on  the  ﬂow  network  in  Figure
24.8(c)  and  show  the  residual  network  after  each  ﬂow  augmentation.
Number  the  vertices  in  L  top  to  bottom  from  1  to  5  and  in  R  top  to
bottom from 6 to 9. For each iteration, pick the augmenting path that is
lexicographically smallest.

24.3-2
Prove Theorem 24.10. Use induction on the number of iterations of the
Ford-Fulkerson method.

24.3-3
Let  G  =  (V,  E)  be  a  bipartite  graph  with  vertex  partition  V  =  L  ∪  R,
and let G′ be its corresponding ﬂow network. Give a good upper bound
on the length of any augmenting path found in G′ during the execution
of FORD-FULKERSON.

Problems

24-1     Escape problem
An n×n grid is an undirected graph consisting of n rows and n columns
of vertices, as shown in Figure 24.9. We denote the vertex in the ith row
and  the  j  th  column  by  (i,  j).  All  vertices  in  a  grid  have  exactly  four
neighbors,  except  for  the  boundary  vertices,  which  are  the  points  (i,  j)
for which i = 1, i = n, j = 1, or j = n.

Given  m  ≤  n2  starting  points  (x1,  y1),  (x2,  y2),  …,  (xm,  ym)  in  the
grid,  the  escape  problem  is  to  determine  whether  there  are  m  vertex-
disjoint paths from the starting points to any m different points on the
boundary. For example, the grid in Figure 24.9(a) has an escape, but the
grid in Figure 24.9(b) does not.

Figure  24.9  Grids  for  the  escape  problem.  Starting  points  are  blue,  and  other  grid  vertices  are
tan. (a) A grid with an escape, shown by blue paths. (b) A grid with no escape.

a. Consider a ﬂow network in which vertices, as well as edges, have

capacities. That is, the total positive ﬂow entering any given vertex is
subject to a capacity constraint. Show how to reduce the problem of
determining the maximum ﬂow in a network with edge and vertex
capacities to an ordinary maximum-ﬂow problem on a ﬂow network
of comparable size.

b. Describe an efﬁcient algorithm to solve the escape problem, and

analyze its running time.

24-2     Minimum path cover
A path cover of a directed graph G = (V, E) is a set P of vertex-disjoint
paths  such  that  every  vertex  in  V  is  included  in  exactly  one  path  in  P.
Paths  may  start  and  end  anywhere,  and  they  may  be  of  any  length,
including 0. A minimum path cover of G is a path cover containing the
fewest possible paths.

a. Give an efﬁcient algorithm to ﬁnd a minimum path cover of a

directed acyclic graph G = (V, E). (Hint: Assuming that V = {1, 2, …,
n}, construct a ﬂow network based on the graph G′ = (V′, E′), where
V′ = {x0, x1, …, xn} ∪ {y0, y1, …, yn},
E′ = {(x0, xi) : i ∈ V } ∪ {(yi, y0) : i ∈ V } ∪ {(xi, yj) : (i, j) ∈ E},

and run a maximum-ﬂow algorithm.)

b. Does your algorithm work for directed graphs that contain cycles?

Explain.

24-3     Hiring consulting experts

Professor  Fieri  wants  to  open  a  consulting  company  for  the  food
industry.  He  has  identiﬁed  n  important  food  categories,  which  he
represents by the set C = {C1, C2, …, Cn}. In each category Ck, he can
hire  an  expert  in  that  category  for  ek  >  0  dollars.  The  consulting
company  has  lined  up  a  set  J  =  {J1,  J2,  …,  Jm}  of  potential  jobs.  In
order  to  perform  job  Ji,  the  company  needs  to  have  hired  experts  in  a
subset  Ri  ⊆  C  of  categories.  Each  expert  can  work  on  multiple  jobs
simultaneously.  If  the  company  chooses  to  accept  job  Ji,  it  must  have
hired  experts  in  all  categories  in  Ri,  and  it  takes  in  revenue  of  pi  >  0
dollars.

Professor Fieri’s job is to determine which categories to hire experts
in and which jobs to accept in order to maximize the net revenue, which
is the total income from jobs accepted minus the total cost of employing
the experts.

Consider the following ﬂow network G. It contains a source vertex s,
vertices C1, C2, …, Cn, vertices J1, J2, …, Jm, and a sink vertex t. For
k = 1, 2 …, n, the ﬂow network contains an edge (s, Ck) with capacity
c(s, Ck) = ek, and for i = 1, 2, …, m, the ﬂow network contains an edge
(Ji, t) with capacity c(Ji, t) = pi. For k = 1, 2, …, n and i = 1, 2, …, m, if
Ck ∈ Ri, then G contains an edge (Ck, Ji) with capacity c(Ck, Ji) = ∞.

a. Show that if Ji ∈ T for a ﬁnite-capacity cut (S, T) of G, then Ck ∈ T

for each Ck ∈ Ri.

b. Show how to determine the maximum net revenue from the capacity

of a minimum cut of G and the given pi values.

c. Give an efﬁcient algorithm to determine which jobs to accept and

which experts to hire. Analyze the running time of your algorithm in
terms of m, n, and

.

24-4     Updating maximum ﬂow
Let  G  =  (V,  E)  be  a  ﬂow  network  with  source  s,  sink  t,  and  integer
capacities. Suppose that you are given a maximum ﬂow in G.

a. Suppose that the capacity of a single edge (u, v) ∈ E increases by 1.
Give an O(V + E)-time algorithm to update the maximum ﬂow.

b. Suppose that the capacity of a single edge (u, v) ∈ E decreases by 1.

Give an O(V + E)-time algorithm to update the maximum ﬂow.

24-5     Maximum ﬂow by scaling
Let G = (V, E) be a ﬂow network with source s, sink t, and an integer
capacity c(u, v) on each edge (u, v) ∈ E. Let C = max {c(u, v) : (u, v) ∈
E}.

a. Argue that a minimum cut of G has capacity at most C |E|.

b. For a given number K, show how to ﬁnd an augmenting path of

capacity at least K in O(E) time, if such a path exists.

The  procedure  MAX-FLOW-BY-SCALING  appearing  on
the
following  page  modiﬁes  the  basic  FORD-FULKERSON-METHOD
procedure to compute a maximum ﬂow in G.

c. Argue that MAX-FLOW-BY-SCALING returns a maximum ﬂow.

d. Show that the capacity of a minimum cut of the residual network Gf

is less than 2K |E| each time line 4 executes.

e. Argue that the inner while loop of lines 5–6 executes O(E) times for

each value of K.

MAX-FLOW-BY-SCALING (G, s, t)
1 C = max {c(u, v) : (u, v) ∈ E}
2 initialize ﬂow f to 0
3 K = 2⌊lg C⌋
4 while K ≥ 1
5

while there exists an augmenting path p of capacity at least K

6

augment ﬂow f along p

K = K/2

7
8 return f

f. Conclude that MAX-FLOW-BY-SCALING can be implemented so

that it runs in O(E2 lg C) time.

implements

24-6     Widest augmenting path
The  Edmonds-Karp  algorithm
the  Ford-Fulkerson
algorithm  by  always  choosing  a  shortest  augmenting  path  in  the
residual  network.  Suppose  instead  that  the  Ford-Fulkerson  algorithm
chooses a widest augmenting path: an augmenting path with the greatest
residual capacity. Assume that G = (V, E) is a ﬂow network with source
s and sink t, that all capacities are integer, and that the largest capacity
is C. In this problem, you will show that choosing a widest augmenting
path results in at most |E| ln |f*| augmentations to ﬁnd a maximum ﬂow
f*.

a. Show how to adjust Dijkstra’s algorithm to ﬁnd the widest

augmenting path in the residual network.

b. Show that a maximum ﬂow in G can be formed by successive ﬂow

augmentations along at most |E| paths from s to t.

c. Given a ﬂow f, argue that the residual network Gf has an augmenting

path p with residual capacity cf (p) ≥ (|f*| − |f|)/|E|.

d. Assuming that each augmenting path is a widest augmenting path, let
fi be the ﬂow after augmenting the ﬂow by the ith augmenting path,
where f0 has f (u, v) = 0 for all edges (u, v). Show that |f*| − |fi| ≤ |f*| (1
− 1/|E|)i.
e. Show that |f* | − |fi| < |f*| e−i/|E|.
f. Conclude that after the ﬂow is augmented at most |E| ln |f*| times, the

ﬂow is a maximum ﬂow.

24-7     Global minimum cut

A global cut in an undirected graph G = (V, E) is a partition (see page
1156) of V into two nonempty sets V1 and V2. This deﬁnition is like the
deﬁnition  of  cut  that  we  have  used  in  this  chapter,  except  that  we  no
longer have distinguished vertices s and t. Any edge (u, v) with u ∈ V1
and v ∈ V2 is said to cross the cut.

We can extend this deﬁnition of a cut to a multigraph G = (V, E) (see
page  1167),  and  we  denote  by  c(u,  v)  the  number  of  edges  in  the
multigraph with endpoints u and v. A global cut in a multigraph is still a
partition  of  the  vertices,  and  the  value  of  a  global  cut  (V1,  V2)  is
.  A  solution  to  the  global-minimum-cut
problem  is  a  cut  (V1,  V2)  such  that  c(V1,  V2)  is  minimum.  Let  μ(G)
denote the value of a global minimum cut in a graph or multigraph G.

a. Show how to ﬁnd a global minimum cut of a graph G = (V, E) by

 maximum-ﬂow problems, each with a different pair of

solving
vertices as the source and sink, and taking the mininum value of the
cuts found.

b. Give an algorithm to ﬁnd a global minimum cut by solving only Θ(V)

maximum-ﬂow problems. What is the running time of your
algorithm?

The remainder of this problem develops an algorithm for the global-
minimum-cut  problem
that  does  not  use  any  maximum-ﬂow
computations.  It  uses  the  notion  of  an  edge  contraction,  deﬁned  on
page  1168,  with  one  crucial  difference.  The  algorithm  maintains  a
multigraph,  so  that  upon  contracting  an  edge  (u,  v),  it  creates  a  new
vertex x, and for any other vertex y ∈ V, the number of edges between
x and y is c(u, y) + c(v, y). The algorithm does not maintain self-loops,
and so it sets c(x, x) to 0. Denote by G/(u, v) the multigraph that results
from contracting edge (u, v) in multigraph G.

Consider  what  can  happen  to  the  minimum  cut  when  an  edge  is
contracted. Assume that, at all points, the minimum cut in a multigraph
G is unique. We’ll remove this assumption later.

c. Show that for any edge (u, v), we have μ(G/(u, v)) ≤ μ(G). Under what

conditions is μ(G/(u, v)) < μ(G)?

Next, you will show that if you pick an edge uniformly at random,

the probability that it belongs to the minimum cut is small.

d. Show that for any multigraph G = (V, E), the value of the global

minimum cut is at most the average degree of a vertex: that μ(G) ≤ 2
|E|/|V|, where |E| denotes the total number of edges in the multigraph.

e. Using the results from parts (c) and (d), show that, if we pick an edge
(u, v) uniformly at random, then the probability that (u, v) belongs to
the minimum cut is at most 2/V.

Consider  the  algorithm  that  repeatedly  chooses  an  edge  at  random
and contracts it until the multigraph has exactly two vertices, say u and
v.  At  that  point,  the  multigraph  corresponds  to  a  cut  in  the  original
graph,  with  vertex  u  representing  all  the  nodes  in  one  side  of  the
original graph, and v representing all the vertices on the other side. The
number of edges given by c(u, v) corresponds exactly to the number of
edges crossing the corresponding cut in the original graph. We call this
algorithm the contraction algorithm.

f. Suppose that the contraction algorithm terminates with a multigraph

whose only vertices are u and v. Show that

.

g. Prove that if the contraction algorithm repeats

 times, then the
probability that at least one of the runs returns the minimum cut is at
least 1 − 1/|V|.

h. Give a detailed implementation of the contraction algorithm that

runs in O(V2) time.

i. Combine the previous parts and remove the assumption that the

minimum cut must be unique, to conclude that running the
contraction algorithm
O(V4 lg V) time and returns a minimum cut with probability at least 1
− 1/V.

 times yields an algorithm that runs in

Chapter notes

Ahuja,  Magnanti,  and  Orlin
[276],
Papadimitriou  and  Steiglitz  [353],  Tarjan  [429],  and  Williamson  [458]
are good references for network ﬂows and related algorithms. Schrijver
[399] has written an interesting review of historical developments in the
ﬁeld of network ﬂows.

[137],  Lawler

[7],  Even

The  Ford-Fulkerson  method  is  due  to  Ford  and  Fulkerson  [149],
who originated the formal study of many of the problems in the area of
network  ﬂow,  including  the  maximum-ﬂow  and  bipartite-matching
problems.  Many  early  implementations  of  the  Ford-Fulkerson  method
found augmenting paths using breadth-ﬁrst search. Edmonds and Karp
[132],  and  independently  Dinic  [119],  proved  that  this  strategy  yields  a
polynomial-time  algorithm.  A  related  idea,  that  of  using  “blocking
ﬂows,” was also ﬁrst developed by Dinic [119].

A  class  of  algorithms  known  as  push-relabel  algorithms,  due  to
Goldberg  [185]  and  Goldberg  and  Tarjan  [188],  takes  a  different
approach  from  the  Ford-Fulkerson  method.  Push-relabel  algorithms
allow ﬂow conservation to be violated at vertices other than the source
and  sink  as  they  execute.  Using  an  idea  ﬁrst  developed  by  Karzonov
[251], they allow a preﬂow in which the ﬂow into a vertex may exceed the
ﬂow out of the vertex. Such a vertex is said to be overﬂowing. Initially,
every edge leaving the source is ﬁlled to capacity, so that all neighbors
of the source are overﬂowing. In a push-relabel algorithm, each vertex is
assigned  an  integer  height.  An  overﬂowing  vertex  may  push  ﬂow  to  a
neighboring  vertex  to  which  it  has  a  residual  edge  provided  that  it  is
higher  than  the  neighbor.  If  all  residual  edges  from  an  overﬂowing
vertex  go  to  neighbors  with  equal  or  greater  heights,  then  the  vertex
may  increase  its  height.  Once  all  vertices  other  than  the  sink  are  no
longer  overﬂowing,  the  preﬂow  is  not  only  a  legal  ﬂow,  but  also  a
maximum ﬂow.

Goldberg and Tarjan [188] gave an O(V3)-time algorithm that uses a
queue  to  maintain  the  set  of  overﬂowing  vertices,  as  well  as  an
algorithm  that  uses  dynamic  trees  to  achieve  a  running  time  of  O(VE
lg(V2/E  +  2)).  Several  other  researchers  developed  improved  variants

and implementations [9, 10, 15, 86, 87, 255, 358], the fastest of which,
by King, Rao, and Tarjan [255], runs in O(VE logE/(V lg V) V) time.

Another  efﬁcient  algorithm  for  maximum  ﬂow,  by  Goldberg  and
Rao [187], runs in O (min{V2/3, E1/2} E lg (V2/E + 2) lg C) time, where
C  is  the  maximum  capacity  any  edge.  Orlin  [350]  gave  an  algorithm  in
the  same  spirit  as  this  algorithm  that  runs  in  O(VE  +  E31/16  lg2  V)
time. Combining it with the algorithm of King, Rao, and Tarjan results
in an O(VE)-time algorithm.

A  different  approach  to  maximum  ﬂows  and  related  problems  is  to
use  techniques  from  continuous  optimization  including  electrical  ﬂows
and interior-point methods. The ﬁrst breakthrough in this line of work
is  due  to  Madry  [308],  who  gave  an  Õ(E10/7)-time  algorithm  for  unit-
capacity  maximum  ﬂow  and  bipartite  maximum  matching.  (See
Problem 3-6 on page 73 for a deﬁnition of Õ.) There has been a series
of  papers  in  this  area  for  matchings,  maximum  ﬂows,  and  minimum-
cost  ﬂows.  The  fastest  algorithm  to  date  in  this  line  of  work  for
maximum ﬂow is due to Lee and Sidford [285], taking
 time.
If  the  capacities  are  not  too  large,  this  algorithm  is  faster  than  the
O(VE)-time algorithm mentioned above. Another algorithm, due to Liu
and Sidford [303] runs in Õ(E11/8C1/4) time, where C is the maximum
capacity of any edge. This algorithm does not run in polynomial time,
but for small enough capacities, it is faster than the previous ones.

In  practice,  push-relabel  algorithms  currently  dominate  algorithms
based  on  augmenting  paths,  continuous-optimization,  and  linear
programming for the maximum-ﬂow problem [88].

1 Recall from Section 20.1 that we represent an attribute f for edge (u, v) with the same style of
notation—(u, v).f—that we use for an attribute of any other object.

