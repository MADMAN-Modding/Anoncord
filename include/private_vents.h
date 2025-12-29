#pragma once
#include <dpp/dpp.h>
#include <vector>
#include <unordered_map>

#include "user_state.h"

using namespace std;

class private_vents
{
public:
    /// @brief Constructor for private_vents class
    /// @param bot Pointer to bot object
    /// @brief Pointer to user_state hashmap
    private_vents(dpp::cluster *bot, unordered_map<dpp::snowflake, user_state> *user_states);

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

    /// @brief Get the hashmap with all the user_state objects
    /// @return Pointer to hashmap with all the user_state objects
    unordered_map<dpp::snowflake, user_state> *get_user_states();

    /// @brief Update either user if the other is typing
    /// @param event Event of what happened
    void typing_dm(dpp::typing_start_t event);

private:
    /// @brief Pointer to bot object
    dpp::cluster *bot;

    /// @brief Pointer to user_state hashmap
    unordered_map<dpp::snowflake, user_state> *user_states;

    /// @brief Sends a DM to the anonymous to inform that their DM request was accepted or rejected
    /// @param accepted True if excepted, false if rejected
    /// @param user_id ID of the requested user
    /// @param anon_user_id ID of the anonymous user
    /// @param color Embed's color (use dpp::colors)
    void response_dm(bool accepted, dpp::snowflake user_id, dpp::snowflake anon_user_id, uint32_t color);
};