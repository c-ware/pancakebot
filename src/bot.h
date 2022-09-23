#ifndef BOT_H
#define BOT_H

#include "libc99/libc99.h"

/* Empty forward reference to Concord's struct discord_emoji */
struct discord_emoji;

/* Tuning parameters */
#define MESSAGE_THRESHOLD           15
#define UNIX_QUOTE_LENGTH_WITH_PS   1024 + 1

#define INIT_VARIABLE(var) \
    memset(&(var), 0, sizeof((var)))

/* A container for stuff that PancakeBot uses. */
struct PancakeBot {
    int message_cooldown;
    struct discord_emoji *pancakes_emoji;
};

/* Fun UNIX quotes from the UNIX Haters Handbook */
static const char *unix_quotes[] = {
    "Two of the most famous products of Berkeley are LSD and Unix. I don't think that is a coincidence.",
    "UNIX: The World's First Computer Virus",
    "Don't Talk to Me, I'm Not a Typewriter!",
    "Not having sendmail is like not having VD.",
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
    "sra@mintaka> man 8 local\nBut what do you want from section local?",
    "Why does the user guide bear no relationship to reality?",
    "For Programmers, Not Users",
    "The Source Code Is the Documentation",
    "Sendmail: The Vietnam of Berkeley Unix",
    "STEP 4: Put the mail into the correct mailbox. Don't you wish?",
    ">From Unix, with Love",
    "I Post, Therefore I Am",
    "Netnews and Usenet: Anarchy Through Growth",
    "Curses! Foiled Again!",
    "X: The Nongraphical GUI",
    "Ice Cube: The Lethal Weapon",
    "What it does give me, however, is a unique pleasure. The overlay plane is used for /dev/console, which means all console messages get printed in 10 Point Troglodyte Bold, superimposed in white over whatever else is on my screen."
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
    "Myth: X Is 'Portable' -- And Iran-Contra wasn't Arms for Hostages",
    "X: the display from hell",
};

/* The rest of the functions. First, handlers: */
void new_message(struct discord *client, const struct discord_message *event);
void unix_handler(struct discord *client, const struct discord_message *event);
void meow_handler(struct discord *client, const struct discord_message *event);
void unix_handler_abs(struct discord *client, const struct discord_message *event);
void pancakes_handler(struct discord *client, const struct discord_message *event);

/* Finally, utility functions: */
struct discord_emoji *load_emoji(struct discord *client, u64snowflake guild_id,
u64snowflake emoji_id);

#endif
