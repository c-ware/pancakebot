#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <concord/discord.h>
#include <concord/discord-internal.h>

#include "bot.h"

/* This will get called when someone says PANCAKES or HOTCAKES */
void pancakes_handler(struct discord *client, const struct discord_message *event) {
    struct discord_ret ret;

    INIT_VARIABLE(ret);

    /* Pancakes emoji; drop a reaction. */
    discord_create_reaction(client, event->channel_id, event->id, 0, "\U0001f95e", &ret);
}


void unix_handler_abs(struct discord *client, const struct discord_message *event) {
    int written = 0;
    const char *quote = NULL;
    char message[UNIX_QUOTE_LENGTH_WITH_PS + 1];
    struct discord_ret_message ret;
    struct discord_create_message params;
    struct PancakeBot *pancake_bot = discord_get_data(client);

    /* No bot fun */
    if(event->author->bot == 1)
        return;

    INIT_VARIABLE(ret);
    INIT_VARIABLE(params);

    params.content = message;
    params.message_reference = event->message_reference;
    quote = unix_quotes[rand() % (sizeof(unix_quotes) / sizeof(char *))];
    written = libc99_snprintf(message, UNIX_QUOTE_LENGTH_WITH_PS, "`%s`\n-- The UNIX Haters Handbook", quote);

    /* Make sure the written quote did not overflow */
    if(written >= UNIX_QUOTE_LENGTH_WITH_PS) {
        fprintf(stderr, "pancake-bot: quote '%s' caused overflow in buffer\n", quote);
        abort();
    }

    pancake_bot->message_cooldown++;
    discord_create_message(client, event->channel_id, &params, &ret);
}

void meow_handler(struct discord *client, const struct discord_message *event) {
    int written = 0;
    struct discord_ret_message ret;
    struct discord_create_message params;
    struct PancakeBot *pancake_bot = discord_get_data(client);

    /* No bot fun */
    if(event->author->bot == 1)
        return;

    /* Only send a UHH quote every N messages */
    if(pancake_bot->message_cooldown != 0) {
        pancake_bot->message_cooldown = ((pancake_bot->message_cooldown + 1) % MESSAGE_THRESHOLD);
        
        return;
    }

    INIT_VARIABLE(ret);
    INIT_VARIABLE(params);

    params.content = "I'm not a cat!";
    params.message_reference = event->message_reference;

    pancake_bot->message_cooldown++;
    discord_create_message(client, event->channel_id, &params, &ret);
}


void unix_handler(struct discord *client, const struct discord_message *event) {
    int written = 0;
    const char *quote = NULL;
    char message[UNIX_QUOTE_LENGTH_WITH_PS + 1];
    struct discord_ret_message ret;
    struct discord_create_message params;
    struct PancakeBot *pancake_bot = discord_get_data(client);

    /* No bot fun */
    if(event->author->bot == 1)
        return;

    /* Only send a UHH quote every N messages */
    if(pancake_bot->message_cooldown != 0) {
        pancake_bot->message_cooldown = ((pancake_bot->message_cooldown + 1) % MESSAGE_THRESHOLD);
        
        return;
    }

    INIT_VARIABLE(ret);
    INIT_VARIABLE(params);

    params.content = message;
    params.message_reference = event->message_reference;
    quote = unix_quotes[rand() % ((sizeof(unix_quotes) / sizeof(char *)))];
    written = libc99_snprintf(message, UNIX_QUOTE_LENGTH_WITH_PS, "`%s`\n-- The UNIX Haters Handbook", quote);

    /* Make sure the written quote did not overflow */
    if(written >= UNIX_QUOTE_LENGTH_WITH_PS) {
        fprintf(stderr, "pancake-bot: quote '%s' caused overflow in buffer\n", quote);
        abort();
    }

    pancake_bot->message_cooldown++;
    discord_create_message(client, event->channel_id, &params, &ret);
}


/* This function is the callback that gets called when a message comes in. */
void new_message(struct discord *client, const struct discord_message *event) {
    int index = 0;
    struct PancakeBot *pancake_bot = discord_get_data(client);

    /* Do not trigger our own messages. */
    if(event->author->bot == 1)
        return;

    /* We want case insensitive pancakes (and UNIX quotes :^)) */
    for(index = 0; event->content[index] != '\0'; index++) {
        if(islower(event->content[index]) == 0)
            continue;

        event->content[index] = toupper(event->content[index]);
    }
    
    /* Meow? */
    if(strstr(event->content, "MEOW") != NULL) {
        meow_handler(client, event);

        return;
    }

    /* Pancakes? */
    if(strstr(event->content, "PANCAKES") != NULL) {
        pancakes_handler(client, event);

        return;
    }

    /* Hotcakes? */
    if(strstr(event->content, "HOTCAKES") != NULL) {
        pancakes_handler(client, event);

        return;
    }

    /* UNIX? */
    if(strstr(event->content, "UNIX") != NULL) {
        unix_handler(client, event);

        return;
    }

    /* Asking for a witty quote? */
    if(strstr(event->content, "&QUOTE") != NULL) {
        unix_handler_abs(client, event);
        return; 
    }

}
