#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

#include <memory>
#include <utility>
#include <unordered_map>
#include "command.h"

class CommandTree {
  public:
    CommandTree();
    void addCommand(std::unique_ptr<Command> command);
    std::unique_ptr<Command> removeCommand(std::string commandName);
    void findAndExecute(std::string inputLine);

  private:
    class CommandNode {
      public:
        std::unordered_map<char, std::unique_ptr<Command>> children;
        std::unique_ptr<Command> command;
    };

    std::unique_ptr<CommandNode> root;
};

#endif
