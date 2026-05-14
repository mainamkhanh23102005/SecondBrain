for

.

C.2 Probability

Probability  is  an  essential  tool  for  the  design  and  analysis  of
probabilistic  and  randomized  algorithms.  This  section  reviews  basic
probability theory.

We  deﬁne  probability  in  terms  of  a  sample  space  S,  which  is  a  set
whose elements are called outcomes or elementary events. Think of each
outcome  as  a  possible  result  of  an  experiment.  For  the  experiment  of
ﬂipping two distinguishable coins, with each individual ﬂip resulting in a
head (H) or a tail (T), you can view the sample space S as consisting of
the set of all possible 2-strings over {H, T}:

S = {HH, HT, TH, TT}.

An  event  is  a  subset1  of  the  sample  space  S.  For  example,  in  the
experiment of ﬂipping two coins, the event of obtaining one head and
one  tail  is  {HT,  TH}.  The  event  S  is  called  the  certain  event,  and  the
event  ∅  is  called  the  null  event.  We  say  that  two  events  A  and  B  are
mutually  exclusive  if  A  ∩  B  =  ∅.  An  outcome  s  also  deﬁnes  the  event
{s}, which we sometimes write as just s. By deﬁnition, all outcomes are
mutually exclusive.

Axioms of probability

A probability distribution Pr {} on a sample space S is a mapping from
events of S to real numbers satisfying the following probability axioms:

1. Pr {A} ≥ 0 for any event A.

2. Pr {S} = 1.
3. Pr  {A  ∪  B}  =  Pr  {A}  +  Pr  {B}  for  any  two  mutually  exclusive
events A and B. More generally, for any sequence of events A1,

A2,  …  (ﬁnite  or  countably  inﬁnite)  that  are  pairwise  mutually
exclusive,

We  call  Pr  {A}  the  probability  of  the  event  A.  Axiom  2  is  simply  a
normalization  requirement:  there  is  really  nothing  fundamental  about
choosing  1  as  the  probability  of  the  certain  event,  except  that  it  is
natural and convenient.

Several  results  follow  immediately  from  these  axioms  and  basic  set
theory (see Section B.1). The null event ∅ has probability Pr {∅} = 0. If
A ⊆ B, then Pr {A} ≤ Pr {B}. Using Ā to denote the event S − A (the
complement of A), we have Pr {Ā} = 1 − Pr {A}. For any two events A
and B,

In  our  coin-ﬂipping  example,  suppose  that  each  of  the  four
outcomes  has  probability  1/4.  Then  the  probability  of  getting  at  least
one head is

Pr {HH, HT, TH} = Pr {HH} + Pr {HT} + Pr {TH}

= 3/4.

Another  way  to  obtain  the  same  result  is  to  observe  that  since  the
probability  of  getting  strictly  less  than  one  head  is  Pr  {TT}  =  1/4,  the
probability of getting at least one head is 1 − 1/4 = 3/4.

Discrete probability distributions

A  probability  distribution  is  discrete  if  it  is  deﬁned  over  a  ﬁnite  or
countably inﬁnite sample space. Let S be the sample space. Then for any
event A,

since  outcomes,  speciﬁcally  those  in  A,  are  mutually  exclusive.  If  S  is
ﬁnite and every outcome s ∈ S has probability Pr {s} = 1/|S|, then we
have  the  uniform  probability  distribution  on  S.  In  such  a  case  the
experiment is often described as “picking an element of S at random.”

As  an  example,  consider  the  process  of  ﬂipping  a  fair  coin,  one  for
which the probability of obtaining a head is the same as the probability
of  obtaining  a  tail,  that  is,  1/2.  Flipping  the  coin  n  times  gives  the
uniform  probability  distribution  deﬁned  on  the  sample  space  S  =  {H,
T}n, a set of size 2n. We can represent each outcome in S as a string of
length n over {H, T}, with each string occurring with probability 1/2n.
The event A = {exactly k heads and exactly n − k tails occur} is a subset
of  S  of  size
  strings  of  length  n  over  {H,  T}  contain
,  since
exactly kH’s. The probability of event A is thus

.

Continuous uniform probability distribution

The  continuous  uniform  probability  distribution  is  an  example  of  a
probability distribution in which not all subsets of the sample space are
considered
to  be  events.  The  continuous  uniform  probability
distribution is deﬁned over a closed interval [a, b] of the reals, where a <
b.  The  intuition  is  that  each  point  in  the  interval  [a,  b]  should  be
“equally  likely.”  Because  there  are  an  uncountable  number  of  points,
however, if all points had the same ﬁnite, positive probability, axioms 2
and  3  would  not  be  simultaneously  satisﬁed.  For  this  reason,  we’d  like
to associate a probability only with some of the subsets of S in such a
way that the axioms are satisﬁed for these events.

For  any  closed  interval  [c,  d],  where  a  ≤  c  ≤  d  ≤  b,  the  continuous
uniform probability distribution deﬁnes the probability of the event [c, d]
to be

Letting c = d gives that the probability of a single point is 0. Removing
the  endpoints  [c,  c]  and  [d,  d]  of  an  interval  [c,  d]  results  in  the  open
interval (c, d). Since [c, d] = [c, c] ∪ (c, d) ∪ [d, d], axiom 3 gives Pr {[c,
d]} = Pr {(c, d)}. Generally, the set of events for the continuous uniform

probability  distribution  contains  any  subset  of  the  sample  space  [a,  b]
that can be obtained by a ﬁnite or countable union of open and closed
intervals, as well as certain more complicated sets.

Conditional probability and independence

Sometimes  you  have  some  prior  partial  knowledge  about  the  outcome
of  an  experiment.  For  example,  suppose  that  a  friend  has  ﬂipped  two
fair coins and has told you that at least one of the coins showed a head.
What  is  the  probability  that  both  coins  are  heads?  The  information
given  eliminates  the  possibility  of  two  tails.  The  three  remaining
outcomes  are  equally  likely,  and  so  you  infer  that  each  occurs  with
probability 1/3. Since only one of these outcomes shows two heads, the
answer is 1/3.

Conditional probability formalizes the notion of having prior partial
knowledge  of  the  outcome  of  an  experiment.  The  conditional
probability of an event A given that another event B occurs is deﬁned to
be

whenever Pr {B} ≠ 0. (Read “Pr {A | B}” as “the probability of A given
B.”)  The  idea  behind  equation  (C.16)  is  that  since  we  are  given  that
event B occurs, the event that A also occurs is A ∩ B. That is, A ∩ B is
the set of outcomes in which both A and B occur. Because the outcome
is one of the elementary events in B, we normalize the probabilities of
all the elementary events in B by dividing them by Pr {B}, so that they
sum  to  1.  The  conditional  probability  of  A  given  B  is,  therefore,  the
ratio of the probability of event A ∩ B to the probability of event B. In
the example above, A is the event that both coins are heads, and B is the
event  that  at  least  one  coin  is  a  head.  Thus,  Pr  {A  |  B}  =  (1/4)/(3/4)  =
1/3.

Two events are independent if

which is equivalent, if Pr {B} ≠ 0, to the condition

Pr {A | B} = Pr {A}.

For example, suppose that you ﬂip two fair coins and that the outcomes
are independent. Then the probability of two heads is (1/2)(1/2) = 1/4.
Now  suppose  that  one  event  is  that  the  ﬁrst  coin  comes  up  heads  and
the  other  event  is  that  the  coins  come  up  differently.  Each  of  these
events occurs with probability 1/2, and the probability that both events
occur  is  1/4.  Thus,  according  to  the  deﬁnition  of  independence,  the
events are independent—even though you might think that both events
depend  on  the  ﬁrst  coin.  Finally,  suppose  that  the  coins  are  welded
together so that they both fall heads or both fall tails and that the two
possibilities are equally likely. Then the probability that each coin comes
up heads is 1/2, but the probability that they both come up heads is 1/2
≠  (1/2)(1/2).  Consequently,  the  event  that  one  comes  up  heads  and  the
event that the other comes up heads are not independent.

A  collection  A1,  A2,  …  ,  An  of  events  is  said  to  be  pairwise

independent if

Pr {Ai ∩ Aj } = Pr {Ai} Pr {Aj}

for  all  1  ≤  i  <  j  ≤  n.  We  say  that  the  events  of  the  collection  are
  of  the  collection,
(mutually)  independent  if  every  k-subset
where 2 ≤ k ≤ n and 1 ≤ i1 < i2 < ⋯ < ik ≤ n, satisﬁes

For  example,  suppose  that  you  ﬂip  two  fair  coins.  Let  A1  be  the  event
that  the  ﬁrst  coin  is  heads,  let  A2  be  the  event  that  the  second  coin  is
heads, and let A3 be the event that the two coins are different. Then,

Pr {A1} = 1/2,
Pr {A2} = 1/2,
Pr {A3} = 1/2,
Pr {A1 ∩ A2} = 1/4,
Pr {A1 ∩ A3} = 1/4,

Pr {A2 ∩ A3} = 1/4,
Pr {A1 ∩ A2 ∩ A3} = 0.

Since for 1 ≤ i < j ≤ 3, we have Pr {Ai ∩ Aj } = Pr {Ai} Pr {Aj} = 1/4, the
events  A1,  A2,  and  A3  are  pairwise  independent.  The  events  are  not
mutually independent, however, because Pr {A1 ∩ A2 ∩ A3} = 0 and Pr
{A1} Pr {A2} Pr {A3} = 1/8 ≠ 0.

Bayes’s theorem

From  the  deﬁnition  (C.16)  of  conditional  probability  and  the
commutative law A ∩ B = B ∩ A, it follows that for two events A and B,
each with nonzero probability,

Solving for Pr {A | B}, we obtain

which  is  known  as  Bayes’s  theorem.  The  denominator  Pr  {B}  is  a
normalizing  constant,  which  we  can  reformulate  as  follows.  Since  B  =
(B ∩ A) ∪ (B ∩ Ā), and since B ∩ A and B ∩ Ā are mutually exclusive
events,

Pr {B} = Pr {B ∩ A} + Pr {B ∩ Ā}

= Pr {A} Pr {B | A} + Pr {Ā} Pr {B | Ā}.

Substituting  into  equation  (C.19)  produces  an  equivalent  form  of
Bayes’s theorem:

Bayes’s  theorem  can  simplify  the  computing  of  conditional
probabilities.  For  example,  suppose  that  you  have  a  fair  coin  and  a
biased coin that always comes up heads. Run an experiment consisting

of  three  independent  events:  choose  one  of  the  two  coins  at  random,
ﬂip that coin once, and then ﬂip it again. Suppose that the coin you have
chosen comes up heads both times. What is the probability that it’s the
biased coin?

Bayes’s  theorem  solves  this  problem.  Let  A  be  the  event  that  you
choose  the  biased  coin,  and  let  B  be  the  event  that  the  chosen  coin
comes up heads both times. We wish to determine Pr {A | B}, knowing
that Pr {A} = 1/2, Pr {B | A} = 1, Pr {Ā} = 1/2, and Pr {B | Ā = 1/4.
Thus we have

Exercises

C.2-1

Professor  Rosencrantz  ﬂips  a  fair  coin  twice.  Professor  Guildenstern
ﬂips a fair coin once. What is the probability that Professor Rosencrantz
obtains strictly more heads than Professor Guildenstern?

C.2-2
Prove Boole’s inequality: For any ﬁnite or countably inﬁnite sequence of
events A1, A2, …,

C.2-3

You shufﬂe a deck of 10 cards, each bearing a distinct number from 1 to
10, in order to mix the cards thoroughly. You then remove three cards,
one at a time, from the deck. What is the probability that the three cards
you select are in sorted (increasing) order?

C.2-4
Prove that

Pr {A | B} + Pr {Ā | B} = 1.

