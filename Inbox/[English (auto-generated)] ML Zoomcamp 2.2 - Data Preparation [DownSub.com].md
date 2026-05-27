hi everyone welcome back this is lesson
two of session two of machine learning
zoom camp and we will
now prepare a data set for our price
prediction project
so remember we already looked at the
data set
and the data set is on google
but i have a copy
that we can use just to find it so we
can go to
github my profile
then
so this serpo ml com code this is what
we need
then
we have this
chapter two car price and then two files
that i showed you one of them is the
data
so we just see
the file
and we need to get the url of this file
so now let's download this url
let's download this data
yeah i think uh i already have it that's
why it added one
so but this is what you do so you can
use this big yet uh
w get for downloading
data or you can just save as uh in your
browser
so you have this data
now what we need to do is first
load it
for that we in bandus we use read csv
function
so it just
loads data and we can
see it immediately right
so all the data we saw on google is all
here
so let's
write it to
a variable
and then usually what i do after that is
i
take a look at the first couple of rows
first five rows
of the data set and see what we have
here
so we see another manufacturer of a car
model year
like a lot of
a lot of different
features like a lot of different
characteristics for car
and this is what we actually want to
predict this msrp manufacturer suggested
retail price
so what we we can see here
is uh there is some
like inconsistency in the way
the columns the column names uh we have
columns so sometimes we have let's say
underscores here sometimes we don't
then we have uh spaces here
that and remember with space
like usually if we want to let's say
access this transmission type
variable
then we need to
use this notation we can do it with dot
because with dot then it's not like it
will say okay i don't know what is that
so what we usually need to do is do a
bit of cleaning like first make it
consistent let's say make it lower case
everywhere
you see this is lowercase this is
uppercase then sometimes there are
underscores sometimes no in this course
so what we want to do now
is uh
make it all consistent so let's lower
case it and let's replace uh spaces with
underscores
so for that um
in pandas there is
this field called columns like in each
data frame
and it contains the names of the columns
and it's an index and in the
introduction to pandas we talked about
indices so index is uh
it's like a special
data structure in pandas it's very
similar to series
and like cds it has this str method uh
str thing
for
doing string manipulations so what we
can do is we can
apply the same string
function to all the column names here so
let's say if we want to
make everything lower case we just get
no we just invoke this lower
and you see that everything becomes
lowercase
and we can also chain it with
multiple string commands and the other
one that we want to use is replace so we
want to replace
replace spaces with underscores
and this is what we get and now what we
can do is
we can write it back to this
columns field so if we do this now
let's write it back
and then now if we look at
the head of this at the top first
records we see that everything now is
more uniform right so it's lowercase
uh it's consistent basically so
it's cleaner
and actually we have the same problem
with
the values so
here sometimes you see it's all cups
uh sometimes it's not all cups
and
yeah so it's
it's also not nice so let's make it uh
let's start that is normalize it as well
so for that we first need to find out
what are all the string
columns
right so we cannot really apply string
methods to this
this column for example because this
these numbers so this str thing works on
different things so first of all we need
to find out
to find all the string
columns
and for that we use this field called d
types
which returns for all the for all the
columns it tells us what is the
the type of this column and we're
interested in objects
so
you see here so this this is integer so
this is not interesting for us
these are floats this rows of load so
these integers these are not interesting
the interesting one for us are objects
so objects
um
here are strings
it can be other objects but usually when
we just
read
something from csv file
it's nothing else but
it cannot be anything else but this
thing
so we are now interested in getting all
the
all the columns that are of type object
so we can do that
uh remember this index basically tells
us
what is object and what is not so we
know that make is
make model
so we know which are objects
so we can
do that to select only those
that are objects so if something is true
we will keep it if something is false we
will not keep it and we get
now this series
and if you remember from
the introduction lecture about python
so this is serious and these are the
values
these are values
and this is the index of the series
so here we're actually not interested in
values because values are all objects
what we're interested in is we want to
get these names
so for that
we
need to use
to get access to index and this is how
we do it
so when we do this we get access to the
index of that series and these are all
the names of the
columns that we need and we can just
convert it to python list
just because no particular reason just
because it looks nicer
and let's call it strings
so this is a
python list that contains all the string
names
and now since we have all these names
what we can do is we can
uh loop over them so let's say for call
and strings so call this column
and df call
basically what we want to do is we want
to
do the same thing we did it here with
columns
let's say for make
what we want to do is do the same thing
and then write it back to make and we
don't
do this just for make we do it for
everything
so and this is how we can do this
so for column one of those
lowercase replace spaces with
underscores
and write it back to the data frame
now
we can see that
it's uh cleaner now everything is lower
case
um spices spaces are exploding replaced
with underscores so the data now looks a
bit cleaner
and
yeah let's also take a look at what we
actually have
um
i think
yeah this is something we will actually
do
in the next
in the next lesson in the next lesson we
will take a look at the data and try to
understand what is there
see you soon