#ifndef ALL_BOARD_ACTION_COMMANDS_H
#define ALL_BOARD_ACTION_COMMANDS_H

#include "board-action-command.h"

class LeftCommand : public BoardActionCommand {
  public:
    LeftCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~LeftCommand() = default;
};

class RightCommand : public BoardActionCommand {
  public:
    RightCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~RightCommand() = default;
};

class DownCommand : public BoardActionCommand {
  public:
    DownCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~DownCommand() = default;
};

class DropCommand : public BoardActionCommand {
  public:
    DropCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~DropCommand() = default;
};

class ClockwiseCommand : public BoardActionCommand {
  ClockwiseCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
  ~ClockwiseCommand() = default;
};

class CounterClockwiseCommand : public BoardActionCommand {
  CounterClockwiseCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
  ~CounterClockwiseCommand() = default;
};

class HoldCommand : public BoardActionCommand {
  public:
    HoldCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~HoldCommand() = default;
};

class HeavyEffectCommand : public BoardActionCommand {
  public:
    HeavyEffectCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~HeavyEffectCommand() = default;
};

class RestartCommand : public BoardActionCommand {
  public:
    RestartCommand(BoardActionProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~RestartCommand() = default;
};

#endif
