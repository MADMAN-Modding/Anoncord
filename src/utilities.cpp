#include "utilities.h"

dpp::embed makeEmbed(string title, string description,
                              uint32_t color)
{
  dpp::embed embed = dpp::embed();
  embed.set_color(color).set_title(title).set_description(description);

  return embed;
};

dpp::component makeButton(string label, dpp::component_style style,
                                   string id)
{
  dpp::component button;
  button.set_type(dpp::cot_button).set_label(label).set_style(style).set_id(id);

  return button;
}

string strToLower(string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}

vector<string> splitString(const string& str, char delimiter) {
    vector<string> parts;
    size_t start = 0;
    size_t end;

    while ((end = str.find(delimiter, start)) != string::npos) {
        parts.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    parts.push_back(str.substr(start)); // Add last part
    return parts;
}