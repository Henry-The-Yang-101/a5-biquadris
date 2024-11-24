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

bool Block::checkPositionValidity(Rotation newRotation, int newrightShift, int newDownShift) const {
  //
}

bool Block::moveLeft() {
  bool valid = this->checkPositionValidity(this->rotation, this->rightShift - 1, this->downShift);
  
  if (valid) {
    this->rightShift--;
  }
  return valid;
}

bool Block::moveRight() {
  bool valid = this->checkPositionValidity(this->rotation, this->rightShift + 1, this->downShift);
  
  if (valid) {
    this->rightShift++;
  }
  return valid;
}

bool Block::rotateClockwise() {
  bool valid = this->checkPositionValidity(rotationAfterRotatedClockwise(this->rotation), this->rightShift, this->downShift);
  
  if (valid) {
    this->rotation = rotationAfterRotatedClockwise(this->rotation);
  }
  return valid;
}

bool Block::rotateCounterClockwise() {
  bool valid = this->checkPositionValidity(rotationAfterRotatedCounterClockwise(this->rotation), this->rightShift, this->downShift);
  
  if (valid) {
    this->rotation = rotationAfterRotatedCounterClockwise(this->rotation);
  }
  return valid;
}


bool Block::checkPositionValidity() const {
  return this->checkPositionValidity(this->rotation, this->rightShift, this->downShift);
}



