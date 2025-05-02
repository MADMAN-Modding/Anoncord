#include <dpp/dpp.h>
#include "include/private.hpp"
#include <iostream>

const std::string BOT_TOKEN = token;

class Main
{
public:
   bool hugOk = false;
};

int main()
{
   dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

   dpp::emoji hug("people_hugging");

   bot.on_log(dpp::utility::cout_logger());

   Main main;

   bot.on_slashcommand([&bot](const dpp::slashcommand_t &event)
                       {
      std::string command = event.command.get_command_name();
  
      if (command == "anon") {
         bool hugOk = std::get<bool>(event.get_parameter("hugs"));
         std::string message = std::get<std::string>(event.get_parameter("vent"));
  
         std::cout << std::boolalpha << hugOk << "\n";
         
         dpp::message msg(event.command.channel_id, message);
         
         if (hugOk) {
         bot.message_create(msg, [&bot, event](const dpp::confirmation_callback_t& callback) {
            if (!callback.is_error()) {
                auto sent_message = std::get<dpp::message>(callback.value);

                // Add a reaction (e.g. a thumbs up 🫂)
                bot.message_add_reaction(sent_message.channel_id, sent_message.id, "👍");
            }
        });
      }
         bot.message_create(dpp::message(event.command.channel_id, message));
         event.reply(dpp::message("Anonymous message sent: " + message).set_flags(dpp::m_ephemeral));

      } })
      ;

   bot.on_ready([&bot](const dpp::ready_t &event)
                {
         if (dpp::run_once<struct register_bot_commands>())
         {
            // Makes the commands   
            dpp::slashcommand anon_command("anon", "Enter a message to be anonymously sent", bot.me.id);
            
            // Encoding commands
            anon_command.add_option(
                  dpp::command_option(dpp::co_string, "vent", "The message to anonymously send", true));
            // anon_command.add_option(
            //    dpp::command_option(dpp::co_boolean, "hugs", "Hugs are allowed?", false)
            // );

            bot.global_bulk_command_delete();
            // Creates the commands 
            bot.global_command_create(anon_command);
         }
      });
   bot.start(dpp::st_wait);

   return 0;
}