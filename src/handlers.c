#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <concord/discord.h>
#include <concord/discord-internal.h>

#include "bot.h"
#include "quotes.h"

/* This will get called when someone says PANCAKES or HOTCAKES */
void pancakes_handler(struct discord *client, const struct discord_message *event) {
    struct discord_ret ret;

    INIT_VARIABLE(ret);

    /* Pancakes emoji; drop a reaction. */
    discord_create_reaction(client, event->channel_id, event->id, 0, "\U0001f95e", &ret);
}


void quote_handler(struct discord *client, const struct discord_message *event, 
        const char **which, int decrement) {
    int written = 0;
    int selected_quote = 0;
    int list_length = 0;
    const char *quote = NULL;
    char *from_name;
    char message[QUOTE_LENGTH_WITH_PS + 1];
    struct discord_ret_message ret;
    struct discord_create_message params;
    struct PancakeBot *pancake_bot = discord_get_data(client);

    /* Disallow bot loopbacks */
    if(event->author->bot == 1)
        return;

    /* Only send a quote every N messages, and only if the decrementor is enabled */
    if(decrement == 1) { /* Are we counting UNIX and MEOW? */
        pancake_bot->message_cooldown = pancake_bot->message_cooldown + 1; /* If so, increment the ticker. */
        if(pancake_bot->message_cooldown != MESSAGE_THRESHOLD) { /* Have we ran over the counter? */
                return; /* It's not time to send a message, so, leave now that the counter's been ticked. */
        }
        pancake_bot->message_cooldown = 0; /* If we're still here, zero the counter and send the message. */
    }

    /* Compute the list of the quotes array by hand, and the "from" text */
    /* Weird way to permit the passing of an address and allowing sizeof to work */
    if(which == unix_quotes) {
        list_length = sizeof(unix_quotes); 
        from_name = "-- The UNIX-Haters Handbook";
    }
    else if(which == oneshot_quotes) {
        list_length = sizeof(oneshot_quotes); 
        from_name = "-- Oneshot";
    }
    else if(which == homestuck_quotes) {
        list_length = sizeof(homestuck_quotes);
        from_name = ""; /* Built-in authors */
    }

    /* Zero variables */
    INIT_VARIABLE(ret);
    INIT_VARIABLE(params);

    /* Select a quote */
    params.content = message;
    params.message_reference = event->message_reference;
    selected_quote = rand() % list_length / sizeof(char *);
    quote = which[selected_quote];
    written = snprintf(message, QUOTE_LENGTH_WITH_PS, "`%s`\n%s", quote, from_name);

    /* Make sure the written quote did not overflow */
    if(written >= QUOTE_LENGTH_WITH_PS) {
        fprintf(stderr, "pancake-bot: quote '%s' caused overflow in buffer\n", quote);
        abort();
    }

    discord_create_message(client, event->channel_id, &params, &ret);
}

void help_handler(struct discord *client, const struct discord_message *event) {
    struct discord_ret_message ret;
    struct discord_create_message params;
    struct PancakeBot *pancake_bot = discord_get_data(client);

    /* No bot fun */
    if(event->author->bot == 1)
        return;

    INIT_VARIABLE(ret);
    INIT_VARIABLE(params);

    params.content = (char*)help_text;
    params.message_reference = event->message_reference;

    discord_create_message(client, event->channel_id, &params, &ret);
}


/* This function is the callback that gets called when a message comes in. */
void new_message(struct discord *client, const struct discord_message *event) {
    int index = 0;
    struct PancakeBot *pancake_bot = discord_get_data(client);

    log_info("[MSG] %s#%s on %llu/%llu, %llu: \"%s\"\n", event->author->username, event->author->discriminator, event->guild_id, event->channel_id, event->id, event->content);

    /* Do not trigger our own messages. */
    /* Another check occurs in the message sender function body. */
    if(event->author->bot == 1)
        return;

    /* We want case insensitive pancakes (and UNIX quotes :^)) */
    for(index = 0; event->content[index] != '\0'; index++) {
        if(islower(event->content[index]) == 0)
            continue;
        event->content[index] = toupper(event->content[index]);
    }
    
    /* ------------------------- start of commands --------------------------- */
    /* Asking for a witty quote? */
    if(strcmp(event->content, "&UNIX") == 0) {
        quote_handler(client, event, unix_quotes, 0);
        return; 
    }


    /* Asking for a witty quote of a different source? */
    if(strcmp(event->content, "&ONESHOT") == 0) {
        quote_handler(client, event, oneshot_quotes, 0);
        return; 
    }

    /* Asking for a homestuck quote? */
    if(strcmp(event->content, "&HS") == 0) {
        quote_handler(client, event, homestuck_quotes, 0);
        return; 
    }

    /* Need help? */
    if(strcmp(event->content, "&HELP") == 0) {
        help_handler(client, event);
        return;
    }
    /* ------------------------- end of commands --------------------------- */
    
    /* ------------------------- start of idles --------------------------- */
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
        quote_handler(client, event, unix_quotes, 1);
        return;
    }

    /* Meow? */
    if(strstr(event->content, "MEOW") != NULL) {
        quote_handler(client, event, oneshot_quotes, 1);
        return;
    }
    /* ------------------------- end of idles --------------------------- */
}


void edit_message(struct discord *client, const struct discord_message *event) {
    log_info("[MSG EDIT] %s#%s on %llu/%llu (%llu): %s\n", event->author->username, event->author->discriminator, event->guild_id, event->channel_id, event->id, event->content);
}


void del_message(struct discord *client, const struct discord_message_delete *event) {
    log_info("[MSG DEL] on %llu/%llu: %llu\n", event->guild_id, event->channel_id, event->id);
}


void del_message_bulk(struct discord *client, const struct discord_message_delete_bulk *event) {
    int message;

    log_info("[MSG DEL BULK START] on %llu/%llu:\n", event->guild_id, event->channel_id);
    for(message = 0; message < event->ids->size; message++) {
            log_info("%d: %llu\n", message, event->ids->array[message]);
    }
    log_info("[MSG DEL BULK END]\n");
}
