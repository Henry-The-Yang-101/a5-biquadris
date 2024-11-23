#ifndef LEVEL_BLOCK_GEN_COMMAND_H
#define LEVEL_BLOCK_GEN_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class LevelBlockGenCommand : Command<LevelBlockGenProxy> {
  LevelBlockGenCommand(LevelBlockGenProxy & biquadrisProxy) : Command<LevelBlockGenProxy>{biquadrisProxy} {}
  virtual ~LevelBlockGenCommand() = default;
};

#endif
