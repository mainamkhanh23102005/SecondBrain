Introduction

Graph problems pervade computer science, and algorithms for working
with  them  are  fundamental  to  the  ﬁeld.  Hundreds  of  interesting
computational  problems  are  couched  in  terms  of  graphs.  This  part
touches on a few of the more signiﬁcant ones.

Chapter 20 shows how to represent a graph in a computer and then
discusses  algorithms  based  on  searching  a  graph  using  either  breadth-
ﬁrst search or depth-ﬁrst search. The chapter gives two applications of
depth-ﬁrst  search:  topologically  sorting  a  directed  acyclic  graph  and
decomposing a directed graph into its strongly connected components.

Chapter  21  describes  how  to  compute  a  minimum-weight  spanning
tree  of  a  graph:  the  least-weight  way  of  connecting  all  of  the  vertices
together  when  each  edge  has  an  associated  weight.  The  algorithms  for
computing  minimum  spanning  trees  serve  as  good  examples  of  greedy
algorithms (see Chapter 15).

Chapters 22 and 23 consider how to compute shortest paths between
vertices when each edge has an associated length or “weight.” Chapter

22  shows  how  to  ﬁnd  shortest  paths  from  a  given  source  vertex  to  all
other  vertices,  and  Chapter  23  examines  methods  to  compute  shortest
paths between every pair of vertices.

Chapter 24 shows how to compute a maximum ﬂow of material in a
ﬂow network, which is a directed graph having a speciﬁed source vertex
of  material,  a  speciﬁed  sink  vertex,  and  speciﬁed  capacities  for  the
amount  of  material  that  can  traverse  each  directed  edge.  This  general
problem  arises  in  many  forms,  and  a  good  algorithm  for  computing
maximum ﬂows can help solve a variety of related problems efﬁciently.

Finally, Chapter 25 explores matchings in bipartite graphs: methods
for  pairing  up  vertices  that  are  partitioned  into  two  sets  by  selecting
edges  that  go  between  the  sets.  Bipartite-matching  problems  model
several situations that arise in the real world. The chapter examines how
to  ﬁnd  a  matching  of  maximum  cardinality;  the  “stable-marriage
problem,”  which  has  the  highly  practical  application  of  matching
medical  residents  to  hospitals;  and  assignment  problems,  which
maximize the total weight of a bipartite matching.

When  we  characterize  the  running  time  of  a  graph  algorithm  on  a
given  graph  G  =  (V,  E),  we  usually  measure  the  size  of  the  input  in
terms of the number of vertices |V| and the number of edges |E| of the
graph. That is, we denote the size of the input with two parameters, not
just  one.  We  adopt  a  common  notational  convention  for  these
parameters.  Inside  asymptotic  notation  (such  as  O-notation  or  Θ-
notation), and only inside such notation, the symbol V denotes |V | and
the  symbol  E  denotes  |E|.  For  example,  we  might  say,  “the  algorithm
runs in O(VE) time,” meaning that the algorithm runs in O(|V| |E|) time.
This  convention  makes  the  running-time  formulas  easier  to  read,
without risk of ambiguity.

Another convention we adopt appears in pseudocode. We denote the
vertex  set  of  a  graph  G  by  G.V  and  its  edge  set  by  G.E.  That  is,  the
pseudocode views vertex and edge sets as attributes of a graph.

