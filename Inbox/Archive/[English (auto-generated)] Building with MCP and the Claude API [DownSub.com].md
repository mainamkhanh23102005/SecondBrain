Am I reading your status updates then in
your Slack and those are all claw
generated?
>> I Yeah, I'm never I'm never actually
writing anything
claw the whole time. Okay, good to know.
>> Hey, I'm Alex. I lead cloud relations
here at Enthropic. Today we're talking
about MCP and the cloud API and I'm
joined by my colleagues.
>> Hey, I'm Michael. I'm an engineer on the
API team here at Enthropic. I'm John and
I work on the model context protocol
team here at Anthropic.
>> To kick us off here today, uh I really
want to give a high level overview of
just what is MCP?
>> MCP is uh the model context protocol and
uh it's a way of providing external
context to models. And so if you have a
chatbot and you're in a conversation,
the history of your conversation is your
context. And the model only has the
ability to see everything that you've
typed in. um which is really useful for
some kinds of tasks like help me solve
this problem or write this thing. But
sometimes cloud needs access to um
things outside of its box like it needs
to be able to talk to the internet or it
needs to be able to reach out to a
travel agency to book your flight. And
so that's kind of where MCP comes in
like it provides these external contexts
to claude so that it can take actions
for you on your behalf in the outer
world.
>> Right. Yeah. I've I've heard a good
analogy in the past of MCP being like
the universal connector between
applications and the model. Yeah.
>> So, a way for us to tie cloud into
everything else that it might need
access to all the other data sources,
tools, everything.
>> Yeah, definitely
>> out there on the internet basically.
>> Why did we build this? What was kind of
the intention? I mean, it seems useful
to have these connections, but like why
did we take that on specifically and why
make it a universal standard protocol?
So I think as we were um starting to get
further and further along in tool use in
uh as cloud's capability, we were
starting to notice that we were
re-implementing a lot of the same
capabilities in v various different
context. So my assistant that I had in
my coding editor um had to get a web
search tool associated with it. Um but
so did claw.ai and so did all these
other surfaces where we want claude to
be able to interact with the outside
world. And uh we figured it would be
good to have a single unified protocol
that um we can implement uh set of
functionalities once
>> and um take that everywhere. So build it
once and configure everywhere. So the
same web search functionality that I
might get on cloud code uh will be the
same web search functionality that I
would get on cloud.ai.
>> Okay, that makes sense. uh creating that
universal compatibility basically when
we have tons of applications that might
need these same connections. Um now our
approach to MCP spec specifically with
open sourcing it was pretty different I
think than a lot of other integration
paths that other companies were going
down at the time. Why did we think to
open source it? Like what was kind of
like the driving factor behind that? I
think there's a lot of value in open
standards to allow uh a wide network of
of engineers, companies, um individuals
to go and uh build an ecosystem around
something. And uh we could have gone and
built the uh the claude app connector
that allows you to tie your things into
cloud, but then like you end up with a
really kind of bad uh user experience
for if you're if you're using multiple
models. If if I'm a company like Asana
and I want to go connect like do I have
to go implement my claude connector and
my open connector or my gro connector
and my Gemini connector and that that
ends up being kind of a nightmare. And
one of the things that we had noticed is
that models having access to external
context is is kind of good for everyone.
It's like a rising tide floats all boats
type of situation. And uh we had this
internal protocol that was really
valuable um for us standardizing our
model interactions. And so we went and
open sourced it as a as a way of being
like hey like we found this useful maybe
the world would find this useful also.
And it got incredibly popular incredibly
fast. Like it turns out a lot of people
had had the same kind of need and jumped
on it and started just hacking together.
Even with like the minimum support,
people started hacking together really
incredible dev environments and it kind
of like boosted I think it was the
fastest growing open source like
protocol like
>> in history. Wow. It's been truly kind of
stratospheric growth in there and
there's like a massive need for it.
Yeah. So we went and open source that
and since this has taken off it's truly
succeeded our wildest dreams when we're
releasing this like little specification
and so we've done a lot of work um as
this is starting to move between a a
neat way for anthropic a project for
anthropic to go and get context to its
models into an industry defining
standard like ecosystem. We've done a
lot of work to go and move that into a
proper open source foundation and like
work with all the other providers and
make MCP something that's durable and is
here for the long term.
>> What is the lay of the land actually on
MCP right now? Both in terms of like the
open source community, but also the
technical spec itself. It's been like I
guess almost a year, a little under a
year since we first announced it. And I
feel like a lot of folks still have kind
of intuitions that were based in how it
was, you know, earlier this year and
early 2025 or something around that. But
the protocol is moving so fast and
things are changing. What's like the
current state in your guys' mind of MCP?
>> I feel like a big aha moment for me at
least was uh when we released remote MCP
support. Some of the initial quirks of
the protocol were that you had to run
everything effectively by yourself. Um,
which um prevented providers of MCP
servers like Asauna from uh being able
to host their own servers that you could
just access very very quickly. Um, and
it made the setup process very very yeah
clunky.
>> And um I think that yeah, a very big
step change in my opinion was when we
kind of provided first class support for
um remote hosted MCP servers that
drastically reduced the setup process.
um so that end users can just get
started fairly quickly.
>> And now we have a registry of these
servers so people can actually like
upload these to the registry and then we
like authorize them or we approve them
and
>> Yeah, totally. So the the the open
source uh the the open source project um
has a we've just released a a central
registry of MCP servers. Um, in kind of
keeping with the open source ethos, we
have both a registry that's hosted at
the model contact protocol organization
site and also a standard that allows
other organizations to extend the
registry, pull that information in. Um,
and so we've seen massive growth of like
MC, GitHub, MCP, like Sauna MCP, like a
lot of companies are are are building
and deploying these endpoints. And so
it's becoming easier to pull this in uh
from a in in the past you would have to
go and if you wanted to interact with
GitHub you'd have to go find some random
developer who had hacked together a
GitHub connector and then trust their
node.js install on your computer to go
in and now you can just go hit the
official GitHub site like I think it's
mcp.github.com you can put that into
your cloud code or cloud.ai AI and then
extend cloud with the ability to
interact with GitHub. So, it's really
maturing in a way that's really cool.
>> That's pretty cool. And I've been using
the GitHub MCP for things in cloud code
as well. And it's nice to just have that
one URL endpoint that can plug in.
>> Is there any kind of fun unique MCPS
right now in the registry or outside of
the registry that you guys have seen?
>> I think one that um I think has been
really really interesting to watch uh
it's called context 7. M
>> um so one of the biggest limitations of
large language models is that they have
a knowledge cut off um that's usually
you know delayed by a couple of months
um which means that working with like
the latest and greatest packages as a
software developer um sometimes
difficult with LMS because they will
just give you outdated information um
and what context 7 does is um it takes
care of pulling um documentation from
these websites um like Nex.js's JS's
website or even our own API's website
and keeping those up to date and all you
have to do is configure your um MCP
connection once and Claude will have the
access to the latest information out
there on whatever it is that you're uh
developing against.
>> Okay. Yeah, I think I had heard of that.
So, we're basically pulling in the
latest docs, everything. And I know
right now we're also in the mid
transition of a lot of folks making
their docs completely just raw text and
accessible to LLMs. So I'm assuming
that's like pulling from that same sort
of information, right?
>> Yeah. So this is like the LLM's.ext
um format. Yeah. Which I've seen a lot
of like adoption of um like throughout
the entire tech industry, which has been
very exciting to see.
>> That's cool.
>> Any from you, John? from from my end
there's um I I found it useful I I from
from my my work as a as a software
developer I really like um playright as
an MCP server uh which allows uh Claude
to go and interact with browsers as
though it was a user clicking around. So
if you're like working on a website uh
Claude can read all your CSS and read
your HTML but it can't actually look at
your web page. But if you go and install
the Playright MCP server, then you can
have Claude go look at your web page and
give you advice on how to how to make it
more beautiful or like fix alignment
issues.
>> So, it's like actually screenshots.
>> Yeah, it's actually loading it up in a
browser, browsing around using um
Playride. It's a Microsoft uh uh project
that allows uh remote browser driving.
>> What happens when you put that in a loop
with something like cloud code? Oh, you
can just uh you can get some
self-improvement loops. Like if I tell
Cloud Code to go and fix an alignment
problem in a header, um it can go make
some changes to my HTML, make some
changes to my CSS, reload the page if
necessary, then go look at it again and
be like, "Oh, everything looks better,"
or "That didn't fix it, and it has the
context of seeing both its changes, and
then actually being able to like take a
screenshot of the website and and say,
"Oh, this set of CSS changes actually
led to this effect that I didn't intend.
>> Let me roll that back and try a
different way." M
>> it's a different type of alignment
problem.
>> Yeah,
>> normally
>> the CSS alignment problem maybe if I
need even a harder problem in some
>> um switching gears a little bit. Uh how
if I'm a developer and I want to use the
the cloud API, how can I use MCPS with
our API and with cloud models?
>> So that's excellent question. The
canonical standard way of doing this is
to install the MCP SDK um set up your
own loop like you mentioned with cloud
code um and handle connecting to any MCP
server that you need to get connected to
um but it's essentially your
responsibility as a software developer
to put together all the glue work um
which is great and it works um but what
we recently released um directly into
the API as a native feature is the MCP
connector feature which allows you to
just specify where your remote MCPs of
like mcp.github.com
and um provide us with whatever
authorization information and we can
take care of that um calling loop um of
executing the tools and getting the
results fed back to the model for you.
So all you really have to do is send a
single API call that says like
>> give me my lettuce pull requests and it
will it will go ahead and take care of
that for you.
>> That's awesome. Yeah, I've been hearing
from a lot of developers that they've
just been able to delete tons of code
because they just have that so they
don't have to handle all that back and
forth themselves now. just like pass in
the URL and to the endpoint and then
you're kind of good to go.
>> Um, what are some other tips for
developers using MCP?
>> I think that um, the main one that I try
to give developers when I talk is that
MCP servers and tools are really at it
core prompts. And so we've kind of
learned that if you're writing AI
powered applications, it's really
important to be careful and precise
about the language that you use when
you're prompting the model. This extends
to
everything about defining your MCP
server, like defining your tool names uh
appropriately, giving them descriptions.
Maybe your description has a few shot
examples in the description of how to
use it. Giving like appropriate
parameter names. Um, this is all stuff
that's going to affect your model's
behavior when it interacts with the MCP
server. An example that I had was I was
making an image generation server and I
had a tool called generate image and
then it had a a field called description
and that's it. And then I you tell
Claude like hey generate me an image of
a cute puppy and it'll go go along call
the tool be like description a cute
puppy. Great. Um if you go and change
that and you say like uh this tool calls
the xxx diffusion model version y and is
should be prompted in this style uh for
best results like use this kind of
descriptive language to do do all of
this. Claude has information about like
how to interact with these systems and
it just needs to be told uh oh great I
know that I'm talking to a diffusion
model now I'm going to change my
language what I'm going to use in this
prompt and it's going to go and instead
of asking for Quppy it's going to give
you a much more detailed uh diffusion
model prompt that will give you much
better results. you get much better
results from your MCP server just by
changing a few words in your description
or your prompt name just the same as you
get better results uh writing pull
requests or doing any sort of knowledge
work with claude that you you would by
uh by tweaking those. I mean, I myself
forget this all the time that when
you're dealing with a tool or some sort
of description in isolation as you're
like working on a new feature for some,
you know, AI app, it all gets pulled
back into the same prompt, right? And
it's all just like one text string at
the end of the day that's getting fed
into the model on each request. And
yeah, that's good advice that like, hey,
that's part of the prompt, too. like the
description that you're writing in some
JSON somewhere in your code is still
going to be pulled into that same prompt
that gets sent to Claude on it on the
request. Let's talk a little bit about
context management as well and like
dealing with lots of tools and lots of
results. I mean this is a huge problem
for LMS right now in terms of polluting
the context.
>> Curious if you have any thoughts there
on how developers should think about
that with MCP. Yeah. So, I think a big
anti pattern that we've seen a lot of
developers make is just stuffing their
MCP servers or their API requests with
MCP servers with just tons of tools or
tons of MCP servers, which not only gets
expensive because you're just generating
tokens for every single one that you're
adding, but um also has a tendency of
confusing the model. An example is um if
you connect both your linear and your
Asauna task management MCP servers um in
the same request, both of those might
have a uh get project status uh MCP tool
um and the model will not have an
implicit information about which one of
them to use in which context. But beyond
that, you're just um yeah, you're you're
essentially confusing the model by
giving it potentially conflicting
information. So just um being very very
careful and deterministic about like
which tools you add, making sure that
the ergonomics around them also make
sense and that using those tools feels
natural to you if you were getting to
use them yourself. Um but beyond that,
making sure that you um yeah, just don't
don't include any information that might
not necessarily help with the current
turn of user prompts. So sometimes older
parts of the conversation um that might
involve very introductory information
like you know what's the weather today
um might not be as relevant much much
later on in the conversation when you
are moving on to the latest news or some
other information that you need from the
model. M I often get asked how many
tools can I pass in cloud or how many
MCP servers can I hook up at one time
and it seems like it's not so much a
number question rather it's like a how
distinct are the tools from each other
and how well defined and scoped out
>> is that correct or is there also kind of
like a absolute number of MCPS
you you also end up with an absolute
number like each if your context window
is is x tokens each server is going to
pull in a number of function
definitions. Each of those is going to
eat it up. So, you're going to um just
just start as you give LLMs more
information, it it makes it harder for
them to make good decisions. And so,
even though it will probably work if you
hook up to a bunch of a bunch of
servers, um it'll probably work better
if you can give Claude a subset that's
relevant to the task that it's looking
at. One other point coming out here from
what Michael was saying is if you're
designing an MCP server, uh generally if
you can have one or two tools in your
server, uh versus having uh 15 or 20
tools, it'll help the model a lot. And
so it's sometimes
m MCP like interface development is is a
bit different than API development where
we're feeding these into LLMs. And if
you give a tool a description that maybe
takes some natural language or has like
as part of like filling out the
parameters, the model is going to make
some decisions and and generates some
text you can maybe get away with instead
of an API where you'd be like get
projects, get posts, get users, you
might just have a like get info tool
where where the because you're calling
LLM will be able to like look at your
description and fill out whatever
information it needs and that way you
can provide
like a much smaller set of tools, you
will both play nicer with other MCP
servers and you'll ensure that your
server gets called more efficiently
appropriately,
>> right? So, it's not always a onetoone
translation like there's different
levels of abstraction apply
>> and perhaps the API spec is not the best
defined thing for the model to take in
either. Yeah.
>> Um, so you guys live and breathe MCP all
day every day basically. uh how are you
guys using it whether it's at work or uh
whether it's at home or a side project
or anything else I know the example of
playright but is there other ways that
you guys are experimenting with MCP on
the side one of the biggest use cases
that I found personally is um anthropic
is often an information highway there's
just so much information all over the
place between our Slack and our docs and
our codebase um and getting the latest
status on how the project that I'm
currently on is going is not often very
very easy to understand from just a
single source. Um so what I've gotten in
the habit of doing is um I will either
on cloud.ai or on cloud code set up my
MCP servers to connect to all these
various locations. Um and I'll just ask
it um hey here's a couple of examples of
past project updates that I've written
myself. Can you go find information from
the last week and generate a status
update uh using the same exact format?
And I would say that like the success
rate on that is is much much higher than
I originally thought. Am I reading your
status updates then in your Slack and
those are all claw generated?
>> I I'm never I'm never actually writing
anything reading claw the whole time.
Okay, good to know. How about you, John?
>> I I found uh a couple of angles from
hacking around my home home hardware. I
I have some MCP servers running on my my
home network that can control things
around my house. And so I can go and in
a conversation with Claude be like,
"Hey, like did uh did I leave my door
unlocked this morning?" And Claude can
say, "Yeah, your door is currently
unlocked. Would you like me to lock it
for you?" And come back and be like,
"Yeah, that would be great." Uh that
sort of thing is really useful. Um kind
of fun to play with. It's kind of feels
like a sneak peek into
what the future world might look like
that it's there's kind of a magical
feeling with MCP servers. uh because you
get these sort of emergent properties
from adding them that you
might not expect like the the an example
of of this is uh when we were very first
time we were started playing with MCP
servers,
I built a knowledge graph graph server
with some of my colleagues here at
anthropic and
>> a knowledge graph in this case is
>> a knowledge graph meaning uh we wanted
to give cloud the ability to take
memories and form like connections
between memories. And so it's an MCP
server that had two tools. It said a
create memory tool and a connect memory
to other memory tool. And the simplest
possible interface and we hooked this up
to Claude and Claude suddenly you'd have
conversations with Claude and it would
enter investigative journalist mode
where I I'd say like I play piano and
Claude would be like that's amazing.
What do you like to play? And I'm like,
I like to play rock on and often. It's
like that's is there any anything that's
that's your favorite there? And and I'd
look at the knowledge graph and Claude
is going and scribbling down and be like
user has sophisticated classical music
taste and it's like trying to find like
like uh it's it's skilled in instruments
and
>> and that's just from like and from such
a small change that you provide it. And
one of the really cool things with
having MCP as a protocol is if you hook
in your Gmail server with your home
automation server, then uh maybe you can
go and claude can figure out some way to
solve a problem that you ask it by
connecting those two together you might
never have thought of.
>> Right.
>> Yeah.
>> Yeah. There's kind of that fuzzy in
between when these things all get hooked
together where
>> Yeah.
>> pair that with Claude's kind of general
intelligence and
>> interesting things can happen. And it's
like one of the core differences between
MCP and um like traditional structured
APIs where because everything is so
fuzzy and because the LMS are smart
enough to just kind of smush it together
like you care a lot less about contracts
like there's this interesting property
where if I have an MCP server for
interacting with Gmail and then I go and
I
>> do some eval and I find like a better
set of tools and descriptions to
interact with Gmail and it changes from
15 tools with a set of descriptions to
like two tools with the other one. Um, I
don't have to go and roll out a new
version of my API for that. Like if
you're changing your API in a massive
way like that,
>> you have to deal with breaking changes,
>> breaking changes, talking to your users,
doing all of that. MCP, I can just roll
that out and because the intent of the
MCP is to allow Claude to interact with
Gmail. It's not like I'm going to
provide a read emails tool and a write
email tool. Um, so it's it's
>> yeah, it's about more like the high
higher level intent and like actions,
right? And like the specific technical
detail of how we get there.
>> Yeah.
>> Yeah, that's really cool.
>> Um, so where's this all headed? Where's
MCP going to be in, you know, 6 months,
12 months, year plus?
>> That's an interesting question because
I've always viewed, you know, like John
said, MCP is a protocol. Um so it's very
interesting to see popularity for a
protocol considering that um it you know
if MCP is successful and um us and
everybody that integrates with it did
their job right um we should never know
that MCP is is happening under the hood
um it should just be you using whatever
program or app that you're using um and
MCP is happening under the hood just
making everything glue together and LLM
kind of configure everything so you're
just giving it the arms and the legs
that it needs
>> but yeah it's it's it's always
interesting to me to see the uh the hype
around MCP,
>> right? Do you think that's going to
continue? Is there like a plateau here
or what does that actually look like in
terms of protocol? Is there any sort of
precedent we can look at to like judge
MCP against?
>> I think it's hard applying a precedent
to anything in the world of of AI that
we're in. Um but uh I I definitely see
um a lot of the stuff that John and and
his colleagues over on the MCP team have
been doing um is very exciting and it's
very to me it's been amazing seeing um
companies big and small um come to the
table and come talk about how we can
proliferate it and make it this
ubiquitous thing that is just everywhere
um the same way that
>> I don't know our internet is. One one
thing that's that's really exciting for
me going forward, I think we're at a
point now where a lot of people have
realized the value of MCP and they've
started writing these servers. But in
terms of the MCP's servers as prompts
analogy, we're in like very early days.
And so
>> I'm really excited for people now that
they've started building out these
servers to start like evaluating how
they how they work and making them
better. And I'm excited for it to start
to become a metric by which you might
evaluate like a vendor for your for your
work. Like if I'm if I'm hiring a log if
I'm paying someone to do log analytics,
for example, it would be really cool.
It's really valuable to me if I could
just hook in your log analytics MCP
server into my cloud and say, "Hey, my
site is down. What's going on?" And if
they've gone and designed and developed
a a really wonderful MCP server that
gives Claude the tools it needs to like
interact with their services and find
those answers, then that's like a huge
selling point for me as an engineer
because then I can I can rely on this
functionality. I don't have to build it.
And I'm excited for this to start
becoming more mature and have it be less
of it's exciting that we've shipped an
MCP server and starting to see people
compete on we have the best MCP server.
this is going to make your life so much
easier. Like you should use us because
we interact with Claude in this way.
>> Well, I'm excited for that future as
well. Um, thank you guys for coming on.
This has been great. Ah,
>> thank you so much.
[Music]