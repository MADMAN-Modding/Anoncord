#include <dpp/dpp.h>
#include "include/private.hpp"
#include <iostream>

const std::string BOT_TOKEN = token;
int main()
{
   dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

   bot.on_log(dpp::utility::cout_logger());

   bot.on_slashcommand([&bot](const dpp::slashcommand_t &event)
      {
      std::string command = event.command.get_command_name();
         if (command == "anon") {
            bot.message_create(dpp::message(event.command.channel_id, std::get<std::string>(event.get_parameter("message"))));
            event.reply(dpp::message("Anonymous message sent: " + std::get<std::string>(event.get_parameter("message"))).set_flags(dpp::m_ephemeral));
         }
      }
   );

   bot.on_ready([&bot](const dpp::ready_t &event)
      {
         if (dpp::run_once<struct register_bot_commands>())
         {
            // Makes the commands
            dpp::slashcommand anon_command("anon", "Enter a message to be anonymously sent", bot.me.id);
            
            // Encoding commands
            anon_command.add_option(
                  dpp::command_option(dpp::co_string, "message", "The message to anonymously send", true));

            bot.global_bulk_command_delete();
            // Creates the commands 
            bot.global_command_create(anon_command);
         }
      });
   bot.start(dpp::st_wait);

   return 0;
}