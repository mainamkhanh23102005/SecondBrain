welcome back this is lesson nine of
machine learning zoom cup session one
and we will talk about pandas so this is
the last lesson for session one
took a bit longer than i expected
and yeah let's let's start pandas is a
library for and manipulating tabular
data in python
so
by now hopefully you have installed
everything
including pandas and again like in case
of numpy we use an alias for referring
to pandas so we import pandas spd
so the main abstraction the main data
structure we use in pandas is called the
data frame which is basically a table so
let's create a simple one we will use a
data set that i prepared
specifically for this session
so i take it from
github repo that you'll find the link
in the description so this is the data
set this is how it looks like
so this is a subset of a
data set that we will use uh for the
next session uh for predicting the price
of a car
so it has five cars um
and these are the characteristics of a
car
make model year
engine horsepower number of cylinders
transmission type vehicle style and this
is the price
so we have the the data in this format
so this is a list of lists and then we
have a separate variable that defines
the columns so let's let me copy it
and
paste it here
so again so this is a list of lists so
each sub list of this list is a row in
the table so each row is a car and then
for the first column here it's make the
second one model
year
engine so horsepower and so on
so this is uh now we can turn it into a
data frame so for that we
create a data frame
using this
this function data frame it's
constructor so if we just in create it
with data
it doesn't know what the columns are so
it just puts 0 1 2 3 4 because it
doesn't know what this column means mean
and we can let it know what each of the
column means by using a special
parameter
columns and we can say that it should be
equal to columns so basically if we do
this
then pandas knows that okay for
so this make this is model year and so
on
so let's save it into a data frame
so usually i call data frames dfs and
yeah it's not the only way you can
create a data frame there are
many other ways so for example again if
we go to
this github repo so it can be so this is
like a more compact way
so here
we don't
mention the name of the column in every
row so we just mentioned it once at the
at the end but it's also possible to
have a list of dictionaries so a
dictionary so this is a python
dictionary and then here we basically
say
we explicitly specify the value for each
of the columns
so this is
first car then this is the second car
and we have uh many cars like that
and
yeah so if we have a list of
dictionaries
we can also use them to create a data
frame so let me paste it
and
so again pd
data frame
and then all we need to provide is just
this list of dictionaries and then so
here we don't specify we don't provide
the names of columns it just infers them
the names of columns from the
dictionaries so because we have the keys
here and the values so
pandas uses keys as the column names
so
let's write it to a data frame
this is a really small data frame but
what i usually do when i read the larger
data frame is the first thing i do is
look at the first couple of rows
so yeah well for that we
for that i use the head method which
returns the first
rows so since our data frame is quite
small it returns the first five rows
uh but yeah we can say let's return me
only the first two rows
then yeah so this is one of the first
thing i do after loading a data frame
let's say from a cc file
or from a sql query i do i look at the
data using the head method okay so we
have this data frame
and every
column of this data frame
is a series so this is a special
game so this is an abstraction from
pandas
that data frame is a table and the table
consists of multiple series and each
column is a panda series
and if we want to access a particular
series
in a data frame so if we just want to
access this the column make so we just
use this documentation right so we just
write
dataframe.make
another option is instead of using the
dot notation we use the brackets
notation
so we specify the name
of the column we want to extract
here
and use the brackets
and this is the same
and as you see so here we have some
columns that have spaces in them so we
cannot really use dot notation here it
will now say okay i don't know what is
that
so for these cases let's say when we
have minuses or when we have uh spaces
there the only way we can access the
variable is using this brackets notation
also we can access multiple rows at the
same time so let's say if we want to get
a subset of our data frame
that contains only
make
model
and price
so we
what we do
is we
put a list inside brackets so that's why
we have these double brackets and in
this list we say which
columns we want to have so in this case
we want to have make model and price and
it returns uh a data frame that has only
these three columns right so it doesn't
have anything else
yeah so this is our data frame and let's
say we want to add another column to
this data frame so let's say we want to
to add a column called id
so we can do this
by
using this notation again brackets
and
so if we just try to get id it says okay
i don't know what is that
but we can say we can create a new
column
and
[Music]
this is how we do this so we use the
same notation as here and we just say
okay for this
we want to
have a
new column
that we will call id
that contains numbers from one to five
this way we do this and then now you see
that there is a column called id
that we can now extract
and we can actually also replace it if
we want so let's say
we want to change it instead of this we
want to
have
a different
different set of values
so now
we replace it
if we want to delete a column we use the
del operator which deletes
a column from this
so this is very similar to
dictionaries if we want to remove
something from dictionary we use the
dell operator and
here we can do the same with pandas
and you see this column is gone yeah so
we talked about columns and in data
frame maybe you see here
numbers here so these are ids of rows
so this is how we can refer to each row
and this is actually called index right
so if we
look at the index so we see that there
is an index called range index that
starts with zero so this is the first
one
and
stops at 5 5 is not
inclusive like usually it's exclusive
so we have and index that goes from 0 to
4. all the series of these
data frame
they all have the same index so let's
say if we access
make
you see we have this
again these numbers here these are the
indices this is the index of make and
again if we
try to access the index we see this is
the same index that the data frame has
so using this index we can
access the elements of the data frame
so
let's say we have we want to access
element
one and two then we use uh
lock so lock stands for location i think
so let's say if we want to get the
element that is indexed by one we use
lock
and we get the row
let me show it once again
so this is the
this row indexed by one and we get this
row here and then we also can return
multiple rows
see so we can
use this lock to get multiple rows and
this is what we look at
so this is the index
we can actually replace this index so we
can use something else
so let's say if instead of that
we want to use
some
id
so it could be a
b
c d
e
so now index is different you see this
is what we use
and this
no longer works it says
i don't know what you're talking about
there are no records with these
ids in the index so now we need to use
let's say
b
and c to refer to this particular
records in the data frame we however
still can refer to
a positional index so this is usual
index right and then there is a
positional index and positional index
this is what we usually use
in
in lists or uh numpy arrays so this is
like uh when it refers to a position
from uh
zero to four so this is what we
previously had as a range range index
we still can refer to elements uh using
positional index except instead of lock
we will need to use i look so let's say
if we want to get
element index by one
we use i lock one and
again we can
ask
multiple elements and this is how we use
it
so
if you see that the index is still the
all index but we use the positional
index to refer to the elements
to the records of this data frame and
now we have this strange index right so
let's say if we want to come back to the
usual index which is
sequential coming from 0 to 1 what we
use is we use the function called reset
index
and yeah what it does
it again
it resets the index to the sequential
index
and it keeps the previous index and it
creates a new column called index
to keep the values from the old index
and uh
if we let's say if we don't need the
values of the old index we use this
parameter called drop true which yeah
which drops the
the index and just keeps the new one
actually this function doesn't change
the
the data frame so it creates a new data
frame you see so here the original data
frame is still unchanged
so here it returns a new data frame that
has the same data but the new index
so what we can do if we want to
uh completely forget about the old one
we just reassign
to
to this df variable so we kind of
overwrite the old data frame with a new
one
and yeah so now we have we're back to
the data frame we had
okay so yeah i actually talked about
accessing elements already so this was
about this lock and i lock so now let's
talk about element y separations like in
numpy we
remember in numpy when we have an array
we can apply an operation to an array to
all the elements of this array right so
for example if we multiply an array by 2
then all the elements of that array get
multiplied by two so actually the same
uh
we can do the same with pandas
so let's say we have this engine hp
column let's say we want to divide it by
hundred
so this is how we do it this is exactly
the same uh as with numpy array so here
yeah i didn't talk about this done so
this is just you know this denotes
a missing number so for this uh pro we
don't know what is the engine horsepower
so we just don't know this value is
missing
and when you divide so for this one it
doesn't do anything but the rest it
divides the rest by 100 or yeah we can
multiply it by two basically we can do
everything we can do in numpy but here
we operate on
series from pandas not on numpy arrays
and the main difference between the two
is that here you have
an index here you have a name
but it's pretty much the same and
under the hood pandas actually uses
numpy
so and
like
like in numpy
we have
so like in pandas
we can do this multiplication
and so on element wise we can also have
some logical operators so for example if
we
want to
find all the records that were created
after
uh 2010
let's say 2015
right so
we see that
this
this
and these records were created after
2015.
so this is how we do this
right so this is very similar to
to numpy and again
so i'm already talking about filtering
so let's say if we want to look at all
the records that were produced that were
all the cars that were manufactured
after year
2015
this is how we do this so there are two
parts here
so the first part is
this part inside right so this is the
condition
so it returns a new series
with a binary series with false and true
values only
and
what this thing does here it looks at
the values that are true
and returns only them
we have a new data frame
which contains only rows that were
produced after 2012
and
let's say if we want to find all cars
that are nissan
and then we
write something like this make
equals to nissan and then we have two
cars that are manufactured by nissan
we can actually combine
this so let's say if we want to
get cars that are
manufactured by nissan
and
and produced
after 2015
so this is what we do
we combine them
using this logical and
operation
and yeah it's just one record
okay so let's talk a bit about string
operators so this is something that
numpy doesn't have so numpy is mostly
used for processing numbers and in
pandas will often have strings so that's
why uh
there are also a couple of useful
things for manipulating strings
so let's take
vehicle style column
so this is a thing and we see that uh
sometimes here so this is sedan with
capital s this is done with a lower
case letter
so yeah it would be nice if we can
somehow standardize it so in python
there is a
function there is a method from the
string class called logger
which takes a string and turns it into
a lowercase so let's say returns capital
case to a lowercase and keeps
lowercase letters
so we can what we want to do is we want
to apply this function to every element
of uh
series for that we can use this thing
called str that allows to
invoke stream methods
on the entire
series so we can do this
so we can say let's apply the lower
function on all the strings from here
and it gives us a lowercase you see like
everything turned
all the capital letters turned into
lowercase letters another thing we can
do is we can replace all the spaces with
underscores
so because sometimes
maybe you have underscore sometimes you
don't so this is a typical
pre-processing step when you work with
text
in case of usual string let's say we
have machine
zoom comp and then there is a method
called replace
and then first it gets the character you
want to replace and then second is what
you want to replace with right so you
want to replace this one by this one
so and then it replaces all the
accuracies of space by the underscore
so we want to
do the same here
so we can just copy this
and apply it again using this str thing
to all the elements of
series and you see so here we have a
space here this space is
replaced by an underscore
and
we can actually change this so first we
can uh so you see it's actually it
doesn't change it it returns a new
series with the modification so actually
see even though we lower case here here
it says it still stays capital case
right so because it doesn't overwrite
the series it returns a new series with
the new values
and we can actually chain them to first
replace and then lowercase and here we
have something that is
let's say more uniform
and then what we can do next is uh
because
this
data frame still has the old values
right
so what we can do is we can replace them
with this clean version so for that we
use the assignment operator
and we just override
this vehicle style the value
with the new
new value
and now if we look at the data frame
we see oops sorry
so look at the data frame and we see
that the values are overwritten so next
thing we will look at
is summarizing operators so like in
numpy we have this element wise
operators
and summarizing operators
the same thing
we have the same summarizing operators
in pandas so let's take it
the price
that's
msrp
so we have this price variable so we
again can look at the mean value which
is 2
000
max value so this is pretty much the
same as we have a number
right and mean for example
this is the average number
but
in addition to that there is a useful
function called describe which
reports all the useful statistics so
first it tells you how many
records are there like what is the size
of this um
what is the size of the series what is
the mean value what is the standard
deviation what is the minimal
then it also returns
the percentiles like 25th percentile so
individual percentile and the max value
so it gives you
um
like a lot of
information
and we can actually do the same thing
but for the entire data frame so we can
just call describe
on the data frame and what it does it
looks at it finds all the
numerical columns so we have four
numerical columns here we have here
engine horsepower engine cylinders and
price
so for all the variables for all the
columns that are numeric so of course it
cannot compute the mean value of model
or make so it can only look at numerical
values so it looks at all the numerical
values and computes
these summary statistics for them
so this is useful
and
yes what i also often do is i use round
here to just look at
to round it
up to two
decimal points so it makes it a bit more
compact
there are some things we can also do for
uh
string for sticks or we call them
categorical variables so for columns
with strings so let's say we have this
make column
and we want to understand how many
unique values are there
so we see that for example there are two
nissans but the rest are unique
so if we want to calculate how many
unique values are there we use this n
unique
function and we just say okay here are
four unique values
and actually we can apply it so to the
entire data frame and then it will tell
us how many unique values
are there for all the columns of the
data frame so there are four unique
areas for make there are
so basically for every so there are only
two transmission types
so it's manual or automatic
yeah so you can get a summary then uh we
mentioned that there is one
here this
nan which is a missing value and when it
comes to machine learning we don't want
to
have these missing values so we want to
know how many of them and we want to do
something with them
so for that we can
use this is null
function
that returns a
another data frame a new data frame
where for each cell it says true if
a value is missing see we have this true
here
and it says false if the value is not
missing
so only one
only one cell has a missing value that's
why it has
true here
and the rest
are not missing
so this is not always super useful so
what we can do
now is we want to understand here each
column how many missing values are there
and for that we call the sum method
and when we do that
we
so it's sums across columns so it
applies the sum to each column
and
then it tells
how many
missing values are there in each column
so and you see that there is one for
engine horsepower and the rest are not
missing so we are almost
over so there's uh two things that i
want to talk about the first is grouping
this one we want to
do something like group by
so if you know sql let's say if we have
a
query like that let me type it
so let's say we have a query like that
and
if you know sql so let me translate this
query to human language
so we want to group by we want to
so we want to
compute the average price per
transmission type so we want to see what
is the mean price for all the manual
uh transmission types for and for all
the automatic transmission types so we
basically want to first group by
transmission type and then within each
group we want to compute the average
number
so for in sql
it will look like that
so this is a query
that we would write in sql and let's
translate this clearly to pandas now
so in pandas we have a
method called group by
and here we specify what we want to
group by which column
this variable transmission type right so
we want to group by it
so yeah this is what we'll write here
group by transmission type
and then we have this me
mr
msrp
variable which is price
manufacturer suggested retail price
price or just price and then we want to
compute the mean number
or let's say if you want to
compute the minimum number
or
the
maximal number so this is how you do
this
uh everything in pandas is backed by
numpy
so let's say if we have so this
msrp
right so which is uh a series if we want
to get the
underlying numpy array we just use
the values field
and it returns
the underlying number
then the last useful thing
i want to show you is
we have this data frame and for creating
this data frame we used
a list of dictionaries right so this is
what we used for creating it
and sometimes you need to convert a
pandas data frame back to this form back
to a list of dictionaries
and for this what you do is
use a function called to
dict
and then you specify that you want to do
this per record so orient while you use
records
and it gives you a list with
dictionaries that you can do something
with them like you can save it to a file
or something like this so it's pretty
useful
and in the next
video it will not be a lesson just a
video with a summary of everything we
learned
during this session
so see you soon