#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

template <typename Dependency>
class Command {
  Dependency & dependency;
  string commandName;
  bool hasArgs;

  public:
    Command(Dependency & dependency) : dependency{dependency} {}

    virtual void execute(int multiplier) = 0;
    virtual void execute(int multiplier, std::vector<std::string> args) {}

    virtual ~Command() = default;
};

#endif
