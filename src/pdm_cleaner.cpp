#include "pdm_cleaner.h"

#include "utilities.h"

#include <thread>
#include <iostream>

void pdm_cleaner::start_watch()
{
    cout << "Starting cleaning thread" << endl;

    watch_loop();
}

void pdm_cleaner::watch_loop()
{
    while (1)
    {
        // Open the database
        open_db(this->db);

        // Check for old dms
        auto old_pdms = find_old_dms();

        // If there are old dms remove them
        if (old_pdms.has_value())
            remove_old(old_pdms.value());

        // Close the DB connection as it is not needed for the desired sleep time
        sqlite3_close(db);

        // Sleep only this thread for the desired sleep time
        this_thread::sleep_for(SLEEP_TIME);
    }
}

void pdm_cleaner::remove_old(vector<int> old_pdms)
{
    const auto time = chrono::high_resolution_clock::now().time_since_epoch();
    
    string query = format("DELETE * FROM private_dms WHERE status = {} OR time <= {}", to_underlying(::private_vents::CLOSED), (time - 60min).count());

    ::pdm_cleaner pdm;

    char *err_msg = nullptr;
    int rc = sqlite3_exec(this->db, query.c_str(), NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        cerr << "SQL Error in remove_old: " << err_msg << endl;
        sqlite3_free(err_msg);
    }
}

optional<vector<int>> pdm_cleaner::find_old_dms()
{
    return optional<vector<int>>();
}