#ifndef BOARD_ACTION_COMMAND_H
#define BOARD_ACTION_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class BoardActionCommand : public Command<BoardActionProxy> {
  protected:
    BoardActionCommand(BoardActionProxy & biquadrisProxy, std::string commandName, bool hasArgs) :
      Command<BoardActionProxy>{biquadrisProxy, commandName, hasArgs} {}

    virtual ~BoardActionCommand() = default;
};

#endif
