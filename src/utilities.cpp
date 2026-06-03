#include "utilities.h"
#include <random>
#include <limits>

dpp::embed make_embed(string title, string description,
                      uint32_t color)
{
  dpp::embed embed = dpp::embed();
  embed.set_color(color).set_title(title).set_description(description);

  return embed;
}

dpp::embed make_embed(string title, dpp::message msg, uint32_t color)
{
  string description = msg.to_json()["content"];
  return make_embed(title, description, color);
}

dpp::component make_button(string label, dpp::component_style style,
                           string id)
{
  dpp::component button;
  button.set_type(dpp::cot_button).set_label(label).set_style(style).set_id(id);

  return button;
}

string str_to_lower(string s)
{
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c)
                 { return std::tolower(c); } // correct
  );
  return s;
}

vector<string> split_string(const string &str, char delimiter)
{
  vector<string> parts;
  size_t start = 0;
  size_t end;

  while ((end = str.find(delimiter, start)) != string::npos)
  {
    parts.push_back(str.substr(start, end - start));
    start = end + 1;
  }
  parts.push_back(str.substr(start)); // Add last part
  return parts;
}

void dm_user(dpp::cluster *bot, dpp::snowflake id, dpp::message message)
{
  bot->direct_message_create(id, message);
}

void dm_user(dpp::cluster *bot, dpp::snowflake id, string message)
{
  dm_user(bot, id, dpp::message(message));
}

int open_db(sqlite3 *&db)
{
  int exit = 0;
  exit = sqlite3_open("database.sqlite", &db);
  if (exit)
  {
    cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
  }

  return exit;
}

int64_t gen_pdm_id()
{
  unsigned long seed = std::time(nullptr);
  std::default_random_engine rng(seed);
  std::uniform_int_distribution<long long int> dist(std::numeric_limits<long long int>::min(), std::numeric_limits<long long int>::max());
  return dist(rng);
}
