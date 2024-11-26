#ifndef ALL_LEVELS_H
#define ALL_LEVELS_H

#include "level.h"

class LevelZero : public Level {
  private:
    static const std::vector<int> BLOCK_PROBABILITY_DISTRIBUTION;
  public:
    LevelZero(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
};

class LevelOne : public RandomizedLevel {
  private:
    static const std::vector<int> BLOCK_PROBABILITY_DISTRIBUTION;
  public:
    LevelOne(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
};

class LevelTwo : public RandomizedLevel {
  private:
    static const std::vector<int> BLOCK_PROBABILITY_DISTRIBUTION;
  public:
    LevelTwo(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
};

class LevelThree : public RandomizedLevel {
  private:
    static const std::vector<int> BLOCK_PROBABILITY_DISTRIBUTION;
  public:
    LevelThree(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
};

class LevelFour : public RandomizedLevel {
  private:
    static const std::vector<int> BLOCK_PROBABILITY_DISTRIBUTION;
    static const int BLOCKS_PLACED_WITHOUT_CLEARING_NEEDED_TO_DROP_STAR_BLOCK = 5;

  public:
    LevelFour(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
    bool checkCustomRuleCondition() const override;
    void executeCustomRuleAction() override;
};

#endif
