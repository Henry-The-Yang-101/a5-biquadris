#ifndef AGGREGATE_COMMAND_H
#define AGGREGATE_COMMAND_H

#include "command.h"

template <typename Dependency>

class AggregateCommand : public Command {
  protected:
    Dependency & dependency;

    AggregateCommand(Dependency & dependency, std::string commandName, bool hasArgs) :
      Command{commandName, hasArgs}, dependency{dependency} {}
    
    virtual ~AggregateCommand() = default;
};

#endif
