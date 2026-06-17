welcome back this is the last uh lesson
of uh session two of machine learning
for regression so here we will summarize
um what we learned
in the session
so here we did a project
for predicting the price of a car
and we downloaded a data set
that had
prices and different characteristics
of a car
so we had things like model make gear
engine fuel type
transmission type all these things and
we wanted to predict this price msrp
which stands for manufacturers just
retail price
um so first what we did is we cleaned
the data set we prepared it so it looks
uh
a bit uh
uniform more uniform because here we
have
like spy spaces here uh capital case
lower case and we made it uniform
so we don't have here
so we made it a uniform so
now it looks cleaner
then we did exploratory data analysis
and we here identified that
we have this long tail
distribution of price and we removed the
long tail by applying the logarithmic
transformation to data and
this is a good idea because with a long
tail
when the distribution has
long tail usually machine learning
models have problems
then there are also missing data and
this later we saw that with missing data
we cannot really train a model so we
need to do something with this
so we did then set a
validation framework
like we did the split between training
validation and set and test
then we looked at
linear regression so how does it work
for a single
example so we implemented it
as a
simple formula using a for loop which is
later then we expand it to the vector
form or matrix form
using a dot product
and then
like we also expressed it as a
matrix vector multiplication
and then we the result of linear
regression the output is the weights
vector the bias term and the weights
and then we looked at how to actually
train a model how to obtain these
weights and we saw that
machine learning is not magic so it's
just a formula and this formula is
called normal equation
and we implemented this normal equation
in numpy
so we have
here the implementation
and with this implementation we trained
our first model
the baseline model that only used the
basic
basic numerical features baseline
features
five of them so the model didn't do
really well
as we saw in the graph
but
just judging from a graph is not
always easy
to understand what is the the
like how it's not easy to objectively
measure
the performance of a model so that's why
we talked about root mean square terror
which is a metric for evaluating the
quality of uh regression models so we
talked about that and then we built this
uh
validation uh
framework in a way so we uh
use this prepare x function that allowed
us to have the same way of preparing
this feature matrix for a different data
set for train
and validation which later allowed us to
experiment a lot faster so we just re
redefined this function and
that let us simplify the process so we
will basically just copy uh copy paste
in this cell
throughout the less throughout the
session
um
yeah so then uh like after
uh
you know i think after that we did
simple feature engineering and teach
engineering is a process of creating new
features from existing ones
so we
created the feature age
that improved
the performance of our model drastically
as we see here so the distributions now
match the predicted distribution and
the the actual values well not exactly
but at least much better than previously
and then we looked at how to integrate
categorical variables
here we represented each categorical
variable with a bunch of
binary columns binary features
and actually this way of
encoding categorical variables is called
one-hot encoding and we will talk
about that in more details in the next
uh
session when we talk about
classification
so we did that and then after that we
found out that performance of our model
degraded significantly so all of a
sudden rmse became very huge
and
because luckily we had this validation
framework we had this validation data
set we could spot the problem easily and
the reason for that was the numerical
instability which we discussed next and
as a way to solve this numerical
instability we use triggerization we
added a sim a small number to the
diagonal of this matrix x transpose x
before uh inverting it
which uh
helped us and we noticed we saw that the
performance of our model after including
all these categorical features
uh increased quite a lot compared to the
previous version and then we
after that we tried different uh
values of regularization parameter to
find out what is the best one
and we concluded that this one 0.001
he seems like maybe it's not the best
but it's
on the same level as others so we
decided to go with this
so
then we trained our final model we
combined the
training and validation data set into
one full train data set
and
we again
use this prepare x function that is very
convenient
and we trained our final model
and we also saw how to apply this model
uh to a car for which we don't know the
price so well actually we know because
this is the test data center but we
pretended we don't know the price for
this car
so we predicted
uh the price
which wasn't that off from the actual
price
so in the next
i will not make a video for this one it
will be just text so i read it
through so there are now i'll talk about
other things you can try to
learn about the topic better and of
course after that there will be homework
where you'll try to
do this what we learned yourself
and then finally in the next section we
will talk about classification
and there instead of implementing things
ourselves like we did here we will use
uh library uh we will use scikit-learn
for implementing all this thing so we
now saw how we can implement things
ourselves and now we are ready to use
the library so see you soon