#ifndef OUTPUT_COMMAND_H
#define OUTPUT_COMMAND_H

#include <iostream>
#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class OutputCommand : Command<ostream> {
  OutputCommand(ostream & out) : Command<ostream>{out} {}
  virtual ~OutputCommand() = default;
};

#endif
