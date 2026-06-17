in this uh in this lesson we will build
a baseline model for predicting the
price of a car so in the previous lesson
we um
saw how to train a linear regression
model and what we want to do is we will
actually use this code that we wrote in
the previous
lesson and now we will use it to
to build the baseline model
so for that what we need to do is
let's take a look at our data frame
okay so what we have here is a
data frame from which we want for now
for the baseline model extract
use all the
numerical columns so we can again take a
look at
the numerical columns we have d types
and we see
that um the numerical
so we have
engine hp uh engine horsepower we have a
number of
cylinders we have
miles per gallon on highway we may uh we
have miles per gallon in city and we
have clarity right so have
this five
right so let's uh
let's build the model using this uh this
five
so for that
we can do is uh
first to write create
at least with all these
feature
names so let me just use
comms here
so here we have engine horsepower
and we have engine cylinders
then we have
these three
all right so we have five of them
um
and
remember if we want to get a subset of
columns
we just use so we put this subset of
columns in a variable called we call
base base just basic
basic features so we have them
and
what we need to do now is to extract
the values from here
so let's do that
okay so let's do let's call the tick
stream first
we have this df train base right and we
use various to extract the numpy array
so we can put this as our
x
extreme
x string and then we have
y train already
all right so we have that
and what we want to do now is train a
model
so we use train uh
train linear regression
and we have a problem so we have nuns
here
and the reason we have nuns is if you
remember
so
let's just
take a look at this if you remember we
have some missing values
so we can just quickly check if there
are some any missing values here so we
have missing values in
engine horsepower and then engine
cylinders
so we need to do something with this
missing values
so the easiest thing we can do with them
is just fill them with zero
fill
and a zero
and then now if you do this is now again
and some
it should be nothing yeah
and by filling missing values with zero
we kinda will make the model ignore
these features so let's say we have
we have our model
our model is again
g uh
for x e which is uh in our case we have
five features right so
let's say we have this uh w0
then uh
xi1 w1
then
let's just use in our example uh
two features right
and
let's say that this variable here
this value here is missing
so what we can do is we can just say
okay
let this value be zero
and when we do this what we get in turn
is uh
uh w0 plus
uh
xi2 times
w2
so effectively we just ignore uh that
this feature exists right so
zero is not always
the best way to deal with missing
variables
and if you think about this let's say if
this
this is like for example could be
engine horsepower right
so it doesn't make much sense
for um
for a car to have zero horsepower right
uh typically there are more or in case
of cylinders like there cannot
the engines with zero cylinders don't
exist so from common sense point of view
maybe replacing it with zero
doesn't make much sense but from
practical point of view when it comes to
machine learning sometimes 0 works fine
and
of course in the previous lecture
we saw in homework as well how to
um how to fill missing values with
non-zeros with mean values
it just makes the process a bit
complicated that's why we'll just go
with
zeros so let's do that
so we again extreme
and now our
x strain shouldn't have any missing
values and that's why training finishes
so we have uh
so let's just write like that
so we have our bias term and we have our
w now we can use these weights to make
predictions
so let's say we can now for for now just
apply the same model that we just
trained to the same data set to train
data set
and for that remember we use matrix
multiplication
um
so we just multiply our
training matrix
feature matrix with our w
and we get the predictions
and we forgot the device term
so we get the predictions and let's call
it a y underscore print
so these are our predictions now we can
plot these predictions to see if they
look similar to
the
original to the target variable that we
want to predict and for that
we can use
the same histogram
function from seaborne that we used
already so it's his plot and then
the first one
will plot predictions
and then the second one will plot
the
train variable
so they now that they have the same
colors so let's change it a little bit
the color could be
um let's say first
red
that the second one
in blue
so now it's better we can just um
have a little bit fewer bins
let's go with
i don't know 50.
we can make them a bit more transparent
alpha is the variable is the parameter
that controls how transparent these
colors are
so they are now more transparent so here
what we have
these are
target variables
values target
and these are predictions
so we see that uh
the shape of predictions is like that it
it's off like it's always less you see
that the the peak is here so even peaks
of the distributions don't match so it
always predicts in many cases it seems
to predict a smaller
value than
than it actually is
just by looking at this chart at this
plot we see that
our model might not be
ideal
but we need to have an objective way of
saying that
is this moodle good or not good
and when we start improving our model we
want to make sure that we indeed improve
our model not just by looking at the
charts
and for that in the next session we will
talk about root mean square there which
is a way to objectively
evaluate the performance of
regression models