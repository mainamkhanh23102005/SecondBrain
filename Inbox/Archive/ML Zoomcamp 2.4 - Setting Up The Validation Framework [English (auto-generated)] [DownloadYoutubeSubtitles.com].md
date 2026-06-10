<<<<<<< HEAD
zoom comes session two and we will talk

about setting up the validation

framework

and um

so if you remember

like for uh

from the last uh

from the last session we talked about

validating models and we talked about

this model selection process

and we talked that

we need to take our data set

for for validating the model we need to

take our data set

and split it into three parts so the

first part used for training

the second part we use for validation

and the last part we use for testing

so

we train a model

we check it if it works fine on

validation data set and we

leave this

we leave this

test data set

only at the end so we use it only very

very occasionally very infrequently only

to check if our model is doing good

so we need to take our data set and now

split it into three parts

right train

validation and test

and then from each of these

parts we create

you know this uh

feature matrices matrix six x

and then target variable y so this is uh

train

so this one is validation

and

also the one for test

okay so this is what we need to do right

now so this is what we'll do now with

pandas

so first of all um

we need to we will do this 20 split so

it will be 20


and


so we need to calculate how many 20

actually is

so the size of our data frame actually

we should have looked at this at the

very beginning when we just loaded so it

has almost 12 000 records

and uh

yeah 20 of that is

approximately

two

um

thousand four hundred right

so

and of course uh we

we don't want to have a number that is a

fraction like it's

we want to have a number that is integer

so we

round it using this

so let's

do this for all three so this n variable

will be the length of our data frame

then the size of

validation

data set will be

20 of

n and then we round it

then

and

test will be the same

so this is the

size of our test data set

and then

and train this will be the size of our

train data set so we can write here 0.6

but we can have a problem that

now

it can be different so now let's check

and

test

so ideally they should uh

be the same

but you see because of rounding so

because here we probably we were

rounding up so that's why uh

it's not the same so like we cannot

split it using these values

because actually

n

here the number of records in our data

frame is actually bigger than yeah the

size of this

so for that to make sure that we don't

accidentally leave a few records what we

do is

we instead of doing that

we just

so what we do is we

take this part out

take this part out

and whatever

is there after taking these two out

we take for training

for that we just do

n minus and validation

minus and test

and yeah so this now they should add up

so now they

they're the same

and then uh so now we know the size of

which of which

uh so let's

just look at the size

which data set so for training it's uh 7

000 for

validation it's uh 2 000 um almost 400.

so this is what we use for

now so this is the sizes of our data

frames

so now we know the size and we need to

take a part of the data frame

out of this size

so for that

we can use this i lock thing that we

talked about

and i lock instead of just

introduction to pandas we talked that

talked about

this dialogue and we mentioned that it's

possible to give it

a list

and it would

return a data frame a subset of the data

frame

it's actually possible to use a range

range so let's say if we want to get 10

first records we can do something like

this so it means from the beginning till


so it's again not x

inclusive so it's uh from zero to nine

and we get uh first uh records

and it also works like let's say if we

wanted to to get from ten to twenty

we do this

and let's say if we want to get

something till the end

how many records are there

so let's say


just want to get remaining four

so this is how we do so it just knows

that if we use this notation

it it's from this one to the end right

so that this

so potentially what we can do is we can

say okay let's give us just the first uh

2382 records and we will use them for

validation

and then the next records uh

so let's see that will be the first one

let's call it data frame

validation

then we can

say okay everything that is after this

one and to the next uh you know

whatever

for

4 thousand

700 something

will be a

test data set so we actually need to sum

them

so this is test

right so now we have these two and then

let's say dataframe train will be

everything that is left

so we just take

this one

and use so till the end right and then

now we have

this so here is a problem we have a

problem here that it's sequential right

so let's say

uh

in our validation data set now we have

all the beam doubles bmws

and we don't have bmws in train right so

we see that there is some order

in this uh in this data set so we need

to shuffle

these records right to make sure that

there are bmws in all three data sets

right and in general it's always a good

idea to shuffle

data to make sure if there is some

accidental order in in the data we want

to break it

so for that what we can do is

if you remember that we can in this i

look we can use uh

we can just specify uh

an arbitrary sequence of numbers and it

will return

them in this order so what we can do is

we can take numbers from uh

can take numbers from

zero to n

then we can reshuffle them

and

we can so these are numbers let's say

from

zero to

n minus one

right so we reshuffle them

so you know we have like 10 here

uh one then 10 000

and so on here zero for example so we

reshuffle them and then we take uh

first twenty percent

for validation and uh

twenty percent for

uh uh

for um

for test and then remaining for

train

okay so let's

implement that

actually i think

if we do it slightly differently

so

i think it might makes more sense to

start the same

so let's say we take

data from train first

and then from train and train cruise

plus and validation

and then we take the rest

so

i think it's a bit more logical to

the first to basically follow uh the

same distribution so first we

take this out then this one and then we

start

okay

so now what we want to do is this one so

we want to generate a sequence of

numbers from one to ns1 n minus one for

that we use a function from numpy called

arrange so it's doing exactly that so it

generates a sequence of numbers so let's

call it idx it's short for index

and then what we want to do now is we

want to shuffle it so

for that there is a function in random

called shuffle and we just do that

and now our index is shuffled

and now let's say if we

take um

first 60 of that

we can use this for our

trained data set right so let's now just

replace this here

with

this

so we just need to

add one more thing inside so instead of

just

getting

uh rows directly from this

um i look

we get them

through this index so maybe let me just

show you um

i look

it

let's see what happens if we take first

step

yeah so when it's shuffled

yep so you see it takes first 10

in shuffled order

right so we want to do this but not 10

but the the number of uh records we have

like 60 and 20 20

and this is what we have

yeah so we did the split

the problem with this when you run it on

your computer you will have different

records here so the first one will not

be porsche but will be something else or

not gmc but something else

to make sure it's reproducible

we usually set a random seed we talked a

bit about

that in the introduction to numpy so we

want to make results reproducible

so for that we use uh

sit

right and we set c to some number let's

say two

and let's again generate this uh index

then shuffle it

and then take a subset

so now that the first one is chevrolet

and if we do it one more time

it's a gangster value so and on your

computer when you do this if you have

the same version of numpy

you will have the same

you will have the same subset

yeah and

that's uh actually what we need to do so

now we have three uh data sets let's

check the length of this uh data sets

train

validation and

it should be seven thousand so let's

check

one more time

because it should be

this way

right so it should be

from 0 to


okay now it's correct

and

a few things before we finish so now we

see that uh when we look at train

we see that this index

is

it changes right so here we have numbers

in this order

so sometimes it's just inconvenient so

we don't really need to know what was

the original index of this record so

what we can do is

reset the index

we talked about this separation in

in the introduction so we don't need

this index column that's why we drop it

and we basically

reassign it back to

to this data frame so you see now it's

from zero to

seven thousand

and finally the same for

test

okay

and then um

we need to do some transformation with

our uh y

so this the f train this is something

we'll use to make our feature matrix x

but if you remember that in our df train

this msrp

we actually need to

turn it to apply the log transformation

to this

lock 1p i think

yeah so this is the lock transformation

and instead of

keeping the series let's immediately get

the

pandas

values

so instead of using pandas

series let's get number

numpy array immediately to use it

because we don't need all these indexes

and

other things

and that will be our

y variable for train and we do the same

for

validation and test

okay now we have these variables

and the last thing that we need to do is

we need to remove this msrp variable

from our data frame for that we use the

dell operator

and we need to delete it because we

might accidentally use it

and we want to avoid this and if we

accidentally use this and then we will

use the price

variable as a feature for predicting

price and of course our model will be

perfect and

we might spend a lot of time figuring

out what's wrong

and

it happened to me many times

like this target variable accidentally

got into the data frame

and that's why i

always try to delete it from our

after splitting the data i try to delete

this data remove it out in a separate

variable and delete it from the data

frame correctly uh completely

to make sure that i don't accidentally

use it for training purposes

okay

so now we have our data

and

let's check the length

should be correct

yeah so what we did

in this lesson was we

implemented this

we implemented this framework for

validation manually so we didn't use a

library for that we just used the plain

pandas and numpy for that

and we saw how to do

to split our data set into three parts

and

now we actually are ready to move to

the training part so in the next

lesson we will talk about linear

regression


=======
zoom comes session two and we will talk

about setting up the validation

framework

and um

so if you remember

like for uh

from the last uh

from the last session we talked about

validating models and we talked about

this model selection process

and we talked that

we need to take our data set

for for validating the model we need to

take our data set

and split it into three parts so the

first part used for training

the second part we use for validation

and the last part we use for testing

so

we train a model

we check it if it works fine on

validation data set and we

leave this

we leave this

test data set

only at the end so we use it only very

very occasionally very infrequently only

to check if our model is doing good

so we need to take our data set and now

split it into three parts

right train

validation and test

and then from each of these

parts we create

you know this uh

feature matrices matrix six x

and then target variable y so this is uh

train

so this one is validation

and

also the one for test

okay so this is what we need to do right

now so this is what we'll do now with

pandas

so first of all um

we need to we will do this 20 split so

it will be 20


and


so we need to calculate how many 20

actually is

so the size of our data frame actually

we should have looked at this at the

very beginning when we just loaded so it

has almost 12 000 records

and uh

yeah 20 of that is

approximately

two

um

thousand four hundred right

so

and of course uh we

we don't want to have a number that is a

fraction like it's

we want to have a number that is integer

so we

round it using this

so let's

do this for all three so this n variable

will be the length of our data frame

then the size of

validation

data set will be

20 of

n and then we round it

then

and

test will be the same

so this is the

size of our test data set

and then

and train this will be the size of our

train data set so we can write here 0.6

but we can have a problem that

now

it can be different so now let's check

and

test

so ideally they should uh

be the same

but you see because of rounding so

because here we probably we were

rounding up so that's why uh

it's not the same so like we cannot

split it using these values

because actually

n

here the number of records in our data

frame is actually bigger than yeah the

size of this

so for that to make sure that we don't

accidentally leave a few records what we

do is

we instead of doing that

we just

so what we do is we

take this part out

take this part out

and whatever

is there after taking these two out

we take for training

for that we just do

n minus and validation

minus and test

and yeah so this now they should add up

so now they

they're the same

and then uh so now we know the size of

which of which

uh so let's

just look at the size

which data set so for training it's uh 7

000 for

validation it's uh 2 000 um almost 400.

so this is what we use for

now so this is the sizes of our data

frames

so now we know the size and we need to

take a part of the data frame

out of this size

so for that

we can use this i lock thing that we

talked about

and i lock instead of just

introduction to pandas we talked that

talked about

this dialogue and we mentioned that it's

possible to give it

a list

and it would

return a data frame a subset of the data

frame

it's actually possible to use a range

range so let's say if we want to get 10

first records we can do something like

this so it means from the beginning till


so it's again not x

inclusive so it's uh from zero to nine

and we get uh first uh records

and it also works like let's say if we

wanted to to get from ten to twenty

we do this

and let's say if we want to get

something till the end

how many records are there

so let's say


just want to get remaining four

so this is how we do so it just knows

that if we use this notation

it it's from this one to the end right

so that this

so potentially what we can do is we can

say okay let's give us just the first uh

2382 records and we will use them for

validation

and then the next records uh

so let's see that will be the first one

let's call it data frame

validation

then we can

say okay everything that is after this

one and to the next uh you know

whatever

for

4 thousand

700 something

will be a

test data set so we actually need to sum

them

so this is test

right so now we have these two and then

let's say dataframe train will be

everything that is left

so we just take

this one

and use so till the end right and then

now we have

this so here is a problem we have a

problem here that it's sequential right

so let's say

uh

in our validation data set now we have

all the beam doubles bmws

and we don't have bmws in train right so

we see that there is some order

in this uh in this data set so we need

to shuffle

these records right to make sure that

there are bmws in all three data sets

right and in general it's always a good

idea to shuffle

data to make sure if there is some

accidental order in in the data we want

to break it

so for that what we can do is

if you remember that we can in this i

look we can use uh

we can just specify uh

an arbitrary sequence of numbers and it

will return

them in this order so what we can do is

we can take numbers from uh

can take numbers from

zero to n

then we can reshuffle them

and

we can so these are numbers let's say

from

zero to

n minus one

right so we reshuffle them

so you know we have like 10 here

uh one then 10 000

and so on here zero for example so we

reshuffle them and then we take uh

first twenty percent

for validation and uh

twenty percent for

uh uh

for um

for test and then remaining for

train

okay so let's

implement that

actually i think

if we do it slightly differently

so

i think it might makes more sense to

start the same

so let's say we take

data from train first

and then from train and train cruise

plus and validation

and then we take the rest

so

i think it's a bit more logical to

the first to basically follow uh the

same distribution so first we

take this out then this one and then we

start

okay

so now what we want to do is this one so

we want to generate a sequence of

numbers from one to ns1 n minus one for

that we use a function from numpy called

arrange so it's doing exactly that so it

generates a sequence of numbers so let's

call it idx it's short for index

and then what we want to do now is we

want to shuffle it so

for that there is a function in random

called shuffle and we just do that

and now our index is shuffled

and now let's say if we

take um

first 60 of that

we can use this for our

trained data set right so let's now just

replace this here

with

this

so we just need to

add one more thing inside so instead of

just

getting

uh rows directly from this

um i look

we get them

through this index so maybe let me just

show you um

i look

it

let's see what happens if we take first

step

yeah so when it's shuffled

yep so you see it takes first 10

in shuffled order

right so we want to do this but not 10

but the the number of uh records we have

like 60 and 20 20

and this is what we have

yeah so we did the split

the problem with this when you run it on

your computer you will have different

records here so the first one will not

be porsche but will be something else or

not gmc but something else

to make sure it's reproducible

we usually set a random seed we talked a

bit about

that in the introduction to numpy so we

want to make results reproducible

so for that we use uh

sit

right and we set c to some number let's

say two

and let's again generate this uh index

then shuffle it

and then take a subset

so now that the first one is chevrolet

and if we do it one more time

it's a gangster value so and on your

computer when you do this if you have

the same version of numpy

you will have the same

you will have the same subset

yeah and

that's uh actually what we need to do so

now we have three uh data sets let's

check the length of this uh data sets

train

validation and

it should be seven thousand so let's

check

one more time

because it should be

this way

right so it should be

from 0 to


okay now it's correct

and

a few things before we finish so now we

see that uh when we look at train

we see that this index

is

it changes right so here we have numbers

in this order

so sometimes it's just inconvenient so

we don't really need to know what was

the original index of this record so

what we can do is

reset the index

we talked about this separation in

in the introduction so we don't need

this index column that's why we drop it

and we basically

reassign it back to

to this data frame so you see now it's

from zero to

seven thousand

and finally the same for

test

okay

and then um

we need to do some transformation with

our uh y

so this the f train this is something

we'll use to make our feature matrix x

but if you remember that in our df train

this msrp

we actually need to

turn it to apply the log transformation

to this

lock 1p i think

yeah so this is the lock transformation

and instead of

keeping the series let's immediately get

the

pandas

values

so instead of using pandas

series let's get number

numpy array immediately to use it

because we don't need all these indexes

and

other things

and that will be our

y variable for train and we do the same

for

validation and test

okay now we have these variables

and the last thing that we need to do is

we need to remove this msrp variable

from our data frame for that we use the

dell operator

and we need to delete it because we

might accidentally use it

and we want to avoid this and if we

accidentally use this and then we will

use the price

variable as a feature for predicting

price and of course our model will be

perfect and

we might spend a lot of time figuring

out what's wrong

and

it happened to me many times

like this target variable accidentally

got into the data frame

and that's why i

always try to delete it from our

after splitting the data i try to delete

this data remove it out in a separate

variable and delete it from the data

frame correctly uh completely

to make sure that i don't accidentally

use it for training purposes

okay

so now we have our data

and

let's check the length

should be correct

yeah so what we did

in this lesson was we

implemented this

we implemented this framework for

validation manually so we didn't use a

library for that we just used the plain

pandas and numpy for that

and we saw how to do

to split our data set into three parts

and

now we actually are ready to move to

the training part so in the next

lesson we will talk about linear

regression


>>>>>>> 4e0b62081cbb4de5280aecd60424a255a9cd6ec1
