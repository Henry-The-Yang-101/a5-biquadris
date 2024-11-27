#ifndef ALL_META_COMMANDS_H
#define ALL_META_COMMANDS_H

#include "meta-command.h"

class RenameCommand : public MetaCommand {
  public:
    RenameCommand(CommandTree & commandTree, std::string commandName);
    void execute(int multiplier) {}
    void execute(int multiplier, std::vector<std::string> && args) override;
};

class MacroCommand : public MetaCommand {
  public:
    MacroCommand(CommandTree & commandTree, std::string commandName);
    void execute(int multiplier) {}
    void execute(int multiplier, std::vector<std::string> && args) override;
};

class MacroInstanceCommand : public MetaCommand {
  const std::vector<std::string> commandSequence;
  public:
    MacroInstanceCommand(CommandTree & commandTree, std::string commandName, std::vector<std::string> && commandSequence);
    void execute(int multiplier);
};

class SequenceCommand : public MetaCommand {
  static const std::string COMMAND_SEQUENCE_FILES_PATH_PREFIX;
  public:
    SequenceCommand(CommandTree & commandTree, std::string commandName);
    void execute(int multiplier) {}
    void execute(int multiplier, std::vector<std::string> && args) override;
};

#endif
