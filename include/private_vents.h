#pragma once
#include <dpp/dpp.h>
#include <vector>
#include "private_vent_session.h"

using namespace std;

class private_vents
{
public:
    /// @brief Constructor for private_vents class
    /// @param bot Pointer to bot object
    private_vents(dpp::cluster *bot, vector<private_vent_session> *private_vent_sessions);

    /// @brief Sends a DM to the specified user asking if they can DM with an anonymous user
    /// @param user_id ID of the user to be DMed
    /// @param anon_user_id ID of the DM requester
    /// @param message Message to send the user to ask them
    void send_dm(dpp::snowflake user_id, dpp::snowflake anon_user_id, string message);

    /// @brief Sends a DM to the dm requester that their request has been accepted
    /// @param user_id ID of the requested user
    /// @param anon_user_id ID of the anonymous user
    void dm_accepted(dpp::snowflake user_id, dpp::snowflake anon_user_id);

    /// @brief Sends a DM to the dm requesters that their request has been denied
    /// @param user_id ID of the requested user
    /// @param anon_user_id ID of the anonymous user
    void dm_rejected(dpp::snowflake user_id, dpp::snowflake anon_user_id);

    /// @brief Get the vector with all the private_vent_session objects
    /// @return Pointer to the vector with all the private_vent_session object
    vector<::private_vent_session>* get_private_vent_sessions();

private:
    /// @brief Pointer to bot object
    dpp::cluster *bot;

    /// @brief Pointed to private_vent_session vector
    vector<::private_vent_session> *private_vent_sessions;

    /// @brief Sends a DM to the anonymous to inform that their DM request was accepted or rejected
    /// @param accepted True if excepted, false if rejected
    /// @param user_id ID of the requested user
    /// @param anon_user_id ID of the anonymous user
    /// @param color Embed's color (use dpp::colors)
    void response_dm(bool accepted, dpp::snowflake user_id, dpp::snowflake anon_user_id, uint32_t color);
};