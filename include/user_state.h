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

    /// @brief Defualt contstructor for user_state class
    user_state() = default;

    /// @brief Constructor for creating a user_state 
    /// @param user_id ID of the user
    /// @param partner_user_id ID of the other user in a vent
    /// @param mode Mode the user is in
    explicit user_state(dpp::snowflake user_id, dpp::snowflake partner_user_id, user_mode mode);
   
    /// @brief Gets the user_id
    /// @return the user_id
    dpp::snowflake get_user_id();

    /// @brief Gets the user_id
    /// @return the user_id
    dpp::snowflake get_partner_user_id();

    /// @brief Gets the mode of the user
    /// @return the mode the user is in
    user_mode get_user_mode();

private:
    /// @brief ID of the user
    dpp::snowflake user_id;

    /// @brief partner_user_id ID of the other user in a vent
    dpp::snowflake partner_user_id;
    
    /// Mode the user is in
    user_mode mode;
};