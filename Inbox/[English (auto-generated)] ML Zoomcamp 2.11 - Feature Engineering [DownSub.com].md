in this lesson we will
add more features to our model so let's
take a look again in our training data
set
and what we see here is this variable
year
and we know that this is one of the most
important
variables was one of the most important
columns for predicting the price of car
because if a car result then
yeah it's usually cheaper if a car is
new
then it's more expensive so
we want to use this variable and instead
of using it as a year what we can do is
we can compute the age of a car
for that
we need to know
i don't know when this data was
collected
so we need to take a look so this data
was collected in 2017 so let's say now
is 2017 and we want to
compute how how old the cars are
so some of the cars are 0 years old some
of the cars are nine years old
so this
um this is uh h of a car and we want to
use this as a variable right so we want
to take this um put this into our data
frame so we want to use this as one of
the features in our model for that so
let's take a look
let's
let's use this function that we wrote
earlier so we already have this function
let's modify it a little bit and add
a new feature here so this feature is
called h
and we computed it in the same way as
previously except that instead of data
frame train we use just any data frame
we pass here
and then here instead of ways we need to
use base plus this new feature so let's
create a list that we will call features
that contains the
the base
baseline numeric features plus the new
feature h
and we will use it here
and let's try to do this we call prepare
x
and
so this is our
training data set and when we executed
this so you see here this first line is
adding a new column here so when we
executed that
what happened is we actually
added a new a new column here so you see
in this data frame a new column appeared
so we modified our data frame this is
not something we should do in this
function as a somebody who uses this
function i don't want it to change my
data so what if it does something that
then cannot be undone
so i would prefer that this function
doesn't modify the data frames i pass
for that we can just before doing all
these things before adding new columns
what we do is we just take a copy
and then
we will work with a copy inside this
inside this function and the original
data frame will not change
so let's first
remove
let's first remove this new variable
so we removed it now we don't have it
and execute it again
so now if we
look at
columns so yeah we don't have h anymore
so because what happened is we passed
this
train data frame and then it took a copy
first and then it modified the copy and
then after leaving the function you just
forgot about
the copy because all we care at the end
it was this x
and actually this
x strain
it has
the there are one two three four five
six six columns six features and this
last feature now is h
and uh let's use it now
so i'll just copy this code now because
we need exactly the same code we
modified this function and now
our model should be better yeah so we
see that
our model improved and it's quite an
improvement so it went
down from 0
76 to
0 51. so it's a big improvement and we
can see that it's a big improvement by
doing the same thing as we did
previously so we can again plot
the predictions we can plot the actual
values and see
so we actually need to use
now validation y validation because
these are
so because now we are actually
predicting on the validation data set
not on the so on the train data set as
previously
so we see that now
it's actually better so at least this
peaks much
of course like here it's not doing it as
well and then it completely misses this
um
this bar here
but
i think in general it's doing it much
better at least
in this area here there is a lot of room
for improvement here but in general it
uh kinda
now the shape of the distribution is
closer
we can actually add more features and in
the next lesson we will talk about
categorical variables these are
variables
columns like model make and so on