#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstdlib>
#include "level.h"
#include "../Block/block-types.h"

// intellesense tweakin wtf

// Level definitions
Level::Level(int levelNum, bool heavy, BoardProxy & boardProxy, const std::string & blockSequenceFileName) :
  levelNum{levelNum}, heavy{heavy}, boardProxy{boardProxy}, blockSequenceFileName{std::move(blockSequenceFileName)}, 
  blockSequenceFileStream{std::ifstream{blockSequenceFileName}} {

  if (!blockSequenceFileStream.is_open()) {
    throw std::runtime_error("Failed to open \"" + blockSequenceFileName + "\" block sequence file");
  }

  for (int i = 0; i < BACKLOG_SIZE; i++) {
    this->blockBacklog.push_back(this->generateBlock(this->chooseBlockType()));
  }
}

std::unique_ptr<Block> Level::generateBlock(char blockType) const {
  switch (blockType) {
    case 'I': return std::make_unique<IBlock>(this->boardProxy, this->levelNum);
    case 'J': return std::make_unique<JBlock>(this->boardProxy, this->levelNum);
    case 'L': return std::make_unique<LBlock>(this->boardProxy, this->levelNum);
    case 'O': return std::make_unique<OBlock>(this->boardProxy, this->levelNum);
    case 'S': return std::make_unique<SBlock>(this->boardProxy, this->levelNum);
    case 'Z': return std::make_unique<ZBlock>(this->boardProxy, this->levelNum);
    case 'T': return std::make_unique<TBlock>(this->boardProxy, this->levelNum);
    case 'i': return std::make_unique<IBlock>(this->boardProxy, this->levelNum);
    case 'j': return std::make_unique<JBlock>(this->boardProxy, this->levelNum);
    case 'l': return std::make_unique<LBlock>(this->boardProxy, this->levelNum);
    case 'o': return std::make_unique<OBlock>(this->boardProxy, this->levelNum);
    case 's': return std::make_unique<SBlock>(this->boardProxy, this->levelNum);
    case 'z': return std::make_unique<ZBlock>(this->boardProxy, this->levelNum);
    case 't': return std::make_unique<TBlock>(this->boardProxy, this->levelNum);
  }
}

void Level::setBlockSequenceFile(std::string & blockSequenceFile) {
  std::ifstream tempFileStream{blockSequenceFile};

  if (!tempFileStream.is_open()) {
    throw std::runtime_error("Failed to open \"" + blockSequenceFile + "\" block sequence file; using \"" + this->blockSequenceFileName + "\" instead");
  }

  this->blockSequenceFileName = blockSequenceFile;
  this->blockSequenceFileStream = std::move(tempFileStream);
}

char Level::chooseBlockType() const {
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

std::unique_ptr<Block> Level::cycleBlock() {
  std::unique_ptr<Block> poppedBlock = std::move(this->blockBacklog[0]);

  this->blockBacklog.erase(this->blockBacklog.begin());
  this->blockBacklog.push_back(this->generateBlock());

  return std::move(poppedBlock);
}

bool Level::checkCustomRuleCondition() const { return false; }

void Level::executeCustomRuleAction() {}


const char BLOCK_TYPE_ORDER[] = {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};

// RandomizedLevel definitions
RandomizedLevel::RandomizedLevel(int levelNum, bool heavy, BoardProxy & boardProxy, const std::string & blockSequenceFileName, const std::vector<int> & distribution) :
  Level{levelNum, heavy, boardProxy, blockSequenceFileName}, blockCumulativeDistributionMap{std::move(convertDistributionToCumulativeMap(distribution))}, distributionTotal{calculateTotal(distribution)} {}

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

char RandomizedLevel::chooseBlockType() const {
  if (this->randomEnabled) {
    int randomChoice = rand() % this->distributionTotal;

    return this->blockCumulativeDistributionMap.find(randomChoice)->second;
  } else {
    return Level::chooseBlockType();
  }
}

void RandomizedLevel::enableRandom() { this->randomEnabled = true; }

void RandomizedLevel::disableRandom() { this->randomEnabled = false; }

void RandomizedLevel::disableRandom(std::string & blockSequenceFile) {
  this->disableRandom();
  this->setBlockSequenceFile(blockSequenceFile);
}
