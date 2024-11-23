#ifndef BOARD_ACTION_COMMAND_H
#define BOARD_ACTION_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class BoardActionCommand : Command<BoardActionProxy> {
  BoardActionCommand(BoardActionProxy & biquadrisProxy) : Command<BoardActionProxy>{biquadrisProxy} {}
  virtual ~BoardActionCommand() = default;
};

#endif
