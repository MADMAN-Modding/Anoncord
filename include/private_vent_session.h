#pragma once
#include <dpp/dpp.h>

class private_vent_session
{
public:
    /// @brief Constructor for private_vent_session class
    /// @param user_id ID of the user helping the venter
    /// @param anon_user_id ID of the venting user
    /// @param dm_inactive_time Timestamp for the last message that was sent
    private_vent_session(dpp::snowflake user_id, dpp::snowflake anon_user_id, u_int64_t dm_inactive_time);

    /// @brief Gets the anon-user's id
    /// @return ID of the venting-user
    dpp::snowflake get_anon_user_id();

    /// @brief Gets the help-user's id
    /// @return ID of the helping-user
    dpp::snowflake get_user_id();

    /// @brief Get's the time the last message was sent
    /// @return Time since the last message was sent in the DM
    dpp::snowflake get_dm_inactive_time();

private:
    /// @brief ID of the user helping the venter
    dpp::snowflake user_id;
    /// @brief ID of the venting user
    dpp::snowflake anon_user_id;
    /// @brief Timestamp for the last message that was sent
    u_int16_t dm_inactive_time;
};