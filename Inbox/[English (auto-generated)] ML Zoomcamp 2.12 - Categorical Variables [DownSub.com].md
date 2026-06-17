hi everyone welcome back this is lesson
12 of machine learning zoomcamp session
two and we will talk about categorical
variables so categorical variables are
variables that are categories so these
are typically strings so these are not
numbers
so things like make model engine fuel
type
uh transmission type driven wheels
they are categorical variables so
typically they are strings and
we have quite a few of them
here if we look at d types so we have
make model and so on so all these
things that have type objects object
they are
categorical variables
but there is one variable that is that
looks like it's numerical number of
doors
but it's actually not
not a numerical variable it's a
criterical variable
because there are
distinct types of cars so there are cars
that have two doors cars that have three
doors and cars that have four doors
right so these cars are quite different
so it's uh it's not really a numerical
number a numerical variable
even though it looks numerical it just
happened that the values of this
variable are numbers and that's why
pandas treats them as usual numbers
right
and
we want to use variables like that for
our models for our model
because they could be important so for
example for
cars with two doors they are probably
more expensive than let's say car with
four doors and the typical way of
encoding no such categorical variables
is we represent
let's say we have
here we have our column with different
values so it can be like number
of doors right it can be say two
three
four again two and the way we usually
encode it is we represent it with a
bunch of binary columns so for each
value
so let's say this is a number of doors
two
number of those three and number of
doors four
for each value we have a different
column and then uh we put one like for
this row because the number of rows is
two then we the number of doors is two
that's why we put
one in this
in this column and put zeros everywhere
and for this one uh one goes here and
these ones get zero
and then for four
again one goes here
to the column number of doors four and
then here again we have two
that's why we have one in the first
column
so we represent uh
one categorical column with
multiple binary columns multiple binary
variables and the way we can do this in
pandas is using this equals equal
separator so let's say when we say that
number of doors 2
equals to two
then basically it shows that uh for the
first car it's
true so the the the number of doors is
actually
you can see that it's two and then this
this is also two two
yeah we can see it's true
so one thing we need to do now is just
turn to it into integer so we have here
ones and zeros and for that we can just
use this as type
function that turns a boolean into
integer
right and then we can do this for
all of them right for two three and four
and
so what we need to do now is just write
it back to a data frame
and then
the way we do this we can just let's say
have a
number of doors
equals four and then have a
kappa variable like that and then it
will create a new
a new variable here a new column in the
data frame
that uh
that is one for all the cars that have
four doors and then
yeah we can
do this for free
for two doors
and for three doors
right
so here it will be two
would be three
but we don't of course need to do that
we can just write a loop that will look
like
for value in two three four so these are
different values
and then we
can use here this
string template so this
let's say number doors
s
and s will be replaced by uh something
will pass
say here in this case it will be
replaced by three
in this case it will be replaced by four
right
so we will create a column
for each of the values
and here we just uh
yeah so
we'll basically go through all the
values of number of doors two 3 4 and
then create a separate column for that
but i will not execute this now here
because i will add this oh actually i
can execute this
let's see what
what happens
so okay i forgot to
uh
to add this here thing here so it needs
to replace s with uh
we see
it appeared here
of course i need to delete this now
yeah and
i'll also delete this
three and four
so now they should be gone
this is how we can represent categorical
variables and also put them in our
feature matrices
so let's modify our prepare x function
um again we make a copy because we don't
want to accidentally write these columns
in our
in our data frames
so here we will
go through three values these three
values
and basically do the same thing
so then i'll just replace dftrain with
df
yeah
so and
here we also need to add this uh
name
the feature name
to the list of features because later we
want to we want to get these features
from the data frame and then put them to
the matrix x
so on that i will use the append
function
here so here i don't use append
because
i want to create a new a new list so i
don't want to change the base list every
time because otherwise if i let's say
use append here
then
it will append the h
value every time to this base list so in
this case i will actually need to
do a copy
so let's call it
features
and then i append to the list
so this is basically the same idea here
so we don't want to modify
uh the list base right
okay
so now so we still compute the h
variable and then we go through the
values of number of doors and then we
put this to the features list so the
features list will contain all the
features we have from the baseline
features
then we will have the age feature and
they will have three new features that
is number of doors two number of doors
three and number of those four
so let's uh
test if it works actually
prepare x let's
test it on our yeah we see now that it
adds a new
set of columns one for those like this
is number of those two number of those
three number of those four and let's
just copy this thing for training
so we don't need actually to change
anything here
and see if there is any improvement
we
see that the results so the previous
result was this one let me just copy it
so it
improved only slightly like only a
little bit right so the improvement is
almost uh negligible so the number of uh
doors feature is not that useful
but i'm pretty sure that
if we add make the make should be
quite useful
so for that
if we look at make
we have quite
a lot of values so let's look at them
unique
so we have a lot of values and
yeah we can just what we can do is just
look at the top
the most popular values so for that we
have
this function called value counts
and when we can see what are the most
popular ones
right we see that for
top five
use this head
function we can see that
now for make these five are the most
popular ones
and again so this is the values this is
the index so if we want to get the
actual values we use this index index
property and yeah let's also wrap it in
a usual
python list so these are the most
popular makes of cars and we can include
them in the same way as
this number of those so let's
for now we can just copy and paste
we i'll come just right now car makes
okay just makes
so we have mix here then for movie in
mix so i'll just
replace here this thing with make
and this thing with make and this thing
will make so the code is the same
so again for each of those makes
and we have
to have chevrolet forward volkswagen
toyota dodge so for each of them
we do a similar thing like here so we
actually will have five um
new columns here because there are five
values and then it will be for all the
several let's it will be one okay so
let's uh
try to see if anything changes
so just copy this and
all right
and we can see that the results improved
but of course the improvement is not as
drastic as when we added h but still
like it
increased
decreased one percent which is
quite okay we can do the same uh for
other variables or for other categories
so let's say we have makes here but in
addition to makes we have so let's look
at again d
types so we have
engine fuel type that's a categorical
variable
then we have transmission type it's
categorical variable and then we have
driving
dripping wheel that's critical variable
then
yeah vehicles market category
vehicle size
vehicle style so all these are
categories
so now we have all the categorical
variables
um
well i'm not adding a
model here because there are simply too
many models but i'll hit
make and all these other other ones
right so we have quite a few of them
um so what we can do now is we can do
the same thing like we did here
but for all of this
right so we can do this for make for
engine fuel type for transmission type
for driven wheels for market category
for
vehicle size for vehicle style yeah so
what we can do is we can maybe create a
first a dictionary
let's call it categories and this
dictionary will contain for each of the
category it will contain the top five
most common ones
so now we will need to go over
this list of categories
and then
for this for each category we will get a
list of the most common ones
okay here we just need to replace this
make with c
and let's see what we get
we need to to give it a different name
um
we can call it categorical
variables
yeah so now it should yes now for make
it contains the most popular mix for
engine fuel type for transmission type
so basically for
for all these
variables we know what
the most popular
values they have now we can just take
this prepare x function and
just throw in all the
all the categories
so for that
we'll need to to
make two loops so one is across uh
for each item uh in this so for each key
of this dictionary and then for each
value inside we will create a new
a new column
so for let's do for c in uh categories
um then for
and actually we need to
to do this over key value pairs of the
dictionary so we use
the items field here
then
we do another loop over the values
of each
category
and then here we need to have something
like that so it will
replace the first one and the first
percentage
with c and then the second percent as
a with v right and here we need to
do that and the last one is just a name
um so number of doors i'll just keep
like that and let's execute
now we again do the same thing
we execute it
and let's see what happens
and what happens is now actually this
value is significantly higher than what
we had before so before we had
0.5 right and now all of a sudden it's
41.
something went wrong
and if we look at the values that we
have so you see
the values that our linear regression
function uh trained linear regression
function outputs they're huge so this is
uh
like this is because scientific notation
it's very difficult to read but if you
convert it to an integer
so it's a huge huge negative number
and
these weights
we see that some of them are also very
large so for example this uh
this row here so this is
so this is a huge huge huge value so
something went wrong we wanted to
improve our model by adding more
variables but we just made it worse and
in the next lesson we will see why that
happened and how to fix it