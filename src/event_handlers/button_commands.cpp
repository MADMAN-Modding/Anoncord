#include "button_commands.h"
#include "utilities.h"

button_commands::button_commands(dpp::cluster *bot, ::private_vents *private_vents) : bot(bot), private_vents(private_vents) {}

void button_commands::on_button_command(const dpp::button_click_t &event)
{
    // Button id
    string command = event.custom_id;

    // Matches the button based on present data
    if (command.find("delete") != string::npos)
    {
        delete_vent(event);
    }
    else if (command.find("accept-dm_"))
    {
        accept_dm(event);
    }
    else if (command.find("reject-dm_"))
    {
        reject_dm(event);
    }
}

void button_commands::delete_vent(const dpp::button_click_t &event)
{
    // Button id
    string command = event.custom_id;

    // Find all the parts
    vector<string> parts = split_string(command, '_');

    // Find the message_id from using the splits
    string msg_id = parts[1];

    // Find the channel_id from using the splits
    string channel_id = parts[2];

    // Find the message with the given ID and delete it
    this->bot->message_delete(msg_id, channel_id);

    event.reply("Your anonymous message has been deleted.");
}

void button_commands::accept_dm(const dpp::button_click_t &event)
{
    // Button id
    string command = event.custom_id;

    // Find all the parts
    vector<string> parts = split_string(command, '_');

    // Find the user_id from using the splits
    dpp::snowflake user_id = stoull(parts[1]);

    // Find the anon_user_id from using the splits
    dpp::snowflake anon_user_id = stoull(parts[2]);

    event.reply(dpp::message("DM Accepted").set_flags(dpp::m_ephemeral));

    // Send the message to the anon user that the dm was accepted
    this->private_vents->dm_accepted(user_id, anon_user_id);
}

void button_commands::reject_dm(const dpp::button_click_t &event)
{
    //Button id
    string command = event.custom_id;
    
    // Find all the parts
    vector<string> parts = split_string(command, '_');

    // Find the user_id from using the splits
    dpp::snowflake user_id = stoull(parts[1]);

    // Find the anon_user_id from using the splits
    dpp::snowflake anon_user_id = stoull(parts[2]);

    event.reply(dpp::message("DM Rejected").set_flags(dpp::m_ephemeral));

    // Send the message to the anon user that the dm was accepted
    this->private_vents->dm_rejected(user_id, anon_user_id);
}
