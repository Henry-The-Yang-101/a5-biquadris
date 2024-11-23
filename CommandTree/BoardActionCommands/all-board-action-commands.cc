#include "all-board-action-commands.h"

// LeftCommand definitions
LeftCommand::LeftCommand(BoardActionProxy & biquadrisProxy, std::string commandName) : BoardActionCommand{biquadrisProxy, commandName, false} {}

void LeftCommand::execute(int multiplier) {
  this->dependency.moveBlockHorizontal(-multiplier);
}

// RightCommand definitions
RightCommand::RightCommand(BoardActionProxy & biquadrisProxy, std::string commandName) : BoardActionCommand{biquadrisProxy, commandName, false} {}

void RightCommand::execute(int multiplier) {
  this->dependency.moveBlockHorizontal(multiplier);
}

// DownCommand definitions
DownCommand::DownCommand(BoardActionProxy & biquadrisProxy, std::string commandName) : BoardActionCommand{biquadrisProxy, commandName, false} {}

void DownCommand::execute(int multiplier) {
  this->dependency.moveBlockDown(multiplier);
}

// DropCommand definitions
DropCommand::DropCommand(BoardActionProxy & biquadrisProxy, std::string commandName) : BoardActionCommand{biquadrisProxy, commandName, false} {}

void DropCommand::execute(int multiplier) {
  this->dependency.dropBlock(multiplier);
}

// ClockwiseCommand definitions
ClockwiseCommand::ClockwiseCommand(BoardActionProxy & biquadrisProxy, std::string commandName) : BoardActionCommand{biquadrisProxy, commandName, false} {}

void ClockwiseCommand::execute(int multiplier) {
  this->dependency.rotateBlockClockwise(multiplier);
}

// CounterClockwiseCommand definitions
CounterClockwiseCommand::CounterClockwiseCommand(BoardActionProxy & biquadrisProxy, std::string commandName) : BoardActionCommand{biquadrisProxy, commandName, false} {}

void CounterClockwiseCommand::execute(int multiplier) {
  this->dependency.rotateBlockCounterClockwise(multiplier);
}

// HoldCommand definitions
HoldCommand::HoldCommand(BoardActionProxy & biquadrisProxy, std::string commandName) : BoardActionCommand{biquadrisProxy, commandName, false} {}

void HoldCommand::execute(int multiplier) {
  this->dependency.holdBlock();
}

// HeavyEffectCommand definitions
HeavyEffectCommand::HeavyEffectCommand(BoardActionProxy & biquadrisProxy, std::string commandName) : BoardActionCommand{biquadrisProxy, commandName, false} {}

void HeavyEffectCommand::execute(int multiplier) {
  this->dependency.heavyEffect();
}

// RestartCommand definitions
RestartCommand::RestartCommand(BoardActionProxy & biquadrisProxy, std::string commandName) : BoardActionCommand{biquadrisProxy, commandName, false} {}

void RestartCommand::execute(int multiplier) {
  this->dependency.restartBoard();
}
