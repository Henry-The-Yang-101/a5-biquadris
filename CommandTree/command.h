#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

class Command {
  std::string commandName;
  bool hasArgs;

  protected:
    Command(std::string commandName, bool hasArgs) : 
      commandName{commandName}, hasArgs{hasArgs} {}

  public:
    bool getHasArgs() { return this->hasArgs; }
    std::string getCommandName() { return this->commandName; }
    void setCommandName(std::string newName) { this->commandName = newName; }
    virtual void execute(int multiplier) = 0;
    virtual void execute(int multiplier, std::vector<std::string> && args) {}
    virtual ~Command() = default;
};

#endif
