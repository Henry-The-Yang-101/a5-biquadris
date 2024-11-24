#include <memory>
#include "block.h"

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;


// BlockCell definitions
BlockCell::BlockCell(BoardProxy & boardProxy, int clearScore, char type) : boardProxy{boardProxy}, clearScore{clearScore}, type{type} {}

BlockCell::~BlockCell() {
  this->boardProxy.increaseScore(this->clearScore);
}


// Block definitions
Block::Block(BoardProxy& boardProxy, int numLevel) : boardProxy{boardProxy}, numLevel{numLevel}, rotation{Rotation::UP} {}

Block::Rotation Block::rotationAfterRotatedClockwise(Rotation rotation) {
  switch(rotation) {
    case Rotation::UP: return Rotation::RIGHT;
    case Rotation::RIGHT: return Rotation::DOWN;
    case Rotation::DOWN: return Rotation::LEFT;
    case Rotation::LEFT: return Rotation::UP;
  }
}

Block::Rotation Block::rotationAfterRotatedCounterClockwise(Rotation rotation) {
  switch(rotation) {
    case Rotation::UP: return Rotation::LEFT;
    case Rotation::LEFT: return Rotation::DOWN;
    case Rotation::DOWN: return Rotation::RIGHT;
    case Rotation::RIGHT: return Rotation::UP;
  }
}

int Block::getClearScore() const {
  return (this->numLevel + 1) * (this->numLevel + 1);
}

BlockCellCoordinates Block::getCellCoordinates(Rotation newRotation, int newRightShift, int newDownShift) const {
  BlockCellCoordinates baseShape = std::move(this->getBaseShape(newRotation));

  for (CellCoordinate & cell : baseShape) {
    cell.first += newRightShift;
    cell.second += newDownShift;
  }
  return baseShape;
}

bool Block::checkPositionValidity(const BlockCellCoordinates & cellCoords) const {
  for (const CellCoordinate & cell : cellCoords) {
    if (cell.first < 0 || cell.first >= this->boardProxy.getBoardWidth()) return false;
    if (cell.second >= this->boardProxy.getBoardHeight()) return false;
    if (!this->boardProxy.cellAvailable(cell.first, cell.second)) return false;
  }
  return true;
}

bool Block::moveLeft() {
  bool valid = this->checkPositionValidity(this->getCellCoordinates(this->rotation, this->rightShift - 1, this->downShift));
  
  if (valid) {
    this->rightShift--;
  }
  return valid;
}

bool Block::moveRight() {
  bool valid = this->checkPositionValidity(this->getCellCoordinates(this->rotation, this->rightShift + 1, this->downShift));
  
  if (valid) {
    this->rightShift++;
  }
  return valid;
}

bool Block::rotateClockwise() {
  bool valid = this->checkPositionValidity(this->getCellCoordinates(rotationAfterRotatedClockwise(this->rotation),
                                                                       this->rightShift,
                                                                       this->downShift));

  if (valid) {
    this->rotation = rotationAfterRotatedClockwise(this->rotation);
  }
  return valid;
}

bool Block::rotateCounterClockwise() {
  bool valid = this->checkPositionValidity(this->getCellCoordinates(rotationAfterRotatedCounterClockwise(this->rotation),
                                                                       this->rightShift,
                                                                       this->downShift));
  
  if (valid) {
    this->rotation = rotationAfterRotatedCounterClockwise(this->rotation);
  }
  return valid;
}

bool Block::down() {
  bool valid = this->checkPositionValidity(this->getCellCoordinates(this->rotation, this->rightShift, this->downShift + 1));
  
  if (valid) {
    this->downShift++;
  }
  return valid;
}

void Block::drop() {
  BlockCellCoordinates dropCoords = std::move(this->getDropPreviewCellCoordinate());
  std::shared_ptr<BlockCell> blockCell = std::make_shared<BlockCell>(this->boardProxy, this->getClearScore(), this->getType());

  for (const CellCoordinate & cell : dropCoords) {
    this->boardProxy.insertBlockCell(cell.first, cell.second, blockCell);
  }
}

BlockCellCoordinates Block::getCellCoordinates() const {
  return this->getCellCoordinates(this->rotation, this->rightShift, this->downShift);
}

BlockCellCoordinates Block::getDropPreviewCellCoordinate() const {
  // checking from downShift + 1 because after constructing Block and running checkPositionValidity
  // to check game over, the currentposition should always be valid
  BlockCellCoordinates currentCellCoordinates = std::move(this->getCellCoordinates(this->rotation, this->rightShift, this->downShift + 1));
  int maxDownShift = 0;

  while (true) {
    for (CellCoordinate & cell : currentCellCoordinates) {
      cell.second++;
    }
    if (!this->checkPositionValidity(currentCellCoordinates)) {
      break;
    }
    maxDownShift++;
  }
  for (CellCoordinate & cell : currentCellCoordinates) {
    cell.second--;
  }

  return currentCellCoordinates;
}

bool Block::checkPositionValidity() const {
  return this->checkPositionValidity(this->getCellCoordinates());
}
