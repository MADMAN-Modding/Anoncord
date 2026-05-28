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
}

bool settings::set_preference(dpp::snowflake user_id, setting setting, bool option)
{
    optional<vector<string>> requests = make_alter_request(user_id, setting, option);
    if (!requests.has_value())
        return false;

    for (const string &sql : requests.value())
    {
        char *error_message = nullptr;
        int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
        if (rc != SQLITE_OK)
        {
            cerr << "Error on: " << sql << endl;
            cerr << "Error: " << sqlite3_errmsg(db) << endl;
            sqlite3_free(error_message);
            return false;
        }
        else
        {
            get_user_settings(user_id);
            switch (setting)
            {
            case ::settings::TYPING:
                this->cached_user_settings.at(user_id).typing_notifications = option;
                break;

            case ::settings::PRIVATE_DMS:
                this->cached_user_settings.at(user_id).allow_private_dms = option;
                break;
            }
        }
    }

    return true;
}

bool settings::get_preference(dpp::snowflake user_id, setting setting)
{
    // If user info is not cached, find it and add to cache
    if (this->cached_user_settings.find(user_id) == this->cached_user_settings.end())
    {
        get_user_settings(user_id);
    }

    user_settings settings = this->cached_user_settings.at(user_id);

    switch (setting)
    {
    case ::settings::setting::TYPING:
        return settings.typing_notifications;
    case ::settings::setting::PRIVATE_DMS:
        return settings.allow_private_dms;

    default:
        return false;
    }
}

optional<vector<string>> settings::make_alter_request(dpp::snowflake user_id, setting setting, bool option)
{
    optional<string> string_setting = this->setting_to_string(setting);
    if (!string_setting.has_value())
        return nullopt;

    uint64_t id = static_cast<uint64_t>(user_id);

    return vector<string>{
        format("INSERT OR IGNORE INTO settings (user_id) VALUES ({});", id),
        format("UPDATE settings SET {} = {} WHERE user_id = {};",
               string_setting.value(), static_cast<int>(option), id)};
}

optional<string> settings::setting_to_string(setting setting)
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

void settings::get_user_settings(dpp::snowflake user_id)
{
    uint64_t id = static_cast<uint64_t>(user_id);

    string sql = format("SELECT * FROM settings WHERE user_id = {}", id);

    int rc = sqlite3_exec(this->db, sql.c_str(), [](void *data, int argc, char **argv, char **azColName)
                          {
    ::settings::user_settings user_settings;
    user_settings.user_id = argv[0];
    user_settings.typing_notifications = argv[1] ? (std::string(argv[1]) == "1") : false;;
    user_settings.allow_private_dms = argv[2] ? (std::string(argv[2]) == "1") : false;;

    auto *cache = static_cast<unordered_map<dpp::snowflake, settings::user_settings>*>(data);
    cache->insert_or_assign(user_settings.user_id, user_settings);

    return 0; }, &this->cached_user_settings, NULL);

    // If there was no row found for the user
    if (this->cached_user_settings.find(user_id) == this->cached_user_settings.end())
    {
        uint64_t id = static_cast<uint64_t>(user_id);
        std::string sql = std::format("INSERT OR IGNORE INTO settings (user_id) VALUES ({});", id);
        sqlite3_exec(this->db, sql.c_str(), NULL, NULL, NULL);

        ::settings::user_settings user_settings;
        user_settings.user_id = user_id;

        this->cached_user_settings.insert_or_assign(user_id, user_settings);
    }
}