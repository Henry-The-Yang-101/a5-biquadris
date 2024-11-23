#ifndef OUTPUT_COMMAND_H
#define OUTPUT_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class OutputCommand : public Command<ostream> {
  protected:
    OutputCommand(ostream & out, std::string commandName, bool hasArgs) : 
      Command<ostream>{out, commandName, hasArgs} {}

    virtual ~OutputCommand() = default;
};

#endif
