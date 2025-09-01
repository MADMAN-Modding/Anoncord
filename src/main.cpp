#include <dpp/dpp.h>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "private.h"
#include "user_state.h"

// Event Classes
#include "button_commands.h"
#include "message_events.h"
#include "slash_commands.h"

using namespace std;

const std::string BOT_TOKEN = token;
int main()
{
   dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

   // Hashmap of user_states
   unordered_map<dpp::snowflake, user_state> user_states;

   // Event Objects
   private_vents private_vents(&bot, &user_states);
   button_commands button_commands(&bot, &private_vents);
   message_events message_events(&bot, &user_states);
   slash_commands slash_commands(&bot, &private_vents);

   bot.on_log(dpp::utility::cout_logger());

   // Button commands
   bot.on_button_click([&button_commands](const dpp::button_click_t &event)
                       { button_commands.on_button_command(event); });

   // Slash commands
   bot.on_slashcommand([&slash_commands](const dpp::slashcommand_t &event)
                       { slash_commands.on_slash_command(event); });

   // Message creation
   bot.on_message_create([&message_events](const dpp::message_create_t &event)
                         { message_events.on_message_create(event); });

   bot.on_ready([&bot](const dpp::ready_t &event)
                {
         if (dpp::run_once<struct register_bot_commands>())
         {
            // Makes the commands
            dpp::slashcommand global_anon_command("anon", "Enter a vent to be anonymously sent", bot.me.id);
            global_anon_command.add_option(
                  dpp::command_option(dpp::co_string, "message", "The vent to anonymously send", true)
            );

            dpp::slashcommand dm_command("private_dm", "Anonymously DM a user", bot.me.id);
            dm_command.add_option(dpp::command_option(dpp::co_user, "user", "The user to request to dm", true));
            dm_command.add_option(dpp::command_option(dpp::co_string, "message", "The message request to be made", true));

            dpp::slashcommand end_private_dm_command("end_dm", "End the current private dm", bot.me.id);

            // Creates the commands 
            bot.global_bulk_command_create({global_anon_command, dm_command, end_private_dm_command});
         } });
   bot.start(dpp::st_wait);

   return 0;
}
