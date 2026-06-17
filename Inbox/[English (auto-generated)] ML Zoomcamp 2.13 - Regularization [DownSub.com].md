welcome back this is lesson 13 of
machine learning zoom comp session 2 and
we will talk about regularization
in the previous lesson we added
categorical variables so we implemented
some code for handling these categorical
variables and we added
them to our prepare x function
and actually this is not the same code i
used for the previous lesson i lost this
code and i had to rewrite it but i think
this is
very similar to
what we had to do
and then we extracted the
future matrix x and then we had a very
very high root means character so i
think in the previous video the
it was a
little bit lower but yeah it was very
high and when we looked at weights the
weights were very high
in this lesson we will look why it
happens remember the formula for a
normal equation is this so for draining
our model so we have this gram matrix
and then we multiply it by x transpose
and then we multiply it by y
and this is our w
so the issue
the problem we have here is this
with this part so we need to take an
inverse of this graph matrix sometimes
this inverse doesn't exist
so it usually happens when we have
x which is our matrix right so we have
multiple columns multiple rows
and sometimes in this matrix the future
vertex some features are could be let's
say we have column two and column three
they could be duplicate features
um and in this case um usually the
inverse of
x transpose x doesn't exist so we can
quickly
uh check it so i prepared the matrix
here
that
see that
the first column is different but second
and third they have the same values so
it's a duplicate
duplicate columns column so let's turn
it into
a numpy array
so yeah we have this mat xx with our
features
and now we want to compute this
gram matrix
here what we see is
this column and this column has the same
values so in this case when something
like that happens
uh in a matrix we want to invert
the inverse simply doesn't exist because
there is uh
in linear algebra we say that one column
is a linear combination of other columns
which means that it's possible to
express the column number three with
other columns of the matrix which is
basically just a duplicate of column two
right
so let's see what happens when we try to
inverse it and then we use this function
for computing the inverse
and it now complains that this matrix is
singular i cannot compute the inverse of
this
right
so the inverse of this x transpose x
doesn't always exist
this is not the case though for our
particular problem so here we didn't
have any so we didn't see this error
that
this is a singular matrix
and the reason for that usually the data
is not
super
clean
in a way that sometimes there is noise
so let's say
when we record
our observations sometimes maybe instead
of writing five we just write five zero
uh five point zero zero zero one right
so in this case so
it's still the same matrix except we add
a tiny number here to one of the uh to
one of the
values here
right
and then in this case we can see that
this is how
the trans uh this gram matrix looks like
here these two columns are no longer um
the same so they are a little bit
different so this one
has this 0.05
and this one has
so basically they have
they're slightly different so now this
matrix
is not exactly singular anymore so the
this column third column is not
a duplicate of the
second column anymore and what happens
is this matrix becomes actually
invertible um at least numerically
invertible
so we see these huge numbers here right
so let us let's write it
to
inverse right so it tries to find the
inverse even though the inverse
shouldn't exist so it kind of comes up
with these huge numbers right so we have
these are very very huge numbers
and when we uh multiply this so when we
multiply it by
x transposed by
y i think we need the y as well
so
y could be
i know one two three
one two three four
so we have yeah we actually have three
um yeah we have three observations here
so if our y looks like that
then
to compute the w
we
uh yeah so what we end up
uh
finding is that for this feature it's
fine and this is the unique feature
but for this for the second and the for
the third one
um it's basically just some large large
numbers when we have a situation like
that when we have let's say duplicates
in our feature matrix then we have this
problem
so to solve this problem what we can do
is we can add a small number to
the diagonal of this matrix so let's say
if we add a small number uh i'll call it
alpha here on the diagonal then it
should solve our problem so let me
let me show you
that on a smaller example
so
let's take a smaller matrix
um that we can use to illustrate this
use something like this
right so we again have a
column that is a duplicate with another
column
and
so what we want to do is now
put it into array
and
try to
inverse it
so it complains of course because we
need to
add a small number here let's see and
here
so now yeah you see that
it actually is able to find an inverse
but the numbers are still quite big so i
think if we do if we add a few numbers
here so they become even larger
and as i said one way of fixing this
problem is to add
a small number to the diagonal
so we add a small number to the diagonal
and now that this helps control
so now these numbers became smaller and
the larger the numbers we add to the
diagonal
the the more we have these weights under
control
and the reason it works because by
adding something on the diagonal we make
sure that
now it's
less possible that this column call
number three is a
duplicator of column number two
to implement that let's say if we now
undo
uh undo everything so let's make it uh
let's remove
so now yeah we again have this problem
and what we can do
is
to add the same number to the diagonal
is remember we have this
i matrix
say
of size
3 right so this is the our identity
matrix
when we add this x to x
matrix to our identity matrix it adds
one on the diagonal right so here we
used to have one now we have two
here we have two here we have two
so now we can actually multiply this i
by some small number
let's say and then this way we add only
that small number to the diagonal let's
call this uh also
x transpose x
and when we
try to invert it now we don't have this
problem anymore
so this is how we solve this problem and
this is uh called regularization so we
kind of regularization i think means
here controlling so we're controlling
the weights that they don't go
uh that they don't grow too much
and
this thing here is actually a parameter
right so the larger number we have on
the diagonal the smaller
actually the values here of this
inverse of x dx right so if we have
something
even bigger here you see these numbers
are very far from what we used to have
previously
so in a way this becomes a parameter
like how much regularization we add to
our matrix
and with that now we can
pre-implement the function we have
yeah this one
so
let's
take
this and slightly change it
i'll just call it
drain linear regression regularized
and then we have one more parameter
which i will call r
which is short for regularization
and
let's say we can have some default
parameter for this which is
0.01
and what we need to do here is we need
to
basically
add that
so
to add
a small number to the diagonal
so we need to have to know the size of
our xx
shape
zero
so now it will create it will add
we need actually r so we'll
add this amount to the main diagonal and
the rest stays the same
all right
so let's secure it
and what we need to do is we can
actually take
this what we have here
and just replace this function that we
used previously
by
this new function and let's use
some
value for r
again we see that this result is
actually not only it's much better one
that we have with not regularized
version but it's also better than what
we have
what we had before
so it's
actually like 0.5
so this is what we had previously so
it's
approximately 0.5 improvement which is
i would say it's a considerable
improvement
so
yeah so by adding a number to the
diagonal we were able to
control our weights to regulate the
regular race our model and this r is a
parameter so because if we set it too
high then maybe our model becomes worse
right so maybe
we said it too high yeah you see like
our model becomes like it's very
difficult for model to work
and if we set it to too low let's say if
we use zero then we are back to the
usual
linear regression so now we actually
need to find
what is the best value for r and this is
what we will do in the next lesson