#include "private_vent_session.h"
#include <chrono>

private_vent_session::private_vent_session(dpp::snowflake anon_user_id, dpp::snowflake user_id, u_int64_t dm_inactive_time)
{
    this->anon_user_id = anon_user_id;
    this->user_id = user_id;
    this->dm_inactive_time = dm_inactive_time;
}

dpp::snowflake private_vent_session::get_anon_user_id()
{
    return this->anon_user_id;
}

dpp::snowflake private_vent_session::get_user_id()
{
    return this->user_id;
}

dpp::snowflake private_vent_session::get_dm_inactive_time()
{
    return this->dm_inactive_time;
}
