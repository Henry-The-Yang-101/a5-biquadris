#include <stdexcept>
#include <iostream>
#include <fstream>
#include "all-meta-commands.h"

// RenameCommand definitions
RenameCommand::RenameCommand(CommandTree & commandTree, std::string commandName) : MetaCommand{commandTree, commandName, true} {}

void RenameCommand::execute(int multiplier, std::vector<std::string> && args) {
  if (args.size() >= 2) {
    std::unique_ptr<Command> previousCommand = this->dependency.removeCommand(args[0]);
    previousCommand->setCommandName(args[1]);
    this->dependency.addCommand(std::move(previousCommand));
  } 
}

// MacroCommand definitions
MacroCommand::MacroCommand(CommandTree & commandTree, std::string commandName) : MetaCommand{commandTree, commandName, true} {}

void MacroCommand::execute(int multiplier, std::vector<std::string> && args) {
  if (args.size() >= 2) {
    std::string macroInstanceName = *(args.begin());
    args.erase(args.begin());

    std::unique_ptr<Command> macroInstance = std::make_unique<MacroInstanceCommand>(this->dependency, macroInstanceName, std::move(args));
    this->dependency.addCommand(std::move(macroInstance));
  }
}

// MacroInstanceCommand definitions
MacroInstanceCommand::MacroInstanceCommand(CommandTree & commandTree, std::string commandName, std::vector<std::string> && commandSequence) : MetaCommand{commandTree, commandName, false}, commandSequence{commandSequence} {}

void MacroInstanceCommand::execute(int multiplier) {
  for (int i = 0; i < multiplier; i++) {
    for (std::string commandName : this->commandSequence) {
      this->dependency.findAndExecute(commandName);
    }
  }
}

// SequenceCommand definitions
SequenceCommand::SequenceCommand(CommandTree & commandTree, std::string commandName) : MetaCommand{commandTree, commandName, true} {}

void SequenceCommand::execute(int multiplier, std::vector<std::string> && args) {
  if (args.size() > 0) {
    std::string commandSequenceFilePath = SequenceCommand::filePathPrefix + args[0];
    for (int i = 0; i < multiplier; i++) {
      std::fstream commandSequenceFile{commandSequenceFilePath};

      if (!commandSequenceFile.is_open()) {
        throw std::runtime_error("Failed to open \"" + args[0] + "\" command sequence file");
      }

      std::string currentLine;
      while (std::getline(commandSequenceFile, currentLine)) {
        this->dependency.findAndExecute(currentLine);
      }

      commandSequenceFile.close();
    }
  }
}
