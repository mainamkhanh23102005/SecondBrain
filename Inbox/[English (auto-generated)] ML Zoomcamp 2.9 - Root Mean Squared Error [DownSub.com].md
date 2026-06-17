welcome back this is lesson nine of uh
session two of machine learning zoom
comp and we will talk about evaluating
regression models and we will talk about
one way of doing this which is root mean
square there
and in the previous session we trained
our first model it was a baseline model
that used only numerical features
and then we uploaded the predictions we
plotted the actual uh values and we saw
that they are a bit off but we don't
have a way to
quantify how bad the model is and this
is what we will do
in in this lesson
so let me start with
writing a formula first
and then we will decompose the formula
and we'll try to make sense of this so
root mean squared error first of all
this is
the difference between so
for each prediction that we have so this
g x i this is the prediction we make for
x i so this is our prediction
for
x i and then we have the actual value
so this is the actual value
so this is the actual value for this
observation i so what we do is we take
the difference between them and then
square this difference
so this is actually this squared error
part
and then what we do is we take the
average
of these
differences so for that
we have a sum sum goes from 1 to m where
m is the number of different
observations
and then we take an average
for that and we take a square root
so now let's uh let's decompose it
so this part here
is
the square difference so let me just
write it here
so this is the difference between the
prediction and the actual
value
for like the actual price so this is
price
price
and this prediction
so imagine we have
an array with predictions
so this is our
y underscore print
and we have some predictions i don't
know 10
9
11 and so on
right so these are our predictions it
could be
10
and then we have the actual price
we have the actual price
so this is uh
our
y train
and then the price could be
nine here 9 here
maybe 10.5 here
and then
perhaps 11.5 here right
so
these are predictions and these are the
actual values so what we do here is we
move it a bit
so what we do now here
is we take the difference so which gives
us another
um another
array
with
differences so here
the difference is one here the
difference is zero here the difference
is 0.5 and here the difference is
minus 1.5
right
then what we do next
is we square this difference
so
take this difference
and square it
and for that so for the square of 1 is 1
square square root 0 is 0 the square for
0.5 is
0.25
and the square of 1.5
2.25 right
so we have that
so what we do next is uh
let me just uh write it one more time so
we have one we have zero
we have
0.25
to
0.25 so this is our
squared error
and now what we need to do is we need to
take an average so for us
the average is
one plus zero
plus zero point 25
plus two point twenty
five divided by
four
so we have
0.875
right so this is our
mean squared error
and then finally what we need to do is
we take
this one and we take this compute the
square root of this
which is
0.93
so for this case so if we have if our
predictions look like this and actual uh
prices look like that
then for just these four observations
this will be root means current error
yeah let's let's implement this
let's implement this so let me just uh
write the formula here one more time
um so first of all it's again
predictions
uh the square difference between the
predictions and the actual value then we
have
the mean here and then we have the
square root yeah let's call it atomos
here
so then we have
two values here the first is y the
actual actual values and then we have y
print which is which are the predictions
so here we need to compute this uh
error the difference between
y and y prep then squared error would be
this error
squared right and then once the error is
squared we can compute the mean actually
i mean so we don't need to compute the
sum and then divide it by the number of
elements
in numpy we can
directly invoke the min method
and this will give us a means quarter
right and then to compute the root mean
squared error what we need to do is
compute the square root right
and this is basically
what we return in the results
and
let's use it
so we can use it for
this
so we already have
some predictions
and we can use it for evaluating the
quality of this and we can actually
simplify this formula a little bit so we
don't need to have this error thing here
we can immediately square them
this errors so maybe
this looks a bit nicer
so we implement the truth mean square
there and now let's use it on our
validation set in the next lesson