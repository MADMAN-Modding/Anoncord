#include <dpp/dpp.h>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "private.h"
#include "user_state.h"
#include "utilities.h"
#include "settings.h"
#include "pdm_cleaner.h"

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

   // Settings
   ::settings settings;

   // PDM Cleaner
   ::pdm_cleaner pdm_cleaner;

   // Event Objects
   ::private_vents private_vents(&bot, &user_states, &settings);
   ::button_commands button_commands(&bot, &private_vents);
   ::message_events message_events(&bot, &user_states);
   ::slash_commands slash_commands(&bot, &private_vents, &settings, &user_states);

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
         // Makes the commands
         if (dpp::run_once<struct register_bot_commands>())
         {
            dpp::slashcommand anon_vent("anon", "Enter a vent to be anonymously sent", bot.me.id);
            anon_vent.add_option(
                  dpp::command_option(dpp::co_string, "message", "The vent to anonymously send", true)
            );

            dpp::slashcommand private_dm("private_dm", "Anonymously DM a user", bot.me.id);
            private_dm.add_option(dpp::command_option(dpp::co_user, "user", "The user to request to dm", true));
            private_dm.add_option(dpp::command_option(dpp::co_string, "message", "The message request to be made", true));

            dpp::slashcommand end_private_dm_command("end_dm", "End the current private dm", bot.me.id);

            dpp::slashcommand set_typing_option("receive_typing_notifications", "Receive typing notifications while in a private dm", bot.me.id);
            set_typing_option.add_option(dpp::command_option(dpp::co_boolean, "receive_notifications", "True to receive notifications, false to not receive notifications", true));
            
            dpp::slashcommand allow_private_dms("allow_private_dm_requests", "Do you want to allow private dm requests? This defaults to true, disabling requests will not stop you from requesting help", bot.me.id);
            allow_private_dms.add_option(dpp::command_option(dpp::co_boolean, "allow_private_dm_requests", "True to allow receiving requests, false to not allow requests", true));

            // Creates the commands 
            bot.global_bulk_command_create({anon_vent, private_dm, end_private_dm_command, set_typing_option, allow_private_dms});
         } });

   bot.on_typing_start([&bot, &private_vents](const dpp::typing_start_t &event)
                       {
                        if (event.typing_channel.owner_id == 0) {
                           private_vents.typing_dm(event);
                        } });

   thread cleaner(&::pdm_cleaner::start_watch, &pdm_cleaner);

   bot.start(dpp::st_wait);

   return 0;
}
