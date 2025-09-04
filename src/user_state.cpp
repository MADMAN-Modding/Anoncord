#include "user_state.h"

user_state::user_state(dpp::snowflake user_id, dpp::snowflake partner_user_id, user_mode mode)
{
    this->user_id = user_id;
    this->partner_user_id = partner_user_id;
    this->mode = mode;
}

user_state::user_state(dpp::snowflake user_id, dpp::snowflake partner_user_id, user_mode mode, dpp::snowflake message_id, dpp::snowflake channel_id)
{
    this->user_id = user_id;
    this->partner_user_id = partner_user_id;
    this->mode = mode;
    this->message_id = message_id;
    this->channel_id = channel_id;
}

dpp::snowflake user_state::get_user_id()
{
    return this->user_id;
}

dpp::snowflake user_state::get_partner_user_id()
{
    return this->partner_user_id;
}

user_state::user_mode user_state::get_user_mode()
{
    return this->mode;
}

dpp::snowflake user_state::get_message_id()
{
    return this->message_id;
}

dpp::snowflake user_state::get_channel_id()
{
    return this->channel_id;
}

void user_state::set_user_mode(user_mode mode)
{
    this->mode = mode;
}
