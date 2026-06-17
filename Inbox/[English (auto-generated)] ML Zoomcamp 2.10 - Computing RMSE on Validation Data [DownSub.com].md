welcome back this is lesson 10 of
machine learning zoom comp session two
and we will talk in this lesson about
validating the model
two lessons ago we built our first
baseline model using numerical features
five numerical features
and then we wrote a function for
objectively measuring the quality of our
model so this was aromaski which is the
root mean squared error but the way we
did it
is
remember the way we should do validation
is we take a
data set we split it into three parts so
we have a
training data set with a validation data
set and we have test data set
so what we did is we took the training
data set
we trained our
linear regression model and then we
again applied it to our training data
set to calculate the root mean squared
error
instead what we should do instead of
applying to training data we should
apply this to validation data and then
look at the root mean squared error on
validation data so
let's do this so first we will get the
code we wrote earlier so we have this
now so this is the code for training the
model
so this line here this is when we
prepare our
feature matrix x a lot of things uh
happening here so let's write a special
function for that
uh we'll call it prepare x which takes
in a data frame
and then let me just copy it here
and decompose it into multiple
things so first of all it creates a
data frame with numbers so we can call
it data frame num
and this should be not just the
training data frame or training data set
or validation data set or the testing
data set it could be any data set
and the idea for this function is uh we
have the same way of preparing the data
set regardless of
whether it's strain validation or test
so we have the prepare x function that
is doing that
and then we have the second step
which is
the first is selecting the numerical
columns then the second step is filling
the missing values and then the last
step is uh
extracting the
feature matrix the the numpy array and
then returning it
so we have this function so from one
line now we have five but at least it's
easier to understand what's going on
so let's use it for uh training
for training matrix
prepare x
on training data set
and then let's uh
train the model again
so we
we prepare the matrix we train the model
then we again prepare the matrix but
this time we prepare our validation data
set so we use the same function
except that instead of using the train
data set we use the validation data set
and then finally we do predictions so we
apply
this
linear regression
the weights we have but instead of
applying them to the training data set
we apply them to the feature matrix
computers from the validation data set
and this is our prediction and then at
the end what we can do
is we can compute the root mean squared
error of this prediction which is uh
by validation y prediction
and it gives us the root mean squared
error so if you see this is pretty
similar to
to what we had so here we can see that
there are two parts so this is the
training part
so here we only
touch the
the training data set and here this is
the validation
uh part so here we
prepare the validation data set in the
same way as the training data set then
we apply the model then we learn from
the previous step then we compute the
root mean square there
for that model
okay now we have a way of evaluating the
quality of our model using root mean
squared error we can do this on the
validation data set and now we can work
on improving the model and this is what
we will do next