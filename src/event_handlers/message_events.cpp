#include "message_events.h"
#include "utilities.h"
#include "private.h"

message_events::message_events(dpp::cluster *bot, unordered_map<dpp::snowflake, ::user_state> *user_states)
{
    this->bot = bot;
    this->user_states = user_states;
}

void message_events::on_message_create(dpp::message_create_t event)
{
    if (!event.msg.is_dm() || bot_id == event.msg.author.id)
    {
        return;
    }

    dpp::snowflake user_id = event.msg.author.id;

    if (this->user_states->find(user_id) != this->user_states->end())
    {
        ::user_state user_state = this->user_states->at(user_id);
        ::user_state::user_mode mode = user_state.get_user_mode();

        switch (mode)
        {
        case ::user_state::HELPING:
            private_vent(event, user_state);
            return;

        case ::user_state::VENTING:
            private_vent(event, user_state);
            return;

        case ::user_state::EDITING:
            edit_msg(event, user_state);
            return;

        default:
            break;
        }
    }
    event.reply(dpp::message("No current message actions (message edits/private DMs)"));
}

void message_events::private_vent(dpp::message_create_t event, ::user_state user_state)
{
    dpp::message msg = event.msg;

    if (user_state.get_user_mode() == ::user_state::HELPING)
    {
        // Get username of helper
        string user = event.msg.author.username;

        dpp::embed embed = make_embed("Message Recieved from " + user, msg, dpp::colors::green);

        // Send message to anon
        this->bot->direct_message_create(user_state.get_partner_user_id(), embed);
    }
    else
    {
        dpp::embed embed = make_embed("Message recieved from Anon", msg, dpp::colors::blood_red);

        // Send message to helper
        this->bot->direct_message_create(user_state.get_partner_user_id(), embed);
    }
}

void message_events::edit_msg(dpp::message_create_t event, ::user_state user_state)
{
    string msg = event.msg.content;

    auto user_id = event.msg.author.id;

    ::user_state state = this->user_states->at(user_id);

    dpp::cluster *bot = this->bot;

    this->bot->message_get(state.get_message_id(), state.get_channel_id(), [bot, msg, event](const dpp::confirmation_callback_t &callback)
                    {
	                if (callback.is_error()) {
	                    event.reply("error");
	                    return;
	                }
	                auto message = callback.get<dpp::message>();
	 
                    auto& embeds = message.embeds;

	                /* change the message content and edit the message itself */
                    embeds[0].set_description(msg);


	                bot->message_edit(message);
	                event.reply("Message has been updated to: ```" + msg + "```"); });

    (*user_states)[user_id].set_user_mode(user_state::NONE);
}
