#pragma once
#include <dpp/dpp.h>
#include <vector>

#include "private_vent_session.h"

class message_events
{
public:
    /// @brief Constructor for messages class
    /// @param bot Pointer to bot object
    /// @param private_vent_sessions Pointer to vector of private_vent_session objects
    message_events(dpp::cluster *bot, std::vector<private_vent_session> *private_vent_sessions);

    /// @brief Handles what happens when a DM is sent to Anoncord 
    /// @param event Event trigger for a message being created
    void on_message_create(dpp::message_create_t event);

private:
    /// @brief Pointer to bot object
    dpp::cluster *bot;
    
    /// @brief Pointer to vector of private_vent_sessions objects
    std::vector<private_vent_session> *private_vent_sessions;
};