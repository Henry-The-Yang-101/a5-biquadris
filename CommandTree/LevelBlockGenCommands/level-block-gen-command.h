#ifndef LEVEL_BLOCK_GEN_COMMAND_H
#define LEVEL_BLOCK_GEN_COMMAND_H

#include "../aggregate-command.h"
#include "../Biquadris/biquadris-proxies.h"

class LevelBlockGenCommand : public AggregateCommand<LevelBlockGenProxy> {
  protected:
    LevelBlockGenCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName, bool hasArgs) : 
      AggregateCommand<LevelBlockGenProxy>{biquadrisProxy, commandName, hasArgs} {}

    virtual ~LevelBlockGenCommand() = default;
};

#endif
