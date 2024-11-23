#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

template <typename Dependency>
class Command {
  bool hasArgs;

  protected:
    Dependency & dependency;
    std::string commandName;

  public:
    Command(Dependency & dependency, std::string commandName, bool hasArgs) : 
      dependency{dependency}, commandName{commandName}, hasArgs{hasArgs} {}

    virtual void execute(int multiplier) = 0;
    virtual void execute(int multiplier, std::vector<std::string> args) {}

    virtual ~Command() = default;
};

#endif
