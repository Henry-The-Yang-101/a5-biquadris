#ifndef MANAGE_GAME_STATE_COMMAND_H
#define MANAGE_GAME_STATE_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class ManageGameStateCommand : Command<ManageGameStateProxy> {
  ManageGameStateCommand(ManageGameStateProxy & biquadrisProxy) : Command<ManageGameStateProxy>{biquadrisProxy} {}
  virtual ~ManageGameStateCommand() = default;
};

#endif
