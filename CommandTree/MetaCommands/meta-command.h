#ifndef META_COMMAND_H
#define META_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class CommandTree; //forward declare

class MetaCommand : public Command<CommandTree *> {
  protected:
    MetaCommand(CommandTree *& commandTree, std::string commandName, bool hasArgs) : 
      Command<CommandTree *>{commandTree, commandName, hasArgs} {}

    virtual ~MetaCommand() = default;
};

#endif
