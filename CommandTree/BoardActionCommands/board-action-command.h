#ifndef BOARD_ACTION_COMMAND_H
#define BOARD_ACTION_COMMAND_H

#include "aggregate-command.h"
#include "../Biquadris/biquadris-proxies.h"

class BoardActionCommand : public AggregateCommand<BoardActionProxy> {
  protected:
    BoardActionCommand(BoardActionProxy & biquadrisProxy, std::string commandName, bool hasArgs) :
      AggregateCommand<BoardActionProxy>{biquadrisProxy, commandName, hasArgs} {}

    virtual ~BoardActionCommand() = default;
};

#endif
