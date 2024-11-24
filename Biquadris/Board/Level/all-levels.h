#ifndef ALL_LEVELS_H
#define ALL_LEVELS_H

#include "../level.h"

class LevelZero : public Level {
  public:
    LevelZero(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
};

class LevelOne : public RandomizedLevel {
  public:
    LevelOne(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
};

class LevelTwo : public RandomizedLevel {
  public:
    LevelTwo(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
};

class LevelThree : public RandomizedLevel {
  public:
    LevelThree(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
};

class LevelFour : public RandomizedLevel {
  public:
    LevelFour(BoardProxy & boardProxy, const std::string & blockSequenceFileName);
    bool checkCustomRuleCondition() const override;
    void executeCustomRuleAction() override;
};

#endif
