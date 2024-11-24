#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstdlib>
#include "level.h"
#include "../Block/block-types.h"

// intellesense tweakin wtf

// Level definitions
Level::Level(int numLevel, bool heavy, BoardProxy & boardProxy, std::string & blockSequenceFileName) :
  numLevel{numLevel}, heavy{heavy}, boardProxy{boardProxy}, blockSequenceFileName{std::move(blockSequenceFileName)}, 
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
    case 'I': return std::make_unique<IBlock>(this->boardProxy, this->numLevel);
    case 'J': return std::make_unique<JBlock>(this->boardProxy, this->numLevel);
    case 'L': return std::make_unique<LBlock>(this->boardProxy, this->numLevel);
    case 'O': return std::make_unique<OBlock>(this->boardProxy, this->numLevel);
    case 'S': return std::make_unique<SBlock>(this->boardProxy, this->numLevel);
    case 'Z': return std::make_unique<ZBlock>(this->boardProxy, this->numLevel);
    case 'T': return std::make_unique<TBlock>(this->boardProxy, this->numLevel);
    case 'i': return std::make_unique<IBlock>(this->boardProxy, this->numLevel);
    case 'j': return std::make_unique<JBlock>(this->boardProxy, this->numLevel);
    case 'l': return std::make_unique<LBlock>(this->boardProxy, this->numLevel);
    case 'o': return std::make_unique<OBlock>(this->boardProxy, this->numLevel);
    case 's': return std::make_unique<SBlock>(this->boardProxy, this->numLevel);
    case 'z': return std::make_unique<ZBlock>(this->boardProxy, this->numLevel);
    case 't': return std::make_unique<TBlock>(this->boardProxy, this->numLevel);
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

std::unique_ptr<Block> Level::cycleBlock() {
  std::unique_ptr<Block> poppedBlock = std::move(this->blockBacklog[0]);

  this->blockBacklog.erase(this->blockBacklog.begin());
  this->blockBacklog.push_back(this->generateBlock());

  return std::move(poppedBlock);
}

bool Level::checkRuleCondition() const { return false; }

void Level::executeRuleAction() {}


const char BLOCK_TYPE_ORDER[] = {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};

// RandomizedLevel definitions
RandomizedLevel::RandomizedLevel(int numLevel, bool heavy, BoardProxy & boardProxy, std::string & blockSequenceFileName, int denom, std::vector<int> & distributionNumerators) :
  Level{numLevel, heavy, boardProxy, blockSequenceFileName}, denom{denom}, 
  blockCumulativeDistributionMap{std::move(convertNumeratorsToCumulativeDistributionMap(distributionNumerators))} {}

std::map<int, char> RandomizedLevel::convertNumeratorsToCumulativeDistributionMap(std::vector<int> & distributionNumerators) {
  std::map<int, char> outputBlockCumulativeDistributionMap;
  int cumulativeKeyAdjustment = 0;
  
  for (size_t i = 0; i < distributionNumerators.size(); i++) {
    for (int j = 0; j < distributionNumerators[i]; j++) {
      outputBlockCumulativeDistributionMap[cumulativeKeyAdjustment + j] = BLOCK_TYPE_ORDER[i];
    }
    cumulativeKeyAdjustment += distributionNumerators[i];
  }
  return outputBlockCumulativeDistributionMap;
}

char RandomizedLevel::chooseBlockType() const {
  if (this->randomEnabled) {
    int randomChoice = rand() % this->denom;

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
