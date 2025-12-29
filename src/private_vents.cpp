#include "private_vents.h"
#include "utilities.h"

private_vents::private_vents(dpp::cluster *bot, unordered_map<dpp::snowflake, user_state> *user_states)
{
  this->bot = bot;
  this->user_states = user_states;
}

void private_vents::send_dm(dpp::snowflake user_id, dpp::snowflake anon_user_id, string description)
{
  // Makes the separate parts of the message
  const dpp::embed embed =
      make_embed("You've been sent a DM request!", description, user_id);
  const dpp::component accept_button =
      make_button("Accept DM", dpp::component_style::cos_primary,
                  "accept-dm_" + to_string(user_id) + "_" + to_string(anon_user_id));
  const dpp::component reject_button =
      make_button("Reject DM", dpp::component_style::cos_danger,
                  "reject-dm_" + to_string(user_id) + "_" + to_string(anon_user_id));

  // Creates the message
  dpp::message message;
  message.add_embed(embed)
      .add_component(dpp::component().add_component(accept_button).add_component(reject_button));

  // Sends the message to the user
  dm_user(bot, user_id, message);
}

void private_vents::dm_accepted(dpp::snowflake user_id, dpp::snowflake anon_user_id)
{
  response_dm(true, user_id, anon_user_id, dpp::colors::green);
}

void private_vents::dm_rejected(dpp::snowflake user_id, dpp::snowflake anon_user_id)
{
  response_dm(false, user_id, anon_user_id, dpp::colors::red);
}

unordered_map<dpp::snowflake, user_state> *private_vents::get_user_states()
{
  return this->user_states;
}

void private_vents::typing_dm(dpp::typing_start_t event)
{

  auto user_id = event.typing_user.id;

  if (this->user_states->find(user_id) != this->user_states->end())
  {
    ::user_state state = this->user_states->at(user_id);

    if (state.get_user_mode() == user_state::HELPING)
    {
      auto anon = state.get_partner_user_id();

      auto embed = make_embed("Typing", "Your helper is typing", dpp::colors::blue);

      dm_user(this->bot, anon, embed);
    }
    else
    {
      auto helper = state.get_partner_user_id();

      auto embed = make_embed("Typing", "Anon is typing", dpp::colors::blue);

      dm_user(this->bot, helper, embed);
    }
  }
}

void private_vents::response_dm(bool accepted, dpp::snowflake user_id, dpp::snowflake anon_user_id, uint32_t color)
{
  string status_text = accepted ? "Accepted" : "Rejected";

  // Makes the separate parts of the message
  const string user = "<@" + to_string(user_id) + "> ";

  // Makes the embed
  dpp::embed embed;
  embed = make_embed("Requested " + status_text + "!", user + str_to_lower(status_text) + " your request!",
                     color);

  // Makes the message to be sent
  dpp::message message;
  message.add_embed(embed);

  // Sends the message to the anonymous user
  dm_user(bot, anon_user_id, message);
}