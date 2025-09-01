<h1>Anoncord</h1>
<p>This bot allows you to send anonymous messages, no filter, no logs, it just spits the message right back out to the channel</p>

<h2>Setup</h2>
<p>One file that you must make is the private.hpp file, stored in include/private.h</p>
<p>Add the following to the file</p>

    #include <iostream>
    #include <dpp/dpp.h>

    static const std::string token = "your_token";

    static const dpp::snowflake bot_id = 0123456789; 