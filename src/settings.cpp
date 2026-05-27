#include "settings.h"
#include <sqlite3.h>
#include <iostream>
#include <format>

settings::settings()
{
    int exit = 0;
    exit = sqlite3_open("settings.sqlite", &this->db);
    if (exit)
    {
        cerr << "Error open DB " << sqlite3_errmsg(this->db) << endl;
    }
    else
    {
        cout << "Opened Database Successfully!" << endl;
    }
}

bool settings::set_preference(dpp::snowflake user_id, setting setting, bool option)
{
    std::optional<std::vector<std::string>> requests = make_alter_request(user_id, setting, option);
    if (!requests.has_value())
        return false;

    for (const std::string &sql : requests.value())
    {
        char *error_message = nullptr;
        int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Error on: " << sql << std::endl;
            std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_free(error_message);
            return false;
        }
    }

    std::cout << "Preference set successfully" << std::endl;
    return true;
}

std::optional<std::vector<std::string>> settings::make_alter_request(dpp::snowflake user_id, setting setting, bool option)
{
    std::optional<std::string> string_setting = this->setting_to_string(setting);
    if (!string_setting.has_value())
        return std::nullopt;

    uint64_t id = static_cast<uint64_t>(user_id);

    return std::vector<std::string>{
        std::format("INSERT OR IGNORE INTO settings (user_id) VALUES ({});", id),
        std::format("UPDATE settings SET {} = {} WHERE user_id = {};",
                    string_setting.value(), static_cast<int>(option), id)};
}

std::optional<std::string> settings::setting_to_string(setting setting)
{
    switch (setting)
    {
    case setting::TYPING:
        return "typing_notification";
    case setting::PRIVATE_DMS:
        return "allow_private_dms";
    default:
        return "";
    }
}
