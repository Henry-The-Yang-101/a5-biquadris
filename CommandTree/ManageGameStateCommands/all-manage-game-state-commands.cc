#include "all-manage-game-state-commands.h"

// BonusOnCommand definitions
BonusOnCommand::BonusOnCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName) : ManageGameStateCommand{biquadrisProxy, commandName, false} {}

void BonusOnCommand::execute(int multiplier) {
  this->dependency.setBonusFeatures(true);
}

// BonusOffCommand definitions
BonusOffCommand::BonusOffCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName) : ManageGameStateCommand{biquadrisProxy, commandName, false} {}

void BonusOffCommand::execute(int multiplier) {
  this->dependency.setBonusFeatures(false);
}

// DevOnCommand definitions
DevOnCommand::DevOnCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName) : ManageGameStateCommand{biquadrisProxy, commandName, false} {}

void BonusOnCommand::execute(int multiplier) {
  this->dependency.setDevMode(true);
}

// DevOffCommand definitions
DevOffCommand::DevOffCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName) : ManageGameStateCommand{biquadrisProxy, commandName, false} {}

void BonusOnCommand::execute(int multiplier) {
  this->dependency.setDevMode(false);
}
