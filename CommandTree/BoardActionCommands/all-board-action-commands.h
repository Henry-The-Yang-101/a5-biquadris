#ifndef ALL_BOARD_ACTION_COMMANDS_H
#define ALL_BOARD_ACTION_COMMANDS_H

#include "board-action-command.h"

class LeftCommand : public BoardActionCommand {
  LeftCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class RightCommand : public BoardActionCommand {
  RightCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class DownCommand : public BoardActionCommand {
  DownCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class DropCommand : public BoardActionCommand {
  DropCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class ClockwiseCommand : public BoardActionCommand {
  ClockwiseCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class CounterClockwiseCommand : public BoardActionCommand {
  CounterClockwiseCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class HoldCommand : public BoardActionCommand {
  HoldCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class HeavyEffectCommand : public BoardActionCommand {
  HeavyEffectCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class RestartCommand : public BoardActionCommand {
  RestartCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

#endif
