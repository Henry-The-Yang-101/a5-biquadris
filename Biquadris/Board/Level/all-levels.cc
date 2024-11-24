#include "all-levels.h"
#include "../Block/block-types.h"

// LevelZero definition
LevelZero::LevelZero(BoardProxy & boardProxy, const std::string & blockSequenceFileName) :
  Level{0, false, boardProxy, blockSequenceFileName} {}

// RandomizedLevel definitions

// Block probability distributions given the following block type order:
//   I, J, L, O, S, Z, T
const std::vector<int> LEVEL_ONE_BLOCK_PROBABILITY_DISTRIBUTION = {2, 2, 2, 2, 1, 1, 2};
const std::vector<int> LEVEL_TWO_BLOCK_PROBABILITY_DISTRIBUTION = {1, 1, 1, 1, 1, 1, 1};
const std::vector<int> LEVEL_THREE_AND_FOUR_BLOCK_PROBABILITY_DISTRIBUTION = {1, 1, 1, 1, 2, 2, 1};

LevelOne::LevelOne(BoardProxy & boardProxy, const std::string & blockSequenceFileName) :
  RandomizedLevel{1, false, boardProxy, blockSequenceFileName, LEVEL_ONE_BLOCK_PROBABILITY_DISTRIBUTION} {}

LevelTwo::LevelTwo(BoardProxy & boardProxy, const std::string & blockSequenceFileName) :
  RandomizedLevel{2, false, boardProxy, blockSequenceFileName, LEVEL_TWO_BLOCK_PROBABILITY_DISTRIBUTION} {}

LevelThree::LevelThree(BoardProxy & boardProxy, const std::string & blockSequenceFileName) :
  RandomizedLevel{3, true, boardProxy, blockSequenceFileName, LEVEL_THREE_AND_FOUR_BLOCK_PROBABILITY_DISTRIBUTION} {}

LevelFour::LevelFour(BoardProxy & boardProxy, const std::string & blockSequenceFileName) :
  RandomizedLevel{4, true, boardProxy, blockSequenceFileName, LEVEL_THREE_AND_FOUR_BLOCK_PROBABILITY_DISTRIBUTION} {}

bool LevelFour::checkCustomRuleCondition() const {
  return (this->boardProxy.getNumBlocksPlacedWithoutClearing() > 0) && 
         (this->boardProxy.getNumBlocksPlacedWithoutClearing() % 5 == 0);
}

void LevelFour::executeCustomRuleAction() {
  std::unique_ptr<Block> starBlock = std::make_unique<StarBlock>(this->boardProxy, this->getLevelNum());
  starBlock->drop();
} // might not be enough logic for edge cases
