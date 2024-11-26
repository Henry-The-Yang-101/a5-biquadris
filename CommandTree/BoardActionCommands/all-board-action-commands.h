#ifndef ALL_BOARD_ACTION_COMMANDS_H
#define ALL_BOARD_ACTION_COMMANDS_H

#include "board-action-command.h"

class LeftCommand : public BoardActionCommand {
  public:
    LeftCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class RightCommand : public BoardActionCommand {
  public:
    RightCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class DownCommand : public BoardActionCommand {
  public:
    DownCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class DropCommand : public BoardActionCommand {
  public:
    DropCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class ClockwiseCommand : public BoardActionCommand {
  public:
    ClockwiseCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class CounterClockwiseCommand : public BoardActionCommand {
  public:
    CounterClockwiseCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class HoldCommand : public BoardActionCommand {
  public:
    HoldCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class HeavyEffectCommand : public BoardActionCommand {
  public:
    HeavyEffectCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class RestartCommand : public BoardActionCommand {
  public:
    RestartCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

#endif
