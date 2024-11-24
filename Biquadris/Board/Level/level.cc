#include "level.h"

Level::Level(int numLevel, bool heavy, BoardProxy & boardProxy, bool random, std::string sequenceFileName) :
  numLevel{numLevel}, heavy{heavy}, boardProxy{boardProxy}, random{random}, sequenceFileName{sequenceFileName} {

  for (int i = 0; i < BACKLOG_SIZE; i++) {
    this->blockBacklog.push_back(this->generateBlock());
  }
}

std::unique_ptr<Block> Level::cycleBlock() {
  std::unique_ptr<Block> poppedBlock = std::move(this->blockBacklog[0]);

  this->blockBacklog.erase(this->blockBacklog.begin());
  this->blockBacklog.push_back(this->generateBlock());

  return std::move(poppedBlock);
}
