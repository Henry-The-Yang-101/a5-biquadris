#include <memory>
#include "block.h"

// BlockCell definitions

BlockCell::BlockCell(BoardProxy & boardProxy, int clearScore, char type) : boardProxy{boardProxy}, clearScore{clearScore}, type{type} {}

BlockCell::~BlockCell() {
  this->boardProxy.increaseScore(this->clearScore);
}


// Block definitions

Block::Block(BoardProxy& boardProxy, char type, int numLevel) : boardProxy{boardProxy}, type{type}, numLevel{numLevel}, rotation{Rotation::UP} {}

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

std::vector<CellCoordinate> Block::getCellCoordinates(Rotation newRotation, int newRightShift, int newDownShift) const {
  std::vector<CellCoordinate> baseShape = std::move(this->getBaseShape(newRotation));

  for (CellCoordinate & cell : baseShape) {
    cell.first += newRightShift;
    cell.second += newDownShift;
  }
  return baseShape;
}

bool Block::checkPositionValidity(const std::vector<CellCoordinate> & coords) const {
  for (CellCoordinate c : coords) {
    if () {
      
    }
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
  std::vector<CellCoordinate> dropCoords = std::move(this->getDropPreviewCellCoordinate());
  std::shared_ptr<BlockCell> blockCell = std::make_shared<BlockCell>(this->boardProxy, this->getClearScore(), this->type);

  for (CellCoordinate & cell : dropCoords) {
    this->boardProxy.insertBlockCell(cell.first, cell.second, blockCell);
  }
}

std::vector<CellCoordinate> Block::getCellCoordinates() const {
  return this->getCellCoordinates(this->rotation, this->rightShift, this->downShift);
}

std::vector<CellCoordinate> Block::getDropPreviewCellCoordinate() const {
  // checking from downShift + 1 because after constructing Block and running checkPositionValidity
  // to check game over, the currentposition should always be valid
  std::vector<CellCoordinate> currentCellCoordinate = std::move(this->getCellCoordinates(this->rotation, this->rightShift, this->downShift + 1));
  int maxDownShift = 0;

  while (true) {
    for (CellCoordinate & cell : currentCellCoordinate) {
      cell.second++;
    }
    if (!this->checkPositionValidity(currentCellCoordinate)) {
      break;
    }
    maxDownShift++;
  }
  for (CellCoordinate & cell : currentCellCoordinate) {
    cell.second--;
  }

  return currentCellCoordinate;
}

bool Block::checkPositionValidity() const {
  return this->checkPositionValidity(this->getCellCoordinates());
}

