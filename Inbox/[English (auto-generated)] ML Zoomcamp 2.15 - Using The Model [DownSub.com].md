welcome back this is lesson 15 of
machine learning zoom comp session 2.
the previous lesson we found the best
parameter for our linear regression and
in this lesson we will
train the final model and use it
and by training the final model i mean
remember that
we have a data set that we split it into
into three parts so we had a
train data set
we have a validation data set
and we have a test data set
so so far what we were doing is we were
training
uh our model
on the training data set applying this
to validation and then getting
our rmse
from that what we want to do now is
instead of that
we want to train a model
on the
entire
part that we use for both training and
validation we can call it
for example full train or something like
this
uh so we
train a model on this one
and then we make the final obligation on
the test data set to make sure that our
model works fine and we check
what is rmse
on that so it shouldn't be too different
from what we saw on the validation data
set
so let's do that
so first of all
what
we need to do now is get our data
so what we have is
remember we have this data frame train
and we have a data frame test these are
necessary data frame validation these
are the two data sets we have what we
want to do is combine them now into one
data set and for that we use a function
called in pandas
called
concat that is short for clicking
it takes a list of data frames
and what it does it concatenates them
together
so it's called full train let's see
we'll train
that
if we print the entire data set we see
that
even though there are 900
9500 rows so we still have the index
from the validation data set
what we can do is just reset index
we write it back
and now we shouldn't have this problem
yeah so now everything is sequential
and
we can use that now to get our
feature matrix
let's call it full train as well
remember we have this prepare x function
that we just
use here
right so we have our feature matrix
we also need to to drain a model we also
need the y
and again then there is a function in
numpy also called concut
oh it's called concrete so there is a
function number i call connecting it
that does exactly the same thing
so we just need to concatenate y train
and one y validation
so there is no index here that's why we
don't need to reset anything and let's
call it also y full train
and now we
take this code
for training the model
and we replace uh
this so x train with x full train
white train with a wifi drain
and then
this r
it was 0.01 yes
and
[Music]
we train our model
this is our final model
so these are the weights
of the model
and
so what we need to do now
is prepare our training our testing data
set and we will do it exactly in the
same way as sorry
we will do it exactly in the same way as
we do the validation data set
except we will just replace validation
with drain
with test sorry
so we get test
then we'll multiply here
and then we get the score and uh we need
to check it with y test
and we see that our model is not too
different from what we had previously it
in fact it has almost the same
rmse like up to third decimal point
which is a very good sign it means that
our model is
it can generalize well so it didn't get
this score just by chance
uh so it's it's good
so we have this final model
and now what we can do is we can use it
the way we want to use it is we actually
want to
use it to predict the price of a car so
imagine that there is a
car
and we want to understand what's the
price of this car
so we extract all the features so we get
this feature
feature vector from
from the car and then we need to put it
into our model
right and then it should predict the
price so this is what we want to do now
so this is our final model this is our
final model and we want to use it to
predict the price of a car
let's see how we can do this
so for that we can take any car from our
test data set and pretend it's a new car
and this is fine because we
we haven't seen this car during training
so we didn't train our model on this
data
so
here we have toyota sienna and yes there
are missing values so and
usually the way we do it we don't get a
data frame here
like when we extract some features so it
could be some
python dictionary with all the
information about the car so let's say
in real life scenario it could be a
website
or an app right where
people enter all these values
about the car
like
toyota
sienna
and then
the website
sends a request with all this
information
to a model and then model replies back
with the price
and so this is what we want to
um
to do now
so for that we need to
turn this into a dictionary because this
is how usually the requests look like
let's say car
so this is our
request
with the car like we know all this uh
all these values yeah so now we want to
put it in a model and for that we need
again to turn this
because remember our prepare
prepare x
function it expects a data frame so we
need to turn
this
this dictionary and remember we pretend
that this dictionary is coming from the
user we pretend that we didn't just
extract it from a data frame
so we need to put a
this prepare x expects a data frame so
for that we can just create a small data
frame with a single row
and for that we use this pandas data
frame
and then we can pass the list of
a list of objects lists of dictionaries
and this list will just contain one
single car
which will be in the car we just
received in our request so we have this
car
and then this car can go to our prepare
x
function
so we get a feature matrix with just one
row
let's call it x small again
right so we have that
and this is how we use this is how we
get predictions for that car
so here instead of x underscore test we
use this feature matrix
and let's see immediately what are the
results the results is
10.6 so
that's actually what we need is we just
need the first number right so for this
car
uh so there is just one single car right
so we don't need an array we just need
one prediction
and what we need to do now remember that
this is the
logarithm of the price so what we need
to do now is take the exponent
so this
this will undo the
logarithm
and this is actually the prediction so
we think that the car with these
characteristics
should cost that much and let's see how
this car actually costs
so it's number 20.
so we can see
why test number 20.
yeah it's reasonably close let's see
what happens when we
undo the logarithmic transformation
yeah so here we see that our prediction
was a bit off by five thousand
i think it's a relatively good uh
prediction yup so this is how we can
first train a full model and then this
is how we
apply this model to
to predict the price of a single car
that's all for this lesson and in the
next one we will have a summary