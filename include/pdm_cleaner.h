#pragma once
#include <sqlite3.h>
#include <vector>
#include <optional>
#include <chrono>

#include "private_vents.h"

#define ms_to_min (1000 * 60)

using namespace std;

class pdm_cleaner {
public:
    /// @brief Row outline for database entries
    struct pdm
    {
        int pdm_id;
        private_vents::pdm_status status;
        long time;
    };

    void start_watch();

private:
    const chrono::minutes SLEEP_TIME = 5min;

    void watch_loop();

    void remove_old(vector<int> old_pdms);

    optional<vector<int>> find_old_dms();

    /// @brief Database pointer
    sqlite3 *db;
};