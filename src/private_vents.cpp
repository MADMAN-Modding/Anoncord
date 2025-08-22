#include "private_vents.hpp"

PrivateVents::PrivateVents(cluster &bot) : bot(bot) {}

void PrivateVents::sendDM(int userID, string description, cluster &bot)
{
  // Makes the separate parts of the message
  const embed embed =
      makeEmbed("You've been sent a DM request!", description, userID);
  const component acceptButton =
      makeButton("Accept DM", component_style::cos_primary,
                 "accept_dm_" + to_string(userID));
  const component rejectButton =
      makeButton("Reject DM", component_style::cos_danger,
                 "reject_dm_" + to_string(userID));

  // Creates the message
  dpp::message message;
  message.add_embed(embed)
      .add_component(acceptButton)
      .add_component(rejectButton);

  // Sends the message to the user
  bot.direct_message_create(userID, message);
}

void PrivateVents::dmAccepted(int userID, int anonUserID)
{
  // Makes the separate parts of the message
  const string message = "<@" + to_string(userID) + ">";

  embed embed;
  embed = makeEmbed("Requested Accepted!", message + "accepted your request!",
                    dpp::colors::green);
}

embed PrivateVents::makeEmbed(string title, string description,
                              uint32_t color)
{
  embed embed = dpp::embed();
  embed.set_color(color).set_title(title).set_description(description);

  return embed;
};

component PrivateVents::makeButton(string label, dpp::component_style style,
                                   string id)
{
  component button;
  button.set_type(cot_button).set_label(label).set_style(style).set_id(id);

  return button;
};
