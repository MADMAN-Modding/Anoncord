#include "message_events.h"
#include "utilities.h"

message_events::message_events(dpp::cluster *bot, std::vector<private_vent_session> *private_vent_sessions)
{
    this->bot = bot;
    this->private_vent_sessions = private_vent_sessions;
}

void message_events::on_message_create(dpp::message_create_t event)
{
    if (!event.msg.is_dm() || dpp::snowflake(1268383421638377612) == event.msg.author.id)
    {
        return;
    }

    dpp::snowflake user_id = event.msg.author.id;

    for (int i = 0; i < this->private_vent_sessions->size(); i++)
    {
        private_vent_session session = this->private_vent_sessions->at(i);

        if (user_id == session.get_user_id())
        {
            // Get the user's message
            dpp::message msg = event.msg;

            dpp::embed embed = make_embed("Message Received from Anon", msg, dpp::colors::blood_red);

            // Send a message to the anon
            this->bot->direct_message_create(session.get_anon_user_id(), embed);
            return;
        }
        else if (user_id == session.get_anon_user_id())
        {
            // Get the anon's message
            dpp::message msg = event.msg;

            string user = event.msg.author.username;

            dpp::snowflake user_id = session.get_user_id();

            dpp::embed embed = make_embed("Message Received from " + user, msg, dpp::colors::green);

            // Send a message to the helper
            bot->direct_message_create(user_id, embed);
            return;
        }
    }

    event.reply(dpp::message("No current private DMs"));
}
