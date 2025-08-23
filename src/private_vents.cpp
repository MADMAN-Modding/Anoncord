#include "private_vents.h"
#include "utilities.h"

PrivateVents::PrivateVents(dpp::cluster *bot) : bot(bot) {}

void PrivateVents::sendDM(dpp::snowflake userID, dpp::snowflake anonUserID, string description)
{

  cout << userID << "\n";

  // Makes the separate parts of the message
  const dpp::embed embed =
      makeEmbed("You've been sent a DM request!", description, userID);
  const dpp::component acceptButton =
      makeButton("Accept DM", dpp::component_style::cos_primary,
        "accept-dm_" + to_string(userID) + "_" + to_string(anonUserID));
        const dpp::component rejectButton =
      makeButton("Reject DM", dpp::component_style::cos_danger,
                 "reject-dm_" + to_string(userID) + "_" + to_string(anonUserID));

  // Creates the message
  dpp::message message;
  message.add_embed(embed)
      .add_component(dpp::component().add_component(acceptButton))
      .add_component(dpp::component().add_component(rejectButton));

  // Sends the message to the user
  bot->direct_message_create(userID, message);
}

void PrivateVents::dmAccepted(dpp::snowflake userID, dpp::snowflake anonUserID)
{
  responseDM(true, userID, anonUserID, dpp::colors::green);
}

void PrivateVents::dmRejected(dpp::snowflake userID, dpp::snowflake anonUserID)
{
  responseDM(false, userID, anonUserID, dpp::colors::red);
}

void PrivateVents::responseDM(bool accepted, dpp::snowflake userID, dpp::snowflake anonUserID, uint32_t color) {
  string statusText = accepted ? "Accepted" : "Rejected";

  // Makes the separate parts of the message
  const string user = "<@" + to_string(userID) + "> ";

  // Makes the embed
  dpp::embed embed;
  embed = makeEmbed("Requested " + statusText + "!", user + strToLower(statusText) + " your request!",
                    color);

  // Makes the message to be sent
  dpp::message message;
  message.add_embed(embed);

  // Sends the message to the anonymous user
  bot->direct_message_create(anonUserID, message);
}