#ifndef ALL_LEVEL_BLOCK_GEN_COMMANDS_H
#define ALL_LEVEL_BLOCK_GEN_COMMANDS_H

#include "level-block-gen-command.h"

class LevelUpCommand : public LevelBlockGenCommand {
  public:
    LevelUpCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class LevelDownCommand : public LevelBlockGenCommand {
  public:
    LevelDownCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class RandomCommand : public LevelBlockGenCommand {
  public:
    RandomCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

class NoRandomCommand : public LevelBlockGenCommand {
  public:
    NoRandomCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) {}
    void execute(int multiplier, std::vector<std::string> args) override;
};

class ForceCommand : public LevelBlockGenCommand {
  public:
    ForceCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) {}
    void execute(int multiplier, std::vector<std::string> args) override;
};

class ReplaceBlockCommand : public LevelBlockGenCommand {
  public:
    ReplaceBlockCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
};

#endif
