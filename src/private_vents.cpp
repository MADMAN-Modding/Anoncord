#include "private_vents.h"
#include <format>
#include "utilities.h"

PrivateVents::PrivateVents(cluster *bot) : bot(bot) {}

void PrivateVents::sendDM(int userID, string description)
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
  bot->direct_message_create(userID, message);
}

void PrivateVents::dmAccepted(int userID, int anonUserID)
{
  // Makes the separate parts of the message
  const string description = "<@" + to_string(userID) + ">";

  // Makes the embed
  embed embed;
  embed = makeEmbed("Requested Accepted!", description + "accepted your request!",
                    dpp::colors::green);

  // Makes the message to be sent
  dpp::message message;
  message.add_embed(embed);

  // Sends the message to the anonymous user
  bot->direct_message_create(anonUserID, message);
}

void PrivateVents::responseDM(bool accepted, int userID, int anonUserID) {
  string statusText = accepted ? "Accepted" : "Rejected";

  // Makes the separate parts of the message
  const string description = "<@" + to_string(userID) + ">";

  // Makes the embed
  embed embed;
  embed = makeEmbed("Requested " + statusText + " !", strToLower(statusText) + " your request!",
                    dpp::colors::green);

  // Makes the message to be sent
  dpp::message message;
  message.add_embed(embed);

  // Sends the message to the anonymous user
  bot->direct_message_create(anonUserID, message);
}