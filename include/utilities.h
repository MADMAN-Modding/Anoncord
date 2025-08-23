#include <dpp/dpp.h>
#include <iostream>

using namespace dpp;
using namespace std;

/// @brief Makes an embed to be sent to the user
/// @param title Embed's title
/// @param description Embed's description
/// @param color Embed's color (use dpp::colors)
/// @return Embed made from supplied values
embed makeEmbed(string title, string description, uint32_t color);

/// @brief Makes a button to be attached to an embed
/// @param label Button's label
/// @param style Button's style
/// @param id Button's id
/// @return Button made from supplied values
component makeButton(string label, component_style style, string id);

/// @brief Converts the supplied string to lowercase
/// @param s String to be converted
/// @return Converted string 
string strToLower(string s);
