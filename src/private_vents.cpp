#include "private_vents.h"
#include "utilities.h"

PrivateVents::PrivateVents(cluster *bot) : bot(bot) {}

void PrivateVents::sendDM(snowflake userID, snowflake anonUserID, string description)
{

  cout << userID << "\n";

  // Makes the separate parts of the message
  const embed embed =
      makeEmbed("You've been sent a DM request!", description, userID);
  const component acceptButton =
      makeButton("Accept DM", component_style::cos_primary,
        "accept-dm_" + to_string(userID) + "_" + to_string(anonUserID));
        const component rejectButton =
      makeButton("Reject DM", component_style::cos_danger,
                 "reject-dm_" + to_string(userID));

  // Creates the message
  dpp::message message;
  message.add_embed(embed)
      .add_component(dpp::component().add_component(acceptButton))
      .add_component(dpp::component().add_component(rejectButton));

  // Sends the message to the user
  bot->direct_message_create(userID, message);
}

void PrivateVents::dmAccepted(snowflake userID, snowflake anonUserID)
{
  responseDM(true, userID, anonUserID);
}

void PrivateVents::dmRejected(snowflake userID, snowflake anonUserID)
{
  responseDM(false, userID, anonUserID);
}

void PrivateVents::responseDM(bool accepted, snowflake userID, snowflake anonUserID) {
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