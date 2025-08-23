#include <dpp/dpp.h>
#include <iostream>

using namespace std;

/// @brief Makes an embed to be sent to the user
/// @param title Embed's title
/// @param description Embed's description
/// @param color Embed's color (use dpp::colors)
/// @return Embed made from supplied values
dpp::embed make_embed(string title, string description, uint32_t color);

/// @brief Makes a button to be attached to an embed
/// @param label Button's label
/// @param style Button's style
/// @param id Button's id
/// @return Button made from supplied values
dpp::component make_button(string label, dpp::component_style style, string id);

/// @brief Converts the supplied string to lowercase
/// @param s String to be converted
/// @return Converted string
string str_to_lower(string s);

/// @brief Find all the parts of a string
/// @param s string to search
/// @param delimiter character to separate parts by
/// @return all found parts
vector<string> split_string(const string &s, char delimiter);