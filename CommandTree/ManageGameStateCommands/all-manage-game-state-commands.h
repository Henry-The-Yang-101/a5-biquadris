#ifndef ALL_MANAGE_GAME_STATE_COMMANDS_H
#define ALL_MANAGE_GAME_STATE_COMMANDS_H

#include "manage-game-state-command.h"

class BonusOnCommand : public ManageGameStateCommand {
  public:
    BonusOnCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~BonusOnCommand() = default;
};

class BonusOffCommand : public ManageGameStateCommand {
  public:
    BonusOffCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~BonusOffCommand() = default;
};

class DevOnCommand : public ManageGameStateCommand {
  public:
    DevOnCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~DevOnCommand() = default;
};

class DevOffCommand : public ManageGameStateCommand {
  public:
    DevOffCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~DevOffCommand() = default;
};

#endif
