welcome back this is lesson 14 of
machine learning zoom comp session two
and now we will talk about finding the
best parameter best regularization
parameter for um our linear regression
model so in the previous section we
talked about regularization and
as a way to solve
the problem of duplicated columns in our
data
and
here we notice that
this r
affects the quality of our model and
what we want to do is we want to try to
find the best
the best value for this r
so what we will do now
is uh we will use the validation set for
finding the best value
and what we will do is we will just try
a bunch of uh
different values for r starting from
zero
then let's have something smaller
then
we'll just gradually
increase this and we can
maybe
something like this so maybe not too too
small
yeah and then maybe we even try one and
then
we don't
so what we do now is we just go through
this r and we try it for every
we try every r from this list
we apply it to our model and we see what
happens and now we just need to
to print the results so let's just print
the
the regularization parameter then let's
also print the bias term and we print
the score
so what we see is um
like for zero regularization the
the bias term is huge and also aroma c
is huge
but for even little bit of uh
it improves so the score doesn't really
change
that much
it starts to become a bit worse as we
uh increase the regularization
and then yeah when it's 10 it's even
worse
okay and here the bias term also kind of
the the molecularization we add the
smaller um the bias term is and it looks
like maybe this 0.01
it's a good one
because
the model hasn't uh
started to
to degrade in performance and then
yes it's just not too not too large not
too big i think this is
good enough i don't think it actually
matters here it could be this one or
could be this one
doesn't matter so we can just go with
with this one and let's train our model
once again
and yeah
so we will just print the score
yeah so we trained we just selected the
best uh
regularization parameter and we train
our
model uh
we trained our model with this
regularization parameter
and we were able to see that it works on
the validation set now what we need to
do
is check this on the test data set as
well and this is what we will do in the
next lecture