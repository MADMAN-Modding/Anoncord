#pragma once
#include <dpp/dpp.h>
#include <sqlite3.h>
#include <optional>

using namespace std;

class settings
{
public:
    struct user_settings
    { 
        dpp::snowflake user_id;
        bool typing_notifications;
        bool allow_private_dms; 
    };

    /// @brief Settings available to set in the database
    enum setting {
        TYPING,
        PRIVATE_DMS
    };

    settings();

    bool set_preference(dpp::snowflake user_id, setting setting, bool option);

private:
    std::optional<std::vector<std::string>> make_alter_request(dpp::snowflake user_id, setting setting, bool option);

    optional<string> setting_to_string(setting setting);

    sqlite3* db;
};