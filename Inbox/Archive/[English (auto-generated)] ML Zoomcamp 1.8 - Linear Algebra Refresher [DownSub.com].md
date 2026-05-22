welcome back this is lesson four of
machine learning zoom comp session one
and we will talk about linear algebra
now
so we'll talk about simple uh
simple operations of linear algebra like
vector operations we'll talk about
multiplication and we talk about a
special operation called matex inverse
so we'll start with the simple vector
operation which is
multiplication so if you want to
multiply a vector by some number
uh so let's say we want to multiply a
vector by number two what we do is we
multiply every element of this
this this vector by two
so in this case it's 4
8
10
12.
and you see that the the way i write
vector is it's like a column so it's a
column
column vector
and this is just a notation this is how
things are usually written in linear
algebra so in linear algebra typically
the vectors are columns not
not rows
if you remember the way we did it in
numpy
so let me just quickly show you
so in numpy actually the vectors are
rows
so here we have it as a row notice the
column so this is just the convention so
this is just how
things are written usually in linear
algebra so they are columns
and if we want to add two vectors let's
say this is vector u
this is vector v so what we do
is and if we want to
add two vectors what we do is
we add
each element of a vector and the result
is
so 3
4
5
so so this is pretty much the same
um
as we saw in the previous lecture in
numpy so we just add things element-wise
so if you see so here i have these two
vectors
u and v
and if we at u plus b then we have
element wise addition
and
yeah here you you remember from the
previous lecture that we can multiply
a numpy array by two and then it the
result is multiplication element wise so
this is
basically the same happens in
linear algebra
now we'll talk a bit about more
interesting things about
how we can multiply vectors with vectors
and how we can multiply a matrix by a
vector and how we can multiply
a matrix by matrix so let's start with
vector vector multiplication so it's
also called dot product or sometimes
inner product so let's say again we have
two vectors
u and v
and we want to multiply vector u by
vector v
and this is not element by
multiplication like we do in numpy so
remember in numpy
if
we do this u times v
so we have an array where we
[Music]
multiply elements
element wise we have element device
multiplication so actually in linear
algebra this dot product produces a
number
so the way
we compute it
is uh
we multiply again each
number separately like for uh
for element for the first element of u
multiplied with the first element of v
for second element of u we multiply the
second element of v and so on
and what we get is 2 times 1
so here we have
4 times 0
5 times 0 6 times 2 and then what we do
we
[Music]
sum them some results
and what we have
as a result is we have
2 plus 12 here
and the result is 14.
so basically
the formula if we want to write the
formula so we have a sum that goes uh
over all elements of
of our
vectors
right so
let's say it calls goes from one uh till
n
where n is dimension of the vector
and then we just multiply if
element of u
with the if element of v
and this is the result of a dot product
so we just saw it
however the way we usually write it in
linear algebra is uh maybe it's a bit
intuitive at first so the way we do it
is
so this is remember so this is u
which is a column vector
but
this this is we
which is a
row vector
and if we want to turn a column vector
into a row vector we use a transpose
operation so transpose operation turns
columns into rows and so this is again
this is just notation so if we want to
uh and you will see later when we
multiply matrix with vectors y is the
case
but this is just notation for dot
product so
we
for for multiplication we will need to
have a row vector and a column vector
and the result is a dot product
so
this is how we usually
write dot product so this is annotation
for dot product
and as we already
uh
saw
that the formula for computing the dot
product
is like this so until e goes from
uh first element to the last element
so this is the
the dot product we can quickly implement
it so let's say
yeah we want to write a function
that does vector vector multiplication
multiplication and then we have two
vectors here u and v
so first what we need to do is make sure
that these vectors have the same size
and we usually do this by checking the
shape of the vectors
so if you remember so let me
let me just show you
what shapes prints shape the shape is
the size of the
the
the array
right and the
first element of this tuple is four
right and then
v
should also have four
and if they are different then
multiplication doesn't make sense so we
need to have to make sure that
the vectors have the same size so that's
why we have this assertion here
and then
yes basically
what we do next is
again in our formula we have also n
which is the number of
elements the vector have
so let's say we can write that n is
this shape of u or shape of e doesn't
matter because they have the same shape
and we just go over a loop
go over all the elements
here of the the arrays
so we say okay we first need to have a
result
the result variable which contains our
dot product
right and then we say that result
should contain
so first of all
so we do this product between each
element so
let me just draw the formula here
so the formula is uh if element of u
times uh is element of b right and then
we go from
one to n
so actually because we are in race
and numpy arrays are indexed from
0 to
n minus 1
and then the size of the array is n so
instead of going from
1 to n we go from
0 to n minus 1
and
this is how we implement this right so
we have
this part here
which corresponds to
the part inside the sum
and this for loop is actually the sum
and then what we need to do at the end
is just return the result
so this is how we translate this formula
into code
so now we can test it
vector vector multiplication between u
and v
so it should return 14.
so
yes like we calculated
actually in uh
in numpy there is already a function
that is doing this it's called dot
product
and we this is how we use it we just
multiply vector u by a vector v
and the result is also 14.
so this is how we translate this formula
into code so we talked about vector
vector multiplication now let's talk
about
matrix vector multiplication
so in matrix vector multiplication so
let's say we have this matrix u
that we want to multiply by a vector v
so this is a capital
and this is lowercase so we want to
actually
compute u times v so u is a matrix
v is a vector
and the way we do it
is
so take the
first row of
matrix u
and multiply it with
the vector v so you see this is a row
and we multiply it by b so this is
exactly like we have here so we have a
row vector and the column vector and
again we have a row
vector here so this is let's call it
u
0 so we will just use the the same
notation as in
numpy so we'll start with zero so you
want
your first and your second
right so what we
need to do now to calculate uh
the multiplication between matrix and
vector
for each row of the matrix
we multiply it with v
okay so this is how we
[Music]
do this so we take the
zero
row of u
and multiplied with b
then we take the first row of u and
multiply it with b
and the second row and multiply
right so this is the result so basically
for each row we do a matrix sorry for
each row of u we do a vector vector
multiplication with v so this is how we
compute uh
matrix vector multiplication so let me
just
write it once again so let's say we have
this
vector u
matrix u
and then we have
let's say we have
k elements of uh here so from u
to
u
k minus 1.
so in total there are
k
rows
and we want to multiply it with
vector v
so this will be just
vector v
and of course dimensionality here should
match so
this vector here
and this vector here should be the same
see let's say dimensionality can be n so
both have n elements
and yeah and the result is a
dot product between each row of the
matrix u and the vector
and vector v
so
this is how we do it let's implement
this in numpy
so let's implement it in python
so we i already have the
the matrix u here
this is it
and let's implement
matrix
vector
multiplication
so we have a
big capital u and i use capital here to
denote that this is matrix
so first we need to make sure that
dimensionality match and if you remember
so here we will have the shape
field
here and
we are interested in the number of
columns so remember here if i go back so
the number of columns in u
should match uh the number of elements
in v so the number of columns in u is
basically the dimensionality of each
row vector of u right so if there are
four columns it means that the
the vector u0 has dimensionality of four
it has four elements
so it means that
the
the second
dimension the number of columns should
match the first dimension so then we
have the number of rows we can use k or
maybe we just put
code number of rows
which is cu shape
zero
so this is uh the dimensionality of our
resulting vector so this is the results
so because we have three rows
so there are three rows in
in matrix u that's why we have three
elements in the result of the
multiplication
so
this is our result matrix
let's initialize it with zeros
and number of uh
the dimensionality of this this vector
the size of this array
is a number of rows so okay
and then we have a loop um so we want
now to go through
uh each row of the matrix u
so we do this
loop
and now we need to access the if
row of u
this is what how we do this
and we need to calculate a dot product
so this is vector vector multiplication
between
the ether of u
and the vector v
and actually we write the result as the
if element of
the result
and then what we do at the end is we
just return the result
so this is how we translate this
this formula
into
[Music]
a
python code right so again we
create
a first
we create an m3 and then for each
element of the array we compute the
vector vector multiplication between
each row of view
and the vector v
and
so let's test it
matrix vector multiplication so we do it
between u and v
and we get
a one dimensional array so in our case
this is a
vector
and
again in numpy if we want to use numpy
for that of course we don't want to
write a function for computing
this
this multiplication every time we just
use a function again dot
so because we invoke this function on a
two-dimensional array numpy knows how to
actually multiply it that it needs a dot
product and you see that
the result is the same
so this is how we do matrix vector
multiplication now let's talk about
matrix matrix multiplication
let's say we have a matrix u which is a
capital u and we have a matrix v capital
v and what we want to compute
is multiplication between matrix u and
matrix v what we do here is we
look at
so we take a matrix v
and we break it down into
multiple columns so we have have a
column v0
v1
and v2
and we look at the entire matrix u
as is
and the result of this multiplication is
a new matrix
where for each column
so it will have the
three columns
for each column we have so column first
is
a matrix u multiplied by
vector v 0
then its
matrix u multiplied by vector v 1
and
matrix u multiplied by a vector v 2.
we represent matrix multi matrix
multiplication as
a bunch of matrix vector multiplications
so
let's implement this
so we already have a matrix e here
so we will do
matrix
matrix
multiplication
to have two matrices here u and v
so what we need to check here is uh the
same so that
here that
actually this multiplication makes sense
that we can multiply a
row of u
with uh
with a column of e right so we need to
make sure that
the dimensions much so we basically can
use the same thing here
so this is the check that makes sure
that
the multiplication makes sense
then we need to create a new matrix so
let's call it result
okay and we use
initialize it with zeros
so the size of this matrix will be
the number of
rows of this matrix will come from here
when we multiply
u
by
v
we will have
a new
vector that has dimensionality 3 because
there are three numbers
so it will be 3
so ub
will have
3 rows and it will have also 3 columns
because there are 3 columns in b
so number of rows comes from u
so this is the number of rows
of u and number
of columns
comes from
the number of columns of b
and then we create
a matrix
with results which with number of rows
coming from u
and number of columns coming from v and
then we do a loop
so here
we
loop over the rows of b so we first do
it for v 0 then v 1
v 1 and b second
so we do it over uh
for each column
and then we let's take you
[Music]
take
the eighth column of u
which is uh
we use this notation so we take all the
rows and eighth column
so now we multiply
this
so
it is out of multiplication it will be a
matrix vector multiplication between uh
so sorry it should be
e
right and then we multiply
u by
this uh
if column of v
right and
then we get some result
and u
d e
so this is the result of multiplication
of our matrix u with
vector v
and what we need to do now is put it to
the result so this is our matrix
result
the result and it has so let's say it's
three by three matrix
filled with zeros yeah actually these
are zero here so what we want to do here
is replace these zeros
with some numbers so we want to replace
this with results of multiplication so
here it will be u
times the
first
and
to reassign a column of
a two-dimensional array
this is the syntax we use so we say that
for if column
of
the result
the result is
this multiplication
right
so we do this for we repeat this for
every column of v
and we return the result
and this is
our multiplication then let's check it
so between u and v
and this is the result and again you
probably figured out this pattern by now
is that if we want to do it with plane
numpy
if we want to multiply two matrices with
plane number
we use the
dot method
and you see it returns the same result
right so
which means that our
matrix matrix multiplication method
works and
this way
we managed to
express matrix matrix multiplication
using matrix vector multiplication
and then in turn we
expressed matrix vector multiplication
with vector vector multiplication there
are still two topics we want to talk
about
let's talk about them so first i want to
talk about the identity matrix we
call identity matrix as capital capital
i
so this is the identity matrix and
identity matrix is a square matrix
where on the
diagonal we have
ones
and we have zeros everywhere when we
take any matrix let's say we have matrix
u
and we multiplied by i
and of course like dimensions should
match here
we get u back
or we can put it
in front and we can again get u
so
identity matrix is like
a number one so if we multiply number
one by any number we get the number back
right
and
no matter on which side we have this one
we get the number back
so in principle
now
this is the same right so this is the
same but for
so this is like a number one but for
matrices if we need
to create uh this identity matrix so in
numpy we use the
function i i don't know why it's called
i
but here we just specify the dimension
the identity matrix and it gives us a
matrix
where on the diagonal we have ones
and we have zeros everywhere else yeah
and we can see let's say if we create
this identity matrix of
size three
then let's say we have
b here
so
we can test it and we see that
yeah when we multiply
v by i
we get the matrix key back
and here we have uh three columns so
that's why
our i should be three dimensions uh it
should have
like the size of three so it should be a
three by three matrix so why we are
talking about this i matrix it's useful
for explaining what a matrix inverse is
so let's say we have matrix a and then
the inverse of a
we usually call it a minus 1 is a matrix
such that when we multiply it by a
we get i
to compute
the inverse so first of all um only
square matrices have inverse so square
matrices matrix is a matrix for which
the number of rows goes to the number of
columns so actually we need to have
a square matrix so let's just take the
first three
rows of b
so this is our matrix
uh square matrix and let's call it v
square
yes
this is our matrix and to compute
inverse of this matrix we use a method
from
from numpy called inf it lives in the
lean arc package which stands for linear
algebra i assume
and
so this is how we use it
and then the result is some matrix which
let's call it a
vs inf so this is the inverse
this then again let's print it
and when we multiply
the s inverse when we multiply the
multiply these two matrices
what we get is uh is an identity matrix
this will be quite useful for
linear regression we will see that in
the next in the next session
and for this lesson that's all
and next
we will have our last lesson of this
section we will talk about pandas which
is a library for manipulating tabular
data in python