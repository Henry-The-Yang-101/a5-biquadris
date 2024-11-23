#ifndef OUTPUT_COMMAND_H
#define OUTPUT_COMMAND_H

#include <iostream>
#include "aggregate-command.h"

class OutputCommand : public AggregateCommand<std::ostream> {
  protected:
    OutputCommand(std::ostream & out, std::string commandName, bool hasArgs) : 
      AggregateCommand<std::ostream>{out, commandName, hasArgs} {}

    virtual ~OutputCommand() = default;
};

#endif
