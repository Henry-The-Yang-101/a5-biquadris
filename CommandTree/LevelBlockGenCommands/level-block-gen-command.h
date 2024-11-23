#ifndef LEVEL_BLOCK_GEN_COMMAND_H
#define LEVEL_BLOCK_GEN_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class LevelBlockGenCommand : public Command<LevelBlockGenProxy> {
  protected:
    LevelBlockGenCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName, bool hasArgs) : 
      Command<LevelBlockGenProxy>{biquadrisProxy, commandName, hasArgs} {}

    virtual ~LevelBlockGenCommand() = default;
};

#endif
