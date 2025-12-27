#include "slash_commands.h"
#include "utilities.h"

slash_commands::slash_commands(dpp::cluster *bot, ::private_vents *private_vents) {
    this->bot = bot;
    this->private_vents = private_vents;
}

void slash_commands::on_slash_command(dpp::slashcommand_t event)
{
    string command = event.command.get_command_name();

    if (command == "anon")
    {
        anon_vent(event);
    }
    else if (command == "private_dm")
    {
        private_dm(event);
    } else if (command == "end_dm") {
        end_dm(event);
    } else {
        dpp::message reply("Command not found");
        reply.set_flags(dpp::m_ephemeral);

        event.reply(reply);
    }
}

void slash_commands::anon_vent(dpp::slashcommand_t event)
{
    // Get the venter's message
    string msg = get<string>(event.get_parameter("message"));

    // bool jiberish = get<bool>(event.get_parameter("jiberish"));

    // cout << jiberish << "\n";

    // Make the embed for the message
    dpp::embed embed = dpp::embed()
                           .set_color(dpp::colors::red_blood)
                           .set_title("Anonymous vent")
                           .set_description(std::get<std::string>(event.get_parameter("message")));

    // Make the message from the channel_id and embed
    dpp::message vent = dpp::message(event.command.channel_id, embed);

    // Create the message and then send a dm to the user
    this->bot->message_create(vent, [this, event, msg](const dpp::confirmation_callback_t &callback)
                              {                    
                // Error handling
                if (callback.is_error()) {
                    cerr << "Failed to send anonymous vent message: " << callback.get_error().message << endl;
                    return;
                }

                // Get the message that was send
                const dpp::message& sent_msg = get<dpp::message>(callback.value);
                dpp::snowflake vent_id = sent_msg.id;

                // Ephemeral confirmation
                dpp::message reply_msg("Your message has been anonymously sent, check your DMs for message services.");
                reply_msg.set_flags(dpp::m_ephemeral);
                event.reply(reply_msg);

                // Direct message with delete button
                dpp::embed direct_embed = make_embed("Anoncord Message Services", "If you'd like to delete or your vent, use the button below:\n" + msg, dpp::colors::red_blood);

                // Make the delete button
                dpp::component delete_button = make_button("Delete Message", dpp::cos_danger, "delete_" + std::to_string(vent_id) + "_" + std::to_string(event.command.channel_id));
                
                // Make the edit button
                dpp::component edit_button = make_button("Edit Message", dpp::cos_primary, "edit_" + std::to_string(vent_id) + "_" + std::to_string(event.command.channel_id));
                
                // Makes the dm to be sent to the venter
                dpp::message direct_msg;
                direct_msg.add_embed(direct_embed)
                        .add_component(dpp::component().add_component(delete_button).add_component(edit_button));

                // Sends the dm to the venter
                dm_user(bot, event.command.member.user_id, direct_msg); });
}

void slash_commands::private_dm(dpp::slashcommand_t event)
{
    dpp::snowflake user_id = get<dpp::snowflake>(event.get_parameter("user"));

    string message = get<string>(event.get_parameter("message"));

    dpp::snowflake anon_user_id = event.command.member.user_id;
    
    string user = "<@" + to_string(user_id) + ">";

    auto *user_states = this->private_vents->get_user_states();

    if (user_states->find(user_id) != user_states->end()) {
        if (user_states->at(user_id).get_user_mode() != user_state::NONE && user_states->at(anon_user_id).get_user_mode() != ::user_state::NONE) {
            event.reply(dpp::message(user + " is currently occupied.").set_flags(dpp::m_ephemeral));
            return;
        }
    } else if (user_states->find(anon_user_id) != user_states->end() && user_states->at(anon_user_id).get_user_mode() != ::user_state::NONE) {
        event.reply(dpp::message("You are currently doing something, stop editing your message or close your current private vent").set_flags(dpp::m_ephemeral));
        return;
    }

    this->private_vents->send_dm(user_id, anon_user_id, message);

    dpp::message reply("DM Request Sent to " + user + ":\n" + message);
    reply.set_flags(dpp::m_ephemeral);

    event.reply(reply);
}

void slash_commands::end_dm(dpp::slashcommand_t event)
{
    dpp::snowflake user_id = event.command.member.user_id;

    unordered_map<dpp::snowflake, ::user_state> *user_states = this->private_vents->get_user_states();

    if (user_states->find(user_id) != user_states->end()) {
        ::user_state state = user_states->at(user_id);
        
        state.set_user_mode(::user_state::NONE);

        dpp::snowflake partner_id = state.get_partner_user_id();

        (*user_states)[user_id] = state;

        event.reply(dpp::message("DM found, it has been ended").set_flags(dpp::m_ephemeral));
        return;
    }  

    event.reply(dpp::message("No private DM session was found.").set_flags(dpp::m_ephemeral));
}
