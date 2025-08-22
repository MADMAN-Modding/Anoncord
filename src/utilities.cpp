#include "utilities.h"

embed makeEmbed(string title, string description,
                              uint32_t color)
{
  embed embed = dpp::embed();
  embed.set_color(color).set_title(title).set_description(description);

  return embed;
};

component makeButton(string label, dpp::component_style style,
                                   string id)
{
  component button;
  button.set_type(cot_button).set_label(label).set_style(style).set_id(id);

  return button;
}

string strToLower(string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}