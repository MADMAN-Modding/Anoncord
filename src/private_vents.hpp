#include <dpp/dpp.h>

using namespace std;
using namespace dpp;

class PrivateVents
{
public:
    cluster& bot;

    /// @brief Constructor for PrivateVents class
    /// @param bot Reference to bot object
    PrivateVents(cluster& bot);

    /// @brief Sends a DM to the specified user asking if they can DM with an anonymous user
    /// @param userID ID of the user to be DMed
    /// @param message Message to send the user to ask them
    /// @param bot Reference to the bot object to send DMs
    void sendDM(int userID, string message, cluster& bot);

    /// @brief Sends a DM to the dm requester that their request has been accepted
    /// @param userID ID of the requested user
    /// @param anonUserID ID of the anonymous user
    void dmAccepted(int userID, int anonUserID);

private:
    /// @brief Makes an embed to be sent to the user
    /// @param title Embed's title
    /// @param description Embed's description
    /// @param color Embed's color (use dpp::colors)
    /// @return Embed made from supplied values
    embed makeEmbed(string title, string description, uint32_t color);

    /// @brief Makes a button to be attached to an embed
    /// @param label Button's label
    /// @param style
    /// @param id
    /// @return Button made from supplied values
    component makeButton(string label, component_style style, string id);
};