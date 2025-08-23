#include <dpp/dpp.h>

#ifndef PRIVATE_VENTS_HPP
#define PRIVATE_VENTS_HPP

using namespace std;

class PrivateVents
{
public:
    dpp::cluster* bot;

    /// @brief Constructor for PrivateVents class
    /// @param bot Reference to bot object
    PrivateVents(dpp::cluster* bot);

    /// @brief Sends a DM to the specified user asking if they can DM with an anonymous user
    /// @param userID ID of the user to be DMed
    /// @param anonUserID ID of the DM requester
    /// @param message Message to send the user to ask them
    void sendDM(dpp::snowflake userID, dpp::snowflake anonUserID, string message);

    /// @brief Sends a DM to the dm requester that their request has been accepted
    /// @param userID ID of the requested user
    /// @param anonUserID ID of the anonymous user
    void dmAccepted(dpp::snowflake userID, dpp::snowflake anonUserID);

    /// @brief Sends a DM to the dm requesters that their request has been denied
    /// @param userID ID of the requested user
    /// @param anonUserID ID of the anonymous user
    void dmRejected(dpp::snowflake userID, dpp::snowflake anonUserID);

private:
    /// @brief Sends a DM to the anonymous to inform that their DM request was accepted or rejected
    /// @param accepted True if excepted, false if rejected
    /// @param userID ID of the requested user
    /// @param anonUserID ID of the anonymous user
    /// @param color Embed's color (use dpp::colors)
    void responseDM(bool accepted, dpp::snowflake userID, dpp::snowflake anonUserID, uint32_t color);
};

#endif