#ifndef META_COMMAND_H
#define META_COMMAND_H

#include "command.h"
#include "commandTree.h"

class CommandTree;

class MetaCommand : public AggregateCommand<CommandTree *> {
  protected:
    MetaCommand(CommandTree *& commandTree, std::string commandName, bool hasArgs) : 
      AggregateCommand<CommandTree *>{commandTree, commandName, hasArgs} {}

    virtual ~MetaCommand() = default;
};

#endif
