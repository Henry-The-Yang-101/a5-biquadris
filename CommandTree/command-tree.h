#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

#include <memory>
#include <utility>
#include <unordered_map>
#include "command.h"

class CommandTree {
  class CommandNode;
  std::unique_ptr<CommandNode> root;

  public:
    CommandTree();
    void addCommand(std::unique_ptr<Command> command);
    std::unique_ptr<Command> removeCommand(std::string commandName);
    void findAndExecute(std::string inputLine);

  private:
    class CommandNode {
      public:
        CommandNode() = default;
        std::unordered_map<char, std::unique_ptr<CommandNode>> children;
        std::unique_ptr<Command> command;
    };
    Command* find(std::string commandName) const;
    std::unique_ptr<Command> recursiveRemoveCommand(CommandNode* node, const std::string& commandName, size_t index);
};

#endif
