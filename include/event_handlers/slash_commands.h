#pragma once
#include "private_vents.h"
#include "settings.h"

class slash_commands
{
public:
    /// @brief Constructor for slash_commands
    /// @param bot Pointer to bot object
    /// @param private_vents Point to private_vents object
    slash_commands(dpp::cluster *bot, ::private_vents *private_vents_obj, ::settings *settings, std::unordered_map<dpp::snowflake, user_state> *user_states);

    /// @brief Determines which function to call when a slashcommand is received
    /// @param event Event trigger with command info
    void on_slash_command(dpp::slashcommand_t event);

private:
    /// @brief Pointer to bot object
    dpp::cluster *bot;

    /// @brief Pointer to private vents object
    ::private_vents *private_vents;

    /// @brief Point to settings object
    ::settings *settings;

    /// @brief user_states Pointer to hashmap of user_state objects
    std::unordered_map<dpp::snowflake, user_state> *user_states;

    /// @brief Sends an anonymous vent
    /// @param event Event trigger with the command info
    void anon_vent(dpp::slashcommand_t event);

    /// @brief Sends a request to a user for a private dm 
    /// @param event Event trigger with the command info
    void private_dm(dpp::slashcommand_t event);

    /// @brief End a private DM with a user
    /// @param event Event trigger with the command info
    void end_dm(dpp::slashcommand_t event);

    /// @brief Set option for typing being shown in private dms
    /// @param event Event trigger with the command info
    void set_typing_option(dpp::slashcommand_t event);

    /// @brief Set option for allowing private dms
    /// @param event Event trigger with the command info
    void allow_private_dms(dpp::slashcommand_t event);

    /// @brief Set preferences of a user
    /// @param user_id User's ID
    /// @param setting Setting to change
    /// @param option Value to set
    /// @return 
    bool set_preference(dpp::snowflake user_id, ::settings::setting setting, bool option);
};