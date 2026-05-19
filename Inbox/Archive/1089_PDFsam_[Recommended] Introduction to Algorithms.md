29        Linear Programming

Many  problems  take  the  form  of  maximizing  or  minimizing  an
objective, given limited resources and competing constraints. If you can
specify the objective as a linear function of certain variables, and if you
can specify the constraints on resources as equalities or inequalities on
those  variables,  then  you  have  a  linear-programming  problem.  Linear
programs  arise  in  a  variety  of  practical  applications.  We  begin  by
studying an application in electoral politics.

A political problem

Suppose that you are a politician trying to win an election. Your district
has  three  different  types  of  areas—urban,  suburban,  and  rural.  These
areas  have,  respectively,  100,000,  200,000,  and  50,000  registered  voters.
Although  not  all  the  registered  voters  actually  go  to  the  polls,  you
decide  that  to  govern  effectively,  you  would  like  at  least  half  the
registered  voters  in  each  of  the  three  regions  to  vote  for  you.  You  are
honorable  and  would  never  consider  supporting  policies  you  don’t
believe  in.  You  realize,  however,  that  certain  issues  may  be  more
effective  in  winning  votes  in  certain  places.  Your  primary  issues  are
preparing  for  a  zombie  apocalypse,  equipping  sharks  with  lasers,
building highways for ﬂying cars, and allowing dolphins to vote.

According  to  your  campaign  staff’s  research,  you  can  estimate  how
many votes you win or lose from each population segment by spending
$1,000  on  advertising  on  each  issue.  This  information  appears  in  the
table  of  Figure  29.1.  In  this  table,  each  entry  indicates  the  number  of

thousands of either urban, suburban, or rural voters who would be won
over by spending $1,000 on advertising in support of a particular issue.
Negative entries denote votes that would be lost. Your task is to ﬁgure
out the minimum amount of money that you need to spend in order to
win 50,000 urban votes, 100,000 suburban votes, and 25,000 rural votes.
You could, by trial and error, devise a strategy that wins the required
number  of  votes,  but  the  strategy  you  come  up  with  might  not  be  the
least  expensive  one.  For  example,  you  could  devote  $20,000  of
advertising  to  preparing  for  a  zombie  apocalypse,  $0  to  equipping
sharks  with  lasers,  $4,000  to  building  highways  for  ﬂying  cars,  and
$9,000  to  allowing  dolphins  to  vote.  In  this  case,  you  would  win  (20  ·
−2) + (0 · 8) + (4 · 0) + (9 · 10) = 50 thousand urban votes, (20 · 5) + (0 ·
2) + (4 · 0) + (9 · 0) = 100 thousand suburban votes, and (20 · 3) + (0 ·
−5) + (4 · 10) + (9 · −2) = 82 thousand rural votes. You would win the
exact  number  of  votes  desired  in  the  urban  and  suburban  areas  and
more  than  enough  votes  in  the  rural  area.  (In  fact,  according  to  your
model,  in  the  rural  area  you  would  receive  more  votes  than  there  are
voters.) In order to garner these votes, you would have paid for 20 + 0 +
4 + 9 = 33 thousand dollars of advertising.

Figure 29.1 The effects of policies on voters. Each entry describes the number of thousands of
urban,  suburban,  or  rural  voters  who  could  be  won  over  by  spending  $1,000  on  advertising
support of a policy on a particular issue. Negative entries denote votes that would be lost.

It’s natural to wonder whether this strategy is the best possible. That
is,  can  you  achieve  your  goals  while  spending  less  on  advertising?
Additional trial and error might help you to answer this question, but a
better approach is to formulate (or model) this question mathematically.
The  ﬁrst  step  is  to  decide  what  decisions  you  have  to  make  and  to
introduce  variables  that  capture  these  decisions.  Since  you  have  four
decisions, you introduce four decision variables:

x1 is the number of thousands of dollars spent on advertising on
preparing for a zombie apocalypse,
x2 is the number of thousands of dollars spent on advertising on
equipping sharks with lasers,
x3 is the number of thousands of dollars spent on advertising on
building highways for ﬂying cars, and
x4 is the number of thousands of dollars spent on advertising on
allowing dolphins to vote.

You then think about constraints, which are limits, or restrictions, on the
values  that  the  decision  variables  can  take.  You  can  write  the
requirement that you win at least 50,000 urban votes as

Similarly, you can write the requirements that you win at least 100,000
suburban votes and 25,000 rural votes as

and

Any  setting  of  the  variables  x1,  x2,  x3,  x4  that  satisﬁes  inequalities
(29.1)–(29.3) yields a strategy that wins a sufﬁcient number of each type
of vote.

Finally,  you  think  about  your  objective,  which  is  the  quantity  that
you wish to either minimize or maximize. In order to keep costs as small
as  possible,  you  would  like  to  minimize  the  amount  spent  on
advertising. That is, you want to minimize the expression

Although negative advertising often occurs in political campaigns, there
is no such thing as negative-cost advertising. Consequently, you require
that

Combining  inequalities  (29.1)–(29.3)  and  (29.5)  with  the  objective  of
minimizing  (29.4)  produces  what  is  known  as  a  “linear  program.”  We
can format this problem tabularly as

subject to

The solution to this linear program yields your optimal strategy.

The  remainder  of  this  chapter  covers  how  to  formulate  linear
programs  and  is  an  introduction  to  modeling  in  general.  Modeling
refers  to  the  general  process  of  converting  a  problem
into  a
mathematical form amenable to solution by an algorithm. Section 29.1
discusses  brieﬂy  the  algorithmic  aspects  of  linear  programming,
although  it  does  not  include  the  details  of  a  linear-programming
algorithm.  Throughout  this  book,  we  have  seen  ways  to  model
problems, such as by shortest paths and connectivity in a graph. When
modeling a problem as a linear program, you go through the steps used
in  this  political  example—identifying  the  decision  variables,  specifying
the  constraints,  and  formulating  the  objective  function.  In  order  to
model  a  problem  as  a  linear  program,  the  constraints  and  objectives
must  be  linear.  In  Section  29.2,  we  will  see  several  other  examples  of
modeling  via  linear  programs.  Section  29.3  discusses  duality,  an
important  concept  in  linear  programming  and  other  optimization
algorithms.

29.1    Linear programming formulations and algorithms

Linear programs take a particular form, which we will examine in this
section.  Multiple  algorithms  have  been  developed  to  solve  linear
programs. Some run in polynomial time, some do not, but they are all
too  complicated  to  show  here.  Instead,  we  will  give  an  example  that

demonstrates  some  ideas  behind  the  simplex  algorithm,  which  is
currently the most commonly deployed solution method.

General linear programs

In  the  general  linear-programming  problem,  we  wish  to  optimize  a
linear function subject to a set of linear inequalities. Given a set of real
numbers a1, a2, … , an and a set of variables x1, x2, … , xn, we deﬁne a
linear function f on those variables by

If b is a real number and f is a linear function, then the equation

f(x1, x2, … , xn) = b

is a linear equality and the inequalities

f(x1, x2, … , xn) ≤ b and f(x1, x2, … , xn) ≥ b

linear  equalities  or

are  linear  inequalities.  We  use  the  general  term  linear  constraints  to
denote  either
inequalities.  Linear
programming  does  not  allow  strict  inequalities.  Formally,  a  linear-
programming  problem
is  the  problem  of  either  minimizing  or
maximizing a linear function subject to a ﬁnite set of linear constraints.
If minimizing, we call the linear program a minimization linear program,
and  if  maximizing,  we  call  the  linear  program  a  maximization  linear
program.

linear

In order to discuss linear-programming algorithms and properties, it
will be helpful to use a standard notation for the input. By convention,
a maximization linear program takes as input n real numbers c1, c2, … ,
cn; m real numbers b1, b2, … , bm; and mn real numbers aij for i = 1, 2,
… , m and j = 1, 2, … , n.
The goal is to ﬁnd n real numbers x1, x2, … , xn that

subject to

We  call  expression  (29.11)  the  objective  function  and  the  n  +  m
inequalities in lines (29.12) and (29.13) the constraints. The n constraints
in  line  (29.13)  are  the  nonnegativity  constraints.  It  can  sometimes  be
more convenient to express a linear program in a more compact form.
If we create an m × n matrix A = (aij), an m-vector b = (bi), an n-vector
c = (cj), and an n-vector x = (xj), then we can rewrite the linear program
deﬁned in (29.11)–(29.13) as

subject to

In line (29.14), cTx is the inner product of two n-vectors. In inequality
(29.15), Ax is the m-vector that is the product of an m × n matrix and
an n-vector, and in inequality (29.16), x ≥ 0 means that each entry of the
vector  x  must  be  nonnegative.  We  call  this  representation  the  standard
form for a linear program, and we adopt the convention that A, b, and c
always have the dimensions given above.

The  standard  form  above  may  not  naturally  correspond  to  real-life
situations  you  are  trying  to  model.  For  example,  you  might  have
equality  constraints  or  variables  that  can  take  on  negative  values.
Exercises 29.1-6 and 29.1-7 ask you to show how to convert any linear
program into this standard form.

We  now  introduce  terminology  to  describe  solutions  to  linear
programs. We denote a particular setting of the values in a variable, say
x,  by  putting  a  bar  over  the  variable  name:  x.  If  x  satisﬁes  all  the
constraints, then it is a feasible solution, but if it fails to satisfy at least
one constraint, then it is an infeasible solution. We say that a solution x
has  objective  value  cTx.  A  feasible  solution  x  whose  objective  value  is
maximum over all feasible solutions is an optimal solution, and we call

its  objective  value  cTx  the  optimal  objective  value.  If  a  linear  program
has  no  feasible  solutions,  we  say  that  the  linear  program  is  infeasible,
and  otherwise,  it  is  feasible.  The  set  of  points  that  satisfy  all  the
constraints is the feasible region. If a linear program has some feasible
solutions  but  does  not  have  a  ﬁnite  optimal  objective  value,  then  the
feasible region is unbounded and so is the linear program. Exercise 29.1-
5  asks  you  to  show  that  a  linear  program  can  have  a  ﬁnite  optimal
objective value even if the feasible region is unbounded.

One  of  the  reasons  for  the  power  and  popularity  of  linear
programming  is  that  linear  programs  can,  in  general,  be  solved
efﬁciently.  There  are  two  classes  of  algorithms,  known  as  ellipsoid
algorithms and interior-point algorithms, that solve linear programs in
polynomial  time.  In  addition,  the  simplex  algorithm  is  widely  used.
Although it does not run in polynomial time in the worst case, it tends
to perform well in practice.

We  will  not  give  a  detailed  algorithm  for  linear  programming,  but
will  discuss  a  few  important  ideas.  First,  we  will  give  an  example  of
using  a  geometric  procedure  to  solve  a  two-variable  linear  program.
Although  this  example  does  not  immediately  generalize  to  an  efﬁcient
algorithm  for  larger  problems,  it  introduces  some  important  concepts
for linear programming and for optimization in general.

A two-variable linear program

Let us ﬁrst consider the following linear program with two variables:

subject to

Figure  29.2(a)  graphs  the  constraints
in  the  (x1,  x2)-Cartesian
coordinate  system.  The  feasible  region  in  the  two-dimensional  space
(highlighted  in  blue  in  the  ﬁgure)  is  convex.1  Conceptually,  you  could

evaluate  the  objective  function  x1  +  x2  at  each  point  in  the  feasible
region, and then identify a point that has the maximum objective value
as  an  optimal  solution.  For  this  example  (and  for  most  linear
programs),  however,  the  feasible  region  contains  an  inﬁnite  number  of
points, and so to solve this linear program, you need an efﬁcient way to
ﬁnd  a  point  that  achieves  the  maximum  objective  value  without
explicitly evaluating the objective function at every point in the feasible
region.

In two dimensions, you can optimize via a graphical procedure. The
set of points for which x1 + x2 = z, for any z, is a line with a slope of
−1.  Plotting  x1  +  x2  =  0  produces  the  line  with  slope  −1  through  the
origin, as in Figure 29.2(b). The intersection of this line and the feasible
region is the set of feasible solutions that have an objective value of 0.
In  this  case,  that  intersection  of  the  line  with  the  feasible  region  is  the
single  point  (0,  0).  More  generally,  for  any  value  z,  the  intersection  of
the  line  x1  +  x2  =  z  and  the  feasible  region  is  the  set  of  feasible
solutions that have objective value z. Figure 29.2(b) shows the lines x1 +
x2  =  0,  x1  +  x2  =  4,  and  x1  +  x2  =  8.  Because  the  feasible  region  in
Figure 29.2 is bounded, there must be some maximum value z for which
the  intersection  of  the  line  x1  +  x2  =  z  and  the  feasible  region  is
nonempty. Any point in the feasible region that maximizes x1 + x2 is an
optimal solution to the linear program, which in this case is the vertex
of the feasible region at x1 = 2 and x2 = 6, with objective value 8.

Figure 29.2 (a) The linear program given in (29.18)–(29.21). Each constraint is represented by a
line  and  a  direction.  The  intersection  of  the  constraints,  which  is  the  feasible  region,  is
highlighted in blue. (b) The red lines show, respectively, the points for which the objective value
is 0, 4, and 8. The optimal solution to the linear program is x1 = 2 and x2 = 6 with objective
value 8.

It  is  no  accident  that  an  optimal  solution  to  the  linear  program
occurs  at  a  vertex  of  the  feasible  region.  The  maximum  value  of  z  for
which the line x1 + x2 = z intersects the feasible region must be on the
boundary  of  the  feasible  region,  and  thus  the  intersection  of  this  line
with the boundary of the feasible region is either a single vertex or a line
segment.  If  the  intersection  is  a  single  vertex,  then  there  is  just  one
optimal  solution,  and  it  is  that  vertex.  If  the  intersection  is  a  line
segment, every point on that line segment must have the same objective
value.  In  particular,  both  endpoints  of  the  line  segment  are  optimal
solutions. Since each endpoint of a line segment is a vertex, there is an
optimal solution at a vertex in this case as well.

Although  you  cannot  easily  graph  linear  programs  with  more  than
two variables, the same intuition holds. If you have three variables, then
each constraint corresponds to a half-space in three-dimensional space.
The intersection of these half-spaces forms the feasible region. The set
of points for which the objective function obtains a given value z is now
a  plane  (assuming  no  degenerate  conditions).  If  all  coefﬁcients  of  the
objective  function  are  nonnegative,  and  if  the  origin  is  a  feasible
solution to the linear program, then as you move this plane away from

the  origin,  in  a  direction  normal  to  the  objective  function,  you  ﬁnd
points  of  increasing  objective  value.  (If  the  origin  is  not  feasible  or  if
some  coefﬁcients  in  the  objective  function  are  negative,  the  intuitive
picture  becomes  slightly  more  complicated.)  As  in  two  dimensions,
because the feasible region is convex, the set of points that achieve the
optimal  objective  value  must  include  a  vertex  of  the  feasible  region.
Similarly, if you have n variables, each constraint deﬁnes a half-space in
n-dimensional  space.  We  call  the  feasible  region  formed  by  the
intersection  of  these  half-spaces  a  simplex.  The  objective  function  is
now  a  hyperplane  and,  because  of  convexity,  an  optimal  solution  still
occurs  at  a  vertex  of  the  simplex.  Any  algorithm  for
linear
programming must also identify linear programs that have no solutions,
as well as linear programs that have no ﬁnite optimal solution.

The simplex algorithm takes as input a linear program and returns an
optimal solution. It starts at some vertex of the simplex and performs a
sequence of iterations. In each iteration, it moves along an edge of the
simplex  from  a  current  vertex  to  a  neighboring  vertex  whose  objective
value is no smaller than that of the current vertex (and usually is larger.)
The  simplex  algorithm  terminates  when  it  reaches  a  local  maximum,
which  is  a  vertex  from  which  all  neighboring  vertices  have  a  smaller
objective value. Because the feasible region is convex and the objective
function  is  linear,  this  local  optimum  is  actually  a  global  optimum.  In
Section  29.3,  we’ll  see  an  important  concept  called  “duality,”  which
we’ll use to prove that the solution returned by the simplex algorithm is
indeed optimal.

inputs,  however,

The  simplex  algorithm,  when  implemented  carefully,  often  solves
general  linear  programs  quickly  in  practice.  With  some  carefully
contrived
the  simplex  algorithm  can  require
exponential  time.  The  ﬁrst  polynomial-time  algorithm  for  linear
programming was the ellipsoid algorithm, which runs slowly in practice.
A  second  class  of  polynomial-time  algorithms  are  known  as  interior-
point methods. In contrast to the simplex algorithm, which moves along
the exterior of the feasible region and maintains a feasible solution that
is  a  vertex  of  the  simplex  at  each  iteration,  these  algorithms  move
through the interior of the feasible region. The intermediate solutions,
while  feasible,  are  not  necessarily  vertices  of  the  simplex,  but  the  ﬁnal

solution is a vertex. For large inputs, interior-point algorithms can run
as  fast  as,  and  sometimes  faster  than,  the  simplex  algorithm.  The
chapter notes point you to more information about these algorithms.

If  you  add  to  a  linear  program  the  additional  requirement  that  all
variables  take  on  integer  values,  you  have  an  integer  linear  program.
Exercise  34.5-3  on  page  1098  asks  you  to  show  that  just  ﬁnding  a
feasible solution to this problem is NP-hard. Since no polynomial-time
algorithms  are  known  for  any  NP-hard  problems,  there  is  no  known
polynomial-time algorithm for integer linear programming. In contrast,
a  general  linear-programming  problem  can  be  solved  in  polynomial
time.

Exercises

29.1-1
Consider the linear program

minimize −2x1 + 3x2

subject to

x1 + x2 = 7
x1 − 2x2 ≤ 4
x1 ≥ 0.

Give  three  feasible  solutions  to  this  linear  program.  What  is  the
objective value of each one?

29.1-2
Consider  the  following  linear  program,  which  has  a  nonpositivity
constraint:

minimize 2x1 + 7x2 + x3

subject to

x1

− x3 = 7

3x1 + x2

≥ 24

x2 ≥ 0
x3 ≤ 0.

Give  three  feasible  solutions  to  this  linear  program.  What  is  the
objective value of each one?

29.1-3
Show that the following linear program is infeasible:

maximize 3x1 − 2x2

subject to

2

x1 + x2 ≤
−2x1 − 2x2 ≤ −10
0.
x1, x2 ≥

29.1-4
Show that the following linear program is unbounded:

maximize x1 − x2

subject to

−2x1 + x2 ≤ −1
−x1 − 2x2 ≤ −2
x1, x2 ≥ 0.

29.1-5
Give an example of a linear program for which the feasible region is not
bounded, but the optimal objective value is ﬁnite.

29.1-6
Sometimes,  in  a  linear  program,  you  need  to  convert  constraints  from
one form to another.

a. Show how to convert an equality constraint into an equivalent set of

inequalities. That is, given a constraint
inequalities that will be satisﬁed if and only if

, give a set of
,

b. Show how to convert an inequality constraint

 into an

equality constraint and a nonnegativity constraint. You will need to
introduce an additional variable s, and use the constraint that s ≥ 0.

29.1-7
Explain how to convert a minimization linear program to an equivalent
maximization linear program, and argue that your new linear program
is equivalent to the original one.

29.1-8
In  the  political  problem  at  the  beginning  of  this  chapter,  there  are
feasible  solutions  that  correspond  to  winning  more  voters  than  there
actually  are  in  the  district.  For  example,  you  can  set  x2  to  200,  x3  to
200, and x1 = x4 = 0. That solution is feasible, yet it seems to say that
you  will  win  400,000  suburban  voters,  even  though  there  are  only
200,000  actual  suburban  voters.  What  constraints  can  you  add  to  the
linear program to ensure that you never seem to win more voters than
there  actually  are?  Even  if  you  don’t  add  these  constraints,  argue  that
the  optimal  solution  to  this  linear  program  can  never  win  more  voters
than there actually are in the district.

29.2    Formulating problems as linear programs

Linear  programming  has  many  applications.  Any  textbook  on
operations research is ﬁlled with examples of linear programming, and
linear  programming  has  become  a  standard  tool  taught  to  students  in
most  business  schools.  The  election  scenario  is  one  typical  example.
Here are two more examples:

An airline wishes to schedule its ﬂight crews. The Federal Aviation
Administration  imposes  several  constraints,  such  as  limiting  the
number  of  consecutive  hours  that  each  crew  member  can  work

and  insisting  that  a  particular  crew  work  only  on  one  model  of
aircraft  during  each  month.  The  airline  wants  to  schedule  crews
on all of its ﬂights using as few crew members as possible.

An  oil  company  wants  to  decide  where  to  drill  for  oil.  Siting  a
drill at a particular location has an associated cost and, based on
geological surveys, an expected payoff of some number of barrels
of  oil.  The  company  has  a  limited  budget  for  locating  new  drills
and wants to maximize the amount of oil it expects to ﬁnd, given
this budget.

Linear  programs  also  model  and  solve  graph  and  combinatorial
problems, such as those appearing in this book. We have already seen a
special case of linear programming used to solve systems of difference
constraints in Section 22.4. In this section, we’ll study how to formulate
several  graph  and  network-ﬂow  problems  as  linear  programs.  Section
35.4 uses linear programming as a tool to ﬁnd an approximate solution
to another graph problem.

Perhaps  the  most  important  aspect  of  linear  programming  is  to  be
able  to  recognize  when  you  can  formulate  a  problem  as  a  linear
program.  Once  you  cast  a  problem  as  a  polynomial-sized  linear
program, you can solve it in polynomial time by the ellipsoid algorithm
or
linear-programming  software
packages  can  solve  problems  efﬁciently,  so  that  once  the  problem  is  in
the form of a linear program, such a package can solve it.

interior-point  methods.  Several

We’ll  look  at  several  concrete  examples  of  linear-programming
problems. We start with two problems that we have already studied: the
single-source  shortest-paths  problem  from  Chapter  22  and  the
maximum-ﬂow  problem  from  Chapter  24.  We  then  describe  the
the  minimum-cost-ﬂow
minimum-cost-ﬂow  problem.
problem  has  a  polynomial-time  algorithm  that  is  not  based  on  linear
programming, we won’t describe the algorithm.) Finally, we describe the
multicommodity-ﬂow  problem,  for  which  the  only  known  polynomial-
time algorithm is based on linear programming.

(Although

When  we  solved  graph  problems  in  Part  VI,  we  used  attribute
notation,  such  as  v.d  and  (u,  v).f.  Linear  programs  typically  use
subscripted  variables  rather  than  objects  with  attached  attributes,

however.  Therefore,  when  we  express  variables  in  linear  programs,  we
indicate vertices and edges through subscripts. For example, we denote
the shortest-path weight for vertex v not by v.d but by dv, and we denote
the  ﬂow  from  vertex  u  to  vertex  v  not  by  (u,  v).f  but  by  fuv.  For
quantities that are given as inputs to problems, such as edge weights or
capacities, we continue to use notations such as w(u, v) and c(u, v).

Shortest paths

We  can  formulate  the  single-source  shortest-paths  problem  as  a  linear
program. We’ll focus on how to formulate the single-pair shortest-path
problem,  leaving  the  extension  to  the  more  general  single-source
shortest-paths problem as Exercise 29.2-2.

In  the  single-pair  shortest-path  problem,  the  input  is  a  weighted,
directed  graph  G  =  (V,  E),  with  weight  function  w  :  E  →  ℝ  mapping
edges to real-valued weights, a source vertex s, and destination vertex t.
The  goal  is  to  compute  the  value  dt,  which  is  the  weight  of  a  shortest
path from s to t. To express this problem as a linear program, you need
to  determine  a  set  of  variables  and  constraints  that  deﬁne  when  you
have a shortest path from s to t. The triangle inequality (Lemma 22.10
on page 633) gives dv ≤ du + w(u, v) for each edge (u, v) ∈ E. The source
vertex  initially  receives  a  value  ds  =  0,  which  never  changes.  Thus  the
following linear program expresses the shortest-path weight from s to t:

subject to

You might be surprised that this linear program maximizes an objective
function when it is supposed to compute shortest paths. Minimizing the
objective  function  would  be  a  mistake,  because  when  all  the  edge
weights are nonnegative, setting dv = 0 for all v ∈ V (recall that a bar
over  a  variable  name  denotes  a  speciﬁc  setting  of  the  variable’s  value)
would yield an optimal solution to the linear program without solving

the shortest-paths problem. Maximizing is the right thing to do because
an  optimal  solution  to  the  shortest-paths  problem  sets  each  dv  to  min
{du + w(u, v) : u ∈ V and (u, v) ∈ E}, so that dv is the largest value that
is  less  than  or  equal  to  all  of  the  values  in  the  set  {du  +  w(u,  v).
Therefore, it makes sense to maximize dv for all vertices v on a shortest
path from s to t subject to these constraints, and maximizing dt achieves
this goal.

This linear program has |V| variables dv, one for each vertex v ∈ V. It
also  has  |E|  +  1  constraints:  one  for  each  edge,  plus  the  additional
constraint  that  the  source  vertex’s  shortest-path  weight  always  has  the
value 0.

Maximum ﬂow

Next,  let’s  express  the  maximum-ﬂow  problem  as  a  linear  program.
Recall that the input is a directed graph G = (V, E) in which each edge
(u, v) ∈ E has a nonnegative capacity c(u, v) ≥ 0, and two distinguished
vertices: a source s and a sink t. As deﬁned in Section 24.1, a ﬂow is a
nonnegative  real-valued  function  f  :  V  ×  V  →  ℝ  that  satisﬁes  the
capacity  constraint  and  ﬂow  conservation.  A  maximum  ﬂow  is  a  ﬂow
that  satisﬁes  these  constraints  and  maximizes  the  ﬂow  value,  which  is
the  total  ﬂow  coming  out  of  the  source  minus  the  total  ﬂow  into  the
source. A ﬂow, therefore, satisﬁes linear constraints, and the value of a
ﬂow is a linear function. Recalling also that we assume that c(u, v) = 0 if
(u,  v)  ∉  E  and  that  there  are  no  antiparallel  edges,  the  maximum-ﬂow
problem can be expressed as a linear program:

subject to

This  linear  program  has  |V|2  variables,  corresponding  to  the  ﬂow
between each pair of vertices, and it has 2 |V|2 + |V| − 2 constraints.

It  is  usually  more  efﬁcient  to  solve  a  smaller-sized  linear  program.
The  linear  program  in  (29.25)–(29.28)  has,  for  ease  of  notation,  a  ﬂow
and capacity of 0 for each pair of vertices u, v with (u, v) ∉ E. It is more
efﬁcient  to  rewrite  the  linear  program  so  that  it  has  O(V  +  E)
constraints. Exercise 29.2-4 asks you to do so.

Minimum-cost ﬂow

In this section, we have used linear programming to solve problems for
which  we  already  knew  efﬁcient  algorithms.  In  fact,  an  efﬁcient
algorithm  designed  speciﬁcally  for  a  problem,  such  as  Dijkstra’s
algorithm  for  the  single-source  shortest-paths  problem,  will  often  be
more efﬁcient than linear programming, both in theory and in practice.

The  real  power  of  linear  programming  comes  from  the  ability  to
solve  new  problems.  Recall  the  problem  faced  by  the  politician  in  the
beginning of this chapter. The problem of obtaining a sufﬁcient number
of  votes,  while  not  spending  too  much  money,  is  not  solved  by  any  of
the algorithms that we have studied in this book, yet it can be solved by
linear programming. Books abound with such real-world problems that
linear programming can solve. Linear programming is also particularly
useful  for  solving  variants  of  problems  for  which  we  may  not  already
know of an efﬁcient algorithm.

Figure 29.3 (a) An example of a minimum-cost-ﬂow problem. Capacities are denoted by c and
costs by a. Vertex s is the source, and vertex t is the sink. The goal is to send 4 units of ﬂow from
s to t. (b) A solution to the minimum-cost ﬂow problem in which 4 units of ﬂow are sent from s
to t. For each edge, the ﬂow and capacity are written as ﬂow/capacity.

Consider, for example, the following generalization of the maximum-
ﬂow  problem.  Suppose  that,  in  addition  to  a  capacity  c(u,  v)  for  each
edge (u, v), you are given a real-valued cost a(u, v). As in the maximum-
ﬂow problem, assume that c(u, v) = 0 if (u, v) ∉ E and that there are no
antiparallel  edges.  If  you  send  fuv  units  of  ﬂow  over  edge  (u,  v),  you
incur  a  cost  of  a(u,  v)  ·  fuv.  You  are  also  given  a  ﬂow  demand  d.  You
wish to send d units of ﬂow from s to t while minimizing the total cost
∑(u,v)∈E a(u, v) · fuv incurred by the ﬂow. This problem is known as the
minimum-cost-ﬂow problem.

Figure 29.3(a) shows an example of the minimum-cost-ﬂow problem,
with  a  goal  of  sending  4  units  of  ﬂow  from  s  to  t  while  incurring  the
minimum  total  cost.  Any  particular  legal  ﬂow,  that  is,  a  function  f
satisfying  constraints
total  cost  of
∑(u,v)∈E a(u, v) · fuv. What is the particular 4-unit ﬂow that minimizes
this  cost?  Figure  29.3(b)  shows  an  optimal  solution,  with  total  cost
∑(u,v)∈E a(u, v) · fuv = (2 · 2) + (5 · 2) + (3 · 1) + (7 · 1) + (1 · 3) = 27.

(29.26)–(29.28),

incurs  a

There  are  polynomial-time  algorithms  speciﬁcally  designed  for  the
minimum-cost-ﬂow  problem,  but  they  are  beyond  the  scope  of  this
book.  The  minimum-cost-ﬂow  problem  can  be  expressed  as  a  linear
program, however. The linear program looks similar to the one for the
maximum-ﬂow problem with the additional constraint that the value of
the ﬂow must be exactly d units, and with the new objective function of
minimizing the cost:

subject to

Multicommodity ﬂow

As  a  ﬁnal  example,  let’s  consider  another  ﬂow  problem.  Suppose  that
the  Lucky  Puck  company  from  Section  24.1  decides  to  diversify  its
product line and ship not only hockey pucks, but also hockey sticks and
hockey  helmets.  Each  piece  of  equipment  is  manufactured  in  its  own
factory,  has  its  own  warehouse,  and  must  be  shipped,  each  day,  from
factory  to  warehouse.  The  sticks  are  manufactured  in  Vancouver  and
are  needed  in  Saskatoon,  and  the  helmets  are  manufactured  in
Edmonton  and  must  be  shipped  to  Regina.  The  capacity  of  the
shipping network does not change, however, and the different items, or
commodities, must share the same network.

This example is an instance of a multicommodity-ﬂow problem. The
input to this problem is once again a directed graph G = (V, E) in which
each  edge  (u,  v)  ∈  E  has  a  nonnegative  capacity  c(u,  v)  ≥  0.  As  in  the
maximum-ﬂow problem, implicitly assume that c(u, v) = 0 for (u, v) ∉ E
and  that  the  graph  has  no  antiparallel  edges.  In  addition,  there  are  k
different  commodities,  K1,  K2,  …  ,  Kk,  with  commodity  i  speciﬁed  by
the triple Ki = (si, ti, di). Here, vertex si is the source of commodity i,
vertex  ti  is  the  sink  of  commodity  i,  and  di  is  the  demand  for
commodity i, which is the desired ﬂow value for the commodity from si
to ti. We deﬁne a ﬂow for commodity i, denoted by fi, (so that fiuv is the
ﬂow  of  commodity  i  from  vertex  u  to  vertex  v)  to  be  a  real-valued
function  that  satisﬁes  the  ﬂow-conservation  and  capacity  constraints.
We  deﬁne  fuv,  the  aggregate  ﬂow,  to  be  the  sum  of  the  various
commodity ﬂows, so that
. The aggregate ﬂow on edge (u, v)
must be no more than the capacity of edge (u, v). This problem has no
objective  function:  the  question  is  to  determine  whether  such  a  ﬂow
exists.  Thus  the  linear  program  for  this  problem  has  a  “null”  objective
function:

The only known polynomial-time algorithm for this problem expresses
it as a linear program and then solves it with a polynomial-time linear-
programming algorithm.

Exercises

29.2-1
Write  out  explicitly  the  linear  program  corresponding  to  ﬁnding  the
shortest path from vertex s to vertex x in Figure 22.2(a) on page 609.

29.2-2
Given a graph G, write a linear program for the single-source shortest-
paths  problem.  The  solution  should  have  the  property  that  dv  is  the
shortest-path weight from the source vertex s to v for each vertex v ∈ V.

29.2-3
Write  out  explicitly  the  linear  program  corresponding  to  ﬁnding  the
maximum ﬂow in Figure 24.1(a).

29.2-4
Rewrite the linear program for maximum ﬂow (29.25)–(29.28) so that it
uses only O(V + E) constraints.

29.2-5
Write a linear program that, given a bipartite graph G = (V, E), solves
the maximum-bipartite-matching problem.

29.2-6

There  can  be  more  than  one  way  to  model  a  particular  problem  as  a
linear  program.  This  exercise  gives  an  alternative  formulation  for  the
maximum-ﬂow  problem.  Let  P  =  {P1,  P2,  …  ,  Pp}  be  the  set  of  all
possible  directed  simple  paths  from  source  s    to  sink  t.  Using  decision
variables x1, … , xp, where xi is the amount of ﬂow on path i, formulate
a  linear  program  for  the  maximum-ﬂow  problem.  What  is  an  upper
bound on p, the number of directed simple paths from s to t?

29.2-7
In  the  minimum-cost  multicommodity-ﬂow  problem,  the  input  is  a
directed  graph  G  =  (V,  E)  in  which  each  edge  (u,  v)  ∈  E  has  a
nonnegative  capacity  c(u,  v)  ≥  0  and  a  cost  a(u,  v).  As  in  the
multicommodity-ﬂow  problem,  there  are  k  different  commodities,  K1,
K2, … , Kk, with commodity i speciﬁed by the triple Ki = (si, ti, di). We
deﬁne the ﬂow fi for commodity i and the aggregate ﬂow fuv on edge (u,
v)  as  in  the  multicommodity-ﬂow  problem.  A  feasible  ﬂow  is  one  in
which  the  aggregate  ﬂow  on  each  edge  (u,  v)  is  no  more  than  the
capacity of edge (u, v). The cost of a ﬂow is ∑u,v∈E a(u, v) · fuv, and the
goal is to ﬁnd the feasible ﬂow of minimum cost. Express this problem
as a linear program.

29.3    Duality

We  will  now  introduce  a  powerful  concept  called  linear-programming
duality. In general, given a maximization problem, duality allows you to
formulate  a  related  minimization  problem  that  has  the  same  objective
value.  The  idea  of  duality  is  actually  more  general  than  linear
programming,  but  we  restrict  our  attention  to  linear  programming  in
this section.

Duality enables us to prove that a solution is indeed optimal. We saw
an example of duality in Chapter 24 with Theorem 24.6, the max-ﬂow
min-cut  theorem.  Suppose  that,  given  an  instance  of  a  maximum-ﬂow
problem, you ﬁnd a ﬂow f with value |f|. How do you know whether f is
a  maximum  ﬂow?  By  the  max-ﬂow  min-cut  theorem,  if  you  can  ﬁnd  a

cut  whose  value  is  also  |f|,  then  you  have  veriﬁed  that  f  is  indeed  a
maximum ﬂow. This relationship provides an example of duality: given
a  maximization  problem,  deﬁne  a  related  minimization  problem  such
that the two problems have the same optimal objective values.

Given a linear program in standard form in which the objective is to
maximize, let’s see how to formulate a dual linear program in which the
objective is to minimize and whose optimal value is identical to that of
the original linear program. When referring to dual linear programs, we
call the original linear program the primal.

Given the primal linear program

subject to

its dual is

subject to

Mechanically,  to  form  the  dual,  change  the  maximization  to  a
minimization, exchange the roles of coefﬁcients on the right-hand sides
and  in  the  objective  function,  and  replace  each  ≤  by  ≥.  Each  of  the  m
constraints  in  the  primal  corresponds  to  a  variable  yi  in  the  dual.
Likewise, each of the n constraints in the dual corresponds to a variable
xj  in  the  primal.  For  example,  consider  the  following  primal  linear
program:

subject to

Its dual is

subject to

Although  forming  the  dual  can  be  considered  a  mechanical
operation,  there  is  an  intuitive  explanation.  Consider  the  primal
maximization  problem  (29.37)–(29.41).  Each  constraint  gives  an  upper
bound  on  the  objective  function.  In  addition,  if  you  take  one  or  more
constraints and add together nonnegative multiples of them, you get a
valid  constraint.  For  example,  you  can  add  constraints  (29.38)  and
(29.39)  to  obtain  the  constraint  3x1  +  3x2  +  8x3  ≤  54.  Any  feasible
solution  to  the  primal  must  satisfy  this  new  constraint,  but  there  is
something  else  interesting  about  it.  Comparing  this  new  constraint  to
the  objective  function  (29.37),  you  can  see  that  for  each  variable,  the
corresponding  coefﬁcient  is  at  least  as  large  as  the  coefﬁcient  in  the
objective  function.  Thus,  since  the  variables  x1,  x2  and  x3  are
nonnegative, we have that

3x1 + x2 + 4x3 ≤ 3x1 + 3x2 + 8x3 ≤ 54,

and  so  the  solution  value  to  the  primal  is  at  most  54.  In  other  words,
adding these two constraints together has generated an upper bound on
the objective value.

In  general,  for  any  nonnegative  multipliers  y1,  y2,  and  y3,  you  can

generate a constraint

y1(x1+x2+3x3)+y2(2x1+2x2+5x3)+y3(4x1+x2+2x3)
30y1+24y2+36y3

≤

from the primal constraints or, by distributing and regrouping,

(y1+2y2+4y3)x1+(y1+2y2+y3)x2+(3y1+5y2+2y3)x3
30y1+24y2+36y3.

≤

Now,  as  long  as  this  constraint  has  coefﬁcients  of  x1,  x2,  and  x3  that
are  at  least  their  objective-function  coefﬁcients,  it  is  a  valid  upper
bound. That is, as long as

y1 + 2y2 + 4y3 ≥ 3,
y1 + 2y2 + y3
≥ 1,
3y1 + 5y2 + 2y3 ≥ 4,

you have a valid upper bound of 30y1+24y2+36y3. The multipliers y1,
y2, and y3 must be nonnegative, because otherwise you cannot combine
the  inequalities.  Of  course,  you  would  like  the  upper  bound  to  be  as
small as possible, and so you want to choose y to minimize 30y1 + 24y2
+ 36y3. Observe that we have just described the dual linear program as
the problem of ﬁnding the smallest possible upper bound on the primal.
We’ll formalize this idea and show in Theorem 29.4 that, if the linear
program and its dual are feasible and bounded, then the optimal value
of the dual linear program is always equal to the optimal value of the
primal linear program. We begin by demonstrating weak duality, which
states that any feasible solution to the primal linear program has a value
no greater than that of any feasible solution to the dual linear program.

Lemma 29.1 (Weak linear-programming duality)
Let x be any feasible solution to the primal linear program in (29.31)–
(29.33), and let ӯ be any feasible solution to its dual linear program in
(29.34)–(29.36). Then

Proof   We have

Corollary 29.2
Let  x  be  a  feasible  solution  to  the  primal  linear  program  in  (29.31)–
(29.33),  and  let  ӯ  be  a  feasible  solution  to  its  dual  linear  program  in
(29.34)–(29.36). If

▪

then  x  and  ӯ  are  optimal  solutions  to  the  primal  and  dual  linear
programs, respectively.

Proof   By Lemma 29.1, the objective value of a feasible solution to the
primal cannot exceed that of a feasible solution to the dual. The primal
linear  program
is  a
minimization problem. Thus, if feasible solutions x and ӯ have the same
objective value, neither can be improved.

is  a  maximization  problem  and  the  dual

▪

We  now  show  that,  at  optimality,  the  primal  and  dual  objective
values  are  indeed  equal.  To  prove  linear  programming  duality,  we  will
require  one  lemma  from  linear  algebra,  known  as  Farkas’s  lemma,  the
proof of which Problem 29-4 asks you to provide. Farkas’s lemma can
take several forms, each of which is about when a set of linear equalities
has  a  solution.  In  stating  the  lemma,  we  use  m  +  1  as  a  dimension
because it matches our use below.

Lemma 29.3 (Farkas’s lemma)
Given  M  ∈  ℝ
statements is true:

(m+1)×n  and  g  ∈  ℝ

m+1,  exactly  one  of  the  following

1. There exists v ∈ ℝ

2. There exists w ∈ ℝ

of all zeros), and wTg < 0.

n such that Mv ≤ g,
m+1 such that w ≥ 0, wTM = 0 (an n-vector

▪

the  primal

Theorem 29.4 (Linear-programming duality)
Given
its
in
corresponding dual in (29.34)–(29.36), if both are feasible and bounded,
then for optimal solutions x* and y*, we have cTx* = bTy*.

(29.31)–(29.33)  and

linear  program

Proof      Let  μ  =  bTy*  be  the  optimal  value  of  the  dual  linear  program
given  in  (29.34)–(29.36).  Consider  an  augmented  set  of  primal
constraints  in  which  we  add  a  constraint  to  (29.31)–(29.33)  that  the
objective value is at least μ. We write out this augmented primal as

We can multiply (29.48) through by −1 and rewrite (29.47)–(29.48) as

Here,
denotes an (m + 1)-vector.

  denotes  an  (m+1)×n  matrix,  x  is  an  n-vector,  and

We  claim  that  if  there  is  a  feasible  solution  x  to  the  augmented
primal, then the theorem is proved. To establish this claim, observe that
x  is  also  a  feasible  solution  to  the  original  primal  and  that  it  has
objective value at least μ. We can then apply Lemma 29.1, which states
that the objective value of the primal is at most μ, to complete the proof
of the theorem.

It  therefore  remains  to  show  that  the  augmented  primal  has  a
feasible  solution.  Suppose,  for  the  purpose  of  contradiction,  that  the
n
augmented  primal  is  infeasible,  which  means  that  there  is  no  v  ∈  ℝ

such that
inequalty (29.49) with

. We can apply Farkas’s lemma, Lemma 29.3, to

Because  the  augmented  primal  is  infeasible,  condition  1  of  Farkas’s
lemma  does  not  hold.  Therefore,  condition  2  must  apply,  so  that  there
m+1 such that w ≥ 0, wTM = 0, and wTg < 0. Let’s
must exist a w ∈ ℝ
m and λ ∈ ℝ, where ӯ ≥ 0 and λ ≥ 0.

write w as
Substituting for w, M, and g in condition 2 gives

 for some ӯ ∈ ℝ

Unpacking the matrix notation gives

We  now  show  that  the  requirements
in  (29.50)  contradict  the
assumption  that  μ  is  the  optimal  solution  value  for  the  dual  linear
program. We consider two cases.

The ﬁrst case is when λ = 0. In this case, (29.50) simpliﬁes to

We’ll  now  construct  a  dual  feasible  solution  y′  with  an  objective  value
smaller than bTy*. Set y′ = y* + ϵ ӯ, for any ϵ > 0. Since

y′

TA = (y* + ϵ ӯ)TA
TA
= y*TA + ϵ ӯ
= y*TA
≥ cT

(by (29.51))

(because y* is feasible),

y′ is feasible. Now consider the objective value
bTy′

= bT(y* + ϵ ӯ)

= bTy* + ϵ bT
< bTy*,

ӯ

ӯ < 0 (since both ӯ

Tb =
where the last inequality follows because ϵ > 0 and, by (29.51), ӯ
bT
ӯ are the inner product of b and ӯ), and
so  their  product  is  negative.  Thus  we  have  a  feasible  dual  solution  of
value less than μ, which contradicts μ being the optimal objective value.
We now consider the second case, where λ > 0. In this case, we can

Tb and bT

take (29.50) and divide through by λ to obtain

Now set y′ = ӯ/λ in (29.52), giving
TA = cT and y′
y′
Thus, y′ is a feasible dual solution with objective value strictly less than
μ,  a  contradiction.  We  conclude  that  the  augmented  primal  has  a
feasible solution, and the theorem is proved.

Tb < μ.

▪

Fundamental theorem of linear programming

We conclude this chapter by stating the fundamental theorem of linear
programming, which extends Theorem 29.4 to the cases when the linear
program may be either feasible or unbounded. Exercise 29.3-8 asks you
to provide the proof.

Theorem 29.5 (Fundamental theorem of linear programming)
Any linear program, given in standard form, either

1. has an optimal solution with a ﬁnite objective value,

2. is infeasible, or

3. is unbounded.

▪

Exercises

29.3-1
Formulate  the  dual  of  the  linear  program  given  in  lines  (29.6)–(29.10)
on page 852.

29.3-2
You  have  a  linear  program  that  is  not  in  standard  form.  You  could
produce  the  dual  by  ﬁrst  converting  it  to  standard  form,  and  then
taking the dual. It would be more convenient, however, to produce the
dual  directly.  Explain  how  to  directly  take  the  dual  of  an  arbitrary
linear program.

29.3-3
Write down the dual of the maximum-ﬂow linear program, as given in
lines  (29.25)–(29.28)  on  page  862.  Explain  how  to  interpret  this
formulation as a minimum-cut problem.

29.3-4
Write down the dual of the minimum-cost-ﬂow linear program, as given
in  lines  (29.29)–(29.30)  on  page  864.  Explain  how  to  interpret  this
problem in terms of graphs and ﬂows.

29.3-5
Show that the dual of the dual of a linear program is the primal linear
program.

29.3-6
Which result from Chapter 24 can be interpreted as weak duality for the
maximum-ﬂow problem?

29.3-7
Consider the following 1-variable primal linear program:

maximize tx
subject to

rx ≤ s

x ≥ 0,

where r, s, and t are arbitrary real numbers. State for which values of r,
s, and t you can assert that

1. Both  the  primal  linear  program  and  its  dual  have  optimal

solutions with ﬁnite objective values.

2. The primal is feasible, but the dual is infeasible.

3. The dual is feasible, but the primal is infeasible.

4. Neither the primal nor the dual is feasible.

29.3-8
Prove the fundamental theorem of linear programming, Theorem 29.5.

Problems

29-1     Linear-inequality feasibility
Given  a  set  of  m  linear  inequalities  on  n  variables  x1,  x2,  …  ,  xn,  the
linear-inequality feasibility problem asks whether there is a setting of the
variables that simultaneously satisﬁes each of the inequalities.

a. Given an algorithm for the linear-programming problem, show how
to use it to solve a linear-inequality feasibility problem. The number
of variables and constraints that you use in the linear-programming
problem should be polynomial in n and m.

b. Given an algorithm for the linear-inequality feasibility problem, show
how to use it to solve a linear-programming problem. The number of
variables and linear inequalities that you use in the linear-inequality
feasibility problem should be polynomial in n and m, the number of
variables and constraints in the linear program.

29-2     Complementary slackness
Complementary slackness describes a relationship between the values of
primal  variables  and  dual  constraints  and  between  the  values  of  dual
variables  and  primal  constraints.  Let  x  be  a  feasible  solution  to  the

primal  linear  program  given  in  (29.31)–(29.33),  and  let  ӯ  be  a  feasible
solution  to  the  dual
in  (29.34)–(29.36).
Complementary  slackness  states  that  the  following  conditions  are
necessary and sufﬁcient for x and ӯ to be optimal:

linear  program  given

and

a. Verify that complementary slackness holds for the linear program in

lines (29.37)–(29.41).

b. Prove that complementary slackness holds for any primal linear

program and its corresponding dual.

c. Prove that a feasible solution x to a primal linear program given in
lines (29.31)–(29.33) is optimal if and only if there exist values ӯ =
(ӯ1, ӯ2, … , ӯm) such that

1. ӯ  is  a  feasible  solution  to  the  dual  linear  program  given  in

(29.34)–(29.36),

2.

 for all j such that xj > 0, and

3. ӯi = 0 for all i such that

.

integer

linear-programming  problem

29-3     Integer linear programming
linear-programming
An
problem with the additional constraint that the variables x must take on
integer values. Exercise 34.5-3 on page 1098 shows that just determining
whether  an  integer  linear  program  has  a  feasible  solution  is  NP-hard,
which means that there is no known polynomial-time algorithm for this
problem.

is  a

a. Show that weak duality (Lemma 29.1) holds for an integer linear

program.

b. Show that duality (Theorem 29.4) does not always hold for an integer

linear program.

c. Given a primal linear program in standard form, let P be the optimal

objective value for the primal linear program, D be the optimal
objective value for its dual, IP be the optimal objective value for the
integer version of the primal (that is, the primal with the added
constraint that the variables take on integer values), and ID be the
optimal objective value for the integer version of the dual. Assuming
that both the primal integer program and the dual integer program
are feasible and bounded, show that

IP ≤ P = D ≤ ID.

29-4     Farkas’s lemma
Prove Farkas’s lemma, Lemma 29.3.

29-5     Minimum-cost circulation

This  problem  considers  a  variant  of  the  minimum-cost-ﬂow  problem
from Section 29.2 in which there is no demand, source, or sink. Instead,
the  input,  as  before,  contains  a  ﬂow  network,  capacity  constraints  c(u,
v),  and  edge  costs  a(u,  v).  A  ﬂow  is  feasible  if  it  satisﬁes  the  capacity
constraint on every edge and ﬂow conservation at every vertex. The goal
is  to  ﬁnd,  among  all  feasible  ﬂows,  the  one  of  minimum  cost.  We  call
this problem the minimum-cost-circulation problem.

a. Formulate the minimum-cost-circulation problem as a linear

program.

b. Suppose that for all edges (u, v) ∈ E, we have a(u, v) > 0. What does
an optimal solution to the minimum-cost-circulation problem look
like?

c. Formulate the maximum-ﬂow problem as a minimum-cost-circulation

problem linear program. That is, given a maximum-ﬂow problem
instance G = (V, E) with source s, sink t and edge capacities c, create a
minimum-cost-circulation problem by giving a (possibly different)
network G′ = (V′, E′) with edge capacities c′ and edge costs a′ such

that you can derive a solution to the maximum-ﬂow problem from a
solution to the minimum-cost-circulation problem.

d. Formulate the single-source shortest-path problem as a minimum-

cost-circulation problem linear program.

Chapter notes

This chapter only begins to study the wide ﬁeld of linear programming.
A  number  of  books  are  devoted  exclusively  to  linear  programming,
including  those  by  Chvátal  [94],  Gass  [178],  Karloff  [246],  Schrijver
[398], and Vanderbei [444]. Many other books give a good coverage of
linear  programming,  including  those  by  Papadimitriou  and  Steiglitz
[353] and Ahuja, Magnanti, and Orlin [7]. The coverage in this chapter
draws on the approach taken by Chvátal.

The  simplex  algorithm  for  linear  programming  was  invented  by  G.
Dantzig in 1947. Shortly after, researchers discovered how to formulate
a number of problems in a variety of ﬁelds as linear programs and solve
them  with  the  simplex  algorithm.  As  a  result,  applications  of  linear
programming ﬂourished, along with several algorithms. Variants of the
simplex algorithm remain the most popular methods for solving linear-
programming  problems.  This  history  appears  in  a  number  of  places,
including the notes in [94] and [246].

The ellipsoid algorithm was the ﬁrst polynomial-time algorithm for
linear programming and is due to L. G. Khachian in 1979. It was based
on  earlier  work  by  N.  Z.  Shor,  D.  B.  Judin,  and  A.  S.  Nemirovskii.
Grötschel, Lovász, and Schrijver [201] describe how to use the ellipsoid
algorithm to solve a variety of problems in combinatorial optimization.
To date, the ellipsoid algorithm does not appear to be competitive with
the simplex algorithm in practice.

Karmarkar’s  paper  [247]  includes  a  description  of  the  ﬁrst  interior-
point  algorithm.  Many  subsequent  researchers  designed  interior-point
algorithms.  Good  surveys  appear  in  the  article  of  Goldfarb  and  Todd
[189] and the book by Ye [463].

Analysis  of  the  simplex  algorithm  remains  an  active  area  of
research. V. Klee and G. J. Minty constructed an example on which the

simplex  algorithm  runs  through  2n  −  1  iterations.  The  simplex
algorithm usually performs well in practice, and many researchers have
tried  to  give  theoretical  justiﬁcation  for  this  empirical  observation.  A
line  of  research  begun  by  K.  H.  Borgwardt,  and  carried  on  by  many
others, shows that under certain probabilistic assumptions on the input,
the simplex algorithm converges in expected polynomial time. Spielman
and  Teng  [421]  made  progress  in  this  area,  introducing  the  “smoothed
analysis of algorithms” and applying it to the simplex algorithm.

The  simplex  algorithm  is  known  to  run  efﬁciently  in  certain  special
cases. Particularly noteworthy is the network-simplex algorithm, which
is  the  simplex  algorithm,  specialized  to  network-ﬂow  problems.  For
certain network problems, including the shortest-paths, maximum-ﬂow,
and  minimum-cost-ﬂow  problems,  variants  of  the  network-simplex
algorithm run in polynomial time. See, for example, the article by Orlin
[349] and the citations therein.

1  An  intuitive  deﬁnition  of  a  convex  region  is  that  it  fulﬁlls  the  requirement  that  for  any  two
points in the region, all points on a line segment between them are also in the region.

