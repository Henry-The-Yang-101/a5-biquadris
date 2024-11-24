#ifndef ALL_LEVEL_BLOCK_GEN_COMMANDS_H
#define ALL_LEVEL_BLOCK_GEN_COMMANDS_H

#include "level-block-gen-command.h"

class LevelUpCommand : public LevelBlockGenCommand {
  public:
    LevelUpCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~LevelUpCommand() = default;
};

class LevelDownCommand : public LevelBlockGenCommand {
  public:
    LevelDownCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~LevelDownCommand() = default;
};

class RandomCommand : public LevelBlockGenCommand {
  public:
    RandomCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~RandomCommand() = default;
};

class NoRandomCommand : public LevelBlockGenCommand {
  public:
    NoRandomCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) {}
    void execute(int multiplier, std::vector<std::string> && args) override;
    ~NoRandomCommand() = default;
};

class ForceCommand : public LevelBlockGenCommand {
  public:
    ForceCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) {}
    void execute(int multiplier, std::vector<std::string> && args) override;
    ~ForceCommand() = default;
};

class ReplaceBlockCommand : public LevelBlockGenCommand {
  public:
    ReplaceBlockCommand(LevelBlockGenProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~ReplaceBlockCommand() = default;
};

#endif
