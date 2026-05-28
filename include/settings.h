#pragma once
#include <dpp/dpp.h>
#include <sqlite3.h>
#include <optional>
#include <unordered_map>

#include "user_state.h"

using namespace std;

class settings
{
public:
    struct user_settings
    { 
        dpp::snowflake user_id;
        bool typing_notifications = true;
        bool allow_private_dms = true; 
    };

    /// @brief Settings available to set in the database
    enum setting {
        TYPING,
        PRIVATE_DMS
    };

    /// @brief Opens the database
    settings();

    /// @brief Set a user's preference
    /// @param user_id User ID
    /// @param setting Setting to Modify
    /// @param option Value to Apply
    /// @return True on success
    bool set_preference(dpp::snowflake user_id, setting setting, bool option);

    /// @brief Get a user's preference
    /// @param user_id User ID
    /// @param setting Setting to Get
    /// @return Value of the preference
    bool get_preference(dpp::snowflake user_id, setting setting);

private:
    optional<vector<string>> make_alter_request(dpp::snowflake user_id, setting setting, bool option);

    /// @brief Converts setting enum to string
    /// @param setting Enum value
    /// @return String value
    optional<string> setting_to_string(setting setting);

    /// @brief Get user settings
    /// @param user_id User ID
    /// @return Void, writes to the cached_user_settings map
    void get_user_settings(dpp::snowflake user_id);

    /// DB Pointer
    sqlite3* db;

    /// @brief Pointer to user_state hashmap
    unordered_map<dpp::snowflake, user_settings> cached_user_settings;
};