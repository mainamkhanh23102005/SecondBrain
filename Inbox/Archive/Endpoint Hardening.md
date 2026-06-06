ThreaTs and aTTacks
on endpoinTs
after completing this module, you should be able to do the following:
1 Identify the different types of attacks using malware
2 Define application attacks
3 Explain how threat actors use application attacks
4 Define adversarial artificial intelligence attacks
Module
3
Front-Page Cybersecurity
despite the skyrocketing number of ransomware attacks in the past five years, ransomware has been used for more than
30 years. The first known ransomware attack was initiated in 1989 by an AIds researcher. he carried out his attack by dis-
tributing 20,000 floppy disks to other AIds researchers in more than 90 countries with an accompanying message that the
disks contained a program that analyzed an individual’s risk of acquiring AIds. however, the disk also contained ransomware
that remained dormant until the computer had been turned on 90 times. At the next startup, the ransomware displayed a
message demanding a payment of $189 (plus $378 for use of the program).
Today, ransomware attacks are running rampant. There were an estimated 184 million ransomware attacks in 2018. In
2019, attackers using ransomware turned their sights on government agencies, educational institutions, and even health-
care providers. but these incidents were not just expensive inconveniences; the disruption they caused put health, safety,
and even lives at risk. ransomware attacks on healthcare providers resulted in emergency patients being redirected to
other hospitals, inaccessible medical records, cancelled surgical procedures, postponed lab tests, and suspended hospi-
tal admissions. emergency responder and law enforcement agencies were also common victims so that emergency 911
services were interrupted, police were unable to access details about criminal histories or active warrants, and jail doors
could not be opened.1
What is fueling the rapid rise of ransomware? Is it a growing sophistication of attackers? Misguided users? More powerful
ransomware? The answer, according to some, is none of these but something entirely unexpected.
The rapid rise of ransomware is attributed to cyber insurance.
cyber insurance started 20 years ago by lloyd’s of london, and today it is an $8 billion industry. About 80 percent of
lloyd’s cyber insurance is written for u.s. entities. A cyber insurance policy is not cheap. The city of houston is now taking out
three $10 million policies from three different insurance companies for a total of $30 million in coverage. For this, houston
will pay $471,400 annually in premiums. Another Texas city, Fort Worth, has only a $5 million policy, but it costs $99,570 in
annual premiums.
how can the blame be placed on cyber insurance agencies for the rapid growth of ransomware?
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

66 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
Following a ransomware attack, enterprises and government agencies need to get back to normal as quickly as possible.
every minute they are locked out of their computers because of ransomware, they are losing money or putting individuals
at risk. cyber insurers claim that it makes more financial sense to pay the ransom and get the key to unlock encrypted files
so that organizations can get back to normal quickly.
however, paying the ransom is actually an advantage to the cyber insurance agencies. by paying the ransom, cyber
insurance agencies hold down their overall costs. They do not have to pay for lost revenue due to downtime brought on by
ransomware or pay for third-party security consultants to aid in the data recovery. but when insurers reward attackers by
paying the ransom, they might actually be encouraging more ransomware attacks because attackers know they will be paid.
In addition, an increase in the number of ransomware attacks could frighten more businesses and government agencies
into buying cyber insurance policies.
but doesn’t paying the ransom cost the cyber insurance agencies money? no. cyber insurance is a very lucrative busi-
ness. The “loss ratio” is an industry standard for comparing premiums paid for insurance (what comes in) against insurance
claims (what goes out). For all property and casualty insurance, like auto insurance and homeowner insurance, that loss ratio
is about 62 percent (or for every dollar of premiums, about 62 cents are paid out in claims). however, for cyber insurance, it
is only 35 percent, meaning that the cyber insurance agencies pay 35 cents in claims for each dollar of premiums.
some researchers claim that cyber insurance is increasing number of ransomware attacks. In fact, the chief technology
officer for a well-known antivirus company has said, “cyber insurance is what’s keeping ransomware alive today.”2
Throughout the years, different words have been used to describe network-connected hardware devices. Thirty years
ago, when the TCP/IP protocol was becoming popular, the word host referred to any communicating device on the
network (networks were made up of hosts). Twenty years ago, as servers became more popular, the word client was
used (clients made requests to servers).
Today, a different word is commonly used when referring to network-connected hardware devices: endpoints. This
change reflects the fact that devices that are connected to a network today are far more than a computing device with
a keyboard and monitor. Instead, devices ranging from mobile smartphones and tablets to wearable fitness trackers,
industrial control system sensors, automotive telematics units, and even personal drones are all network-connected
hardware devices. The word endpoint has become an accurate description of today’s end-user technology devices.
This change in terminology also reflects the increased risks that have multiplied—exponentially—with the increase
of these new devices. Instead of protecting hosts or clients located inside a network security perimeter, today each
endpoint is a target for attackers to attempt to steal or manipulate their data. And because the endpoints are connected
to the network, a vulnerability on an endpoint can result in an attack that penetrates the network and infects all other
endpoints. In short, today every endpoint is a potential entry point.
This module examines threats and attacks on endpoints. It begins by looking at attacks using various types of
malware and then looks at application attacks. It concludes by examining adversarial artificial intelligence attacks.
aTTacks Using Malware
✔ CertiFiCation
1.2 Given a scenario, analyze potential indicators to determine the type of attack.
In a legal setting, a “computer contaminant” is defined as any set of computer instructions that is designed to modify,
damage, destroy, record, or transmit information within a computer, computer system, or network without the intent
or permission of the owner of the information, computer system, or network.3 This legal definition is the basis for the
definition of the cybersecurity word malware (malicious software), which is software that enters a computer system
without the user’s knowledge or consent and then performs an unwanted and harmful action. Malware is most often
used as the general term that refers to a wide variety of damaging software programs.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Malware is continually evolving to avoid detection by improved security measures. noTe 1
According to one report, the number of new malware releases every month exceeds
20 million, and the total malware in existence is approaching 900 million instances.4 Yet The popular vulnerability feed
no standard has been established for the classification of the different types of malware Mitre common Vulnerabilities
so that like malware can be grouped together for study. and exposures (cVe) assigns a
One attempt at classifying the diverse types of malware can be to examine the cVe Id number, brief descrip-
primary action that the malware performs and then group those together with simi- tion, and any pertinent ref-
lar actions. These malware actions used for groupings are imprison, launch, snoop, erences but does not try to
deceive, and evade. group common vulnerabili-
ties together. likewise, the
imprison national Vulnerability data-
base (nVd) does not attempt
A prison is a building or location housing individuals who have been deprived of to classify vulnerabilities. both
their freedom. Some types of malware attempt to take away the freedom of the user cVe and nVd are covered in
to do whatever they want on their computer. The types of malware that imprisons Module 2.
are ransomware and cryptomalware.
ransomware
One of the fastest-growing types of malware is ransomware. ransomware prevents
a user’s endpoint device from properly and fully functioning until a fee is paid; that
is, it takes away a user’s freedom from freely using their computer until the ransom
is transacted. The ransomware embeds itself onto the computer in such a way that
it cannot be bypassed, and even rebooting causes the ransomware to launch again.
Ransomware became widespread around 2010. This earliest ransomware dis-
plays a screen and prevents the user from accessing the computer’s resources
(called blocker ransomware). The screen contains instructions that pretends to be
from a reputable third party, giving a “valid” reason for blocking the user’s computer. One example is ransomware that
purports to come from a law enforcement agency. This message, using official-looking imagery, states that the user
performed an illegal action such as downloading pornography and must immediately pay a fine online by entering a
credit card number. Figure 3-1 shows a blocker ransomware message.
Figure 3-1 Blocker ransomware message
esnopseR
ytiruceS
cetnamyS
:ecruoS
Module 3 ThreaTs and aTTacks on endpoinTs 67
noTe 2
some malware has more than
one of these actions. however,
in terms of classification, the
primary action of the malware
is used here.
Another variation of this type of ransomware pretends to come from a software vendor and displays a fictitious
warning that a software license has expired or there is a problem with the computer such as imminent hard drive
failure or—in a touch of irony—a malware infection. This ransomware variation tells users that they must immediately
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

renew their license or purchase additional software online to fix a nonexistent problem. The ransomware example in
Figure 3-2 uses color schemes and icons like those found on legitimate software.
noTe 3
researchers have devel-
oped an entirely new means
of detecting a ransomware
infection, and it works even
if the type of ransomware
is new and has never been
seen before. When ransom-
ware begins to encrypt files,
the computer’s temperature,
power consumption, and
voltage levels experience a
surge. sensors can detect
these surges and immedi- Figure 3-2 Ransomware computer infection
ately halt the encryption pro-
cess, stopping ransomware As ransomware became more widespread, the threat agents dropped the pretense
dead in its tracks. that the ransomware was from a reputable third party. Instead, they simply blocked
the user’s computer and demanded a fee for its release. Ransomware attackers have
determined what they consider the optimal price point for payment to unblock a
noTe 4 computer: the amount must be small enough that most victims will begrudgingly pay
to have their systems unblocked, but large enough that when thousands of victims
originally, the FbI did not sup-
pay up, the attackers can garner a handsome sum. For individuals, the ransom is
port paying a ransom in any
usually around $500. However, for enterprises, the price has increased dramatically:
circumstances. It said, “The
the average ransom paid for one type of malware was more than $1.3 million, and the
FbI does not advocate paying
average ransom for all ransomware has increased by one-third.5
a ransom, in part because it
Ransomware continues to be a serious threat to users. Threat actors have
does not guarantee an orga-
now shifted their sights to state and local governments that typically have
nization will regain access to
weaker security. In 2019, two-thirds of ransomware attacks targeted state and
its data . . . paying ransoms
local governments;6 to date, more than 350 of these governments have been the
emboldens criminals to target
victims of successful attacks.7
other organizations and pro-
vides an alluring and lucrative cryptomalware
enterprise to other criminals.”
In recent years, a more malicious form of ransomware has arisen. Instead of just
but in late 2019, the FbI seem-
blocking users from accessing the computer, it encrypts all the files on the device so
ingly softened its stance by
that none of them can be opened. This is called cryptomalware. A screen appears
adding, “however, the FbI
telling the victims that their files are now encrypted, and a fee must be paid to
understands that when busi-
receive a key to unlock them. In addition, threat actors have increased the urgency
nesses are faced with an
for payment: the cost for the key to unlock the cryptomalware increases every few
inability to function, execu-
hours or days. On some occasions, the threat actors claim that a growing number of
tives will evaluate all options
the encrypted user files will be deleted until the ransom is paid; if the ransom is not
to protect their shareholders,
paid promptly, the key to unlock the files can never be purchased. Figure 3-3 shows
employees, and customers.”8
a cryptomalware message.
tfosorciM
morf
snoissimrep
htiw
desU
:ecruoS
68 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Figure 3-3 Cryptomalware message
noTe 5
With early cryptomalware
In addition to encrypting files on the user’s local hard drive, new variants of
attacks, threat actors only deliv-
cryptomalware encrypt all files on any network or attached device connected
ered the decryption key fewer
to that computer. This includes secondary hard disk drives, USB hard drives,
than half of the times that a
network-attached storage devices, network servers, and even cloud-based data
ransom was paid. however,
repositories. Thus, if a user’s computer in an enterprise is infected with cryptomal-
this resulted in some victims
ware, potentially all files for the enterprise—and not just those on one c omputer—can
not paying a ransom since the
be locked.
risk was high of not getting the
key. Threat actors have since
launch
learned that there is more to
gain in the long run of making
Another category of malware is that which infects a computer to launch attacks on
the key available after a ransom
other computers. This includes a virus, worm, and bot.
is paid. Today, when victims
Virus
pay the ransom, a decryption
There are two types of viruses: a file-based virus and a fileless virus. tool is delivered 99 percent of
the time. however, the key only
File-Based Virus A biological virus is composed of tiny bits of genetic material
works about 96 percent of the
enclosed by a protective shell. By themselves, viruses are lifeless and inert as they
time. This is because specific
wait for a favorable environment in which to reproduce. When a virus encounters a
variants of ransomware have a
host cell, the virus attaches itself to the outer wall of the cell, enters inside, travels
tendency to corrupt data when
to the cell’s genome, merges with its genes, and then tricks the host’s genome into
it is encrypted.9
make copies of itself.
nioctiB
:ecruoS
Module 3 ThreaTs and aTTacks on endpoinTs 69
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

70 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
A file-based virus is remarkably similar to a biological virus. It is malicious computer code that is attached to a file.
A very large number of file types can contain a virus, and Table 3-1 lists some of the 50 different Microsoft Windows
file types that can be infected with a virus. Like its biological counterpart, a file-based virus reproduces itself on the
same computer. Strictly speaking, a file-based virus replicates itself (or an evolved copy of itself) without any human
intervention.
noTe 6 Table 3-1 Windows file types that can be infected
When the host cell is infected
File extension Description
by a virus, the virus takes over
docX or XlsX Microsoft office user documents
the operation of that cell, con-
eXe executable program file
verting it into a virtual factory to
make more copies of the virus. MsI Microsoft installer file
The host cell rapidly produces Msp Windows installer patch file
millions of identical copies of scr Windows screen saver
the original virus. biologists
cpl Windows control panel file
often say that viruses exist only
Msc Microsoft Management console file
to make more viruses.
WsF Windows script file
ps1 Windows powershell script
noTe 7
Early viruses were relatively straightforward in how they infected files. One
one of the first viruses found basic type of infection is the appender infection. The virus first attaches or appends
on a microcomputer was writ- itself to the end of the infected file. It then inserts at the beginning of the file a jump
ten for the Apple II in 1982. instruction that points to the end of the file, which is the beginning of the virus code.
rich skrenta, a ninth-grade When the program is launched, the jump instruction redirects control to the virus.
student in pittsburgh, wrote Figure 3-4 shows how an appender infection works.
“elk cloner,” which displayed
his poem on the screen after
Jump
every 50th use of the infected
Code Line 1
floppy disk. unfortunately, the Code Line 2
virus leaked out and found its Code Line 3
Code Line 4
way onto the computer used
etc.
by skrenta’s math teacher. In
1984, the mathematician dr.
Frederick cohen introduced
the term virus based on a rec-
ommendation from his advi- Program Code
sor, who came up with the
name from reading science
fiction novels.
Virus Code
Figure 3-4 Appender infection
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 71
However, these types of viruses could be detected by virus scanners relatively noTe 8
easily. Later file-based viruses went to greater lengths to avoid detection; this type
of virus is called an armored file-based virus. Some of the armored virus infection some armored viruses scan
techniques include the split infection (it split the malicious code itself into several for the presence of files that
parts and then these parts are placed at random positions throughout the program security researchers typically
code) and the mutation (the virus changes its internal code to one of a set number of use. If those files are present,
predefined mutations whenever it is executed). the virus assumes it is being
Each time the infected program is launched or the data file is opened—either by examined for weaknesses and
the user or the computer’s operating system (OS)—the virus first unloads a payload to automatically self-destructs by
perform a malicious action (such as to corrupt or delete files, prevent programs from deleting itself.
launching, steal data to be sent to another computer, cause a computer to crash repeat-
edly, or turn off the computer’s security settings). Then the virus reproduces itself by
noTe 9
inserting its code into another file, but only on the same computer. A virus can only rep-
licate itself on the host computer where it is located; it cannot automatically spread to several similarities between
another computer by itself. Instead, it must rely on the actions of users to spread to other biological and computer
computers. Because viruses are attached to files, they are spread when a user transfers viruses exist: both must enter
those files to other devices. For example, a user might send an infected file as an email their host passively (by rely-
attachment or copy an infected file to a USB flash drive and give the drive to another user. ing on the action of an out-
Once the virus reaches a new computer, it begins to infect it. Thus, a virus must have side agent), both must be on
two carriers: a file to which it attaches and a human to transport it to other computers. the correct host (a horse virus
cannot make a human sick,
Fileless Virus A fileless virus, on the other hand, does not attach itself to a file.
just as an Apple Mac virus
Instead, fileless viruses take advantage of native services and processes that are part
cannot infect a Windows com-
of the OS to avoid detection and carry out its attacks. These native services used in a
puter), both can only replicate
fileless virus are called living-off-the-land binaries (LOLBins). For a computer running
when inside the host, both
Microsoft Windows, some of commonly exploited LOLBins are listed in Table 3-2.
may remain dormant for a
period of time, and both types
Table 3-2 Microsoft Windows common LOLBins
of viruses replicate at the
expense of the host.
Name Description
powershell A cross-platform and open source task automation and
configuration management framework
Windows A Microsoft standard for accessing management information noTe 10
Management about devices
Instrumentation Microsoft Windows lolbins
(WMI) are often categorized into
.neT Framework A free, cross-platform, open source developer platform for binaries (programs that end
building different types of applications in .eXe), libraries (.dll), and
Macro A series of instructions that can be grouped together as a scripts (.Vbs). by some esti-
single command to automate a complex set of tasks or a mates 115 Windows lolbins
repeated series of tasks, can be written by using a macro
can be exploited by a fileless
scripting language, such as Visual basic for Applications (VbA),
virus, while unIX/linux sys-
and is stored within the user document (such as in an excel
.xlsx workbook or Word .docx file) tems have 185 lolbins.
Unlike a file-based virus, a fileless virus does not infect a file and wait for that file to be launched. Instead, the mali-
cious code of a fileless virus is loaded directly in the computer’s random access memory (RAM) through the LOLBins
and then executed.
There are several advantages of a fileless virus over a file-based virus:
• Easy to infect. A fileless virus does not require that a specific type of file be stored on the computer’s hard drive for
the virus to infect. Instead, a common delivery method is through malicious webpages that the user visits. These
pages silently send a script to the victim’s web browser, which invokes a scripting language such as JavaScript.
The browser passes instructions to a LOLBin such as PowerShell, which reads and executes the commands.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

72 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
• Extensive control. Several LOLBins have extensive control and authority on a computer. For example, Power-
Shell has full access to the core OS of a Windows computer, so it can undermine existing security features.
PowerShell can also manipulate user accounts and password protection.
• Persistent. A program that is loaded into RAM for execution will terminate once the computer is shut down or
rebooted. However, fileless viruses often write their script into the Windows Registry, which is a database that
stores settings for the Windows OS and application programs. Each time the computer is restarted or on a set
schedule, the script of the fileless virus is again launched.
• Difficult to detect. Files that are infected with a file-based virus can be scanned by an antivirus tool for detec-
tion. However, because a fileless virus loads into RAM, no telltale file can be scanned. Also, by using LOLBins,
there is no evidence of other tools being used. And some LOLBins like PowerShell run in a section of system
memory that cannot be queried or searched, making its activities virtually impossible to detect.
• Difficult to defend against. To fully defend against a fileless virus, it would be necessary to turn off all the poten-
tial LOLBins, which would cripple the OS and cause it to not properly function. Also, these LOLBins are loaded
by default when the OS starts so that any attempt to turn selected LOLBins off would already be too late.
worm
A second type of malware that has as its primary purpose to spread is a worm. A worm is a malicious program that
uses a computer network to replicate. (Worms are sometimes called network viruses.) A worm is designed to enter a
computer through the network and then take advantage of a vulnerability in an application or an OS on the host com-
puter. Once the worm has exploited the vulnerability on one system, it immediately searches for another computer
on the network that has the same vulnerability.
noTe 11
one of the first wide-scale worm infections occurred in 1988. This worm exploited a misconfiguration in a program that
allowed commands emailed to a remote system to be executed on that system. The worm also carried a payload con-
taining a program that attempted to determine user passwords. Almost 6,000 computers, or 10 percent of the devices
connected to the Internet at that time, were affected. The threat actor responsible was later convicted of federal crimes
in connection with this incident.
Early worms were relatively benign and designed simply to spread quickly but not corrupt the systems they
infected. These worms slowed down the network through which they were transmitted by replicating so quickly that
they consumed all network resources. Today’s worms can leave behind a payload on the systems they infect and cause
harm, much like a virus. Actions that worms have performed include deleting files on the computer or allowing the
computer to be remotely controlled by an attacker.
noTe 12
Although viruses and worms are said to be automatically self-replicating, where they replicate is different. A virus self-
replicates on the host computer but does not spread to other computers by itself. A worm self-replicates between com-
puters (from one computer to another).
Bot
Another popular payload of malware is software that allows the infected computer to be placed under the remote
control of an attacker for the purpose of launching attacks. This infected robot computer is known as a bot or zombie.
When hundreds, thousands, or even millions of bot computers are gathered into a logical computer network, they
create a botnet under the control of a bot herder.
noTe 13
due to the multitasking capabilities of modern computers, a computer can act as a bot while carrying out the tasks of its
regular user. users are completely unaware that their computer is being used for malicious activities.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 73
Table 3-3 lists some of the attacks that can be generated through botnets.
Table 3-3 Uses of botnets
Type of attack Description
spamming botnets are widely recognized as the primary source of spam email. A botnet
consisting of thousands of bots enables an attacker to send massive amounts of spam.
spreading malware botnets can be used to spread malware and create new bots and botnets. bots can
download and execute a file sent by the attacker.
Ad fraud Threat actors earn money by generating a high number of “clicks” on advertisements
at targeted websites, using a bot to mimic the mouse clicks of a user.
Mining cryptocurrencies Also called “cryptomining,” this is a process in which transactions for various forms of
cryptocurrency are verified, earning the “miner” a monetary reward. botnets combine
the resources of millions of bots for mining cryptocurrencies.
Infected bot computers receive instructions through a command and control (C&C) structure from the bot herders
regarding which computers to attack and how. There are a variety of ways for this communication to occur, including
the following:
• A bot can receive its instructions by automatically signing in to a bot-herding website where information has
been placed that the bot knows how to interpret as commands.
• Bots can sign in to a third-party website; this has an advantage of the bot herder not needing to have a direct
affiliation with that website.
• Commands can be sent via blogs, specially coded attack commands through posts on Twitter, or notes posted
in Facebook.
• Bot herders are increasingly using a “dead drop” C&C mechanism by setting up a Google Gmail email account
and then creating a draft email message that is never sent but contains commands the bot receives when it
logs in to Gmail and reads the draft. Because the email message is never sent, there is no record of the com-
mands. All Gmail transmissions are protected so that outsiders cannot view them.
snoop
Another category of malware “snoops” or spies on its victims. The two common types of snooping malware are
spyware and keyloggers.
spyware
Spyware is tracking software that is deployed without the consent or control of the user. Spyware can secretly moni-
tor users by collecting information without their approval through the computer’s resources, including programs
already installed on the computer, to collect and distribute personal or sensitive information. Table 3-4 lists different
technologies used by spyware.
Table 3-4 Technologies used by spyware
Technology Description Impact
Automatic downloads and installs software without the user’s could install unauthorized
download software interaction applications
passive tracking Gathers information about user activities without could collect private information
technologies installing any software such as websites a user has visited
system modifying Modifies or changes user configurations, such as changes configurations to settings
software the web browser home page or search page, default that the user did not approve
media player, or lower-level system functions
Tracking software Monitors user behavior or gathers information about could collect personal information
the user, sometimes including personally identifiable that can be shared widely or stolen,
or other sensitive information resulting in fraud or identity theft
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Caution not all spyware is necessarily malicious. For example, spyware monitoring tools can help parents
keep track of the online activities of their children.
keylogger
Another type of spying is done with a keylogger that silently captures and stores each keystroke that a user types on
the computer’s keyboard. The threat actor can then search the captured text for any useful information such as pass-
words, credit card numbers, or personal information. A keylogger can be a software program or a small hardware device.
Software keyloggers are programs installed on the computer that silently capture sensitive information. However,
software keyloggers, which conceal themselves so that the user cannot detect them, go far beyond capturing a user’s
keystrokes. These programs can also capture everything on the user’s screen and silently turn on the computer’s web
camera to record images of the user. A software keylogger is illustrated in Figure 3-5.
noTe 14
An advantage of software keyloggers is that they do not require physical access to the user’s computer because they
can be installed remotely. They can routinely send captured information back to the attacker through the victim’s own
Internet connection.
Figure 3-5 Software keylogger
gofeR
74 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
For computers that are in a public location such as a library or computer lab but are “locked down” so that no soft-
ware can be installed, a hardware keylogger can be used instead. These keyloggers are hardware devices inserted between
the computer keyboard connection and USB port, as shown in Figure 3-6. Because the device resembles an ordinary
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

keyboard plug and the computer keyboard USB port is often on the back of the computer, a hardware keylogger can eas-
ily go undetected. In addition, the device is beyond the reach of the computer’s antimalware scanning software and thus
raises no alarms. A disadvantage of a hardware keylogger is that the threat actor must install and then later return to
physically remove the device in order to access the information it has stored, each time being careful not to be detected.
Hardware
keylogger
Figure 3-6 Hardware keylogger
deceive
Some malware attempts to deceive the user and hide its true intentions. Software in this category includes potentially
unwanted programs (PUPs), Trojans, and remote access Trojans (RATs).
potentially Unwanted program (pUp)
A broad category of software that is often more annoying than malicious is called potentially unwanted programs
(PuPs). A PUP is software that the user does not want on their computer. PUPs often become installed along with other
programs and are the result of the user overlooking the default installation options on software downloads, as seen
in Figure 3-7.
Figure 3-7 Default installation options
noitaroproC
elcarO
:ecruoS
Module 3 ThreaTs and aTTacks on endpoinTs 75
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

76 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
noTe 15 PUPs may include software that is pre-installed on a new computer or smart-
phone and cannot be easily removed (if at all). Other examples of PUPs are adver-
The term pup was created by tising that obstructs content or interferes with web browsing, pop-up windows,
an Internet security company pop-under windows, search engine hijacking, home page hijacking, toolbars with no
because marketing firms value for the user, and settings that redirect to competitors’ websites, alter search
objected to having their prod- results, and replace ads on webpages.
ucts being called “spyware.”
Trojan
According to ancient legend, the Greeks won the Trojan War by hiding soldiers in a
large hollow wooden horse that was presented as a gift to the city of Troy. Once the horse was wheeled into the forti-
fied city, the soldiers crept out of the horse during the night and attacked the unsuspecting defenders.
A computer Trojan is an executable program that masquerades as performing a benign activity but also does
something malicious. For example, a user might download what is advertised as a calendar program, yet in addition to
installing the calendar, it also installs malware that scans the system for credit card numbers and passwords, connects
through the network to a remote system, and then transmits that information to the attacker.
remote access Trojan (raT)
A special type of Trojan is a remote access Trojan (rAT). A RAT has the basic functionality of a Trojan but also gives
the threat agent unauthorized remote access to the victim’s computer by using specially configured communication
protocols. This creates an opening into the victim’s computer, allowing the threat agent unrestricted access. The
attacker can not only monitor what the user is doing but also change computer settings, browse and copy files, and
even use the computer to access other computers connected on the network.
evade
The final category of malware attempts to help malware or attacks evade detection. This includes backdoor, logic
bomb, and rootkit.
Backdoor
A backdoor gives access to a computer, program, or service that circumvents any normal security protections. Back-
doors installed on a computer allow the attacker to return later and bypass security settings.
Creating a legitimate backdoor is a common practice by developers, who may need to access a program or device
on a regular basis, yet do not want to be hindered by continual requests for passwords or other security approvals.
The intent is for the backdoor to be removed once the application is finalized. However, in some instances, backdoors
have been left installed, and attackers have used them to bypass security.
logic Bomb
A logic bomb is computer code that is typically added to a legitimate program but lies dormant and evades detec-
tion until a specific logical event triggers it. Once it is triggered, the program then deletes data or performs other
malicious activities.
Logic bombs are difficult to detect before they are triggered. This is because
noTe 16 logic bombs are often embedded in very large computer programs, some contain-
ing hundreds of thousands of lines of code, and a trusted employee can easily
Many logic bombs have
insert a few lines of computer code into a long program without anyone detecting
been planted by disgruntled
it. In addition, these programs are not routinely scanned for containing malicious
employees. For example,
actions.
a Maryland government
employee tried to destroy the rootkits
contents of more than 4,000
A rootkit is malware that can hide its presence and the presence of other malware
servers by planting a logic
on the computer. It does this by accessing “lower layers” of the operating system or
bomb script that was sched-
even using undocumented functions to make alterations. This enables the rootkit and
uled to activate 90 days after
any accompanying software to become undetectable by the operating system and
he was terminated.
common antimalware scanning software that is designed to seek and find malware.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 77
noTe 17
The risks of rootkits are significantly diminished today due to protections built into operating systems. These protections
include preventing unauthorized kernel drivers from loading, stopping modifications to certain kernel areas used by
rootkits to hide, and preventing rootkits from modifying the bootloader program.
two rights & a wrong
1. It is a common tactic for cryptomalware attackers to not send the decryption key after the ransom has been paid.
2. Fileless viruses take advantage of native services and processes that are part of the operating system (os)
to avoid detection and carry out its attacks, and these native services used in a fileless virus are called
living-off-the-land binaries (LOLBins).
3. A remote access Trojan (rAT) can monitor what the user is doing, change computer settings, browse and
copy files, and use the computer to access other computers connected on the network.
See Appendix B for the answer.
applicaTion aTTacks
✔ CertiFiCation
1.3 Given a scenario, analyze potential indicators associated with application attacks.
Attacks using malware typically add malicious software to an endpoint. Another category of attacks specifically targets
software applications that are already installed and running on the device. These attacks look for vulnerabilities in the
application or manipulate the application in order to compromise it. While on occasion threat actors target applications
running on a user’s endpoint like a personal computer, more often, their sights are set on compromising applications
that can provide many more potential victims than a single computer user. The more common targets of attackers
using application attacks are Internet web servers.
A web server provides services that are implemented as “web applications” through software applications run-
ning on the server. A typical web application infrastructure is shown in Figure 3-8. The client’s web browser makes a
request using the Hypertext Transport Protocol (HTTP) to a web server, which may be connected to one or more web
application servers. These application servers run the specific “web apps,” which in turn are directly connected to
database servers on the internal network. Information from these database servers is retrieved and returned to the
web server so that the information can be sent back to the user’s web browser.
App server Database server
HTTP traffic
Web server App server Database server
Client
App server Database server
Figure 3-8 Web server application infrastructure
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

The multiple elements in a web application infrastructure provide multiple attack points: a single vulnerability
could expose many other users who are accessing the web server. An attack could also compromise backend databases
and app servers, and the connected network infrastructure.
Application attacks include scripting attacks, injection attacks, request forgery attacks, and replay attacks. These
attacks typically target how the applications function. In addition, attacks directly focused on vulnerabilities in the
software applications are common.
scripting
Most web applications create dynamic content based on input from the user. Figure 3-9 illustrates a fictitious web
application that allows friends to share their favorite bookmarks with each other online. Users can enter their name,
a description, and the URL of the bookmark and then receive a personalized “Thank You” screen. In Figure 3-10, the
code that generates the “Thank You” screen is illustrated.
Figure 3-9 Bookmark page that accepts user input
noTe 18 In a cross-site scripting (XSS) attack, a website that accepts user input without
validating it (called sanitizing) and uses that input in a response can be exploited.
The term cross-site scripting In the previous example, the input that the user enters for Name is not verified but
refers to an attack using scripting instead is automatically added to a code segment that becomes part of an automated
that originates on one site (the response. An attacker can take advantage of this in an XSS attack by tricking a valid
web server) to impact another website into feeding a malicious script to another user’s web browser, which will
site (the user’s computer). then execute it.
injection
In addition to cross-site attacks on web server applications, attacks called injections also introduce new input
to exploit a vulnerability. One of the most common injection attacks, called SQl injection, inserts statements
to manipulate a database server. SQL stands for Structured Query language, a language used to view and
manipulate data that is stored in a relational database. SQL injection targets SQL servers by introducing mali-
cious commands into them.
tfosorciM
morf
snoissimrep
htiw
desU
:ecruoS
Figure 3-10 Input used in response
tfosorciM
morf
snoissimrep
htiw
desU
:ecruoS
78 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 79
Consider a webpage that offers a solution for users who have forgotten their password. An online form asks users
to enter their username, which is also their email address that is already on file. The submitted email address is com-
pared to the stored email address, and if they match, a reset URL is emailed to that address.
If the email address entered by the user into the form is stored in the variable $EMAIL, then the underlying SQL
statement to retrieve the stored email address from the database would be similar to this:
SELECT fieldlist FROM table WHERE field = ‘$EMAIL’
The WHERE clause is meant to limit the database query to only display information when the condition is consid-
ered true (that is, when the email address in $EMAIL matches an address in the database).
An attacker using an SQL injection attack would begin by first entering a fictitious email address on this
webpage that included a single quotation mark as part of the data, such as braden.thomas@fakemail.com’. If
the message E-mail Address Unknown is displayed, it indicates that user input is being properly filtered and an
SQL attack cannot be rendered on the site. However, if the error message Server Failure is displayed, it means
that the user input is not being filtered and all user input is sent directly to the database. This is because the
Server Failure message is due to a syntax error created by the additional single quotation mark in the fictitious
email address.
Armed with the knowledge that input is sent unfiltered to the database, the attacker knows that anything he enters
as a username in the form would be sent to and then processed by the SQL database. Now, instead of entering a user
name, the attacker would enter this command, which would let him view all the email addresses in the database: what-
ever’ or ‘a’5’a. This command is stored in the variable $EMAIL. The expanded SQL statement would read
SELECT fieldlist FROM table WHERE field = ‘whatever’ or ‘a’=‘a’
These values are the following:
• ‘whatever’. This can be anything meaningless.
• or. The SQL or means that as long as either of the conditions are true, the entire statement is true and will be
executed.
• ‘a’5‘a’. This is a statement that will always be true.
Because ‘a’5‘a’ is always true, the WHERE clause is also true. It is not limited as it was when searching for
a single email address before it would become true. The result can be that all user email addresses will then be
displayed.
By entering crafted SQL statements as user input, information from the database can be extracted or the existing
data can be manipulated. SQL injection statements that can be entered and stored in $EMAIL, and their pending results
are shown in Table 3-5.
Table 3-5 SQL injection statements
SQL injection statement Result
‘whatever’ AND email IS NULL; determine the names of different fields in the database
‘whatever’ AND 15 (SELECT COUNT(*) FROM tabname); discover the name of the table
‘whatever’ OR full name LIKE ‘%Mia%’; Find specific users
‘whatever’; DROP TABLE members; erase the database table
‘whatever’; UPDATE members SET email 5 ‘ attacker-email@ Mail password to attacker’s email account
evil.net’ WHERE email 5 ‘ Mia@good.com’;
In addition to using SQL to view and manipulate data that is stored in a relational database, other types of data-
bases not using SQL (called NoSQL databases) are also used. One popular type of NoSQL database manipulates data
using the eXtensible Markup language (XMl). Like the markup language Hyper Text Markup Language (HTML) used
for webpages, XML is not a processing language but instead is designed to store information. A NoSQL database that
uses XML for data manipulation is also subject to an injection attack like SQL injection if the input is not sanitized.
This is called an XMl injection.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

80 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
request Forgery
Although some attacks have confusing names, that is not the case with the category of request forgery. As its name sug-
gests, it is a request that has been fabricated. There are two types of request forgeries. These are a cross-site request
forgery (CSRF) and a server-site request forgery (SSRF).
cross-site request Forgery (csrF)
A cross-site request forgery (CSrF) takes advantage of an authentication “token” that a website sends to a user’s web
browser. If a user is currently authenticated on a website and is then tricked into loading another webpage, the new
page inherits the identity and privileges of the victim, who may then perform an undesired function on the attacker’s
behalf. Figure 3-11 illustrates a cross-site request forgery. Because a CSRF takes place on the client site, it is sometimes
called a client-side request forgery.
3. Victim unknowingly clicks email hyperlink
2. Attacker sends email
to victim who is logged in
to Bank A’s website 4. Request is sent to Bank A
with victim’s verified credentials
5. Bank A validates request
with victim’s credentials and
1. Attacker forges a fund sends funds to attacker
transfer request from Bank A
and embeds it into email
hyperlink
Figure 3-11 Cross-site request forgery
noTe 19 server-side request Forgery (ssrF)
A server-side request forgery (SSrF) takes advantage of a trusting relationship between
In other words, in a csrF
web servers (as opposed to a CSRF, which manipulates the trust from a user’s browser
attack a request to a website
to a server). SSRF attacks exploit how a web server processes external information
is not from the authentic user
received from another server. Some web applications are designed to read informa-
but is a forgery that involves
tion from or write information to a specific URL. If an attacker can modify that target
crossing sites.
URL, they can potentially extract sensitive information from the application or inject
untrusted input into it. Table 3-6 outlines the differences between a CSRF and a SSRF.
Table 3-6 CSRF and SSRF differences
Attack name Attack target Purpose of attack
csrF user Force target to take action for attacker while pretending to be
authorized user
ssrF Web server Gain access to sensitive data or inject harmful data
replay
Whereas some attacks try to capture data sent between two users, a replay attack copies data and then uses it for an
attack. Replay attacks are commonly used against digital identities—after intercepting and copying data, the threat
actor retransmits selected and edited portions of the copied communications later to impersonate the legitimate user.
Many digital identity replay attacks are between a user and an authentication server.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 81
attacks on software
Other attacks are directly focused on vulnerabilities in the software applications. These include exploiting memory
vulnerabilities, improper exception and error handling, and external software components.
Memory Vulnerabilities
Several attacks are directed at vulnerabilities associated with how a program uses RAM. These are often the result of
poor techniques (or laziness) by the software developer.
Some memory-related attacks are called resource exhaustion attacks because they “deplete” parts of memory and
thus interfere with the normal operation of the program in RAM. This may allow the threat actor access to the underlying
OS in a way that it could be exploited by bypass security settings. An example is a memory leak. An application nor-
mally dynamically allocates memory, but due to a programming error, it may not free that memory when finished using
it. An attacker can then take advantage of the unexpected program behavior resulting from a low memory condition.
Other memory-related attacks attempt to manipulate memory contents. Again, these are made possible by poor
programming practices. These types of attacks include buffer overflow attacks and integer overflow attacks.
Buffer overflow Consider a teacher working in his office who manually grades a lengthy written examination by
marking incorrect answers with a red pen. Because he is frequently interrupted in his grading by students, the teacher
places a ruler on the test question he is currently grading to indicate his “return point,” or the point at which he should
resume the grading. Suppose that two devious students enter his office as he is grading examinations. While one stu-
dent distracts him, the second student silently slides the ruler down from question 4 to question 20. When the teacher
returns to grading, he will resume at the wrong "return point” and not look at the answers for questions 4 through 19.
This scenario is similar to how a buffer overflow attacker attempts to compromise a computer. A storage buffer
on a computer typically contains the memory location of the software program that was being executed when another
function interrupted the process; that is, the storage buffer contains the “return address” where the computer’s proces-
sor should resume once the new process has finished. Attackers can substitute their own “return address” in order to
point to a different area in the computer’s memory that contains their malware code.
A buffer overflow attack occurs when a process attempts to store data in RAM beyond the boundaries of a
fixed-length storage buffer. This extra data overflows into the adjacent memory locations (a buffer overflow). Because
the storage buffer typically contains the “return address” memory location of the software program being executed
when another function interrupted the process, an attacker can overflow the buffer with a new address pointing to
the attacker’s malware code. A buffer overflow attack is shown in Figure 3-12.
Normal process
Program instructions Buffer storing integer data Buffer storing character data Return address pointer
Program jumps to address of next instruction
Buffer overflow
Program instructions Buffer storing integer data Buffer storing character data Return address pointer
Malware Fill and overflow buffer New
pointer
Program jumps to
attacker malware
Figure 3-12 Buffer overflow attack
noTe 20
The “return address” is not the only element that can be altered in a buffer overflow attack, but it is one of the most
commonly altered elements.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

82 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
integer overflow Consider a digital clock that can display the hours only as 1 to 12. What happens when the time
moves past 12:59? The clock then “wraps around” to the lowest hour value of 1 again.
On a computer, an integer overflow is the condition that occurs when the result of an arithmetic operation—such
as addition or multiplication—exceeds the maximum size of the integer type used to store it. When this integer over-
flow occurs, the interpreted value then wraps around from the maximum value to the minimum value. For example, an
eight-bit signed integer has a maximum value of 127 and a minimum value of 2128. If the value 127 is stored in a vari-
able and 1 is added to it, the sum exceeds the maximum value for this integer type and wraps around to become 2128.
In an integer overflow attack, an attacker changes the value of a variable to something outside the range that the
programmer had intended by using an integer overflow. This type of attack could be used in the following situations:
• An attacker could use an integer overflow attack to create a buffer overflow. If an integer overflow could be
introduced during the calculations for the length of a buffer when a copy is occurring, it could result in a buf-
fer that is too small to hold the data. An attacker could then use this to create a
buffer overflow attack.
noTe 21 • A program that calculates the total cost of items purchased would use the num-
ber of units sold times the cost per unit. If an integer overflow were introduced
An extreme example of an
when tallying the number of items sold, it could result in a negative value and a
integer overflow attack would
resulting negative total cost, indicating that a refund is due the customer.
be withdrawing $1 from an
• A large positive value in a bank transfer could be wrapped around by an integer
account that has a balance of
overflow attack to become a negative value, which could then reverse the flow of
0, which could cause a new
money: instead of adding this amount to the victim’s account, it could withdraw
balance of $4,294,967,295!
that amount and later transfer it to the attacker’s account.
improper exception handling
Other attacks on software, like memory vulnerabilities, are the result of poor coding on the part of software develop-
ers. This is commonly the case when the program does not properly check for exceptions that may occur when the
program is running.
Software that allows the user to enter data but has improper input handling features does not filter or validate user
input to prevent a malicious action. For example, a webpage on a web server with improper input handling that asks for
the user’s email address could allow an attacker to instead enter a direct command that the server would then execute.
Other software may not properly trap an error condition and thus provides an attacker with underlying access to
the system. This is known as incorrect error handling. Suppose an attacker enters a string of characters that is much
longer than expected. Because the software has not been designed for this event, the program could crash or suddenly
halt its execution and then display an underlying OS prompt, giving an attacker access to the computer.
Another improper exception handling situation is a NULL pointer/object dereference. (A dereference obtains
from a pointer the address of a data item held in another location.) When an application dereferences a pointer that it
expects to be valid but instead has a value of NULL, it typically will cause a program to crash or exit. A NULL pointer/
object dereference can occur through a number of flaws, including simple programming omissions.
A NULL pointer/object dereference can also be the result of a race condition. A race condition in software occurs
when two concurrent threads of execution access a shared resource simultaneously, resulting in unintended conse-
quences. For example, in a program with two threads that have access to the same location in memory, Thread #1 stores
the value A in that memory location. But since Thread #2 is also executing, it may overwrite the same memory location
with the value Z. When Thread #1 retrieves the value stored, it is given Thread #2’s Z instead of its own A. The software
checks the state of a resource before using that resource, but the resource’s state can change between the check and
the use in a way that invalidates the results of the check. This is called a time of check/time of use race condition.
This condition is often security-relevant: a threat actor who can influence the state of the resource between check and
use can negatively impact a number of shared resources such as files, memory, or variables in multithreaded programs.
Caution Time of check/time of use often appears as time of check to time of use (TocTTou). A typo of
TocTTou is ToccTou and has been used in some influential documents, so the typo is repeated
fairly frequently.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 83
attacks on external software components
In addition to attacking the software directly, threat actors also target external software components. These include
the following:
• Application program interface (API). An application program interface (API) is a link provided by an OS, web
browser, or other platform that allows a developer access to resources at a high level. An example of an API
is when a user visits a website and the message “This site wants to know your
location” appears. The website is attempting to the use geolocation API avail-
able in the web browser. APIs relieve the developer from the need to write code noTe 22
for specific hardware and software. Because APIs provide direct access to data
ApI vulnerabilities are par-
and an entry point to an application’s functions, they are attractive targets
ticularly attractive because
for attackers looking for vulnerabilities in the API in an application program
they can have a broad impact
interface (API) attack.
and may take a long time to
• Device driver. A device driver is software that controls and operates an external
discover. In 2018, Facebook
hardware device that is connected to a computer. Device drivers are specific
found a vulnerability in its ApI
to both the OS and the hardware device. Threat actors may attempt to alter
code that made it possible
a device driver for use in an attack (called device driver manipulation). An
for attackers to steal access
attacker may use shimming, or transparently adding a small coding library
tokens and take over the
that intercepts calls made by the device and changes the parameters passed
accounts of 30 million users.
between the device and the device driver. This refactoring (changing the
It took Facebook 14 months
design of existing code) can be difficult to detect yet serves as a real threat.
before they discovered the ApI
• Dynamic-link library (DLL). A dynamic-link library (DLL) is a repository of both
vulnerability. It is predicted
code and data that can be used by more than one program at the same time.
that by 2022, ApI abuses will
For example, in the Windows operating systems, the Comdlg32.DLL performs
become the most common
common dialog box related functions. Attackers use a technique called
type of web application attack
dll injection for inserting code into a running process through a DLL to cause
resulting in a data breach.10
a program to function in a different way than intended.
two rights & a wrong
1. In an Xss attack, a website that accepts user input without sanitizing it and uses that input in a response
can be exploited.
2. An ssrF takes advantage of a trusting relationship between a web browser and web servers.
3. A time of check/time of use is a vulnerability that causes a race condition.
See Appendix B for the answer.
adVersarial arTiFicial inTelligence aTTacks
✔ CertiFiCation
1.2 Given a scenario, analyze potential indicators to determine the type of attack.
Artificial intelligence is being used worldwide in a wide variety of applications, ranging from the mundane to the very
sophisticated. Cybersecurity is likewise using these innovative technologies to enhance the detection of malicious
behavior and advanced threats. However, there are significant vulnerabilities and risks with using these new tools.
Understanding them includes knowing what the tools are and what they can do, how these tools are used in cyber-
security, and their potential risks.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

84 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
what are artificial intelligence (ai) and Machine learning (Ml)?
Consider the following scenario. Junaid’s team leader asks him to fly to another branch of the company tomorrow
morning to assist with its new direct marketing campaign. He agrees and books online an airplane reservation
for early the next morning. As Junaid awakens, his smartphone buzzes. His phone alerts him about the weather
at his destination and makes recommendations about the clothes to pack for his trip. It also tells him what time
to leave for the airport based on local traffic and the length of time needed to
pass through airport security. When Junaid pulls his car out of his driveway, he
noTe 23
receives another message on his phone explaining that an accident is slowing traf-
The original goal of AI was fic on the main road to the airport and directing him to take an alternate route.
to make computers more After his flight, Junaid arrives at the hotel and suddenly remembers that he vol-
useful and more capable of unteered to help plan a birthday party for his niece on Saturday. Using the smart
independent reasoning. Most speaker in his hotel room, he logs in to his account and tells the voice assistant
historians trace the birth of what he needs. After a few minutes, he has arranged for the party invitations to
AI to a dartmouth research be sent to select individuals in his contact list, ordered a birthday present based
project in 1956 that explored on what is popular with other children the same age as his niece, and has set a
problem solving and symbolic reminder for him to pick up the cake after he arrives back home. The next morn-
methods. In the 1960s, the ing, Junaid arrives at the remote office to help with a direct marketing campaign.
u.s. dod became interested He begins by demonstrating to a college intern how to use the company’s new
in this research and worked smart assistant to segment their customers into groups to receive targeted mes-
on training computers to imi- saging in order to increase the response rates.
tate human reasoning. some Just a few years ago, this scenario would have been nothing more than science
projects that came from the fiction. Today, however, it is commonplace and occurs multiple times every day in
dod were a street-mapping our work and personal lives. This is based on tools that provide genuine human-to-
project in the 1970s and intel- machine interaction.
ligent personal assistants in The foundation behind this interaction is called artificial intelligence (AI).
the early 2000s. Although definitions of AI vary, at its core, AI may be defined as technology that imi-
tates human abilities. Although the practical use of AI has only appeared recently, it
has a long history dating back to the first large-scale computers.
noTe 24
A recognized subset of AI is machine learning (ML). Humans learn by direct com-
mands of someone older and wiser, but this requires the other person to always be
The relationship between AI
present. Humans also learn through experiences (such as touching a hot stove results
and Ml is AI applies Ml to
in a painful burn). ML is defined as “teaching” a technology device to “learn” by itself
solve problems without being
without the continual instructions of a computer programmer. ML also involves learn-
explicitly programmed what
ing through repeated experience: that is, if something attempted does not work, then
to do.
it determines how it could be changed to make it work.
Uses in cybersecurity
Cybersecurity AI allows organizations to detect, predict, and respond to cyberthreats in real time using ML. AI is
already being used broadly in cybersecurity defenses. Virtually all email systems use some type of AI to block phish-
ing attacks by examining obvious clues (such as the URL of the link that the victim is being tempted to click) but also
subtle clues (such as the tense and voice of words in the email). AI using ML can analyze these to continually learn to
distinguish and block phishing emails while allowing genuine emails to reach the user’s inbox.
The prime advantages of using AI to combat threats are continual learning and greater speed in response. By rely-
ing on data from previous similar attacks, AI can predict and prevent future attacks. ML learning algorithms can quickly
apply complex pattern recognition techniques to spot and thwart attacks much faster than humans can.
The use of AI in cybersecurity is widespread. About one in five organizations used cybersecurity AI before 2019,
increasing to two out of three organizations planning to deploy it by the end of 2020. Telecommunications provid-
ers use cybersecurity AI more than any other sector: 80 percent of telecom companies said that they would not be
able to respond to cyberattacks without using AI.11 Figure 3-13 illustrates where AI cybersecurity is used in specific
areas within an enterprise.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

75%
71% 68%
65% 64%
59%
53%
Network Data Endpoint Identity Application Cloud IoT
Security Security Security and Access Security Security Security
Security
Figure 3-13 How AI cybersecurity is used
Caution Another concern is that threat actors themselves will turn to using AI for attacks in order to
circumvent defenses.
inimegpaC
:ecruoS
Module 3 ThreaTs and aTTacks on endpoinTs 85
risks in Using ai and Ml in cybersecurity
Although the use of AI in cybersecurity is growing, there are risks associated with using AI and ML in cybersecurity. This
is called adversarial artificial intelligence. The first risk is the security of the Ml algorithms. Just as all hardware
and software is subject to being infiltrated by threat actors, AI-powered cybersecurity applications and their devices
likewise have vulnerabilities. These could be attacked and compromised, allowing threat actors to alter algorithms to
ignore attacks, much like a rootkit can instruct an OS to ignore malicious actions.
Another risk is tainted training data for machine learning. Attackers can attempt to alter the training data that
is used by ML in order to produce false negatives to cloak themselves.
two rights & a wrong
1. Artificial intelligence (AI) may be defined as technology that imitates human abilities.
2. AI is already being used broadly in cybersecurity defenses.
3. A recognized subset of Ml is AI.
See Appendix B for the answer.
VM Lab you’re now ready to complete the live, virtual machine labs for this module. The labs can be
found each module in the MindTap.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

86 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
sUMMary
• The word “endpoint” is commonly used when referring to network-connected hardware devices. Devices that are
connected to a network today include traditional desktop computers, mobile smartphones, tablets, wearable fit-
ness trackers, and even personal drones. The word endpoint reflects the risks that have increased with using these
devices. Instead of protecting devices located inside a network security perimeter, today each endpoint is a target
for attackers to attempt to steal or manipulate their data. Every endpoint is a potential entry point for attackers.
• Malware (malicious software) is software that enters a computer system without the user’s knowledge or
consent and then performs an unwanted and harmful action. There has been no standard established for the
classification of the different types of malware so that like malware can be grouped together for study. One
attempt at classifying the diverse types of malware can be to examine the primary action that the malware
performs and then group those together with similar actions.
• Some types of malware attempt to take away the freedom of users to do whatever they want on their computer.
These types of malware “imprison” the user. One of the fastest-growing types of malware is ransomware, which
takes away users’ freedom from using their computer until the ransom is transacted. Early ransomware pre-
tended to be from a reputable third-party, giving a “valid” reason for blocking the user’s computer. As ransomware
became more widespread, the threat agents dropped the pretense that the ransomware was from a reputable
third party. Instead, they simply blocked the user’s computer and demanded a fee for its release. In recent years,
a more malicious form of ransomware has arisen. Instead of just blocking the user from accessing the computer,
it encrypts all the files on the device so that none of them can be opened. This is called cryptomalware.
• Another category of malware infects a computer to then launch attacks on other computers. A file-based virus
is remarkably similar to a biological virus. It is malicious computer code that is attached to a file. Like its bio-
logical counterpart, a file-based virus reproduces itself on the same computer. Early viruses were relatively
straightforward in how they infected files. Later file-based viruses went to greater lengths to avoid detection;
this type of virus is called an armored file-based virus. A fileless virus does not attach itself to a file but takes
advantage of native services and processes that are part of the OS to avoid detection and carry out its attacks.
These native services used in a fileless virus are called living-off-the-land binaries (LOLBins). There are several
advantages of a fileless virus over a file-based virus. These include ease of infection, extensive control, persis-
tence, difficulty in detection, and difficulty in defense. A worm is a malicious program that uses a computer
network to replicate. It is designed to enter a computer through the network and then take advantage of a
vulnerability in an application or an OS on the host computer. An infected computer that is under the remote
control of an attacker for the purpose of launching attacks is called a bot or zombie. When large numbers of
bot computers are gathered into a logical computer network, they create a botnet. Infected bot computers
receive instructions through a command and control (C&C) structure.
• Another category of malware “snoops” or spies on its victims. Spyware is tracking software that is deployed
without the consent or control of the user. Spyware typically secretly monitors users by collecting information
without their approval using the computer’s resources, including programs already installed on the computer,
to collect and distribute personal or sensitive information. A keylogger silently captures and stores each key-
stroke that a user types on the computer’s keyboard so that the attacker can later search the captured text
for any useful information. A keylogger can be a software program or a small hardware device.
• Some malware attempts to deceive the user and hide its true intentions. A broad category of software that
is often more annoying than malicious is called potentially unwanted programs (PUPs), or software that the
user does not want on their computer. PUPs often become installed along with other programs when the user
overlooks the default installation options on software downloads. A computer Trojan is an executable program
that masquerades as performing a benign activity but also does something malicious. A special type of Trojan
is a remote access Trojan (RAT). A RAT has the basic functionality of a Trojan but also gives the threat agent
unauthorized remote access to the victim’s computer by using specially configured communication protocols.
• Some malware attempts to evade detection. A backdoor gives access to a computer, program, or service that
circumvents any normal security protections. When installed on a computer, a backdoor allows the attacker to
return later and bypass security settings. A logic bomb is computer code that is typically added to a legitimate
program but lies dormant and evades detection until a specific logical event triggers it. Once it is triggered, the
program then deletes data or performs other malicious activities. Logic bombs are difficult to detect before
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 87
they are triggered because they are often embedded in very large computer programs. A rootkit is malware
that can hide its presence and the presence of other malware on the computer. It does this by accessing “lower
layers” of the operating system or even using undocumented functions to make alterations.
• Another category of attacks specifically targets software applications that are already installed and running on
the device. These attacks look for vulnerabilities in the application or manipulate the application in order to
compromise it. In a cross-site scripting (XSS) attack, a website that accepts user input without validating (sani-
tizing) it and uses that input in a response can be exploited. Another type of attack called injections introduces
new input to exploit a vulnerability. One of the most common injection attacks, called SQL injection, inserts
statements to manipulate a database server. By entering crafted SQL statements as user input, information
from the database can be extracted or the existing data can be manipulated. In addition to using SQL, other
types of databases are used, such as those containing the eXtensible Markup Language (XML), which can also
be used for data manipulation similar to an SQL injection. This is called an XML injection.
• A cross-site request forgery (CSRF) takes advantage of an authentication “token” that a website sends to a
user’s web browser. If a user is currently authenticated on a website and is then tricked into loading another
webpage, the new page inherits the identity and privileges of the victim, who may then perform an undesired
function on the attacker’s behalf. A server-side request forgery (SSRF) takes advantage of a trusting relation-
ship between web servers. SSRF attacks exploit how a web server processes external information received
from another server. A replay attack copies data and then uses it for an attack.
• Several attacks are directed at vulnerabilities associated with how a program uses RAM. Some of these mem-
ory-related attacks are called resource exhaustion attacks because they “deplete” parts of memory and thus
interfere with the normal operation of the program in RAM. This may allow the threat actor access to the
underlying OS in a way that it could be exploited by bypassing security settings. A memory leak occurs when
an application, instead of normally dynamically allocating memory, does not free that memory when fin-
ished using it. An attacker can then take advantage of the unexpected program behavior resulting from a low
memory condition. A buffer overflow attack occurs when a process attempts to store data in RAM beyond the
boundaries of a fixed-length storage buffer, and this extra data overflows into the adjacent memory locations.
An attacker can overflow the buffer with a new address pointing to the attacker’s malware code. An integer
overflow attack occurs when an attacker changes the value of a variable to something outside the range that
the programmer had intended by using an integer overflow.
• Software that allows the user to enter data but has improper input handling features does not filter or validate
user input to prevent a malicious action. Other software may not properly trap an error condition and thus
provides an attacker with underlying access to the system. This is known as incorrect error handling. When
an application dereferences a pointer that it expects to be valid but instead has a value of NULL, it typically
will cause a program to crash or exit. A NULL pointer/object dereference can occur through a number of flaws,
including simple programming omissions. It can also be the result of a race condition, in which two concurrent
threads of execution access a shared resource simultaneously.
• In an application program interface (API) attack, a threat actor looks for vulnerabilities in the API, a link provided
by an OS, web browser, or other platform that allows a developer access to resources at a high level. A device
driver is software that controls and operates an external hardware device that is connected to a computer and
is specific to both the OS and the hardware device. Threat actors may attempt to alter a device driver for use in
an attack (called device driver manipulation). A dynamic link library (DLL) is a repository of both code and data
that can be used by more than one program at the same time. Attackers use a technique called DLL injection for
inserting code into a running process through a DLL to cause a program to function in a way other than intended.
• Artificial intelligence (AI) is technology that imitates human abilities. Although the practical use of AI has only
appeared recently, it has a long history dating back to the first large-scale computers. A recognized subset of AI is
machine learning (ML). ML is defined as “teaching” a technology device to “learn” by itself without the continual
instructions of a computer programmer and also to learn through repeated experience. Cybersecurity AI allows orga-
nizations to detect, predict, and respond to cyberthreats in real time using ML. There are risks associated with using
AI and ML in cybersecurity called adversarial artificial intelligence. One risk is the security of the ML algorithms: just
as all hardware and software is subject to being infiltrated by threat actors, AI-powered cybersecurity applications
and their devices likewise have vulnerabilities. Another risk is tainted training data for machine learning. Attackers
can attempt to alter the training data that is used by ML in order to produce false negatives to cloak themselves.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

88 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
key Terms
adversarial artificial intelligence fileless virus replay
application program interface (API) improper input handling resource exhaustion attacks
attack injections rootkit
backdoor integer overflow attack security of the ML algorithms
bot keylogger server-side request forgery (SSRF)
buffer overflow attack logic bomb shimming
client-side request forgery malware spyware
command and control (C&C) memory leak SQL injection
cross-site request forgery (CSRF) pointer/object dereference Structured Query Language
cross-site scripting (XSS) potentially unwanted programs tainted training data for machine
cryptomalware (PUPs) learning
device driver manipulation race condition time of check/time of use
DLL injection ransomware Trojan
error handling refactoring worm
eXtensible Markup Language (XML) remote access Trojan XML injection
review Questions
1. What word is the currently accepted term to refer b. Cryptomalware can encrypt all files on any network
to network-connected hardware devices? that is connected to the employee’s computer.
a. Host c. The organization may be forced to pay up to $500
b. Endpoint for the ransom.
c. Device d. The employee would have to wait at least an hour
d. Client before her computer could be restored.
2. Which of the following is NOT a characteristic of 5. Which type of malware relies on LOLBins?
malware? a. PUP
a. Deceive b. File-based virus
b. Launch c. Fileless virus
c. Imprison d. Bot
d. Diffusion 6. Which of the following is known as a network virus?
3. Gabriel’s sister called him about a message a. TAR
that suddenly appeared on her screen that says b. Worm
her software license has expired and she must c. Remote exploitation virus (REV)
immediately pay $500 to have it renewed before d. C&C
control of the computer will be returned to her. 7. Josh is researching the different types of attacks
What type of malware has infected her computer? that can be generated through a botnet. Which of
a. Persistent lockware the following would NOT be something distributed
b. Blocking ransomware by a botnet?
c. Cryptomalware a. LOLBins
d. Impede-ware b. Spam
c. Malware
4. Marius’s team leader has just texted him that
d. Ad fraud
an employee, who violated company policy by
bringing in a file on her USB flash drive, has just 8. Which of the following is NOT a means by which a
reported that her computer is suddenly locked up bot communicates with a C&C device?
with cryptomalware. Why would Marius consider a. Signing in to a website the bot herder operates
this a dangerous situation? b. Signing in to a third-party website
a. It sets a precedent by encouraging other employees c. Email
to violate company policy. d. Command sent through Twitter posts
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 89
9. Randall’s roommate is complaining to him about all c. EXMAL
of the software that came pre-installed on his new d. SCSI
computer. He doesn’t want the software because it
15. Which type of memory vulnerability attack
slows down the computer. What type of software is this?
manipulates the “return address” of the memory
a. Spyware
location of a software program?
b. BOT
a. Shim overflow attack
c. PUP
b. Factor overflow attack
d. Keylogger
c. Integer overflow attack
10. What is the difference between a Trojan and a RAT? d. Buffer overflow attack
a. There is no difference.
16. What race condition can result in a NULL pointer/
b. A RAT gives the attacker unauthorized remote
object dereference?
access to the victim’s computer.
a. Conflict race condition
c. A Trojan can carry malware while a RAT cannot.
b. Value-based race condition
d. A RAT can infect only a smartphone and not a
c. Thread race condition
computer.
d. Time of check/time of use race condition
11. Which of these would NOT be considered the result
17. Which of the following attacks targets the external
of a logic bomb?
software component that is a repository of both
a. Send an email to Rowan’s inbox each Monday morning
code and data?
with the agenda of that week’s department meeting.
a. Application program interface (API) attack
b. If the company’s stock price drops below $50,
b. Device driver manipulation attack
then credit Oscar’s retirement account with one
c. Dynamic-link library (DLL) injection attack
additional year of retirement credit.
d. OS REG attack
c. Erase the hard drives of all the servers 90 days after
Alfredo’s name is removed from the list of current
18. What term refers to changing the design of existing
employees.
code?
d. Delete all human resource records regarding
a. Library manipulation
Augustine one month after he leaves the company.
b. Shimming
12. Which of the following attacks is based on a c. Refactoring
website accepting user input without sanitizing it? d. Design driver manipulation
a. RSS
19. Which of the following is technology that imitates
b. XSS
human abilities?
c. SQLS
a. AI
d. SSXRS
b. ML
13. Which of the following attacks is based on c. RC
the principle that when a user is currently d. XLS
authenticated on a website and then loads another
20. Which statement regarding a keylogger is
webpage, the new page inherits the identity and
NOT true?
privileges of the first website?
a. Software keyloggers can be designed to send
a. SSFR
captured information automatically back to the
b. DLLS
attacker through the Internet.
c. CSRF
b. Hardware keyloggers are installed between the
d. DRCR
keyboard connector and computer keyboard
14. Which of the following manipulates the trusting USB port.
relationship between web servers? c. Software keyloggers are generally easy to detect.
a. SSRF d. Keyloggers can be used to capture passwords,
b. CSRF credit card numbers, or personal information.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

90 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
hands-on Projects
project 3-1: analyze File and Url for File-Based Viruses Using VirusTotal—part 1
Time required: 25 minutes
objective: Given a scenario, analyze potential indicators to determine the type of attack.
description: VirusTotal is a free online service that analyzes files and urls to identify potential malware. VirusTotal
combines 70 antivirus scanners and url/domain blacklisting services along with other tools to identify malware.
A wide range of files can be submitted to VirusTotal for examination, such as user data files and documents,
executable programs, pdFs, and images. one of the uses of VirusTotal is to provide a “second opinion” on a file or
url that may have been flagged as suspicious by other scanning software. In this project, you use VirusTotal to scan
a file and a url.
1. First view several viruses from 20 years ago and observe their benign but annoying impact. open your web
browser and enter the url archive.org/details/malwaremuseum&tab=collection (if you are no longer able to
access the site through the web address, use a search engine to search for “Malware Museum”).
2. All of the viruses have been rendered ineffective and will not harm a computer. click several of the viruses and
notice what they do.
3. When finished, close your web browser.
4. use Microsoft Word to create a document that contains the preceding paragraph description about VirusTotal.
save the document as VirusTotal.docx.
5. exit Word.
6. open your web browser and enter the url www.virustotal.com (if you are no longer able to access the site
through the web address, use a search engine to search for “Virus Total”).
7. If necessary, click the File tab.
8. click Choose File.
9. navigate to the location of VirusTotal.docx and click open.
10. click Confirm upload.
11. Wait until the upload and analysis are completed.
12. scroll through the list of antivirus (AV) vendors that have been polled regarding this file. A green checkmark
means no malware was detected.
13. click the deTAIlS tab and read through the analysis.
14. use your browser’s back button to return to the VirusTotal home page.
15. now you will analyze a website. click url.
16. enter the url of your school, place of employment, or another site with which you are familiar.
17. Wait until the analysis is completed.
18. click the deTAIlS tab and read through the analysis.
19. click scroll through the list of vendor analysis. do any of these sites indicate unrated site or Malware site?
20. how could VirusTotal be useful to users? how could it be useful to security researchers? could it also be used
by attackers to test their own malware before distributing it to ensure that it does not trigger an AV alert? What
should be the protections against this?
21. close all windows.
project 3-2: analyze Virus File Using VirusTotal—part 2
Time required: 20 minutes
objective: Given a scenario, analyze potential indicators to determine the type of attack.
description: What happens when VirusTotal detects a file-based virus? In this project, you will download a file that
has a “signature” of a file-based virus into a sandbox in order to upload it to VirusTotal.
noTe 25
none of the actions in this project will harm the underlying computer.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 91
1. open your web browser.
2. enter the url www.eicar.org/?page_id=3950.
3. scroll down to download area using the standard protocol http.
4. click eicar.com to start the download.
5. your antimalware software on your personal computer should immediately flag this file as malicious and not
allow you to download it. because it cannot (and should not) be downloaded on your regular computer, you will
instead want to use the Windows sandbox or VMware sandbox you created in Module 1.
noTe 26
refer to project 1-3 and project 1-4 of Module 1 for creating these sandboxes.
6. If you are using the Windows sandbox, click Start, scroll down to Windows sandbox, and then click windows
Sandbox.
7. First you will turn off the security protections in Windows sandbox. click Start and then windows Security.
8. click the three horizontal lines at the left of the screen to display the menu options.
9. click App & browser control.
10. For each of the categories, click the off button to turn off security. remember this will only impact the security
within the Windows sandbox and will have no impact on the underlying computer.
11. open Internet explorer in the Windows sandbox.
noTe 27
be sure to use the web browser in the Windows sandbox and not the web browser in the underlying computer.
12. enter the url www.eicar.org/?page_id=3950.
13. scroll down to download area using the standard protocol http.
14. click eicar.com to start the download.
15. The antimalware software within Windows sandbox will now allow the file to be downloaded into the sandbox.
16. open another tab on the Internet explorer web browser in the Windows sandbox, and enter the url www.virustotal.com
(if you are no longer able to access the site through the web address, use a search engine to search for “Virus Total”).
17. If necessary, click the File tab.
18. click Choose File.
19. navigate to the location of eicar.com and click open.
20. click Confirm upload.
21. Wait until the upload and analysis are completed.
22. scroll through the list of AV vendors that have been polled regarding this file. A green checkmark means no
malware was detected.
23. click the deTAIlS tab and read through the analysis.
24. close the Windows sandbox. This will delete the eicar.com file and reset the security settings to normal.
project 3-3: explore ransomware sites
Time required: 15 minutes
objective: Given a scenario, analyze potential indicators to determine the type of attack.
description: A variety of sites provide information about ransomware along with tools for counteracting some types
of infection. In this project, you explore different ransomware sites.
1. open your web browser and enter the url www.nomoreransom.org (if you are not able to access this site
open a search engine and search for “Nomoreransom.org”).
2. click the No button.
3. read through the prevention Advice. do you think it is helpful?
4. click Crypto Sheriff. how could this be useful to a user who has suffered a ransomware infection?
5. click ransomware: Q&A. read through the information. Which statements would you agree with? Which
statements would you disagree with?
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

92 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
6. click decryption Tools. This contains a list of different tools that may help restore a computer that has been
infected by a specific type of ransomware.
7. click one of the tools and then click download to download. note that these tools change frequently based on
the latest types of ransomware that is circulating.
8. run the program to understand how these decryption tools function. note that you will not be able to complete
the process because there are no encrypted files on the computer. close the program.
9. now visit another site that provides ransomware information and tools. open your web browser and enter the
url id-ransomware.malwarehunterteam.com.
10. What features does this site provide?
11. how could these sites be useful?
12. close all windows.
project 3-4: Use a software keylogger
Caution The purpose of this activity is to provide information regarding how these programs function
in order that adequate defenses can be designed and implemented. These programs should
never be used in a malicious fashion against another user.
Time required: 25 minutes
objective: Given a scenario, analyze potential indicators to determine the type of attack.
description: A keylogger program captures everything that a user enters on a computer keyboard. In this project, you
download and use a software keylogger.
1. open your web browser and enter the url refog.com (if you are no longer able to access the program through
the url, use a search engine to search for “refog keylogger”).
2. click Features to see the features of the product.
3. click home.
4. click download.
5. click Create an account and enter the requested information.
6. click download.
7. When the file finishes downloading, run the installation program. note that you may have to enter the password
on the previous page to extract the files.
8. When prompted with I’m going to use this software to monitor: select My own computer.
9. click hide program icon from Windows tray. click Next.
10. click I Agree.
11. click Select All and then Next.
12. create a login and password for the online dashboard. click Activate.
13. you will receive a message that the subscription has expired. click yes to install in offline mode.
14. click Install.
15. click restart Now.
16. After the computer has restarted, use the keystroke combination Ctrl 1 Alt 1 Shift 1 k to launch refog keylogger.
17. click Tools and then click Settings.
18. note the default settings regarding what is captured.
19. click Back to log.
20. Minimize refog keylogger.
21. use your computer normally by opening a web browser to surf to a website. open Microsoft Word and type
several sentences. open and close several programs on the computer.
22. Maximize keylogger and note the information that was captured.
23. In the left pane, click through the different items that were captured.
24. under settings, click websites Visited.
25. under Websites Visited, click Make website screenshots.
26. click Apply.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 3 ThreaTs and aTTacks on endpoinTs 93
27. open a web browser and surf to multiple websites.
28. under users, click websites visited. note the screen captures of the different sites.
29. What type of information would a software keylogger provide to a threat actor? how could it be used against
the victim?
30. click File and then exit to close keylogger.
31. you may uninstall keylogger if you wish.
32. close all windows.
Case Projects
case project 3-1: Biological and File-Based Viruses
The word virus comes from latin, meaning a slimy liquid, poison, or poisonous secretion. In late Middle english, it was used
for the venom of a snake. The word later evolved from the discharge to the substances within the body that caused the
infectious diseases that produced the discharge. In 1799, edward Jenner published his discovery that the cowpox virus could
actually be used as a vaccine against smallpox. As biological science continued to advance, the word “virus” became even
more specific when referring to tiny infectious agents—even smaller than bacteria—that replicate in living cells. This new
field of virology exploded in the 1930s, when electronic microscopes allowed scientists to see viruses for the first time. since
then, scientists have continued to identify and name new biological viruses. combating viruses by developing vaccines has
many parallels to how malicious file-based viruses are identified and removed from a computer. using the Internet, research
these two types of viruses and find the similarities between combating biological and computer viruses. Write a one-to-two-
paragraph summary of your research.
case project 3-2: living-off-the-land Binaries (lolBins)
Fileless viruses take advantage of native services and processes that are part of the os to avoid detection and carry out
their attacks. These native services used in a fileless virus are called living-off-the-land binaries (lolbins). use the Internet to
research fileless viruses and lolbins. When did fileless viruses first appear? how do they compare with file-based viruses?
What are the defenses against fileless viruses? Write a one-page paper on your research.
case project 3-3: infamous logic Bombs
search the Internet for examples of logic bombs. select four logic bombs and write a report about them. Who was respon-
sible? When did the bombs go off? What was the damage? What was the penalty for the person responsible? did the orga-
nization make any changes after the attack? how can they be prevented?
case project 3-4: cybersecurity ai
The use of AI in cybersecurity is growing rapidly. use the Internet to research the latest developments in cybersecurity AI.
how does it work? What platforms are using it? What are some examples of it? how is it being improved? how can adversarial
AI attacks be defended against? Write a one-page paper of what you have learned.
case project 3-5: information security community site activity
The Information security community site is an online companion to this textbook. It contains a wide variety of tools, informa-
tion, discussion boards, and other features to assist learners. In order to gain the most benefit from the site, you will need
to set up a free account.
Go to community.cengage.com/infosec2. search the blogs on the topic “ransomware.” What did you learn? What
were your biggest surprises? What did you already know? how could you use this information in your first security job?
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

94 CoMPTIA SeCurITy+ GuIde To NeTwork SeCurITy FuNdAMeNTAlS
case project 3-6: north ridge security
north ridge security provides security consulting and assurance services. you have recently been hired as an intern to assist them.
north ridge is preparing a presentation to the monthly meeting of IT programmers and has asked you to do research
on attacks on software.
1. create a powerpoint presentation on memory leaks, buffer overflow, integer overflow, pointer/object dereference,
and attacks using ApI, device drivers, and dlls. your presentation should be at least nine slides in length.
2. As a follow-up to your presentation, you have been asked to write a one-page report on race conditions. use the
Internet to research race conditions and how they can best be addressed.
references
1. “The state of ransomware in the US: Report and statistics 2019,” Emisoft, Dec. 12, 2019, accessed May 6,
2020, https://blog.emsisoft.com/en/34822/the-state-of-ransomware-in-the-us-report-and-statistics-2019/.
2. Dudley, Renee, “The extortion economy: How insurance companies are fueling a rise in ransomware
attacks,” ProPublica, Aug. 27, 2019, accessed Oct. 27, 2019, www.propublica.org/article
/the-extortion-economy-how-insurance-companies-are-fueling-a-rise-in-ransomware-attacks.
3. “Definition of computer contaminant,” Law Insider, accessed May 9, 2020, www.lawinsider.com
/dictionary/computer-contaminant.
4. “McAfee Labs Threats Report,” Dec. 2018, accessed Apr. 21, 2019, www.mcafee.com/enterprise/en-us
/assets/reports/rp-quarterly-threats-dec-2018.pdf.
5. “Ransomware payments up 33% as Maze and Sodinokibi proliferate in Q1 2020,” Coveware, accessed
May 5, 2020, www.coveware.com/blog/q1-2020-ransomware-marketplace-report.
6. Soare, Bianca, “This year in ransomware payouts (2019 edition),” Heimdal Security, Dec. 11, 2019, accessed
May 9, 2020, https://heimdalsecurity.com/blog/ransomware-payouts/.
7. “Ransomware attacks map,” Statescoop, accessed May 9, 2020, https://statescoop.com/ransomware-map/.
8. “High-impact ransomware attacks threaten U.S. businesses and organizations,” Public Service
Announcement Federal Bureau of Investigation, Oct 2, 2019, accessed May 9, 2020, www.ic3.gov
/media/2019/191002.aspx.
9. “Ransomware payments up 33% as Maze and Sodinokibi proliferate in Q1 2020,” Coveware, accessed
May 5, 2020, www.coveware.com/blog/q1-2020-ransomware-marketplace-report.
10. Zumerle, Dioisio, D’Hoinne, Jeremy, and O’Neill, Mark, “How to build an effective API security strategy,”
Gartner Research, Dec. 8, 2017, accessed May 12, 2020, www.gartner.com/en/documents/3834704.
11. “Reinventing cybersecurity with artificial intelligence: The new frontier in digital security,”
Capgemini Research Institute, accessed May 13, 2020, www.capgemini.com/wp-content/
uploads/2019/07/AI-in-Cybersecurity_Report_20190711_V06.pdf.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Endpoint and
application
dEvElopmEnt SEcurity
After completing this module, you should be able to do the following:
1 Describe different threat intelligence sources
2 List the steps for securing an endpoint
3 Explain how to create and deploy SecDevOps
Module
4
Front-Page Cybersecurity
Suppose you were to uncover a zero-day vulnerability that nobody else knew about. What could you do with it?
You could be a broker and sell your knowledge of the vulnerability to a willing buyer. Governments often serve as buyers
of zero-day vulnerabilities to protect their citizens or attack their enemies. Other willing buyers are third-party “acquisition
platforms” who buy and then resell the vulnerability information to a government or a software developer. Very willing buy-
ers are also threat actors who would craft their own attacks based on the vulnerability.
However, a more responsible option would be for you to privately disclose the vulnerability to the developer of the soft-
ware, allowing the developer to fix it before an attacker uncovers and takes advantage of it. Not all zero-day vulnerabilities
are discovered by individuals. Many organizations have internal security teams who look for vulnerabilities in their own code
and in programs from other developers. When they find a problem, they privately contact the software developer with the
information so the developer can patch it.
What happens if developers drag their feet and do not patch the vulnerability within a reasonable period of time? Delay-
ing can keep the door open for a threat actor to find the zero-day vulnerability and exploit it.
Faced with the conundrum of trying to give developers time to create a patch and the public’s right to protection from
attacks, organizations have come up with “disclosure deadlines,” or the time that the software developer is given to patch a
vulnerability before it is publicly disclosed. These disclosure deadlines generally range from 45 days to 120 days.
Google started Project Zero in 2014 to look for zero-day vulnerabilities in its code and code from other software devel-
opers. Many developers responded quickly to a private alert of a zero-day vulnerability. As soon as the patch was available,
Project Zero released information about it. However, not all developers moved quickly: in some instances, it took six months
for the software developers to issue a patch.
Google’s Project Zero set a disclosure deadline of 90 days, after which it would go public with information about the
vulnerability. Going public would alert the user base to be aware of the vulnerability and possibly stop using the software
while shaming the developer into a faster response. The next year, Project Zero added a 14-day grace period: after the 90-day
deadline, a developer could request two additional weeks to make a patch available. Beyond 14 days, however, Google would
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

96 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
go public with the information. Project Zero said that by 2019, 97.7 percent of vulnerabilities uncovered were fixed within
90 days.
However, in early 2020, Project Zero announced a trial tweak to their disclosure deadline. The limit is still 90 days. But
Project Zero sometimes found that software developers were rushing to fix the zero-day vulnerability to meet the 90-day
deadline, and this sometimes resulted in a rushed and flawed patch that introduced another vulnerability into the code.
With Project Zero’s new trial tweak, software developers will now have the full 90 days to create a patch for the vulnerability,
and Project Zero will say nothing until the end of the 90 days. Even if the developer can fix the vulnerability in just 20 days,
Google will still say nothing until 90 days have elapsed. However, the developer and Google can make a mutual disclosure
before the 90-day deadline if both sides agree on the early disclosure.
Why the change? Project Zero says that faster patch development, while still important, is not the exclusive goal any-
more. Instead, thorough patch development—not sticking a bandage on it but actually finding the underlying problem and
correcting it—and improved patch adoption are also important. In the words of Project Zero, “End user security doesn’t
improve when a bug is found, and it doesn’t improve when a bug is fixed. It improves once the end user is aware of the bug
and typically patches their device.”
Attacks using malware, application attacks, and adversarial artificial intelligence attacks against endpoints continue
around the clock every day. What defenses can be used to ward off these attacks?
First, it is important to access threat intelligence sources in order to be aware of the latest types of attacks and how
to defend against them. With that information at hand, securing devices through boot integrity, protecting endpoints,
and hardening endpoints can then effectively be used. But deploying these defenses is still considered “after the fact.”
A growing chorus of security professionals today are demanding that it is the responsibility of the software developers
to create and deploy software using secure application development coding techniques.
In this module, you will learn about securing endpoint devices and creating and deploying secure applications.
But first you will explore the sources of threat intelligence information.
thrEat intElligEncE SourcES
✔ CertiFiCation
1.5 Explain different threat actors, vectors, and intelligence sources.
At one time, organizations were reluctant to share information about attacks on their networks and endpoints, often
because they were concerned about “bad publicity” that might arise from this disclosure. Today that is no longer the
case. Organizations are pooling their experiences and knowledge gained about the latest attacks with the broader
security community. Sharing this type of information has become an important aid to help other organizations shore
up their defenses.
One type of shared information is the evidence of an attack. Most organizations monitor their networking environ-
ment to determine what normally occurs. They use this data to create a database of key risk indicators (KRIs). A KRI
is a metric of the upper and lower bounds of specific indicators of normal network activity. These indicators may
include the total network logs per second, number of failed remote logins, network
notE 1 bandwidth, and outbound email traffic. A KRI exceeding its normal bounds could be
(but is not always) an indicator of compromise (IOC). An IOC shows that a malicious
Like radar that shows the
activity is occurring but is still in the early stages of an attack.
enemy approaching, predic-
Making IOC information available to others can prove to be of high value as it
tive analysis helps determine
may indicate a common attack that other organizations are also experiencing or
when and where attacks may
will soon experience. This information aids others in their predictive analysis or
occur.
discovering an attack before it occurs.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 97
Threat intelligence sources fall into several categories, as do the sources from which threat intelligence informa-
tion can be gathered.
categories of Sources
The two categories of threat intelligence sources are open source and closed source.
open Source information
The phrase open source has its roots in the computer industry. Initially, it referred to software for which the source
code was open for anyone to examine. Over time, “open source” was used to refer to anything that could be freely used
without restrictions, such as an open source film or open source curriculum.
notE 2
The phrase “open source” came out of a strategy session in 1998 by about a half dozen Linux software developers who
wanted to take advantage of an announcement by Netscape that it was planning to give away the source code of its
browser. The developers wanted to persuade the corporate world about the superiority of an open software development
process but found that the phrase “free software” that had been used previously carried a stigma of being inferior. After
a brainstorming session, the label “open source” was agreed upon.
Open source threat intelligence information that is freely available, often called open source intelligence (OSINT),
has become a vital resource. This information is often collected and then disseminated through public information
sharing centers. A typical sharing center is the U.S. Department of Homeland Security (DHS) Cyber Information Shar-
ing and Collaboration Program (CISCP). The CISCP “enables actionable, relevant,
and timely unclassified information exchange through trusted public-private partner-
notE 3
ships across all critical infrastructure sectors.” With the DHS serving as the coordina-
tor, the CISCP enables its members (called “partners”) to not only share threat and The CISCP program is free to
vulnerability information but also take advantage of the DHS’s cyber resources. Some join and use. Those interested
of the CISCP services include the following: must agree to a Cyber Infor-
mation Sharing and Collabora-
• Analyst-to-analyst technical exchanges. Partners can share and receive informa-
tion Agreement (CISCA), which
tion on threat actor tactics, techniques, and procedures (TTPs) and emerging
enables DHS and its partners
trends.
to exchange anonymized
• CISCP analytical products. A portal can be accessed through which partners
information. Once partners
can receive analysis of products and threats.
sign the agreement, DHS
• Cross industry orchestration. Partners can share lessons learned and their
coordinates an on- boarding
expertise with peers across common sectors.
session to customize how
• Digital malware analysis. Suspected malware can be submitted to be analyzed
DHS and the organization can
and then used to generate malware analysis reports to mitigate threats and
exchange information.
attack vectors.
The two concerns around public information sharing centers are the privacy of
shared information and the speed at which the information is shared.
Privacy A concern about using public information sharing centers is that of privacy. An organization that is the victim
of an attack must be careful not to share proprietary or sensitive information when providing IOCs and attack details.
As a safeguard, most public information sharing centers have protections in place to prevent the disclosure of
proprietary information. For example, Table 4-1 lists the privacy protections of the CISCP.
Speed Threat intelligence information must be distributed as quickly as possible to others. To rely on email alerts
that require a human to read them and then react takes far too much time. As an alternative, Automated Indicator
Sharing (AIS) can be used instead. AIS enables the exchange of cyberthreat indicators between parties through
computer-to-computer communication, not email communication. Threat indicators such malicious IP addresses or
the sender address of a phishing email can be quickly distributed to enable others to repel these attacks.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

98 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
notE 4
Those participating in AIS generally are connected to a managed system controlled by the public information shar-
ing center that allows bidirectional sharing of cyberthreat indicators. Not only do participants receive indicators, but
they can also share indicators they have observed in their own network defenses to the public center, which then
distributes them to all participants.
table 4-1 CISCP privacy protections
| Protection | Explanation | Example |
| ---------- | ----------- | ------- |
Cybersecurity Information Sharing  CISA is a federal law passed in  CISA requires a non-federal entity
Act (CISA) 2015 that provides authority for  to remove any information from a
|     | cybersecurity information sharing       | cyberthreat indicator that it knows      |
| --- | --------------------------------------- | ---------------------------------------- |
|     | between the private sector, state, and  | at the time of sharing to be personal    |
|     | local governments and the federal       | information of a specific individual or  |
|     | government.                             | information that identifies a specific   |
individual that is not directly related
to a cybersecurity threat.
Freedom of Information Act (FOIA) FOIA was passed in 1967 and  Although federal agencies are
|     | provides the public the right to    | required to disclose any information  |
| --- | ----------------------------------- | ------------------------------------- |
|     | request access to records from any  | requested under the FOIA, they        |
|     | federal agency.                     | offer nine exemptions, one of which   |
protects interests such as personal
privacy.
Traffic-Light Protocol (TLP) TLP is a set of designations used to  TLP uses four colors (red, amber,
|     | ensure that sensitive information    | green, and white) to indicate the  |
| --- | ------------------------------------ | ---------------------------------- |
|     | is shared only with the appropriate  | expected sharing limitations the   |
|     | audience.                            | recipients should apply.           |
Protected Critical Infrastructure  The PCII Act of 2002 protects private  To qualify for PCII protections,
Information (PCII) sector infrastructure information  information must be related to the
|     | that is voluntarily shared with the  | security of the critical infrastructure,  |
| --- | ------------------------------------ | ----------------------------------------- |
|     | government for the purposes of       | voluntarily submitted, and not            |
|     | homeland security.                   | submitted in place of compliance          |
with a regulatory requirement.
notE 5 Two tools facilitate AIS. Structured Threat Information expression (STIX) is
a language and format used to exchange cyberthreat intelligence. All information
APIs are covered in Module 3.
about a threat can be represented with objects and descriptive relationships. STIX
information can be visually represented for a security analyst to view or stored in
a lightweight format to be used by a computer. Trusted Automated exchange of
Intelligence Information (TAXII) is an application protocol for exchanging cyberthreat intelligence over Hypertext
Transfer Protocol Secure (HTTPS). TAXII defines an application protocol interface (API) and a set of requirements for
TAXII clients and servers.
closed Source information
notE 6 Closed source is the opposite of open source. It is proprietary, meaning it is owned
by an entity that has an exclusive right to it. Organizations that are participants in
AIS is used more extensively
closed source information are part of private information sharing centers that
with public information shar-
restrict both access to data and participation. Whereas private sharing centers are
ing  centers  than  private
similar to public sharing centers in that members share threat intelligence informa-
centers. tion, insights, and best practices, private sharing centers are restrictive regarding
who may participate. All candidates must go through a vetting process and meet
certain criteria.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Sources of threat intelligence
Several sources of threat intelligence are useful. These include the following:
• Vulnerability databases. A vulnerability database is a repository of known notE 7
vulnerabilities and information as to how they have been exploited. These
Data feeds, vulnerability feeds,
databases create “feeds” of the latest cybersecurity incidences. Common
threat feeds, and TTP are cov-
cybersecurity data feeds include vulnerability feeds that provide information
ered in Module 2.
on the latest vulnerabilities and threat feeds that outline current threats and
attacks. The adversary tactics, techniques, and procedures (TTP) is a database
of the behavior of threat actors and how they orchestrate and manage attacks.
• Threat maps. A cybersecurity threat map illustrates cyberthreats overlaid on a diagrammatic representation
of a geographical area. Figure 4-1 illustrates a threat map. Threat maps help in visualizing attacks and provide
a limited amount of context of the source and the target countries, the attack types, and historical and near
real-time data about threats.
Figure 4-1 Threat map
Caution Threat maps may look impressive, but in reality, they provide limited valuable information. Many
maps claim that they show data in real time, but most are simply a playback of previous attacks.
Because threat maps show anonymized data, it is impossible to know the identity of the attackers
or the victims. Also, threat actors usually mask their real locations, so what is displayed on a threat
map is incorrect. As a result, many cybersecurity professionals question the value of threat maps.
• File and code repositories. File and code repositories are another source of notE 8
threat intelligence. Victims of an attack can upload malicious files and software
code that can then be examined by others to learn more about the attacks The Hands-On Projects 3-1
and craft their defenses. Several entities of the U.S. government—including and 3-2 in Module 3 provide
the Federal Bureau of Investigation (FBI), the Cybersecurity and Infrastruc- you with experience using
ture Security Agency (CISA), and the Department of Defense (DoD) U.S. Cyber VirusTotal.
Command—are particularly active in posting to file and code repositories.
Often samples of recently discovered malware variants are uploaded to the
VirusTotal malware aggregation repository along with published detailed mal-
ware analysis reports (MARs) containing IOCs for each malware variant.
.dtL
seigolonhceT
erawtfoS
tnioP
kcehC
:ecruoS
Module 4 endPoint and aPPlication develoPMent Security 99
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

• Dark web. The web has three levels, as illustrated in Figure 4-2: the clear web, which includes ordinary websites
(social media, ecommerce, news, etc.) that most users access regularly and can be located by a search engine;
the deep web, which includes exclusive and protected websites (corporate email, material behind a digital
paywall, cloud hosting services, etc.) that are hidden from a search engine and cannot be accessed without
valid credentials; and the dark web. The dark web is like the deep web in that it is beyond the reach of a
normal search engine, but it is the domain of threat actors. Using special software such as Tor or I2P (Invisible
Internet Project) this software will mask the user’s identity to allow for malicious activity such as selling drugs
and stolen personal information and buying and selling malicious software used for attacks. Some security
professionals and organizations use the dark web on a limited basis to look for signs that information critical
to that enterprise is being sought out or sold on the dark web.
Clear web
Academic
Medical
Legal
Records Scientific
Deep web Government
Subscription-only
information
Databases
Organization-specific
information
Dark web Illegal activities
Figure 4-2 Dark web
Caution Finding information on the dark web is difficult. First, it requires using Tor or IP2, which prevents
a device’s IP address being traced. Second, although some dark web search engines are avail-
able, they are unlike regular search engines such as Google. The dark web search engines are
difficult to use and notoriously inaccurate. One reason is because merchants who buy and sell
stolen data or illicit drugs are constantly on the run, and their dark websites appear and then
suddenly disappear with no warning. Finally, dark websites use a naming structure that results
in URLs such as p6f47s5p3dq3qkd.onion. All of these are hurdles that keep out anyone who does
not understand these inner workings.
two rights & a wrong
1. Two concerns about public information sharing centers are the privacy of shared information and the
speed at which the information is shared.
2. Two tools that facilitate AIS are STIX and TAXII.
3. Security professionals consider threat maps a vital source of information.
See Appendix B for the answer.
moc.kcotsrettuhS/inavaT
olomoR
:ecruoS
100 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 101
SEcuring Endpoint computErS
✔ CertiFiCation
3.2 Given a scenario, implement host or application security solutions.
4.4 Given an incident, apply mitigation techniques or controls to secure an environment.
Despite the fact that endpoint devices like smartphones, tablets, and wearable fitness trackers receive the bulk of
attention today, the “workhorse” of technology remains the personal computer. More than 260 million computers are
sold annually in the United States1 compared to 160 million smartphones sold each year.2 While all endpoints must
be protected from attacks, endpoint desktop and laptop computers must be secured because they are connected to
corporate networks and its data, they contain data stored locally, and they can be used as a springboard to attack
other endpoints.
Securing endpoint computers primarily involves three major tasks: confirming that the computer has started
securely, protecting the computer from attacks, and then hardening it for even greater protection.
confirm Boot integrity
One of the steps that is often overlooked in securing endpoint computers is to confirm that the computer has started
without any malicious activity taking place. Ensuring secure startup involves the Unified Extensible Firmware Interface
(UEFI) and its boot security features.
unified Extensible Firmware interface (uEFi)
Early cowboys and workhands were known for wearing tall, tight-fitting boots. These boots had a tab or loop at the top
through which a tool called a boot hook could be inserted to assist in pulling on the boot. In the mid-1800s, the expres-
sion pull yourself up by your own bootstraps was used to describe an impossible task of lifting oneself off the ground by
pulling on the bootstrap. The phrase later came to mean to improve your situation by your own efforts without any
external help.
Computers adopted this language to describe the process of starting a computer when it has been powered off.
Because a computer is unable to rely on external assistance when powered on, starting a computer is called booting up
or just booting.
The booting process on early personal computers, both Apple Mac and Windows PC, used firmware called the
BIOS (Basic Input/Output System). The BIOS was a chip integrated into the comput-
er’s motherboard. When the computer was powered on, the BIOS software would notE 9
“awaken” and perform the following steps in a legacy BIOS boot:
Although BIOS chips were
1. The BIOS would first test the various components of the computer to
nonvolatile (they retained the
ensure that they were functioning properly (called the POST or Power-On
information even when the
Self-Test).
computer was turned off),
2. Next, the BIOS would reference the Master Boot Record (MBR) that specified CMOS needed its own dedi-
the computer’s partition table, which instructed the BIOS where the com- cated power source, which
puter’s operating system (OS) could be located. was a lithium-ion battery
3. Finally, the BIOS passed control to the installed boot loader, which about the size of a coin that
launched the OS. could hold a charge for up to
10 years before needing to be
Originally, BIOS firmware was stored in a ROM (read-only memory) chip on the
replaced. If the CMOS battery
motherboard, supplemented by a CMOS (complementary metal-oxide-semiconductor)
died, the BIOS settings were
chip that stored any changes to the BIOS. Later computer systems stored the BIOS
not lost but instead were reset
contents in flash memory so it could be easily updated. This provided the ability to
to their default settings.
update to the BIOS firmware so new features could be added.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

To add functionality, an improved firmware interface was developed to replace the BIOS. Known as ueFI (unified
extensible Firmware Interface), it provides several enhancements over BIOS. This includes the ability to access hard
drives that are larger than two terabytes (TB), support for an unlimited number of primary hard drive partitions, faster
booting, and support for networking functionality in the UEFI firmware itself to aid in remote troubleshooting. UEFI
also has a more advanced user interface for configurations and information, as seen in Figure 4-3.
Figure 4-3 UEFI user interface
SUSA
:ecruoS
102 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
notE 10 Boot Security
Another significant improvement of UEFI over BIOS relates to boot security. The abil-
Legacy BIOS boot support
ity to update the BIOS in firmware also opened the door for a threat actor to create
from motherboard manufac-
malware to infect the BIOS. Called a BIOS attack, it would exploit the update feature
turers ended in 2020 and UEFI
of the BIOS. Because the BIOS resides in firmware and an infected BIOS would then
is now the standard.
persistently re-infect the computer whenever it was powered on, BIOS attacks were
difficult to uncover and hard to disinfect. UEFI, used along with other components, is
designed to combat these BIOS vulnerabilities and provide improved boot security.
Caution UEFI by itself does not provide enhanced boot security. It must be paired with other boot security
functions.
Boot security involves validating that each element used in each step of the boot process has not been modified.
This process begins with the validation of the first element (boot software). Once the first element has been validated,
it can then validate the next item (such as software drivers) and so on until control has been handed over to the OS.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 103
This is called a chain of trust: each element relies on the confirmation of the previous element to know that the entire
process is secure.
But how does the chain begin? What if a threat actor were to inject malware prior to start of the chain of trust? If
the starting point is software, it can be replaced or modified. That would then compromise each element of the chain.
To prevent this, a chain of trust requires a strong starting point.
The strongest starting point is hardware, which cannot be modified like software. This is known as the hardware
root of trust. Security checks are “rooted” in (begin with) hardware checks. Because this chain of trust begins with a
hardware verification, each subsequent check can rely upon it (called boot attestation).
Several techniques can be used to assure boot security, all of which rely on UEFI; some also rely on the hardware
root of trust. Boot security modes are listed in Table 4-2.
table 4-2 Boot security modes
Name Description Advantages Disadvantages
Legacy BIOS Uses BIOS for boot functions Compatible with older systems No security features
Boot
UEFI Native Uses UEFI standards for boot Security boot modules can be No validation or protection of
Mode functions patched or updated as needed. the boot process
Secure Boot Each firmware and software All system firmware, Custom hardware, firmware,
executable at boot time must bootloaders, kernels, and and software may not pass
be verified as having prior other boot-time executables without first being submitted
approval. are validated. to system vendors like
Microsoft.
Trusted Boot Windows OS checks the Takes over where Secure Boot Requires using Microsoft OS
integrity of every component of leaves off by validating the
boot process before loading it. Windows 10 software before
loading it
Measured Computer’s firmware logs the Provides highest degree of Could slow down the boot
Boot boot process so the OS can security process
send it to a trusted server to
assess the security.
Caution The Secure Boot security standard is designed to ensure that a computer boots using only soft-
ware that is trusted by the computer manufacturer. Manufacturers can update the list of trusted
hardware, drivers, and OS for a computer, which are stored in the Secure Boot database on the
computer. Although it is possible for the user to disable Secure Boot to install hardware or run
software or OS that have not been trusted by the manufacturer, this makes it difficult or impos-
sible to reactivate Secure Boot without restoring the computer back to its original factory state.
protect Endpoints
Once boot security has been established; the computer endpoints must be actively protected. The protection can be
done through software installed on the endpoint, such as antivirus software, antimalware, web browser protections,
and monitoring and response systems.
antivirus
One of the first software protections was antivirus (av) software. This software can
examine a computer for file-based virus infections as well as monitor computer activity
and scan new documents that might contain a virus. (Scanning is typically performed notE 11
when files are opened, created, or closed.) If a virus is detected, options generally include
Viruses are covered in
cleaning the file of the virus, quarantining the infected file, or deleting the file. Log files
Module 3.
created by AV products can also provide beneficial information regarding attacks.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

104 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
Many AV products use signature-based monitoring, also called static analysis. The AV software scans files by
attempting to match known virus patterns against potentially infected files (called string scanning). Other variations
include wildcard scanning (a wildcard is allowed to skip bytes or ranges of bytes instead of looking for an exact match)
and mismatch scanning (mismatches allow a set number of bytes in the string to be any value regardless of their posi-
tion in the string).
Caution The weakness of signature-based monitoring is that the AV vendor must constantly be searching
for new viruses, extracting virus signatures, and distributing those updated databases to all users.
Any out-of-date signature database could result in an infection.
notE 12 A newer approach to AV is heuristic monitoring (called dynamic analysis),
which uses a variety of techniques to spot the characteristics of a virus instead of
One AV heuristic monitoring attempting to make matches. The difference between static analysis and dynamic
technique used is code emula- analysis detection is similar to how airport security personnel in some nations
tion in which a virtual environ- screen for terrorists. A known terrorist attempting to go through security can be
ment is created that simulates identified by comparing his face against photographs of known terrorists (static
the CPU and memory of the analysis). What about a new terrorist with no photograph? Security personnel can
computer. Any questionable look at the person’s characteristics—holding a one-way ticket, not checking any
program code is executed in luggage, showing extreme nervousness—as possible indicators that the individual
the virtual environment (no may need to be questioned (dynamic analysis).
actual virus code is executed
by the real CPU) to determine antimalware
if it is a virus. Instead of only protecting against file-based viruses as with AV, antimalware is a
suite of software intended to provide protections against multiple types of malware,
such as ransomware, cryptomalware, and Trojans.
notE 13 Some antimalware software protects against spam that has evaded the corporate
email gateway and monitors emails for spam and other unwanted content. Antimal-
Bayesian filters generally trap
ware spam protection is often performed using a technique called Bayesian filtering.
a much higher percentage of
The software divides email messages that have been received into two piles, spam
spam than other techniques.
and nonspam. The filter then analyzes every word in each email and determines how
frequently a word occurs in the spam pile compared to the nonspam pile. A word
such as “the” would occur equally in both piles and be given a neutral 50 percent
ranking. A word such as “report” may occur frequently in nonspam messages and would receive a 99 percent prob-
ability of being a nonspam word, while a word like “sex” may receive a 99 percent probability of being a spam word.
Whenever email arrives, the filter looks for the 15 words with the highest probabilities to calculate the message’s
overall spam probability rating.
Another component of an antimalware suite is antispyware, which helps prevent
notE 14 computers from becoming infected by spyware. One common technique is to use
a pop-up blocker. A pop-up is a small web browser window that appears over a
A pop-up blocker can be part
webpage. Most pop-up windows are created by advertisers and launch as soon as
of an antimalware package, a
a new website is visited. Using a pop-up blocker, users can often select the level of
separate program, or a feature
blocking, ranging from blocking all pop-ups to allowing specific pop-ups.
incorporated within a browser
that stops pop-up advertise- Web Browsers
ments from appearing.
Web browsers have a degree of security that can protect endpoint computers. This
security includes secure cookies and HTTP headers.
Secure cookies The Hypertext Transfer Protocol (HTTP) is the Internet-based protocol that is the foundation of
all data exchanges on the web. It is a client-server protocol so that requests are initiated by the recipient or client,
usually a web browser, to a web server.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 105
One of the limitations of HTTP is that it is a stateless protocol. Unlike a stateful pro- notE 15
tocol, which “remembers” everything that occurs between the browser client and the
server, a stateless protocol “forgets” what occurs when the session is interrupted or A cookie can contain a variety
ends. Three ways the stateless protocol HTTP can mimic a stateful protocol include of information based on the
the following: user’s preferences when visit-
ing a website. For example, if
• Using a URL extension so the state is sent as part of the URL as a response
a user inquires about a rental
• Using “hidden form fields” in which the state is sent to the client as part of the
car at the car agency’s website,
response and returned to the server as part of a form’s hidden data
that site might create a cookie
• Storing user-specific information in a file on the user’s local computer and then
that contains the user’s travel
retrieve it later in a file called a cookie.
itinerary. In addition, it may
Websites use several types of cookies. A first-party cookie is created from the record the pages visited on a
website that a user is currently viewing; whenever the user returns to this site, that site to help the site customize
cookie is used by the site to view the user’s preferences and better customize the the view for any future visits.
browsing experience. Some websites attempt to place additional cookies on the local Cookies can also store any
hard drive. These cookies often come from third parties that advertise on the site and personally identifiable infor-
want to record the user’s preferences. These cookies are called third-party cookies. mation (name, email address,
A session cookie is stored in random-access memory (RAM), instead of on the hard work address, telephone num-
drive, and only lasts for the duration of visiting the website. ber, and so on) that was pro-
Cookies can pose security risks as well as privacy risks. First-party cookies can vided when visiting the site;
be stolen and used to impersonate the user, while third-party cookies can be used to however, a website cannot
track the browsing or buying habits of a user. When multiple websites are serviced gain access to private infor-
by a single marketing organization, cookies can be used to track browsing habits on mation stored on the local
all the client’s sites. computer.
As a means of protection for cookies, a web browser can send a secure cookie.
This cookie is only sent to the server with an encrypted request over the secure
HTTPS protocol. This prevents an unauthorized person from intercepting a cookie
that is being transmitted between the browser and the web server.
HttP response Headers When users visit a website through their web browser, the web server answers back
with HTTP response Headers. These headers tell the browser how to behave while communicating with the website.
Several HTTP Response Headers can improve security; these are listed in Table 4-3.
table 4-3 HTTP response headers
HTTP response header Description Protection
HTTP Strict Transport Forces browser to communicate over Encrypts transmissions to prevent
Security (HSTS) more secure HTTPS instead of HTTP unauthorized user from intercepting
Content Security Policy (CSP) Restricts the resources a user is allowed Protects against injection attacks
to load within the website
Cross Site Scripting Prohibits a page from loading if it detects Prevents XSS attacks
Protection (X-XSS) a cross-site scripting attack
X-Frame-Options Prevents attackers from “overlaying” their Foils a threat actor’s attempt to trick a
content on the webpage user into providing personal information
monitoring and response Systems
The three types of monitoring and response systems for endpoint computers are host intrusion detection systems
(HIDS), host intrusion prevention systems (HIPS), and endpoint detection and response (EDR).
Host intrusion detection Systems (HidS) A host intrusion detection system (HIdS) is a software-based appli-
cation that runs on an endpoint computer and can detect that an attack has occurred. The primary function of a HIDS
is automated detection, which saves someone from sorting through log files to find an indication of unusual behavior.
HIDS can quickly detect evidence that an intrusion has occurred. Figure 4-4 shows a HIDS dashboard.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Figure 4-4 HIDS dashboard
Caution One of the drawbacks to a HIPS is a high number of false positives can be generated. Both
legitimate and malicious programs often access the same resource, and each can cause a HIPS
to then block the action.
sdniWraloS
:ecruoS
106 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
A HIDS relies on agents installed directly on the endpoint, and these agents work closely with the OS to observe
activity. HIDSs typically monitor these types of endpoint computer functions:
• System calls. Each operation in a computing environment starts with a system call. A system call is an instruc-
tion that interrupts the program being executed and requests a service from the operating system. HIDS can
monitor system calls based on the process, mode, and action being requested.
• File system access. System calls usually require specific files to be opened to access data. A HIDS works to
ensure that all file openings are based on legitimate needs and are not the result of malicious activity.
• Host input/output. HIDS monitors all input and output communications to watch for malicious activity. For
example, if the system never uses instant messaging (IM) and suddenly a threat attempts to open an IM con-
nection from the system, the HIDS would detect this as anomalous activity.
Host intrusion Prevention Systems (HiPS) As its name implies, an intrusion prevention system not only monitors
to detect malicious activities but also attempts to stop them. A host intrusion prevention system (HIPS) monitors
endpoint activity to immediately block a malicious attack by following specific rules. Activity that a HIPS watches for
includes an event that attempts to control other programs, terminate programs, and install devices and drivers. When
a HIPS blocks action, it then alerts the user so an appropriate decision about what to do can be made.
endpoint detection and response (edr) endpoint detection and response (edr) tools have a similar function-
ality to HIDS of monitoring endpoint events and of HIPS of taking immediate action. However, EDR tools are considered
more robust than HIDS and HIPS. First, an EDR can aggregate data from multiple endpoint computers to a centralized
database so that security professionals can further investigate and gain a better picture of events occurring across
multiple endpoints instead of just on a single endpoint. This can help determine if an attack is more widespread across
the enterprise and if more comprehensive and higher-level action needs to be taken. Second, EDR tools can perform
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 107
more sophisticated analytics that identify patterns and detect anomalies. This can notE 16
help detect unusual or unrecognized activities by performing baseline comparisons
of normal behavior. Many EDRs also allow for a
manual or user analysis of the
harden Endpoints data.
After boot security has been established and the endpoints have been protected,
the next step is to harden the endpoints for further protection. Hardening endpoints involves patch management and
OS protections.
patch management
One of the most important steps in securing an endpoint computer is to promptly install patches. Threat actors often
watch for the release of a patch and then immediately craft an attack around the vulnerability the patch addresses,
knowing that many users and organizations are lax in applying patches.
Effective patch management involves two types of patch management tools to administer patches. The first type
includes tools for patch distribution, while the second type involves patch reception.
Patch distribution Modern operating systems—such as Red Hat Linux, Apple macOS, Ubuntu Linux, and Microsoft
Windows—frequently distribute patches. A growing number of application and utility software developers are also
distributing patches for their products (third-party updates).
These patches, however, can sometimes create new problems, such as preventing a custom application from
running correctly. Organizations that have these types of applications usually test patches when they are released to
ensure that they do not adversely affect any customized applications. In these instances, the organization delays the
installation of a patch from the vendor’s online update service until the patch is thoroughly tested. But how can an
organization prevent its employees from installing the latest patch until it has passed testing and still ensure that all
users download and install necessary patches?
The answer is an automated patch update service. This service is used to manage patches within the enterprise
instead of relying upon the vendor’s online update service. An automated patch update service typically consists of a
component installed on one or more servers inside the corporate network. Because these servers can replicate infor-
mation among themselves, usually only one of the servers must be connected to the vendor’s online update service,
as seen in Figure 4-5.
Advantages of using an automated patch update service include the following:
• Downloading patches from a local server instead of using the vendor’s online update service can save band-
width and time because each computer does not have to connect to an external server.
• Administrators can approve or decline updates for client systems, force updates to install by a specific date,
and obtain reports on what updates each computer needs.
• Administrators can approve updates for “detection” only; this allows them to see which computers require
the update without installing it.
Patch reception Early versions of OSs allowed the user to configure how they receive patches. For example, prior
to Windows 10, Microsoft users had several options regarding accepting or even rejecting patches. These options
included Install updates automatically, Download updates but let me choose whether to install them, Check for updates
but let me choose whether to download and install them, and Never check for updates. However, this approach frequently
resulted in important security patches being ignored by users and putting their computers at risk.
Today users have fewer—if any—options regarding patches: usually patches are automatically downloaded and
installed whenever they become available. This is called auto-update, and it ensures that the software is always up to date.
Microsoft Windows 10 is typical of the enhancements of patch reception. Figure 4-6 shows the Windows 10
Advanced options. These options include the following:
• Forced updates. Users can no longer refuse or indefinitely delay security updates. By default, all updates will
be downloaded and installed automatically. However, users can defer the “quality updates” (those with secu-
rity patches) but only for seven days (Windows 10 Home edition) or 35 days (all other versions). New feature
updates (those without security patches) can be delayed for 35 days (Windows 10 Home edition) or 365 days
(all other versions).
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

108 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
Vendor’s online
update server
Internet
Automated patch
update server 1
Automated patch
update server 2
Figure 4-5 Automated patch update service
• No selective updates. Unlike in previous versions of Windows, users cannot select individual Windows updates
to download and install. However, users can select if they want to receive updates for other installed Microsoft
products (such as Office).
• More efficient distribution. If many Windows 10 devices are connected to a network, each device does not
have to download the updates over the Internet individually. Instead, once one device has downloaded the
updates, they can then be distributed to the other devices across the local network. In addition, Windows will
not download updates on mobile devices unless that device is connected to an unrestricted Wi-Fi network (so
that it does not use the cellular data connections that users pay for).
operating Systems
There are different types and uses of operating systems. Several of the major types are listed in Table 4-4.
Although protections within the OS are designed to provide security for the endpoint device, the OS itself must be
protected. Securing an OS involves proper security configurations and using confinement tools.
Security configuration The security of an OS depends upon the proper configuration of its built-in security fea-
tures. Modern operating systems have hundreds of security settings. A typical OS security configuration should include
the following:
• Disabling unnecessary ports and services. One of the primary OS security configurations involves disabling
unnecessary open ports and services, or “turning off” any service that is not being used, such as Microsoft
Windows ASP.NET State Service, Portable Device Enumerator Service, and Apple macOS Spotlight Indexing.
In addition, closing any unnecessary TCP ports can also enhance security.
• Disabling default accounts/passwords. Another important disabling function is disabling default accounts and
passwords. Some OSs include unnecessary accounts. For example, Microsoft Windows 10 includes a built-in
Administrator account that can be used for those building new computers to run programs and applications
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4  endPoint and aPPlication develoPMent Security 109
tfosorciM morf snoissimrep htiw desU :ecruoS
Figure 4-6 Microsoft Windows 10 Advanced options
table 4-4 Types of OSs
| OS type | Uses | Examples |
| ------- | ---- | -------- |
Network OS Software that runs on a network device like a  Cisco Internetwork Operating System (IOS),
|     | firewall, router, or switch | Juniper JUNOS, MikroTik RouterOS |
| --- | --------------------------- | -------------------------------- |
Server OS Operating system software that runs on a  Microsoft Windows Server, Apple macOS
|     | network server to provide resources to network  | Server, Red Hat Linux |
| --- | ----------------------------------------------- | --------------------- |
users
Workstation OS Software that manages hardware and software  Microsoft Windows, Apple macOS, Ubuntu
|     | on a client computer | Linux |
| --- | -------------------- | ----- |
Appliance OS OS in firmware that is designed to manage a  Linpus Linux
specific device like a digital video recorder or
video game console.
Kiosk OS System and user interface software for an  Microsoft Windows, Google Chrome OS, Apple
|     | interactive kiosk | iOS, Instant WebKiosk, KioWare (Android) |
| --- | ----------------- | ---------------------------------------- |
Mobile OS Operating system for mobile phones,  Google Android, Apple iOS, Apple iPadOS
smartphones, tablets, and other handheld
devices
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

110 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
before a user account is created. In addition, some accounts may come with default passwords that should
be changed.
• Employing least functionality. The concept of “least functionality” states a user should only be given the mini-
mum set of permissions required to perform necessary tasks; all other permissions should be configured as
not available to the user. For example, a user should not have the ability to modify system security features.
Instead of recreating the same security configuration on each endpoint computer, tools can be used to automate
the process. In Microsoft Windows, a security template is a collection of security configuration settings. These settings
typically include account policies, user rights, event log settings, restricted groups, system services, file permissions,
and registry permissions. Once a single endpoint computer has been configured properly, a security template from
that device can be developed and used for deploying to other systems. Predefined security templates are also available
to be imported, and these settings then can be modified to create a unique security configuration for all endpoints.
notE 17
Although a Microsoft Windows security template can be deployed manually, this requires an administrator to access each
computer and apply the security template either through using the command line or a snap-in, which is a software module
that provides administrative capabilities for a device. A preferred method is to use Group Policy, which is a feature that
provides centralized management and configuration of computers and remote users who are using specific Microsoft
directory services known as Active Directory (AD). Group Policy allows a single configuration to be set and then deployed
to many or all users.
notE 18 For a Microsoft Windows endpoint computer, it is also important to secure the
registry, which is a database that contains low-level settings used by the Windows
Tamper Protection also pre- OS and for those applications that use the registry. Threat actors who can modify
vents changes to security set- the registry could be able to disable antivirus and antimalware protections, disable
tings by programs, Windows any cloud-delivered protection, and remove security updates.
command line commands, or To mitigate this risk, the Windows 10 Tamper Protection security feature pre-
through Group Policy. vents Windows security settings from being changed or disabled by a threat actor
who modifies the registry. Instead, the security settings can only be accessed directly
notE 19
through the Windows 10 user interface or through enterprise management software.
In addition to Tamper Protection, a Group Policy setting can prevent access to
Instead of managing secu-
the tool that can alter the registry. This setting is Prevent access to registry editing
rity options on an OS that
tools and is shown in Figure 4-7.
has been deployed, in some
cases, it is necessary to tighten confinement tools Several tools can be used to “confine” or restrict malware.
security during the design and These tools include the following:
coding of the OS. This is called
• Application whitelisting/blacklisting. An increasingly popular approach to client
OS hardening. An OS that has
OS security is to employ application whitelisting/blacklisting. whitelisting
been designed in this way to
is approving in advance only specific applications to run on the OS so that any
be secure is a trusted OS.
item not approved is either restricted or denied (“default-deny”). The inverse of
whitelisting is blacklisting, creating a list of unapproved software so that any
item not on the list of blacklisted applications can run (“default-allow”). Applica-
tion whitelisting/blacklisting requires preapproval for an application to run or
not run.
notE 20
The elite Tailored Access Operations (TAO) section of the National Security Agency (NSA) is responsible for compromising
networks owned by hostile nations to spy on them. The head of the TAO spoke at a security conference about the best
practices of security from the NSA’s perspective (in his own words, “what can you do to defend yourself to make my life
hard?”). One of the most important steps was to employ whitelisting for the software that runs on servers. A similar step
is to whitelist a predefined set of websites to which users can connect to prevent malware from accessing a C&C or to
exfiltrate stolen information.3
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Figure 4-7 Prevent access to registry editing tools
• Sandbox. Figure 4-8 illustrates a conceptual view of applications that interact notE 21
with an OS. A sandbox is a “container” in which an application can be run so
that it does not impact the underlying OS, as illustrated in Figure 4-9. Anything A sandbox is not the same as
that occurs within the sandbox is not visible to other applications or the OS a virtual machine. A virtual
outside the sandbox. Also, the contents of the sandbox are not saved when the machine is a “computer within
sandbox is closed. Sandboxes are often used when downloading or running a computer” in which an entire
suspicious programs to ensure that the endpoint will not become infected. OS runs as an application on
• Quarantine. Whereas a sandbox is used to contain an application, quarantine top of the regular OS. How-
is a process that holds a suspicious document. Quarantine is most commonly ever, its contents can be saved
used with email attachments. When an attachment is received, the quarantine for future use.
process removes the attachment and, depending upon the policy set by the
organization, either sends to the user sent a sanitized version of the attach-
ment (such as a Word DOCX document that has been converted to a PDF docu-
ment) or a URL to the document on a restricted computer so that the user can
view, print, or delete the attachment.
notE 22
Microsoft Office documents that are received as attachments, opened from an Internet location, or opened from an
unsafe location are by default quarantined. The documents are displayed in Protected View, which is a read-only mode
with most editing functions disabled. If the file needs to be saved or printed, the user can click the “Enable Editing” but-
ton to open the document as normal.
tfosorciM
morf
snoissimrep
htiw
desU
:ecruoS
Module 4 endPoint and aPPlication develoPMent Security 111
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

112 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
Application 1 Application 2 Application 3
Operating System Files and settings
Drivers
Hardware
Figure 4-8 Applications interacting with an OS
Sandbox Application 2 Application 3
Application 1
Files and settings
Operating System Files and settings
Drivers
Hardware
Figure 4-9 Using a sandbox
two rights & a wrong
1. In a Trusted Boot, the endpoint’s firmware logs the boot process to the OS can send it to a trusted server
to assess the security.
2. Dynamic analysis uses heuristic monitoring.
3. Cookies are a workaround of the stateless protocol HTTP.
See Appendix B for the answer.
crEating and dEploying SEcdEvopS
✔ CertiFiCation
2.3 Summarize secure application development, deployment, and automation concepts.
3.2 Given a scenario, implement host or application security solutions.
Confirming boot integrity, protecting endpoints, and hardening endpoints are all essential steps in securing an endpoint
computer. But an additional element that is also critical is creating and deploying secure applications. Because endpoint
computers run applications, the best endpoint boot security, antivirus and antimalware, patch management, and OS
security configurations can all be negatively impacted—and sometimes negated—by an application that contains
vulnerabilities. An unsecure application can open the door for attackers to exploit the application, the data that it
uses, and even the underlying OS. Table 4-5 lists attacks that can be launched using vulnerabilities in applications.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 113
table 4-5 Attacks based on application vulnerabilities
Attack Description Defense
Executable files Trick the vulnerable application into Prevent the application from creating or
attack modifying or creating executable files on the modifying executable files for its proper
system function
System tampering Use the vulnerable application to modify Do not allow applications to modify special
special sensitive areas of the operating areas of the OS
system (Microsoft Windows registry keys,
system startup files, etc.) and take advantage
of those modifications
Process spawning Trick the vulnerable application into Take away the process spawning ability from
control spawning executable files on the system the application
One particularly dangerous attack can be the result of a vulnerability in an application. The root directory is a
specific directory on a web server’s file system, and users who access the server are usually restricted to the root
directory and directories and files beneath the root directory, but they cannot access other directories. For example,
the default root directory of Microsoft’s Internet Information Services (IIS) web server is C:\Inetpub\wwwroot. Users
have access to this directory and subdirectories beneath this root (C:\Inetpub\wwwroot\news) if given permission,
but they do not have access to other directories in the file system, such as C:\Windows\System32. A directory tra-
versal attack takes advantage of vulnerability in the web application program or the web server software so that a
user can move from the root directory to other restricted directories. The ability to
move to another directory could allow an unauthorized user to view confidential
notE 23
files or even enter commands to execute on a server known as command injection. A
directory traversal attack is illustrated in Figure 4-10. Other dangerous weaknesses
Buffer overflow, integer over-
in an application can create vulnerabilities in computer memory or buffer areas that
flow, pointer/object derefer-
can be easily exploited. These poor memory management vulnerabilities result in
ence, and DLL injection attacks
attacks such as buffer overflow, integer overflow, pointer/object deference, and DLL
are all covered in Module 3.
injection attacks.
C:\
Windows
System32
Inetpub
wwwroot
news
Attacker’s path to
restricted directory
Figure 4-10 Directory traversal attack
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

114 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
The cause of most unsecure applications is usually the result of how the application was designed and written.
Creating and developing secure software involves understanding application development concepts, secure coding
techniques, and code testing.
application development concepts
The two levels of application development concepts include general concepts that apply to all application development
and those that apply to a more rigorous security-based approach.
general concepts
Developing an application requires completing several stages. These stages include the following:
• Development. At the development stage, the requirements for the application are established, and it is con-
firmed that the application meets the intended business needs before the actual coding begins.
• Testing. The testing stage thoroughly tests the application for any errors that could result in a security
vulnerability.
• Staging. The staging stage tests to verify that the code functions as intended.
• Production. In the production stage the application is released to be used in its actual setting.
Often application development will involve software diversity. Software diversity is a software development
technique in which two or more functionally identical variants of a program are developed from the same specification
but by different programmers or programming teams. The intent is to provide error detection, increased reliability,
and additional documentation. It also can reduce the probability that errors created by different compilers, which are
programs that create binary machine code from human source code, will influence the end results.
Another concept regarding application development involves how the completed application will be used in the
context of the larger IT footprint of the enterprise. Provisioning is the enterprise-wide configuration, deployment, and
management of multiple types of IT system resources, of which the new application would be viewed as a new resource.
deprovisioning in application development is removing a resource that is no longer needed.
Integrity measurement is an “attestation mechanism” designed to be able to convince a remote party (external
to the coding team) that an application is running only a set of known and approved executables. Whenever a file is
called in an executable mode, such as when a program is invoked or a sharable library is mapped, the integrity mea-
surement tool generates a unique digital value of that file. On request, the tool can produce a list of all programs run
and their corresponding digital values. This list can then be examined to ensure that no unknown or known vulnerable
applications have been run.
Secdevops
An application development lifecycle model is a conceptual model that describes the stages involved in creating an
application. Most projects use one of two major application development lifecycle models.
The waterfall model uses a sequential design process: as each stage is fully completed, the developers move on to
the next stage. This means that once a stage is finished, developers cannot go back to a previous stage without starting
all over again. For example, in the waterfall model, quality assurance (QA)—verification of quality—occurs only after
the application has been tested and before it is finally placed in production. However, this makes any issues uncovered
by QA difficult to address since it is at the end of the process. The waterfall model demands extensive planning in the
very beginning and requires that it be followed carefully.
The agile model was designed to overcome the disadvantages of the waterfall model. Instead of following a rigid
sequential design process, the agile model takes an incremental approach. Developers might start with a simplistic
project design and begin to work on small modules. The work on these modules is done in short (weekly or monthly)
“sprints,” and at the end of each sprint, the project’s priorities are again evaluated as tests are being run. This approach
allows for software issues to be incrementally discovered so that feedback and changes can be incorporated into the
design before the next sprint is started.
One specific type of software methodology that follows the agile model and heavily incorporates secure coding
practices and techniques to create secure software applications is called SecDevOps. SecDevOps (also known as
DevSecOps and DevOpsSec) is the process of integrating secure development best practices and methodologies
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 115
into application software development and deployment processes using the agile model. It is a set of best practices
designed to help organizations implant secure coding deep in the heart of their applications.
SecDevOps is often promoted in terms of its elasticity (flexibility or resilience in code development) and its
s calability (expandability from small projects to very large projects). However, the cornerstone of SecDevOps is
automation. With standard application development, security teams often find themselves stuck with time-consuming
manual tasks. SecDevOps, on the other hand, applies what is called automated courses of action to develop the code
as quickly and securely as possible. This automation enables continuous monitoring (examining the processes in real
time instead of at the end of a stage), continuous validation (ongoing approvals of the code), continuous integration
(ensuring that security features are incorporated at each stage), continuous delivery (moving the code to each stage
as it is completed), and continuous deployment (continual code implementation).
notE 24
The SecDevOps methodology also includes concepts such as immutable systems (once a value or configuration is employed
as part of an application, it is not modified; if changes are necessary, a new system must be created), infrastructure as
code (managing a hardware and software infrastructure using the same principles as developing computer code), and
baselining (creating a starting point for comparison purposes in order to apply targets and goals to measure success).
Table 4-6 lists sources of recommendations for SecDevOps.
table 4-6 Secure SDLC sources
Source Description Materials available
OwASP (Open web Application A group that monitors web attacks Maturity models, development
Security Project) guides, testing guides, code review
guides, and application security
verification standards
SANS (SysAdmin, Audit, Network and A company that specializes in White papers, research reports, and
Security Institute) cybersecurity and secure web best practices guidelines
application development
CIS (Center for Internet Security) Not-for-profit organization that Training, assessment tools, and
compiles CIS security controls consulting services
Because SecDevOps is based on the agile method, it involves continuous modifications throughout the process.
With these continual changes, it is important to use tools that support change management or creating a plan for docu-
menting changes to the application. One tool for change management is version control software that allows changes
to be automatically recorded and, if necessary, “rolled back” to a previous version of the software.
Secure coding techniques
Several coding techniques should be used to create secure applications and limit
data exposure or disclosing sensitive data to attackers. These techniques include
determining how encryption will be implemented and ensuring that memory man-
agement is handled correctly so as not to introduce memory vulnerabilities. Other
notE 25
techniques are summarized in Table 4-7.
Edsger W. Dijkstra, a famous
code testing
software engineer, once
said, “Program testing can be
Testing is one of the most important steps in SecDevOps. Instead of testing only after
used to show the presence of
the application is completed, testing should be performed much earlier during the
bugs, but never to show their
implementation and verification phases of a software development process. Testing
absence!”
involves static code analysis and dynamic code analysis.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

116 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
table 4-7 Secure coding techniques
Coding technique Description Security advantage
Proper input validation Accounting for errors such as incorrect Can prevent Cross-site scripting (XSS)
user input (entering a file name for a file and Cross-site request forgery (CSRF)
that does not exist). attacks
Normalization Organizing data within a database to Reduces footprint of data exposed to
minimize redundancy. attackers
Stored procedure A subroutine available to applications that Eliminates the need to write a subroutine
access a relational database. that could have vulnerabilities
Code signing Digitally signing applications. Confirms the software author and
guarantees the code has not been
altered or corrupted
Obfuscation/ Writing an application in such a way that Helps prevent an attacker from
camouflaged code its inner functionality is difficult for an understanding a program’s function
outsider to understand.
dead code A section of an application that executes Provides an unnecessary attack vector
but performs no meaningful function. for attackers
Server-side execution Input validation generally uses the server Adds another validation to the process
and validation or Client- to perform validation but can also have
side execution and the client perform validation by the user’s
validation web browser.
Code reuse of third-party Code reuse is using existing software in a Existing libraries that have already been
libraries and Sdks new application; a software development vetted as secure eliminate the need to
kit (SDK) is a set of tools used to write write new code
applications.
Static code analysis
Analysis and testing of the software should occur from a security perspective before the source code is even compiled.
These tests are called static code analysis. Figure 4-11 illustrates an automated static code analysis tool.
Automated static code analysis may also be accompanied by manual peer reviews. In these reviews, software
engineers and developers are paired together or grouped in larger teams to laboriously examine each line of source
code, looking for vulnerabilities.
dynamic code analysis
Security testing should also be performed after the source code is compiled (a process called dynamic code analysis
or run-time verification) and when all components are integrated and running. This testing typically uses a tool or suite
of pre-built attacks or testing tools that specifically monitor the application’s behavior for memory corruption, user
privilege issues, and other critical security problems.
Some of the most common dynamic code analysis tools use a process called fuzzing. Fuzzing provides random
input to a program in an attempt to trigger exceptions, such as memory corruption, program crashes, or security
breaches. An advantage of fuzzing is that it produces a record of what input triggered the exception so it can be repro-
duced to track down the problem within the code. Fuzzing test software consists of an execution engine and an input
generator, which usually allows the tester to configure the types of inputs (see Figure 4-12).
Caution A single pass of a fuzzer is unlikely to find all exceptions in software due to the randomness in the
fuzzing process. The mutation of the inputs relies on randomness to determine where to mutate
input and what to mutate. Fuzzers require multiple trials and statistical tests.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Figure 4-11 Automated static code analysis tool
two rights & a wrong
1. A goal of software diversity is to reduce the probability that errors created by different compilers will
influence the end results.
2. Provisioning is removing a resource that is no longer needed.
3. SecDevOps has elasticity and scalability.
See Appendix B for the answer.
VM Lab You’re now ready to complete the live virtual machine labs for this module. The labs can be
found in each module in the MindTap.
hceTammarG
:ecruoS
Module 4 endPoint and aPPlication develoPMent Security 117
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Figure 4-12 Fuzzer input generator
Summary
• Organizations are pooling their experiences and knowledge gained about the latest attacks with the broader
security community because sharing this type of information has become an important aid to help other orga-
nizations shore up their defenses. Open source threat intelligence information that is freely available, often
called open source intelligence (OSINT), has become a vital resource. This information is often collected and
then disseminated through public information sharing centers. The two concerns around public information
sharing centers are the privacy of shared information and the speed at which the information is shared. Closed
source is the opposite of open source. Organizations that are participants in closed source information are
part of private information sharing centers that restrict both access to data and participation.
• Several sources of threat intelligence are useful. A vulnerability database is a repository of known vulner-
abilities and information as to how they have been exploited. These databases create “feeds” of the latest
cybersecurity incidences. A cybersecurity threat map illustrates cyberthreats overlaid on a diagrammatic
representation of a geographical area. Threat maps help in visualizing attacks and provide a limited amount of
context of the source and the target countries, the attack types, and historical and near real-time data about
threats, although they provide limited valuable information. File and code repositories are used by victims
of an attack who can upload malicious files and software code that can then be examined by others to learn
more about these attacks and craft their defenses. The dark web is the domain of threat actors and beyond
the reach of a normal search engine. Malicious activity such as selling drugs and stolen personal information
and buying and selling malicious software used for attacks occurs on the dark web. Some security profession-
als and organizations use the dark web on a limited basis to look for signs that information critical to that
enterprise is being sought out or sold on the dark web.
erawtfoS
uv
àjéD
:ecruoS
118 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 119
• One of the steps that is often overlooked in securing endpoint computers is to confirm that the computer
has started without any malicious activity taking place. The booting process on early personal computers
used firmware called the BIOS (Basic Input/Output System). Although the ability to update the BIOS firmware
enabled new features to be added, it also opened the door for threat actors to create malware to infect the
BIOS. To combat this vulnerability and add functionality, UEFI (Unified Extensible Firmware Interface) was
developed, in conjunction with the Secure Boot security standard. Several techniques can be used to assure
boot security by taking advantage of the features in UEFI.
• Antivirus (AV) software can examine a computer for any file-based virus infections and monitor computer
activity and scan new documents that might contain a virus. A new approach to AV is dynamic analysis, which
uses a variety of techniques to spot the characteristics of a virus instead of attempting to make matches.
Antimalware is a suite of software intended to provide protections against multiple types of malware, such as
ransomware, cryptomalware, Trojans, spam, and spyware.
• Web browsers have a degree of security that can protect endpoint computers. User-specific informa-
tion stored in a file on the user’s local computer is called a cookie. There are several types of cookies.
As a means of protection for cookies, a web browser can send a secure cookie. This cookie is only sent
to the server with an encrypted request over the secure HTTPS protocol. When a user visits a website
through their web browser, the web server answers back with HTTP Response Headers. These headers
tell the browser how to behave while communicating with the website. Several HTTP Response Headers
can improve security.
• A host intrusion detection system (HIDS) is a software-based application that runs on an endpoint computer
and can detect that an attack has occurred. The primary function of a HIDS is automated detection, which
saves someone from sorting through log files to find an indication of unusual behavior. A HIDS relies on agents
installed directly on the endpoint, and these agents work closely with the OS to observe activity. A host intru-
sion prevention system (HIPS) monitors endpoint activity to immediately react to block a malicious attack
by following specific rules. Activity that a HIPS watches for includes an event that attempts to control other
programs, terminate programs, and install devices and drivers. Endpoint detection and response (EDR) tools
have a similar functionality to HIDS of monitoring endpoint events and of HIPS of taking immediate action.
However, EDR tools are considered more robust than HIDS and HIPS.
• One of the most important steps in securing an endpoint computer is to promptly install patches. Modern
operating systems—such as Red Hat Linux, Apple macOS, Ubuntu Linux, and Microsoft Windows—frequently
distribute patches. A growing number of application and utility software developers are also distributing
patches called third-party updates. An automated patch update service is used to manage patches within the
enterprise instead of relying upon the vendor’s online update service. Early versions of OSs allowed users
to configure how they receive patches; however, today patches are usually automatically downloaded and
installed whenever they become available.
• An unsecure application can open the door for attackers to exploit the application, the data that it uses, and
even the underlying OS. The cause of most unsecure applications is usually the result of how the application
was designed and written. Developing an application requires several stages. An application development
lifecycle model is a conceptual model that describes the stages involved in creating an application. The water-
fall model uses a sequential design process: as each stage is fully completed, the developers move on to the
next stage. The agile model was designed to overcome the disadvantages of the waterfall model. Instead of
following a rigid sequential design process, the agile model takes an incremental approach. One specific type
of software methodology that follows the agile model and heavily incorporates secure coding practices and
techniques to create secure software applications is called SecDevOps. Several coding techniques should be
used to create secure applications and limit data exposure or disclosing sensitive data to attackers. These
techniques include determining how encryption will be implemented and ensuring that memory management
is handled correctly so as to not introduce memory vulnerabilities.
• Testing is one of the most important steps in SecDevOps. Yet, instead of testing only after the application is
completed, testing should be performed much earlier during the implementation and verification phases of a
software development process. Analysis and testing of the software should occur from a security perspective
before the source code is even compiled. These tests are called static code analysis. Security testing should
also be performed after the source code is compiled (a process called dynamic code analysis).
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

120 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
Key terms
| antimalware | disabling unnecessary open ports  | provisioning |
| ----------- | --------------------------------- | ------------ |
antivirus (AV) and services public information sharing centers
application whitelisting/ dynamic code analysis quality assurance (QA)
| blacklisting | elasticity | quarantine |
| ------------ | ---------- | ---------- |
automated courses of action endpoint detection and response  registry
| Automated Indicator Sharing   | (EDR)                            | sandbox                      |
| ----------------------------- | -------------------------------- | ---------------------------- |
| (AIS)                         | file and code repositories       | scalability                  |
| auto-update                   | fuzzing                          | secure coding practices and  |
| binary                        | hardware root of trust           | techniques                   |
| blacklisting                  | host intrusion detection system  | secure cookie                |
| boot attestation              | (HIDS)                           | server-side execution and    |
client-side execution and  host intrusion prevention system  validation
| validation    | (HIPS)                | software diversity |
| ------------- | --------------------- | ------------------ |
| closed source | HTTP Response Headers | staging stage      |
code reuse of third-party libraries  indicator of compromise (IOC) static code analysis
| and SDKs | integrity measurement | stored procedure |
| -------- | --------------------- | ---------------- |
code signing manual peer reviews Structured Threat Information
| compilers             | Measured Boot     | Expression (STIX)   |
| --------------------- | ----------------- | ------------------- |
| continuous delivery   | memory management | testing stage       |
| continuous deployment | normalization     | third-party updates |
continuous integration obfuscation/camouflaged code threat map
continuous monitoring open source Trusted Automated Exchange
continuous validation OWASP (Open Web Application  of Intelligence Information
| dark web | Security Project) | (TAXII) |
| -------- | ----------------- | ------- |
data exposure predictive analysis UEFI (Unified Extensible Firmware
| dead code           | private information sharing  | Interface)             |
| ------------------- | ---------------------------- | ---------------------- |
| deprovisioning      | centers                      | version control        |
| development stage   | production stage             | vulnerability database |
| directory traversal | proper input validation      | whitelisting           |
review Questions
1. An IOC occurs when what metric exceeds its  c. TLP
normal bounds? d. PCII
a. IRR
4. Oskar has been receiving emails about critical
b. LRG
threat intelligence information from a public
c. EXR information sharing center. His team leader has
d. KRI
asked him to look into how the process can
2. What are the two concerns about using public  be automated so that the information can feed
information sharing centers? directly into the team’s technology security. What
a. Cost and availability technology will Oskar recommend?
b. Privacy and speed a. Automated Indicator Sharing (AIS)
c. Security and privacy b. Bidirectional Security Protocol (BSP)
d. Regulatory approval and sharing c. Linefeed Access
d. Lightwire JSON Control
3. Which privacy protection uses four colors
to indicate the expected sharing limitations   5. Which of the following is an application protocol
that are to be applied by recipients of the  for exchanging cyberthreat intelligence over
information? HTTPS?
a. CISA a. STIX
b. FOIA b. AIP-TAR
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 121
c. TAXII 12. Which stage conducts a test that will verify the
d. TCP-Over-Secure (ToP) code functions as intended?
a. Production stage
6. What are the two limitations of private information
b. Testing stage
sharing centers?
c. Staging stage
a. Access to data and participation
d. Development stage
b. Government approval and cost
c. Timing of reports and remote access 13. Which model uses a sequential design process?
d. Bandwidth and CPU a. Secure model
b. Agile model
7. Which of the following is NOT a limitation of a
c. Rigid model
threat map?
d. Waterfall model
a. Many maps claim that they show data in real
time, but most are simply a playback of previous 14. Which of the following is NOT an advantage of an
attacks. automated patch update service?
b. Because threat maps show anonymized data, it is a. Downloading patches from a local server instead of
impossible to know the identity of the attackers or using the vendor’s online update service can save
the victims. bandwidth and time because each computer does
c. They can be difficult to visualize. not have to connect to an external server.
d. Threat actors usually mask their real locations, so b. Administrators can approve updates for “detection”
what is displayed on a threat map is incorrect. only; this allows them to see which computers
require the update without installing it.
8. Luka has been asked by his supervisor to monitor
c. Users can disable or circumvent updates just as
the dark web for any IOCs concerning their
they can if their computer is configured to use the
organization. The next week, Luca reports that
vendor’s online update service.
he was unable to find anything because looking
d. Administrators can approve or decline updates for
for information on the dark web is different from
client systems, force updates to install by a specific
using the regular web. Which of the following is
date, and obtain reports on what updates each
FALSE about looking for information on the dark
computer needs.
web?
a. It is necessary to use Tor or IP2. 15. What type of analysis is heuristic monitoring based on?
b. Dark web search engines are identical to regular a. Dynamic analysis
search engines. b. Static analysis
c. Dark web merchants open and close their sites c. Code analysis
without warning. d. Input analysis
d. The naming structure is different on the dark web.
16. Which of these is a list of preapproved
9. Which of the following is NOT an improvement of applications?
UEFI over BIOS? a. Greenlist
a. Stronger boot security b. Redlist
b. Networking functionality in UEFI c. Blacklist
c. Access larger hard drives d. Whitelist
d. Support of USB 3.0
17. What is the advantage of a secure cookie?
10. Which boot security mode sends information on a. It cannot be stored on the local computer without
the boot process to a remote server? the user’s express permission.
a. UEFI Native Mode b. It is sent to the server over HTTPS.
b. Secure Boot c. It is analyzed by AV before it is transmitted.
c. Trusted Boot d. It only exists in RAM and is deleted once the web
d. Measured Boot browser is closed.
11. Which of the following is NOT an important OS 18. Which of the following tries to detect and stop an
security configuration? attack?
a. Employing least functionality a. HIDS
b. Disabling default accounts b. HIPS
c. Disabling unnecessary services c. RDE
d. Restricting patch management d. SOMA
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

122 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
19. What does Windows 10 Tamper Protection 20. Which of the following is FALSE about a quarantine
do? process?
a. Limits access to the registry. a. It holds a suspicious application until the user gives
b. Prevents any updates to the registry until the approval.
user approves the update. b. It can send a sanitized version of the attachment.
c. Compresses and locks the registry. c. It can send a URL to the document that is on a
d. Creates a secure backup copy of the restricted computer.
registry. d. It is most often used with email attachments.
hands-on Projects
Caution If you are concerned about installing any of the software in these projects on your regular
computer, you can instead install the software in the Windows in the Microsoft Sandbox or
a virtual machine created in the Module 1 Hands-On Projects. Software installed within the
virtual machine will not impact the host computer.
project 4-1: using the microsoft online Security Bulletins
Time required: 20 minutes
Objective: Explain different threat actors, vectors, and intelligence sources.
description: Microsoft has made its security bulletins available in a searchable online database. All security
professionals need to be familiar with using this database. In this project, you will explore the online database.
1. Open your web browser and enter the URL portal.msrc.microsoft.com/en-us/. (The location of content on the
Internet may change without warning. If you are no longer able to access the program through this URL, use a
search engine to search for “Microsoft Security Response Center.”)
2. Click read the Security update Guide FAQ.
3. Click expand all to read through the information.
4. Click the link www.icasi.org/cvrf/ (or enter it into another tab in your browser). What is the Common
Vulnerability Reporting Framework (CVRF)? How is it used?
5. Return to the Microsoft Security Update Guide and then the MSRC main page.
6. Click the Go to the Security update Guide button.
7. If no security updates appear, adjust the From date to the first day of the previous month.
8. Scroll through the list of security updates.
9. Click the first link under Article.
10. Read through this information.
11. Now return to the previous page and select another article to read.
12. How useful is this information? Is it presented in a format that is helpful?
13. Now click the CVE link under details and read this information. Note the detail of this information.
14. Read the information under exploitability Assessment (if the exploit you selected does not list an Exploitability
Assessment, then select another that does include the assessment). What does this mean? Open another tab on
your web browser, and search for Microsoft exploitability Index. Read through the description that you find
and keep this tab open.
15. Return to the Microsoft Security Update Guide and view the exploitability Assessment. How serious is this
security vulnerability?
16. How important is this information to a security professional? How easy is this online database to use?
17. Now compare the Microsoft database with Apple’s. Enter the URL support.apple.com/en-us/HT201222. (The
location of content on the Internet may change without warning. If you are no longer able to access the program
through the above URL, use a search engine to search for “Apple Security Updates.”)
18. Scroll down through the list of Apple security updates. How does this list compare with the updates from Microsoft?
19. Select a recent event under Name and information link.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 123
20. Read the information about the update. How does this information compare with Microsoft’s information? Why
is there such a difference? Which provides better information for security professions?
21. Close all windows.
project 4-2: Setting Windows local Security policy
Time required: 20 minutes
Objective: Given a scenario, implement host or application security solutions.
description: The Local Group Policy Editor is a Microsoft Management Console (MMC) snap-in that gives a single user
interface through which all the Computer Configuration and User Configuration settings of Local Group Policy objects
can be managed. The Local Security Policy settings are among the security settings contained in the Local Group
Policy Editor. An administrator can use these to set policies that are applied to the computer. In this project, you will
view and change local security policy settings.
Caution
You will need to be an administrator to open the Local Group Policy Editor.
1. Click Start.
2. Type secpol.msc into the Search box, and then click secpol.
notE 26
If your computer is already joined to a domain then searching for secpol.msc might not launch the application. If this
is the case, click Start and type mmc.msc. On the File menu, click Add/remove snap-in, and then click Add. In Add
Standalone Snap-in, double-click Group Policy Object editor.
3. First create a policy regarding passwords. Expand Account Policies in the left pane, and then expand Password Policy.
4. Double-click enforce password history in the right pane. This setting defines how many previously used
passwords Windows will record. This prevents users from “recycling” old passwords.
5. Change passwords remembered to 4.
6. Click Ok.
7. Double-click Maximum password age in the right pane. The default value is 42, meaning that a user must
change his password after 42 days.
8. Change days to 30.
9. Click Ok.
10. Double-click Minimum password length in the right pane. The default value is a length of eight characters.
11. Change characters to 10.
12. Click Ok.
13. Double-click Password must meet complexity requirements in the right pane. This setting forces a password
to include at least two opposite case letters, a number, and a special character (such as a punctuation mark).
14. Click enabled.
15. Click Ok.
16. Double-click Store passwords using reversible encryption in the right pane. Because passwords should be
stored in an encrypted format, this setting should not be enabled.
17. If necessary, click disabled.
18. Click Ok.
19. In the left pane, click Account lockout policy.
20. Double-click Account lockout threshold in the right pane. This is the number of times that a user can enter an
incorrect password before Windows will lock the account from being accessed. (This prevents an attacker from
attempting to guess the password with unlimited attempts.)
21. Change invalid login attempts to 5.
22. Click Ok.
23. Note that the Local Security Policy suggests changing the Account lockout duration and the reset account
lockout counter after values to 30 minutes.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

124 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
24. Click Ok.
25. Expand local Policies in the left pane, and then click Audit Policy.
26. Double-click Audit account logon events.
27. Check both Success and Failure.
28. Click Ok.
29. Right-click Security Settings in the left pane.
30. Click reload to have these policies applied.
31. Close all windows.
project 4-3: configuring microsoft Windows Security—part 1
Time required: 15 minutes
Objective: Given a scenario, implement host or application security solutions.
description: It is important that security settings be properly configured on a computer in order to protect it. In this
project, you examine several security settings on a Microsoft Windows 10 computer using the Windows interface.
Caution This project shows how to configure Windows security for a personal computer. If this com-
puter is part of a computer lab or office, these settings should not be changed without the
proper permissions.
1. Click Start and Settings.
2. Click update and security.
3. If necessary, click windows update in the left pane.
4. Click Pause updates for 7 days. What warning are you given?
5. Click resume updates.
6. Click view update history.
7. Expand each area and select one update to review. Read through the information on the update. How detailed is
this information?
8. Return to the view update history page.
9. Return to the windows update page.
10. Click Advanced options.
11. Be sure that receive updates for other Microsoft products when you update windows is set to On. This will
allow for updates for Microsoft software such as Office to also be updated.
12. Read the information under Pause updates. Why would you select this option?
13. Click the down arrow under A quality update includes security improvements. It can be deferred for this
many days:. How many days can you defer security updates?
14. Return to the windows update page.
15. In the left pane, click windows Security.
16. Click virus & threat protection.
17. Click Scan options and be sure that Quick scan is selected.
18. Now perform a Quick scan of the most essential files. Click Scan now. Depending upon your system, it may take
several minutes to complete. What was the result of the scan?
19. Return to the Virus & threat protection page. Under virus & threat protection settings, click Manage settings.
20. Read through the details of the options. Are there any that you would change? Why?
21. Close all windows.
project 4-4: configuring microsoft Windows Security—part 2
Time required: 15 minutes
Objective: Given a scenario, implement host or application security solutions.
description: As seen from Project 4-3, Windows security settings are found across several different screens. This can
make it easy to overlook important settings and time consuming to fine-tune the settings, especially when configuring
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

Module 4 endPoint and aPPlication develoPMent Security 125
the Windows Defender virus and threat protection product. A third-party tool called ConfigureDefender provides an
easier interface. In this project, you will download and use the ConfigureDefender product.
notE 27
ConfigureDefender is not installed on the computer but runs as a stand-alone application.
1. Open your web browser and enter the URL github.com/AndyFul/Configuredefender (if you are no longer able
to access the program through the URL, use a search engine to search for “ConfigureDefender”).
2. Find the latest version of ConfigureDefender (the program is compressed in a ZIP file). Click the filename.
3. Click download.
4. After the file has downloaded, unpack it, and then launch the program.
5. Click the Info about defender button to see the computer’s Defender settings. When finished, close the
window.
6. Click the defender Security log button. Read the log file about recent actions. Does anything surprise you?
When finished, close the window.
7. Scroll down and read the different settings. Were you aware that there were so many different options for
Windows Defender?
8. Hover over the deFAulT button and read the information.
9. Now hover over the HIGH button and read the information.
10. Click the HIGH button, and then close the pop-up box.
11. Scroll down through the settings. How much stronger are they than from the Default settings?
12. Now hover over the MAX button and read the information.
13. Click the MAX button, and then close the pop-up box.
14. Scroll down through the settings. How much stronger are they?
15. Finally click either the deFAulT or HIGH button to set your computer at the security level that you choose.
16. How easy is ConfigureDefender to use? Would you recommend it to others?
17. Close all windows.
Case Projects
case project 4-1: av comparison
Select four antivirus products, one of which is a free product, and compare their features. Create a table that lists the fea-
tures. How do they compare with the AV software you currently use? Which would you recommend to others? Why? Create
a report on your research.
case project 4-2: threat maps
Locate four online cybersecurity threat maps. Compare their real-time results. Why are these results different? What type
of information do they provide? How easy or hard are they to use? How could they be used? How should they not be used?
What are the strengths? What are the weaknesses? What recommendations would you make for improving host security?
Write a one-page paper on your analysis.
case project 4-3: application patch management
Select four third-party applications (not OSs) that you frequently use. How does each of them address patch management?
Visit their websites to determine how they alert users to new vulnerabilities. Are the patch management systems adequate?
Should patch management be required of all third-party applications? What are the advantages? What are the disadvan-
tages? Write a one-page paper on your findings.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.

126 COMPTIA SeCurITy+ GuIde TO NeTwOrk SeCurITy FuNdAMeNTAlS
case project 4-4: uEFi
Use the Internet to research UEFI. What are its advantages? What are its disadvantages? What criticisms have been leveled
against it? Do you agree with the criticism? Write a one-page paper on your findings.
case project 4-5: StiX and taXii
Research the Internet to find information on STIX and TAXII. How are they used? What formats do they provide? How widely
are they used? What are their strengths and weaknesses? Write a one-page paper on your findings.
case project 4-6 information Security community Site activity
The Information Security Community Site is an online companion to this textbook. It contains a wide variety of tools, informa-
tion, discussion boards, and other features to assist learners. In order to gain the most benefit from the site, you will need
to set up a free account.
Go to community.cengage.com/infosec2. Post your thoughts about the following: Should the dark web be shut down?
What would be the advantages? What would it take for this to happen? What would threat actors do if it were suddenly
unavailable? Is there any impact on free speech? Does free speech protect criminal enterprises? What do you think?
case project 4-7 north ridge Security
North Ridge Security provides security consulting and assurance services. You have recently been hired as an intern to assist
this organization.
You have been asked to prepare a presentation on SecDevOps for a group of students studying programming at a
local college.
1. Create a PowerPoint presentation on SecDevOps, how it compares to standard application development, how it is
different, and how it works. Your presentation should be at least seven slides in length.
2. As a follow-up to your presentation, you have been asked to write a one-page report on fuzzing. Use the Internet to
research fuzzing, how it can be used, its strengths and weaknesses, and your recommendations.
references
1. Porter, Jon, “The PC market just had its first year of growth since 2011,” The Verge,
Jan. 14, 2020, retrieved May 20, 2020, www.theverge.com/2020/1/14/21065100/
pc-market-shipments-idc-gartner-growth-2019-laptops-desktops-windows-7-10.
2. O’Dea, S., “Number of smartphone unit shipments In the United States from 2013 to 2023
(In millions),” Statista, Feb. 27, 2020, retrieved May 20, 2020, www.statista.com/statistics/619811/
smartphone-unit-shipments-in-the-us/.
3. Horowitz, Michael, “The head of NSA TAO advises on defensive computing for networks,” Computerworld,
Feb. 1, 2016, accessed May 11, 2017, www.computerworld.com/article/3028025/security/defending-a-
network-from-the-nsa.html.
Copyright 2022 Cengage Learning. All Rights Reserved. May not be copied, scanned, or duplicated, in whole or in part. Due to electronic rights, some third party content may be suppressed from the eBook and/or eChapter(s).
Editorial review has deemed that any suppressed content does not materially affect the overall learning experience. Cengage Learning reserves the right to remove additional content at any time if subsequent rights restrictions require it.