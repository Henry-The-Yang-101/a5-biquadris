#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

#include <memory>
#include <utility>
#include <unordered_map>
#include "command.h"

class commandTree {
  public:
    void addCommand(Command command);
    void removeCommand(std::string commandName);
    void findAndExecute(std::string input);

  private:
    class CommandNode {
      public:
        std::unordered_map<char, Command> children;
        std::unique_ptr<Command> command;
    };

    std::unique_ptr<CommandNode> root;
};

#endif
