#include "biquadris-proxies.h"

// ManageGameStateProxy definitions
ManageGameStateProxy::ManageGameStateProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void ManageGameStateProxy::setBonusFeatures(bool isOn) {
  this->gameEngine.setBonusFeatures(isOn);
}

void ManageGameStateProxy::setDevMode(bool isOn) {
  this->gameEngine.setDevMode(isOn);
}

void ManageGameStateProxy::gameOver() {
  this->gameEngine.gameOver();
}

// VisualEffectProxy definitions
VisualEffectProxy::VisualEffectProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void VisualEffectProxy::blindEffect() {
  this->gameEngine.blindEffect();
}

// BoardActionProxy definitions
BoardActionProxy::BoardActionProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void BoardActionProxy::moveBlockHorizontal(int multipler) {
  this->gameEngine.moveBlockHorizontal(multipler);
}

void BoardActionProxy::moveBlockDown(int multipler) {
  this->gameEngine.moveBlockDown(multipler);
}

void BoardActionProxy::rotateBlockClockwise(int multipler) {
  this->gameEngine.rotateBlockClockwise(multipler);
}

void BoardActionProxy::rotateBlockCounterClockwise(int multipler) {
  this->gameEngine.rotateBlockCounterClockwise(multipler);
}

void BoardActionProxy::dropBlock(int multipler) {
  this->gameEngine.dropBlock(multipler);
}

void BoardActionProxy::holdBlock() {
  this->gameEngine.holdBlock();
}

void BoardActionProxy::restartBoard() {
  this->gameEngine.restartBoard();
}

void BoardActionProxy::heavyEffect() {
  this->gameEngine.heavyEffect();
}

// LevelBlockGenProxy definitions
LevelBlockGenProxy::LevelBlockGenProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void LevelBlockGenProxy::levelUp(int multipler) {
  this->gameEngine.levelUp(multipler);
}

void LevelBlockGenProxy::levelDown(int multipler) {
  this->gameEngine.levelDown(multipler);
}

void LevelBlockGenProxy::enableRandom() {
  this->gameEngine.enableRandom();
}

void LevelBlockGenProxy::disableRandom(string blockSequenceFile) {
  this->gameEngine.disableRandom(blockSequenceFile);
}

void LevelBlockGenProxy::replaceCurrentBlock(char blockType) {
  this->gameEngine.replaceCurrentBlock(blockType);
}

void LevelBlockGenProxy::forceEffect(char blockType) {
  this->gameEngine.forceEffect(blockType);
}
