#ifndef MANAGE_GAME_STATE_COMMAND_H
#define MANAGE_GAME_STATE_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class ManageGameStateCommand : public Command<ManageGameStateProxy> {
  protected:
    ManageGameStateCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName, bool hasArgs) : 
      Command<ManageGameStateProxy>{biquadrisProxy, commandName, hasArgs} {}

    virtual ~ManageGameStateCommand() = default;
};

#endif
