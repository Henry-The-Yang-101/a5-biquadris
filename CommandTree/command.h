#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

class Command {
  bool hasArgs;

  protected:
    std::string commandName;

    Command(std::string commandName, bool hasArgs) : 
      commandName{commandName}, hasArgs{hasArgs} {}
    
    virtual ~Command() = default;

  public:
    virtual void execute(int multiplier) = 0;
    virtual void execute(int multiplier, std::vector<std::string> args) {}
};

#endif
