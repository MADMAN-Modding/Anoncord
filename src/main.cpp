#include <dpp/dpp.h>
#include "private.h"
#include <iostream>
#include "private_vents.h"
#include "utilities.h"

using namespace std;

const std::string BOT_TOKEN = token;
int main()
{
   dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

   PrivateVents privateVents(&bot);



   bot.on_log(dpp::utility::cout_logger());

   bot.on_slashcommand([&bot, &privateVents](const dpp::slashcommand_t &event)
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
   } else if (command == "private_dm") {
      dpp::snowflake userID = get<dpp::snowflake>(event.get_parameter("user"));

      cout << userID << "\n";

      string message = get<string>(event.get_parameter("message"));

      cout << message << "\n";

      dpp::snowflake anonUserID = event.command.member.user_id;
      
      privateVents.sendDM(userID, anonUserID, message);

      dpp::message reply("DM Sent");
      reply.set_flags(dpp::m_ephemeral);

      event.reply(reply);
   } });

   bot.on_button_click([&bot, &privateVents](const dpp::button_click_t &event)
                       {
      string command = event.custom_id;

      if (command.find("delete") != string::npos) {
         // Find all the parts
         vector<string> parts = splitString(command, '_');

         // Find the message_id from using the splits
         string msgID = parts[1];

         // Find the channelID from using the splits
         string channelID = parts[2];

         // Commenting these for debug purposes
         // cout << "Msg ID: " << msgID << "\n";
         // cout << "Channel ID: " << channelID << "\n";

         // Find the message with the given ID and delete it
         bot.message_delete(msgID, channelID);

         event.reply("Your anonymous message has been deleted.");
      } else if (command.find("accept-dm_") != string::npos) {
         // Find all the parts
         vector<string> parts = splitString(command, '_');

         // Find the userID from using the splits
         dpp::snowflake userID = stoull(parts[1]);

         // Find the anonUserID from using the splits
         dpp::snowflake anonUserID = stoull(parts[2]);

         event.reply(dpp::message("DM Accepted").set_flags(dpp::m_ephemeral));

         // Send the message to the anon user that the dm was accepted
         privateVents.dmAccepted(userID, anonUserID);
      } else if (command.find("reject-dm_") != string::npos) {
         // Find all the parts
         vector<string> parts = splitString(command, '_');

         // Find the userID from using the splits
         dpp::snowflake userID = stoull(parts[1]);

         // Find the anonUserID from using the splits
         dpp::snowflake anonUserID = stoull(parts[2]);

         event.reply(dpp::message("DM Rejected").set_flags(dpp::m_ephemeral));

         // Send the message to the anon user that the dm was accepted
         privateVents.dmRejected(userID, anonUserID);
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
