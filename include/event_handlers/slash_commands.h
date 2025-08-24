#include "private_vents.h"

class slash_commands
{
public:
    /// @brief Constructor for slash_commands
    /// @param bot Pointer to bot object
    /// @param private_vents Point to private_vents object
    slash_commands(dpp::cluster *bot, ::private_vents *private_vents_obj);

    /// @brief Determines which function to call when a slashcommand is received
    /// @param event Event trigger with command info
    void on_slash_command(dpp::slashcommand_t event);

private:
    dpp::cluster *bot;
    ::private_vents *private_vents;

    /// @brief Sends an anonymous vent
    /// @param event Event trigger with command info
    void anon_vent(dpp::slashcommand_t event);

    /// @brief Sends a request to a user for a private dm 
    /// @param event Event trigger with command info
    void private_dm(dpp::slashcommand_t event);
}; 