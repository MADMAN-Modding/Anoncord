#include <dpp/dpp.h>
#include "include/private.hpp"
#include <iostream>
#include "private_vents.cpp"

using namespace std;

const std::string BOT_TOKEN = token;
int main()
{
   dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

   PrivateVents privateVents(&bot);


   bot.on_log(dpp::utility::cout_logger());

   bot.on_slashcommand([&bot](const dpp::slashcommand_t &event)
                       {


      string command = event.command.get_command_name();
         if (command == "anon" || command == "guild_anon") {
            string msg = get<string>(event.get_parameter("message"));

            dpp::embed embed = dpp::embed()
               .set_color(dpp::colors::red_blood)
               .set_title("Anonymous vent")
               .set_description(std::get<std::string>(event.get_parameter("message")));

            dpp::message vent = dpp::message(event.command.channel_id, embed);

            bot.message_create(vent, [&bot, event, msg](const dpp::confirmation_callback_t &callback) {
               if (callback.is_error()) {
                  cerr << "Failed to send anonymous vent message: " << callback.get_error().message << endl;
                  return;
               }

               const dpp::message& sent_msg = get<dpp::message>(callback.value);
               dpp::snowflake vent_id = sent_msg.id; // message ID is always a snowflake

               // Ephemeral confirmation
               dpp::message reply_msg("Only you can see this.");
               reply_msg.set_flags(dpp::m_ephemeral);
               event.reply(reply_msg);

               // Direct message with delete button
               dpp::embed direct_embed = dpp::embed()
                  .set_color(dpp::colors::red_blood)
                  .set_title("Anoncord Message Deletion Services")
                  .set_description("If you'd like to delete your vent, use the button below:\n" + msg);

               dpp::component delete_button;
               delete_button.set_type(dpp::cot_button)
                           .set_label("Delete Message")
                           .set_style(dpp::cos_danger)
                           .set_id("delete_" + std::to_string(vent_id) + "_" + std::to_string(event.command.channel_id));

               dpp::message direct_msg;
               direct_msg.add_embed(direct_embed)
                        .add_component(dpp::component().add_component(delete_button));

               bot.direct_message_create(event.command.member.user_id, direct_msg);
            });
   } });

   bot.on_button_click([&bot](const dpp::button_click_t &event)
                       {
      string command = event.custom_id;

      if (command.find("delete") != string::npos) {
         // Find the first underscore
         int split = command.find("_");

         // Find the second underscore
         int split2 = command.find("_", split + 1);

         // Find the message_id from using the splits
         string msg_id = command.substr(split + 1, split2 - split - 1);

         // Find the channel_id from using the splits
         string channel_id = command.substr(split2 + 1);

         // Commenting these for debug purposes
         // cout << "Msg ID: " << msg_id << "\n";
         // cout << "Channel ID: " << channel_id << "\n";

         // Find the message with the given ID and delete it
         bot.message_delete(msg_id, channel_id);

         event.reply("Your anonymous message has been deleted.");
      } });

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
