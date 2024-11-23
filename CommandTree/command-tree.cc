#include <stdexcept>
#include <sstream>
#include <vector>
#include "command-tree.h"

CommandTree::CommandTree() : root{std::make_unique<CommandNode>()} {}

void CommandTree::addCommand(std::unique_ptr<Command> command) {
  CommandNode *currentNode = this->root.get();

  for (char c : command->getCommandName()) {
    if (!currentNode->children[c]) {
      currentNode->children[c] = std::make_unique<CommandNode>();
    }
    currentNode = currentNode->children[c].get();
  }
  currentNode->command = std::move(command);
}

std::unique_ptr<Command> CommandTree::removeCommand(std::string commandName) {
  return recursiveRemoveCommand(this->root.get(), commandName, 0);
}

void CommandTree::findAndExecute(std::string inputLine) {
  std::istringstream inputStream{inputLine};

  int multiplier;
  inputStream >> multiplier;

  if (inputStream.fail()) {
    multiplier = 1;
    inputStream.clear();
  }

  if (multiplier > 0) {
    std::string commandName;
    if (inputStream >> commandName) {
      Command* command = this->find(commandName);

      if (command->getHasArgs()) {
        std::string currentArg;
        std::vector<std::string> args;

        while (inputStream >> currentArg) {
          args.push_back(currentArg);
        }

        command->execute(multiplier, std::move(args));
      } else {
        command->execute(multiplier);
      }
    }
  }
}

Command* CommandTree::find(std::string commandName) const {
  CommandNode *currentNode = this->root.get();
  for (char c : commandName) {
    if (currentNode->children.find(c) != currentNode->children.end()) {
      currentNode = currentNode->children[c].get();
    } else {
      throw std::runtime_error(std::string{"Command with name \""} + commandName + "\" not found");
    }
  }
  if (currentNode->command != nullptr) {
    return currentNode->command.get();
  }

  while (currentNode->children.size() == 1) {
    currentNode = currentNode->children.begin()->second.get();
    if (currentNode->command != nullptr) {
      return currentNode->command.get();
    }
  }

  if (currentNode->children.empty()) {
    throw std::runtime_error(std::string{"Command with name \""} + commandName + "\" not found");
  } else {
    throw std::runtime_error(std::string{"Ambiguous command name \""} + commandName + "\"");
  }
}

std::unique_ptr<Command> CommandTree::recursiveRemoveCommand(CommandNode* node, const std::string& commandName, size_t index) {
  // Base case: Reached the end of the provided commandName
  if (index == commandName.size()) {
    if (node->command != nullptr) {
      // If this node has a command return it
      return std::move(node->command);
    } else if (node->children.size() == 1) {
      // if it only has one child traverse it and return the command if there is enough provided in the commandName to
      //   differentiate it from all other commands (autocomplete)
      return recursiveRemoveCommand(node->children.begin()->second.get(), commandName, index);
    } else if (node->children.size() == 0) {
      // No command found
      throw std::runtime_error(std::string{"Command with name \""} + commandName + "\" not found");
    } else {
      // More than one possible command given the provided commandName
      throw std::runtime_error(std::string{"Ambiguous command name \""} + commandName + "\"");
    }
  }

  // Recursive case: Traverse to the next child node based on the current character
  char currentChar = commandName[index];
  auto it = node->children.find(currentChar);
  if (it == node->children.end()) {
    throw std::runtime_error(std::string{"Command with name \""} + commandName + "\" not found");
  }

  // Recursively request to remove the command in the child node
  std::unique_ptr<Command> removedCommand = recursiveRemoveCommand(it->second.get(), commandName, index + 1);

  // Cleanup: Remove child node if it has no children or command
  if (it->second->command == nullptr && it->second->children.empty()) {
    node->children.erase(it);
  }

  return removedCommand;
}

