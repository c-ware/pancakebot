#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <concord/discord.h>
#include <concord/discord-internal.h>

#include "bot.h"

struct discord_emoji *load_emoji(struct discord *client, u64snowflake guild_id, u64snowflake emoji_id) {
    struct discord_ret_emoji emoji_settings;
    struct discord_emoji *emoji_buffer = malloc(sizeof(struct discord_emoji));

    INIT_VARIABLE(*emoji_buffer);
    INIT_VARIABLE(emoji_settings);

    emoji_settings.sync = emoji_buffer;
    discord_get_guild_emoji(client, guild_id, emoji_id, &emoji_settings);

    return emoji_buffer;
}

int main(void) {
    struct PancakeBot pancake_bot;
    struct discord *client = discord_config_init("config.json");

    /* Initialize the pancake bot and Discord */
    srand(time(NULL));
    INIT_VARIABLE(pancake_bot);
    discord_set_data(client, &pancake_bot);

    pancake_bot.pancakes_emoji = load_emoji(client, 928763123362578552, 928817847487066144);

    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);
    discord_set_on_message_create(client, new_message);
    discord_run(client);

    discord_cleanup(client);

    return 0;
}
