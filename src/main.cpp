#include <dpp/dpp.h>
#include "private.h"
#include <iostream>
#include "private_vents.h"
#include "slash_commands.h"
#include "button_commands.h"
#include "utilities.h"

using namespace std;

const std::string BOT_TOKEN = token;
int main()
{
   dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

   private_vents private_vents(&bot);
   slash_commands slash_commands(&bot, &private_vents);
   button_commands button_commands(&bot, &private_vents);

   bot.on_log(dpp::utility::cout_logger());

   // Slash commands
   bot.on_slashcommand([&slash_commands](const dpp::slashcommand_t &event)
                       { slash_commands.on_slash_command(event); });

   // Button commands
   bot.on_button_click([&button_commands](const dpp::button_click_t &event)
                       { button_commands.on_button_command(event); });

   bot.on_ready([&bot](const dpp::ready_t &event)
                {
         if (dpp::run_once<struct register_bot_commands>())
         {
            // Makes the commands
            dpp::slashcommand global_anon_command("anon", "Enter a vent to be anonymously sent", bot.me.id);
            global_anon_command.add_option(
                  dpp::command_option(dpp::co_string, "message", "The vent to anonymously send", true)
            );


            dpp::slashcommand guild_anon_command("guild_anon", "Enter a vent to be anonymously snet", bot.me.id);
            guild_anon_command.add_option(
               dpp::command_option(dpp::co_string, "message", "The vent to be anonymously sent", true)
            );


            dpp::slashcommand dm_command("private_dm", "Anonymously DM a user", bot.me.id);
            dm_command.add_option(dpp::command_option(dpp::co_user, "user", "The user to request to dm"));
            dm_command.add_option(dpp::command_option(dpp::co_string, "message", "The message request to be made"));

            // Creates the commands 
            bot.global_bulk_command_create({global_anon_command, dm_command});
            bot.guild_bulk_command_create({guild_anon_command}, 1338708878702940244);
         } });
   bot.start(dpp::st_wait);

   return 0;
}
