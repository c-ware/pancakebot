#ifndef BOT_H
#define BOT_H

#include "libc99/libc99.h"

/* Empty forward reference to Concord's struct discord_emoji */
struct discord_emoji;

/* Tuning parameters */
#define MESSAGE_THRESHOLD      50
#define QUOTE_LENGTH_WITH_PS   1024 + 1
#define LOG_FILE               "/root/PBlogfile.txt"

/* Assistance macros */
#define INIT_VARIABLE(var) \
    memset(&(var), 0, sizeof((var)))

/* A container for stuff that PancakeBot uses. */
struct PancakeBot {
    int message_cooldown;
    struct discord_emoji *pancakes_emoji;
};

/* The rest of the functions. First, handlers: */
void new_message(struct discord *client, const struct discord_message *event);
void help_handler(struct discord *client, const struct discord_message *event);
void quote_handler(struct discord *client, const struct discord_message *event,
        const char **which, int decrement);
void pancakes_handler(struct discord *client, const struct discord_message *event);
void edit_message(struct discord *client, const struct discord_message *event);
void del_message(struct discord *client, const struct discord_message_delete *event);
void del_message_bulk(struct discord *client, 
        const struct discord_message_delete_bulk *event);
/* void timers_handler(struct discord *client, const struct discord_message *event); */

/* Finally, utility functions: */
struct discord_emoji *load_emoji(struct discord *client, u64snowflake guild_id,
u64snowflake emoji_id);

#endif
