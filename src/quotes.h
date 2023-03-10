#ifndef QUOTES_H
#define QUOTES_H

/* Fun UNIX quotes from the UNIX Haters Handbook */
static const char *unix_quotes[] = {
    "Two of the most famous products of Berkeley are LSD and Unix. I don't think that is a coincidence.",
    "UNIX: The World's First Computer Virus",
    "Don't Talk to Me, I'm Not a Typewriter!",
    "Terminal Insanity.. Curses! Foiled Again!",
    "X: The First Fully Modular Software Disaster",
    "Csh, pipes, and find: Power Tools for Power Fools",
    "C++: The COBOL of the 90s",
    "C++ Is to C as Lung Cancer Is to Lung",
    "UNIX is computer-scientology, not computer science.",
    "Superuser: The Superflaw",
    "To Delete Your File, Try the Compiler",
    "% man: why did you get a divorce? \nman:: Too many arguments.",
    "% got a light?\nNo match.",
    "$ mkdir matter; cat >matter\nmatter: cannot create",
    "man was great for its time. But that time has long passed.",
    "No Manual Entry for Well Thought-Out",
    "Why does the user guide bear no relationship to reality?",
    "For Programmers, Not Users",
    "The Source Code Is the Documentation",
    "Sendmail: The Vietnam of Berkeley Unix",
    "STEP 4: Put the mail into the correct mailbox. Don't you wish?",
    ">From Unix, with Love",
    "Curses! Foiled Again!",
    "X: The Nongraphical GUI",
    "X Graphics: Square Peg in a Round Hole",
    "Programming X Windows is like trying to find the square root of pi using roman numerals.",
    "X: On the Road to Nowhere",
    "UNIX: Programming in Plato's Cave",
    "C++: The Assembly Language of Object-Oriented Programming",
    "Security Is Not a Line Printer",
    "Compromised Systems Usually Stay That Way",
    "The File System: Sure It Corrupts Your Files, But Look How Fast It Is!",
    "This Is Internal Documentation?",
    "X Windows is the Iran-Contra of graphical user interfaces.",
    "X has had its share of $5,000 toilet seats.",
    "X Windows is to memory as Ronald Reagan was to money.",
    "If you sacrificed all the RAM from 22 Commodore 64s to clock tool, it still wouldn't have enough to tell you the time.",
    "Years of 'Voodoo Ergonomics' have resulted in an unprecedented memory deficit of gargantuan proportions.",
    "This is the reason that cut-and-paste never works properly with X.",
    "Using these toolkits is like trying to make a bookshelf out of mashed potatoes.",
    "At the mere mention of network window systems, certain propeller heads who confuse technology with economics will start foaming at the mouth about their client/server models and how in the future palmtops will just run the X server and let the other half of the program run on some Cray down the street.",
    "Anybody who has ever used X knows that Chapman's error was trying to use xauth in the first place. He should have known better.",
    "X: the display from hell"
};

static const char* oneshot_quotes[] = {
    "I'm not a cat!",
    "*confused cat noises*",
    "I am not tamed.",
    "Squares are bad news, man.",
    "*glitches out*",
    "Ouch, m-my eyes.",
    "[It was not worth the effort]",
    "[You tried]"
};

static const char* help_text = "PancakeBot\n\nThis bot will randomly dump out quotes from either the UNIX Haters Handbook or a variety of video games, prompted by certain keywords. This bot features some old-style commands:\n&unix - display a UNIX Haters quote\n&oneshot - display a OneShot quote\n&hs - display a Homestuck quote\n&help - display this help text\n";

#endif
