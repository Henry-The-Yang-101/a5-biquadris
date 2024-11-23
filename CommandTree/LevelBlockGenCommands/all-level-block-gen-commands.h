#ifndef ALL_LEVEL_BLOCK_GEN_COMMANDS_H
#define ALL_LEVEL_BLOCK_GEN_COMMANDS_H

#include "level-block-gen-command.h"

class LevelUpCommand : public LevelBlockGenCommand {
  LevelUpCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class LevelDownCommand : public LevelBlockGenCommand {
  LevelDownCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class RandomCommand : public LevelBlockGenCommand {
  RandomCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class NoRandomCommand : public LevelBlockGenCommand {
  NoRandomCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) {}
  void execute(int multiplier, std::vector<std::string> args) override;
};

class ForceCommand : public LevelBlockGenCommand {
  ForceCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) {}
  void execute(int multiplier, std::vector<std::string> args) override;
};

class ReplaceBlockCommand : public LevelBlockGenCommand {
  ReplaceBlockCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

#endif
