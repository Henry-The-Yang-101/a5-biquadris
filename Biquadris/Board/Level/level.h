#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "../board-proxy.h"

class Level {
  private:
    const int numLevel;
    const bool heavy;
    std::string blockSequenceFileName;
    std::ifstream blockSequenceFileStream;
    std::vector<std::unique_ptr<Block>> blockBacklog;
  
    std::unique_ptr<Block> generateBlock(char blockType) const;
  protected:
    BoardProxy & boardProxy;

    Level(int numLevel, bool heavy, BoardProxy & boardProxy, std::string & blockSequenceFileName);
    void setBlockSequenceFile(std::string & blockSequenceFile);
    virtual char chooseBlockType() const;
    virtual ~Level() = default;

  public:
    static const int BACKLOG_SIZE = 4;

    std::unique_ptr<Block> cycleBlock();
    virtual bool checkRuleCondition() const;
    virtual void executeRuleAction();
};

class RandomizedLevel : public Level {
  private:
    const int denom;
    const std::map<int, char> blockCumulativeDistributionMap;
    bool randomEnabled;

    static std::map<int, char> convertNumeratorsToCumulativeDistributionMap(std::vector<int> & distributionNumerators);

  protected:
    RandomizedLevel(int numLevel, bool heavy, BoardProxy & boardProxy, std::string & blockSequenceFileName, int denomLCM, std::vector<int> & distributionNumerators);
    char chooseBlockType() const override;
    virtual ~RandomizedLevel() = default;

  public: 
    void enableRandom();
    void disableRandom();
    void disableRandom(std::string & blockSequenceFile);
};

#endif
