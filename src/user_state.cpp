#include "user_state.h"

user_state::user_state() {
    this->user_id = 0;
    this->mode = NONE;
}

user_state::user_state(dpp::snowflake user_id, user_mode mode)
{
    this->user_id = user_id;
    this->mode = mode;
}

dpp::snowflake user_state::get_user_id() {
    return this->user_id;
}

user_state::user_mode user_state::get_user_mode()
{
    return this->mode;
}