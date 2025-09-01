#pragma once
#include <dpp/dpp.h>
#include <unordered_map>

#include "user_state.h"
class message_events
{
public:
    /// @brief Constructor for messages class
    /// @param bot Pointer to bot object
    /// @param user_states Pointer to hashmap of user_state objects
    message_events(dpp::cluster *bot, std::unordered_map<dpp::snowflake, ::user_state> *user_states);

    /// @brief Handles what happens when a DM is sent to Anoncord 
    /// @param event Event trigger for a message being created
    void on_message_create(dpp::message_create_t event);

private:
    /// @brief Pointer to bot object
    dpp::cluster *bot;
    
    /// @brief user_states Pointer to hashmap of user_state objects
    std::unordered_map<dpp::snowflake, user_state> *user_states;

    /// @brief Send the message to a private vent session
    /// @param event Event trigger with message info
    /// @param user_state User that is being acted on
    void private_vent(dpp::message_create_t event, ::user_state user_state);

    /// @brief Send message to be edited
    /// @param event Event trigger with message info
    /// @param user_state User that is being acted on
    void edit_msg(dpp::message_create_t event, ::user_state user_state);
};