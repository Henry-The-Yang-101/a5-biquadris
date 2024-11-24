#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "../board-proxy.h"

class Level {
  const int numLevel;
  const bool heavy;
  BoardProxy & boardProxy;
  bool random;
  std::string sequenceFileName;
  std::vector<std::unique_ptr<Block>> blockBacklog;

  protected:
    Level(int numLevel, bool heavy, BoardProxy & boardProxy, bool random, std::string sequenceFileName);
    virtual std::unique_ptr<Block> generateBlock() = 0;

  public:
    static const int BACKLOG_SIZE = 4;

    std::unique_ptr<Block> cycleBlock();
    virtual bool checkRuleCondition() const { return false; }
    virtual void executeRuleAction() {}
};

#endif
