#include "private_vents.h"

class button_commands {
public:
    /// @brief Constructor for button_commands
    /// @param bot Pointer to bot object
    /// @param private_vents Pointer to private_vents object
    button_commands(dpp::cluster *bot, ::private_vents *private_vents);

    /// @brief Determines which function to call when a button is clicked
    /// @param event Event trigger with command info
    void on_button_command(const dpp::button_click_t &event);

private:
    dpp::cluster *bot;
    ::private_vents *private_vents;

    /// @brief Deletes the anonymous vent specified in the button's id
    /// @param event Event trigger with command info
    void delete_vent(const dpp::button_click_t &event);

    /// @brief Sends a message to the DM requester that their request was accepted
    /// @param event Event trigger with command info
    void accept_dm(const dpp::button_click_t &event);
    
    /// @brief Sends a message to the DM requester that their request was denied
    /// @param event Event trigger with command info
    void reject_dm(const dpp::button_click_t &event);
};