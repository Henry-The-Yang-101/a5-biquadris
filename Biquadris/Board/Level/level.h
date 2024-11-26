#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_set>
#include "../board-proxy.h"
#include "../Block/block.h"

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;
using BlockAttributes = std::pair<BlockCellCoordinates, char>;

class Level {
  private:
    static const std::string BLOCK_SEQUENCE_FILES_PATH_PREFIX;
    static const size_t BACKLOG_SIZE;
    const int levelNum;
    const bool heavy;
    std::string blockSequenceFileName;
    std::ifstream blockSequenceFileStream;
    std::vector<std::unique_ptr<Block>> blockBacklog;
  
    std::unique_ptr<Block> generateBlock(char blockType) const;
  protected:
    BoardProxy & boardProxy;

    Level(int levelNum, bool heavy, BoardProxy & boardProxy, const std::string & blockSequenceFileName);
    virtual char chooseBlockType();

  public:
    int getLevelNum() const;
    bool getHeavy() const;
    std::vector<BlockAttributes> getBlockAttributesBacklog() const;
    void setBlockSequenceFile(std::string & blockSequenceFile);
    std::unique_ptr<Block> cycleBlock();
    virtual bool checkCustomRuleCondition() const;
    virtual void executeCustomRuleAction();
    virtual ~Level() = default;
};

class RandomizedLevel : public Level {
  private:
    const std::map<int, char> blockCumulativeDistributionMap;
    const int distributionTotal;
    bool randomEnabled;

    static std::map<int, char> convertDistributionToCumulativeMap(const std::vector<int> & distribution);
    static int calculateTotal(const std::vector<int> & distribution);

  protected:
    RandomizedLevel(int levelNum, bool heavy, BoardProxy & boardProxy, const std::string & blockSequenceFileName, const std::vector<int> & distribution);
    char chooseBlockType() override;

  public:
    static const std::unordered_set<int> RANDOMIZED_LEVEL_NUMS;
    void setRandomEnabled(bool enabled);
    virtual ~RandomizedLevel() = default;
};

#endif
