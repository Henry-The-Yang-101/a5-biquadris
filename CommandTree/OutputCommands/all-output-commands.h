#ifndef ALL_OUTPUT_COMMANDS_H
#define ALL_OUTPUT_COMMANDS_H

#include "output-command.h"

class HintCommand : public OutputCommand {
  public:
    HintCommand(std::ostream & out, std::string commandName);
    void execute(int multiplier) override;
};

#endif
