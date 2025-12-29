#pragma once
#include <dpp/dpp.h>

class user_state
{
public:
    /// @brief Modes the user can be in
    enum user_mode
    {
        /// @brief The user isn't doing anything
        NONE,
        /// @brief The user is editing a message
        EDITING,
        /// @brief The user is helping another user
        HELPING,
        /// @brief The user is venting to a another user
        VENTING
    };

    /// @brief Default constructor for user_state class
    user_state() = default;

    /// @brief Constructor for creating a user_state 
    /// @param user_id ID of the user
    /// @param partner_user_id ID of the other user in a vent
    /// @param mode Mode the user is in
    explicit user_state(dpp::snowflake user_id, dpp::snowflake partner_user_id, user_mode mode);
   
    /// @brief Constructor for creating a user_state with message and channel IDs
    /// @param user_id ID of the user
    /// @param partner_user_id ID of the other user in a vent
    /// @param mode Mode the user is in
    /// @param message_id ID of the message being edited
    /// @param channel_id ID of the channel the message is in
    explicit user_state(dpp::snowflake user_id, dpp::snowflake partner_user_id, user_mode mode, dpp::snowflake message_id, dpp::snowflake channel_id);

    /// @brief Gets the user_id
    /// @return the user_id
    dpp::snowflake get_user_id();

    /// @brief Gets the user_id
    /// @return the user_id
    dpp::snowflake get_partner_user_id();

    /// @brief Gets the mode of the user
    /// @return the mode the user is in
    user_mode get_user_mode();

    dpp::snowflake get_message_id();

    dpp::snowflake get_channel_id();

    void set_user_mode(user_mode mode);

private:
    /// @brief ID of the user
    dpp::snowflake user_id;

    /// @brief partner_user_id ID of the other user in a vent
    dpp::snowflake partner_user_id;
    
    /// @brief Mode the user is in
    user_mode mode;

    /// @brief Message the user is editing
    dpp::snowflake message_id = 0;

    /// @brief Channel the message being editted is in
    dpp::snowflake channel_id = 0;

    /// @brief Does the user want to be notified when the other user is typing (currently stored in RAM, eventually will be in a database)
    bool typing_notify = true;
};