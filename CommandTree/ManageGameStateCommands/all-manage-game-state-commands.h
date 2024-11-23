#ifndef ALL_MANAGE_GAME_STATE_COMMANDS_H
#define ALL_MANAGE_GAME_STATE_COMMANDS_H

#include "manage-game-state-command.h"

class BonusOnCommand : public ManageGameStateCommand {
  BonusOnCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class BonusOffCommand : public ManageGameStateCommand {
  BonusOffCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class DevOnCommand : public ManageGameStateCommand {
  DevOnCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

class DevOffCommand : public ManageGameStateCommand {
  DevOffCommand(ManageGameStateProxy & biquadrisProxy, std::string commandName);
  void execute(int multiplier) override;
};

#endif
