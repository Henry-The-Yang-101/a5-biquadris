#ifndef META_COMMAND_H
#define META_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class CommandTree; //forward declare

class MetaCommand : Command<CommandTree *> {
  MetaCommand(CommandTree *& commandTree) : Command<CommandTree *>{commandTree} {}
  virtual ~MetaCommand() = default;
};

#endif
