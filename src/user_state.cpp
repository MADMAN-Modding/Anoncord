#include "user_state.h"

user_state::user_state(dpp::snowflake user_id, dpp::snowflake partner_user_id, user_mode mode)
{
    this->user_id = user_id;
    this->partner_user_id = partner_user_id;
    this->mode = mode;
}

dpp::snowflake user_state::get_user_id() {
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

void user_state::set_user_mode(user_mode mode)
{
    this->mode = mode;
}
