#include "all-level-block-gen-commands.h"

// LevelUpCommand definitions
LevelUpCommand::LevelUpCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName) : LevelBlockGenCommand{biquadrisProxy, commandName, false} {}

void LevelUpCommand::execute(int multiplier) {
  this->dependency.levelUp(multiplier);
}

// LevelDownCommand definitions
LevelDownCommand::LevelDownCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName) : LevelBlockGenCommand{biquadrisProxy, commandName, false} {}

void LevelDownCommand::execute(int multiplier) {
  this->dependency.levelDown(multiplier);
}

// RandomCommand definitions
RandomCommand::RandomCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName) : LevelBlockGenCommand{biquadrisProxy, commandName, false} {}

void RandomCommand::execute(int multiplier) {
  this->dependency.enableRandom();
}

// NoRandomCommand definitions
NoRandomCommand::NoRandomCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName) : LevelBlockGenCommand{biquadrisProxy, commandName, true} {}

void NoRandomCommand::execute(int multiplier, std::vector<std::string> && args) {
  if (args.size() == 0) {
    this->dependency.disableRandom();
  } else {
    this->dependency.disableRandom(args[0]);
  }
}

// ForceCommand definitions
ForceCommand::ForceCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName) : LevelBlockGenCommand{biquadrisProxy, commandName, true} {}

void ForceCommand::execute(int multiplier, std::vector<std::string> && args) {
  if (args.size() == 1 && args[0].size() > 0) this->dependency.forceEffect(args[0][0]);
}

// ReplaceBlockCommand definitions
ReplaceBlockCommand::ReplaceBlockCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName) : LevelBlockGenCommand{biquadrisProxy, commandName, false} {}

void ReplaceBlockCommand::execute(int multiplier) {
  this->dependency.replaceCurrentBlock(this->getCommandName()[0]);
}
