#ifndef MANAGE_GAME_STATE_COMMAND_H
#define MANAGE_GAME_STATE_COMMAND_H

#include "../aggregate-command.h"
#include "../Biquadris/biquadris-proxies.h"

class ManageGameStateCommand : public AggregateCommand<ManageGameStateProxy> {
  protected:
    ManageGameStateCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName, bool hasArgs) : 
      AggregateCommand<ManageGameStateProxy>{biquadrisProxy, commandName, hasArgs} {}

    virtual ~ManageGameStateCommand() = default;
};

#endif
