#include "button_commands.h"
#include "utilities.h"

button_commands::button_commands(dpp::cluster *bot, ::private_vents *private_vents)
{
    this->bot = bot;
    this->private_vents = private_vents;
}

void button_commands::on_button_command(const dpp::button_click_t &event)
{
    // Button id
    string command = event.custom_id;

    // Matches the button based on present data
    if (command.find("delete") != string::npos)
    {
        delete_vent(event);
    }
    else if (command.find("edit_") != string::npos)
    {
        edit_vent(event);
    }
    else if (command.find("accept-dm_") != string::npos)
    {
        accept_dm(event);
    }
    else if (command.find("reject-dm_") != string::npos)
    {
        reject_dm(event);
    }
    else
    {
        event.reply(dpp::message(command + " not found").set_flags(dpp::m_ephemeral));
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

void button_commands::edit_vent(const dpp::button_click_t &event)
{
    // Button id
    string command = event.custom_id;

    auto user_id = event.command.member.user_id;

    if (this->private_vents->get_user_states()->find(user_id) != this->private_vents->get_user_states()->end() && this->private_vents->get_user_states()->at(user_id).get_user_mode() == user_state::NONE)
    {
        event.reply(dpp::message("You are currently doing something, stop editing your message or close your current private vent").set_flags(dpp::m_ephemeral));
        return;
    }

    // Find all the parts of the id
    vector<string> parts = split_string(command, '_');

    // Find the message id from using the splits
    string msg_id = parts[1];

    // Find the channel_id from using the splits
    string channel_id = parts[2];

    bot->message_get(msg_id, channel_id, [event](const dpp::confirmation_callback_t &callback)
                     {
	                if (callback.is_error()) {
	                    event.reply("error editing message");
	                    return;
	                }
	                auto message = callback.get<dpp::message>();
	 
                    string message_desription = to_string(message.to_json()["embeds"][0]["description"]);

                    // Trims the leading and tailing parentheses
                    message_desription = message_desription.substr(1, message_desription.length() - 2);

	                event.reply("Your originally message was: ```" + message_desription + "```"); });

    auto user_states = private_vents->get_user_states();

    ::user_state state(user_id, 0, user_state::EDITING, stoull(msg_id), stoull(channel_id));

    (*user_states)[user_id] = state;
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

    if (this->private_vents->get_user_states()->find(user_id) != this->private_vents->get_user_states()->end() && this->private_vents->get_user_states()->at(user_id).get_user_mode() != user_state::NONE)
    {
        event.reply(dpp::message("You are currently doing something, stop editing your message or close your current private vent").set_flags(dpp::m_ephemeral));
        return;
    }

    if (this->private_vents->get_user_states()->find(anon_user_id) != this->private_vents->get_user_states()->end() && this->private_vents->get_user_states()->at(anon_user_id).get_user_mode() != user_state::NONE)
    {
        event.reply(dpp::message("The anonymous user is currently doing something else.").set_flags(dpp::m_ephemeral));
        return;
    }

    // Make a user_state object and then set or add it to the hashmap
    ::user_state user_state(user_id, anon_user_id, ::user_state::HELPING);
    ::user_state anon_user_state(anon_user_id, user_id, ::user_state::VENTING);

    this->private_vents->get_user_states()->insert_or_assign(user_id, user_state);
    this->private_vents->get_user_states()->insert_or_assign(anon_user_id, anon_user_state);

    event.reply(dpp::message("DM Accepted").set_flags(dpp::m_ephemeral));

    // Send the message to the anon user that the dm was accepted
    this->private_vents->dm_accepted(user_id, anon_user_id);
}

void button_commands::reject_dm(const dpp::button_click_t &event)
{
    // Button id
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
