#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstdlib>
#include "level.h"
#include "../Block/block-types.h"

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;
using BlockAttributes = std::pair<BlockCellCoordinates, char>;

// Level definitions
Level::Level(int levelNum, bool heavy, BoardProxy & boardProxy, const std::string & blockSequenceFileName) :
  levelNum{levelNum}, heavy{heavy}, boardProxy{boardProxy}, blockSequenceFileName{std::move(blockSequenceFileName)}, 
  blockSequenceFileStream{std::ifstream{blockSequenceFileName}} {

  if (!blockSequenceFileStream.is_open()) {
    throw std::runtime_error("Failed to open \"" + blockSequenceFileName + "\" block sequence file");
  }

  for (size_t i = 0; i < BACKLOG_SIZE; i++) {
    this->blockBacklog.push_back(this->generateBlock(this->chooseBlockType()));
  }
}

std::unique_ptr<Block> Level::generateBlock(char blockType) const {
  switch (blockType) {
    case 'I': return std::make_unique<IBlock>(this->boardProxy);
    case 'J': return std::make_unique<JBlock>(this->boardProxy);
    case 'L': return std::make_unique<LBlock>(this->boardProxy);
    case 'O': return std::make_unique<OBlock>(this->boardProxy);
    case 'S': return std::make_unique<SBlock>(this->boardProxy);
    case 'Z': return std::make_unique<ZBlock>(this->boardProxy);
    case 'T': return std::make_unique<TBlock>(this->boardProxy);
    case 'i': return std::make_unique<IBlock>(this->boardProxy);
    case 'j': return std::make_unique<JBlock>(this->boardProxy);
    case 'l': return std::make_unique<LBlock>(this->boardProxy);
    case 'o': return std::make_unique<OBlock>(this->boardProxy);
    case 's': return std::make_unique<SBlock>(this->boardProxy);
    case 'z': return std::make_unique<ZBlock>(this->boardProxy);
    case 't': return std::make_unique<TBlock>(this->boardProxy);
  }
}

char Level::chooseBlockType() {
  char blockType;

  this->blockSequenceFileStream >> std::ws;
  this->blockSequenceFileStream >> blockType;

  if (this->blockSequenceFileStream.fail()) {
    this->blockSequenceFileStream.close();
    this->blockSequenceFileStream.open(this->blockSequenceFileName);
    this->blockSequenceFileStream >> std::ws;
    this->blockSequenceFileStream >> blockType;
    if (this->blockSequenceFileStream.fail()) {
      throw std::ios_base::failure("Provided block sequence file \"" + this->blockSequenceFileName + "\" is invalid.");
    }
  }
  return blockType;
}

int Level::getLevelNum() const { return this->levelNum; }

bool Level::getHeavy() const { return this->heavy; }

std::vector<BlockAttributes> Level::getBlockAttributesBacklog() const {
  std::vector<BlockAttributes> blockAttributesBacklog;

  for (size_t i = 0; i < BACKLOG_SIZE; i++) {
    blockAttributesBacklog.emplace_back(std::move(this->blockBacklog[i]->getCellCoordinates()), this->blockBacklog[i]->getType());
  }
  return blockAttributesBacklog;
}

void Level::setBlockSequenceFile(std::string & blockSequenceFile) {
  std::ifstream tempFileStream{blockSequenceFile};

  if (!tempFileStream.is_open()) {
    throw std::runtime_error("Failed to open \"" + blockSequenceFile + "\" block sequence file; using \"" + this->blockSequenceFileName + "\" instead");
  }

  this->blockSequenceFileName = blockSequenceFile;
  this->blockSequenceFileStream = std::move(tempFileStream);
}

std::unique_ptr<Block> Level::cycleBlock() {
  std::unique_ptr<Block> poppedBlock = std::move(this->blockBacklog[0]);

  this->blockBacklog.erase(this->blockBacklog.begin());
  this->blockBacklog.push_back(this->generateBlock(this->chooseBlockType()));

  return std::move(poppedBlock);
}

bool Level::checkCustomRuleCondition() const { return false; }

void Level::executeCustomRuleAction() {}


const char BLOCK_TYPE_ORDER[] = {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};

// RandomizedLevel definitions
RandomizedLevel::RandomizedLevel(int levelNum, bool heavy, BoardProxy & boardProxy, const std::string & blockSequenceFileName, const std::vector<int> & distribution) :
  Level{levelNum, heavy, boardProxy, blockSequenceFileName}, blockCumulativeDistributionMap{std::move(convertDistributionToCumulativeMap(distribution))}, distributionTotal{calculateTotal(distribution)} {}

const std::unordered_set<int> RandomizedLevel::RANDOMIZED_LEVEL_NUMS = {1, 2, 3, 4};

std::map<int, char> RandomizedLevel::convertDistributionToCumulativeMap(const std::vector<int> & distribution) {
  std::map<int, char> outputBlockCumulativeDistributionMap;
  int cumulativeKeyAdjustment = 0;
  
  for (size_t i = 0; i < distribution.size(); i++) {
    for (int j = 0; j < distribution[i]; j++) {
      outputBlockCumulativeDistributionMap[cumulativeKeyAdjustment + j] = BLOCK_TYPE_ORDER[i];
    }
    cumulativeKeyAdjustment += distribution[i];
  }
  return outputBlockCumulativeDistributionMap;
}

int RandomizedLevel::calculateTotal(const std::vector<int> & distribution) {
  int total = 0;

  for (int i : distribution) {
    total += i;
  }
  return total;
}

char RandomizedLevel::chooseBlockType() {
  if (this->randomEnabled) {
    int randomChoice = rand() % this->distributionTotal;

    return this->blockCumulativeDistributionMap.find(randomChoice)->second;
  } else {
    return Level::chooseBlockType();
  }
}

void RandomizedLevel::setRandomEnabled(bool enabled) { this->randomEnabled = enabled; }
