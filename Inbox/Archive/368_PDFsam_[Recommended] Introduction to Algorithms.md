11        Hash Tables

Many  applications  require  a  dynamic  set  that  supports  only  the
dictionary operations INSERT, SEARCH, and DELETE. For example,
a compiler that translates a programming language maintains a symbol
table,  in  which  the  keys  of  elements  are  arbitrary  character  strings
corresponding to identiﬁers in the language. A hash table is an effective
data structure for implementing dictionaries. Although searching for an
element in a hash table can take as long as searching for an element in a
linked list—Θ(n) time in the worst case—in practice, hashing performs
extremely  well.  Under  reasonable  assumptions,  the  average  time  to
search  for  an  element  in  a  hash  table  is  O(1).  Indeed,  the  built-in
dictionaries of Python are implemented with hash tables.

A  hash  table  generalizes  the  simpler  notion  of  an  ordinary  array.
Directly addressing into an ordinary array takes advantage of the O(1)
access  time  for  any  array  element.  Section  11.1  discusses  direct
addressing in more detail. To use direct addressing, you must be able to
allocate an array that contains a position for every possible key.

When the number of keys actually stored is small relative to the total
number of possible keys, hash tables become an effective alternative to
directly addressing an array, since a hash table typically uses an array of
size  proportional  to  the  number  of  keys  actually  stored.  Instead  of
using  the  key  as  an  array  index  directly,  we  compute  the  array  index
from  the  key.  Section  11.2  presents  the  main  ideas,  focusing  on
“chaining” as a way to handle “collisions,” in which more than one key
maps  to  the  same  array  index.  Section  11.3  describes  how  to  compute
array  indices  from  keys  using  hash  functions.  We  present  and  analyze

several  variations  on  the  basic  theme.  Section  11.4  looks  at  “open
addressing,”  which  is  another  way  to  deal  with  collisions.  The  bottom
line is that hashing is an extremely effective and practical technique: the
basic  dictionary  operations  require  only  O(1)  time  on  the  average.
Section  11.5  discusses  the  hierarchical  memory  systems  of  modern
computer  systems  have  and  illustrates  how  to  design  hash  tables  that
work well in such systems.

11.1    Direct-address tables

Direct  addressing  is  a  simple  technique  that  works  well  when  the
universe  U  of  keys  is  reasonably  small.  Suppose  that  an  application
needs  a  dynamic  set  in  which  each  element  has  a  distinct  key  drawn
from the universe U = {0, 1, …, m − 1}, where m is not too large.

To represent the dynamic set, you can use an array, or direct-address
table,  denoted  by  T[0  :  m  −  1],  in  which  each  position,  or  slot,
corresponds  to  a  key  in  the  universe  U.  Figure  11.1  illustrates  this
approach.  Slot  k  points  to  an  element  in  the  set  with  key  k.  If  the  set
contains no element with key k, then T[k] = NIL.

The

dictionary

operations  DIRECT-ADDRESS-SEARCH,
DIRECT-ADDRESS-INSERT,  and  DIRECT-ADDRESS-DELETE
on  the  following  page  are  trivial  to  implement.  Each  takes  only  O(1)
time.

For  some  applications,  the  direct-address  table  itself  can  hold  the
elements  in  the  dynamic  set.  That  is,  rather  than  storing  an  element’s
key  and  satellite  data  in  an  object  external  to  the  direct-address  table,
with  a  pointer  from  a  slot  in  the  table  to  the  object,  save  space  by
storing  the  object  directly  in  the  slot.  To  indicate  an  empty  slot,  use  a
special key. Then again, why store the key of the object at all? The index
of  the  object  is  its  key!  Of  course,  then  you’d  need  some  way  to  tell
whether slots are empty.

Figure  11.1  How  to  implement  a  dynamic  set  by  a  direct-address  table  T.  Each  key  in  the
universe  U  =  {0,  1,  …,  9}  corresponds  to  an  index  into  the  table.  The  set  K  =  {2,  3,  5,  8}  of
actual keys determines the slots in the table that contain pointers to elements. The other slots, in
blue, contain NIL.

DIRECT-ADDRESS-SEARCH(T, k)
1return T[k]

DIRECT-ADDRESS-INSERT(T, x)
1T[x.key] = x

DIRECT-ADDRESS-DELETE(T, x)
1T[x.key] = NIL

Exercises

11.1-1
A dynamic set S is represented by a direct-address table T of length m.
Describe a procedure that ﬁnds the maximum element of S. What is the
worst-case performance of your procedure?

11.1-2
A bit vector is simply an array of bits (each either 0 or 1). A bit vector
of length m takes much less space than an array of m pointers. Describe

how to use a bit vector to represent a dynamic set of distinct elements
drawn  from  the  set  {0,  1,  …,  m  −  1}  and  with  no  satellite  data.
Dictionary operations should run in O(1) time.

11.1-3
Suggest  how  to  implement  a  direct-address  table  in  which  the  keys  of
stored  elements  do  not  need  to  be  distinct  and  the  elements  can  have
satellite data. All three dictionary operations (INSERT, DELETE, and
SEARCH)  should  run  in  O(1)  time.  (Don’t  forget  that  DELETE  takes
as an argument a pointer to an object to be deleted, not a key.)

★ 11.1-4
Suppose  that  you  want  to  implement  a  dictionary  by  using  direct
addressing  on  a  huge  array.  That  is,  if  the  array  size  is  m  and  the
dictionary contains at most n elements at any one time, then m ≫ n. At
the  start,  the  array  entries  may  contain  garbage,  and  initializing  the
entire  array  is  impractical  because  of  its  size.  Describe  a  scheme  for
implementing a direct-address dictionary on a huge array. Each stored
object  should  use  O(1)  space;  the  operations  SEARCH,  INSERT,  and
DELETE should take O(1) time each; and initializing the data structure
should take O(1) time. (Hint: Use an additional array, treated somewhat
like  a  stack  whose  size  is  the  number  of  keys  actually  stored  in  the
dictionary, to help determine whether a given entry in the huge array is
valid or not.)

11.2    Hash tables

The downside of direct addressing is apparent: if the universe U is large
or  inﬁnite,  storing  a  table  T  of  size  |U|  may  be  impractical,  or  even
impossible,  given  the  memory  available  on  a  typical  computer.
Furthermore, the set K of keys actually stored may be so small relative
to U that most of the space allocated for T would be wasted.

When the set K of keys stored in a dictionary is much smaller than
the  universe  U  of  all  possible  keys,  a  hash  table  requires  much  less
storage than a direct-address table. Speciﬁcally, the storage requirement

reduces  to  Θ(|K|)  while  maintaining  the  beneﬁt  that  searching  for  an
element in the hash table still requires only O(1) time. The catch is that
this bound is for the average-case time,1 whereas for direct addressing it
holds for the worst-case time.

With direct addressing, an element with key k is stored in slot k, but
with hashing, we use a hash function h to compute the slot number from
the key k, so that the element goes into slot h(k). The hash function h
maps the universe U of keys into the slots of a hash table T[0 : m − 1]:

h : U → {0, 1, …, m − 1},
where the size m of the hash table is typically much less than |U|. We say
that an element with key k hashes to slot h(k), and we also say that h(k)
is  the  hash  value  of  key  k.  Figure  11.2  illustrates  the  basic  idea.  The
hash  function  reduces  the  range  of  array  indices  and  hence  the  size  of
the array. Instead of a size of |U|, the array can have size m. An example
of a simple, but not particularly good, hash function is h(k) = k mod m.
There is one hitch, namely that two keys may hash to the same slot.
We  call  this  situation  a  collision.  Fortunately,  there  are  effective
techniques for resolving the conﬂict created by collisions.

Of  course,  the  ideal  solution  is  to  avoid  collisions  altogether.  We
might  try  to  achieve  this  goal  by  choosing  a  suitable  hash  function  h.
One idea is to make h appear to be “random,” thus avoiding collisions
or at least minimizing their number. The very term “to hash,” evoking
images  of  random  mixing  and  chopping,  captures  the  spirit  of  this
approach. (Of course, a hash function h must be deterministic in that a
given input k must always produce the same output h(k).) Because |U| >
m,  however,  there  must  be  at  least  two  keys  that  have  the  same  hash
value, and avoiding collisions altogether is impossible. Thus, although a
well-designed, “random”-looking hash function can reduce the number
of collisions, we still need a method for resolving the collisions that do
occur.

Figure  11.2  Using  a  hash  function  h  to  map  keys  to  hash-table  slots.  Because  keys  k2  and  k5
map to the same slot, they collide.

The  remainder  of  this  section  ﬁrst  presents  a  deﬁnition  of
“independent  uniform  hashing,”  which  captures  the  simplest  notion  of
what it means for a hash function to be “random.” It then presents and
analyzes  the  simplest  collision  resolution  technique,  called  chaining.
Section  11.4  introduces  an  alternative  method  for  resolving  collisions,
called open addressing.

Independent uniform hashing

An “ideal” hashing function h would have, for each possible input k in
the  domain  U,  an  output  h(k)  that  is  an  element  randomly  and
independently chosen uniformly from the range {0, 1, …, m − 1}. Once
a value h(k) is randomly chosen, each subsequent call to h with the same
input k yields the same output h(k).

We  call  such  an  ideal  hash  function  an  independent  uniform  hash
function. Such a function is also often called a random oracle [43]. When
hash  tables  are  implemented  with  an  independent  uniform  hash
function, we say we are using independent uniform hashing.

Independent uniform hashing is an ideal theoretical abstraction, but
it  is  not  something  that  can  reasonably  be  implemented  in  practice.
Nonetheless,  we’ll  analyze  the  efﬁciency  of  hashing  under  the

assumption  of  independent  uniform  hashing  and  then  present  ways  of
achieving useful practical approximations to this ideal.

Figure  11.3  Collision  resolution  by  chaining.  Each  nonempty  hash-table  slot  T[j]  points  to  a
linked list of all the keys whose hash value is j. For example, h(k1) = h(k4) and h(k5) = h(k2) =
h(k7).  The  list  can  be  either  singly  or  doubly  linked.  We  show  it  as  doubly  linked  because
deletion may be faster that way when the deletion procedure knows which list element (not just
which key) is to be deleted.

Collision resolution by chaining

At  a  high  level,  you  can  think  of  hashing  with  chaining  as  a
nonrecursive form of divide-and-conquer: the input set of n elements is
divided randomly into m subsets, each of approximate size n/m. A hash
function determines which subset an element belongs to. Each subset is
managed independently as a list.

Figure  11.3  shows  the  idea  behind  chaining:  each  nonempty  slot
points to a linked list, and all the elements that hash to the same slot go
into that slot’s linked list. Slot j contains a pointer to the head of the list
of all stored elements with hash value j. If there are no such elements,
then slot j contains NIL.

When  collisions  are  resolved  by  chaining,  the  dictionary  operations
are  straightforward  to  implement.  They  appear  on  the  next  page  and
use the linked-list procedures from Section 10.2. The worst-case running
time for insertion is O(1). The insertion procedure is fast in part because

it assumes that the element x being inserted is not already present in the
table. To enforce this assumption, you can search (at additional cost) for
an element whose key is x.key before inserting. For searching, the worst-
case running time is proportional to the length of the list. (We’ll analyze
this operation more closely below.) Deletion takes O(1) time if the lists
are  doubly  linked,  as  in  Figure  11.3.  (Since  CHAINED-HASH-
DELETE  takes  as  input  an  element  x  and  not  its  key  k,  no  search  is
needed. If the hash table supports deletion, then its linked lists should
be doubly linked in order to delete an item quickly. If the lists were only
singly  linked,  then  by  Exercise  10.2-1,  deletion  could  take  time
proportional  to  the  length  of  the  list.  With  singly  linked  lists,  both
deletion and searching would have the same asymptotic running times.)

CHAINED-HASH-INSERT(T, x)
1 LIST-PREPEND(T[h(x.key)], x)

CHAINED-HASH-SEARCH(T, k)
1 return LIST-SEARCH(T[h(k)], k)

CHAINED-HASH-DELETE(T, x)

1 LIST-DELETE(T[h(x.key)], x)

Analysis of hashing with chaining

How well does hashing with chaining perform? In particular, how long
does it take to search for an element with a given key?

Given  a  hash  table  T  with  m  slots  that  stores  n  elements,  we  deﬁne
the load factor α for T as n/m, that is, the average number of elements
stored in a chain. Our analysis will be in terms of α, which can be less
than, equal to, or greater than 1.

The  worst-case  behavior  of  hashing  with  chaining  is  terrible:  all  n
keys  hash  to  the  same  slot,  creating  a  list  of  length  n.  The  worst-case
time  for  searching  is  thus  Θ(n)  plus  the  time  to  compute  the  hash
function—no  better  than  using  one  linked  list  for  all  the  elements.  We
clearly don’t use hash tables for their worst-case performance.

The  average-case  performance  of  hashing  depends  on  how  well  the
hash  function  h  distributes  the  set  of  keys  to  be  stored  among  the  m
slots, on the average (meaning with respect to the distribution of keys to
be hashed and with respect to the choice of hash function, if this choice
is  randomized).  Section  11.3  discusses  these  issues,  but  for  now  we
assume that any given element is equally likely to hash into any of the m
slots.  That  is,  the  hash  function  is  uniform.  We  further  assume  that
where  a  given  element  hashes  to  is  independent  of  where  any  other
elements  hash  to.  In  other  words,  we  assume  that  we  are  using
independent uniform hashing.

Because  hashes  of  distinct  keys  are  assumed  to  be  independent,
independent  uniform  hashing  is  universal:  the  chance  that  any  two
distinct keys k1 and k2 collide is at most 1/m. Universality is important
in our analysis and also in the speciﬁcation of universal families of hash
functions, which we’ll see in Section 11.3.2.

For j = 0, 1, …, m − 1, denote the length of the list T[j] by nj, so that

and the expected value of nj is E[nj] = α = n/m.

We assume that O(1) time sufﬁces to compute the hash value h(k), so
that  the  time  required  to  search  for  an  element  with  key  k  depends
linearly  on  the  length  nh(k)  of  the  list  T[h(k)].  Setting  aside  the  O(1)
time required to compute the hash function and to access slot h(k), we’ll
consider  the  expected  number  of  elements  examined  by  the  search
algorithm,  that  is,  the  number  of  elements  in  the  list  T[h(k)]  that  the
algorithm checks to see whether any have a key equal to k. We consider
two cases. In the ﬁrst, the search is unsuccessful: no element in the table
has key k. In the second, the search successfully ﬁnds an element with
key k.

Theorem 11.1
In  a  hash  table  in  which  collisions  are  resolved  by  chaining,  an
unsuccessful  search  takes  Θ(1  +  α)  time  on  average,  under  the
assumption of independent uniform hashing.

Proof   Under the assumption of independent uniform hashing, any key
k not already stored in the table is equally likely to hash to any of the m
slots.  The  expected  time  to  search  unsuccessfully  for  a  key  k  is  the
expected  time  to  search  to  the  end  of  list  T[h(k)],  which  has  expected
length E[nh(k)] = α. Thus, the expected number of elements examined in
an  unsuccessful  search  is  α,  and  the  total  time  required  (including  the
time for computing h(k)) is Θ(1 + α).

▪

The  situation  for  a  successful  search  is  slightly  different.  An
unsuccessful search is equally likely to go to any slot of the hash table.
A successful search, however, cannot go to an empty slot, since it is for
an element that is present in one of the linked lists. We assume that the
element  searched  for  is  equally  likely  to  be  any  one  of  the  elements  in
the table, so the longer the list, the more likely that the search is for one
of  its  elements.  Even  so,  the  expected  search  time  still  turns  out  to  be
Θ(1 + α).

Theorem 11.2
In a hash table in which collisions are resolved by chaining, a successful
search  takes  Θ(1  +  α)  time  on  average,  under  the  assumption  of
independent uniform hashing.

Proof   We assume that the element being searched for is equally likely
to be any of the n elements stored in the table. The number of elements
examined during a successful search for an element x is 1 more than the
number  of  elements  that  appear  before  x  in  x’s  list.  Because  new
elements are placed at the front of the list, elements before x in the list
were  all  inserted  after  x  was  inserted.  Let  xi  denote  the  ith  element
inserted into the table, for i = 1, 2, …, n, and let ki = xi.key.

Our  analysis  uses  indicator  random  variables  extensively.  For  each
slot q in the table and for each pair of distinct keys ki and kj, we deﬁne
the indicator random variable

Xijq = I {the search is for xi, h(ki) = q, and h(kj) = q}.

That is, Xijq = 1 when keys ki and kj collide at slot q and the search is
for element xi. Because Pr{the search is for xi} = 1/n, Pr{h(ki) = q} =
1/m, Pr{h(kj) = q} = 1/m, and these events are all independent, we have
that  Pr{Xijq  =  1}  =  1/nm2.  Lemma  5.1  on  page  130  gives  E[Xijq]  =
1/nm2.

Next, we deﬁne, for each element xj, the indicator random variable

Yj = I {xj appears in a list prior to the element being searched for}

=

,

since  at  most  one  of  the  Xijq  equals  1,  namely  when  the  element  xi
being searched for belongs to the same list as xj (pointed to by slot q),
and i < j (so that xi appears after xj in the list).

Our  ﬁnal  random  variable  is  Z,  which  counts  how  many  elements

appear in the list prior to the element being searched for:

Because  we  must  count  the  element  being  searched  for  as  well  as  all
those  preceding  it  in  its  list,  we  wish  to  compute  E[Z  +  1].  Using
linearity of expectation (equation (C.24) on page 1192), we have

Thus, the total time required for a successful search (including the time
for computing the hash function) is Θ(2 + α/2 − α/2n) = Θ(1 + α).

▪

What does this analysis mean? If the number of elements in the table
is at most proportional to the number of hash-table slots, we have n =
O(m)  and,  consequently,  α  =  n/m  =  O(m)/m  =  O(1).  Thus,  searching
takes  constant  time  on  average.  Since  insertion  takes  O(1)  worst-case
time and deletion takes O(1) worst-case time when the lists are doubly
linked  (assuming  that  the  list  element  to  be  deleted  is  known,  and  not
just  its  key),  we  can  support  all  dictionary  operations  in  O(1)  time  on
average.

The  analysis  in  the  preceding  two  theorems  depends  only  on  two
essential  properties  of  independent  uniform  hashing:  uniformity  (each
key  is  equally  likely  to  hash  to  any  one  of  the  m  slots),  and
independence (so any two distinct keys collide with probability 1/m).

Exercises

11.2-1
You  use  a  hash  function  h  to  hash  n  distinct  keys  into  an  array  T  of
length m. Assuming independent uniform hashing, what is the expected
number of collisions? More precisely, what is the expected cardinality of
{{k1, k2} : k1 ≠ k2 and h(k1) = h(k2)}?

11.2-2
Consider a hash table with 9 slots and the hash function h(k) = k mod 9.
Demonstrate what happens upon inserting the keys 5, 28, 19, 15, 20, 33,
12, 17, 10 with collisions resolved by chaining.

11.2-3
Professor  Marley  hypothesizes
that  he  can  obtain  substantial
performance  gains  by  modifying  the  chaining  scheme  to  keep  each  list
in  sorted  order.  How  does  the  professor’s  modiﬁcation  affect  the
running  time  for  successful  searches,  unsuccessful  searches,  insertions,
and deletions?

11.2-4
Suggest how to allocate and deallocate storage for elements within the
hash table itself by creating a “free list”: a linked list of all the unused
slots. Assume that one slot can store a ﬂag and either one element plus a
pointer  or  two  pointers.  All  dictionary  and  free-list  operations  should
run in O(1) expected time. Does the free list need to be doubly linked, or
does a singly linked free list sufﬁce?

11.2-5
You need to store a set of n keys in a hash table of size m. Show that if
the keys are drawn from a universe U with |U| > (n − 1)m, then U has a
subset of size n consisting of keys that all hash to the same slot, so that
the worst-case searching time for hashing with chaining is Θ(n).

11.2-6
You have stored n keys in a hash table of size m, with collisions resolved
by  chaining,  and  you  know  the  length  of  each  chain,  including  the
length  L  of  the  longest  chain.  Describe  a  procedure  that  selects  a  key
uniformly at random from among the keys in the hash table and returns
it in expected time O(L · (1 + 1/α)).

11.3    Hash functions

For  hashing  to  work  well,  it  needs  a  good  hash  function.  Along  with
being efﬁciently computable, what properties does a good hash function
have? How do you design good hash functions?

This section ﬁrst attempts to answer these questions based on two ad
hoc  approaches  for  creating  hash  functions:  hashing  by  division  and
hashing by multiplication. Although these methods work well for some
sets of input keys, they are limited because they try to provide a single
ﬁxed  hash  function  that  works  well  on  any  data—an  approach  called
static hashing.

We  then  see  that  provably  good  average-case  performance  for  any
data  can  be  obtained  by  designing  a  suitable  family  of  hash  functions
and  choosing  a  hash  function  at  random  from  this  family  at  runtime,
independent  of  the  data  to  be  hashed.  The  approach  we  examine  is

called random hashing. A particular kind of random hashing, universal
hashing,  works  well.  As  we  saw  with  quicksort  in  Chapter  7,
randomization is a powerful algorithmic design tool.

What makes a good hash function?

A  good  hash  function  satisﬁes  (approximately)  the  assumption  of
independent uniform hashing: each key is equally likely to hash to any
of  the  m  slots,  independently  of  where  any  other  keys  have  hashed  to.
What does “equally likely” mean here? If the hash function is ﬁxed, any
probabilities  would  have  to  be  based  on  the  probability  distribution  of
the input keys.

Unfortunately,  you  typically  have  no  way  to  check  this  condition,
unless you happen to know the probability distribution from which the
keys are drawn. Moreover, the keys might not be drawn independently.

Occasionally  you  might  know  the  distribution.  For  example,  if  you
know  that  the  keys  are  random  real  numbers  k  independently  and
uniformly distributed in the range 0 ≤ k < 1, then the hash function

h(k) = ⌊km⌋
satisﬁes the condition of independent uniform hashing.

A good static hashing approach derives the hash value in a way that
you  expect  to  be  independent  of  any  patterns  that  might  exist  in  the
data.  For  example,  the  “division  method”  (discussed  in  Section  11.3.1)
computes the hash value as the remainder when the key is divided by a
speciﬁed  prime  number.  This  method  may  give  good  results,  if  you
(somehow) choose a prime number that is unrelated to any patterns in
the distribution of keys.

Random  hashing,  described  in  Section  11.3.2,  picks  the  hash
function  to  be  used  at  random  from  a  suitable  family  of  hashing
functions. This approach removes any need to know anything about the
probability  distribution  of  the  input  keys,  as  the  randomization
necessary for good average-case behavior then comes from the (known)
random process used to pick the hash function from the family of hash
functions,  rather  than  from  the  (unknown)  process  used  to  create  the
input keys. We recommend that you use random hashing.

Keys are integers, vectors, or strings

In  practice,  a  hash  function  is  designed  to  handle  keys  that  are  one  of
the following two types:

A  short  nonnegative  integer  that  ﬁts  in  a  w-bit  machine  word.
Typical values for w would be 32 or 64.

A short vector of nonnegative integers, each of bounded size. For
example,  each  element  might  be  an  8-bit  byte,  in  which  case  the
vector  is  often  called  a  (byte)  string.  The  vector  might  be  of
variable length.

To begin, we assume that keys are short nonnegative integers. Handling
vector  keys  is  more  complicated  and  discussed  in  Sections  11.3.5  and
11.5.2.

11.3.1    Static hashing
Static  hashing  uses  a  single,  ﬁxed  hash
function.  The  only
randomization  available  is  through  the  (usually  unknown)  distribution
of input keys. This section discusses two standard approaches for static
hashing: the division method and the multiplication method. Although
static  hashing  is  no  longer  recommended,  the  multiplication  method
also provides a good foundation for “nonstatic” hashing—better known
as random hashing—where the hash function is chosen at random from
a suitable family of hash functions.

The division method

The division method for creating hash functions maps a key k into one
of m slots by taking the remainder of k divided by m. That is, the hash
function is

h(k) = k mod m.

For example, if the hash table has size m = 12 and the key is k = 100,
then h(k) = 4. Since it requires only a single division operation, hashing
by division is quite fast.

The division method may work well when m is a prime not too close
to an exact power of 2. There is no guarantee that this method provides
good  average-case  performance,  however,  and  it  may  complicate
applications since it constrains the size of the hash tables to be prime.

The multiplication method

The  general  multiplication  method  for  creating  hash  functions  operates
in two steps. First, multiply the key k by a constant A in the range 0 < A
< 1 and extract the fractional part of kA. Then, multiply this value by m
and take the ﬂoor of the result. That is, the hash function is

h(k) = ⌊m (kA mod 1)⌋,
where “kA mod 1” means the fractional part of kA, that is, kA − ⌊kA⌋.
The general multiplication method has the advantage that the value of
m is not critical and you can choose it independently of how you choose
the multiplicative constant A.

Figure 11.4 The multiply-shift method to compute a hash function. The w-bit representation of
the key k is multiplied by the w-bit value a = A · 2w. The ℓ highest-order bits of the lower w-bit
half of the product form the desired hash value ha(k).

The multiply-shift method

In  practice,  the  multiplication  method  is  best  in  the  special  case  where
the number m of hash-table slots is an exact power of 2, so that m = 2ℓ
for some integer ℓ, where ℓ ≤ w and w is the number of bits in a machine

word. If you choose a ﬁxed w-bit positive integer a = A 2w, where 0 < A
< 1 as in the multiplication method so that a is in the range 0 < a < 2w,
you  can  implement  the  function  on  most  computers  as  follows.  We
assume that a key k ﬁts into a single w-bit word.

Referring to Figure 11.4, ﬁrst multiply k by the w-bit integer a. The
result is a 2w-bit value r12w + r0, where r1 is the high-order w-bit word
of the product and r0 is the low-order w-bit word of the product. The
desired  ℓ -bit  hash  value  consists  of  the  ℓ   most  signiﬁcant  bits  of  r0.
(Since  r1  is  ignored,  the  hash  function  can  be  implemented  on  a
computer  that  produces  only  a  w-bit  product  given  two  w-bit  inputs,
that is, where the multiplication operation computes modulo 2w.)
In other words, you deﬁne the hash function h = ha, where

for  a  ﬁxed  nonzero  w-bit  value  a.  Since  the  product  ka  of  two  w-bit
words  occupies  2w  bits,  taking  this  product  modulo  2w  zeroes  out  the
high-order  w  bits  (r1),  leaving  only  the  low-order  w  bits  (r0).  The ⋙
operator performs a logical right shift by w − ℓ bits, shifting zeros into
the vacated positions on the left, so that the ℓ most signiﬁcant bits of r0
move into the ℓ rightmost positions. (It’s the same as dividing by 2w−ℓ
and taking the ﬂoor of the result.) The resulting value equals the ℓ most
signiﬁcant  bits  of  r0.  The  hash  function  ha  can  be  implemented  with
three machine instructions: multiplication, subtraction, and logical right
shift.

As an example, suppose that k = 123456, ℓ = 14, m = 214 = 16384,
and w = 32. Suppose further that we choose a = 2654435769 (following
a  suggestion  of  Knuth  [261]).  Then  ka  =  327706022297664  =  (76300  ·
232)  +  17612864,  and  so  r1  =  76300  and  r0  =  17612864.  The  14  most
signiﬁcant bits of r0 yield the value ha(k) = 67.

Even though the multiply-shift method is fast, it doesn’t provide any
guarantee  of  good  average-case  performance.  The  universal  hashing

approach  presented  in  the  next  section  provides  such  a  guarantee.  A
simple randomized variant of the multiply-shift method works well on
the  average,  when  the  program  begins  by  picking  a  as  a  randomly
chosen odd integer.

11.3.2    Random hashing
Suppose  that  a  malicious  adversary  chooses  the  keys  to  be  hashed  by
some ﬁxed hash function. Then the adversary can choose n keys that all
hash  to  the  same  slot,  yielding  an  average  retrieval  time  of  Θ(n).  Any
static  hash  function  is  vulnerable  to  such  terrible  worst-case  behavior.
The  only  effective  way  to  improve  the  situation  is  to  choose  the  hash
function  randomly  in  a  way  that  is  independent  of  the  keys  that  are
actually going to be stored. This approach is called random hashing. A
special  case  of  this  approach,  called  universal  hashing,  can  yield
provably  good  performance  on  average  when  collisions  are  handled  by
chaining, no matter which keys the adversary chooses.

To use random hashing, at the beginning of program execution you
select the hash function at random from a suitable family of functions.
As  in  the  case  of  quicksort,  randomization  guarantees  that  no  single
input  always  evokes  worst-case  behavior.  Because  you  randomly  select
the  hash  function,  the  algorithm  can  behave  differently  on  each
execution,  even  for  the  same  set  of  keys  to  be  hashed,  guaranteeing
good average-case performance.

Let H be a ﬁnite family of hash functions that map a given universe
U of keys into the range {0, 1, …, m − 1}. Such a family is said to be
universal  if  for  each  pair  of  distinct  keys  k1,  k2  ∈  U,  the  number  of
hash  functions  h  ∈  H  for  which  h(k1)  =  h(k2)  is  at  most  |H|/m.  In
other words, with a hash function randomly chosen from H, the chance
of  a  collision  between  distinct  keys  k1  and  k2  is  no  more  than  the
chance  1/m  of  a  collision  if  h(k1)  and  h(k2)  were  randomly  and
independently chosen from the set {0, 1, …, m − 1}.

Independent uniform hashing is the same as picking a hash function
uniformly at random from a family of mn hash functions, each member

of  that  family  mapping  the  n  keys  to  the  m  hash  values  in  a  different
way.

Every  independent  uniform  random  family  of  hash  function  is
universal, but the converse need not be true: consider the case where U
=  {0,  1,  …,  m  −  1}  and  the  only  hash  function  in  the  family  is  the
identity function. The probability that two distinct keys collide is zero,
even though each key is hashes to a ﬁxed value.

The  following  corollary  to  Theorem  11.2  on  page  279  says  that
universal hashing provides the desired payoff: it becomes impossible for
an adversary to pick a sequence of operations that forces the worst-case
running time.

Corollary 11.3
Using  universal  hashing  and  collision  resolution  by  chaining  in  an
initially empty table with m slots, it takes Θ(s) expected time to handle
any  sequence  of  s  INSERT,  SEARCH,  and  DELETE  operations
containing n = O(m) INSERT operations.

Proof      The  INSERT  and  DELETE  operations  take  constant  time.
Since  the  number  n  of  insertions  is  O(m),  we  have  that  α  =  O(1).
Furthermore,  the  expected  time  for  each  SEARCH  operation  is  O(1),
which  can  be  seen  by  examining  the  proof  of  Theorem  11.2.  That
analysis  depends  only  on  collision  probabilities,  which  are  1/m  for  any
pair  k1,  k2  of  keys  by  the  choice  of  an  independent  uniform  hash
function  in  that  theorem.  Using  a  universal  family  of  hash  functions
here  instead  of  using  independent  uniform  hashing  changes  the
probability  of  collision  from  1/m  to  at  most  1/m.  By  linearity  of
expectation,  therefore,  the  expected  time  for  the  entire  sequence  of  s
operations is O(s). Since each operation takes Ω(1) time, the Θ(s) bound
follows.

▪

11.3.3    Achievable properties of random hashing
There is a rich literature on the properties a family H of hash functions
can  have,  and  how  they  relate  to  the  efﬁciency  of  hashing.  We
summarize a few of the most interesting ones here.

Let H be a family of hash functions, each with domain U and range
{0, 1, …, m − 1}, and let h be any hash function that is picked uniformly
at random from H. The probabilities mentioned are probabilities over
the picks of h.

The family H is uniform if for any key k in U and any slot q in
the range {0, 1, …, m − 1}, the probability that h(k) = q is 1/m.

The family H is universal if for any distinct keys k1 and k2 in U,
the probability that h(k1) = h(k2) is at most 1/m.

The family H of hash functions is ϵ-universal if for any distinct
keys k1 and k2 in U, the probability that h(k1) = h(k2) is at most
ϵ.  Therefore,  a  universal  family  of  hash  functions  is  also  1/m-
universal.2

The family H is d-independent if for any distinct keys k1, k2, …,
kd in U and any slots q1, q2, …, qd, not necessarily distinct, in {0,
1,  …,  m  −  1}  the  probability  that  h(ki)  =  qi  for  i  =  1,  2,  …,  d  is
1/md.

Universal  hash-function  families  are  of  particular  interest,  as  they  are
the simplest type supporting provably efﬁcient hash-table operations for
any input data set. Many other interesting and desirable properties, such
as those noted above, are also possible and allow for efﬁcient specialized
hash-table operations.

11.3.4    Designing a universal family of hash functions
This  section  present  two  ways  to  design  a  universal  (or  ϵ-universal)
family  of  hash  functions:  one  based  on  number  theory  and  another
based on a randomized variant of the multiply-shift method presented
in Section 11.3.1. The ﬁrst method is a bit easier to prove universal, but
the second method is newer and faster in practice.

A universal family of hash functions based on number theory

We can design a universal family of hash functions using a little number
theory. You may wish to refer to Chapter 31 if you are unfamiliar with
basic concepts in number theory.

Begin  by  choosing  a  prime  number  p  large  enough  so  that  every
possible key k lies in the range 0 to p − 1, inclusive. We assume here that
p  has  a  “reasonable”  length.  (See  Section  11.3.5  for  a  discussion  of
methods  for  handling  long  input  keys,  such  as  variable-length  strings.)
Let ℤp denote the set {0, 1, …, p − 1}, and let
 denote the set {1, 2,
…, p − 1}. Since p is prime, we can solve equations modulo p with the
methods given in Chapter 31. Because the size of the universe of keys is
greater  than  the  number  of  slots  in  the  hash  table  (otherwise,  just  use
direct addressing), we have p > m.

Given any

 and any b ∈ ℤp, deﬁne the hash function hab as a
linear  transformation  followed  by  reductions  modulo  p  and  then
modulo m:

For example, with p = 17 and m = 6, we have

h3,4(8) = ((3 · 8 + 4) mod 17) mod 6
= (28 mod 17) mod 6
= 11 mod 6
= 5.

Given p and m, the family of all such hash functions is

Each hash function hab maps ℤp to ℤm. This family of hash functions
has the nice property that the size m of the output range (which is the
size of the hash table) is arbitrary—it need not be prime. Since you can
choose  from  among  p  −  1  values  for  a  and  p  values  for  b,  the  family
Hpm contains p(p − 1) hash functions.

Theorem 11.4

The  family Hpm  of  hash  functions  deﬁned  by  equations  (11.3)  and
(11.4) is universal.

Proof   Consider two distinct keys k1 and k2 from ℤp, so that k1 ≠ k2.
For a given hash function hab, let

r1 = (ak1 + b) mod p,
r2 = (ak2 + b) mod p.

We ﬁrst note that r1 ≠ r2. Why? Since we have r1 − r2 = a(k1 − k2) (mod
p), it follows that r1 ≠ r2 because p is prime and both a and (k1 − k2) are
nonzero  modulo  p.  By  Theorem  31.6  on  page  908,  their  product  must
also  be  nonzero  modulo  p.  Therefore,  when  computing  any  hab  ∈
Hpm,  distinct  inputs  k1  and  k2  map  to  distinct  values  r1  and  r2
modulo  p,  and  there  are  no  collisions  yet  at  the  “mod  p  level.”
Moreover, each of the possible p(p − 1) choices for the pair (a, b) with a
≠  0  yields  a  different  resulting  pair  (r1,  r2)  with  r1  ≠  r2,  since  we  can
solve for a and b given r1 and r2:
a = ((r − r2)((k1 − k2)−1 mod p)) mod p,
b = (r1 − ak1) mod p,
where  ((k1  −  k2)−1  mod  p)  denotes  the  unique  multiplicative  inverse,
modulo p, of k1 − k2. For each of the p possible values of r1, there are
only p − 1 possible values of r2 that do not equal r1, making only p(p −
1)  possible  pairs  (r1,  r2)  with  r1  ≠  r2.  Therefore,  there  is  a  one-to-one
correspondence between pairs (a, b) with a ≠ 0 and pairs (r1, r2) with r1
≠ r2. Thus, for any given pair of distinct inputs k1 and k2, if we pick (a,
,  the  resulting  pair  (r1,  r2)  is
b)  uniformly  at  random  from
equally likely to be any pair of distinct values modulo p.

Therefore, the probability that distinct keys k1 and k2 collide is equal
to  the  probability  that  r1  =  r2  (mod  m)  when  r1  and  r2  are  randomly

chosen as distinct values modulo p. For a given value of r1, of the p − 1
possible remaining values for r2, the number of values r2 such that r2 ≠
r1 and r2 = r1 (mod m) is at most

The  probability  that  r2  collides  with  r1  when  reduced  modulo  m  is  at
most ((p − 1)/m)/(p − 1) = 1/m, since r2 is equally likely to be any of the
p − 1 values in Zp that are different from r1, but at most (p − 1)/m of
those values are equivalent to r1 modulo m.

Therefore, for any pair of distinct values k1, k2 ∈ ℤp,

Pr{hab(k1) = hab(k2)} ≤ 1/m,

so that Hpm is indeed universal.

▪

A 2/m-universal family of hash functions based on the multiply-shift
method

We  recommend  that  in  practice  you  use  the  following  hash-function
family  based  on  the  multiply-shift  method.  It  is  exceptionally  efﬁcient
and (although we omit the proof) provably 2/m-universal. Deﬁne H to
be the family of multiply-shift hash functions with odd constants a:

Theorem 11.5
The  family  of  hash  functions  H  given  by  equation  (11.5)  is  2/m-
universal.

▪

That  is,  the  probability  that  any  two  distinct  keys  collide  is  at  most
2/m.  In  many  practical  situations,  the  speed  of  computing  the  hash

function  more  than  compensates  for  the  higher  upper  bound  on  the
probability  that  two  distinct  keys  collide  when  compared  with  a
universal hash function.

11.3.5    Hashing long inputs such as vectors or strings

Sometimes hash function inputs are so long that they cannot be easily
encoded modulo a reasonably sized prime number p or encoded within
a  single  word  of,  say,  64  bits.  As  an  example,  consider  the  class  of
vectors,  such  as  vectors  of  8-bit  bytes  (which  is  how  strings  in  many
programming  languages  are  stored).  A  vector  might  have  an  arbitrary
nonnegative  length,  in  which  case  the  length  of  the  input  to  the  hash
function may vary from input to input.

Number-theoretic approaches

One way to design good hash functions for variable-length inputs is to
extend  the  ideas  used  in  Section  11.3.4  to  design  universal  hash
functions. Exercise 11.3-6 explores one such approach.

Cryptographic hashing

Another way to design a good hash function for variable-length inputs
is  to  use  a  hash  function  designed  for  cryptographic  applications.
Cryptographic  hash  functions  are  complex  pseudorandom  functions,
designed  for  applications  requiring  properties  beyond  those  needed
here, but are robust, widely implemented, and usable as hash functions
for hash tables.

A cryptographic hash function takes as input an arbitrary byte string
and  returns  a  ﬁxed-length  output.  For  example,  the  NIST  standard
deterministic  cryptographic  hash  function  SHA-256  [346]  produces  a
256-bit (32-byte) output for any input.

include

Some  chip  manufacturers

in  their  CPU
architectures  to  provide  fast  implementations  of  some  cryptographic
functions.  Of  particular
instructions  that  efﬁciently
interest  are
implement  rounds  of  the  Advanced  Encryption  Standard  (AES),  the
“AES-NI”  instructions.  These  instructions  execute  in  a  few  tens  of
nanoseconds, which is generally fast enough for use with hash tables. A

instructions

message authentication code such as CBC-MAC based on AES and the
use  of  the  AES-NI  instructions  could  be  a  useful  and  efﬁcient  hash
function.  We  don’t  pursue  the  potential  use  of  specialized  instruction
sets further here.

Cryptographic hash functions are useful because they provide a way
of implementing an approximate version of a random oracle. As noted
earlier,  a  random  oracle  is  equivalent  to  an  independent  uniform  hash
function family. From a theoretical point of view, a random oracle is an
unachievable  ideal:  a  deterministic  function  that  provides  a  randomly
selected  output  for  each  input.  Because  it  is  deterministic,  it  provides
the  same  output  if  queried  again  for  the  same  input.  From  a  practical
point  of  view,  constructions  of  hash  function  families  based  on
cryptographic  hash  functions  are  sensible  substitutes  for  random
oracles.

There are many ways to use a cryptographic hash function as a hash

function. For example, we could deﬁne

h(k) = SHA-256(k) mod m.

To  deﬁne  a  family  of  such  hash  functions  one  may  prepend  a  “salt”
string a to the input before hashing it, as in

ha(k) = SHA-256(a ‖ k) mod m,

where a ‖ k denotes the string formed by concatenating the strings a and
k.  The  literature  on  message  authentication  codes  (MACs)  provides
additional approaches.

Cryptographic  approaches  to  hash-function  design  are  becoming
more  practical  as  computers  arrange  their  memories  in  hierarchies  of
differing capacities and speeds. Section 11.5 discusses one hash-function
design based on the RC6 encryption method.

Exercises

11.3-1
You  wish  to  search  a  linked  list  of  length  n,  where  each  element
contains  a  key  k  along  with  a  hash  value  h(k).  Each  key  is  a  long

character  string.  How  might  you  take  advantage  of  the  hash  values
when searching the list for an element with a given key?

11.3-2
You hash a string of r characters into m slots by treating it as a radix-
128 number and then using the division method. You can represent the
number  m  as  a  32-bit  computer  word,  but  the  string  of  r  characters,
treated  as  a  radix-128  number,  takes  many  words.  How  can  you  apply
the division method to compute the hash value of the character string
without using more than a constant number of words of storage outside
the string itself ?

11.3-3
Consider  a  version  of  the  division  method  in  which  h(k)  =  k  mod  m,
where  m  =  2p  −  1  and  k  is  a  character  string  interpreted  in  radix  2p.
Show  that  if  string  x  can  be  converted  to  string  y  by  permuting  its
characters, then x and y hash to the same value. Give an example of an
application  in  which  this  property  would  be  undesirable  in  a  hash
function.

11.3-4
Consider  a  hash  table  of  size  m  =  1000  and  a  corresponding  hash
function  h(k)  =  ⌊m  (kA  mod  1)⌋  for
.  Compute  the
locations to which the keys 61, 62, 63, 64, and 65 are mapped.

★ 11.3-5
Show that any ϵ-universal family H of hash functions from a ﬁnite set
U to a ﬁnite set Q has ϵ ≥ 1/|Q| − 1/|U|.

★ 11.3-6
Let U be the set of d-tuples of values drawn from ℤp, and let Q = ℤp,
where p is prime. Deﬁne the hash function hb : U → Q for b ∈ ℤp on an
input d-tuple 〈a0, a1, …, ad−1〉 from U as

and let H = {hb : b ∈ ℤp}. Argue that H is ϵ-universal for ϵ = (d −
1)/p. (Hint: See Exercise 31.4-4.)

11.4    Open addressing

This  section  describes  open  addressing,  a  method  for  collision
resolution  that,  unlike  chaining,  does  not  make  use  of  storage  outside
of the hash table itself. In open addressing, all elements occupy the hash
table  itself.  That  is,  each  table  entry  contains  either  an  element  of  the
dynamic  set  or  NIL.  No  lists  or  elements  are  stored  outside  the  table,
unlike in chaining. Thus, in open addressing, the hash table can “ﬁll up”
so that no further insertions can be made. One consequence is that the
load factor α can never exceed 1.

Collisions  are  handled  as  follows:  when  a  new  element  is  to  be
inserted  into  the  table,  it  is  placed  in  its  “ﬁrst-choice”  location  if
possible. If that location is already occupied, the new element is placed
in  its  “second-choice”  location.  The  process  continues  until  an  empty
slot is found in which to place the new element. Different elements have
different preference orders for the locations.

To search for an element, systematically examine the preferred table
slots for that element, in order of decreasing preference, until either you
ﬁnd the desired element or you ﬁnd an empty slot and thus verify that
the element is not in the table.

Of course, you could use chaining and store the linked lists inside the
hash  table,  in  the  otherwise  unused  hash-table  slots  (see  Exercise  11.2-
4),  but  the  advantage  of  open  addressing  is  that  it  avoids  pointers
altogether. Instead of following pointers, you compute the sequence of
slots  to  be  examined.  The  memory  freed  by  not  storing  pointers
provides  the  hash  table  with  a  larger  number  of  slots  in  the  same
amount  of  memory,  potentially  yielding  fewer  collisions  and  faster
retrieval.

To perform insertion using open addressing, successively examine, or
probe,  the  hash  table  until  you  ﬁnd  an  empty  slot  in  which  to  put  the
key. Instead of being ﬁxed in the order 0, 1, …, m − 1 (which implies a
Θ(n)  search  time),  the  sequence  of  positions  probed  depends  upon  the
key being inserted. To determine which slots to probe, the hash function
includes the probe number (starting from 0) as a second input. Thus, the
hash function becomes

h : U × {0, 1, …, m − 1} → {0, 1, …, m − 1}.

Open addressing requires that for every key k, the probe sequence 〈h(k,
0), h(k, 1), …, h(k, m − 1)〉 be a permutation of 〈0, 1, …, m − 1〉, so that
every hash-table position is eventually considered as a slot for a new key
as  the  table  ﬁlls  up.  The  HASH-INSERT  procedure  on  the  following
page  assumes  that  the  elements  in  the  hash  table  T  are  keys  with  no
satellite information: the key k is identical to the element containing key
k.  Each  slot  contains  either  a  key  or  NIL  (if  the  slot  is  empty).  The
HASH-INSERT  procedure  takes  as  input  a  hash  table  T  and  a  key
k  that  is  assumed  to  be  not  already  present  in  the  hash  table.  It  either
returns the slot number where it stores key k or ﬂags an error because
the hash table is already full.

HASH-INSERT(T, k)
1 i = 0
2 repeat
3

q = h(k, i)
if T[q] == NIL
T[q] = k
return q
else i = i + 1

4

5

6

7
8 until i == m
9 error “hash table overﬂow”

HASH-SEARCH(T, k)

1 i = 0
2 repeat

3

4

5

q = h(k, i)
if T[q] == k
return q

i = i + 1

6
7 until T[q] == NIL or i == m
8 return NIL

The  algorithm  for  searching  for  key  k  probes  the  same  sequence  of
slots  that  the  insertion  algorithm  examined  when  key  k  was  inserted.
Therefore,  the  search  can  terminate  (unsuccessfully)  when  it  ﬁnds  an
empty  slot,  since  k  would  have  been  inserted  there  and  not  later  in  its
probe sequence. The procedure HASH-SEARCH takes as input a hash
table T and a key k, returning q if it ﬁnds that slot q contains key k, or
NIL if key k is not present in table T.

Deletion from an open-address hash table is tricky. When you delete
a key from slot q, it would be a mistake to mark that slot as empty by
simply storing NIL in it. If you did, you might be unable to retrieve any
key  k  for  which  slot  q  was  probed  and  found  occupied  when  k  was
inserted. One way to solve this problem is by marking the slot, storing
in it the special value DELETED instead of NIL. The HASH-INSERT
procedure then has to treat such a slot as empty so that it can insert a
new key there. The HASH-SEARCH procedure passes over DELETED
values  while  searching,  since  slots  containing  DELETED  were  ﬁlled
when  the  key  being  searched  for  was  inserted.  Using  the  special  value
DELETED, however, means that search times no longer depend on the
load  factor  α,  and  for  this  reason  chaining  is  frequently  selected  as  a
collision  resolution  technique  when  keys  must  be  deleted.  There  is  a
simple  special  case  of  open  addressing,  linear  probing,  that  avoids  the
need to mark slots with DELETED. Section 11.5.1 shows how to delete
from a hash table when using linear probing.

In our analysis, we assume independent uniform permutation hashing
(also confusingly known as uniform hashing in the literature): the probe
sequence of each key is equally likely to be any of the m! permutations
of  〈0,  1,  …,  m  −  1〉.  Independent  uniform  permutation  hashing
generalizes  the  notion  of  independent  uniform  hashing  deﬁned  earlier

to  a  hash  function  that  produces  not  just  a  single  slot  number,  but  a
whole probe sequence. True independent uniform permutation hashing
is  difﬁcult
suitable
implement,  however,  and
approximations (such as double hashing, deﬁned below) are used.

in  practice

to

We’ll  examine  both  double  hashing  and  its  special  case,  linear
probing. These techniques guarantee that 〈h(k, 0), h(k, 1), …, h(k, m −
1)〉 is a permutation of 〈0, 1, …, m − 1〉 for each key k. (Recall that the
second parameter to the hash function h is the probe number.) Neither
the  assumption  of
linear  probing  meets
double  hashing  nor
independent  uniform  permutation  hashing,  however.  Double  hashing
cannot generate more than m2 different probe sequences (instead of the
m!
requires).
independent  uniform  permutation  hashing
Nonetheless,  double  hashing  has  a  large  number  of  possible  probe
sequences and, as you might expect, seems to give good results. Linear
probing is even more restricted, capable of generating only m different
probe sequences.

that

Double hashing

Double  hashing  offers  one  of  the  best  methods  available  for  open
addressing  because  the  permutations  produced  have  many  of  the
characteristics of randomly chosen permutations. Double hashing uses a
hash function of the form

h(k, i) = (h1(k) + ih2(k)) mod m,

where both h1 and h2 are auxiliary hash functions. The initial probe goes
to  position  T[h1(k)],  and  successive  probe  positions  are  offset  from
previous  positions  by  the  amount  h2(k),  modulo  m.  Thus,  the  probe
sequence  here  depends  in  two  ways  upon  the  key  k,  since  the  initial
probe position h1(k), the step size h2(k), or both, may vary. Figure 11.5
gives an example of insertion by double hashing.

In order for the entire hash table to be searched, the value h2(k) must
be  relatively  prime  to  the  hash-table  size  m.  (See  Exercise  11.4-5.)  A
convenient way to ensure this condition is to let m be an exact power of

2 and to design h2 so that it always produces an odd number. Another
way  is  to  let  m  be  prime  and  to  design  h2  so  that  it  always  returns  a
positive  integer  less  than  m.  For  example,  you  could  choose  m  prime
and let

Figure 11.5 Insertion by double hashing. The hash table has size 13 with h1(k) = k mod 13 and
h2(k) = 1 + (k mod 11). Since 14 = 1 (mod 13) and 14 = 3 (mod 11), the key 14 goes into empty
slot 9, after slots 1 and 5 are examined and found to be occupied.

h1(k) = k mod m,
h2(k) = 1 + (k mod m′),

where m′ is chosen to be slightly less than m (say, m − 1). For example,
if k = 123456, m = 701, and m′ = 700, then h1(k) = 80 and h2(k) = 257,
so  that  the  ﬁrst  probe  goes  to  position  80,  and  successive  probes
examine  every  257th  slot  (modulo  m)  until  the  key  has  been  found  or
every slot has been examined.

Although values of m other than primes or exact powers of 2 can in
principle  be  used  with  double  hashing,  in  practice  it  becomes  more
difﬁcult  to  efﬁciently  generate  h2(k)  (other  than  choosing  h2(k)  =  1,
which  gives  linear  probing)  in  a  way  that  ensures  that  it  is  relatively

prime to m, in part because the relative density ϕ(m)/m of such numbers
for general m may be small (see equation (31.25) on page 921).

When  m  is  prime  or  an  exact  power  of  2,  double  hashing  produces
Θ(m2)  probe  sequences,  since  each  possible  (h1(k),  h2(k))  pair  yields  a
distinct  probe  sequence.  As  a  result,  for  such  values  of  m,  double
hashing appears to perform close to the “ideal” scheme of independent
uniform permutation hashing.

Linear probing

Linear  probing,  a  special  case  of  double  hashing,  is  the  simplest  open-
addressing approach to resolving collisions. As with double hashing, an
auxiliary hash function h1 determines the ﬁrst probe position h1(k) for
inserting an element. If slot T[h1(k)] is already occupied, probe the next
position T[h1(k) + 1]. Keep going as necessary, on up to slot T[m − 1],
and  then  wrap  around  to  slots  T[0],  T[1],  and  so  on,  but  never  going
past slot T[h1(k) − 1]. To view linear probing as a special case of double
hashing,  just  set  the  double-hashing  step  function  h2  to  be  ﬁxed  at  1:
h2(k) = 1 for all k. That is, the hash function is

for i = 0, 1, …, m − 1. The value of h1(k) determines the entire probe
sequence, and so assuming that h1(k) can take on any value in {0, 1, …,
m − 1}, linear probing allows only m distinct probe sequences.

We’ll revisit linear probing in Section 11.5.1.

Analysis of open-address hashing

As  in  our  analysis  of  chaining  in  Section  11.2,  we  analyze  open
addressing in terms of the load factor α = n/m of the hash table. With
open addressing, at most one element occupies each slot, and thus n ≤
m, which implies α ≤ 1. The analysis below requires α to be strictly less
than  1,  and  so  we  assume  that  at  least  one  slot  is  empty.  Because
deleting from an open-address hash table does not really free up a slot,
we assume as well that no deletions occur.

For the hash function, we assume independent uniform permutation
hashing.  In  this  idealized  scheme,  the  probe  sequence  〈h(k,  0),  h(k,  1),
…, h(k, m − 1)〉 used to insert or search for each key k is equally likely
to be any permutation of 〈0, 1, …, m − 1〉. Of course, any given key has
a unique ﬁxed probe sequence associated with it. What we mean here is
that,  considering  the  probability  distribution  on  the  space  of  keys  and
the  operation  of  the  hash  function  on  the  keys,  each  possible  probe
sequence is equally likely.

We  now  analyze  the  expected  number  of  probes  for  hashing  with
open  addressing  under  the  assumption  of
independent  uniform
permutation  hashing,  beginning  with  the  expected  number  of  probes
made in an unsuccessful search (assuming, as stated above, that α < 1).
3  +  ⋯,  has  an
intuitive interpretation. The ﬁrst probe always occurs. With probability
approximately α, the ﬁrst probe ﬁnds an occupied slot, so that a second
2,  the  ﬁrst  two  slots
probe  happens.  With  probability  approximately  α
are occupied so that a third probe ensues, and so on.

The  bound  proven,  of  1/(1  −  α)  =  1  +  α  +  α

2  +  α

Theorem 11.6
Given  an  open-address  hash  table  with  load  factor  α  =  n/m  <  1,  the
expected number of probes in an unsuccessful search is at most 1/(1 −
α),  assuming  independent  uniform  permutation  hashing  and  no
deletions.

Proof      In  an  unsuccessful  search,  every  probe  but  the  last  accesses  an
occupied  slot  that  does  not  contain  the  desired  key,  and  the  last  slot
probed  is  empty.  Let  the  random  variable  X  denote  the  number  of
probes made in an unsuccessful search, and deﬁne the event Ai, for i =
1, 2, …, as the event that an ith probe occurs and it is to an occupied
slot. Then the event {X ≥ i} is the intersection of events A1 ⋂ A2 ⋂ ⋯
⋂ Ai−1. We bound Pr{X ≥ i} by bounding Pr{A1 ⋂ A2 ⋂ ⋯ ⋂ Ai−1}.
By Exercise C.2-5 on page 1190,

Pr{A1  ⋂  A2  ⋂  ⋯  ⋂
Ai−1}

= Pr{A1} · Pr{A2 | A1} · Pr {A3 | A1 ⋂ A2}

⋯
Pr{Ai−1 | A1 ⋂ A2 ⋂ ⋯ ⋂ Ai−2}.

Since  there  are  n  elements  and  m  slots,  Pr{A1}  =  n/m.  For  j  >  1,  the
probability that there is a jth probe and it is to an occupied slot, given
that the ﬁrst j − 1 probes were to occupied slots, is (n − j + 1)/(m − j +
1). This probability follows because the jth probe would be ﬁnding one
of  the  remaining  (n  −  (j  −  1))  elements  in  one  of  the  (m  −  (j  −  1))
unexamined  slots,  and  by  the  assumption  of  independent  uniform
permutation  hashing,  the  probability  is  the  ratio  of  these  quantities.
Since n < m implies that (n − j)/(m − j) ≤ n/m for all j in the range 0 ≤ j <
m, it follows that for all i in the range 1 ≤ i ≤ m, we have

The product in the ﬁrst line has i − 1 factors. When i = 1, the product is
1,  the  identity  for  multiplication,  and  we  get  Pr{X  ≥  1}  =  1,  which
makes sense, since there must always be at least 1 probe. If each of the
ﬁrst  n  probes  is  to  an  occupied  slot,  then  all  occupied  slots  have  been
probed. Then, the (n + 1)st probe must be to an empty slot, which gives
Pr{X ≥ i} = 0 for i > n + 1. Now, we use equation (C.28) on page 1193 to
bound the expected number of probes:

▪

If α is a constant, Theorem 11.6 predicts that an unsuccessful search
runs in O(1) time. For example, if the hash table is half full, the average
number of probes in an unsuccessful search is at most 1/(1 − .5) = 2. If
it is 90% full, the average number of probes is at most 1/(1 − .9) = 10.

Theorem  11.6  yields  almost  immediately  how  well  the  HASH-

INSERT procedure performs.

Corollary 11.7
Inserting an element into an open-address hash table with load factor α,
where  α  <  1,  requires  at  most  1/(1  −  α)  probes  on  average,  assuming
independent uniform permutation hashing and no deletions.

Proof   An element is inserted only if there is room in the table, and thus
α  <  1.  Inserting  a  key  requires  an  unsuccessful  search  followed  by
placing  the  key  into  the  ﬁrst  empty  slot  found.  Thus,  the  expected
number of probes is at most 1/(1 − α).

▪

It  takes  a  little  more  work  to  compute  the  expected  number  of

probes for a successful search.

Theorem 11.8

Given an open-address hash table with load factor α < 1, the expected
number of probes in a successful search is at most

assuming  independent  uniform  permutation  hashing  with  no  deletions
and assuming that each key in the table is equally likely to be searched
for.

Proof      A  search  for  a  key  k  reproduces  the  same  probe  sequence  as
when  the  element  with  key  k  was  inserted.  If  k  was  the  (i  +  1)st  key
inserted  into  the  hash  table,  then  the  load  factor  at  the  time  it  was
inserted  was  i/m,  and  so  by  Corollary  11.7,  the  expected  number  of
probes  made  in  a  search  for  k  is  at  most  1/(1  −  i/m)  =  m/(m  −  i).
Averaging over all n keys in the hash table gives us the expected number
of probes in a successful search:

If  the  hash  table  is  half  full,  the  expected  number  of  probes  in  a
successful  search  is  less  than  1.387.  If  the  hash  table  is  90%  full,  the
expected  number  of  probes  is  less  than  2.559.  If  α  =  1,  then  in  an
unsuccessful  search,  all  m  slots  must  be  probed.  Exercise  11.4-4  asks
you to analyze a successful search when α = 1.

▪

Exercises

11.4-1
Consider inserting the keys 10, 22, 31, 4, 15, 28, 17, 88, 59 into a hash
table  of  length  m  =  11  using  open  addressing.  Illustrate  the  result  of
inserting  these  keys  using  linear  probing  with  h(k,  i)  =  (k  +  i)  mod  m
and using double hashing with h1(k) = k and h2(k) = 1 + (k mod (m −
1)).

11.4-2
Write  pseudocode  for  HASH-DELETE  that  ﬁlls  the  deleted  key’s  slot
with  the  special  value  DELETED,  and  modify  HASH-SEARCH  and
HASH-INSERT as needed to handle DELETED.

11.4-3
Consider  an  open-address  hash  table  with  independent  uniform
permutation  hashing  and  no  deletions.  Give  upper  bounds  on  the
expected  number  of  probes  in  an  unsuccessful  search  and  on  the
expected number of probes in a successful search when the load factor
is 3/4 and when it is 7/8.

11.4-4
Show  that  the  expected  number  of  probes  required  for  a  successful
search  when  α  =  1  (that  is,  when  n  =  m),  is  Hm,  the  mth  harmonic
number.

★ 11.4-5
Show that, with double hashing, if m and h2(k) have greatest common
divisor  d  ≥  1  for  some  key  k,  then  an  unsuccessful  search  for  key  k
examines (1/d)th of the hash table before returning to slot h1(k). Thus,
when  d  =  1,  so  that  m  and  h2(k)  are  relatively  prime,  the  search  may
examine the entire hash table. (Hint: See Chapter 31.)

★ 11.4-6
Consider an open-address hash table with a load factor α. Approximate
the  nonzero  value  α  for  which  the  expected  number  of  probes  in  an

unsuccessful  search  equals  twice  the  expected  number  of  probes  in  a
successful  search.  Use  the  upper  bounds  given  by  Theorems  11.6  and
11.8 for these expected numbers of probes.

11.5    Practical considerations

Efﬁcient hash table algorithms are not only of theoretical interest, but
also of immense practical importance. Constant factors can matter. For
this reason, this section discusses two aspects of modern CPUs that are
not included in the standard RAM model presented in Section 2.2:

Memory  hierarchies:  The  memory  of  modern  CPUs  has  a  number  of
levels,  from  the  fast  registers,  through  one  or  more  levels  of  cache
memory, to the main-memory level. Each successive level stores more
data than the previous level, but access is slower. As a consequence, a
complex  computation  (such  as  a  complicated  hash  function)  that
works entirely within the fast registers can take less time than a single
read  operation  from  main  memory.  Furthermore,  cache  memory  is
organized  in  cache  blocks  of  (say)  64  bytes  each,  which  are  always
fetched together from main memory. There is a substantial beneﬁt for
ensuring that memory usage is local: reusing the same cache block is
much  more  efﬁcient  than  fetching  a  different  cache  block  from  main
memory.

The  standard  RAM  model  measures  efﬁciency  of  a  hash-table
operation  by  counting  the  number  of  hash-table  slots  probed.  In
practice, this metric is only a crude approximation to the truth, since
once  a  cache  block  is  in  the  cache,  successive  probes  to  that  cache
block are much faster than probes that must access main memory.

Advanced  instruction  sets:  Modern  CPUs  may  have  sophisticated
instruction  sets  that  implement  advanced  primitives  useful  for
encryption or other forms of cryptography. These instructions may be
useful in the design of exceptionally efﬁcient hash functions.

Section  11.5.1  discusses  linear  probing,  which  becomes  the  collision-
resolution  method  of  choice  in  the  presence  of  a  memory  hierarchy.

Section  11.5.2  suggests  how  to  construct  “advanced”  hash  functions
based  on  cryptographic  primitives,  suitable  for  use  on  computers  with
hierarchical memory models.

11.5.1    Linear probing

Linear probing is often disparaged because of its poor performance in
the  standard  RAM  model.  But  linear  probing  excels  for  hierarchical
memory  models,  because  successive  probes  are  usually  to  the  same
cache block of memory.

Deletion with linear probing

Another reason why linear probing is often not used in practice is that
deletion  seems  complicated  or  impossible  without  using  the  special
DELETED  value.  Yet  we’ll  now  see  that  deletion  from  a  hash  table
based  on  linear  probing  is  not  all  that  difﬁcult,  even  without  the
DELETED  marker.  The  deletion  procedure  works  for  linear  probing,
but  not  for  open-address  probing  in  general,  because  with  linear
probing keys all follow the same simple cyclic probing sequence (albeit
with different starting points).

The deletion procedure relies on an “inverse” function to the linear-
probing hash function h(k, i) = (h1(k) + i) mod m, which maps a key k
and  a  probe  number  i  to  a  slot  number  in  the  hash  table.  The  inverse
function g maps a key k and a slot number q, where 0 ≤ q < m, to the
probe number that reaches slot q:

g(k, q) = (q − h1(k)) mod m.

If h(k, i) = q, then g(k, q) = i, and so h(k, g(k, q)) = q.

The procedure LINEAR-PROBING-HASH-DELETE on the facing
page deletes the key stored in position q from hash table T. Figure 11.6
shows how it works. The procedure ﬁrst deletes the key in position q by
setting T[q] to NIL in line 2. It then searches for a slot q′ (if any) that
contains a key that should be moved to the slot q just vacated by key k.
Line  9  asks  the  critical  question:  does  the  key  k′  in  slot  q′  need  to  be
moved to the vacated slot q in order to preserve the accessibility of k′?
If g(k′, q) < g(k′, q′), then during the insertion of k′ into the table, slot q

was examined but found to be already occupied. But now slot q, where a
search  will  look  for  k′,  is  empty.  In  this  case,  key  k′  moves  to  slot  q  in
line 10, and the search continues, to see whether any later key also needs
to be moved to the slot q′ that was just freed up when k′ moved.

Figure  11.6  Deletion  in  a  hash  table  that  uses  linear  probing.  The  hash  table  has  size  10  with
h1(k) = k mod 10. (a) The hash table after inserting keys in the order 74, 43, 93, 18, 82, 38, 92.
(b)  The  hash  table  after  deleting  the  key  43  from  slot  3.  Key  93  moves  up  to  slot  3  to  keep  it
accessible, and then key 92 moves up to slot 5 just vacated by key 93. No other keys need to be
moved.

LINEAR-PROBING-HASH-DELETE(T, q)
  1 while TRUE
  2

// make slot q empty
// starting point for search

T[q] = NIL
q′ = q
repeat

q′ = (q′ + 1) mod m // next slot number with linear probing
k′ = T[q′]
if k′ == NIL
return

// next key to try to move

until g(k′, q) < g(k′, q′)
T[q] = k′
q = q′

// return when an empty slot is found
// was empty slot q probed before q′?
// move k′ into slot q
// free up slot q′

  3

  4

  5

  6

  7

  8

  9

10

11

Analysis of linear probing

Linear probing is popular to implement, but it exhibits a phenomenon
known  as  primary  clustering.  Long  runs  of  occupied  slots  build  up,
increasing the average search time. Clusters arise because an empty slot
preceded by i full slots gets ﬁlled next with probability (i + 1)/m. Long
runs  of  occupied  slots  tend  to  get  longer,  and  the  average  search  time
increases.

In  the  standard  RAM  model,  primary  clustering  is  a  problem,  and
general double hashing usually performs better than linear probing. By
contrast,  in  a  hierarchical  memory  model,  primary  clustering  is  a
beneﬁcial  property,  as  elements  are  often  stored  together  in  the  same
cache  block.  Searching  proceeds  through  one  cache  block  before
advancing  to  search  the  next  cache  block.  With  linear  probing,  the
running  time  for  a  key  k  of  HASH-INSERT,  HASH-SEARCH,  or
LINEAR-PROBING-HASH-DELETE  is  at  most  proportional  to  the
distance from h1(k) to the next empty slot.

The  following  theorem  is  due  to  Pagh  et  al.  [351].  A  more  recent
proof is given by Thorup [438]. We omit the proof here. The need for 5-
independence is by no means obvious; see the cited proofs.

Theorem 11.9
If h1 is 5-independent and α ≤ 2/3, then it takes expected constant time
to search for, insert, or delete a key in a hash table using linear probing.

▪

(Indeed, the expected operation time is O(1/ϵ 2) for α = 1 − ϵ.)

★ 11.5.2 Hash functions for hierarchical memory models
This section illustrates an approach for designing efﬁcient hash tables in
a modern computer system having a memory hierarchy.

Because of the memory hierarchy, linear probing is a good choice for
resolving collisions, as probe sequences are sequential and tend to stay
within cache blocks. But linear probing is most efﬁcient when the hash
function  is  complex  (for  example,  5-independent  as  in  Theorem  11.9).

Fortunately,  having  a  memory  hierarchy  means  that  complex  hash
functions can be implemented efﬁciently.

As  noted  in  Section  11.3.5,  one  approach  is  to  use  a  cryptographic
hash  function  such  as  SHA-256.  Such  functions  are  complex  and
sufﬁciently  random  for  hash  table  applications.  On  machines  with
specialized instructions, cryptographic functions can be quite efﬁcient.

Instead,  we  present  here  a  simple  hash  function  based  only  on
addition,  multiplication,  and  swapping  the  halves  of  a  word.  This
function can be implemented entirely within the fast registers, and on a
machine  with  a  memory  hierarchy,  its  latency  is  small  compared  with
the time taken to access a random slot of the hash table. It is related to
the  RC6  encryption  algorithm  and  can  for  practical  purposes  be
considered a “random oracle.”

The wee hash function

Let w denote the word size of the machine (e.g., w = 64), assumed to be
even, and let a and b be w-bit unsigned (nonnegative) integers such that
a is odd. Let swap(x) denote the w-bit result of swapping the two w/2-bit
halves of w-bit input x. That is,

swap(x) = (x ⋙ (w/2)) + (x ⋘ (w/2))
where  “⋙”  is  “logical  right  shift”  (as  in  equation  (11.2))  and  “⋘  is
“left shift.” Deﬁne
fa(k) = swap((2k2 + ak) mod 2w).
Thus,  to  compute  fa(k),  evaluate  the  quadratic  function  2k2  +  ak
modulo 2w and then swap the left and right halves of the result.

Let  r  denote  a  desired  number  of  “rounds”  for  the  computation  of
the hash function. We’ll use r = 4, but the hash function is well deﬁned
 the result of iterating fa a total
for any nonnegative r. Denote by
of r times (that is, r rounds) starting with input value k. For any odd a
, although complicated, is one-to-one (see
and any r ≥ 0, the function

Exercise  11.5-1).  A  cryptographer  would  view
cipher operating on w-bit input blocks, with r rounds and key a.

  as  a  simple  block

We  ﬁrst  deﬁne  the  wee  hash  function  h  for  short  inputs,  where  by
“short” we means “whose length t is at most w-bits,” so that the input
ﬁts within one computer word. We would like inputs of different lengths
to be hashed differently. The wee hash function ha,b,t,r(k) for parameters
a, b, and r on t-bit input k is deﬁned as

That is, the hash value for t-bit input k is obtained by applying
 to k
+ b, then taking the ﬁnal result modulo m. Adding the value b provides
hash-dependent randomization of the input, in a way that ensures that
for variable-length inputs the 0-length input does not have a ﬁxed hash
value.  Adding  the  value  2t  to  a  ensures  that  the  hash  function  acts
differently  for  inputs  of  different  lengths.  (We  use  2t  rather  than  t  to
ensure that the key a + 2t is odd if a is odd.) We call this hash function
“wee” because it uses a tiny amount of memory—more precisely, it can
be implemented efﬁciently using only the computer’s fast registers. (This
hash function does not have a name in the literature; it is a variant we
developed for this textbook.)

Speed of the wee hash function

It  is  surprising  how  much  efﬁciency  can  be  bought  with  locality.
Experiments  (unpublished,  by  the  authors)  suggest  that  evaluating  the
wee hash function takes less time than probing a single randomly chosen
slot  in  a  hash  table.  These  experiments  were  run  on  a  laptop  (2019
MacBook  Pro)  with  w  =  64  and  a  =  123.  For  large  hash  tables,
evaluating  the  wee  hash  function  was  2  to  10  times  faster  than
performing a single probe of the hash table.

The wee hash function for variable-length inputs

Sometimes  inputs  are  long—more  than  one  w-bit  word  in  length—or
have variable length, as discussed in Section 11.3.5. We can extend the
wee hash function, deﬁned above for inputs that are at most single w-bit

word  in  length,  to  handle  long  or  variable-length  inputs.  Here  is  one
method for doing so.

Suppose that an input k has length t (measured in bits). Break k into
a sequence 〈k1, k2, …, ku〉 of w-bit words, where u = ⌈t/w⌉, k1 contains
the  least-signiﬁcant  w  bits  of  k,  and  ku  contains  the  most  signiﬁcant
bits.  If  t  is  not  a  multiple  of  w,  then  ku  contains  fewer  than  w  bits,  in
which case, pad out the unused high-order bits of ku with 0-bits. Deﬁne
the function chop to return a sequence of the w-bit words in k:

chop(k) = 〈k1, k2, …, ku〉.

The most important property of the chop operation is that it is one-to-
one,  given  t:  for  any  two  t-bit  keys  k  and  k′,  if  k  ≠  k′  then  chop(k)  ≠
chop(k′), and k can be derived from chop(k) and t. The chop operation
also has the useful property that a single-word input key yields a single-
word output sequence: chop(k) = 〈k〉.

With  the  chop  function  in  hand,  we  specify  the  wee  hash  function

ha,b,t,r(k) for an input k of length t bits as follows:

ha,b,t,r(k) = WEE(k, a, b, t, r, m),

where  the  procedure  WEE  deﬁned  on  the  facing  page  iterates  through
 to the
the elements of the w-bit words returned by chop(k), applying
sum of the current word ki and the previously computed hash value so
far,  ﬁnally  returning  the  result  obtained  modulo  m.  This  deﬁnition  for
variable-length and long (multiple-word) inputs is a consistent extension
of  the  deﬁnition  in  equation  (11.7)  for  short  (single-word)  inputs.  For
practical  use,  we  recommend  that  a  be  a  randomly  chosen  odd  w-bit
word, b be a randomly chosen w-bit word, and that r = 4.

Note that the wee hash function is really a hash function family, with
individual  hash  functions  determined  by  parameters  a,  b,  t,  r,  and  m.
The (approximate) 5-independence of the wee hash function family for
variable-length inputs can be argued based on the assumption that the
1-word wee hash function is a random oracle and on the security of the
cipher-block-chaining  message  authentication  code  (CBC-MAC),  as
studied by Bellare et al. [42]. The case here is actually simpler than that

studied  in  the  literature,  since  if  two  messages  have  different  lengths  t
and  t′,  then  their  “keys”  are  different:  a  +  2t  ≠  a  +  2t′.  We  omit  the
details.

WEE(k, a, b, t, r, m)
1 u = ⌈t/w⌉
2 〈k1, k2, …, ku〉 = chop(k)
3 q = b
4 for i = 1 to u
5

6 return q mod m

This deﬁnition of a cryptographically inspired hash-function family
is  meant  to  be  realistic,  yet  only  illustrative,  and  many  variations  and
improvements are possible. See the chapter notes for suggestions.

In summary, we see that when the memory system is hierarchical, it
becomes  advantageous  to  use  linear  probing  (a  special  case  of  double
hashing), since successive probes tend to stay in the same cache block.
Furthermore,  hash  functions  that  can  be  implemented  using  only  the
computer’s fast registers are exceptionally efﬁcient, so they can be quite
complex and even cryptographically inspired, providing the high degree
of independence needed for linear probing to work most efﬁciently.

Exercises

★ 11.5-1
Complete  the  argument  that  for  any  odd  positive  integer  a  and  any
  is  one-to-one.  Use  a  proof  by
integer  r  ≥  0,  the  function
contradiction  and  make  use  of  the  fact  that  the  function  fa  works
modulo 2w.

★ 11.5-2
Argue that a random oracle is 5-independent.

★ 11.5-3
Consider  what  happens  to  the  value

the  input  value  k,  for  various  values  of  r.  Let

  as  we  ﬂip  a  single  bit  ki  of
  and
 deﬁne the bit values ki in the input (with k0 the least-
signiﬁcant  bit)  and  the  bit  values  bj  in  ga(k)  =  (2k2  +  ak)  mod  2w
(where  ga(k)  is  the  value  that,  when  its  halves  are  swapped,  becomes
fa(k)). Suppose that ﬂipping a single bit ki of the input k may cause any
bit  bj  of  ga(k)  to  ﬂip,  for  j  ≥  i.  What  is  the  least  value  of  r  for  which
ﬂipping  the  value  of  any  single  bit  ki  may  cause  any  bit  of  the  output

 to ﬂip? Explain.

Problems

11-1     Longest-probe bound for hashing
Suppose you are using an open-addressed hash table of size m to store n
≤ m/2 items.

a. Assuming independent uniform permutation hashing, show that for i

= 1, 2, …, n, the probability is at most 2−p that the ith insertion
requires strictly more than p probes.

b. Show that for i = 1, 2, …, n, the probability is O(1/n2) that the ith

insertion requires more than 2 lg n probes.

Let  the  random  variable  Xi  denote  the  number  of  probes  required  by
the  ith  insertion.  You  have  shown  in  part  (b)  that  Pr{Xi  >  2  lg  n}  =
O(1/n2).  Let  the  random  variable  X  =  max  {Xi  :  1  ≤  i  ≤  n}  denote  the
maximum number of probes required by any of the n insertions.

c. Show that Pr{X > 2 lg n} = O(1/n).

d. Show that the expected length E[X] of the longest probe sequence is

O(lg n).

11-2     Searching a static set
You are asked to implement a searchable set of n elements in which the
keys  are  numbers.  The  set  is  static  (no  INSERT  or  DELETE
operations), and the only operation required is SEARCH. You are given
an  arbitrary  amount  of  time  to  preprocess  the  n  elements  so  that
SEARCH operations run quickly.

a. Show how to implement SEARCH in O(lg n) worst-case time using
no extra storage beyond what is needed to store the elements of the
set themselves.

b. Consider implementing the set by open-address hashing on m slots,
and assume independent uniform permutation hashing. What is the
minimum amount of extra storage m − n required to make the average
performance of an unsuccessful SEARCH operation be at least as
good as the bound in part (a)? Your answer should be an asymptotic
bound on m − n in terms of n.

11-3     Slot-size bound for chaining
Given  a  hash  table  with  n  slots,  with  collisions  resolved  by  chaining,
suppose that n keys are inserted into the table. Each key is equally likely
to  be  hashed  to  each  slot.  Let  M  be  the  maximum  number  of  keys  in
any slot after all the keys have been inserted. Your mission is to prove
an O(lg n / lg lg n) upper bound on E[M], the expected value of M.

a. Argue that the probability Qk that exactly k keys hash to a particular

slot is given by

b. Let Pk be the probability that M = k, that is, the probability that the
slot containing the most keys contains k keys. Show that Pk ≤ nQk.
c. Show that Qk < ek/kk. Hint: Use Stirling’s approximation, equation
(3.25) on page 67.

d. Show that there exists a constant c > 1 such that
c lg n / lg lg n. Conclude that Pk < 1/n2 for k ≥ k0 = c lg n / lg lg n.
e. Argue that

 for k0 =

Conclude that E[M] = O(lg n / lg lg n).

11-4     Hashing and authentication
Let H be a family of hash functions in which each hash function h ∈
H maps the universe U of keys to {0, 1, …, m − 1}.
a. Show that if the family H of hash functions is 2-independent, then it

is universal.

b. Suppose that the universe U is the set of n-tuples of values drawn

from ℤp = {0, 1, …, p − 1}, where p is prime. Consider an element x =
〈x0, x1, …, xn−1〉 ∈ U. For any n-tuple a = 〈a0, a1, …, an−1〉 ∈ U,
deﬁne the hash function ha by

Let  H  =  {ha  :  a  ∈  U}.  Show  that  H  is  universal,  but  not  2-
independent.  (Hint:  Find  a  key  for  which  all  hash  functions  in  H
produce the same value.)

c. Suppose that we modify H slightly from part (b): for any a ∈ U and

for any b ∈ ℤp, deﬁne

.  Argue  that  H′  is  2-independent.
and
(Hint: Consider ﬁxed n-tuples x ∈ U and y ∈ U, with xi ≠ yi for some

i. What happens to

 and

 as ai and b range over ℤp?)

d. Alice and Bob secretly agree on a hash function h from a 2-

independent family H of hash functions. Each h ∈ H maps from a
universe of keys U to ℤp, where p is prime. Later, Alice sends a
message m to Bob over the internet, where m ∈ U. She authenticates
this message to Bob by also sending an authentication tag t = h(m),
and Bob checks that the pair (m, t) he receives indeed satisﬁes t =
h(m). Suppose that an adversary intercepts (m, t) en route and tries to
fool Bob by replacing the pair (m, t) with a different pair (m′, t′).
Argue that the probability that the adversary succeeds in fooling Bob
into accepting (m′, t′) is at most 1/p, no matter how much computing
power the adversary has, even if the adversary knows the family H of
hash functions used.

Chapter notes

The  books  by  Knuth  [261]  and  Gonnet  and  Baeza-Yates  [193]  are
excellent  references  for  the  analysis  of  hashing  algorithms.  Knuth
credits  H.  P.  Luhn  (1953)  for  inventing  hash  tables,  along  with  the
chaining method for resolving collisions. At about the same time, G. M.
Amdahl  originated  the  idea  of  open  addressing.  The  notion  of  a
random  oracle  was  introduced  by  Bellare  et  al.  [43].  Carter  and
Wegman  [80]  introduced  the  notion  of  universal  families  of  hash
functions in 1979.

Dietzfelbinger  et  al.  [113]  invented  the  multiply-shift  hash  function
and  gave  a  proof  of  Theorem  11.5.  Thorup  [437]  provides  extensions
and  additional  analysis.  Thorup  [438]  gives  a  simple  proof  that  linear
probing  with  5-independent  hashing  takes  constant  expected  time  per
operation. Thorup also describes the method for deletion in a hash table
using linear probing.

Fredman, Komlós, and Szemerédi [154] developed a perfect hashing
scheme for static sets—“perfect” because all collisions are avoided. An
extension  of  their  method  to  dynamic  sets,  handling  insertions  and

deletions
Dietzfelbinger et al. [114].

in  amortized  expected  time  O(1),  has  been  given  by

The  wee  hash  function  is  based  on  the  RC6  encryption  algorithm
[379].  Leiserson  et  al.  [292]  propose  an  “RC6MIX”  function  that  is
essentially  the  same  as  the  wee  hash  function.  They  give  experimental
evidence that it has good randomness, and they also give a “DOTMIX”
function  for  dealing  with  variable-length  inputs.  Bellare  et  al.  [42]
provide an analysis of the security of the cipher-block-chaining message
authentication  code.  This  analysis  implies  that  the  wee  hash  function
has the desired pseudorandomness properties.

1 The deﬁnition of “average-case” requires care—are we assuming an input distribution over the
keys, or are we randomizing the choice of hash function itself ? We’ll consider both approaches,
but with an emphasis on the use of a randomly chosen hash function.
2  In  the  literature,  a  (c/m)-universal  hash  function  is  sometimes  called  c-universal  or  c-
approximately universal. We’ll stick with the notation (c/m)-universal.

